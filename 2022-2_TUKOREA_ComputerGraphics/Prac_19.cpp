#include "pch.h"

std::mt19937 mersenne{ std::random_device{}() };
std::uniform_real_distribution<GLfloat> randomColor{ 0.0f,1.0f };
enum class ProjectionType { Ortho = 0, Perspective };

class Shader;
enum class Direction { Idle = 0, Positive, Negative };
enum class CraneComponent { Bottom = 0, Top, LeftArm, RightArm };

class CoordSystem {
private:
	friend class Shader;
	static CoordSystem* pInst;
	const GLfloat vertex[6][3]{
		{-2.0f,0.1f,0.0f}, {2.0f,0.1f,0.0f},
		{0.0f,-2.0f,0.0f}, {0.0f,2.0f,0.0f},
		{0.0f,0.1f,-2.0f}, {0.0f,0.1f,2.0f} };
	const GLfloat color[6][3]{
		{1.0f,0.0f,0.0f}, {1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f}, {0.0f,1.0f,0.0f},
		{0.0f,0.0f,1.0f}, {0.0f,0.0f,1.0f} };
	glm::vec3 positionVector{ 0.0f,0.0f,0.0f };
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

	glm::vec3& getPositionVector() { return positionVector; }

	void render() const { glDrawArrays(GL_LINES, 0, 6); }
};

class Floor {
private:
	friend class Shader;
	static Floor* pInst;
	const GLfloat vertex[4][3]{ {-5.0f,0.0f,-5.0f},{-5.0f,0.0f,5.0f},{5.0f,0.0f,5.0f},{5.0f,0.0f,-5.0f} };
	GLfloat color[4][3]{ {randomColor(mersenne),randomColor(mersenne),randomColor(mersenne)}, {randomColor(mersenne),randomColor(mersenne),randomColor(mersenne)},
		{randomColor(mersenne),randomColor(mersenne),randomColor(mersenne)},{randomColor(mersenne),randomColor(mersenne), randomColor(mersenne)} };
	unsigned int index[6] = { 0,1,2,0,2,3 };
	glm::vec3 positionVector{ 0.0f,0.0f,0.0f };
private:
	Floor()
	{

	}
public:
	static Floor* getInstance()
	{
		if (nullptr == pInst)
			pInst = new Floor;

		return pInst;
	}

