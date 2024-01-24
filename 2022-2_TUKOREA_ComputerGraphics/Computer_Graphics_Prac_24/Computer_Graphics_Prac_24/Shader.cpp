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

void Shader::glGenerate()
{
	glGenVertexArrays(1, &(Floor::getInstance()->vao));
	glGenBuffers(1, &(Floor::getInstance()->vertexVbo));
	glGenBuffers(1, &(Floor::getInstance()->normalVbo));
	glGenBuffers(1, &(Floor::getInstance()->colorVbo));

	glGenVertexArrays(1, &(Light::getInstance()->vao));
	glGenBuffers(1, &(Light::getInstance()->vertexVbo));
	glGenBuffers(1, &(Light::getInstance()->normalVbo));
	glGenBuffers(1, &(Light::getInstance()->colorVbo));

	glGenVertexArrays(1, &(Crane::getInstance()->bottomVao));
	glGenBuffers(1, &(Crane::getInstance()->bottomVertexVbo));
	glGenBuffers(1, &(Crane::getInstance()->bottomNormalVbo));
	glGenBuffers(1, &(Crane::getInstance()->bottomColorVbo));

	glGenVertexArrays(1, &(Crane::getInstance()->topVao));
	glGenBuffers(1, &(Crane::getInstance()->topVertexVbo));
	glGenBuffers(1, &(Crane::getInstance()->topNormalVbo));
	glGenBuffers(1, &(Crane::getInstance()->topColorVbo));

	glGenVertexArrays(1, &(Crane::getInstance()->leftHandVao));
	glGenBuffers(1, &(Crane::getInstance()->leftHandVertexVbo));
	glGenBuffers(1, &(Crane::getInstance()->leftHandNormalVbo));
	glGenBuffers(1, &(Crane::getInstance()->leftHandColorVbo));

	glGenVertexArrays(1, &(Crane::getInstance()->rightHandVao));
	glGenBuffers(1, &(Crane::getInstance()->rightHandVertexVbo));
	glGenBuffers(1, &(Crane::getInstance()->rightHandNormalVbo));
	glGenBuffers(1, &(Crane::getInstance()->rightHandColorVbo));

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

	// Crane
	{
		// Bottom
		{
			glBindVertexArray(Crane::getInstance()->bottomVao);
			glBindBuffer(GL_ARRAY_BUFFER, Crane::getInstance()->bottomVertexVbo);
			glBufferData(GL_ARRAY_BUFFER, Crane::getInstance()->bottomVerticies.size() * sizeof(glm::vec3), Crane::getInstance()->bottomVerticies.data(), GL_STATIC_DRAW);
			GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
			glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, Crane::getInstance()->bottomNormalVbo);
			glBufferData(GL_ARRAY_BUFFER, Crane::getInstance()->bottomNormals.size() * sizeof(glm::vec3), Crane::getInstance()->bottomNormals.data(), GL_STATIC_DRAW);
			GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
			glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, Crane::getInstance()->bottomColorVbo);
			glBufferData(GL_ARRAY_BUFFER, Crane::getInstance()->bottomColors.size() * sizeof(glm::vec3), Crane::getInstance()->bottomColors.data(), GL_STATIC_DRAW);
			GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
			glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(cAttribute);
		}

		// Top
		{
			glBindVertexArray(Crane::getInstance()->topVao);
			glBindBuffer(GL_ARRAY_BUFFER, Crane::getInstance()->topVertexVbo);
			glBufferData(GL_ARRAY_BUFFER, Crane::getInstance()->topVerticies.size() * sizeof(glm::vec3), Crane::getInstance()->topVerticies.data(), GL_STATIC_DRAW);
			GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
			glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, Crane::getInstance()->topNormalVbo);
			glBufferData(GL_ARRAY_BUFFER, Crane::getInstance()->topNormals.size() * sizeof(glm::vec3), Crane::getInstance()->topNormals.data(), GL_STATIC_DRAW);
			GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
			glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, Crane::getInstance()->topColorVbo);
			glBufferData(GL_ARRAY_BUFFER, Crane::getInstance()->topColors.size() * sizeof(glm::vec3), Crane::getInstance()->topColors.data(), GL_STATIC_DRAW);
			GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
			glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(cAttribute);
		}

		// Left Hand
		{
			glBindVertexArray(Crane::getInstance()->leftHandVao);
			glBindBuffer(GL_ARRAY_BUFFER, Crane::getInstance()->leftHandVertexVbo);
			glBufferData(GL_ARRAY_BUFFER, Crane::getInstance()->leftHandVerticies.size() * sizeof(glm::vec3), Crane::getInstance()->leftHandVerticies.data(), GL_STATIC_DRAW);
			GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
			glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, Crane::getInstance()->leftHandNormalVbo);
			glBufferData(GL_ARRAY_BUFFER, Crane::getInstance()->leftHandNormals.size() * sizeof(glm::vec3), Crane::getInstance()->leftHandNormals.data(), GL_STATIC_DRAW);
			GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
			glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, Crane::getInstance()->leftHandColorVbo);
			glBufferData(GL_ARRAY_BUFFER, Crane::getInstance()->leftHandColors.size() * sizeof(glm::vec3), Crane::getInstance()->leftHandColors.data(), GL_STATIC_DRAW);
			GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
			glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(cAttribute);
		}

		// Right Hand
		{
			glBindVertexArray(Crane::getInstance()->rightHandVao);
			glBindBuffer(GL_ARRAY_BUFFER, Crane::getInstance()->rightHandVertexVbo);
			glBufferData(GL_ARRAY_BUFFER, Crane::getInstance()->rightHandVerticies.size() * sizeof(glm::vec3), Crane::getInstance()->rightHandVerticies.data(), GL_STATIC_DRAW);
			GLint pAttribute = glGetAttribLocation(shaderProgram, "vPos");
			glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, Crane::getInstance()->rightHandNormalVbo);
			glBufferData(GL_ARRAY_BUFFER, Crane::getInstance()->rightHandNormals.size() * sizeof(glm::vec3), Crane::getInstance()->rightHandNormals.data(), GL_STATIC_DRAW);
			GLint nAttribute = glGetAttribLocation(shaderProgram, "vNormal");
			glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute);

			glBindBuffer(GL_ARRAY_BUFFER, Crane::getInstance()->rightHandColorVbo);
			glBufferData(GL_ARRAY_BUFFER, Crane::getInstance()->rightHandColors.size() * sizeof(glm::vec3), Crane::getInstance()->rightHandColors.data(), GL_STATIC_DRAW);
			GLint cAttribute = glGetAttribLocation(shaderProgram, "vColor");
			glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(cAttribute);
		}
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
		glUniform3f(lightPosLocation, Light::getInstance()->getLightDirectionVector().x, Light::getInstance()->getLightDirectionVector().y, Light::getInstance()->getLightDirectionVector().z);
		GLuint lightColorLocation = glGetUniformLocation(shaderProgram, "lightColor"); // lightColor 전달 
		glUniform3f(lightColorLocation, Light::getInstance()->getLightColor().x, Light::getInstance()->getLightColor().y, Light::getInstance()->getLightColor().z);
		GLuint viewPosLocation = glGetUniformLocation(shaderProgram, "viewPos"); // viewPos 값 전달: 카메라 위치 
		glUniform3f(viewPosLocation, Camera::getInstance()->getPositionVector().x, Camera::getInstance()->getPositionVector().y, Camera::getInstance()->getPositionVector().z);
	}
}

void Shader::release()
{

}
