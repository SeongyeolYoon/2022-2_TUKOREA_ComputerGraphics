#include "SquarePyramid.h"

SquarePyramid::SquarePyramid()
{

}

SquarePyramid* SquarePyramid::getInstance()
{
	static SquarePyramid* pInst = nullptr;

	if (nullptr == pInst)
		pInst = new SquarePyramid;

	return pInst;
}

void SquarePyramid::initialize()
{

}

void SquarePyramid::update()
{

}

void SquarePyramid::render()
{
	glm::mat4 transformMatrix{ 1.0f };
	glm::mat4 parentMatrix{ 1.0f };
	glm::mat4 revolutionMatrix{ 1.0f };
	glm::mat4 translationMatrix{ 1.0f };
	glm::mat4 rotationMatrix{ 1.0f };
	glm::mat4 scaleMatrix{ 1.0f };
	translationMatrix = glm::translate(translationMatrix, positionVector);
	scaleMatrix = glm::scale(scaleMatrix, scaleVector);
	transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
	unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 54); // vertices.size() = 18 == 3(index) * 6(numOfFace)
}
