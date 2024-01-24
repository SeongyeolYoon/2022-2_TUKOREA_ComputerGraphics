#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Shader* Shader::pInst = nullptr;

Shader::Shader()
{

}

Shader* Shader::getInstance()
{
	if (nullptr == pInst)
		pInst = new Shader;

	return pInst;
}

const GLuint& Shader::getShaderProgram() { return shaderProgram; }

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

void Shader::glGenerate(std::vector<Snow*>& pSnow, std::vector<Pillar*>& pPillar)
{
	// Floor
	glGenVertexArrays(1, &(Floor::getInstance()->vao));
	glGenBuffers(1, &(Floor::getInstance()->vertexVbo));
	glGenBuffers(1, &(Floor::getInstance()->normalVbo));
	glGenBuffers(1, &(Floor::getInstance()->uvVbo));
	glGenBuffers(1, &(Floor::getInstance()->colorVbo));
	glGenTextures(1, &(Floor::getInstance()->texture));

	// Pyramid
	glGenVertexArrays(1, &(Pyramid::getInstance()->vao));
	glGenBuffers(1, &(Pyramid::getInstance()->vbo));
	glGenTextures(1, &(Pyramid::getInstance()->texture));

	// Snow
	for (size_t i = 0; i < NumOfSnow; ++i) {
		glGenVertexArrays(1, &(pSnow[i]->vao));
		glGenBuffers(1, &(pSnow[i]->vertexVbo));
		glGenBuffers(1, &(pSnow[i]->normalVbo));
		glGenBuffers(1, &(pSnow[i]->uvVbo));
		glGenBuffers(1, &(pSnow[i]->colorVbo));
		glGenTextures(1, &(pSnow[i]->texture));
	}

	//// Pillar
	//for (size_t i = 0; i < NumOfPillar; ++i) {
	//	glGenVertexArrays(1, &(pPillar[i]->vao));
	//	glGenBuffers(1, &(pPillar[i]->vertexVbo));
	//	glGenBuffers(1, &(pPillar[i]->normalVbo));
	//	glGenBuffers(1, &(pPillar[i]->uvVbo));
	//	glGenBuffers(1, &(pPillar[i]->colorVbo));
	//	glGenTextures(1, &(pPillar[i]->texture));
	//}
}

