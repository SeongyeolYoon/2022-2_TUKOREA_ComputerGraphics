#include "pch.h"

std::mt19937 mersenne{ std::random_device{}() };
std::uniform_real_distribution<GLfloat> urColor{ 0.0f,1.0f };

enum class Shape { None = 0, Hexahedron_And_Cone, Spere_And_Cylinder };
enum class Direction { Idle = 0, Positive, Negative };
enum class AxisType { None = 0, X, Y };

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
{1.0f,0.0f,0.0f}, {1.0f,0.0f,0.0f},
{0.0f,1.0f,0.0f}, {0.0f,1.0f,0.0f},
{0.0f,0.0f,1.0f}, {0.0f,0.0f,1.0f} };
	GLfloat rotXDegree{ 30.0f };
	GLfloat rotYDegree{-60.0f};
	bool onRotation{ false };
	Direction rotationDirection{ Direction::Idle };
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

	GLfloat& getRotXDegree() { return rotXDegree; }

	GLfloat& getRotYDegree() { return rotYDegree; }

	bool& isOnRotation() { return onRotation; }

	Direction& getRotationDirection() { return rotationDirection; }

	void render() const
	{
		glPointSize(2.0f);
		glDrawArrays(GL_LINES, 0, 6);
	}
};

class Hexahedron {
private:
	friend class Shader;
	static Hexahedron* pInst;
	GLfloat vertex[8][3]{
	{-0.05f,0.05f,-0.05f}
	,{-0.05f,0.05f,0.05f}
	,{0.05f,0.05f,0.05f}
	,{0.05f,0.05f,-0.05f}
	,{-0.05f,-0.05f,-0.05f}
	,{-0.05f,-0.05f,0.05f}
	,{0.05f,-0.05f,0.05f}
	,{0.05f,-0.05f,-0.05f} };
	GLfloat tempVertex[8][3]{
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
	GLfloat revXDegree{ 0.0f };
	GLfloat revYDegree{ 0.0f };
	GLfloat rotXDegree{ 0.0f };
	GLfloat rotYDegree{ 0.0f };
	AxisType rotationAxisType{ AxisType::None };
	Direction rotationDirectopn{ Direction::Idle };
	Direction revolutionDirection{ Direction::Idle };
	GLint degree{ 0 };
	GLfloat radian{ 0.0f };
	GLfloat xPos{ 0.0f };
	GLfloat yPos{ 0.0f };
	GLfloat zPos{ 0.0f };
	GLfloat tempXPos{ 0.0f };
	GLfloat tempYPos{ 0.0f };
	GLfloat tempZPos{ 0.0f };
	GLfloat scaleAmount{ 0.1f };
	GLfloat xScaleAmount{ 1.0f };
	GLfloat yScaleAmount{ 1.0f };
	GLfloat zScaleAmount{ 1.0f };
	GLfloat radianAmount{ 0.0006f };
	GLfloat getMoveAMount{ 0.01f };
	GLfloat distance{ 0.0f};
	glm::vec3 positionVector{ glm::vec3{0.5f,0.0f,0.0f} };
	glm::vec3 directionVector{ glm::vec3{0.0f,0.0f,0.0f} };
	glm::vec3 tempPositionVector{ glm::vec3{0.0f,0.0f,0.0f} };
	glm::vec3 tempLengthVector{ glm::vec3{0.0f,0.0f,0.0f} };
	bool onRotationTimer{ false };
	bool onRevolutionTimer{ false };
	bool onTornadoTimer{ false };
	bool onMoveToStartPoint{ false };
	bool onMoveToOpponentPoint{ false };
	bool ownAxis{ true };
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

	GLfloat& getXPos() { return xPos; }

	GLfloat& getYPos() { return yPos; }
	
	GLfloat& getZPos() { return zPos; }

	GLfloat& getTempXPos() { return tempXPos; }

	GLfloat& getTempYPos() { return tempYPos; }

	GLfloat& getTempZPos() { return tempZPos; }

	GLfloat& getScaleAmount() { return scaleAmount; }

	GLfloat& getXScaleAmount() { return xScaleAmount; }

	GLfloat& getYScaleAmount() { return yScaleAmount; }

	GLfloat& getZScaleAmount() { return zScaleAmount; }

	Direction& getRotationDirection() { return rotationDirectopn; }

	Direction& getRevolutionDirection() { return revolutionDirection; }

	AxisType& getRotationAxisType() { return rotationAxisType; }

	GLint& getDegree() { return degree; }

	GLfloat& getRadian() { return radian; }

	GLfloat& getRadianAmount() { return radianAmount; }

	GLfloat& getMoveAmount() { return getMoveAMount; }

	GLfloat& getDistance() { return distance; }

	glm::vec3& getPositionVector() { return positionVector; }

	glm::vec3& getDirectionVector() { return directionVector; }

	glm::vec3& getTempPositionVector() {return tempPositionVector; }

	glm::vec3& getTempLengthVector() { return tempLengthVector; }

	bool& isOnRotationTimer() { return onRotationTimer; }

	bool& isOnRevolutionTimer() { return onRevolutionTimer; }

	bool& isOnTornadoTimer() { return onTornadoTimer; }

	bool& isOnMoveToStartPoint() { return onMoveToStartPoint; }
	
	bool& isOnMoveToOpponentPoint() { return onMoveToOpponentPoint; }

	bool& isOwnAxis() { return ownAxis; }

	void render() const { glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); }
};

