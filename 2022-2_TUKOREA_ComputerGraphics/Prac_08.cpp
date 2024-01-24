#include "pch.h"

std::mt19937 mersenne{ std::random_device{}() };
std::uniform_real_distribution<GLfloat> urColor{ 0.0f,1.0f };
GLfloat r;
GLfloat g;
GLfloat b;
class Shader;

class Rect {
private:
	friend class Shader;
	GLfloat vertex[4][3]{ 0.0f };
	GLfloat color[4][3]{ 0.0f };
public:
	Rect()
	{

	}

	void setVertex(const GLfloat&ltx, const GLfloat& lty, const GLfloat& ltz, const GLfloat& lbx, const GLfloat& lby, const GLfloat& lbz, 
		const GLfloat& rbx, const GLfloat& rby, const GLfloat& rbz, const GLfloat& rtx, const GLfloat& rty, const GLfloat& rtz)
	{
		vertex[0][0] = ltx;
		vertex[0][1] = lty;
		vertex[0][2] = ltz;
		vertex[1][0] = lbx;
		vertex[1][1] = lby;
		vertex[1][2] = lbz;
		vertex[2][0] = rbx;
		vertex[2][1] = rby;
		vertex[2][2] = rbz;
		vertex[3][0] = rtx;
		vertex[3][1] = rty;
		vertex[3][2] = rtz;
	}

	void setColor(const GLfloat& ltx, const GLfloat& lty, const GLfloat& ltz, const GLfloat& lbx, const GLfloat& lby, const GLfloat& lbz,
		const GLfloat& rbx, const GLfloat& rby, const GLfloat& rbz, const GLfloat& rtx, const GLfloat& rty, const GLfloat& rtz)
	{
		color[0][0] = ltx;
		color[0][1] = lty;
		color[0][2] = ltz;
		color[1][0] = lbx;
		color[1][1] = lby;
		color[1][2] = lbz;
		color[2][0] = rbx;
		color[2][1] = rby;
		color[2][2] = rbz;
		color[3][0] = rtx;
		color[3][1] = rty;
		color[3][2] = rtz;
	}

	void render() const
	{
		glDrawArrays(GL_LINE_LOOP, 0, 4);
	}
};

class InnerTriangleUp {
private:
	friend class Shader;
	GLfloat vertex[3][3]{ 0.0f };
	GLfloat color[3][3]{ 0.0f };
	GLfloat xMoveAmount{ 0.03f };
	static bool timer;
public:
	InnerTriangleUp()
	{

	}

	void setVertex(const GLfloat& tx, const GLfloat& ty, const GLfloat& tz, const GLfloat& lbx, const GLfloat& lby, const GLfloat& lbz,
		const GLfloat& rbx, const GLfloat& rby, const GLfloat& rbz)
	{
		vertex[0][0] = tx;
		vertex[0][1] = ty;
		vertex[0][2] = tz;
		vertex[1][0] = lbx;
		vertex[1][1] = lby;
		vertex[1][2] = lbz;
		vertex[2][0] = rbx;
		vertex[2][1] = rby;
		vertex[2][2] = rbz;
	}
	
	void setColor(const GLfloat& vx1, const GLfloat& vy1, const GLfloat& vz1, const GLfloat& vx2, const GLfloat& vy2, const GLfloat& vz2,
		const GLfloat& vx3, const GLfloat& vy3, const GLfloat& vz3)
	{
		color[0][0] = vx1;
		color[0][1] = vy1;
		color[0][2] = vz1;
		color[1][0] = vx2;
		color[1][1] = vy2;
		color[1][2] = vz2;
		color[2][0] = vx3;
		color[2][1] = vy3;
		color[2][2] = vz3;
	}


	static bool& getTimer()
	{
		return timer;
	}

	void move()
	{
		for (int i = 0; i < 3; ++i) {
			vertex[i][0] += xMoveAmount;
		}
		
		for( int i =0; i <3; ++i){
			if (vertex[i][0] <= -0.5f || vertex[i][0] >= 0.5f) {
				xMoveAmount = -xMoveAmount;
				for (int j = 0; j < 3; ++j) {
					for (int k = 0; k < 3; ++k) {
						if (0 == k) {
							color[j][k] = r;
						}
						else if (1 == k) {
							color[j][k] = g;
						}
						else if (2 == k) {
							color[j][k] = b;
						}
					}
				}
			}
		}
	}

