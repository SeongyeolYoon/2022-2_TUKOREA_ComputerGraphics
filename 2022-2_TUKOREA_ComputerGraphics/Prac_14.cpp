#include "pch.h"

std::mt19937 mersenne{ std::random_device{}() };
std::uniform_real_distribution<GLfloat> urColor{ 0.0f,1.0f };

enum class Shape { None = 0, Hexahedron_And_Cone , Spere_And_Cylinder };
enum class Direction { Idle = 0, Positive, Negative };
enum class AxisType { None = 0, X, Y };

class CoordSystem {
private:
	friend class Shader;
	static CoordSystem* pInst;
	const GLfloat vertex[6][3]{
		{-1.0f,0.0f,0.0f}, {1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f}, {0.0f,-1.0f,0.0f},
		{0.0f,0.0f,1.0f}, {0.0f,0.0f,-1.0f} };
	const GLfloat color[6][3]{
	{urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)},
	{urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)},
	{urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)} };
	GLfloat revXDegree{ 30.0f };
	GLfloat revYDegree{ -30.0f };
private:
	CoordSystem()
	{

	}
public:
	~CoordSystem()
	{
		delete pInst;
		pInst = nullptr;
	}

	static CoordSystem* getInstance()
	{
		if (nullptr == pInst)
			pInst = new CoordSystem;

		return pInst;
	}

	GLfloat& getRevXDegree() { return revXDegree; }

	GLfloat& getRevYDegree() { return revYDegree; }

	void render() const 
	{ 
		glDrawArrays(GL_LINES, 0, 6); 
	}
};

class Hexahedron {
private:
	friend class Shader;
	static Hexahedron* pInst;
	GLfloat vertex[8][3]{
	{0.25f,0.25f,-0.25f}
	,{0.25f,0.25f,0.25f}
	,{0.75f,0.25f,0.25f}
	,{0.75f,0.25f,-0.25f}
	,{0.25f,-0.25f,-0.25f}
	,{0.25f,-0.25f,0.25f}
	,{0.75f,-0.25f,0.25f}
	,{0.75f,-0.25f,-0.25f} };
	GLfloat tempVertex[8][3] {
	{0.25f,0.25f,-0.25f}
	,{0.25f,0.25f,0.25f}
	,{0.75f,0.25f,0.25f}
	,{0.75f,0.25f,-0.25f}
	,{0.25f,-0.25f,-0.25f}
	,{0.25f,-0.25f,0.25f}
	,{0.75f,-0.25f,0.25f}
	,{0.75f,-0.25f,-0.25f} };
	const GLfloat color[8][3]
	{ {urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)}
		, {urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)},
		{urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)},
		{urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)} };
	const GLuint index[36]{ 0,1,2,0,2,3,4,5,6,4,6,7,0,1,5,0,5,4,3,2,6,3,6,7,1,5,6,1,6,2,0,4,7,0,7,3 };
	GLfloat revXDegree{ 30.0f };
	GLfloat revYDegree{ -30.0f };
	GLfloat rotXDegree{ 0.0f };
	GLfloat rotYDegree{ 0.0f };
	AxisType rotationAxisType{ AxisType::None };
	Direction rotationDirectopn{ Direction::Idle };
	Direction revolutionDirection{ Direction::Idle };
	bool onRotationTimer{ false };
	bool onRevolutionTimer{ false };
private:
	Hexahedron()
	{

	}
public:
	~Hexahedron()
	{
		delete pInst;
		pInst = nullptr;
	}

	static Hexahedron* getInstance()
	{
		if (nullptr == pInst)
			pInst = new Hexahedron;

		return pInst;
	}

	GLfloat& getVertex(const int& row, const int& col) { return vertex[row][col]; }

	GLfloat& getTempVertex(const int& row, const int& col) { return tempVertex[row][col]; }

	GLfloat& getRevXDegree() { return revXDegree; }

	GLfloat& getRevYDegree() { return revYDegree; }

	GLfloat& getRotXDegree() { return rotXDegree; }

	GLfloat& getRotYDegree() { return rotYDegree; }

	Direction& getRotationDirection()  { return rotationDirectopn; }

	Direction& getRevolutionDirection() { return revolutionDirection; }

	AxisType& getRotationAxisType() { return rotationAxisType; }

	bool& isOnRotationTimer() { return onRotationTimer; }

	bool& isOnRevolutionTimer() { return onRevolutionTimer; }

	void render() const { glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); }
};