class Point {
private:
	friend class Shader;
	static const int nPoint = 1800;
	GLfloat vertex[3]{ 0.0f,0.0f,0.0f };
	GLfloat color[3]{ 1.0f,0.0f,1.0f };
	GLint degree{ 0 };
	GLfloat radian{ 0.0f };
public:
	Point()
	{

	}

	void setDegree(const GLint& degreeIn) { degree = degreeIn; }

	void setRadian(const GLfloat& radianIn) { radian = radianIn; }

	const GLint& getDegree() const  { return degree; }
	
	const GLfloat& getRadian() const { return radian; }

	static const int& getNPoint() { return nPoint; }

	void render() const
	{
		glPointSize(2.0f);
		glDrawArrays(GL_POINTS, 0, 1);
	}
};

Point* pPoint[1800];

class Sphere {
private:
	GLUquadricObj* pObj;
	GLfloat revXDegree{ 0.0f };
	GLfloat revYDegree{ 0.0f };
	GLfloat rotXDegree{ 0.0f };
	GLfloat rotYDegree{ 0.0f };
	AxisType rotationAxisType{ AxisType::None };
	Direction rotationDirectopn{ Direction::Idle };
	Direction revolutionDirection{ Direction::Idle };
	GLint degree{ 0 };
	GLfloat radian{ 0.0f };
	GLfloat xMoveAmount{ 0.0f };
	GLfloat yMoveAmount{ 0.0f };
	GLfloat zMoveAmount{ 0.0f };
	GLfloat xPos{ 0.0f };
	GLfloat yPos{ 0.0f };
	GLfloat zPos{ 0.0f };
	GLfloat tempXPos{ 0.0f };
	GLfloat tempYPos{ 0.0f };
	GLfloat tempZPos{ 0.0f };
	GLfloat scaleAmount{ 0.1f };
	GLfloat xScaleAmount{ 1.0f };
	GLfloat yScaleAmount{ 1.0f };
	GLfloat zScaleAmount{ 1.0f };
	GLfloat moveAmount{ 0.01f };
	GLfloat radianAmount{ 0.0006f };
	GLfloat distance{ 0.0f };
	glm::vec3 positionVector{ glm::vec3{-0.5f,0.0f,0.0f} };
	glm::vec3 directionVector{ glm::vec3{0.0f,0.0f,0.0f} };
	glm::vec3 tempPositionVector{ glm::vec3{0.0f,0.0f,0.0f} };
	bool ownAxis{ true };
	bool onRotationTimer{ false };
	bool onRevolutionTimer{ false };
	bool onTornadoTimer{ false };
	bool onMoveToStartPoint{ false };
	bool onMoveToOpponentPoint{ false };
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

	GLfloat& getXPos() { return xPos; }

	GLfloat& getYPos() { return yPos; }

	GLfloat& getZPos() { return zPos; }

	GLfloat& getTempXPos() { return tempXPos; }

