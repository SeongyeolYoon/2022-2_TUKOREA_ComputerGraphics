#include "Crane.h"

Crane::Crane()
{

}

Crane* Crane::getInstance()
{
	static Crane* pInst = nullptr;

	if (nullptr == pInst)
		pInst = new Crane;

	return pInst;
}

void Crane::initialize(const char* objName)
{
	bottomPositionVector = glm::vec3(0.0f, 0.0f, 0.0f);
	bottomScaleVector = glm::vec3(1.0f, 0.5f, 1.0f);
	bottomColorVector = glm::vec3(1.0f, 0.0f, 0.0f);

	topPositionVector = glm::vec3(0.0f, 0.5f, 0.0f);
	topScaleVector = glm::vec3(0.5f, 0.5f, 0.5f);
	topColorVector = glm::vec3(0.0f, 1.0f, 0.0f);
	
	leftHandPositionVector = glm::vec3(-0.3f, 1.5f, 0.0);
	leftHandScaleVector = glm::vec3(0.1f, 0.5f, 0.1f);
	leftHandColorVector = glm::vec3(0.0f, 0.0f, 1.0f);

	rightHandPositionVector = glm::vec3(0.3f, 1.5f, 0.0f);
	rightHandScaleVector = glm::vec3(0.1f, 0.5f, 0.1f);
	rightHandColorVector = glm::vec3(0.0f, 0.0f, 1.0f);
	readObj(objName);
}

