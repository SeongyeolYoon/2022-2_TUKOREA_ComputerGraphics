#include "pch.h"
enum class Shape{Hexahedron = 0, SquarePyramid};
enum class ProjectionType{Ortho = 0, Perspective};
std::mt19937 mersenne{ std::random_device{}() };
std::uniform_real_distribution<GLfloat> urd{ 0.0f,1.0f };

class Shader;
class CoordSystem {
private:
	friend class Shader;
	static CoordSystem* pInst;
	const GLfloat vertex[6][3]{
		{-2.0f,0.0f,0.0f}, {2.0f,0.0f,0.0f},
		{0.0f,-2.0f,0.0f}, {0.0f,2.0f,0.0f},
		{0.0f,0.0f,-2.0f}, {0.0f,0.0f,2.0f} };
	const GLfloat color[6][3]{
		{1.0f,0.0f,0.0f}, {1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f}, {0.0f,1.0f,0.0f},
		{0.0f,0.0f,1.0f}, {0.0f,0.0f,1.0f} };
private:
	CoordSystem()
	{

	}
public:
	static CoordSystem* getInstance()
	{
		if (nullptr == pInst)
			pInst = new CoordSystem;

		return pInst;
	}

	void render() const { glDrawArrays(GL_LINES, 0, 6); }
};

class Hexahedron {
private:
	friend class Shader;
	static Hexahedron* pInst;
	GLfloat vertex[8][3]{
{-1.0f,1.0f,-1.0f}
,{-1.0f,1.0f,1.0f}
,{1.0f,1.0f,1.0f}
,{1.0f,1.0f,-1.0f}
,{-1.0f,-1.0f,-1.0f}
,{-1.0f,-1.0f,1.0f}
,{1.0f,-1.0f,1.0f}
,{1.0f,-1.0f,-1.0f} };
	unsigned int index[36]{ 0,1,2,0,2,3,4,5,6,4,6,7,0,1,5,0,5,4,3,2,6,3,6,7,1,5,6,1,6,2,0,4,7,0,7,3 };
	const GLfloat color[8][3]
	{ {urd(mersenne),urd(mersenne),urd(mersenne)}, {urd(mersenne),urd(mersenne),urd(mersenne)}
		, {urd(mersenne),urd(mersenne),urd(mersenne)}, {urd(mersenne),urd(mersenne),urd(mersenne)},
		{urd(mersenne),urd(mersenne),urd(mersenne)}, {urd(mersenne),urd(mersenne),urd(mersenne)},
		{urd(mersenne),urd(mersenne),urd(mersenne)}, {urd(mersenne),urd(mersenne),urd(mersenne)} };
	glm::vec3 positionVector{ glm::vec3{0.0f,0.0f, 0.0f}};
	glm::vec3 sidePositionVector{ 0.0f };
	GLfloat revYDegree{ 0.0f };
	GLfloat revolutionAmount{ 0.1f };
	GLfloat ceilingRotationDegree{ 0.0f };
	GLfloat frontRotationDegree{ 0.0f };
	bool onRevolution{ false };
	bool onOpenCeiling{ false };
	bool onOpenSide{ false };
	bool onOpenFront{ false };
private:
	Hexahedron()
	{

	}
public:
	static Hexahedron* getInstance()
	{
		if (nullptr == pInst)
			pInst = new Hexahedron;

		return pInst;
	}

	GLfloat& getRotYDegree() { return revYDegree; }

	GLfloat& getCeilingRotationDegree() { return ceilingRotationDegree; }

	GLfloat& getFrontRotationDegree() { return frontRotationDegree; }

	glm::vec3& getSidePositionVector() { return sidePositionVector; }

	const GLfloat& getRevolutionAmount() const { return revolutionAmount; }
 
	glm::vec3 getPositionVector() { return positionVector; }

	bool& isOnRevolution() { return onRevolution; }
	
	bool& isOnOpenCeiling() { return onOpenCeiling; }

	bool& isOnOpenSide() { return onOpenSide; }
	
	bool& isOnOpenFront() { return onOpenFront; }

	void render(const int& index) const
	{
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>(index * sizeof(int)));
	}
};

