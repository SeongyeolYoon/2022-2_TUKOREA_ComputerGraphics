#include "pch.h"

class Shader;
std::mt19937 mersenne{ std::random_device{}() };
std::uniform_real_distribution<GLfloat> urColor{ 0.0f,1.0f };

class Rect {
private:
	friend class Shader;
	GLfloat vertex[4][3]{ -0.5f,0.5f,0.0f, -0.5f,-0.5f,0.0f , 0.5f,-0.5f,0.0f, 0.5f,0.5f,0.0f };
	GLfloat color[4][3]{ urColor(mersenne),urColor(mersenne),urColor(mersenne),
		urColor(mersenne),urColor(mersenne),urColor(mersenne),
		urColor(mersenne),urColor(mersenne),urColor(mersenne),
		urColor(mersenne),urColor(mersenne),urColor(mersenne) };
public:
	Rect()
	{

	}

	GLfloat& getVertex(const int& x, const int& y) 
	{
		return vertex[x][y];
	}

	void render()
	{
		glDrawArrays(GL_LINE_LOOP, 0, 4);
	}
};

Rect* pRect;

class Shader {
private:
	friend class Rect;
	enum { MaxVao = 1, MaxVbo = 2, MaxEbo = 1 };
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
		ebo = new GLuint[MaxEbo];
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(pRect->vertex), pRect->vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pRect->color), pRect->color, GL_STATIC_DRAW);
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

Shader* pShader;

constexpr GLuint wWidth{ 800 };
constexpr GLuint wHeight{ 600 };

GLfloat my;
GLfloat mx;
GLfloat offX[4], offY[4];
bool isClickLeftButton{ false };
GLvoid RenderScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
void Motion(int, int);
void ConvertDeviceXYOpenGLXY(int, int, GLfloat*, GLfloat*);

int main(int argc, char** argv)
{
	pShader = new Shader;
	pRect = new Rect;

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
	glutMotionFunc(Motion);
	glutMainLoop();
}

GLvoid RenderScene()
{
	pShader->initBuffer();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 model = glm::mat4(1.0f);
	unsigned int transformLocation = glGetUniformLocation(pShader->getShaderProgram(), "model");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(model));
	glBindVertexArray(pShader->getVao()[0]);
	glLineWidth(5.0f);
	pRect->render();
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	ConvertDeviceXYOpenGLXY(x, y, &mx, &my);

	if (GLUT_LEFT_BUTTON == button && GLUT_DOWN == state) {
		isClickLeftButton = true;
		if (pRect->getVertex(0,0)<= mx && mx <= pRect->getVertex(2, 0)
			&& my <= pRect->getVertex(0, 1) && my >= pRect->getVertex(2, 1)) {
			for (int i = 0; i < 4; ++i) {
				offX[i] = mx - pRect->getVertex(i,0);
				offY[i] = my - pRect->getVertex(i,1);
			}
		}
	}
	//glutPostRedisplay();
}

void ConvertDeviceXYOpenGLXY(int x, int y, GLfloat* pMx, GLfloat* pMy)
{
	int w = wWidth;
	int h = wHeight;

	*pMx = GLfloat((x - GLfloat(w) / 2.0) * GLfloat((1.0 / GLfloat(w / 2.0))));
	*pMy = -GLfloat((y - GLfloat(h) / 2.0) * GLfloat((1.0 / GLfloat(h / 2.0))));
}

void Motion(int x, int y)
{
	ConvertDeviceXYOpenGLXY(x, y, &mx, &my);

	for (int i = 0; i < 4; ++i) {
		if ((pRect->getVertex(0,0) <= mx) && (pRect->getVertex(1,0)<= mx) && (mx <= pRect->getVertex(2,0)) && (mx <= pRect->getVertex(3,0))
			&& (pRect->getVertex(0,1) >= my) && (pRect->getVertex(3,1) >= my) && (my >= pRect->getVertex(1,1)) && (my >= pRect->getVertex(2,1))) {
			if (isClickLeftButton) {
				pRect->getVertex(i,0) = mx - offX[i];
				pRect->getVertex(i,1) = my - offY[i];
			}
		}
		else if (mx <= pRect->getVertex(0, 0) && my >= pRect->getVertex(0, 1)) {
			if (isClickLeftButton) {
				pRect->getVertex(0, 0) = mx;
				pRect->getVertex(0, 1) = my;
			}
		}
		else if (mx <= pRect->getVertex(1, 0) && my <= pRect->getVertex(1, 1)) {
			if (isClickLeftButton) {
				pRect->getVertex(1, 0) = mx;
				pRect->getVertex(1, 1) = my;
			}
		}
		else if (mx >= pRect->getVertex(2, 0) && my <= pRect->getVertex(2, 1)) {
			if (isClickLeftButton) {
				pRect->getVertex(2, 0) = mx;
				pRect->getVertex(2, 1) = my;
			}
		}
		else if (mx >= pRect->getVertex(3,0) && my >= pRect->getVertex(3, 1)){
			if (isClickLeftButton) {
				pRect->getVertex(3, 0) = mx;
				pRect->getVertex(3, 1) = my;
			}
		}
	}
	glutPostRedisplay();
}