class Cone {
private:
	GLUquadricObj* pObj;
	GLfloat revXDegree{ 0.0f };
	GLfloat revYDegree{ 0.0f };
	GLfloat rotXDegree{ 0.0f };
	GLfloat rotYDegree{ 0.0f };
	AxisType rotationAxisType{ AxisType::None };
	Direction rotationDirectopn{ Direction::Idle };
	Direction revolutionDirection{ Direction::Idle };
	bool onRotationTimer{ false };
	bool onRevolutionTimer{ false };
public:
	Cone()
	{
		pObj = gluNewQuadric();
		gluQuadricDrawStyle(pObj, GLU_LINE);
		gluQuadricNormals(pObj, GLU_SMOOTH);
		gluQuadricOrientation(pObj, GLU_OUTSIDE);
		glColor3f(1.0f, 0.0f, 0.0f);
	}

	GLfloat& getRevXDegree() { return revXDegree; }

	GLfloat& getRevYDegree() { return revYDegree; }

	GLfloat& getRotXDegree() { return rotXDegree; }

	GLfloat& getRotYDegree() { return rotYDegree; }

	Direction& getRotationDirection() { return rotationDirectopn; }

	Direction& getRevolutionDirection() { return revolutionDirection; }

	AxisType& getRotationAxisType() { return rotationAxisType; }

	bool& isOnRotationTimer() { return onRotationTimer; }

	bool& isOnRevolutionTimer() { return onRevolutionTimer; }

	void render() const
	{
		// object, z= 0에 있는 반지름, z = height에 있는 반지름, 높이, z축을 중심으로 하는 회전의 개수, z축을 따르는 
		gluCylinder(pObj, 0.25, 0.0, 0.5, 20, 8);
	}
};

class Cylinder {
private:
	GLUquadricObj* pObj;
	GLfloat revXDegree{ 30.0f };
	GLfloat revYDegree{ -30.0f };
	GLfloat rotXDegree{ 0.0f };
	GLfloat rotYDegree{ 0.0f };
	AxisType rotationAxisType{ AxisType::None };
	Direction rotationDirectopn{ Direction::Idle };
	Direction revolutionDirection{ Direction::Idle };
	bool onRotationTimer{ false };
	bool onRevolutionTimer{ false };

public:
	Cylinder()
	{
		pObj = gluNewQuadric();
		gluQuadricDrawStyle(pObj, GLU_LINE);
		gluQuadricNormals(pObj, GLU_SMOOTH);
		gluQuadricOrientation(pObj, GLU_OUTSIDE);
		glColor3f(1.0f, 0.0f, 0.0f);
	}


	GLfloat& getRevXDegree() { return revXDegree; }

	GLfloat& getRevYDegree() { return revYDegree; }

	GLfloat& getRotXDegree() { return rotXDegree; }

	GLfloat& getRotYDegree() { return rotYDegree; }

	Direction& getRotationDirection() { return rotationDirectopn; }

	Direction& getRevolutionDirection() { return revolutionDirection; }

	AxisType& getRotationAxisType() { return rotationAxisType; }

	bool& isOnRotationTimer() { return onRotationTimer; }

	bool& isOnRevolutionTimer() { return onRevolutionTimer; }

	void render() const
	{
		gluCylinder(pObj, 0.25, 0.25, 0.5, 20, 8);
	}
};

class Sphere {
private:
	GLUquadricObj* pObj;
	GLfloat revXDegree{ 30.0f };
	GLfloat revYDegree{ -30.0f };
	GLfloat rotXDegree{ 0.0f };
	GLfloat rotYDegree{ 0.0f };
	AxisType rotationAxisType{ AxisType::None };
	Direction rotationDirectopn{ Direction::Idle };
	Direction revolutionDirection{ Direction::Idle };
	bool onRotationTimer{ false };
	bool onRevolutionTimer{ false };

public:
	Sphere()
	{
		pObj = gluNewQuadric();
		gluQuadricDrawStyle(pObj, GLU_LINE);
		gluQuadricNormals(pObj, GLU_SMOOTH);
		gluQuadricOrientation(pObj, GLU_OUTSIDE);
		glColor3f(1.0f, 0.0f, 0.0f);
	}