	void render() const
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};

class InnerTriangleDown {
private:
	friend class Shader;
	GLfloat vertex[3][3]{ 0.0f };
	GLfloat color[3][3]{ 0.0f };
	GLfloat xMoveAmount{ 0.03f };
	static bool timer;
public:
	InnerTriangleDown()
	{

	}

	void setVertex(const GLfloat& tx, const GLfloat& ty, const GLfloat& tz, const GLfloat& lbx, const GLfloat& lby, const GLfloat& lbz,
		const GLfloat& rbx, const GLfloat& rby, const GLfloat& rbz)
	{
		vertex[0][0] = tx;
		vertex[0][1] = ty;
		vertex[0][2] = tz;
		vertex[1][0] = lbx;
		vertex[1][1] = lby;
		vertex[1][2] = lbz;
		vertex[2][0] = rbx;
		vertex[2][1] = rby;
		vertex[2][2] = rbz;
	}

	void setColor(const GLfloat& vx1, const GLfloat& vy1, const GLfloat& vz1, const GLfloat& vx2, const GLfloat& vy2, const GLfloat& vz2,
		const GLfloat& vx3, const GLfloat& vy3, const GLfloat& vz3)
	{
		color[0][0] = vx1;
		color[0][1] = vy1;
		color[0][2] = vz1;
		color[1][0] = vx2;
		color[1][1] = vy2;
		color[1][2] = vz2;
		color[2][0] = vx3;
		color[2][1] = vy3;
		color[2][2] = vz3;
	}

	static bool& getTimer()
	{
		return timer;
	}

	decltype(auto) getVertex(const int& index)
	{
		return vertex[index];
	}

	void move()
	{
		for (int i = 0; i < 3; ++i) {
			vertex[i][0] -= xMoveAmount;
		}

		for (int i = 0; i < 3; ++i) {
			if (vertex[i][0] <= -0.5f || vertex[i][0] >= 0.5f) {
				xMoveAmount = -xMoveAmount;
				for (int j = 0; j < 3; ++j) {
					for (int k = 0; k < 3; ++k) {
						if (0 == k) {
							color[j][k] = r;
						}
						else if (1 == k) {
							color[j][k] = g;
						}
						else if (2 == k) {
							color[j][k] = b;
						}
					}
				}
			}
		}
	}

	void render() const
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};

class Triangle {
private:
	friend class Shader;
	GLfloat vertex[3][3]{ 0.0f };
	GLfloat color[3][3]{ 0.0f };
	GLfloat degree{ 0.0f };
	GLfloat xMoveAmount{ 0.03f };
	GLfloat yMoveAmount{ 0.03f };
	bool flag{ false };
	static bool timer;
public:
	Triangle()
	{

	}
	void setVertex(const GLfloat& tx, const GLfloat& ty, const GLfloat& tz, const GLfloat& lbx, const GLfloat& lby, const GLfloat& lbz,
		const GLfloat& rbx, const GLfloat& rby, const GLfloat& rbz)
	{
		vertex[0][0] = tx;
		vertex[0][1] = ty;
		vertex[0][2] = tz;
		vertex[1][0] = lbx;
		vertex[1][1] = lby;
		vertex[1][2] = lbz;
		vertex[2][0] = rbx;
		vertex[2][1] = rby;
		vertex[2][2] = rbz;
	}

	void setColor(const GLfloat& vx1, const GLfloat& vy1, const GLfloat& vz1, const GLfloat& vx2, const GLfloat& vy2, const GLfloat& vz2,
		const GLfloat& vx3, const GLfloat& vy3, const GLfloat& vz3)
	{
		color[0][0] = vx1;
		color[0][1] = vy1;
		color[0][2] = vz1;
		color[1][0] = vx2;
		color[1][1] = vy2;
		color[1][2] = vz2;
		color[2][0] = vx3;
		color[2][1] = vy3;
		color[2][2] = vz3;
	}