	GLfloat& getTempYPos() { return tempYPos; }

	GLfloat& getTempZPos() { return tempZPos; }

	GLfloat& getScaleAmount() { return scaleAmount; }

	GLfloat& getXScaleAmount() { return xScaleAmount; }

	GLfloat& getYScaleAmount() { return yScaleAmount; }

	GLfloat& getZScaleAmount() { return zScaleAmount; }

	GLfloat& getMoveAmount() { return moveAmount; }

	GLint& getDegree() { return degree; }

	GLfloat& getRadian() { return radian; }

	GLfloat& getXMoveAmount() { return xMoveAmount; }

	GLfloat& getYMoveAmount() { return yMoveAmount; }

	GLfloat& getZMoveAmount() { return zMoveAmount; }

	GLfloat& getRadianAmount() { return radianAmount; }

	GLfloat& getDistance() { return distance; }

	glm::vec3& getPositionVector() { return positionVector; }

	glm::vec3& getDirectionVector() { return directionVector; }
	
	glm::vec3& getTempPositionVector() { return tempPositionVector; }

	bool& isOwnAxis() { return ownAxis; }

	bool& isOnRotationTimer() { return onRotationTimer; }

	bool& isOnRevolutionTimer() { return onRevolutionTimer; }

	bool& isOnTornadoTimer() { return onTornadoTimer; }
	
	bool& isOnMoveToStartPoint() { return onMoveToStartPoint; }

	bool& isOnMoveToOpponentPoint() { return onMoveToOpponentPoint; }

	void render() const
	{
		gluSphere(pObj, 0.05, 15, 15);
	}
};

class Shader {
private:
	friend class Point;
	friend class CoordSystem;
	friend class Hexahedron;
	static Shader* pInst;
	enum { MaxVao = 1802, MaxVbo = 3604, MaxEbo = 1 };
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

		for (int i = 2; i < Point::getNPoint() + 2; ++i) {
			glBindVertexArray(vao[i]);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[i * 2]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(pPoint[i]->vertex), pPoint[i]->vertex, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[i * 2 + 1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(pPoint[i]->color), pPoint[i]->color, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);
		}
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

//Cone* pCone;
Sphere* pSphere;
//Cylinder* pCylinder;

Shape shapeType{ Shape::Hexahedron_And_Cone };

bool g_onRenderingPoint{ false };
constexpr GLuint wWidth{ 800 };
constexpr GLuint wHeight{ 600 };
constexpr float PI = 3.141592f;
constexpr float deg2Rad = PI / 180.0f;
GLfloat test{ 0.0f };
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
	int degree{ };
	float radian{ };

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

	for (int i{}; i < Point::getNPoint(); ++i) {
		pPoint[i] = new Point;
		degree ++;
		radian += 0.00001f;
	
		pPoint[i]->setDegree(degree);
		pPoint[i]->setRadian(radian);
	}

	//pCone = new Cone;
	pSphere = new Sphere;
	//pCylinder = new Cylinder;

	Shader::getInstance()->glGenerate();
	Shader::getInstance()->initBuffer();
	Shader::getInstance()->initShader();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutTimerFunc(10, TimerFunc, 1);
	glutMainLoop();

	//delete pCone;
	delete pSphere;
	//delete pCylinder;
}

