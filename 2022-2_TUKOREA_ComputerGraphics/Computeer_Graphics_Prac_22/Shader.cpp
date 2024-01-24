#include "Shader.h"

Shader::Shader()
{

}

Shader* Shader::getInstance()
{
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

void Shader::glGenerate(std::vector<Orbit*>& pOrbit)
{
	glGenVertexArrays(1, &(CoordSystem::getInstance()->vao));
	glGenBuffers(2, (CoordSystem::getInstance()->vbo));

	glGenVertexArrays(1, &(SquarePyramid::getInstance()->vao));
	glGenBuffers(2, (SquarePyramid::getInstance()->vbo));
	
	glGenVertexArrays(1, &(Hexahedron::getInstance()->vao));
	glGenBuffers(1, &(Hexahedron::getInstance()->positionVbo));
	glGenBuffers(1, &(Hexahedron::getInstance()->normalVbo));
	glGenBuffers(1, &(Hexahedron::getInstance()->colorVbo));

	glGenVertexArrays(1, &(Light::getInstance()->vao));
	glGenBuffers(1, &(Light::getInstance()->positionVbo));
	glGenBuffers(1, &(Light::getInstance()->normalVbo));
	glGenBuffers(1, &(Light::getInstance()->colorVbo));

	glGenVertexArrays(1, &(Sphere::getInstance()->vao));
	glGenBuffers(1, &(Sphere::getInstance()->positionVbo));
	glGenBuffers(1, &(Sphere::getInstance()->normalVbo));
	glGenBuffers(1, &(Sphere::getInstance()->colorVbo));

	for (size_t i = 0; i < MaxOrbit; ++i) {
		glGenVertexArrays(1, &(pOrbit[i]->vao));
		glGenBuffers(1, &(pOrbit[i]->positionVbo));
		glGenBuffers(1, &(pOrbit[i]->normalVbo));
		glGenBuffers(1, &(pOrbit[i]->colorVbo));
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

void Shader::initBuffer(std::vector<Orbit*>& pOrbit)
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

	// Hexahedron
	{
		glBindVertexArray(Hexahedron::getInstance()->vao);
		glBindBuffer(GL_ARRAY_BUFFER, Hexahedron::getInstance()->positionVbo);
		glBufferData(GL_ARRAY_BUFFER, Hexahedron::getInstance()->verticies.size() * sizeof(glm::vec3), Hexahedron::getInstance()->verticies.data(), GL_STATIC_DRAW);
		GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
		glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(pAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, Hexahedron::getInstance()->normalVbo);
		glBufferData(GL_ARRAY_BUFFER, Hexahedron::getInstance()->normals.size() * sizeof(glm::vec3), Hexahedron::getInstance()->normals.data(), GL_STATIC_DRAW);
		GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
		glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(nAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, Hexahedron::getInstance()->colorVbo);
		glBufferData(GL_ARRAY_BUFFER, Hexahedron::getInstance()->colors.size() * sizeof(glm::vec3), Hexahedron::getInstance()->colors.data(), GL_STATIC_DRAW);
		GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
		glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(cAttribute);
	}

	// Sphere
	{
		glBindVertexArray(Sphere::getInstance()->vao);
		glBindBuffer(GL_ARRAY_BUFFER, Sphere::getInstance()->positionVbo);
		glBufferData(GL_ARRAY_BUFFER, Sphere::getInstance()->verticies.size() * sizeof(glm::vec3), Sphere::getInstance()->verticies.data(), GL_STATIC_DRAW);
		GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
		glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(pAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, Sphere::getInstance()->normalVbo);
		glBufferData(GL_ARRAY_BUFFER, Sphere::getInstance()->normals.size() * sizeof(glm::vec3), Sphere::getInstance()->normals.data(), GL_STATIC_DRAW);
		GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
		glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(nAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, Sphere::getInstance()->colorVbo);
		glBufferData(GL_ARRAY_BUFFER, Sphere::getInstance()->colors.size() * sizeof(glm::vec3), Sphere::getInstance()->colors.data(), GL_STATIC_DRAW);
		GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
		glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(cAttribute);
	}

	// SquarePyramid
	{
		glBindVertexArray(SquarePyramid::getInstance()->vao);
		glBindBuffer(GL_ARRAY_BUFFER, SquarePyramid::getInstance()->vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SquarePyramid::getInstance()->vertex), SquarePyramid::getInstance()->vertex, GL_STATIC_DRAW);
		
		GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
		glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
		glEnableVertexAttribArray(pAttribute);
		
		GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
		glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3*sizeof(float)));
		glEnableVertexAttribArray(nAttribute);
	
		glBindBuffer(GL_ARRAY_BUFFER, SquarePyramid::getInstance()->vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SquarePyramid::getInstance()->color), SquarePyramid::getInstance()->color, GL_STATIC_DRAW);
		GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
		glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(cAttribute);
	}

	// Orbit
	{
		for (size_t i = 0; i < MaxOrbit; ++i) {
			glBindVertexArray(pOrbit[i]->vao);
			glBindBuffer(GL_ARRAY_BUFFER, pOrbit[i]->positionVbo);
			glBufferData(GL_ARRAY_BUFFER, pOrbit[i]->verticies.size() * sizeof(glm::vec3), pOrbit[i]->verticies.data(), GL_STATIC_DRAW);
			GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
			glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, pOrbit[i]->normalVbo);
			glBufferData(GL_ARRAY_BUFFER, pOrbit[i]->normals.size() * sizeof(glm::vec3), pOrbit[i]->normals.data(), GL_STATIC_DRAW);
			GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
			glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, pOrbit[i]->colorVbo);
			glBufferData(GL_ARRAY_BUFFER, pOrbit[i]->colors.size() * sizeof(glm::vec3), pOrbit[i]->colors.data(), GL_STATIC_DRAW);
			GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
			glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(cAttribute);
		}
	}

	// Light
	{
		glBindVertexArray(Light::getInstance()->vao);
		glBindBuffer(GL_ARRAY_BUFFER, Light::getInstance()->positionVbo);
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

		glUseProgram(shaderProgram);

		GLuint lightPosLocation = glGetUniformLocation(shaderProgram, "lightPos"); // lightPos 전달 
		glUniform3f(lightPosLocation, Light::getInstance()->getLightPosition().x, Light::getInstance()->getLightPosition().y, Light::getInstance()->getLightPosition().z);

		GLuint lightColorLocation = glGetUniformLocation(shaderProgram, "lightColor"); // lightColor 전달 
		glUniform3f(lightColorLocation, Light::getInstance()->getLightColor().x, Light::getInstance()->getLightColor().y, Light::getInstance()->getLightColor().z);
		GLuint viewPosLocation = glGetUniformLocation(shaderProgram, "viewPos"); // viewPos 값 전달: 카메라 위치 
		glUniform3f(viewPosLocation, Camera::getInstance()->getPositionVector().x, Camera::getInstance()->getPositionVector().y, Camera::getInstance()->getPositionVector().z);
	}
}

void Shader::release()
{
	if (nullptr != pInst)
		delete pInst;
}