	void setXMoveAmount(const GLfloat& amount)
	{
		xMoveAmount = amount;
	}

	void setYMoveAmount(const GLfloat& amount)
	{
		yMoveAmount = amount;
	}

	static bool& getTimer()
	{
		return timer;
	}

	GLfloat& getDegree()
	{
		return degree;
	}

	decltype(auto) getColor(const int& i)
	{
		return color[i];
	}

	decltype(auto) getVertex(const int& i)
	{
		return vertex[i];
	}

	const GLfloat& getDegree() const
	{
		return degree;
	}

	const GLfloat& getXMoveAmount() const
	{
		return xMoveAmount;
	}

	const GLfloat& getYMoveAmount() const
	{
		return yMoveAmount;
	}

	void render() const
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void move()
	{
		// move
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (0 == j)
					vertex[i][j] += xMoveAmount;
				else if (1 == j)
					vertex[i][j] += yMoveAmount;
			}
		}

		// 좌우 충돌
		for (int i = 0; i < 3; ++i) {
			if (vertex[i][0] <= -1.0f) {
				xMoveAmount = -xMoveAmount;
				degree = 270.0f;
				flag = false;
			}
			if (vertex[i][0] >= 1.0f) {
				xMoveAmount = -xMoveAmount;
				degree = 90.0f;
				flag = false;
			}
			if (!flag) {
				if (vertex[i][0] == -0.5f && -0.5f <= vertex[i][1] && vertex[i][1] <= 0.5f) {
					xMoveAmount = -xMoveAmount;
					degree = 90.0f;
					flag = true;
				}

				if (vertex[i][0] == 0.5f && -0.5f <= vertex[i][1] && vertex[i][1] <= 0.5f) {
					xMoveAmount = -xMoveAmount;
					degree = 270.0f;
					flag = true;
				}
			}
		}

		// 상하 충돌
		for (int i = 0; i < 3; ++i) {
			if (vertex[i][1] <= -1.0f) {
				yMoveAmount = -yMoveAmount;
				degree = 0.0f;
				flag = false;
			}
			if (vertex[i][1] >= 1.0f) {
				yMoveAmount = -yMoveAmount;
				degree = 180.0f;
				flag = false;
			}

			if (!flag) {
				if (vertex[i][1] == -0.5f && -0.5f <= vertex[i][0] && vertex[i][0] <= 0.5f) {
					yMoveAmount = -yMoveAmount;
					degree = 180.0f;
					flag = true;
				}

				if (vertex[i][1] == 0.5f && -0.5f <= vertex[i][0] && vertex[i][0] <= 0.5f) {
					yMoveAmount = -yMoveAmount;
					degree = 0.0f;
					flag = true;
				}
			}
		}
	}		
};

Triangle* triangles[6];
Rect* pRectangle;
InnerTriangleUp* pInTriangleUp;
InnerTriangleDown* pInTriangleDown;

bool InnerTriangleUp::timer{ false };
bool InnerTriangleDown::timer{ false };
bool Triangle::timer{ false };

class Shader {
private:
	friend class Triangle;
	friend class Rect;
	friend class InnerTriangleUp;
	friend class InnerTriangleDown;
	// *******************************
	enum { maxVao = 7, maxVbo = 14, maxEbo = 1 };
	// *******************************
public:
	GLuint* vao, * vbo, * ebo;
	GLchar* vertexSource, * fragmentSource;
	GLchar vertexShader, fragmentShader;
	GLuint shaderProgram;
public:
	Shader()
	{
		vao = new GLuint[maxVao];
		vbo = new GLuint[maxVbo];
		ebo = new GLuint[maxEbo];
	}

	~Shader()
	{
		safeDeleteArray(vao);
		safeDeleteArray(vbo);
		safeDeleteArray(ebo);
		safeDeleteArray(vertexSource);
		safeDeleteArray(fragmentSource);
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
		glGenVertexArrays(maxVao, vao);
		glGenBuffers(maxVbo, vbo);
		glGenBuffers(maxEbo, ebo);
	}

