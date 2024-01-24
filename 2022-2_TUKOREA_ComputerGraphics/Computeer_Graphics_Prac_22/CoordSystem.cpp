#include "CoordSystem.h"

CoordSystem::CoordSystem()
{

}

CoordSystem* CoordSystem::getInstance()
{
	if (nullptr == pInst)
		pInst = new CoordSystem;

	return pInst;
}

glm::mat4 CoordSystem::render() const 
{
	glm::mat4 coordMatrix{ 1.0f };
	glm::mat4 transform{ 1.0f };
	glm::mat4 xRevolution{ 1.0f };
	glm::mat4 yRevolution{ 1.0f };
	glm::mat4 trans{ 1.0f };
	glm::mat4 rotation{ 1.0f };
	glm::mat4 scaleMatrix{ 1.0f };
	xRevolution = glm::rotate(xRevolution, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	yRevolution = glm::rotate(yRevolution, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//	rotation = glm::rotate(rotation, glm::radians(Hexahedron::getInstance()->getRotationDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
	coordMatrix = xRevolution * yRevolution * trans * rotation * scaleMatrix;
	unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(coordMatrix));
	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, 6); 
	return coordMatrix;
}
