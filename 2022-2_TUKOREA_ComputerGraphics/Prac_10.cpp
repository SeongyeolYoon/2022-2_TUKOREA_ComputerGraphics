#include "pch.h"

class Shader;
std::mt19937 mersenne{ std::random_device{}() };
std::uniform_real_distribution<GLfloat> urColor{ 0.0f,1.0f };

class CoordSystem {
private:
	static CoordSystem* pInst;
	friend class Shader;
	GLfloat vertex[4][3]{ 0.0f,1.0f,0.0f,0.0f,-1.0f,0.0f,-1.0f,0.0f,0.0f,1.0f,0.0f,0.0f };
	const GLfloat color[4][3]{ urColor(mersenne),urColor(mersenne) ,urColor(mersenne) ,
	urColor(mersenne) ,urColor(mersenne) ,urColor(mersenne) ,
	urColor(mersenne) ,urColor(mersenne) ,urColor(mersenne) ,
	urColor(mersenne) ,urColor(mersenne) ,urColor(mersenne) };
private:
	CoordSystem()
	{

	}
public:
	~CoordSystem()
	{
		delete pInst;
	}

	static CoordSystem* getInstance()
	{
		if (nullptr == pInst)
			pInst = new CoordSystem;

		return pInst;
	}


	void render() const
	{
		glDrawArrays(GL_LINES, 0, 4);
	}
};

class Triangle {
private:
	friend class Shader;
	static Triangle* pInst;
	// -0.75f,0.25f,0.0f,-0.25f,0.75f,0.0f
	GLfloat vertex[3][3]{ 0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f , 0.0f,0.0f,0.0f };
	const GLfloat color[3][3]{ urColor(mersenne),urColor(mersenne),urColor(mersenne),
		urColor(mersenne),urColor(mersenne),urColor(mersenne),
		urColor(mersenne), urColor(mersenne),urColor(mersenne) };
	bool sizeFlag{ false };
	GLfloat moveXAmount{ 0.01f };
	GLfloat moveYAmount{ -0.01f };
private:
	Triangle()
	{

	}
public:
	~Triangle()
	{
		delete pInst;
	}

	void setVertex(const GLfloat& x1, const GLfloat& y1, const GLfloat& z1,
		const GLfloat& x2, const GLfloat& y2, const GLfloat& z2,
		const GLfloat& x3, const GLfloat& y3, const GLfloat& z3)
	{
		vertex[0][0] = x1;
		vertex[0][1] = y1;
		vertex[0][2] = z1;
		vertex[1][0] = x2;
		vertex[1][1] = y2;
		vertex[1][2] = z2;
		vertex[2][0] = x3;
		vertex[2][1] = y3;
		vertex[2][2] = z3;
	}

	GLfloat& getVertex(const int& row, const int& col)
	{
		return vertex[row][col];
	}

	static Triangle* getInstance()
	{
		if (nullptr == pInst)
			pInst = new Triangle;

		return pInst;
	}

	bool& getSizeFlag()
	{
		return sizeFlag;
	}

	GLfloat& getXMoveAmount()
	{
		return moveXAmount;
	}

	GLfloat& getYMoveAmount()
	{
		return moveYAmount;
	}

	void render() const
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};

class Rect {
private:
	friend class Shader;
	static Rect* pInst;
	// 0.25f, 0.75f, 0.0f, 0.25f, 0.25f, 0.0f, 0.75f, 0.25f, 0.0f, 0.75f, 0.75f, 0.0f
	GLfloat vertex[4][3]{ 0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f , 0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f };
	const GLfloat color[4][3]{ urColor(mersenne),urColor(mersenne),urColor(mersenne),
		urColor(mersenne),urColor(mersenne),urColor(mersenne),
		urColor(mersenne),urColor(mersenne),urColor(mersenne),
		urColor(mersenne),urColor(mersenne),urColor(mersenne) };
	const GLuint index[6]{ 0,1,2,0,2,3 };
	bool sizeFlag{ false };
	GLfloat moveXAmount{ 0.01f };
private:
	Rect()
	{
		
	}
public:
	~Rect()
	{
		delete pInst;
	}

	void setVertex(const GLfloat& x1, const GLfloat& y1, const GLfloat& z1,
		const GLfloat& x2, const GLfloat& y2, const GLfloat& z2,
		const GLfloat& x3, const GLfloat& y3, const GLfloat& z3,
		const GLfloat& x4, const GLfloat& y4, const GLfloat& z4)
	{
		vertex[0][0] = x1;
		vertex[0][1] = y1;
		vertex[0][2] = z1;
		vertex[1][0] = x2;
		vertex[1][1] = y2;
		vertex[1][2] = z2;
		vertex[2][0] = x3;
		vertex[2][1] = y3;
		vertex[2][2] = z3;
		vertex[3][0] = x4;
		vertex[3][1] = y4;
		vertex[3][2] = z4;
	}

	static Rect* getInstance()
	{
		if (nullptr == pInst)
			pInst = new Rect;

		return pInst;
	}

	GLfloat& getVertex(const int& row, const int& col)
	{
		return vertex[row][col];
	}

