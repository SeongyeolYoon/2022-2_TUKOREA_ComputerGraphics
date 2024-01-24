#pragma once

#include "pch.h"
#include "Shader.h"

class Crane {
private:
	std::vector<glm::vec3> bottomVerticies;
	std::vector<glm::vec3> bottomNormals;
	std::vector<glm::vec3> bottomColors;
	std::vector<glm::vec2> bottomUvs;
	std::vector<GLuint> bottomVertexIndices;
	std::vector<GLuint> bottomNormalIndices;
	std::vector<GLuint> bottomUvIndices;
	GLuint bottomVao;
	GLuint bottomVertexVbo;
	GLuint bottomNormalVbo;
	GLuint bottomColorVbo;
	GLuint bottomUvVbo;
	GLuint bottomTransformLocation;
	glm::vec3 bottomPositionVector{ 0.0f,0.0f,0.0f };
	glm::vec3 bottomScaleVector{ 0.0f,0.0f,0.0f };
	glm::vec3 bottomColorVector{ 0.0f,0.0f,0.0f };

	std::vector<glm::vec3> topVerticies;
	std::vector<glm::vec3> topNormals;
	std::vector<glm::vec3> topColors;
	std::vector<glm::vec2> topUvs;
	std::vector<GLuint> topVertexIndices;
	std::vector<GLuint> topNormalIndices;
	std::vector<GLuint> topUvIndices;
	GLuint topVao;
	GLuint topVertexVbo;
	GLuint topNormalVbo;
	GLuint topColorVbo;
	GLuint topUvVbo;
	GLuint topTransformLocation;
	glm::vec3 topPositionVector{ 0.0f,0.0f,0.0f };
	glm::vec3 topScaleVector{ 0.0f,0.0f,0.0f };
	glm::vec3 topColorVector{ 0.0f,0.0f,0.0f };

	std::vector<glm::vec3> leftHandVerticies;
	std::vector<glm::vec3> leftHandNormals;
	std::vector<glm::vec3> leftHandColors;
	std::vector<glm::vec2> leftHandUvs;
	std::vector<GLuint> leftHandVertexIndices;
	std::vector<GLuint> leftHandNormalIndices;
	std::vector<GLuint> leftHandUvIndices;
	GLuint leftHandVao;
	GLuint leftHandVertexVbo;
	GLuint leftHandNormalVbo;
	GLuint leftHandColorVbo;
	GLuint leftHandUvVbo;
	GLuint leftHandTransformLocation;
	glm::vec3 leftHandPositionVector{ 0.0f,0.0f,0.0f };
	glm::vec3 leftHandScaleVector{ 0.0f,0.0f,0.0f };
	glm::vec3 leftHandColorVector{ 0.0f,0.0f,0.0f };

	std::vector<glm::vec3> rightHandVerticies;
	std::vector<glm::vec3> rightHandNormals;
	std::vector<glm::vec3> rightHandColors;
	std::vector<glm::vec2> rightHandUvs;
	std::vector<GLuint> rightHandVertexIndices;
	std::vector<GLuint> rightHandNormalIndices;
	std::vector<GLuint> rightHandUvIndices;
	GLuint rightHandVao;
	GLuint rightHandVertexVbo;
	GLuint rightHandNormalVbo;
	GLuint rightHandColorVbo;
	GLuint rightHandUvVbo;
	GLuint rightHandTransformLocation;
	glm::vec3 rightHandPositionVector{ 0.0f,0.0f,0.0f };
	glm::vec3 rightHandScaleVector{ 0.0f,0.0f,0.0f };
	glm::vec3 rightHandColorVector{ 0.0f,0.0f,0.0f };

	

	friend class Shader;
private:
	Crane();
public:
	static Crane* getInstance();

	void initialize(const char* objName);

	void readObj(const char* objName);

	void update();

	void render();
};