class SquarePyramid {
private:
	friend class Shader;
	static SquarePyramid* pInst;
	GLfloat vertex[5][3]
	{ {0.0f,2.0f,0.0f}, {-1.0f,0.0f,-1.0f}, {-1.0f,0.0f,1.0f},
	{1.0f,0.0f,1.0f}, {1.0f,0.0f,-1.0f} };
	unsigned int index[18]{ 0,1,2,0,2,3,0,3,4,0,1,4,1,2,3,1,3,4 };
	const GLfloat color[5][3]
	{ {urd(mersenne),urd(mersenne),urd(mersenne)}, {urd(mersenne),urd(mersenne),urd(mersenne)}
		, {urd(mersenne),urd(mersenne),urd(mersenne)}, {urd(mersenne),urd(mersenne),urd(mersenne)},
		{urd(mersenne),urd(mersenne),urd(mersenne)} };
	GLfloat revYDegree{ 0.0f };
	GLfloat revolutionAmount{ 0.1f };
	bool onRevolution{ false };
	bool onOpenSide{ false };
	GLfloat frontRotationDegree{ 0.0f };
	GLfloat backRotationDegree{ 0.0f };
	GLfloat leftSideRotationDegree{ 0.0f };
	GLfloat rightSideRotationDegree{ 0.0f };
private:
	SquarePyramid()
	{

	}
public:
	static SquarePyramid* getInstance()
	{
		if (nullptr == pInst)
			pInst = new SquarePyramid;

		return pInst;
	}
	
	GLfloat& getRotYDegree() { return revYDegree; }

	GLfloat& getLeftSideRotationDegree() { return leftSideRotationDegree; }

	GLfloat& getFrontRotationDegree() { return frontRotationDegree; }

	GLfloat& getRightSideRotationDegree() { return rightSideRotationDegree; }

	GLfloat& getBackRotationDegree() { return backRotationDegree; }

	const GLfloat& getRevolutionAmount() const { return revolutionAmount; }

	bool& isOnRevolution() { return onRevolution; }

	bool& isOnOpenSide() { return onOpenSide; }

	void renderFloor() const
	{
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>(12 * sizeof(int)));
	}

	void renderSide(const int& index) const
	{
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, reinterpret_cast<void*>(index * sizeof(int)));
	}
};

class Shader {
private:
	friend class CoordSystem;
	friend class Hexahedron;
	friend class SquarePyramid;
	static Shader* pInst;
	enum { MaxVao = 3, MaxVbo = 6, MaxEbo = 2 };
private:
	GLuint* vao, * vbo, * ebo;
	GLchar* vertexSource, * fragmentSource;
	GLchar vertexShader, fragmentShader;
	GLuint shaderProgram;
private:
	Shader()
	{
		vao = new GLuint[MaxVao];
		vbo = new GLuint[MaxVbo];
		ebo = new GLuint[MaxEbo];
	}
public:
	static Shader* getInstance()
	{
		if (nullptr == pInst)
			pInst = new Shader;

		return pInst;
	}

	~Shader()
	{
		safeDeleteArray(vao);
		safeDeleteArray(vbo);
		safeDeleteArray(ebo);
	}

	GLuint& getShaderProgram()
	{
		return shaderProgram;
	}

	decltype(auto) getVao()
	{
		return vao;
	}

	char* file2Buffer(const char* file)
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

	void makeVertexShader()
	{
		vertexSource = file2Buffer("vertex.glsl");

		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertexShader, 1, (const GLchar**)(&vertexSource), 0);

		glCompileShader(vertexShader);