	GLfloat& getXMoveAmount()
	{
		return moveXAmount;
	}


	bool& getSizeFlag()
	{
		return sizeFlag;
	}

	void render() const
	{
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	} 
};

class Pentagon {
private:
	friend class Shader;
	GLfloat vertex[6][3]{ 0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f , 0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f };
	const GLfloat color[6][3]{ urColor(mersenne) ,urColor(mersenne) ,urColor(mersenne) ,
	urColor(mersenne) ,urColor(mersenne) ,urColor(mersenne) ,
	urColor(mersenne) ,urColor(mersenne) ,urColor(mersenne) ,
	urColor(mersenne) ,urColor(mersenne) ,urColor(mersenne) ,
	urColor(mersenne) ,urColor(mersenne) ,urColor(mersenne) ,
	urColor(mersenne) ,urColor(mersenne) ,urColor(mersenne) };
	const GLuint index[15]{0,1,5,1,2,5,2,3,5,3,4,5,4,0,5 };
	bool sizeFlag{ false };
	GLfloat xMoveAmount{ 0.005f };
	GLfloat yMoveAmount{ 0.01f };
public:
	Pentagon()
	{

	}

	~Pentagon()
	{
	}

	void setVertex(const GLfloat& x1, const GLfloat& y1, const GLfloat& z1,
		const GLfloat& x2, const GLfloat& y2, const GLfloat& z2,
		const GLfloat& x3, const GLfloat& y3, const GLfloat& z3,
		const GLfloat& x4, const GLfloat& y4, const GLfloat& z4,
		const GLfloat& x5, const GLfloat& y5, const GLfloat& z5,
		const GLfloat& x6, const GLfloat& y6, const GLfloat& z6)
	{
		vertex[0][0] = x1;
		vertex[0][1] = y1;
		vertex[0][2] = z1;
		vertex[1][0] = x2;
		vertex[1][1] = y2;
		vertex[1][2] = z2;
		vertex[2][0] = x3;
		vertex[2][1] = y3;
		vertex[2][2] = z3;
		vertex[3][0] = x4;
		vertex[3][1] = y4;
		vertex[3][2] = z4;
		vertex[4][0] = x5;
		vertex[4][1] = y5;
		vertex[4][2] = z5;
		vertex[5][0] = x6;
		vertex[5][1] = y6;
		vertex[5][2] = z6;
	}

	GLfloat& getVertex(const int& row, const int& col)
	{
		return vertex[row][col];
	}
	
	GLfloat& getMoveAmount()
	{
		return xMoveAmount;
	}
	GLfloat& getYMoveAmount()
	{
		return yMoveAmount;
	}

	bool& getSizeFlag()
	{
		return sizeFlag;
	}

	void render() const
	{
		glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
	}
};
Pentagon* pPentagon[2];

class Shader {
private:
	friend class CoordSystem;
	friend class Triangle;
	friend class Rect;
	friend class Pentagon;
	enum { MaxVao = 5, MaxVbo = 10, MaxEbo = 3 };
private:
	static Shader* pInst;
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
	~Shader()
	{
		safeDeleteArray(vao);
		safeDeleteArray(vbo);
		safeDeleteArray(ebo);
		delete pInst;
	}
	static Shader* getInstance()
	{
		if (nullptr == pInst)
			pInst = new Shader;

		return pInst;
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle::getInstance()->vertex), Triangle::getInstance()->vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle::getInstance()->color), Triangle::getInstance()->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[2]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Rect::getInstance()->vertex), Rect::getInstance()->vertex, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Rect::getInstance()->index), Rect::getInstance()->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Rect::getInstance()->color), Rect::getInstance()->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[3]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[6]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pPentagon[0]->vertex), pPentagon[0]->vertex, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pPentagon[0]->index), pPentagon[0]->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[7]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pPentagon[0]->color), pPentagon[0]->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[4]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[8]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pPentagon[1]->vertex), pPentagon[1]->vertex, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[2]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pPentagon[1]->index), pPentagon[1]->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[9]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pPentagon[1]->color), pPentagon[1]->color, GL_STATIC_DRAW);
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

CoordSystem* CoordSystem::pInst = nullptr;
Triangle* Triangle::pInst = nullptr;
Rect* Rect::pInst = nullptr;
Shader* Shader::pInst = nullptr;
constexpr GLuint wWidth{ 800 };
constexpr GLuint wHeight{ 600 };

GLvoid RenderScene();
GLvoid Reshape(int, int);
GLvoid TimerFunc(int);

