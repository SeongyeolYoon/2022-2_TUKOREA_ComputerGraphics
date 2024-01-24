#pragma once
#include "pch.h"
#include "Shader.h"
#include "Orbit.h"

class Light {
private:
	friend class Shader;
	friend class Orbit;
	static Light* pInst;
	std::vector<glm::vec3> verticies;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> colors;
	std::vector<GLuint> vertexIndices;
	std::vector<GLuint> uvIndices;
	std::vector<GLuint> normalIndices;

	GLuint vao;
	GLuint positionVbo;
	GLuint normalVbo;
	GLuint colorVbo;

	glm::vec3 lightPositionVector{ 0.0f, 0.0f, 4.0f };
	glm::vec3 lightColor{ 0.0f,0.0f,0.0f };
	
	GLfloat moveAMount{ 0.1f };
	GLfloat revolutionDegree{ 18.0f };
	GLfloat radian{ 5.0f };

	bool onLight{ false };
	bool revolutionTimer{ false };

	Direction revolutionDirection{ Direction::NONE };
private:
	Light();
public:
	static Light* getInstance();

	void readObj(const char* fileName);

	void on();

	void off();

	bool& isOnRight();

	glm::vec3& getLightColor();

	glm::vec3& getLightPosition();
	
	GLfloat& getMoveAmount();

	GLfloat& getRadian();

	bool& isOnRevolution();

	Direction& getRevolutionDirection();

	GLfloat& getRevolutionDegree();

	void render(glm::mat4&) const;
};
