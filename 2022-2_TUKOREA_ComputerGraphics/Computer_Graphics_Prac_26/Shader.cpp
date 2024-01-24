#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Shader* Shader::pInst = nullptr;

Shader* Shader::getInstance()
{
	if (nullptr == pInst)
		pInst = new Shader;

	return pInst;
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

void Shader::glGenerate()
{
	glGenVertexArrays(1, &(CoordSystem::getInstance()->vao));
	glGenBuffers(2, (CoordSystem::getInstance()->vbo));

	glGenVertexArrays(1, &(BackGround::getInstance()->vao));
	glGenBuffers(1, &(BackGround::getInstance()->vertexVbo));
	glGenBuffers(1, &(BackGround::getInstance()->normalVbo));
	glGenBuffers(1, &(BackGround::getInstance()->uvVbo));
	glGenTextures(1, &(BackGround::getInstance()->texture));

	glGenVertexArrays(1, &(Cube::getInstance()->vao));
	glGenBuffers(1, &(Cube::getInstance()->vertexVbo));
	glGenBuffers(1, &(Cube::getInstance()->normalVbo));
	glGenBuffers(1, &(Cube::getInstance()->uvVbo));
	glGenTextures(6, (Cube::getInstance()->textures));

	glGenVertexArrays(1, &(Pyramid::getInstance()->vao));
	glGenBuffers(1, &(Pyramid::getInstance()->vbo));
	glGenTextures(5, (Pyramid::getInstance()->textures));
}

void Shader::initTexture()
{
	for (int i = 0; i < 6; ++i) {
		int imageWidth, imageHeight, numberOfChannel;
		glBindTexture(GL_TEXTURE_2D, Cube::getInstance()->textures[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_set_flip_vertically_on_load(true);

		unsigned char* data;

		switch (i)
		{
		case 0:
			data = stbi_load("dice00.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 1:
			data = stbi_load("dice01.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 2:
			data = stbi_load("dice02.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 3:
			data = stbi_load("dice03.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 4:
			data = stbi_load("dice04.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 5:
			data = stbi_load("dice05.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < 6; ++i) {
		int imageWidth, imageHeight, numberOfChannel;
		glBindTexture(GL_TEXTURE_2D, Pyramid::getInstance()->textures[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_set_flip_vertically_on_load(true);

		unsigned char* data;

		switch (i)
		{
		case 0:
			data = stbi_load("alphabet00.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 1:
			data = stbi_load("alphabet01.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 2:
			data = stbi_load("alphabet02.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 3:
			data = stbi_load("alphabet03.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 4:
			data = stbi_load("alphabet04.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		case 5:
			data = stbi_load("alphabet05.png", &imageWidth, &imageHeight, &numberOfChannel, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
			break;
		default:
			break;
		}
	}

	{
		int imageWidth, imageHeight, numberOfChannel;
		glBindTexture(GL_TEXTURE_2D, BackGround::getInstance()->texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load("sky.jpg", &imageWidth, &imageHeight, &numberOfChannel, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
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

void Shader::initBuffer()
{
	// CoordSystem
	{
		glBindVertexArray(CoordSystem::getInstance()->vao);
		glBindBuffer(GL_ARRAY_BUFFER, CoordSystem::getInstance()->vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CoordSystem::getInstance()->vertex), CoordSystem::getInstance()->vertex, GL_STATIC_DRAW);
		GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
		glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(pAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, CoordSystem::getInstance()->vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CoordSystem::getInstance()->color), CoordSystem::getInstance()->color, GL_STATIC_DRAW);
		GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
		glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(cAttribute);
	}

	{
		glBindVertexArray(Cube::getInstance()->vao);
		glBindBuffer(GL_ARRAY_BUFFER, Cube::getInstance()->vertexVbo);
		glBufferData(GL_ARRAY_BUFFER, Cube::getInstance()->verticies.size() * sizeof(glm::vec3), Cube::getInstance()->verticies.data(), GL_STATIC_DRAW);
		GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
		glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(pAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, Cube::getInstance()->normalVbo);
		glBufferData(GL_ARRAY_BUFFER, Cube::getInstance()->normals.size() * sizeof(glm::vec3), Cube::getInstance()->normals.data(), GL_STATIC_DRAW);
		GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
		glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(nAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, Cube::getInstance()->uvVbo);
		glBufferData(GL_ARRAY_BUFFER, Cube::getInstance()->uvs.size() * sizeof(glm::vec2), Cube::getInstance()->uvs.data(), GL_STATIC_DRAW);
		GLint tAttribute = glGetAttribLocation(shaderProgram, "vTexCoord");
		glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glEnableVertexAttribArray(tAttribute);
	}

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

	{
		glBindVertexArray(BackGround::getInstance()->vao);
		glBindBuffer(GL_ARRAY_BUFFER, BackGround::getInstance()->vertexVbo);
		glBufferData(GL_ARRAY_BUFFER, BackGround::getInstance()->verticies.size() * sizeof(glm::vec3), BackGround::getInstance()->verticies.data(), GL_STATIC_DRAW);
		GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
		glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(pAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, BackGround::getInstance()->normalVbo);
		glBufferData(GL_ARRAY_BUFFER, BackGround::getInstance()->normals.size() * sizeof(glm::vec3), BackGround::getInstance()->normals.data(), GL_STATIC_DRAW);
		GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
		glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(nAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, BackGround::getInstance()->uvVbo);
		glBufferData(GL_ARRAY_BUFFER, BackGround::getInstance()->uvs.size() * sizeof(glm::vec2), BackGround::getInstance()->uvs.data(), GL_STATIC_DRAW);
		GLint tAttribute = glGetAttribLocation(shaderProgram, "vTexCoord");
		glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glEnableVertexAttribArray(tAttribute);
	}
}

void Shader::release()
{

}