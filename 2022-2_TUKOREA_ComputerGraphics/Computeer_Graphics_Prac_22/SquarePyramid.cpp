#include "SquarePyramid.h"

SquarePyramid* SquarePyramid::getInstance()
{
	static SquarePyramid* pInst = nullptr;

	if (nullptr == pInst)
		pInst = new SquarePyramid;

	return pInst;
}

GLfloat& SquarePyramid::getRotationDegree() { return rotationDegree; }

bool& SquarePyramid::isOnRotation() { return onRotation; }

void SquarePyramid::render(const glm::mat4& parent)
{
	glm::mat4 transformMatrix{ 1.0f };
	glm::mat4 parentMatrix{ 1.0f };
	glm::mat4 revolutionMatrix{ 1.0f };
	glm::mat4 translationMatrix{ 1.0f };
	glm::mat4 rotationMatrix{ 1.0f };
	glm::mat4 scaleMatrix{ 1.0f };
	parentMatrix = parent;
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotationDegree), glm::vec3(0.0f, 1.0f, 0.0f));
	transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
	unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36); // vertices.size() = 18 == 3(index) * 6(numOfFace)
}
