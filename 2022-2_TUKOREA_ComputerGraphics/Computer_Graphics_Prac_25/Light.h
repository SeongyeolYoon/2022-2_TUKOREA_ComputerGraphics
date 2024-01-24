#pragma once
#include "pch.h"
#include "Shader.h"

class Light {
private:
	std::vector<glm::vec3> verticies;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> colors;
	std::vector<GLuint> vertexIndices;
	std::vector<GLuint> uvIndices;
	std::vector<GLuint> normalIndices;
	
	GLuint vao;
	GLuint vertexVbo;
	GLuint normalVbo;
	GLuint colorVbo;

	
	glm::mat4 parentMatrix{ 1.0f };
	glm::mat4 transformMatrix{ 1.0f };
	glm::mat4 revolutionMatrix{ 1.0f };
	glm::mat4 translationMatrix{ 1.0f };
	glm::mat4 rotationMatrix{ 1.0f };
	glm::mat4 scaleMatrix{ 1.0f };

	glm::vec3 scaleVector{ 0.0f,0.0f,0.0f };
	glm::vec3 positionVector{ 0.0f,0.0f,0.0f };
	glm::vec3 lightColor{ 1.0f,1.0f,1.0f };

	GLfloat moveAmount{ 0.1f };
	GLfloat revolutionDegree{ 210.0f };

	GLfloat radian{ 280.0f };

	State curState{ State::IDLE };
	GLuint transformLocation;
	friend class Shader;
private:
	Light();
public:
	static Light* getInstance();

	void initialize(const char* fileName);

	void readObj(const char* fileName);

	glm::vec3& getLightPositionVector();
	glm::vec3& getLightColor();

	const GLfloat& getMoveAmount() const;

	State& getState();

	void update();

	void render() const;
};