	// ***************************************************************************************************
	void initBuffer()
	{
		glBindVertexArray(vao[0]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[0]->vertex), triangles[0]->vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[0]->color), triangles[0]->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[1]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[1]->vertex), triangles[1]->vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[1]->color), triangles[1]->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[2]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[2]->vertex), triangles[2]->vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[2]->color), triangles[2]->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[3]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[6]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[3]->vertex), triangles[3]->vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[7]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[3]->color), triangles[3]->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[4]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[8]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pRectangle->vertex), pRectangle->vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[9]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pRectangle->color), pRectangle->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[5]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[10]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pInTriangleUp->vertex), pInTriangleUp->vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[11]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pInTriangleUp->color), pInTriangleUp->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[6]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[12]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pInTriangleDown->vertex), pInTriangleDown->vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[13]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pInTriangleDown->color), pInTriangleDown->color, GL_STATIC_DRAW);
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
	void safeDeleteArray(T* pUint)
	{
		if (pUint) {
			delete[] pUint;
			pUint = nullptr;
		}
	}
};

Shader shader;

bool leftButton{ false };
bool g_isLine{ false };

constexpr unsigned wWidth = 800;
constexpr unsigned wHeight = 600;

constexpr float PI = 3.141592f;
constexpr float deg2Rad = PI / 180.0f;

GLvoid RenderScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid TimerFunc(int);
void ConvertDeviceXYOpenGLXY(int, int, GLfloat*, GLfloat*);