int main(int argc, char** argv)
{
	constexpr unsigned winXPos = 0;
	constexpr unsigned winYPos = 0;
	const char winName[]{ "Example" };
	pPentagon[0] = new Pentagon;
	pPentagon[1] = new Pentagon;
	Triangle::getInstance()->setVertex(-0.5f, 0.75f, 0.0f, -0.75f, 0.25f, 0.0f,(- 0.5f + -0.75f) / 2.0f + 0.01f, (0.75f + 0.25f) / 2.0f + 0.01f, 0.0f);
	Rect::getInstance()->setVertex(0.5f, 0.75f, 0.0f, 0.25f, 0.25f, 0.0f, 0.75f, 0.25f, 0.0f, 0.5f, 0.75f, 0.0f);
	pPentagon[0]->setVertex(-0.5f, -0.25f, 0.0f, -0.75f, -0.25f, 0.0f, -0.75f, -0.75f, 0.0f, -0.25f, -0.75f, 0.0f, -0.25f, -0.25f, 0.0f, -0.5f, -0.5f, 0.0f);
	pPentagon[1]->setVertex(0.5f,-0.25f,0.0f,0.35f,-0.5f,0.0f,0.375f,-0.75f,0.0f,0.625f,-0.75f,0.0f,0.65f,-0.5f,0.0f,0.5f,-0.5f,0.0f);
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
	glutTimerFunc(100, TimerFunc, 1);
	glutMainLoop();
}

GLvoid RenderScene()
{
	Shader::getInstance()->initBuffer();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glm::mat4 model = glm::mat4(1.0f);
	unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "model");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(Shader::getInstance()->getVao()[0]);
	CoordSystem::getInstance()->render();

	glBindVertexArray(Shader::getInstance()->getVao()[1]);
	Triangle::getInstance()->render();

	glBindVertexArray(Shader::getInstance()->getVao()[2]);
	Rect::getInstance()->render();

	glBindVertexArray(Shader::getInstance()->getVao()[3]);
	pPentagon[0]->render();
	
	glBindVertexArray(Shader::getInstance()->getVao()[4]);
	pPentagon[1]->render();
	
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid TimerFunc(int value)
{
	if ((Triangle::getInstance()->getVertex(2, 0) >= -0.25f) || (Triangle::getInstance()->getVertex(2, 1) <= 0.25f) || Triangle::getInstance()->getVertex(2, 0) <= -0.625f) {
		Triangle::getInstance()->getXMoveAmount() = -Triangle::getInstance()->getXMoveAmount();
		Triangle::getInstance()->getYMoveAmount() = -Triangle::getInstance()->getYMoveAmount();
	}
	Triangle::getInstance()->getVertex(2, 0) += Triangle::getInstance()->getXMoveAmount();
	Triangle::getInstance()->getVertex(2, 1) += Triangle::getInstance()->getYMoveAmount();

	if (Rect::getInstance()->getVertex(0, 0) < 0.25f || Rect::getInstance()->getVertex(0, 0) > 0.5f
		|| Rect::getInstance()->getVertex(3, 0) > 0.75f || Rect::getInstance()->getVertex(3,0) < 0.5f) {
		Rect::getInstance()->getXMoveAmount() = -Rect::getInstance()->getXMoveAmount();
	}
	Rect::getInstance()->getVertex(0, 0) -= Rect::getInstance()->getXMoveAmount();
	Rect::getInstance()->getVertex(3, 0) += Rect::getInstance()->getXMoveAmount();

	if((pPentagon[0]->getVertex(1,1) < -0.6f || pPentagon[0]->getVertex(1,1) >-0.25f) ||
		(pPentagon[0]->getVertex(4,1) < -0.6f || pPentagon[0]->getVertex(4,1) >-0.25f) ||
		(pPentagon[0]->getVertex(2,0) < -0.75f || pPentagon[0]->getVertex(2,0) > -0.6f) ||
		(pPentagon[0]->getVertex(3,0) > -0.25f || pPentagon[0] ->getVertex(3,0) < -0.4f)) {
		pPentagon[0]->getMoveAmount() = -pPentagon[0]->getMoveAmount();
		pPentagon[0]->getYMoveAmount() = -pPentagon[0]->getYMoveAmount();
	}
	pPentagon[0]->getVertex(1, 1) -= pPentagon[0]->getYMoveAmount();
	pPentagon[0]->getVertex(4, 1) -= pPentagon[0]->getYMoveAmount();
	pPentagon[0]->getVertex(2, 0) += pPentagon[0]->getMoveAmount();
	pPentagon[0]->getVertex(3, 0) -= pPentagon[0]->getMoveAmount();

	if ((pPentagon[1]->getVertex(2,0) >= 0.475 ) || (pPentagon[1]->getVertex(2,0) < 0.375f)) {
		pPentagon[1]->getMoveAmount() = -pPentagon[1]->getMoveAmount();
		pPentagon[1]->getYMoveAmount() = -pPentagon[1]->getYMoveAmount();
	}
	pPentagon[1]->getVertex(0, 1) -= (pPentagon[1]->getYMoveAmount());
	pPentagon[1]->getVertex(1, 0) += (pPentagon[1]->getMoveAmount());
	pPentagon[1]->getVertex(2, 0) += pPentagon[1]->getMoveAmount();
	pPentagon[1]->getVertex(2, 1) += pPentagon[1]->getYMoveAmount();
	pPentagon[1]->getVertex(3, 0) -= pPentagon[1]->getMoveAmount();
	pPentagon[1]->getVertex(3, 1) += pPentagon[1]->getYMoveAmount();
	pPentagon[1]->getVertex(4, 0) -= (pPentagon[1]->getMoveAmount());
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}