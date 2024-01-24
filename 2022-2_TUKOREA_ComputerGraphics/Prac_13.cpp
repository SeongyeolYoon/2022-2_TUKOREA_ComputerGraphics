#include "pch.h"

std::mt19937 mersenne{ std::random_device{}() };
std::uniform_real_distribution<GLfloat> urColor{ 0.0f,1.0f };
enum Direction{Idle = 0, Positive, Negative };
enum AxisType{None = 0, X, Y};
class Shader;
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
{-0.25f,0.25f,-0.25f}
,{-0.25f,0.25f,0.25f}
,{0.25f,0.25f,0.25f}
,{0.25f,0.25f,-0.25f}
,{-0.25f,-0.25f,-0.25f}
,{-0.25f,-0.25f,0.25f}
,{0.25f,-0.25f,0.25f}
,{0.25f,-0.25f,-0.25f} };
	GLfloat tempVertex[8][3]{
{-0.25f,0.25f,-0.25f}
,{-0.25f,0.25f,0.25f}
,{0.25f,0.25f,0.25f}
,{0.25f,0.25f,-0.25f}
,{-0.25f,-0.25f,-0.25f}
,{-0.25f,-0.25f,0.25f}
,{0.25f,-0.25f,0.25f}
,{0.25f,-0.25f,-0.25f} };
	const GLfloat color[8][3]
	{ {urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)}
		, {urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)},
		{urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)},
		{urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)} };
	const unsigned int index[36]{ 0,1,2,0,2,3,4,5,6,4,6,7,0,1,5,0,5,4,3,2,6,3,6,7,1,5,6,1,6,2,0,4,7,0,7,3 };
	Direction dir{ Direction::Idle };
	AxisType rotationAxisType{ AxisType::None };
	GLfloat xRotationDegree{ 0.0f };
	GLfloat yRotationDegree{ 0.0f };
	GLfloat xMoveAmount{ 0.0f };
	GLfloat yMoveAmount{ 0.0f };
	bool isOn{ false };
	bool onTimer{ false };
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
	
	bool& getState() { return isOn; }

	bool& getTimer() { return onTimer; }

	GLfloat& getXRotationDegree() { return xRotationDegree; }

	GLfloat& getYRotationDegree() { return yRotationDegree; }

	AxisType& getRotationAxisType() { return rotationAxisType; }


	Direction& getDirection() { return dir; }

	GLfloat& getVertex(const int& x, const int& y) { return vertex[x][y]; }

	GLfloat& getTempVertex(const int& x, const int& y) { return tempVertex[x][y]; }

	GLfloat& getXMoveAmount() { return xMoveAmount; }

	GLfloat& getYMoveAmount() { return yMoveAmount; }

	void render() const { glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); }
};

class SquarePyramid {
private:
	friend class Shader;
	static SquarePyramid* pInst;
	GLfloat vertex[5][3]{
	{0.0f,0.25f,0.0f},
	{-0.25f,-0.25f,-0.25f},
	{-0.25f,-0.25f,0.25f},
	{0.25f,-0.25f,0.25f},
	{0.25f,-0.25f,-0.25f}
	};
	GLfloat tempVertex[5][3]{
	{0.0f,0.25f,0.0f},
	{-0.25f,-0.25f,-0.25f},
	{-0.25f,-0.25f,0.25f},
	{0.25f,-0.25f,0.25f},
	{0.25f,-0.25f,-0.25f}
	};
	const GLfloat color[5][3]{ 
	{urColor(mersenne),urColor(mersenne),urColor(mersenne)} ,{urColor(mersenne),urColor(mersenne),urColor(mersenne)} ,
	{urColor(mersenne),urColor(mersenne),urColor(mersenne)} ,{urColor(mersenne),urColor(mersenne),urColor(mersenne)} ,
	{urColor(mersenne),urColor(mersenne),urColor(mersenne)} };
	unsigned int index[18]{ 0,2,1,0,2,3,0,3,4,0,1,4,1,2,3,1,3,4 };
	Direction dir{ Direction::Idle };
	AxisType rotationAxisType{ AxisType::None };
	GLfloat xRotationDegree{ 0.0f };
	GLfloat yRotationDegree{ 0.0f };
	GLfloat xMoveAmount{ 0.0f };
	GLfloat yMoveAmount{ 0.0f };
	bool isOn{ false };
	bool onTimer{ false };
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