void Crane::readObj(const char* objName)
{
	// Bottom
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
				bottomVertexIndices.push_back(vertexIndex[0]);
				bottomVertexIndices.push_back(vertexIndex[1]);
				bottomVertexIndices.push_back(vertexIndex[2]);
				bottomUvIndices.push_back(uvIndex[0]);
				bottomUvIndices.push_back(uvIndex[1]);
				bottomUvIndices.push_back(uvIndex[2]);
				bottomNormalIndices.push_back(normalIndex[0]);
				bottomNormalIndices.push_back(normalIndex[1]);
				bottomNormalIndices.push_back(normalIndex[2]);
			}
		}
		aveX = sumX / bottomVertexIndices.size();
		aveY = sumY / bottomVertexIndices.size();
		aveZ = sumZ / bottomVertexIndices.size();
		scaleX = maxX - minX;
		scaleY = maxY - minY;
		scaleZ = maxZ - minZ;

		glm::vec3 temp;

		for (size_t i = 0; i < bottomVertexIndices.size(); ++i) {
			GLuint vertexIndex = bottomVertexIndices[i];
			temp = tempVertices[vertexIndex - 1];
			temp.x = temp.x - minX;
			temp.y = temp.y - minY;
			temp.z = temp.z - minZ;

			temp.x = ((temp.x * 2.0f) / scaleX) - 1.0f;
			temp.y = ((temp.y * 2.0f) / scaleY) - 1.0f;
			temp.z = ((temp.z * 2.0f) / scaleZ) - 1.0f;

			bottomVerticies.push_back(temp);
		}

		for (size_t i = 0; i < bottomUvIndices.size(); ++i) {
			GLuint uvIndex = bottomUvIndices[i];
			glm::vec2 vertex = tempUvs[uvIndex - 1];
			bottomUvs.push_back(vertex);
		}

		for (size_t i = 0; i < bottomNormalIndices.size(); ++i) {
			GLuint normalIndex = bottomNormalIndices[i];
			glm::vec3 vertex = tempNormals[normalIndex - 1];
			bottomNormals.push_back(vertex);
		}

		for (size_t i = 0; i < bottomVerticies.size(); ++i) {
			bottomColors.push_back(bottomColorVector);
		}
	}


	// top
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
				topVertexIndices.push_back(vertexIndex[0]);
				topVertexIndices.push_back(vertexIndex[1]);
				topVertexIndices.push_back(vertexIndex[2]);
				topUvIndices.push_back(uvIndex[0]);
				topUvIndices.push_back(uvIndex[1]);
				topUvIndices.push_back(uvIndex[2]);
				topNormalIndices.push_back(normalIndex[0]);
				topNormalIndices.push_back(normalIndex[1]);
				topNormalIndices.push_back(normalIndex[2]);
			}
		}
		aveX = sumX / topVertexIndices.size();
		aveY = sumY / topVertexIndices.size();
		aveZ = sumZ / topVertexIndices.size();
		scaleX = maxX - minX;
		scaleY = maxY - minY;
		scaleZ = maxZ - minZ;

		glm::vec3 temp;

		for (size_t i = 0; i < topVertexIndices.size(); ++i) {
			GLuint vertexIndex = topVertexIndices[i];
			temp = tempVertices[vertexIndex - 1];
			temp.x = temp.x - minX;
			temp.y = temp.y - minY;
			temp.z = temp.z - minZ;

			temp.x = ((temp.x * 2.0f) / scaleX) - 1.0f;
			temp.y = ((temp.y * 2.0f) / scaleY) - 1.0f;
			temp.z = ((temp.z * 2.0f) / scaleZ) - 1.0f;

			topVerticies.push_back(temp);
		}

		for (size_t i = 0; i < topUvIndices.size(); ++i) {
			GLuint uvIndex = topUvIndices[i];
			glm::vec2 vertex = tempUvs[uvIndex - 1];
			topUvs.push_back(vertex);
		}

		for (size_t i = 0; i < topNormalIndices.size(); ++i) {
			GLuint normalIndex = topNormalIndices[i];
			glm::vec3 vertex = tempNormals[normalIndex - 1];
			topNormals.push_back(vertex);
		}

		for (size_t i = 0; i < topVerticies.size(); ++i) {
			topColors.push_back(topColorVector);
		}
	}

	// left hand
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
				leftHandVertexIndices.push_back(vertexIndex[0]);
				leftHandVertexIndices.push_back(vertexIndex[1]);
				leftHandVertexIndices.push_back(vertexIndex[2]);
				leftHandUvIndices.push_back(uvIndex[0]);
				leftHandUvIndices.push_back(uvIndex[1]);
				leftHandUvIndices.push_back(uvIndex[2]);
				leftHandNormalIndices.push_back(normalIndex[0]);
				leftHandNormalIndices.push_back(normalIndex[1]);
				leftHandNormalIndices.push_back(normalIndex[2]);
			}
		}
		aveX = sumX / leftHandVertexIndices.size();
		aveY = sumY / leftHandVertexIndices.size();
		aveZ = sumZ / leftHandVertexIndices.size();
		scaleX = maxX - minX;
		scaleY = maxY - minY;
		scaleZ = maxZ - minZ;

		glm::vec3 temp;

		for (size_t i = 0; i < leftHandVertexIndices.size(); ++i) {
			GLuint vertexIndex = leftHandVertexIndices[i];
			temp = tempVertices[vertexIndex - 1];
			temp.x = temp.x - minX;
			temp.y = temp.y - minY;
			temp.z = temp.z - minZ;

			temp.x = ((temp.x * 2.0f) / scaleX) - 1.0f;
			temp.y = ((temp.y * 2.0f) / scaleY) - 1.0f;
			temp.z = ((temp.z * 2.0f) / scaleZ) - 1.0f;

			leftHandVerticies.push_back(temp);
		}

		for (size_t i = 0; i < leftHandUvIndices.size(); ++i) {
			GLuint uvIndex = leftHandUvIndices[i];
			glm::vec2 vertex = tempUvs[uvIndex - 1];
			leftHandUvs.push_back(vertex);
		}

		for (size_t i = 0; i < leftHandNormalIndices.size(); ++i) {
			GLuint normalIndex = leftHandNormalIndices[i];
			glm::vec3 vertex = tempNormals[normalIndex - 1];
			leftHandNormals.push_back(vertex);
		}

		for (size_t i = 0; i < leftHandVerticies.size(); ++i) {
			leftHandColors.push_back(leftHandColorVector);
		}
	}

	// right Hand
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
				rightHandVertexIndices.push_back(vertexIndex[0]);
				rightHandVertexIndices.push_back(vertexIndex[1]);
				rightHandVertexIndices.push_back(vertexIndex[2]);
				rightHandUvIndices.push_back(uvIndex[0]);
				rightHandUvIndices.push_back(uvIndex[1]);
				rightHandUvIndices.push_back(uvIndex[2]);
				rightHandNormalIndices.push_back(normalIndex[0]);
				rightHandNormalIndices.push_back(normalIndex[1]);
				rightHandNormalIndices.push_back(normalIndex[2]);
			}
		}
		aveX = sumX / rightHandVertexIndices.size();
		aveY = sumY / rightHandVertexIndices.size();
		aveZ = sumZ / rightHandVertexIndices.size();
		scaleX = maxX - minX;
		scaleY = maxY - minY;
		scaleZ = maxZ - minZ;

		glm::vec3 temp;

		for (size_t i = 0; i < rightHandVertexIndices.size(); ++i) {
			GLuint vertexIndex = rightHandVertexIndices[i];
			temp = tempVertices[vertexIndex - 1];
			temp.x = temp.x - minX;
			temp.y = temp.y - minY;
			temp.z = temp.z - minZ;

			temp.x = ((temp.x * 2.0f) / scaleX) - 1.0f;
			temp.y = ((temp.y * 2.0f) / scaleY) - 1.0f;
			temp.z = ((temp.z * 2.0f) / scaleZ) - 1.0f;

			rightHandVerticies.push_back(temp);
		}

		for (size_t i = 0; i < rightHandUvIndices.size(); ++i) {
			GLuint uvIndex = rightHandUvIndices[i];
			glm::vec2 vertex = tempUvs[uvIndex - 1];
			rightHandUvs.push_back(vertex);
		}

		for (size_t i = 0; i < rightHandNormalIndices.size(); ++i) {
			GLuint normalIndex = rightHandNormalIndices[i];
			glm::vec3 vertex = tempNormals[normalIndex - 1];
			rightHandNormals.push_back(vertex);
		}

		for (size_t i = 0; i < rightHandVerticies.size(); ++i) {
			rightHandColors.push_back(rightHandColorVector);
		}
	}
}

