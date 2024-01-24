#include <iostream>
#include <cstdlib>
#include <random>
#include <gl\glew.h>
#include <gl\freeglut.h>
#include <gl\freeglut_ext.h>

struct Color {
	GLfloat r, g, b;
};

struct Position2D {
	GLfloat left, bottom, right, top;
};

class Rect {
private:
	Position2D pos;
	Position2D tempPos;
	Color color;
public:
	static int nRect;
public:
	Rect(const Position2D& pos_in = Position2D{ 0.0f,0.0f,0.0f,0.0f }, const Color& color_in = Color{ 0.0f,0.0f,0.0f })
		: pos{ pos_in }, color{ color_in }
	{

	}

	const Position2D& getTempPos()
	{
		return tempPos;
	}

	const Position2D& getPos()
	{
		return pos;
	}

	void setPos(const Position2D& pos_in)
	{
		pos = pos_in;
	}
	void render() const
	{
		glColor3f(color.r, color.g, color.b);
		glRectf(pos.left, pos.bottom, pos.right, pos.top);
	}

	bool isInRect(const GLfloat& mx, const GLfloat& my)
	{
		return ((pos.left < mx&& mx < pos.right) && (pos.bottom < my&& my < pos.top)) ? true : false;
	}
};

constexpr unsigned int winWidth{ 800 };
constexpr unsigned int winHeight{ 600 };
bool g_isClick{ false };
int Rect::nRect = 50;
Rect* pRect[20];
Rect* eraser;

GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Motion(int x, int y);
GLvoid TimerFunc(int);
GLvoid Keyboard(unsigned char, int, int);
void ConvertDeviceXYOpenGLXY(const int&, const int&, GLfloat*, GLfloat*);

void CreateRect();
int main(int argc, char** argv)
{
	constexpr unsigned int winPosX{ 0 };
	constexpr unsigned int winPosY{ 0 };
	CreateRect();
	std::mt19937 mersenne{ std::random_device{}() };
	std::uniform_real_distribution<GLfloat> uiColor{ 0.0f,1.0f };
	std::uniform_real_distribution<GLfloat> uiPos{ -1.0f,1.0f };

	eraser = new Rect{ Position2D(-0.15f,-0.15f,0.15f,0.15f),Color{ uiColor(mersenne), uiColor(mersenne), uiColor(mersenne)} };

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(winPosX, winPosY);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Prac_04");

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		std::cerr << "Unalbe to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}


GLvoid DrawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < Rect::nRect; ++i) {
		pRect[i]->render();
	}

	if (g_isClick)
		eraser->render();

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

	if (GLUT_LEFT_BUTTON == button && GLUT_DOWN == state) {
		g_isClick = true;
	}
	else
		g_isClick = false;
}

GLvoid Motion(int x, int y)
{
	GLfloat mx{ 0.0f };
	GLfloat my{ 0.0f };
	ConvertDeviceXYOpenGLXY(x, y, &mx, &my);

	if (g_isClick) {
		eraser->setPos(Position2D(mx - 0.15f, my - 0.15f, mx + 0.15f, my + 0.15f));
		if (eraser->isInRect(mx, my)) {
			eraser->setPos(Position2D(mx - 0.15f, my - 0.15f, mx + 0.15f, my + 0.15f));
		}
	}

	for (int i = 0; i < Rect::nRect; ++i) {
		if ((eraser->getPos().left < pRect[i]->getPos().left) && (eraser->getPos().right > pRect[i]->getPos().right)
			&& (eraser->getPos().top > pRect[i]->getPos().top) && (eraser->getPos().bottom < pRect[i]->getPos().bottom)) {
			pRect[i]->setPos(Position2D(0.0f, 0.0f, 0.0f, 0.0f));
		}
	}
	glutPostRedisplay();
}

void ConvertDeviceXYOpenGLXY(const int& x, const int& y, GLfloat* pMx, GLfloat* pMy)
{
	int w = winWidth;
	int h = winHeight;

	*pMx = GLfloat((x - GLfloat(w) / 2.0) * GLfloat((1.0 / GLfloat(w / 2.0))));
	*pMy = -GLfloat((y - GLfloat(h) / 2.0) * GLfloat((1.0 / GLfloat(h / 2.0))));
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
		for (int i = 0; i < Rect::nRect; ++i) {
			delete pRect[i];
		}
		CreateRect();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void CreateRect()
{
	std::mt19937 mersenne{ std::random_device{}() };
	std::uniform_real_distribution<GLfloat> uiColor{ 0.0f,1.0f };
	std::uniform_real_distribution<GLfloat> uiPos{ -1.0f,1.0f };
	GLfloat left;
	GLfloat bottom;
	for (int i = 0; i < Rect::nRect; ++i) {
		left = uiPos(mersenne);
		bottom = uiPos(mersenne);
		pRect[i] = new Rect{ Position2D(left, bottom, left + 0.05f, bottom + 0.05f), Color{ uiColor(mersenne), uiColor(mersenne), uiColor(mersenne) } };
	}
}