		checkCompileError(vertexShader, "vertex");
	}

	void makeFragmentShader()
	{
		fragmentSource = file2Buffer("fragment.glsl");

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(fragmentShader, 1, (const GLchar**)(&fragmentSource), 0);

		glCompileShader(fragmentShader);

		checkCompileError(fragmentShader, "fragment");
	}

	void checkCompileError(const GLuint& shaderType, const char* name)
	{
		GLint result;

		GLchar errorLog[512];

		glGetShaderiv(shaderType, GL_COMPILE_STATUS, &result);

		if (!result) {
			glGetShaderInfoLog(shaderType, 512, NULL, errorLog);
			std::cerr << "ERROR:" << name << " complie Failed!\n" << errorLog << std::endl;
		}
	}

	void glGenerate()
	{
		glGenVertexArrays(MaxVao, vao);
		glGenBuffers(MaxVbo, vbo);
		glGenBuffers(MaxEbo, ebo);
	}

	// **************************************************************************************************************************************
	void initBuffer()
	{
		glBindVertexArray(vao[0]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CoordSystem::getInstance()->vertex), CoordSystem::getInstance()->vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CoordSystem::getInstance()->color), CoordSystem::getInstance()->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[1]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Hexahedron::getInstance()->vertex), Hexahedron::getInstance()->vertex, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Hexahedron::getInstance()->index), Hexahedron::getInstance()->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Hexahedron::getInstance()->color), Hexahedron::getInstance()->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[2]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SquarePyramid::getInstance()->vertex), SquarePyramid::getInstance()->vertex, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SquarePyramid::getInstance()->index), SquarePyramid::getInstance()->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SquarePyramid::getInstance()->color), SquarePyramid::getInstance()->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}
	// **************************************************************************************************************************************


	void initShader()
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

	template<typename T>
	void safeDeleteArray(T* ptr)
	{
		if (nullptr != ptr) {
			delete[] ptr;
			//ptr = nullptr;
		}
	}
};

class Camera {
private:
	glm::vec3 positionVector{ glm::vec3{0.0f,0.0f,1.0f} };
	glm::vec3 targetVector{ glm::vec3{0.0f,0.0f,0.0f} };
	glm::vec3 directionVector{glm::normalize(targetVector- positionVector)};
	glm::vec3 defaultUpVector{ glm::vec3{0.0f, 1.0f, 0.0f}};
	glm::vec3 rightVector{ glm::normalize(glm::cross(defaultUpVector,directionVector)) };
	glm::vec3 upVector{ glm::cross(directionVector,rightVector) };
public:
	glm::vec3& getPositionVector() { return positionVector; }
	glm::vec3& getTargetVector() { return targetVector; }
	glm::vec3& getDirectionVector() { return directionVector; }
	glm::vec3& getUpVector() { return upVector; }
};

constexpr GLuint wWidth{ 800 };
constexpr GLuint wHeight{ 600 };

Shader* Shader::pInst = nullptr;
CoordSystem* CoordSystem::pInst = nullptr;
Hexahedron* Hexahedron::pInst = nullptr;
SquarePyramid* SquarePyramid::pInst = nullptr;
Camera* pCamera;
Shape shapeType{ Shape::Hexahedron };
ProjectionType projectionType{ ProjectionType::Ortho };

GLvoid RenderScene();
GLvoid Reshape(int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid TimerFunc(int);

int main(int argc, char** argv)
{
	constexpr unsigned winXPos = 0;
	constexpr unsigned winYPos = 0;
	const char winName[]{ "Example" };

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(winXPos, winYPos);
	glutInitWindowSize(wWidth, wHeight);
	glutCreateWindow(winName);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	pCamera = new Camera;
	Shader::getInstance()->glGenerate();
	Shader::getInstance()->initBuffer();
	Shader::getInstance()->initShader();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, TimerFunc, 1);
	glutMainLoop();
}

