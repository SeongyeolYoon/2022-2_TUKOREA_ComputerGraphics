#include "Shader.h"

Shader::Shader()
{

}

Shader* Shader::getInstance()
{
	static Shader* pInst = nullptr;

	if (nullptr == pInst)
		pInst = new Shader;

	return pInst;
}

const GLuint& Shader::getShaderProgram() const
{
	return shaderProgram;
}

char* Shader::file2Buffer(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;

	fptr = fopen(file, "rb");
	if (!fptr)
		return NULL;
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;

	return buf;
}

void Shader::makeVertexShader()
{
	vertexSource = file2Buffer("vertex.glsl");

	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, (const GLchar**)(&vertexSource), 0);

	glCompileShader(vertexShader);

	checkCompileError(vertexShader, "vertex");
}

void Shader::makeFragmentShader()
{
	fragmentSource = file2Buffer("fragment.glsl");

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, (const GLchar**)(&fragmentSource), 0);

	glCompileShader(fragmentShader);

	checkCompileError(fragmentShader, "fragment");
}

void Shader::checkCompileError(const GLuint& shaderType, const char* name)
{
	GLint result;

	GLchar errorLog[512];

	glGetShaderiv(shaderType, GL_COMPILE_STATUS, &result);

	if (!result) {
		glGetShaderInfoLog(shaderType, 512, NULL, errorLog);
		std::cerr << "ERROR:" << name << " complie Failed!\n" << errorLog << std::endl;
	}
}

void Shader::glGenerate(std::vector<Snow*>& pSnows, std::vector<Planet*>& pPlanets)
{
	glGenVertexArrays(1, &(Floor::getInstance()->vao));
	glGenBuffers(1, &(Floor::getInstance()->vertexVbo));
	glGenBuffers(1, &(Floor::getInstance()->normalVbo));
	glGenBuffers(1, &(Floor::getInstance()->colorVbo));

	glGenVertexArrays(1, &(SquarePyramid::getInstance()->vao));
	glGenBuffers(1, &(SquarePyramid::getInstance()->vertexVbo));
	glGenBuffers(1, &(SquarePyramid::getInstance()->normalVbo));
	glGenBuffers(1, &(SquarePyramid::getInstance()->colorVbo));

	for (size_t i = 0; i < NumOfSnow; ++i) {
		glGenVertexArrays(1, &(pSnows[i]->vao));
		glGenBuffers(1, &(pSnows[i]->vertexVbo));
		glGenBuffers(1, &(pSnows[i]->normalVbo));
		glGenBuffers(1, &(pSnows[i]->colorVbo));
	}

	for (size_t i = 0; i < NumOfPlanet; ++i) {
		glGenVertexArrays(1, &(pPlanets[i]->vao));
		glGenBuffers(1, &(pPlanets[i]->vertexVbo));
		glGenBuffers(1, &(pPlanets[i]->normalVbo));
		glGenBuffers(1, &(pPlanets[i]->colorVbo));
	}

	glGenVertexArrays(1, &(Light::getInstance()->vao));
	glGenBuffers(1, &(Light::getInstance()->vertexVbo));
	glGenBuffers(1, &(Light::getInstance()->normalVbo));
	glGenBuffers(1, &(Light::getInstance()->colorVbo));
}

void Shader::initShader()
{
	makeVertexShader();
	makeFragmentShader();

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	checkCompileError(shaderProgram, "shader program");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgram);
}