	GLfloat& getRevXDegree() { return revXDegree; }

	GLfloat& getRevYDegree() { return revYDegree; }

	GLfloat& getRotXDegree() { return rotXDegree; }

	GLfloat& getRotYDegree() { return rotYDegree; }

	Direction& getRotationDirection() { return rotationDirectopn; }

	Direction& getRevolutionDirection() { return revolutionDirection; }

	AxisType& getRotationAxisType() { return rotationAxisType; }

	bool& isOnRotationTimer() { return onRotationTimer; }

	bool& isOnRevolutionTimer() { return onRevolutionTimer; }

	void render() const
	{
		gluSphere(pObj, 0.25, 50 ,50);
	}
};

class Shader {
private:
	friend class CoordSystem;
	friend class Hexahedron;
	friend class Cone;
	static Shader* pInst;
	enum { MaxVao = 2, MaxVbo = 4, MaxEbo = 1 };
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

		delete pInst;
		pInst = nullptr;
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

	// ***************************************************************************************************
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
	}
	// ***************************************************************************************************

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
			ptr = nullptr;
		}
	}
};

Shader* Shader::pInst = nullptr;
CoordSystem* CoordSystem::pInst = nullptr;
Hexahedron* Hexahedron::pInst = nullptr;

 Cone* pCone;
 Sphere* pSphere;
 Cylinder* pCylinder;

Shape shapeType{ Shape::Hexahedron_And_Cone };

constexpr GLuint wWidth{ 800 };
constexpr GLuint wHeight{ 600 };
bool g_onCulling{ false };
GLfloat testDegree{ 0.0f };
GLvoid RenderScene();
GLvoid Reshape(int, int);
GLvoid TimerFunc(int);
GLvoid Keyboard(unsigned char, int, int);

int main(int argc, char** argv)
{
	constexpr unsigned winXPos = 0;
	constexpr unsigned winYPos = 0;
	const char winName[]{ "Example" };

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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

	pCone = new Cone;
	pSphere = new Sphere;
	pCylinder = new Cylinder;

	Shader::getInstance()->glGenerate();
	Shader::getInstance()->initBuffer();
	Shader::getInstance()->initShader();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, TimerFunc, 1);
	glutMainLoop();

	delete pCone;
	delete pSphere;
	delete pCylinder;
}