GLvoid RenderScene()
{
	Shader::getInstance()->initBuffer();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 coordMatrix{ 1.0f };
	glm::mat4 viewMatrix{ 1.0f };
	glm::mat4 projectionMatrix{ 1.0f };
	viewMatrix = glm::lookAt(pCamera->getPositionVector(), pCamera->getDirectionVector(), pCamera->getUpVector());
	if (ProjectionType::Ortho == projectionType)
		projectionMatrix = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
	if (ProjectionType::Perspective == projectionType) {
		projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 50.0f);
		projectionMatrix = glm::translate(projectionMatrix, glm::vec3(0.0f, 0.0f, -5.0f));
	}
	unsigned int viewTrasnformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "viewTransform");
	unsigned int projectionTransformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "projectionTransform");
	glUniformMatrix4fv(viewTrasnformLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	// CoordSystem
	{
		glm::mat4 transform{ 1.0f };
		glm::mat4 xRevolution{ 1.0f };
		glm::mat4 yRevolution{ 1.0f };
		glm::mat4 trans{ 1.0f };
		glm::mat4 rotation{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		xRevolution = glm::rotate(xRevolution, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		yRevolution = glm::rotate(yRevolution, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		coordMatrix = xRevolution * yRevolution * trans * rotation * scaleMatrix;
		unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(coordMatrix));
		glBindVertexArray(Shader::getInstance()->getVao()[0]);
		CoordSystem::getInstance()->render();
	}

	switch (shapeType)
	{
	case Shape::Hexahedron:
	{
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 revY{ 1.0f };
			parentMatrix = coordMatrix;
			revY = glm::rotate(revY, glm::radians(Hexahedron::getInstance()->getRotYDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			revolutionMatrix = revY;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[1]);
			Hexahedron::getInstance()->render(6);
			Hexahedron::getInstance()->render(30);
		}
		// 천장 0번
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 revY{ 1.0f };
			glm::mat4 transFirst{ 1.0f };
			glm::mat4 transLast{ 1.0f };
			glm::mat4 rotX{ 1.0f };
			revY = glm::rotate(revY, glm::radians(Hexahedron::getInstance()->getRotYDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			transFirst = glm::translate(transFirst, glm::vec3(0.0f,-1.0f,0.0f));
			transLast = glm::translate(transLast, glm::vec3(0.0f,1.0f,0.0f));
			rotX = glm::rotate(rotX, glm::radians(Hexahedron::getInstance()->getCeilingRotationDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
			parentMatrix = coordMatrix;
			revolutionMatrix = revY;
			rotationMatrix= transLast * rotX * transFirst;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[1]);
			Hexahedron::getInstance()->render(0);
		}

		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 revY{ 1.0f };
			glm::mat4 transFirst{ 1.0f };
			glm::mat4 transLast{ 1.0f };
			glm::mat4 rotX{ 1.0f };
			revY = glm::rotate(revY, glm::radians(Hexahedron::getInstance()->getRotYDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			parentMatrix = coordMatrix;
			revolutionMatrix = revY;
			translationMatrix = glm::translate(translationMatrix, Hexahedron::getInstance()->getSidePositionVector());
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[1]);
			Hexahedron::getInstance()->render(12);
			Hexahedron::getInstance()->render(18);
		}

		// 앞 24 
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 revY{ 1.0f };
			glm::mat4 transFirst{ 1.0f };
			glm::mat4 transLast{ 1.0f };
			glm::mat4 rotX{ 1.0f };
			revY = glm::rotate(revY, glm::radians(Hexahedron::getInstance()->getRotYDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			transFirst = glm::translate(transFirst, glm::vec3(0.0f, 1.0f, -1.0f));
			transLast = glm::translate(transLast, glm::vec3(0.0f, -1.0f, 1.0f));
			rotX = glm::rotate(rotX, glm::radians(Hexahedron::getInstance()->getFrontRotationDegree()), glm::vec3(0.5f, 0.0f, 0.0f));
			parentMatrix = coordMatrix;
			revolutionMatrix = revY;
			rotationMatrix = transLast * rotX * transFirst;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[1]);
			Hexahedron::getInstance()->render(24);
		}
		break;
	}
	case Shape::SquarePyramid:
	{
		glm::mat4 transformMatrix{ 1.0f };
		glm::mat4 parentMatrix{ 1.0f };
		glm::mat4 revolutionMatrix{ 1.0f };
		glm::mat4 translationMatrix{ 1.0f };
		glm::mat4 rotationMatrix{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		glm::mat4 revY{ 1.0f };
		parentMatrix = coordMatrix;
		revY = glm::rotate(revY, glm::radians(SquarePyramid::getInstance()->getRotYDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
		revolutionMatrix = revY;
		//translationMatrix = glm::translate(translationMatrix, SquarePyramid::getInstance()->getPositionVector());
		transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
		unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glBindVertexArray(Shader::getInstance()->getVao()[2]);
		SquarePyramid::getInstance()->renderFloor();
		
		// left
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 transFirst{ 1.0f };
			glm::mat4 transLast{ 1.0f };
			glm::mat4 rotZ{ 1.0f };
			transFirst = glm::translate(transFirst, glm::vec3(1.0f, 0.0f, 0.0f));
			transLast = glm::translate(transLast, glm::vec3(-1.0f, 0.0f, 0.0f));
			rotZ = glm::rotate(rotZ, glm::radians(SquarePyramid::getInstance()->getLeftSideRotationDegree()), glm::vec3(0.0f, 0.0f, 1.0f));
			parentMatrix = coordMatrix;
			revolutionMatrix = revY;
			rotationMatrix = transLast * rotZ * transFirst;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[2]);
			SquarePyramid::getInstance()->renderSide(0);
		}

		// front
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 transFirst{ 1.0f };
			glm::mat4 transLast{ 1.0f };
			glm::mat4 rotZ{ 1.0f };
			transFirst = glm::translate(transFirst, glm::vec3(0.0f, 0.0f, -1.0f));
			transLast = glm::translate(transLast, glm::vec3(0.0f, 0.0f, 1.0f));
			rotZ = glm::rotate(rotZ, glm::radians(SquarePyramid::getInstance()->getFrontRotationDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
			parentMatrix = coordMatrix;
			revolutionMatrix = revY;
			rotationMatrix = transLast * rotZ * transFirst;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[2]);
			SquarePyramid::getInstance()->renderSide(3);
		}

		// right
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 transFirst{ 1.0f };
			glm::mat4 transLast{ 1.0f };
			glm::mat4 rotZ{ 1.0f };
			transFirst = glm::translate(transFirst, glm::vec3(-1.0f, 0.0f, 0.0f));
			transLast = glm::translate(transLast, glm::vec3(1.0f, 0.0f, 0.0f));
			rotZ = glm::rotate(rotZ, glm::radians(SquarePyramid::getInstance()->getRightSideRotationDegree()), glm::vec3(0.0f, 0.0f, 1.0f));
			parentMatrix = coordMatrix;
			revolutionMatrix = revY;
			rotationMatrix = transLast * rotZ * transFirst;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[2]);
			SquarePyramid::getInstance()->renderSide(6);
		}

		// back
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 transFirst{ 1.0f };
			glm::mat4 transLast{ 1.0f };
			glm::mat4 rotZ{ 1.0f };
			transFirst = glm::translate(transFirst, glm::vec3(0.0f, 0.0f, 1.0f));
			transLast = glm::translate(transLast, glm::vec3(0.0f, 0.0f, -1.0f));
			rotZ = glm::rotate(rotZ, glm::radians(SquarePyramid::getInstance()->getBackRotationDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
			parentMatrix = coordMatrix;
			revolutionMatrix = revY;
			rotationMatrix = transLast * rotZ * transFirst;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[2]);
			SquarePyramid::getInstance()->renderSide(9);
		}
		break;
	}
	default:
		break;
	}
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid TimerFunc(int value)
{
	switch (shapeType)
	{
	case Shape::Hexahedron:
		if (Hexahedron::getInstance()->isOnRevolution()) {
			Hexahedron::getInstance()->getRotYDegree() += Hexahedron::getInstance()->getRevolutionAmount();
		}
		if (Hexahedron::getInstance()->isOnOpenCeiling()) {
			Hexahedron::getInstance()->getCeilingRotationDegree() += 1.0f;
		}
		if (Hexahedron::getInstance()->isOnOpenFront()) {
			if (Hexahedron::getInstance()->getFrontRotationDegree() < 90.0f) {
				Hexahedron::getInstance()->getFrontRotationDegree() += 1.0f;
			}
		}
		else {
			if (Hexahedron::getInstance()->getFrontRotationDegree() > 0.0f) {
				Hexahedron::getInstance()->getFrontRotationDegree() -= 1.0f;
			}
		}
		if (Hexahedron::getInstance()->isOnOpenSide()) {
			if (Hexahedron::getInstance()->getSidePositionVector().y < 2.0f) {
				Hexahedron::getInstance()->getSidePositionVector().y += 0.01f;
			}
		}
		else {
			if (Hexahedron::getInstance()->getSidePositionVector().y > 0.0f) {
				Hexahedron::getInstance()->getSidePositionVector().y -= 0.01f;
			}
		}
		break;
	case Shape::SquarePyramid:
		if (SquarePyramid::getInstance()->isOnRevolution()) {
			SquarePyramid::getInstance()->getRotYDegree() += SquarePyramid::getInstance()->getRevolutionAmount();
		}
		if (SquarePyramid::getInstance()->isOnOpenSide()) {
			if (SquarePyramid::getInstance()->getLeftSideRotationDegree() < 233.5f && SquarePyramid::getInstance()->getFrontRotationDegree() < 233.5f) {
				SquarePyramid::getInstance()->getLeftSideRotationDegree() += 0.5f;
				SquarePyramid::getInstance()->getFrontRotationDegree() += 0.5f;
			}
			if (SquarePyramid::getInstance()->getRightSideRotationDegree() > -233.5f && SquarePyramid::getInstance()->getBackRotationDegree() > -233.5f) {
				SquarePyramid::getInstance()->getRightSideRotationDegree() -= 0.5f;
				SquarePyramid::getInstance()->getBackRotationDegree() -= 0.5f;
			}
		}
		else {
			if (SquarePyramid::getInstance()->getLeftSideRotationDegree() > 0.0f && SquarePyramid::getInstance()->getFrontRotationDegree() > 0.0f) {
				SquarePyramid::getInstance()->getLeftSideRotationDegree() -= 0.5f;
				SquarePyramid::getInstance()->getFrontRotationDegree() -= 0.5;
			}
			if (SquarePyramid::getInstance()->getRightSideRotationDegree() < 0.0f && SquarePyramid::getInstance()->getBackRotationDegree() < 0.0f) {
				SquarePyramid::getInstance()->getRightSideRotationDegree() += 0.5f;
				SquarePyramid::getInstance()->getBackRotationDegree() += 0.5f;
			}
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunc, 1);
}

GLvoid Keyboard(unsigned char key, int x, int y) 
{
	switch (key)
	{
	case 'h':
		glEnable(GL_DEPTH_TEST);
		break;
	case 'H':
		glDisable(GL_DEPTH_TEST);
		break;
	case 'y':
		switch (shapeType)
		{
		case Shape::Hexahedron:
			Hexahedron::getInstance()->isOnRevolution() = !(Hexahedron::getInstance()->isOnRevolution());
			break;
		case Shape::SquarePyramid:
			SquarePyramid::getInstance()->isOnRevolution() = !(SquarePyramid::getInstance()->isOnRevolution());
			break;
		default:
			break;
		}
		break;
	case 't':
		shapeType = Shape::Hexahedron;
		Hexahedron::getInstance()->isOnOpenCeiling() = true;
		break;
	case 'T':
		shapeType = Shape::Hexahedron;
		Hexahedron::getInstance()->isOnOpenCeiling() = false;
		break;
	case 'f':
		shapeType = Shape::Hexahedron;
		Hexahedron::getInstance()->isOnOpenFront() = true;
		break;
	case 'F':
		shapeType = Shape::Hexahedron;
		Hexahedron::getInstance()->isOnOpenFront() = false;
		break;
	case '1':
		shapeType = Shape::Hexahedron;
		Hexahedron::getInstance()->isOnOpenSide() = true;
		break;
	case '2':
		shapeType = Shape::Hexahedron;
		Hexahedron::getInstance()->isOnOpenSide() = false;
		break;
	case 'o':
		shapeType = Shape::SquarePyramid;
		SquarePyramid::getInstance()->isOnOpenSide() = true;
		break;
	case 'O':
		shapeType = Shape::SquarePyramid;
		SquarePyramid::getInstance()->isOnOpenSide() = false;
		break;
	case 'p':
		projectionType = ProjectionType::Ortho;
		break;
	case 'P':
		projectionType = ProjectionType::Perspective;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}