	void render() const
	{
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	glm::vec3& getPositionVector() { return positionVector; }
};

class Crane {
private:
	friend class Shader;
	static Crane* pInst;
	const GLfloat bottomVertices[8][3]{
{-0.7f,0.5f,-0.7f}
,{-0.7f,0.5f,0.7f}
,{0.7f,0.5f,0.7f}
,{0.7f,0.5f,-0.7f}
,{-0.7f,0.0f,-0.7f}
,{-0.7f,0.0f,0.7f}
,{0.7f,0.0f,0.7f}
,{0.7f,0.0f,-0.7f} };
	const GLfloat topVertices[8][3]{
	{-0.4f, 0.8f, -0.4f}
	, { -0.4f,0.8f,0.4f }
		, { 0.4f,0.8f,0.4f }
		, { 0.4f,0.8f,-0.4f }
		, { -0.4f,0.5f,-0.4f }
		, { -0.4f,0.5f,0.4f }
		, { 0.4f,0.5f,0.4f }
		, { 0.4f,0.5f,-0.4f }
	};
	const GLfloat leftArmVertices[8][3]{
	{-0.1f, 1.6f, 0.1f}
	, { -0.1f,1.6f,0.3f }
		, { 0.1f,1.6f,0.3f }
		, { 0.1f,1.6f,0.1f }
		, { -0.1f,0.8f,0.1f }
		, { -0.1f,0.8f,0.3f }
		, { 0.1f,0.8f,0.3f }
		, { 0.1f,0.8f,0.1f }
	};
	const GLfloat rightArmVertices[8][3]{
	{-0.1f, 1.6f, -0.3f}
	, { -0.1f,1.6f,-0.1f }
		, { 0.1f,1.6f,-0.1f }
		, { 0.1f,1.6f,-0.3f }
		, { -0.1f,0.8f,-0.3f }
		, { -0.1f,0.8f,-0.1f }
		, { 0.1f,0.8f,-0.1f }
		, { 0.1f,0.8f,-0.3f }
	};
	const GLfloat color[8][3]{ {randomColor(mersenne), randomColor(mersenne), randomColor(mersenne)}, { randomColor(mersenne),randomColor(mersenne),randomColor(mersenne) }
		, { randomColor(mersenne),randomColor(mersenne),randomColor(mersenne) }, { randomColor(mersenne),randomColor(mersenne),randomColor(mersenne) },
		{ randomColor(mersenne),randomColor(mersenne),randomColor(mersenne) }, { randomColor(mersenne),randomColor(mersenne),randomColor(mersenne) },
		{ randomColor(mersenne),randomColor(mersenne),randomColor(mersenne) }, { randomColor(mersenne),randomColor(mersenne),randomColor(mersenne) } };
	unsigned int indexes[36] = { 0,1,2,0,2,3,4,5,6,4,6,7,0,1,5,0,5,4,3,2,6,3,6,7,1,5,6,1,6,2,0,4,7,0,7,3 };
	glm::vec3 positionVector{ 0.0f,0.0f,0.0f };
	GLfloat topRotationDegree{ 0.0f };
	GLfloat leftArmRotationDegree{ 0.0f };
	GLfloat rightArmRotationDegree{ 0.0f };
	GLfloat degreeAmount{ 1.0f };
	GLfloat moveAmount{ 0.01f };
	bool onMoveCrane{ false };
	bool onTopRotation{ false };
	bool onArmRotation{ false };
	Direction rotateDirection{ Direction::Idle };
	Direction armRotateDirection{ Direction::Idle };
	Direction craneMoveDirection{ Direction::Idle };
private:
	Crane()
	{

	}
public:
	static Crane* getInstance()
	{
		if (nullptr == pInst)
			pInst = new Crane;

		return pInst;
	}
public:

	glm::vec3& getPositionVector() { return positionVector; }

	GLfloat& getTopRotationDegree() { return topRotationDegree; }

	GLfloat& getLeftArmRotationDegree() { return leftArmRotationDegree; }

	GLfloat& getRightArmRotationDegree() { return rightArmRotationDegree; }

	GLfloat& getDegreeAmount() { return degreeAmount; }

	GLfloat& getMoveAmount() { return moveAmount; }

	bool& isOnTopRotation() { return onTopRotation; }

	Direction& getRotateDirection() { return rotateDirection; }

	Direction& getArmRotateDirection() { return armRotateDirection; }

	Direction& getCraneMoveDirection() { return craneMoveDirection; }

	bool& isOnArmRotation() { return onArmRotation; }

	bool& isOnMoveCrane() { return onMoveCrane; }


	void render() const
	{
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
};

class Shader {
private:
	friend class CoordSystem;
	friend class Floor;
	friend class Camera;
	friend class Crane;
	static Shader* pInst;
	enum { MaxVao = 6, MaxVbo = 12, MaxEbo = 2 };
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(Floor::getInstance()->vertex), Floor::getInstance()->vertex, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Floor::getInstance()->index), Floor::getInstance()->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Floor::getInstance()->color), Floor::getInstance()->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);


		glBindVertexArray(vao[2]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Crane::getInstance()->bottomVertices), Crane::getInstance()->bottomVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Crane::getInstance()->indexes), Crane::getInstance()->indexes, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Crane::getInstance()->color), Crane::getInstance()->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[3]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[6]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Crane::getInstance()->topVertices), Crane::getInstance()->topVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Crane::getInstance()->indexes), Crane::getInstance()->indexes, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[7]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Crane::getInstance()->color), Crane::getInstance()->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[4]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[8]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Crane::getInstance()->leftArmVertices), Crane::getInstance()->leftArmVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Crane::getInstance()->indexes), Crane::getInstance()->indexes, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[9]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Crane::getInstance()->color), Crane::getInstance()->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[5]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[10]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Crane::getInstance()->rightArmVertices), Crane::getInstance()->rightArmVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Crane::getInstance()->indexes), Crane::getInstance()->indexes, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[11]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Crane::getInstance()->color), Crane::getInstance()->color, GL_STATIC_DRAW);
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
	glm::vec3 positionVector{ 0.0f,1.0f,2.0f };
	glm::vec3 targetVector{ 0.0f,0.0f,0.0f };
	glm::vec3 directionVector{ glm::normalize(targetVector - positionVector) };
	glm::vec3 defaultUpVector{ 0.0f, 1.0f, 0.0f };
	glm::vec3 rightVector{ glm::normalize(glm::cross(defaultUpVector,directionVector)) };
	glm::vec3 upVector{ glm::cross(directionVector,rightVector) };
	glm::mat4 viewMatrix{ 1.0f };
	glm::mat4 revolutionMatrix{ 0.0f };
	glm::mat4 rotationMatrix{ 1.0f };
	glm::mat4 translationMatrix{ 1.0f };
	glm::mat4 projectionMatrix{ 1.0f };
	ProjectionType projectionType{ ProjectionType::Perspective };
	GLfloat rotationDegree{ 0.0f };
	GLfloat revolutionDegree{ 0.0f };
	bool onRevolution{ false };
	bool onRotation{ false };
	Direction revolutionDirection{ Direction::Idle };