int main(int argc, char** argv)
{
	GLfloat tempColor;
	tempColor = urColor(mersenne);
	pRectangle = new Rect();
	pRectangle->setVertex(-0.5f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f);
	pRectangle->setColor(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,0.0f,0.0f,1.0f);

	triangles[0] = new Triangle();
	triangles[0]->setVertex(-0.9f,0.9f,0.0f,-0.95f,0.75f,0.0f,-0.85f,0.75f,0.0f);
	triangles[0]->setColor(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	triangles[0]->setXMoveAmount(0.1f);
	triangles[0]->setXMoveAmount(0.1f);

	triangles[1] = new Triangle();
	triangles[1]->setVertex(0.8f, 0.9f, 0.0f, 0.75f, 0.75f, 0.0f, 0.85f, 0.75f, 0.0f);
	triangles[1]->setColor(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	triangles[1]->setXMoveAmount(0.1f);
	triangles[1]->setXMoveAmount(0.1f);

	triangles[2] = new Triangle();
	triangles[2]->setVertex(-0.9f, -0.75f, 0.0f, -0.95f, -0.95f, 0.0f, -0.85f, -0.95f, 0.0f);
	triangles[2]->setColor(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	triangles[2]->setXMoveAmount(0.1f);
	triangles[2]->setXMoveAmount(0.1f);

	triangles[3] = new Triangle();
	triangles[3]->setVertex(0.8f, -0.75f, 0.0f, 0.75f, -0.9f, 0.0f, 0.85f, -0.9f, 0.0f);
	triangles[3]->setColor(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	triangles[3]->setXMoveAmount(0.1f);
	triangles[3]->setXMoveAmount(0.1f);

	pInTriangleUp = new InnerTriangleUp();
	pInTriangleUp->setVertex(-0.4f,-0.25f,0.0f,-0.5,-0.5f,0.0f,-0.3f,-0.5f,0.0f);
	pInTriangleUp->setColor(tempColor, 0.0f, 0.0f, tempColor, 0.0f, 0.0f, tempColor, 0.0f, 0.0f);

	pInTriangleDown = new InnerTriangleDown();
	pInTriangleDown->setVertex(0.4f,0.6f,0.0f,0.3f,0.35f,0.0f,0.5f,0.35f,0.0f);
	pInTriangleDown->setColor(tempColor, 0.0f, 0.0f, tempColor, 0.0f, 0.0f, tempColor, 0.0f, 0.0f);

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

	shader.glGenerate();
	shader.initBuffer();
	shader.initShader();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunc, 1);
	glutMainLoop();
}

GLvoid RenderScene()
{
	shader.initBuffer();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (g_isLine) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(5.0f);
	}

	// Render Rect
	{
		glm::mat4 model = glm::mat4(1.0f);
		unsigned int transformLocation = glGetUniformLocation(shader.shaderProgram, "model");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(shader.vao[4]);
		pRectangle->render();
	}

	// Render pInTriUp
	{
		glm::mat4 model = glm::mat4(1.0f);
		unsigned int transformLocation = glGetUniformLocation(shader.shaderProgram, "model");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(shader.vao[5]);
		pInTriangleUp->render();
	}

	// Render pInTriDown
	{
		GLfloat cx = (pInTriangleDown->getVertex(0)[0] + pInTriangleDown->getVertex(1)[0] + pInTriangleDown->getVertex(2)[0]) / 3.0f;
		GLfloat cy = (pInTriangleDown->getVertex(0)[1] + pInTriangleDown->getVertex(1)[1] + pInTriangleDown->getVertex(2)[1]) / 3.0f;
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 trans1 = glm::mat4(1.0f);
		glm::mat4 trans2 = glm::mat4(1.0f);
		glm::mat4 rotate = glm::mat4(1.0f);
		trans1 = glm::translate(trans1, glm::vec3(-cx, -cy, 0.0f));
		trans2 = glm::translate(trans2, glm::vec3(+cx, +cy, 0.0f));
		rotate = glm::rotate(rotate, 180 * deg2Rad, glm::vec3(0.0f, 0.0f, 1.0f));
		model =  trans2 *  rotate * trans1;
		unsigned int transformLocation = glGetUniformLocation(shader.shaderProgram, "model");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(shader.vao[6]);
		pInTriangleDown->render();
	}

	// Render Tri
	for (int i = 0; i < 4; ++i) {
		GLfloat cx = (triangles[i]->getVertex(0)[0] + triangles[i]->getVertex(1)[0] + triangles[i]->getVertex(2)[0]) / 3.0f;
		GLfloat cy = (triangles[i]->getVertex(0)[1] + triangles[i]->getVertex(1)[1] + triangles[i]->getVertex(2)[1]) / 3.0f;
		glm::mat4 rotate = glm::mat4(1.0f);
		glm::mat4 trans1 = glm::mat4(1.0f);
		glm::mat4 trans2 = glm::mat4(1.0f);
		glm::mat4 model = glm::mat4(1.0f);
		trans1 = glm::translate(trans1, glm::vec3(-cx, -cy, 0.0f));
		trans2 = glm::translate(trans2, glm::vec3(+cx, +cy, 0.0f));
		rotate = glm::rotate(rotate, triangles[i]->getDegree() * deg2Rad, glm::vec3(0.0f, 0.0f, 1.0f));
		model = trans2 * rotate * trans1;
		unsigned int transformLocation = glGetUniformLocation(shader.shaderProgram, "model");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(shader.vao[i]);
		triangles[i]->render();
	}

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	GLfloat mx{ 0.0f };
	GLfloat my{ 0.0f };
	ConvertDeviceXYOpenGLXY(x, y, &mx, &my);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		g_isLine = true;
		break;
	case 'b':
		g_isLine = false;
		break;
	case 'o':
		Triangle::getTimer() = !Triangle::getTimer();
		break;
	case 'i':
		pInTriangleUp->getTimer() = !pInTriangleUp->getTimer();
		pInTriangleDown->getTimer() = !pInTriangleDown->getTimer();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void ConvertDeviceXYOpenGLXY(int x, int y, GLfloat* pMx, GLfloat* pMy)
{
	int w = wWidth;
	int h = wHeight;

	*pMx = GLfloat((x - GLfloat(w) / 2.0) * GLfloat((1.0 / GLfloat(w / 2.0))));
	*pMy = -GLfloat((y - GLfloat(h) / 2.0) * GLfloat((1.0 / GLfloat(h / 2.0))));
}

void TimerFunc(int value)
{
	r = urColor(mersenne);
	g = urColor(mersenne);
	b = urColor(mersenne);
	if (Triangle::getTimer()) {
		for (int i = 0; i < 4; ++i) {
			triangles[i]->move();
		}
	}

	if(pInTriangleUp->getTimer())
		pInTriangleUp->move();
	if(pInTriangleDown->getTimer())
		pInTriangleDown->move();

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}