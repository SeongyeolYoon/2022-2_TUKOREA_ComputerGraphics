#include "pch.h"
#include <cmath>
#include <cstdlib>
class Shader;

struct BGColor {
	GLfloat r{0.0f}, g{0.0f}, b{0.0f}, a{1.0f};
};

class Point {
private:
	friend class Shader;
	GLfloat vertex[3]{ 0.0f,0.0f,0.0f };
	GLfloat color[3]{ 0.0f,0.0f,0.0f };
	GLint degree{ 0 };
	GLfloat radian{ 0 };
	bool isRender{ false };
	static int count;
	static const int nCircle = 2900;
public:
	Point()
	{

	}

	void setVertex(const float& x, const float& y, const float& z)
	{
		vertex[0] = x;
		vertex[1] = y;
		vertex[2] = z;
	}

	void setColor(const float& x, const float& y, const float& z)
	{
		color[0] = x;
		color[1] = y;
		color[2] = z;
	}
	
	void setRadian(const float& r)
	{
		radian = r;
	}

	void setDegree(const int& degreeIn)
	{
		degree = degreeIn;
	}


	const int& getDegree() const 
	{
		return degree;
	}

	const float& getRadian() const
	{
		return radian;
	}

	static int& getCount() 
	{
		return count;
	}

	static const int& getNCircle()
	{
		return nCircle;
	}

	const bool& checkRender() const
	{
		return isRender;
	}

	void render()
	{
		glDrawArrays(GL_POINTS, 0, 1);
	}
};

Point* pCircle[2900];
int Point::count = 0;

GLfloat my{ 0.0f };
GLfloat mx{ 0.0f };

std::mt19937 mersenne{ std::random_device{}() };
std::uniform_real_distribution<GLfloat> urd{ 0.0f,1.0f };

class Shader {
private:
	friend class Point;
	enum { MaxVao = 2900, MaxVbo = 5800};
private:
	GLuint* vao, * vbo, * ebo;
	GLchar* vertexSource, * fragmentSource;
	GLchar vertexShader, fragmentShader;
	GLuint shaderProgram;
public:
	Shader()
	{
		vao = new GLuint[MaxVao];
		vbo = new GLuint[MaxVbo];
	}

	~Shader()
	{
		safeDeleteArray(vao);
		safeDeleteArray(vbo);
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
	}
	// ***************************************************************************************************
	void initBuffer()
	{
		for (int i = 0; i < 2900; ++i) {
			glBindVertexArray(vao[i]);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[i*2]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(pCircle[i]->vertex), pCircle[i]->vertex, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[i*2 + 1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(pCircle[i]->color), pCircle[i]->color, GL_STATIC_DRAW);
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

Shader* pShader;

const GLint wWidth{ 800 };
const GLint wHeight{ 600 };
BGColor bgColor;

constexpr float PI = 3.141592f;
constexpr float deg2Rad = PI / 180.0f;
int degree{ };
bool g_onTimer{ false };

GLvoid RenderScene();
GLvoid Mouse(int, int,int,int);
GLvoid Reshape(int,int);
void TimerFunc(int);

void ConvertDeviceXYOpenGLXY(int , int , GLfloat*, GLfloat*);
int main(int argc, char** argv)
{
	pShader = new Shader;
	int degree{ };
	float radian{ };

	for (int i = 0; i < Point::getNCircle(); ++i) {
		pCircle[i] = new Point;
		if (i <= 1440) {
			degree++;
			radian += 0.0001f;
		}
		if (i >= 1441) {
			degree--;
			radian -= 0.0001f;
		}
		pCircle[i]->setDegree(degree);
		pCircle[i]->setRadian(radian);
		pCircle[i]->setVertex(0.0f,0.0f,0.0f);
		pCircle[i]->setColor(1.0f, 0.0f, 0.0f);
	}

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

	pShader->glGenerate();
	pShader->initBuffer();
	pShader->initShader();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutTimerFunc(1, TimerFunc, 1);
	glutMainLoop();
}

GLvoid RenderScene()
{
	pShader->initBuffer();

	glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2.0f);

	if (g_onTimer) {
		for (int i{}; i < Point::getCount(); ++i) {
			glm::mat4 model = glm::mat4(1.0f);
			if(i < 1440)
			model = glm::translate(model, glm::vec3(mx + pCircle[i]->getRadian() * (cosf(pCircle[i]->getDegree() * deg2Rad)), my + pCircle[i]->getRadian() * sinf(pCircle[i]->getDegree() * deg2Rad), 0.0f));
			else
				model = glm::translate(model, glm::vec3(mx + 0.29 + pCircle[i]->getRadian() * (-cosf(pCircle[i]->getDegree() * deg2Rad)), my + pCircle[i]->getRadian() * sinf(-pCircle[i]->getDegree() * deg2Rad), 0.0f));

			unsigned int transformLocation = glGetUniformLocation(pShader->getShaderProgram(), "model");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(pShader->getVao()[i]);
			pCircle[i]->render();
		}
	}
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void TimerFunc(int value)
{
	glutPostRedisplay();

	if (g_onTimer) {
		if(Point::getCount() < 2898)
			Point::getCount()++;
		std::cout << "radian: " << pCircle[Point::getCount()]->getRadian() << std::endl;
		std::cout << "count: " << Point::getCount() << std::endl;
		std::cout << "degree: " << pCircle[Point::getCount()]->getDegree() << std::endl;
	}
	glutTimerFunc(1, TimerFunc, 1);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	ConvertDeviceXYOpenGLXY(x, y, &mx, &my);

	if (GLUT_LEFT_BUTTON == button && GLUT_DOWN == state) {
		g_onTimer = true;
		Point::getCount() = 0;
		bgColor.r = urd(mersenne);
		bgColor.g = urd(mersenne);
		bgColor.b = urd(mersenne);
	}

}

void ConvertDeviceXYOpenGLXY(int x, int y, GLfloat* pMx, GLfloat* pMy)
{
	int w = wWidth;
	int h = wHeight;

	*pMx = GLfloat((x - GLfloat(w) / 2.0) * GLfloat((1.0 / GLfloat(w / 2.0))));
	*pMy = -GLfloat((y - GLfloat(h) / 2.0) * GLfloat((1.0 / GLfloat(h / 2.0))));
}