GLvoid RenderScene()
{
	Shader::getInstance()->initBuffer();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 coordMatrix{ 1.0f };

	// CoordSystem
	{
		glm::mat4 transform{ 1.0f };
		glm::mat4 xRevolution{ 1.0f };
		glm::mat4 yRevolution{ 1.0f };
		glm::mat4 trans{ 1.0f };
		glm::mat4 rotation{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		xRevolution = glm::rotate(xRevolution, glm::radians(CoordSystem::getInstance()->getRotXDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
		yRevolution = glm::rotate(yRevolution, glm::radians(CoordSystem::getInstance()->getRotYDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
		coordMatrix = xRevolution * yRevolution * trans * rotation * scaleMatrix;
		unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "model");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(coordMatrix));
		glBindVertexArray(Shader::getInstance()->getVao()[0]);
		CoordSystem::getInstance()->render();
	}

	// Hexahedron
	{
		glm::mat4 transformMaxrix{ 1.0f };
		glm::mat4 parentMatrix{ 1.0f };
		glm::mat4 revolutionMatrix{ 1.0f };
		glm::mat4 translationMatrix{ 1.0f };
		glm::mat4 rotationMatrix{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		glm::mat4 trans1{ 1.0f };
		glm::mat4 trans2{ 1.0f };
		glm::mat4 rotX{ 1.0f };
		glm::mat4 rotY{ 1.0f };
		glm::mat4 revX{ 1.0f };
		glm::mat4 revY{ 1.0f };
		revX = glm::rotate(revX, glm::radians(Hexahedron::getInstance()->getRevXDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
		revY = glm::rotate(revY, glm::radians(Hexahedron::getInstance()->getRevYDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
		trans2 = glm::translate(trans2, glm::vec3(+0.5f, 0.0f, 0.0f));
		trans1 = glm::translate(trans1, glm::vec3(-0.5f, 0.0f, 0.0f));
		rotX = glm::rotate(rotX, glm::radians(Hexahedron::getInstance()->getRotXDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
		rotY = glm::rotate(rotY, glm::radians(Hexahedron::getInstance()->getRotYDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
		parentMatrix = coordMatrix;
		revolutionMatrix = revX * revY;
		rotationMatrix = trans2 * rotX * rotY * trans1;
		scaleMatrix = glm::scale(scaleMatrix, glm::vec3(Hexahedron::getInstance()->getXScaleAmount(), Hexahedron::getInstance()->getYScaleAmount(), Hexahedron::getInstance()->getZScaleAmount()));
		//if(Hexahedron::getInstance()->isOnTornadoTimer())
		//	translationMatrix = glm::translate(translationMatrix, glm::vec3(Hexahedron::getInstance()->getPositionVector().x-0.5f, Hexahedron::getInstance()->getPositionVector().y, Hexahedron::getInstance()->getPositionVector().z));
		//else {
		//}
		translationMatrix = glm::translate(translationMatrix, Hexahedron::getInstance()->getPositionVector());
		if(Hexahedron::getInstance()->isOwnAxis())
			transformMaxrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
		else
			transformMaxrix = scaleMatrix * parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix;

		unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "model");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMaxrix));
		glBindVertexArray(Shader::getInstance()->getVao()[1]);
		Hexahedron::getInstance()->render();
	}

	// pSpere
	{
		glm::mat4 transformMaxrix{ 1.0f };
		glm::mat4 parentMatrix{ 1.0f };
		glm::mat4 revolutionMatrix{ 1.0f };
		glm::mat4 translationMatrix{ 1.0f };
		glm::mat4 rotationMatrix{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		glm::mat4 formMatrix{ 1.0f };
		glm::mat4 trans1{ 1.0f };
		glm::mat4 trans2{ 1.0f };
		glm::mat4 rotX{ 1.0f };
		glm::mat4 rotY{ 1.0f };
		glm::mat4 revX{ 1.0f };
		glm::mat4 revY{ 1.0f };
		glm::mat4 r1{ 1.0f };
		glm::mat4 r2{ 1.0f };
		glm::mat4 r3{ 1.0f };
		revX = glm::rotate(revX, glm::radians(pSphere->getRevXDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
		revY = glm::rotate(revY, glm::radians(pSphere->getRevYDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
		rotX = glm::rotate(rotX, glm::radians(pSphere->getRotXDegree()), glm::vec3(1.0f, 0.0f, 0.0f));
		rotY = glm::rotate(rotY, glm::radians(pSphere->getRotYDegree()), glm::vec3(0.0f, 0.0f, 1.0f));
		r1 = glm::rotate(r1, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		parentMatrix = coordMatrix;
		revolutionMatrix = revX * revY;
		formMatrix = r3 * r2 * r1;
		rotationMatrix = trans1 * rotX * rotY * trans2;
		scaleMatrix = glm::scale(scaleMatrix, glm::vec3(pSphere->getXScaleAmount(),pSphere->getYScaleAmount(),pSphere->getZScaleAmount()));
	/*	if(pSphere->isOnTornadoTimer())
			translationMatrix = glm::translate(translationMatrix, glm::vec3(0.5f + pSphere->getPositionVector().x, pSphere->getPositionVector().y, pSphere->getPositionVector().z));
		else*/
		translationMatrix = glm::translate(translationMatrix,pSphere->getPositionVector());
		if(pSphere->isOwnAxis())
			transformMaxrix = parentMatrix * revolutionMatrix * translationMatrix * formMatrix * rotationMatrix * scaleMatrix;
		else
			transformMaxrix = scaleMatrix  * parentMatrix * revolutionMatrix * translationMatrix * formMatrix * rotationMatrix;
		unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "model");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMaxrix));
		pSphere->render();
	}

	if (g_onRenderingPoint) {
		// pPoint
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			parentMatrix = coordMatrix;
			for (int i = 0; i < Point::getNPoint(); ++i) {
				translationMatrix = glm::translate(translationMatrix, glm::vec3(pPoint[i]->getRadian() * (cosf(pPoint[i]->getDegree() * deg2Rad)), 0.0f, pPoint[i]->getRadian() * sinf(pPoint[i]->getDegree() * deg2Rad)));
				transformMatrix = parentMatrix * translationMatrix;
				unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "model");
				glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
				glBindVertexArray(Shader::getInstance()->getVao()[i]);
				pPoint[i]->render();
			}
		}
	}
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid TimerFunc(int value)
{
	if (Hexahedron::getInstance()->isOnTornadoTimer()) {

		Hexahedron::getInstance()->getDegree()++;
		Hexahedron::getInstance()->getRadian() += Hexahedron::getInstance()->getRadianAmount();
		Hexahedron::getInstance()->getPositionVector().x = Hexahedron::getInstance()->getRadian() * cosf(Hexahedron::getInstance()->getDegree() * deg2Rad);
		Hexahedron::getInstance()->getPositionVector().z = Hexahedron::getInstance()->getRadian() * sinf(Hexahedron::getInstance()->getDegree() * deg2Rad);
		if (Hexahedron::getInstance()->getDegree() >= 1700) {
			g_onRenderingPoint = false;
			Hexahedron::getInstance()->isOnTornadoTimer() = false;
			Hexahedron::getInstance()->getDegree() = 0;
			Hexahedron::getInstance()->getRadian() = 0;
			Hexahedron::getInstance()->getPositionVector() = glm::vec3{ 0.5f,0.0f,0.0f };
		}
	}

	if (Hexahedron::getInstance()->isOnMoveToStartPoint()) {
		
		Hexahedron::getInstance()->getPositionVector() +=  Hexahedron::getInstance()->getMoveAmount() * Hexahedron::getInstance()->getDirectionVector();

		if (Hexahedron::getInstance()->getDistance() < std::sqrtf(std::powf(Hexahedron::getInstance()->getPositionVector().x - Hexahedron::getInstance()->getTempPositionVector().x,2) +
			std::powf(Hexahedron::getInstance()->getPositionVector().y - Hexahedron::getInstance()->getTempPositionVector().y, 2) +
			std::powf(Hexahedron::getInstance()->getPositionVector().z - Hexahedron::getInstance()->getTempPositionVector().z, 2))) {
			Hexahedron::getInstance()->getMoveAmount() = -Hexahedron::getInstance()->getMoveAmount();
			Hexahedron::getInstance()->getTempPositionVector() = Hexahedron::getInstance()->getPositionVector();
		}
	}

	if (Hexahedron::getInstance()->isOnMoveToOpponentPoint()) {
		Hexahedron::getInstance()->getPositionVector() += Hexahedron::getInstance()->getMoveAmount() * Hexahedron::getInstance()->getDirectionVector();

		if (Hexahedron::getInstance()->getDistance() <= (std::sqrtf(std::powf(Hexahedron::getInstance()->getPositionVector().x - Hexahedron::getInstance()->getTempPositionVector().x, 2) +
			std::powf(Hexahedron::getInstance()->getPositionVector().y - Hexahedron::getInstance()->getTempPositionVector().y, 2) +
			std::powf(Hexahedron::getInstance()->getPositionVector().z - Hexahedron::getInstance()->getTempPositionVector().z, 2)))) {
			Hexahedron::getInstance()->isOnMoveToOpponentPoint() = false;
		}
	} 

	if (pSphere->isOnTornadoTimer()) {
		pSphere->getDegree()++;
		pSphere->getRadian() += pSphere->getRadianAmount();
		pSphere->getPositionVector().x = pSphere->getRadian() * cosf(pSphere->getDegree() * deg2Rad);
		pSphere->getPositionVector().z = pSphere->getRadian() * sinf(pSphere->getDegree() * deg2Rad);

		if (pSphere->getDegree() >= 1700) {
			g_onRenderingPoint = false;
			pSphere->isOnTornadoTimer() = false;
			pSphere->getPositionVector() = glm::vec3{ -0.5f,0.0f,0.0f };
			pSphere->getDegree() = 0;
			pSphere->getRadian() = 0;
		}
	}

	if (pSphere->isOnMoveToStartPoint()) {

		pSphere->getPositionVector() += pSphere->getMoveAmount() * pSphere->getDirectionVector();

		if (pSphere->getDistance() < std::sqrtf(std::powf(pSphere->getPositionVector().x - pSphere->getTempPositionVector().x, 2) +
			std::powf(pSphere->getPositionVector().y - pSphere->getTempPositionVector().y, 2) +
			std::powf(pSphere->getPositionVector().z - pSphere->getTempPositionVector().z, 2))) {
			pSphere->getMoveAmount() = -pSphere->getMoveAmount();
			pSphere->getTempPositionVector() = pSphere->getPositionVector();
		}
	}

	if (pSphere->isOnMoveToOpponentPoint()) {
			pSphere->getPositionVector() += pSphere->getMoveAmount() * pSphere->getDirectionVector();

			if (pSphere->getDistance() < std::sqrtf(std::powf(pSphere->getPositionVector().x - pSphere->getTempPositionVector().x, 2) +
				std::powf(pSphere->getPositionVector().y - pSphere->getTempPositionVector().y, 2) +
				std::powf(pSphere->getPositionVector().z - pSphere->getTempPositionVector().z, 2))) {
				pSphere->isOnMoveToOpponentPoint() = false;
			}
	}

	glutPostRedisplay();
	glutTimerFunc(10, TimerFunc, 1);
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: // 육면체 z축 양방향 이동
		Hexahedron::getInstance()->getPositionVector().z += Hexahedron::getInstance()->getMoveAmount();
		break;
	case GLUT_KEY_RIGHT: // 육면체 z축 음방향 이동
		Hexahedron::getInstance()->getPositionVector().z -= Hexahedron::getInstance()->getMoveAmount();
		break;
	case GLUT_KEY_UP: // 육면체 x축 음방향 이동
		Hexahedron::getInstance()->getPositionVector().x -= Hexahedron::getInstance()->getMoveAmount();
		break;
	case GLUT_KEY_DOWN: // 육면체 x축 양방향 이동
		Hexahedron::getInstance()->getPositionVector().x += Hexahedron::getInstance()->getMoveAmount();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid Keyboard(unsigned char key, int x , int y)
{
	switch (key)
	{
	case 't':
		Hexahedron::getInstance()->getMoveAmount() = 0.01f;
		pSphere->getMoveAmount() = 0.01f;
		glm::vec3 destination{ glm::vec3{0.0f,0.0f,0.0f} };
		Hexahedron::getInstance()->getTempPositionVector() = Hexahedron::getInstance()->getPositionVector();
		pSphere->getTempPositionVector() = pSphere->getPositionVector();
		Hexahedron::getInstance()->getDistance() = std::sqrtf(std::powf(destination.x - Hexahedron::getInstance()->getPositionVector().x,2) + 
		std::powf(destination.y - Hexahedron::getInstance()->getPositionVector().y, 2) +
		std::powf(destination.z - Hexahedron::getInstance()->getPositionVector().z, 2));
		pSphere->getDistance() = std::sqrtf(std::powf(destination.x - pSphere->getPositionVector().x, 2) +
		std::powf(destination.y - pSphere->getPositionVector().y, 2) +
		std::powf(destination.z - pSphere->getPositionVector().z, 2));
		Hexahedron::getInstance()->getDirectionVector() = glm::normalize(destination - Hexahedron::getInstance()->getPositionVector());
		pSphere->getDirectionVector() = glm::normalize(destination - pSphere->getPositionVector());
		Hexahedron::getInstance()->isOnMoveToStartPoint() = true;
		pSphere->isOnMoveToStartPoint() = true;
		break;
	case 'T':
		Hexahedron::getInstance()->isOnMoveToStartPoint() = false;
		pSphere->isOnMoveToStartPoint() = false;
		break;
	case 'z': // 육면체, 구 z축 양방향 이동
		Hexahedron::getInstance()->getPositionVector().z += Hexahedron::getInstance()->getMoveAmount();
		pSphere->getPositionVector().z += pSphere->getMoveAmount();
		break;
	case 'x': // 육면체, 구 z축 음방향 이동
		Hexahedron::getInstance()->getPositionVector().z-= Hexahedron::getInstance()->getMoveAmount();
		pSphere->getPositionVector().z -= pSphere->getMoveAmount();
		break;
	case 'v': // 육면체, 구 x축 음방향 이동
		Hexahedron::getInstance()->getPositionVector().x -= Hexahedron::getInstance()->getMoveAmount();
		pSphere->getPositionVector().x -= pSphere->getMoveAmount();
		break;
	case 'b': // 육면체, 구 x축 음방향 이동
		Hexahedron::getInstance()->getPositionVector().x += Hexahedron::getInstance()->getMoveAmount();
		pSphere->getPositionVector().x += pSphere->getMoveAmount();
		break;
	case 'n': // 육면체, 구 y축 음방향 이동
		Hexahedron::getInstance()->getPositionVector().y -= Hexahedron::getInstance()->getMoveAmount();
		pSphere->getYPos() -= pSphere->getMoveAmount();
		break;
	case 'm': // 육면체, 구 y축 양방향 이동
		Hexahedron::getInstance()->getPositionVector().y += Hexahedron::getInstance()->getMoveAmount();
		pSphere->getPositionVector().y += pSphere->getMoveAmount();
		break;
	case 'o': // 구 y축 양방향 이동
		pSphere->getPositionVector().y += pSphere->getMoveAmount();
		break;
	case 'p': // 구 y축 음방향 이동
		pSphere->getPositionVector().y -= pSphere->getMoveAmount();
		break;
	case 'i': // 구 x축 음방향 이동
		pSphere->getPositionVector().x -= pSphere->getMoveAmount();
		break;
	case 'j': // 구 z축 양방향 이동
		pSphere->getPositionVector().z += pSphere->getMoveAmount();
		break;
	case 'k': // 구 x축 양방향 이동
		pSphere->getPositionVector().x += pSphere->getMoveAmount();
		break;
	case 'l': // 구 z축 음방향 이동
		pSphere->getPositionVector().z -= pSphere->getMoveAmount();
		break;
	case 'c': // 육면체 제자리 확대
		Hexahedron::getInstance()->isOwnAxis() = true;
		Hexahedron::getInstance()->getXScaleAmount() += Hexahedron::getInstance()->getScaleAmount();
		Hexahedron::getInstance()->getYScaleAmount() += Hexahedron::getInstance()->getScaleAmount();
		Hexahedron::getInstance()->getZScaleAmount() += Hexahedron::getInstance()->getScaleAmount();
		break;
	case 'C': // 육면체 제자리 축소
		Hexahedron::getInstance()->isOwnAxis() = true;
		Hexahedron::getInstance()->getXScaleAmount() -= Hexahedron::getInstance()->getScaleAmount();
		Hexahedron::getInstance()->getYScaleAmount() -= Hexahedron::getInstance()->getScaleAmount();
		Hexahedron::getInstance()->getZScaleAmount() -= Hexahedron::getInstance()->getScaleAmount();
		break;
	case 'f': // 육면체 원점에 대해서 확대
		Hexahedron::getInstance()->isOwnAxis() = false;
		Hexahedron::getInstance()->getXScaleAmount() += Hexahedron::getInstance()->getScaleAmount();
		Hexahedron::getInstance()->getYScaleAmount() += Hexahedron::getInstance()->getScaleAmount();
		Hexahedron::getInstance()->getZScaleAmount() += Hexahedron::getInstance()->getScaleAmount();
		break;
	case 'F':// 육면체 원점에 대해서 축소
		Hexahedron::getInstance()->isOwnAxis() = false;
		Hexahedron::getInstance()->getXScaleAmount() -= Hexahedron::getInstance()->getScaleAmount();
		Hexahedron::getInstance()->getYScaleAmount() -= Hexahedron::getInstance()->getScaleAmount();
		Hexahedron::getInstance()->getZScaleAmount() -= Hexahedron::getInstance()->getScaleAmount();
		break;
	case 'd': // 구 제자리 확대
		pSphere->isOwnAxis() = true;
		pSphere->getXScaleAmount() += pSphere->getScaleAmount();
		pSphere->getYScaleAmount() += pSphere->getScaleAmount();
		pSphere->getZScaleAmount() += pSphere->getScaleAmount();
		break;
	case 'D': // 구 제자리 축소
		pSphere->isOwnAxis() = true;
		pSphere->getXScaleAmount() -= pSphere->getScaleAmount();
		pSphere->getYScaleAmount() -= pSphere->getScaleAmount();
		pSphere->getZScaleAmount() -= pSphere->getScaleAmount();
		break;
	case 'e':// 구 원점에 대해서 확대
		pSphere->isOwnAxis() = false;
		pSphere->getXScaleAmount() += pSphere->getScaleAmount();
		pSphere->getYScaleAmount() += pSphere->getScaleAmount();
		pSphere->getZScaleAmount() += pSphere->getScaleAmount();
		break;
	case 'E':// 구 원점에 대해서 축소
		pSphere->isOwnAxis() = false;
		pSphere->getXScaleAmount() -= pSphere->getScaleAmount();
		pSphere->getYScaleAmount() -= pSphere->getScaleAmount();
		pSphere->getZScaleAmount() -= pSphere->getScaleAmount();
		break;
	case '[': // 육면체 y축 양방향 이동
		Hexahedron::getInstance()->getPositionVector().y += Hexahedron::getInstance()->getMoveAmount();
		break;
	case ']': // 육면체 y축 음방향 이동
		Hexahedron::getInstance()->getPositionVector().y -= Hexahedron::getInstance()->getMoveAmount();
		break;
	case 'r': // 회오리 위치에 따라 객체 이동
		g_onRenderingPoint = true;
		Hexahedron::getInstance()->getPositionVector() = glm::vec3{ 0.0f,0.0f,0.0f };
		pSphere->getPositionVector() = glm::vec3{ 0.0f,0.0f,0.0f };
		Hexahedron::getInstance()->isOnTornadoTimer() = !Hexahedron::getInstance()->isOnTornadoTimer();
		pSphere->isOnTornadoTimer() = !pSphere->isOnTornadoTimer();
		break;
	case 's':
		Hexahedron::getInstance()->getMoveAmount() = 0.01f;
		pSphere->getMoveAmount() = 0.01f;
		Hexahedron::getInstance()->getTempPositionVector() = Hexahedron::getInstance()->getPositionVector();
		pSphere->getTempPositionVector() = pSphere->getPositionVector();
		glm::vec3 pSpereDestination = Hexahedron::getInstance()->getTempPositionVector();
		glm::vec3 hexahedronDestination = pSphere->getTempPositionVector();
		Hexahedron::getInstance()->getDistance() = (std::sqrtf(std::powf(pSpereDestination.x - hexahedronDestination.x, 2) + std::powf(pSpereDestination.y - hexahedronDestination.y,2) + std::powf(pSpereDestination.z - hexahedronDestination.z,2)));
		pSphere->getDistance() = std::sqrtf(std::powf(hexahedronDestination.x - pSpereDestination.x,2) + std::powf(hexahedronDestination.y - pSpereDestination.y, 2) + std::powf(hexahedronDestination.z - pSpereDestination.z, 2));
		Hexahedron::getInstance()->getDirectionVector() = glm::normalize(hexahedronDestination - pSpereDestination);
		pSphere->getDirectionVector() = glm::normalize(pSpereDestination - hexahedronDestination);
		Hexahedron::getInstance()->isOnMoveToOpponentPoint() = true;
		pSphere->isOnMoveToOpponentPoint() = true;
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