GLvoid RenderScene()
{
	Shader::getInstance()->initBuffer();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	{
		glm::mat4 transformMatrix{ 1.0f };
		glm::mat4 parentMatrix{ 1.0f };
		glm::mat4 revolutionMatrix{ 1.0f };
		glm::mat4 translationMatrix{ 1.0f };
		glm::mat4 rotationMatrix{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		glm::mat4 revX{ 1.0f };
		glm::mat4 revY{ 1.0f };
		glm::mat4 rotation{ 1.0f };
		glm::mat4 trans1{ 1.0f };
		glm::mat4 trans2{ 1.0f };
		revX = glm::rotate(revX, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		revY = glm::rotate(revY, glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		revolutionMatrix = revX * revY;
		transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
		unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "model");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glBindVertexArray(Shader::getInstance()->getVao()[0]);
		CoordSystem::getInstance()->render();
	}


	switch (shapeType)
	{
	case Shape::Hexahedron_And_Cone:
	{
		// Hexahedron
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 revX{ 1.0f };
			glm::mat4 revY{ 1.0f };
			glm::mat4 xRotation{ 1.0f };
			glm::mat4 yRotation{ 1.0f };
			glm::mat4 trans1{ 1.0f };
			glm::mat4 trans2{ 1.0f };
			revX = glm::rotate(revX, glm::radians(Hexahedron::getInstance()->getRevXDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
			revY = glm::rotate(revY, glm::radians(Hexahedron::getInstance()->getRevYDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			xRotation = glm::rotate(xRotation, glm::radians(Hexahedron::getInstance()->getRotXDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
			yRotation = glm::rotate(yRotation, glm::radians(Hexahedron::getInstance()->getRotYDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			trans1 = glm::translate(trans1, glm::vec3(-0.5f, 0.0f, 0.0f));
			trans2 = glm::translate(trans2, glm::vec3(0.5f, 0.0f, 0.0f));
			revolutionMatrix = revX * revY;
			rotationMatrix = trans2 * xRotation * yRotation * trans1;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "model");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[1]);
			Hexahedron::getInstance()->render();
		}

		// Cone
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f }; // 공전
			glm::mat4 translationMatrix{ 1.0 }; // 위치잡기
			glm::mat4 rotationMatrix{ 1.0f }; // 자전
			glm::mat4 formMatrix{ 1.0 };  // 모양잡기
			glm::mat4 r1{ 1.0f };
			glm::mat4 r2{ 1.0f };
			glm::mat4 r3{ 1.0f };
			glm::mat4 rotX{ 1.0f };
			glm::mat4 rotZ{ 1.0f };
			glm::mat4 revX{ 1.0f };
			glm::mat4 revY{ 1.0f };
			revX = glm::rotate(revX, glm::radians(pCone->getRevXDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
			revY = glm::rotate(revY, glm::radians(pCone->getRevYDegree()), glm::vec3(0.0f, 1.0f, 0.0f));

			rotX = glm::rotate(rotX, glm::radians(pCone->getRotXDegree()), glm::vec3(1.0f, 0.0f,0.0f));
			rotZ = glm::rotate(rotZ, glm::radians(pCone->getRotYDegree()), glm::vec3(0.0f, 0.0f, 1.0f));

			r1 = glm::rotate(r1, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			r2 = glm::rotate(r2, glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			r3 = glm::rotate(r3, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));

			revolutionMatrix = revX * revY;
			translationMatrix = glm::translate(translationMatrix, glm::vec3(-0.5f, 0.0f, 0.0f));
			formMatrix = r3 * r2 * r1;
			rotationMatrix = rotX * rotZ;
			transformMatrix = revolutionMatrix * translationMatrix * formMatrix * rotationMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "model");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			pCone->render();
		}


		break;
	}
	case Shape::Spere_And_Cylinder:
	{
		// Sphere
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f }; // 공전
			glm::mat4 translationMatrix{ 1.0 }; // 위치잡기
			glm::mat4 rotationMatrix{ 1.0f }; // 자전
			glm::mat4 formMatrix{ 1.0 };  // 모양잡기
			glm::mat4 r1{ 1.0f };
			glm::mat4 r2{ 1.0f };
			glm::mat4 r3{ 1.0f };
			glm::mat4 rotX{ 1.0f };
			glm::mat4 rotZ{ 1.0f };
			glm::mat4 revX{ 1.0f };
			glm::mat4 revY{ 1.0f };
			revX = glm::rotate(revX, glm::radians(pSphere->getRevXDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
			revY = glm::rotate(revY, glm::radians(pSphere->getRevYDegree()), glm::vec3(0.0f, 1.0f, 0.0f));

			rotX = glm::rotate(rotX, glm::radians(pSphere->getRotXDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
			rotZ = glm::rotate(rotZ, glm::radians(pSphere->getRotYDegree()), glm::vec3(0.0f, 0.0f, 1.0f));

			r1 = glm::rotate(r1, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			r2 = glm::rotate(r2, glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			r3 = glm::rotate(r3, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));

			revolutionMatrix = revX * revY;
			translationMatrix = glm::translate(translationMatrix, glm::vec3(-0.5f, 0.0f, 0.0f));
			formMatrix = r3 * r2 * r1;
			rotationMatrix = rotX * rotZ;
			transformMatrix = revolutionMatrix * translationMatrix * formMatrix * rotationMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "model");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			pSphere->render();
		}

		// Cylinder
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f }; // 공전
			glm::mat4 translationMatrix{ 1.0 }; // 위치잡기
			glm::mat4 rotationMatrix{ 1.0f }; // 자전
			glm::mat4 formMatrix{ 1.0 };  // 모양잡기
			glm::mat4 r1{ 1.0f };
			glm::mat4 r2{ 1.0f };
			glm::mat4 r3{ 1.0f };
			glm::mat4 rotX{ 1.0f };
			glm::mat4 rotZ{ 1.0f };
			glm::mat4 revX{ 1.0f };
			glm::mat4 revY{ 1.0f };
			revX = glm::rotate(revX, glm::radians(pCylinder->getRevXDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
			revY = glm::rotate(revY, glm::radians(pCylinder->getRevYDegree()), glm::vec3(0.0f, 1.0f, 0.0f));

			rotX = glm::rotate(rotX, glm::radians(pCylinder->getRotXDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
			rotZ = glm::rotate(rotZ, glm::radians(pCylinder->getRotYDegree()), glm::vec3(0.0f, 0.0f, 1.0f));

			r1 = glm::rotate(r1, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			r2 = glm::rotate(r2, glm::radians(-15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			r3 = glm::rotate(r3, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));

			revolutionMatrix = revX * revY;

			translationMatrix = glm::translate(translationMatrix, glm::vec3(+0.5f, 0.0f, 0.0f));

			formMatrix = r3 * r2 * r1;

			rotationMatrix = rotX * rotZ;

			transformMatrix = revolutionMatrix * translationMatrix * formMatrix * rotationMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "model");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			pCylinder->render();
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
	case Shape::Hexahedron_And_Cone:

		// 육면체 자전
		if (Hexahedron::getInstance()->isOnRotationTimer()) {
			switch (Hexahedron::getInstance()->getRotationAxisType())
			{
			case AxisType::X:
				switch (Hexahedron::getInstance()->getRotationDirection())
				{
				case Direction::Positive:
					Hexahedron::getInstance()->getRotXDegree() += 1.0f;
					break;
				case Direction::Negative:
					Hexahedron::getInstance()->getRotXDegree() -= 1.0f;
					break;
				default:
					break;
				}
				break;
			case AxisType::Y:
				switch (Hexahedron::getInstance()->getRotationDirection())
				{
				case Direction::Positive:
					Hexahedron::getInstance()->getRotYDegree() += 1.0f;
					break;
				case Direction::Negative:
					Hexahedron::getInstance()->getRotYDegree() -= 1.0f;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		// 육면체 공전
		else if (Hexahedron::getInstance()->isOnRevolutionTimer()) {
			switch (Hexahedron::getInstance()->getRevolutionDirection())
			{
			case Direction::Positive:
				Hexahedron::getInstance()->getRevYDegree() += 1.0f;
				break;
			case Direction::Negative:
				Hexahedron::getInstance()->getRevYDegree() -= 1.0f;
				break;
			default:
				break;
			}
		}

		if (pCone->isOnRotationTimer()) {
			switch (pCone->getRotationAxisType())
			{
			case AxisType::X:
				switch (pCone->getRotationDirection())
				{
				case Direction::Positive:
					pCone->getRotXDegree() += 1.0f;
					break;
				case Direction::Negative:
					pCone->getRotXDegree() -= 1.0f;
					break;
				default:
					break;
				}
				break;
			case AxisType::Y:
				switch (pCone->getRotationDirection())
				{
				case Direction::Positive:
					pCone->getRotYDegree() += 1.0f;
					break;
				case Direction::Negative:
					pCone->getRotYDegree() -= 1.0f;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		else if (pCone->isOnRevolutionTimer()) {
			switch (pCone->getRevolutionDirection())
			{
			case Direction::Positive:
				pCone->getRevYDegree() -= 1.0f;
				break;
			case Direction::Negative:
				pCone->getRevYDegree() += 1.0f;
				break;
			default:
				break;
			}
		}
		break;
	case Shape::Spere_And_Cylinder:
		if (pSphere->isOnRotationTimer()) {
			switch (pSphere->getRotationAxisType())
			{
			case AxisType::X:
				switch (pSphere->getRotationDirection())
				{
				case Direction::Positive:
					pSphere->getRotXDegree() += 1.0f;
					break;
				case Direction::Negative:
					pSphere->getRotXDegree() -= 1.0f;
					break;
				default:
					break;
				}
				break;
			case AxisType::Y:
				switch (pSphere->getRotationDirection())
				{
				case Direction::Positive:
					pSphere->getRotYDegree() += 1.0f;
					break;
				case Direction::Negative:
					pSphere->getRotYDegree() -= 1.0f;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		else if (pSphere->isOnRevolutionTimer()) {
			switch (pSphere->getRevolutionDirection())
			{
			case Direction::Positive:
				pSphere->getRevYDegree() -= 1.0f;
				break;
			case Direction::Negative:
				pSphere->getRevYDegree() += 1.0f;
				break;
			default:
				break;
			}
		}

		if (pCylinder->isOnRotationTimer()) {
			switch (pCylinder->getRotationAxisType())
			{
			case AxisType::X:
				switch (pCylinder->getRotationDirection())
				{
				case Direction::Positive:
					pCylinder->getRotXDegree() += 1.0f;
					break;
				case Direction::Negative:
					pCylinder->getRotXDegree() -= 1.0f;
					break;
				default:
					break;
				}
				break;
			case AxisType::Y:
				switch (pCylinder->getRotationDirection())
				{
				case Direction::Positive:
					pCylinder->getRotYDegree() += 1.0f;
					break;
				case Direction::Negative:
					pCylinder->getRotYDegree() -= 1.0f;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		else if (pCylinder->isOnRevolutionTimer()) {
			switch (pCylinder->getRevolutionDirection())
			{
			case Direction::Positive:
				pCylinder->getRevYDegree() -= 1.0f;
				break;
			case Direction::Negative:
				pCylinder->getRevYDegree() += 1.0f;
				break;
			default:
				break;
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
	case 'x':
		// 육면체 x축 양방향 자전
		if (Shape::Hexahedron_And_Cone == shapeType) {
			Hexahedron::getInstance()->isOnRevolutionTimer() = false;
			Hexahedron::getInstance()->isOnRotationTimer() = true;
			Hexahedron::getInstance()->getRotationAxisType() = AxisType::X;
			Hexahedron::getInstance()->getRotationDirection() = Direction::Positive;

		}
		// 실린더 x축 양방향 자전
		else if (Shape::Spere_And_Cylinder == shapeType) {
			pCylinder->isOnRotationTimer() = true;
			pCylinder->isOnRevolutionTimer() = false;
			pCylinder->getRotationAxisType() = AxisType::X;
			pCylinder->getRotationDirection() = Direction::Positive;
		}
		break;
	case 'X':
		// 육면체 X축 음방향 자전
		if (Shape::Hexahedron_And_Cone == shapeType) {
			Hexahedron::getInstance()->isOnRevolutionTimer() = false;
			Hexahedron::getInstance()->isOnRotationTimer() = true;
			Hexahedron::getInstance()->getRotationAxisType() = AxisType::X;
			Hexahedron::getInstance()->getRotationDirection() = Direction::Negative;

		}
		// 실린더 X축 음방향 자전
		else if (Shape::Spere_And_Cylinder == shapeType) {
			pCylinder->isOnRotationTimer() = true;
			pCylinder->isOnRevolutionTimer() = false;
			pCylinder->getRotationAxisType() = AxisType::X;
			pCylinder->getRotationDirection() = Direction::Negative;
		}
		break;
	case 'y':
		// 육면체  y축 양방향 자전
		if (Shape::Hexahedron_And_Cone == shapeType) {
			Hexahedron::getInstance()->isOnRevolutionTimer() = false;
			Hexahedron::getInstance()->isOnRotationTimer() = true;
			Hexahedron::getInstance()->getRotationAxisType() = AxisType::Y;
			Hexahedron::getInstance()->getRotationDirection() = Direction::Positive;

		}
		// 실린더 y축 양방향 자전
		else if (Shape::Spere_And_Cylinder == shapeType) {
			pCylinder->isOnRotationTimer() = true;
			pCylinder->isOnRevolutionTimer() = false;
			pCylinder->getRotationAxisType() = AxisType::Y;
			pCylinder->getRotationDirection() = Direction::Positive;
		}
		break;
	case 'Y':
		// 육면체 y축 음방향 자전
		if (Shape::Hexahedron_And_Cone == shapeType) {
			Hexahedron::getInstance()->isOnRevolutionTimer() = false;
			Hexahedron::getInstance()->isOnRotationTimer() = true;
			Hexahedron::getInstance()->getRotationAxisType() = AxisType::Y;
			Hexahedron::getInstance()->getRotationDirection() = Direction::Negative;
		}
		// 실린더 y축 음방향 자전
		else if (Shape::Spere_And_Cylinder == shapeType) {
			pCylinder->isOnRotationTimer() = true;
			pCylinder->isOnRevolutionTimer() = false;
			pCylinder->getRotationAxisType() = AxisType::Y;
			pCylinder->getRotationDirection() = Direction::Negative;
		}
		break;
	case 'a':
		// 원뿔 x축 양방향 자전
		if (Shape::Hexahedron_And_Cone == shapeType) {
			pCone->isOnRotationTimer() = true;
			pCone->isOnRevolutionTimer() = false;
			pCone->getRotationAxisType() = AxisType::X;
			pCone->getRotationDirection() = Direction::Positive;
		}
		// 구 x축 양방향 자전
		else if (Shape::Spere_And_Cylinder == shapeType) {
			pSphere->isOnRotationTimer() = true;
			pSphere->isOnRevolutionTimer() = false;
			pSphere->getRotationAxisType() = AxisType::X;
			pSphere->getRotationDirection() = Direction::Positive;
		}
		break;
	case 'A':
		// 원뿔 x축 음방향 자전
		if (Shape::Hexahedron_And_Cone == shapeType) {
			pCone->isOnRotationTimer() = true;
			pCone->isOnRevolutionTimer() = false;
			pCone->getRotationAxisType() = AxisType::X;
			pCone->getRotationDirection() = Direction::Negative;
		}
		//// 구 x축 음방향 자전
		else if (Shape::Spere_And_Cylinder == shapeType) {
			pSphere->isOnRotationTimer() = true;
			pSphere->isOnRevolutionTimer() = false;
			pSphere->getRotationAxisType() = AxisType::X;
			pSphere->getRotationDirection() = Direction::Negative;
		}
		break;
	case 'b':
		//// 원뿔  y축 양방향 자전
		if (Shape::Hexahedron_And_Cone == shapeType) {
			pCone->isOnRotationTimer() = true;
			pCone->isOnRevolutionTimer() = false;
			pCone->getRotationAxisType() = AxisType::Y;
			pCone->getRotationDirection() = Direction::Positive;
		}
		// 구 y축 양방향 자전
		else if (Shape::Spere_And_Cylinder == shapeType) {
			pSphere->isOnRotationTimer() = true;
			pSphere->isOnRevolutionTimer() = false;
			pSphere->getRotationAxisType() = AxisType::Y;
			pSphere->getRotationDirection() = Direction::Positive;
		}
		break;
	case 'B':
		//// 원뿔  y축 음방향 자전
		if (Shape::Hexahedron_And_Cone == shapeType) {
			pCone->isOnRotationTimer() = true;
			pCone->isOnRevolutionTimer() = false;
			pCone->getRotationAxisType() = AxisType::Y;
			pCone->getRotationDirection() = Direction::Negative;
		}
		//// 구 y축 음방향 자전
		else if (Shape::Spere_And_Cylinder == shapeType) {
			pSphere->isOnRotationTimer() = true;
			pSphere->isOnRevolutionTimer() = false;
			pSphere->getRotationAxisType() = AxisType::Y;
			pSphere->getRotationDirection() = Direction::Negative;
		}
		break;
	case 'r':
		// 육면체, 원뿔  y축 양방향 공전
		if (Shape::Hexahedron_And_Cone == shapeType) {
			Hexahedron::getInstance()->isOnRevolutionTimer() = true;
			Hexahedron::getInstance()->isOnRotationTimer() = false;
			Hexahedron::getInstance()->getRevolutionDirection() = Direction::Positive;

			pCone->isOnRevolutionTimer() = true;
			pCone->isOnRotationTimer() = false;
			pCone->getRevolutionDirection() = Direction::Positive;
		}
		// 구, 원기둥 y축 양방향 공전
		else if (Shape::Spere_And_Cylinder == shapeType) {
			pSphere->isOnRevolutionTimer() = true;
			pSphere->isOnRotationTimer() = false;
			pSphere->getRevolutionDirection() = Direction::Positive;

			pCylinder->isOnRevolutionTimer() = true;
			pCylinder->isOnRotationTimer() = false;
			pCylinder->getRevolutionDirection() = Direction::Positive;
		}
		break;
	case 'R':
		// 육면체, 원뿔  y축 음방향 공전
		if (Shape::Hexahedron_And_Cone == shapeType) {
			Hexahedron::getInstance()->isOnRevolutionTimer() = true;
			Hexahedron::getInstance()->isOnRotationTimer() = false;
			Hexahedron::getInstance()->getRevolutionDirection() = Direction::Negative;

			pCone->isOnRevolutionTimer() = true;
			pCone->isOnRotationTimer() = false;
			pCone->getRevolutionDirection() = Direction::Negative;
		}
		// 구, 원기둥 y축 음방향 공전
		else if (Shape::Spere_And_Cylinder == shapeType) {
			pSphere->isOnRevolutionTimer() = true;
			pSphere->isOnRotationTimer() = false;
			pSphere->getRevolutionDirection() = Direction::Negative;

			pCylinder->isOnRevolutionTimer() = true;
			pCylinder->isOnRotationTimer() = false;
			pCylinder->getRevolutionDirection() = Direction::Negative;
		}
		break;
	case 'c':
		if (Shape::None == shapeType) {
			shapeType = Shape::Hexahedron_And_Cone;
		}
		else if (Shape::Hexahedron_And_Cone == shapeType) {
			shapeType = Shape::Spere_And_Cylinder;
		}
		else if (Shape::Spere_And_Cylinder == shapeType) {
			shapeType = Shape::None;
		}
		break;
	case 's':
		// Reset
		shapeType = Shape::None;
		Hexahedron::getInstance()->isOnRevolutionTimer() = false;
		Hexahedron::getInstance()->isOnRevolutionTimer() = false;
		Hexahedron::getInstance()->getRotationDirection() = Direction::Idle;
		Hexahedron::getInstance()->getRevolutionDirection() = Direction::Idle;
		Hexahedron::getInstance()->getRotationAxisType() = AxisType::None;
		Hexahedron::getInstance()->getRevXDegree() = 30.0f;
		Hexahedron::getInstance()->getRevYDegree() = -30.0f;
		Hexahedron::getInstance()->getRotXDegree() = 0.0f;
		Hexahedron::getInstance()->getRotYDegree() = 0.0f;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 3; ++j) {
				Hexahedron::getInstance()->getVertex(i, j) = Hexahedron::getInstance()->getTempVertex(i, j);
			}
		}

		pCone->getRevXDegree() = 0.0f;
		pCone->getRevYDegree() = 0.0f;
		pCone->getRotXDegree() = 0.0f;
		pCone->getRotYDegree() = 0.0f;
		pCone->isOnRotationTimer() = false;
		pCone->isOnRevolutionTimer() = false;
		pCone->getRotationAxisType() = AxisType::None;
		pCone->getRotationDirection() = Direction::Idle;
		pCone->getRevolutionDirection() = Direction::Idle;

		pSphere->getRevXDegree() = 0.0f;
		pSphere->getRevYDegree() = 0.0f;
		pSphere->getRotXDegree() = 0.0f;
		pSphere->getRotYDegree() = 0.0f;
		pSphere->isOnRotationTimer() = false;
		pSphere->isOnRevolutionTimer() = false;
		pSphere->getRotationAxisType() = AxisType::None;
		pSphere->getRotationDirection() = Direction::Idle;
		pSphere->getRevolutionDirection() = Direction::Idle;

		pCylinder->getRevXDegree() = 0.0f;
		pCylinder->getRevYDegree() = 0.0f;
		pCylinder->getRotXDegree() = 0.0f;
		pCylinder->getRotYDegree() = 0.0f;
		pCylinder->isOnRotationTimer() = false;
		pCylinder->isOnRevolutionTimer() = false;
		pCylinder->getRotationAxisType() = AxisType::None;
		pCylinder->getRotationDirection() = Direction::Idle;
		pCylinder->getRevolutionDirection() = Direction::Idle;
		break;
	case 'h':
		glEnable(GL_DEPTH_TEST);
		break;
	case 'H':
		glDisable(GL_DEPTH_TEST);
		break;
	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'W':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}