void Shader::initBuffer(std::vector<Snow*>& pSnows, std::vector<Planet*>& pPlanets)
{
	// Floor
	{
		glBindVertexArray(Floor::getInstance()->vao);
		glBindBuffer(GL_ARRAY_BUFFER, Floor::getInstance()->vertexVbo);
		glBufferData(GL_ARRAY_BUFFER, Floor::getInstance()->verticies.size() * sizeof(glm::vec3), Floor::getInstance()->verticies.data(), GL_STATIC_DRAW);
		GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
		glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(pAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, Floor::getInstance()->normalVbo);
		glBufferData(GL_ARRAY_BUFFER, Floor::getInstance()->normals.size() * sizeof(glm::vec3), Floor::getInstance()->normals.data(), GL_STATIC_DRAW);
		GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
		glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(nAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, Floor::getInstance()->colorVbo);
		glBufferData(GL_ARRAY_BUFFER, Floor::getInstance()->colors.size() * sizeof(glm::vec3), Floor::getInstance()->colors.data(), GL_STATIC_DRAW);
		GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
		glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(cAttribute);
	}

	// Snow
	{
		for (size_t i = 0; i < NumOfSnow; ++i) {
			glBindVertexArray(pSnows[i]->vao);
			glBindBuffer(GL_ARRAY_BUFFER, pSnows[i]->vertexVbo);
			glBufferData(GL_ARRAY_BUFFER, pSnows[i]->verticies.size() * sizeof(glm::vec3), pSnows[i]->verticies.data(), GL_STATIC_DRAW);
			GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
			glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, pSnows[i]->normalVbo);
			glBufferData(GL_ARRAY_BUFFER, pSnows[i]->normals.size() * sizeof(glm::vec3), pSnows[i]->normals.data(), GL_STATIC_DRAW);
			GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
			glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, pSnows[i]->colorVbo);
			glBufferData(GL_ARRAY_BUFFER, pSnows[i]->colors.size() * sizeof(glm::vec3), pSnows[i]->colors.data(), GL_STATIC_DRAW);
			GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
			glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(cAttribute);
		}
	}

	// Planet
	{
		for (size_t i = 0; i < NumOfPlanet; ++i) {
			glBindVertexArray(pPlanets[i]->vao);
			glBindBuffer(GL_ARRAY_BUFFER, pPlanets[i]->vertexVbo);
			glBufferData(GL_ARRAY_BUFFER, pPlanets[i]->verticies.size() * sizeof(glm::vec3), pPlanets[i]->verticies.data(), GL_STATIC_DRAW);
			GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
			glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, pPlanets[i]->normalVbo);
			glBufferData(GL_ARRAY_BUFFER, pPlanets[i]->normals.size() * sizeof(glm::vec3), pPlanets[i]->normals.data(), GL_STATIC_DRAW);
			GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
			glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, pPlanets[i]->colorVbo);
			glBufferData(GL_ARRAY_BUFFER, pPlanets[i]->colors.size() * sizeof(glm::vec3), pPlanets[i]->colors.data(), GL_STATIC_DRAW);
			GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
			glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(cAttribute);
		}
	}

	// SquarePyramid
	{
		glBindVertexArray(SquarePyramid::getInstance()->vao);
		glBindBuffer(GL_ARRAY_BUFFER, SquarePyramid::getInstance()->vertexVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SquarePyramid::getInstance()->verticies), SquarePyramid::getInstance()->verticies, GL_STATIC_DRAW);
		GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
		glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(pAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, SquarePyramid::getInstance()->normalVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SquarePyramid::getInstance()->normals), SquarePyramid::getInstance()->normals, GL_STATIC_DRAW);
		GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
		glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(nAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, SquarePyramid::getInstance()->colorVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SquarePyramid::getInstance()->color), SquarePyramid::getInstance()->color, GL_STATIC_DRAW);
		GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
		glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(cAttribute);
	}

	// Light
	{
		glBindVertexArray(Light::getInstance()->vao);
		glBindBuffer(GL_ARRAY_BUFFER, Light::getInstance()->vertexVbo);
		glBufferData(GL_ARRAY_BUFFER, Light::getInstance()->verticies.size() * sizeof(glm::vec3), Light::getInstance()->verticies.data(), GL_STATIC_DRAW);
		GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
		glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(pAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, Light::getInstance()->normalVbo);
		glBufferData(GL_ARRAY_BUFFER, Light::getInstance()->normals.size() * sizeof(glm::vec3), Light::getInstance()->normals.data(), GL_STATIC_DRAW);
		GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
		glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(nAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, Light::getInstance()->colorVbo);
		glBufferData(GL_ARRAY_BUFFER, Light::getInstance()->colors.size() * sizeof(glm::vec3), Light::getInstance()->colors.data(), GL_STATIC_DRAW);
		GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
		glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(cAttribute);

		GLuint lightPosLocation = glGetUniformLocation(shaderProgram, "lightPos"); // lightPos 전달 
		glUniform3f(lightPosLocation, Light::getInstance()->getLightPositionVector().x, Light::getInstance()->getLightPositionVector().y, Light::getInstance()->getLightPositionVector().z);
		GLuint lightColorLocation = glGetUniformLocation(shaderProgram, "lightColor"); // lightColor 전달 
		glUniform3f(lightColorLocation, Light::getInstance()->getLightColor().x, Light::getInstance()->getLightColor().y, Light::getInstance()->getLightColor().z);
		GLuint viewPosLocation = glGetUniformLocation(shaderProgram, "viewPos"); // viewPos 값 전달: 카메라 위치 
		glUniform3f(viewPosLocation, Camera::getInstance()->getPositionVector().x, Camera::getInstance()->getPositionVector().y, Camera::getInstance()->getPositionVector().z);
	}
}

void Shader::release()
{

}