void Crane::render()
{
	// bottom
	{
		glm::mat4 parentMatrix{ 1.0f };
		glm::mat4 transformMatrix{ 1.0f };
		glm::mat4 revolutionMatrix{ 1.0f };
		glm::mat4 translationMatrix{ 1.0f };
		glm::mat4 rotationMatrix{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		translationMatrix = glm::translate(translationMatrix, bottomPositionVector);
		scaleMatrix = glm::scale(scaleMatrix, bottomScaleVector);
		transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
		bottomTransformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(bottomTransformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glBindVertexArray(bottomVao);
		glDrawArrays(GL_TRIANGLES, 0, bottomVerticies.size());
	}

	// top
	{
		glm::mat4 parentMatrix{ 1.0f };
		glm::mat4 transformMatrix{ 1.0f };
		glm::mat4 revolutionMatrix{ 1.0f };
		glm::mat4 translationMatrix{ 1.0f };
		glm::mat4 rotationMatrix{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		translationMatrix = glm::translate(translationMatrix, topPositionVector);
		scaleMatrix = glm::scale(scaleMatrix, topScaleVector);
		transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
		topTransformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(topTransformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glBindVertexArray(topVao);
		glDrawArrays(GL_TRIANGLES, 0, topVerticies.size());
	}

	// left hand
	{
		glm::mat4 parentMatrix{ 1.0f };
		glm::mat4 transformMatrix{ 1.0f };
		glm::mat4 revolutionMatrix{ 1.0f };
		glm::mat4 translationMatrix{ 1.0f };
		glm::mat4 rotationMatrix{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		translationMatrix = glm::translate(translationMatrix, leftHandPositionVector);
		scaleMatrix = glm::scale(scaleMatrix, leftHandScaleVector);
		transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
		leftHandTransformLocation= glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(leftHandTransformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glBindVertexArray(leftHandVao);
		glDrawArrays(GL_TRIANGLES, 0, leftHandVerticies.size());
	}

	// right hand
	{
		glm::mat4 parentMatrix{ 1.0f };
		glm::mat4 transformMatrix{ 1.0f };
		glm::mat4 revolutionMatrix{ 1.0f };
		glm::mat4 translationMatrix{ 1.0f };
		glm::mat4 rotationMatrix{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		translationMatrix = glm::translate(translationMatrix, rightHandPositionVector);
		scaleMatrix = glm::scale(scaleMatrix, rightHandScaleVector);
		transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
		rightHandTransformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(rightHandTransformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glBindVertexArray(rightHandVao);
		glDrawArrays(GL_TRIANGLES, 0, rightHandVerticies.size());
	}
}

void Crane::update()
{

}