void Shader::initTexture(std::vector<Snow*>& pSnow, std::vector<Pillar*>& pPillar)
{
	// Floor
	{
		int imageWidth, imageHeight, numberOfChannel;
		glBindTexture(GL_TEXTURE_2D, Floor::getInstance()->texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load("floor.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	// Pyramid
	{
		int imageWidth, imageHeight, numberOfChannel;
		glBindTexture(GL_TEXTURE_2D, Pyramid::getInstance()->texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load("floor.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	// Snow
	{
		for (size_t i = 0; i < NumOfSnow; ++i) {
			int imageWidth, imageHeight, numberOfChannel;
			glBindTexture(GL_TEXTURE_2D, pSnow[i]->texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			stbi_set_flip_vertically_on_load(true);
			unsigned char* data = stbi_load("dice01.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
	}
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

void Shader::initBuffer(std::vector<Snow*>& pSnow, std::vector<Pillar*>& pPillar)
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

		glBindBuffer(GL_ARRAY_BUFFER, Floor::getInstance()->uvVbo);
		glBufferData(GL_ARRAY_BUFFER, Floor::getInstance()->uvs.size() * sizeof(glm::vec2), Floor::getInstance()->uvs.data(), GL_STATIC_DRAW);
		GLint tAttribute = glGetAttribLocation(shaderProgram, "vTexCoord");
		glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glEnableVertexAttribArray(tAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, Floor::getInstance()->colorVbo);
		glBufferData(GL_ARRAY_BUFFER, Floor::getInstance()->colors.size() * sizeof(glm::vec3), Floor::getInstance()->colors.data(), GL_STATIC_DRAW);
		GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
		glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(cAttribute);
	}

	// Snow
	{
		for (size_t i = 0; i < NumOfSnow; ++i) {
			glBindVertexArray(pSnow[i]->vao);
			glBindBuffer(GL_ARRAY_BUFFER, pSnow[i]->vertexVbo);
			glBufferData(GL_ARRAY_BUFFER, pSnow[i]->verticies.size() * sizeof(glm::vec3), pSnow[i]->verticies.data(), GL_STATIC_DRAW);
			GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
			glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, pSnow[i]->normalVbo);
			glBufferData(GL_ARRAY_BUFFER, pSnow[i]->normals.size() * sizeof(glm::vec3), pSnow[i]->normals.data(), GL_STATIC_DRAW);
			GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
			glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, pSnow[i]->uvVbo);
			glBufferData(GL_ARRAY_BUFFER, pSnow[i]->uvs.size() * sizeof(glm::vec2), pSnow[i]->uvs.data(), GL_STATIC_DRAW);
			GLint tAttribute = glGetAttribLocation(shaderProgram, "vTexCoord");
			glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
			glEnableVertexAttribArray(tAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, pSnow[i]->colorVbo);
			glBufferData(GL_ARRAY_BUFFER, pSnow[i]->colors.size() * sizeof(glm::vec3), pSnow[i]->colors.data(), GL_STATIC_DRAW);
			GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
			glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(cAttribute);
		}
	}

	//// Pillar
	//{
	//	for (size_t i = 0; i < NumOfPillar; ++i) {
	//		glBindVertexArray(pPillar[i]->vao);
	//		glBindBuffer(GL_ARRAY_BUFFER, pPillar[i]->vertexVbo);
	//		glBufferData(GL_ARRAY_BUFFER, pPillar[i]->verticies.size() * sizeof(glm::vec3), pPillar[i]->verticies.data(), GL_STATIC_DRAW);
	//		GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
	//		glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	//		glEnableVertexAttribArray(pAttribute);

	//		glBindBuffer(GL_ARRAY_BUFFER, pPillar[i]->normalVbo);
	//		glBufferData(GL_ARRAY_BUFFER, pPillar[i]->normals.size() * sizeof(glm::vec3), pPillar[i]->normals.data(), GL_STATIC_DRAW);
	//		GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
	//		glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	//		glEnableVertexAttribArray(nAttribute);

	//		glBindBuffer(GL_ARRAY_BUFFER, pPillar[i]->uvVbo);
	//		glBufferData(GL_ARRAY_BUFFER, pPillar[i]->uvs.size() * sizeof(glm::vec2), pPillar[i]->uvs.data(), GL_STATIC_DRAW);
	//		GLint tAttribute = glGetAttribLocation(shaderProgram, "vTexCoord");
	//		glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	//		glEnableVertexAttribArray(tAttribute);

	//		glBindBuffer(GL_ARRAY_BUFFER, pPillar[i]->colorVbo);
	//		glBufferData(GL_ARRAY_BUFFER, pPillar[i]->colors.size() * sizeof(glm::vec3), pPillar[i]->colors.data(), GL_STATIC_DRAW);
	//		GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
	//		glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	//		glEnableVertexAttribArray(cAttribute);
	//	}
	//}

	// Pyramid
	{
		glBindVertexArray(Pyramid::getInstance()->vao);
		glBindBuffer(GL_ARRAY_BUFFER, Pyramid::getInstance()->vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Pyramid::getInstance()->vertex), Pyramid::getInstance()->vertex, GL_STATIC_DRAW);

		GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
		glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(0));
		glEnableVertexAttribArray(pAttribute);
		GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
		glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
		glEnableVertexAttribArray(nAttribute);
		GLint tAttribute = glGetAttribLocation(shaderProgram, "vTexCoord");
		glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
		glEnableVertexAttribArray(tAttribute);
	}

	// Light
	{
		GLuint lightPosLocation = glGetUniformLocation(shaderProgram, "lightPos"); // lightPos 전달 
		glUniform3f(lightPosLocation, Light::getInstance()->getPosition().x, Light::getInstance()->getPosition().y, Light::getInstance()->getPosition().z);
		GLuint lightColorLocation = glGetUniformLocation(shaderProgram, "lightColor"); // lightColor 전달 
		glUniform3f(lightColorLocation, Light::getInstance()->getLightColor().x, Light::getInstance()->getLightColor().y, Light::getInstance()->getLightColor().z);
		GLuint viewPosLocation = glGetUniformLocation(shaderProgram, "viewPos"); // viewPos 값 전달: 카메라 위치 
		glUniform3f(viewPosLocation, Camera::getInstance()->getPositionVector().x, Camera::getInstance()->getPositionVector().y, Camera::getInstance()->getPositionVector().z);
	}
}

void Shader::release()
{

}
