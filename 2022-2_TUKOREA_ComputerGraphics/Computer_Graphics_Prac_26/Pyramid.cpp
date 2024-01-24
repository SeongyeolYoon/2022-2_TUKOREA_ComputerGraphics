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

Direction& Pyramid::getDirection() { return direction; }

Axis& Pyramid::getAxis() { return axis; }

bool& Pyramid::isOnRotation() { return onRotation; }

void Pyramid::update()
{
	if (onRotation) {
		switch (axis)
		{
		case Axis::NONE:
			break;
		case Axis::X:
			switch (direction)
			{
			case Direction::NONE:
				break;
			case Direction::POSITIVE:
				xRotationDegree += 1.0f;
				break;
			case Direction::NEGATIVE:
				xRotationDegree -= 1.0f;
				break;
			default:
				break;
			}
			break;
		case Axis::Y:
			switch (direction)
			{
			case Direction::NONE:
				break;
			case Direction::POSITIVE:
				yRotationDegree += 1.0f;
				break;
			case Direction::NEGATIVE:
				yRotationDegree -= 1.0f;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void Pyramid::render(glm::mat4& parent)
{
	glm::mat4 transformMatrix{ 1.0f };
	glm::mat4 parentMatrix{ 1.0f };
	glm::mat4 revolutionMatrix{ 1.0f };
	glm::mat4 translationMatrix{ 1.0f };
	glm::mat4 rotationMatrix{ 1.0f };
	glm::mat4 scaleMatrix{ 1.0f };
	parentMatrix = parent;
	scaleMatrix = glm::scale(scaleMatrix,scaleVector);
	translationMatrix = glm::translate(translationMatrix, positionVector);
	switch (axis)
	{
	case Axis::NONE:
		break;
	case Axis::X:
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(xRotationDegree), glm::vec3(1.0f, 0.0f, 0.0f));
		break;
	case Axis::Y:
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(yRotationDegree), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	default:
		break;
	}
	transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
	unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
	glBindVertexArray(vao);

	for (size_t i = 0; i < 6; ++i) {
		glBindVertexArray(vao);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glDrawArrays(GL_TRIANGLES, i * 3, 3); // 0¾Æ·§¸é 6À­¸é  12¾Õ¸é 18¿À¸¥ÂÊ 24µÚ  30¿Þ
	}

	//glDrawArrays(GL_TRIANGLES, 0, 36); // vertices.size() = 18 == 3(index) * 6(numOfFace)
}