public:
	glm::vec3& getPositionVector() { return positionVector; }
	glm::vec3& getTargetVector() { return targetVector; }
	glm::vec3& getDirectionVector() { return directionVector; }
	glm::vec3& getUpVector() { return upVector; }
	
	ProjectionType& getProjectionType() { return projectionType; }

	void Locate()
	{
		viewMatrix = glm::lookAt(getPositionVector(), getDirectionVector(), getUpVector());
		switch (projectionType)
		{
		case ProjectionType::Ortho:
			projectionMatrix = glm::ortho(-6.0f, 6.0f, -6.0f, 6.0f, -6.0f, 6.0f);
			break;
		case ProjectionType::Perspective:
			projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 50.0f);
			projectionMatrix = glm::translate(projectionMatrix, glm::vec3(0.0f, 0.0f, -10.0f));
			break;
		default:
			break;
		}
		unsigned int viewTrasnformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "viewTransform");
		unsigned int projectionTransformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "projectionTransform");
		glUniformMatrix4fv(viewTrasnformLocation, 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
	}

	bool& isOnRevolution() { return onRevolution; }

	bool& isOnRotation() { return onRotation; }

	GLfloat& getRotationDegree() { return rotationDegree; }
	GLfloat& getRevolutionDegree() { return revolutionDegree; }

	Direction& getRevolutionDirection() { return revolutionDirection; }
};

GLfloat testDegree{ 0.0f };
constexpr GLuint wWidth{ 1200 };
constexpr GLuint wHeight{ 800 };