	GLfloat& getXRotationDegree() { return xRotationDegree; }

	GLfloat& getYRotationDegree() { return yRotationDegree; }

	AxisType& getRoationAxisType() { return rotationAxisType; }

	bool& getState() { return isOn; }

	bool& getTimer() { return onTimer; }

	GLfloat& getVertex(const int& x, const int& y) { return vertex[x][y]; }

	GLfloat& getTempVertex(const int& x, const int& y) { return tempVertex[x][y]; }

	Direction& getDirection() { return dir; }

	GLfloat& getXMoveAmount() { return xMoveAmount; }

	GLfloat& getYMoveAmount() { return yMoveAmount; }

	void render() const { glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0); }
};

class Cone {
private:
	GLUquadric* qObj;
public:
	Cone()
	{
		qObj = gluNewQuadric();
	}

	void render() const 
	{ 

		gluQuadricDrawStyle(qObj, GLU_LINE);
		gluQuadricNormals(qObj, GLU_SMOOTH);
		gluQuadricOrientation(qObj, GLU_OUTSIDE);
		gluCylinder(qObj, 1.0, 2.0, 2.0, 20, 8);
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
SquarePyramid* SquarePyramid::pInst = nullptr;
constexpr GLuint wWidth{ 800 };
constexpr GLuint wHeight{ 600 };
bool g_onCulling{ false };

GLvoid RenderScene();
GLvoid Reshape(int, int);
GLvoid TimerFunc(int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid SpecialKeyboard(int key, int x, int y);
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

	Shader::getInstance()->glGenerate();
	Shader::getInstance()->initBuffer();
	Shader::getInstance()->initShader();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutTimerFunc(10, TimerFunc, 1);
	glutMainLoop();
}

GLvoid RenderScene()
{
	Shader::getInstance()->initBuffer();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (g_onCulling) {
		glEnable(GL_DEPTH_TEST);
	}
	else {
		glDisable(GL_DEPTH_TEST);
	}

	glm::mat4 transform(1.0f);
	glm::mat4 revX{ 1.0f };
	glm::mat4 revY{ 1.0f };
	revX = revX = glm::rotate(revX, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	revY = glm::rotate(revY, glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = revX * revY;
	unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "model");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));
	glBindVertexArray(Shader::getInstance()->getVao()[0]);
	CoordSystem::getInstance()->render();
	
	if (Hexahedron::getInstance()->getState()) {
		glm::mat4 transformMatrix{ 1.0f };
		glm::mat4 parentMatrix{ 1.0f };
		glm::mat4 revolutionMatrix{ 1.0f };
		glm::mat4 translationMatrix{ 1.0f };
		glm::mat4 rotationMatrix{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		glm::mat4 revX{ 1.0f };
		glm::mat4 revY{ 1.0f };
		glm::mat4 rotTransFirst{ 1.0f };
		glm::mat4 rotX{ 1.0f };
		glm::mat4 rotY{ 1.0f };
		glm::mat4 rotTransLast{ 1.0f };
		revX = revX = glm::rotate(revX, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		revY = glm::rotate(revY, glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		rotTransLast = glm::translate(rotTransLast, glm::vec3(0.0f, 0.0f, 0.0f));
		rotX = glm::rotate(rotX, glm::radians(Hexahedron::getInstance()->getXRotationDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
		rotY = glm::rotate(rotY, glm::radians(Hexahedron::getInstance()->getYRotationDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
		rotTransFirst = glm::translate(rotTransFirst, glm::vec3(0.0f, 0.0f, 0.0f));
		revolutionMatrix = revX * revY;
		translationMatrix = glm::translate(translationMatrix, glm::vec3(Hexahedron::getInstance()->getXMoveAmount(), Hexahedron::getInstance()->getYMoveAmount(), 0.0f));
		rotationMatrix = rotTransLast * rotX * rotY * rotTransFirst;
		transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
		unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "model");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glBindVertexArray(Shader::getInstance()->getVao()[1]);
		Hexahedron::getInstance()->render();
	}
	else if (SquarePyramid::getInstance()->getState()) {
		glm::mat4 transformMatrix{ 1.0f };
		glm::mat4 parentMatrix{ 1.0f };
		glm::mat4 revolutionMatrix{ 1.0f };
		glm::mat4 translationMatrix{ 1.0f };
		glm::mat4 rotationMatrix{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		glm::mat4 revX{ 1.0f };
		glm::mat4 revY{ 1.0f };
		glm::mat4 rotTransFirst{ 1.0f };
		glm::mat4 rotX{ 1.0f };
		glm::mat4 rotY{ 1.0f };
		glm::mat4 rotTransLast{ 1.0f };
		revX = revX = glm::rotate(revX, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		revY = glm::rotate(revY, glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		rotTransLast = glm::translate(rotTransLast, glm::vec3(0.0f, 0.0f, 0.0f));
		rotX = glm::rotate(rotX, glm::radians(SquarePyramid::getInstance()->getXRotationDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
		rotY = glm::rotate(rotY, glm::radians(SquarePyramid::getInstance()->getYRotationDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
		rotTransFirst = glm::translate(rotTransFirst, glm::vec3(0.0f, 0.0f, 0.0f));
		revolutionMatrix = revX * revY;
		translationMatrix = glm::translate(translationMatrix, glm::vec3(SquarePyramid::getInstance()->getXMoveAmount(), SquarePyramid::getInstance()->getYMoveAmount(), 0.0f));
		rotationMatrix = rotTransLast * rotX * rotY * rotTransFirst;
		transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
		unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "model");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glBindVertexArray(Shader::getInstance()->getVao()[2]);
		SquarePyramid::getInstance()->render();
	}

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'c':
		Hexahedron::getInstance()->getState() = true;
		SquarePyramid::getInstance()->getState() = false;
		SquarePyramid::getInstance()->getTimer() = false;
		break;
	case 'p':
		Hexahedron::getInstance()->getState() = false;
		Hexahedron::getInstance()->getTimer() = false;
		SquarePyramid::getInstance()->getState() = true;
		break;
	case 'h':
		g_onCulling = !g_onCulling;
		break;
	case 'x':
		if (Hexahedron::getInstance()->getState()) {
			Hexahedron::getInstance()->getTimer() = true;
			Hexahedron::getInstance()->getRotationAxisType() = AxisType::X;
			Hexahedron::getInstance()->getDirection() = Direction::Positive;
		}
		if (SquarePyramid::getInstance()->getState()) {
			SquarePyramid::getInstance()->getTimer() = true;
			SquarePyramid::getInstance()->getRoationAxisType() = AxisType::X;
			SquarePyramid::getInstance()->getDirection() = Direction::Positive;
		}
		break;
	case 'X':
		if (Hexahedron::getInstance()->getState()) {
			Hexahedron::getInstance()->getTimer() = true;
			Hexahedron::getInstance()->getRotationAxisType() = AxisType::X;
			Hexahedron::getInstance()->getDirection() = Direction::Negative;
		}
		if (SquarePyramid::getInstance()->getState()) {
			SquarePyramid::getInstance()->getTimer() = true;
			SquarePyramid::getInstance()->getRoationAxisType() = AxisType::X;
			SquarePyramid::getInstance()->getDirection() = Direction::Negative;
		}
		break;
	case 'y':
		if (Hexahedron::getInstance()->getState()) {
			Hexahedron::getInstance()->getTimer() = true;
			Hexahedron::getInstance()->getRotationAxisType() = AxisType::Y;
			Hexahedron::getInstance()->getDirection() = Direction::Positive;
		}
		if (SquarePyramid::getInstance()->getState()) {
			SquarePyramid::getInstance()->getTimer() = true;
			SquarePyramid::getInstance()->getRoationAxisType() = AxisType::Y;
			SquarePyramid::getInstance()->getDirection() = Direction::Positive;
		}
		break;
	case 'Y':
		if (Hexahedron::getInstance()->getState()) {
			Hexahedron::getInstance()->getTimer() = true;
			Hexahedron::getInstance()->getRotationAxisType() = AxisType::Y;
			Hexahedron::getInstance()->getDirection() = Direction::Negative;
		}
		if (SquarePyramid::getInstance()->getState()) {
			SquarePyramid::getInstance()->getTimer() = true;
			SquarePyramid::getInstance()->getRoationAxisType() = AxisType::Y;
			SquarePyramid::getInstance()->getDirection() = Direction::Negative;
		}
		break;
	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'W':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 's':
		if (Hexahedron::getInstance()->getState()) {
			for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 3; ++j) {
					Hexahedron::getInstance()->getVertex(i, j) = Hexahedron::getInstance()->getTempVertex(i, j);
				}
			}
			Hexahedron::getInstance()->getXRotationDegree() = 0;
			Hexahedron::getInstance()->getYRotationDegree() = 0;
			Hexahedron::getInstance()->getRotationAxisType() = AxisType::None;
			Hexahedron::getInstance()->getXMoveAmount() = 0.0f;
			Hexahedron::getInstance()->getYMoveAmount() = 0.0f;
			Hexahedron::getInstance()->getTimer() = false;
		}
		else if (SquarePyramid::getInstance()->getState()) {
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 3; ++j) {
					SquarePyramid::getInstance()->getVertex(i, j) = SquarePyramid::getInstance()->getTempVertex(i, j);
				}
			}
			SquarePyramid::getInstance()->getXRotationDegree() = 0;
			SquarePyramid::getInstance()->getYRotationDegree() = 0;
			SquarePyramid::getInstance()->getRoationAxisType() = AxisType::None;
			SquarePyramid::getInstance()->getXMoveAmount() = 0.0f;
			SquarePyramid::getInstance()->getYMoveAmount() = 0.0f;
			SquarePyramid::getInstance()->getTimer() = false;
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (Hexahedron::getInstance()->getState()) 
			Hexahedron::getInstance()->getXMoveAmount() -= 0.1f;
		else if (SquarePyramid::getInstance()->getState())
			SquarePyramid::getInstance()->getXMoveAmount() -= 0.1f;
		break;
	case GLUT_KEY_RIGHT:
		if (Hexahedron::getInstance()->getState()) 
			Hexahedron::getInstance()->getXMoveAmount() += 0.1f;
		else if (SquarePyramid::getInstance()->getState()) 
			SquarePyramid::getInstance()->getXMoveAmount() += 0.1f;
		break;
	case GLUT_KEY_UP:
		if (Hexahedron::getInstance()->getState()) 
			Hexahedron::getInstance()->getYMoveAmount() += 0.1f;
		else if (SquarePyramid::getInstance()->getState()) 
			SquarePyramid::getInstance()->getYMoveAmount() += 0.1f;
		break;
	case GLUT_KEY_DOWN:
		if (Hexahedron::getInstance()->getState()) 
			Hexahedron::getInstance()->getYMoveAmount() -= 0.1f;
		else if (SquarePyramid::getInstance()->getState())
			SquarePyramid::getInstance()->getYMoveAmount() -= 0.1f;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid TimerFunc(int value)
{
	if (Hexahedron::getInstance()->getState()) {
		if (Hexahedron::getInstance()->getTimer()) {
			switch (Hexahedron::getInstance()->getRotationAxisType())
			{
			case AxisType::X:
				switch (Hexahedron::getInstance()->getDirection())
				{
				case Direction::Positive:
					Hexahedron::getInstance()->getXRotationDegree() += 1.0f;
					break;
				case Direction::Negative:
					Hexahedron::getInstance()->getXRotationDegree() -= 1.0f;
					break;
				default:
					break;
				}
				break;
			case AxisType::Y:
				switch (Hexahedron::getInstance()->getDirection())
				{
				case Direction::Positive:
					Hexahedron::getInstance()->getYRotationDegree() += 1.0f;
					break;
				case Direction::Negative:
					Hexahedron::getInstance()->getYRotationDegree() -= 1.0f;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}
	if (SquarePyramid::getInstance()->getState()) {
		if (SquarePyramid::getInstance()->getTimer()) {
			switch (SquarePyramid::getInstance()->getRoationAxisType())
			{
			case AxisType::X:
				switch (SquarePyramid::getInstance()->getDirection())
				{
				case Direction::Positive:
					SquarePyramid::getInstance()->getXRotationDegree() += 1.0f;
					break;
				case Direction::Negative:
					SquarePyramid::getInstance()->getXRotationDegree() -= 1.0f;
					break;
				default:
					break;
				}
				break;
			case AxisType::Y:
				switch (SquarePyramid::getInstance()->getDirection())
				{
				case Direction::Positive:
					SquarePyramid::getInstance()->getYRotationDegree() += 1.0f;
					break;
				case Direction::Negative:
					SquarePyramid::getInstance()->getYRotationDegree() -= 1.0f;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunc, 1);
}