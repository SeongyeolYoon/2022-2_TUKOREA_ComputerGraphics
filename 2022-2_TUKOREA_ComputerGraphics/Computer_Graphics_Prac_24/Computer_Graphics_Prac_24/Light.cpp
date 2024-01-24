#include "Light.h"

Light::Light()
{

}

Light* Light::getInstance()
{
	static Light* pInst = nullptr;

	if (nullptr == pInst)
		pInst = new Light;

	return pInst;
}

void Light::initialize(const char* objName)
{
	readObj(objName);
	positionVector = glm::vec3(5.0f, 0.0f, 0.0f);
	scaleVector = glm::vec3(0.5f, 0.5f, 0.5f);
}

void Light::readObj(const char* objName)
{
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec3> tempNormals;
	std::vector<glm::vec2> tempUvs;
	GLfloat sumX{ 0.0f }, sumY{ 0.0f }, sumZ{ 0.0f };
	GLfloat aveX{ 0.0f }, aveY{ 0.0f }, aveZ{ 0.0f };
	GLfloat scaleX{ 0.0f }, scaleY{ 0.0f }, scaleZ{ 0.0f };
	GLfloat minX{ 0.0f }, minY{ 0.0f }, minZ{ 0.0f };
	GLfloat maxX{ 0.0f }, maxY{ 0.0f }, maxZ{ 0.0f };
	GLfloat scaleAll{ 0.0f };
	GLfloat sizeX{ 0.0f }, sizeY{ 0.0f }, sizeZ{ 0.0f };

	FILE* objFile;

	fopen_s(&objFile, objName, "rb");

	if (NULL == objFile) {
		std::cerr << "Cannot file open!" << "\n";
		assert(false);
		return;
	}
	while (true) {
		GLchar lineHeader[50000];
		GLint res = fscanf(objFile, "%s", lineHeader);

		if (EOF == res)
			break;

		if (0 == strcmp(lineHeader, "v")) {
			glm::vec3 vertex;
			fscanf(objFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

			if (vertex.x < minX) minX = vertex.x;
			if (vertex.y < minY) minY = vertex.y;
			if (vertex.z < minZ) minZ = vertex.z;
			if (vertex.x > maxX) maxX = vertex.x;
			if (vertex.y > maxY) maxY = vertex.y;
			if (vertex.z > maxZ) maxZ = vertex.z;
			sumX += vertex.x;
			sumY += vertex.y;
			sumZ += vertex.z;

			tempVertices.push_back(vertex);
		}
		else if (0 == strcmp(lineHeader, "vt")) {
			glm::vec2 uv;
			fscanf(objFile, "%f %f\n", &uv.x, &uv.y);
			tempUvs.push_back(uv);
		}
		else if (0 == strcmp(lineHeader, "vn")) {
			glm::vec3 normal;
			fscanf(objFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tempNormals.push_back(normal);
		}
		else if (0 == strcmp(lineHeader, "f")) {
			std::string vertex1, vertex2, vertex3;
			GLuint vertexIndex[3], uvIndex[3], normalIndex[3];
			// vertex uv normal
			int matches = fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

			if (9 != matches) {
				std::cerr << "File can't be read by our simple parser : ( Try exporting with other options )" << "\n";
				return;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	aveX = sumX / vertexIndices.size();
	aveY = sumY / vertexIndices.size();
	aveZ = sumZ / vertexIndices.size();
	scaleX = maxX - minX;
	scaleY = maxY - minY;
	scaleZ = maxZ - minZ;

	glm::vec3 temp;

	for (size_t i = 0; i < vertexIndices.size(); ++i) {
		GLuint vertexIndex = vertexIndices[i];
		temp = tempVertices[vertexIndex - 1];
		temp.x = temp.x - minX;
		temp.y = temp.y - minY;
		temp.z = temp.z - minZ;

		temp.x = ((temp.x * 2.0f) / scaleX) - 1.0f;
		temp.y = ((temp.y * 2.0f) / scaleY) - 1.0f;
		temp.z = ((temp.z * 2.0f) / scaleZ) - 1.0f;

		verticies.push_back(temp);
	}

	for (size_t i = 0; i < uvIndices.size(); ++i) {
		GLuint uvIndex = uvIndices[i];
		glm::vec2 vertex = tempUvs[uvIndex - 1];
		uvs.push_back(vertex);
	}

	for (size_t i = 0; i < normalIndices.size(); ++i) {
		GLuint normalIndex = normalIndices[i];
		glm::vec3 vertex = tempNormals[normalIndex - 1];
		normals.push_back(vertex);
	}

	for (size_t i = 0; i < verticies.size(); ++i) {
		colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	}
}

void Light::update()
{
	switch (revolutionDirection)
	{
	case Direction::NONE:
		break;
	case Direction::POSITIVE:
		if (revolutionTimer) {
			if (revolutionDegree < 360.0f)
				revolutionDegree += 0.01f;
			else
				revolutionDegree = 0.0f;

			Light::getInstance()->getLightDirectionVector().x = 200.0f * glm::radians(sinf(revolutionDegree));
			Light::getInstance()->getLightDirectionVector().z = 200.0f * glm::radians(cosf(revolutionDegree));
		}
		break;
	case Direction::NEGATIVE:
		if (revolutionTimer) {
			if (revolutionDegree > -360.0f)
				revolutionDegree -= 0.01f;
			else
				revolutionDegree = 0.0f;
			Light::getInstance()->getLightDirectionVector().x = 200.0f * glm::radians(sinf(revolutionDegree));
			Light::getInstance()->getLightDirectionVector().z = 200.0f * glm::radians(cosf(revolutionDegree));
		}
		break;
	default:
		break;
	}
}

void Light::render()
{
	glm::mat4 transformMatrix{ 1.0f };
	glm::mat4 parentMatrix{ 1.0f };
	glm::mat4 revolutionMatrix{ 1.0f };
	glm::mat4 translationMatrix{ 1.0f };
	glm::mat4 rotationMatrix{ 1.0f };
	glm::mat4 scaleMatrix{ 1.0f };
	glm::mat4 xRevolution{ 1.0f };
	glm::mat4 yRevolution{ 1.0f };
	// parentMatrix = parent;
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
	//revolutionMatrix = glm::rotate(revolutionMatrix, glm::radians(revolutionDegree), glm::vec3(0.0f, 1.0f, 0.0f));
	translationMatrix = glm::translate(translationMatrix, lightDirectionVector);
	transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
	unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, verticies.size()); // vertices.size() = 18 == 3(index) * 6(numOfFace)
}

void Light::release()
{

}

glm::vec3& Light::getLightDirectionVector()
{
	return lightDirectionVector;
}

glm::vec3& Light::getLightPositionVector()
{
	return lightPositionVector;
}

glm::vec3& Light::getLightColor()
{
	return lightColor;
}

GLuint& Light::getColor() { return color; }

bool& Light::onRevolution() { return revolutionTimer; }

Direction& Light::getRevolutionDirection() { return revolutionDirection; }

GLuint Light::color = 0;
