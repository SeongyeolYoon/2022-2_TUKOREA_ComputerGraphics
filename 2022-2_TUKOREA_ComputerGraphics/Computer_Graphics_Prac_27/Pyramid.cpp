#include "Pyramid.h"

Pyramid* Pyramid::pInst = nullptr;

Pyramid::Pyramid()
{

}

Pyramid* Pyramid::getInstance()
{
	if (nullptr == pInst)
		pInst = new Pyramid;

	return pInst;
}

void Pyramid::update()
{

}

void Pyramid::render()
{
	glm::mat4 transformMatrix{ 1.0f };
	glm::mat4 parentMatrix{ 1.0f };
	glm::mat4 revolutionMatrix{ 1.0f };
	glm::mat4 translationMatrix{ 1.0f };
	glm::mat4 rotationMatrix{ 1.0f };
	glm::mat4 scaleMatrix{ 1.0f };
	//parentMatrix = parent;
	scaleMatrix = glm::scale(scaleMatrix, scaleVector);
	translationMatrix = glm::translate(translationMatrix, positionVector);
	transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
	unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, 18); // 0¾Æ·§¸é 6À­¸é  12¾Õ¸é 18¿À¸¥ÂÊ 24µÚ  30¿Þ
}