Shader* Shader::pInst = nullptr;
CoordSystem* CoordSystem::pInst = nullptr;
Floor* Floor::pInst = nullptr;
Crane* Crane::pInst = nullptr;
Camera* pCraneViewCamera;
Camera* pTopViewCamera;
Camera* pSideViewCamera;

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

	pCraneViewCamera = new Camera;

	pTopViewCamera = new Camera;
	pTopViewCamera->getPositionVector() = glm::vec3{ 0.0f, 3.0f, 0.0f };
	pTopViewCamera->getProjectionType() = ProjectionType::Ortho;
	
	pSideViewCamera = new Camera;
	pSideViewCamera->getPositionVector() = { 0.0f,0.0f,2.0f };
	pSideViewCamera->getProjectionType() = ProjectionType::Ortho;

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
	glEnable(GL_DEPTH_TEST);
	{
		pCraneViewCamera->Locate();
		glViewport(0, 0, 600, 400);
		// CoordSystem
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			glm::mat4 revY{ 1.0f };
			glm::mat4 revX{ 1.0f };
			glm::mat4 revZ{ 1.0f };
			//	parentMatrix = cameraPositionMatrix;
			rotY = glm::rotate(rotY, glm::radians(pCraneViewCamera->getRevolutionDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			rotationMatrix = rotY;
			translationMatrix = glm::translate(translationMatrix, glm::vec3(CoordSystem::getInstance()->getPositionVector()));
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[0]);
			CoordSystem::getInstance()->render();
		}

		// Floor
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotX{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			//	parentMatrix = cameraPositionMatrix;
			rotY = glm::rotate(rotY, glm::radians(pCraneViewCamera->getRevolutionDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			rotationMatrix = rotY;
			translationMatrix = glm::translate(translationMatrix, glm::vec3(Floor::getInstance()->getPositionVector()));
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[1]);
			Floor::getInstance()->render();
		}

		glm::mat4 bottomTransformMatrix{ 1.0f };
		// Bottom
		{
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			rotY = glm::rotate(rotY, glm::radians(pCraneViewCamera->getRevolutionDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			rotationMatrix = rotY;
			translationMatrix = glm::translate(translationMatrix, glm::vec3(Crane::getInstance()->getPositionVector().x, Crane::getInstance()->getPositionVector().y, Crane::getInstance()->getPositionVector().z));
			bottomTransformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(bottomTransformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[2]);
			Crane::getInstance()->render();
		}

		// Top
		glm::mat4 topTransformMatrix{ 1.0f };
		{
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			parentMatrix = bottomTransformMatrix;
			rotationMatrix = glm::rotate(rotationMatrix, glm::radians(Crane::getInstance()->getTopRotationDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			topTransformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(topTransformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[3]);
			Crane::getInstance()->render();
		}

		// LeftArm
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotZ{ 1.0f };
			glm::mat4 firstTrans{ 1.0 };
			glm::mat4 lastTrans{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			revolutionMatrix = rotY;
			rotZ = glm::rotate(rotZ, glm::radians(Crane::getInstance()->getLeftArmRotationDegree()), glm::vec3(0.0f, 0.0, 1.0f));
			firstTrans = glm::translate(firstTrans, glm::vec3(0.0f, -0.65f, 0.0f));
			lastTrans = glm::translate(lastTrans, glm::vec3(0.0f, 0.65f, 0.0f));
			rotationMatrix = lastTrans * rotZ * firstTrans;
			parentMatrix = topTransformMatrix;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[4]);
			Crane::getInstance()->render();
		}

		// RightArm
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotZ{ 1.0f };
			glm::mat4 firstTrans{ 1.0 };
			glm::mat4 lastTrans{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			revolutionMatrix = rotY;
			rotZ = glm::rotate(rotZ, glm::radians(Crane::getInstance()->getRightArmRotationDegree()), glm::vec3(0.0f, 0.0, 1.0f));
			firstTrans = glm::translate(firstTrans, glm::vec3(0.0f, -0.65f, 0.0f));
			lastTrans = glm::translate(lastTrans, glm::vec3(0.0f, 0.65f, 0.0f));
			rotationMatrix = lastTrans * rotZ * firstTrans;
			parentMatrix = topTransformMatrix;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[5]);
			Crane::getInstance()->render();
		}
	}


	{
		pTopViewCamera->Locate();
		glViewport(800, 400, 300, 300);
		// CoordSystem
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			glm::mat4 revY{ 1.0f };
			glm::mat4 revX{ 1.0f };
			glm::mat4 revZ{ 1.0f };
			//	parentMatrix = cameraPositionMatrix;
			rotY = glm::rotate(rotY, glm::radians(pCraneViewCamera->getRevolutionDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			rotationMatrix = rotY;
			translationMatrix = glm::translate(translationMatrix, glm::vec3(CoordSystem::getInstance()->getPositionVector()));
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[0]);
			CoordSystem::getInstance()->render();
		}

		// Floor
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotX{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			//	parentMatrix = cameraPositionMatrix;
			rotY = glm::rotate(rotY, glm::radians(pCraneViewCamera->getRevolutionDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			rotationMatrix = rotY;
			translationMatrix = glm::translate(translationMatrix, glm::vec3(Floor::getInstance()->getPositionVector()));
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[1]);
			Floor::getInstance()->render();
		}

		glm::mat4 bottomTransformMatrix{ 1.0f };
		// Bottom
		{
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			rotY = glm::rotate(rotY, glm::radians(pCraneViewCamera->getRevolutionDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			rotationMatrix = rotY;
			translationMatrix = glm::translate(translationMatrix, glm::vec3(Crane::getInstance()->getPositionVector().x, Crane::getInstance()->getPositionVector().y, Crane::getInstance()->getPositionVector().z));
			bottomTransformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(bottomTransformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[2]);
			Crane::getInstance()->render();
		}

		// Top
		glm::mat4 topTransformMatrix{ 1.0f };
		{
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			parentMatrix = bottomTransformMatrix;
			rotationMatrix = glm::rotate(rotationMatrix, glm::radians(Crane::getInstance()->getTopRotationDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			topTransformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(topTransformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[3]);
			Crane::getInstance()->render();
		}

		// LeftArm
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotZ{ 1.0f };
			glm::mat4 firstTrans{ 1.0 };
			glm::mat4 lastTrans{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			revolutionMatrix = rotY;
			rotZ = glm::rotate(rotZ, glm::radians(Crane::getInstance()->getLeftArmRotationDegree()), glm::vec3(0.0f, 0.0, 1.0f));
			firstTrans = glm::translate(firstTrans, glm::vec3(0.0f, -0.65f, 0.0f));
			lastTrans = glm::translate(lastTrans, glm::vec3(0.0f, 0.65f, 0.0f));
			rotationMatrix = lastTrans * rotZ * firstTrans;
			parentMatrix = topTransformMatrix;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[4]);
			Crane::getInstance()->render();
		}

		// RightArm
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotZ{ 1.0f };
			glm::mat4 firstTrans{ 1.0 };
			glm::mat4 lastTrans{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			revolutionMatrix = rotY;
			rotZ = glm::rotate(rotZ, glm::radians(Crane::getInstance()->getRightArmRotationDegree()), glm::vec3(0.0f, 0.0, 1.0f));
			firstTrans = glm::translate(firstTrans, glm::vec3(0.0f, -0.65f, 0.0f));
			lastTrans = glm::translate(lastTrans, glm::vec3(0.0f, 0.65f, 0.0f));
			rotationMatrix = lastTrans * rotZ * firstTrans;
			parentMatrix = topTransformMatrix;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[5]);
			Crane::getInstance()->render();
		}
	}

	{
		pSideViewCamera->Locate();
		glViewport(800, 0, 300, 300);
		// CoordSystem
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			glm::mat4 revY{ 1.0f };
			glm::mat4 revX{ 1.0f };
			glm::mat4 revZ{ 1.0f };
			//	parentMatrix = cameraPositionMatrix;
			rotY = glm::rotate(rotY, glm::radians(pCraneViewCamera->getRevolutionDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			rotationMatrix = rotY;
			translationMatrix = glm::translate(translationMatrix, glm::vec3(CoordSystem::getInstance()->getPositionVector()));
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[0]);
			CoordSystem::getInstance()->render();
		}

		// Floor
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotX{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			//	parentMatrix = cameraPositionMatrix;
			rotY = glm::rotate(rotY, glm::radians(pCraneViewCamera->getRevolutionDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			rotationMatrix = rotY;
			translationMatrix = glm::translate(translationMatrix, glm::vec3(Floor::getInstance()->getPositionVector()));
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[1]);
			Floor::getInstance()->render();
		}

		glm::mat4 bottomTransformMatrix{ 1.0f };
		// Bottom
		{
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			rotY = glm::rotate(rotY, glm::radians(pCraneViewCamera->getRevolutionDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			rotationMatrix = rotY;
			translationMatrix = glm::translate(translationMatrix, glm::vec3(Crane::getInstance()->getPositionVector().x, Crane::getInstance()->getPositionVector().y, Crane::getInstance()->getPositionVector().z));
			bottomTransformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(bottomTransformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[2]);
			Crane::getInstance()->render();
		}

		// Top
		glm::mat4 topTransformMatrix{ 1.0f };
		{
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			parentMatrix = bottomTransformMatrix;
			rotationMatrix = glm::rotate(rotationMatrix, glm::radians(Crane::getInstance()->getTopRotationDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			topTransformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(topTransformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[3]);
			Crane::getInstance()->render();
		}

		// LeftArm
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotZ{ 1.0f };
			glm::mat4 firstTrans{ 1.0 };
			glm::mat4 lastTrans{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			revolutionMatrix = rotY;
			rotZ = glm::rotate(rotZ, glm::radians(Crane::getInstance()->getLeftArmRotationDegree()), glm::vec3(0.0f, 0.0, 1.0f));
			firstTrans = glm::translate(firstTrans, glm::vec3(0.0f, -0.65f, 0.0f));
			lastTrans = glm::translate(lastTrans, glm::vec3(0.0f, 0.65f, 0.0f));
			rotationMatrix = lastTrans * rotZ * firstTrans;
			parentMatrix = topTransformMatrix;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[4]);
			Crane::getInstance()->render();
		}

		// RightArm
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotZ{ 1.0f };
			glm::mat4 firstTrans{ 1.0 };
			glm::mat4 lastTrans{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			revolutionMatrix = rotY;
			rotZ = glm::rotate(rotZ, glm::radians(Crane::getInstance()->getRightArmRotationDegree()), glm::vec3(0.0f, 0.0, 1.0f));
			firstTrans = glm::translate(firstTrans, glm::vec3(0.0f, -0.65f, 0.0f));
			lastTrans = glm::translate(lastTrans, glm::vec3(0.0f, 0.65f, 0.0f));
			rotationMatrix = lastTrans * rotZ * firstTrans;
			parentMatrix = topTransformMatrix;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[5]);
			Crane::getInstance()->render();
		}
	}


	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	//glViewport(0, 0, w, h);
}
GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'b':
		Crane::getInstance()->isOnMoveCrane() = !Crane::getInstance()->isOnMoveCrane();
		Crane::getInstance()->getCraneMoveDirection() = Direction::Positive;

		break;
	case 'B':
		Crane::getInstance()->isOnMoveCrane() = !Crane::getInstance()->isOnMoveCrane();
		Crane::getInstance()->getCraneMoveDirection() = Direction::Negative;
		break;
	case 'm':
		Crane::getInstance()->isOnTopRotation() = !Crane::getInstance()->isOnTopRotation();
		Crane::getInstance()->getRotateDirection() = Direction::Positive;
		break;
	case 'M':
		Crane::getInstance()->isOnTopRotation() = !Crane::getInstance()->isOnTopRotation();
		Crane::getInstance()->getRotateDirection() = Direction::Negative;
		break;
	case 't':
		Crane::getInstance()->isOnArmRotation() = !Crane::getInstance()->isOnArmRotation();
		Crane::getInstance()->getArmRotateDirection() = Direction::Positive;
		break;
	case 'T':
		Crane::getInstance()->isOnArmRotation() = !Crane::getInstance()->isOnArmRotation();
		Crane::getInstance()->getArmRotateDirection() = Direction::Negative;
		break;
	case 'z':
		pCraneViewCamera->getPositionVector().z += 0.1f;
		pCraneViewCamera->getDirectionVector().z += 0.1f;
		break;
	case 'Z':
		pCraneViewCamera->getPositionVector().z -= 0.1f;
		pCraneViewCamera->getDirectionVector().z -= 0.1f;
		break;
	case 'x':
		pCraneViewCamera->getPositionVector().x += 0.1f;
		pCraneViewCamera->getDirectionVector().x += 0.1f;
		break;
	case 'X':
		pCraneViewCamera->getPositionVector().x -= 0.1f;
		pCraneViewCamera->getDirectionVector().x -= 0.1f;
		break;
		// -------------------------------------------------
	case 'y':
		pCraneViewCamera->isOnRotation() = true;
		break;
	case 'Y':
		pCraneViewCamera->isOnRotation() = false;
		break;
	case 'r':
		pCraneViewCamera->getRevolutionDegree() += 0.5f;
		break;
	case 'R':
		pCraneViewCamera->getRevolutionDegree() -= 0.5f;
		break;
	case 'a':
		pCraneViewCamera->isOnRevolution() = !pCraneViewCamera->isOnRevolution();
		pCraneViewCamera->getRevolutionDirection() = Direction::Positive;
		break;
	case 'A':
		pCraneViewCamera->isOnRevolution() = !pCraneViewCamera->isOnRevolution();
		pCraneViewCamera->getRevolutionDirection() = Direction::Negative;
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	case 's':
		Crane::getInstance()->isOnMoveCrane() = false;
		Crane::getInstance()->isOnTopRotation() = false;
		Crane::getInstance()->isOnArmRotation() = false;
		pCraneViewCamera->isOnRevolution() = false;
		break;
	case 'c':
		pCraneViewCamera->getRevolutionDirection() = Direction::Idle;
		Crane::getInstance()->getCraneMoveDirection() = Direction::Idle;
		Crane::getInstance()->getRotateDirection() = Direction::Idle;
		Crane::getInstance()->getArmRotateDirection() = Direction::Idle;
		Crane::getInstance()->getPositionVector() = glm::vec3(0.0f, 0.0f, 0.0f);
		Crane::getInstance()->getTopRotationDegree() = 0.0f;
		Crane::getInstance()->getLeftArmRotationDegree() = 0.0f;
		Crane::getInstance()->getRightArmRotationDegree() = 0.0f;
		Crane::getInstance()->isOnArmRotation() = false;
		pCraneViewCamera->getRevolutionDegree() = 0.0f;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid TimerFunc(int value)
{
	if (Crane::getInstance()->isOnMoveCrane()) {
		switch (Crane::getInstance()->getCraneMoveDirection())
		{
		case Direction::Positive:
			if (Crane::getInstance()->getPositionVector().x < 4.3f) {
				Crane::getInstance()->getPositionVector().x += Crane::getInstance()->getMoveAmount();
				std::cout << Crane::getInstance()->getPositionVector().x << '\n';
			}
			break;
		case Direction::Negative:
			if (Crane::getInstance()->getPositionVector().x > -4.3f) {
				Crane::getInstance()->getPositionVector().x -= Crane::getInstance()->getMoveAmount();

			}
			break;
		default:
			break;
		}

		std::cout << "Crane positionX: " << Crane::getInstance()->getPositionVector().x << '\n';
		std::cout << "Crane positionY: " << Crane::getInstance()->getPositionVector().y << '\n';
		std::cout << "Crane positionZ: " << Crane::getInstance()->getPositionVector().z << '\n';
	}
	if (Crane::getInstance()->isOnTopRotation()) {

		switch (Crane::getInstance()->getRotateDirection())
		{
		case Direction::Positive:
			Crane::getInstance()->getTopRotationDegree() += 1.0f;
			break;
		case Direction::Negative:
			Crane::getInstance()->getTopRotationDegree() -= 1.0f;
			break;
		default:
			break;
		}
	}

	if (Crane::getInstance()->isOnArmRotation()) {
		Crane::getInstance()->getLeftArmRotationDegree() += Crane::getInstance()->getDegreeAmount();
		Crane::getInstance()->getRightArmRotationDegree() -= Crane::getInstance()->getDegreeAmount();

		if (Crane::getInstance()->getLeftArmRotationDegree() > 45.0f || Crane::getInstance()->getLeftArmRotationDegree() < -45.0f) {
			Crane::getInstance()->getDegreeAmount() = -Crane::getInstance()->getDegreeAmount();
		}
	}
	// Camera

	if (pCraneViewCamera->isOnRevolution()) {
		switch (pCraneViewCamera->getRevolutionDirection())
		{
		case Direction::Positive:
			pCraneViewCamera->getRevolutionDegree() += 0.5f;
			break;
		case Direction::Negative:
			pCraneViewCamera->getRevolutionDegree() -= 0.5f;
			break;
		default:
			break;
		}
	}

	if (pCraneViewCamera->isOnRotation()) {
		pCraneViewCamera->getRotationDegree() += 0.01f;
		pCraneViewCamera->getPositionVector().x = std::cosf(pCraneViewCamera->getRotationDegree());
		pCraneViewCamera->getPositionVector().z = std::sinf(pCraneViewCamera->getRotationDegree());
		pCraneViewCamera->getDirectionVector() = glm::normalize(pCraneViewCamera->getTargetVector() - pCraneViewCamera->getPositionVector());
		std::cout << pCraneViewCamera->getRotationDegree() << '\n';
	}

	glutTimerFunc(10, TimerFunc, 1);
	glutPostRedisplay();
}