#include <iostream>
#include <cstdlib>
#include <random>
#include <gl\glew.h>
#include <gl\freeglut.h>
#include <gl\freeglut_ext.h>

enum class Direction { IDLE = 0, LU, LD, RU, RD };

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
	Direction dir;
	Direction zigDir;
	GLfloat tempZigzag{ 0.0f };
	int randomNum;
public:
	static int nRect;
	bool sizeFlag{ false };
	bool zigzagFlag{ false };
	static const float moveAmount;
public:
	Rect(const Position2D& pos_in = Position2D{ 0.0f,0.0f,0.0f,0.0f }, const Color& color_in = Color{ 0.0f,0.0f,0.0f }, const Direction& dir_in = Direction::IDLE, const int& r_in = -1)
		: pos{ pos_in }, color{ color_in }, dir{ dir_in }, tempPos{ pos_in },randomNum{r_in}
	{

	}

	const Position2D& getTempPos()
	{
		return tempPos;
	}

	const int& getRandomNum()
	{
		return randomNum;
	}

	void setPos(const Position2D& pos_in)
	{
		pos = pos_in;
	}

	const Position2D& getPos() { return pos; }

	void render() const
	{
		glColor3f(color.r, color.g, color.b);
		glRectf(pos.left, pos.bottom, pos.right, pos.top);
	}

	void move()
	{
		std::mt19937 mersenne{ std::random_device{}() };
		std::uniform_int_distribution<int> uiDir{ 1,4 };
		switch (dir)
		{
		case Direction::LU:
			if (pos.left <= -0.9f || pos.top >= 0.9f) {
				Direction d;
				while (true) {
					d = static_cast<Direction>(uiDir(mersenne));
					if (d != dir)
						break;
				}
				dir = d;
			}
			pos.left -= moveAmount;
			pos.bottom += moveAmount;
			pos.right -= moveAmount;
			pos.top += moveAmount;
			pos.left += 0.05f;
			pos.right += 0.05f;
			break; 
		case Direction::LD:
			if (pos.left <= -0.9f || pos.bottom <= -0.9f) {
				Direction d;
				while (true) {
					d = static_cast<Direction>(uiDir(mersenne));
					if (d != dir)
						break;
				}
				dir = d;
			}
			pos.left -= moveAmount;
			pos.bottom -= moveAmount;
			pos.right -= moveAmount;
			pos.top -= moveAmount;
			break;
		case Direction::RU:
			if (pos.right >= 0.9f || pos.top >= 0.9f) {
				Direction d;
				while (true) {
					d = static_cast<Direction>(uiDir(mersenne));
					if (d != dir)
						break;
				}
				dir = d;
			}
			pos.left += moveAmount;
			pos.bottom += moveAmount;
			pos.right += moveAmount;
			pos.top += moveAmount;
			break;
		case Direction::RD:
			if (pos.right >= 0.9f || pos.bottom <= -0.9f) {
				Direction d;
				while (true) {
					d = static_cast<Direction>(uiDir(mersenne));
					if (d != dir)
						break;
				}
				dir = d;
			}
			pos.left += moveAmount;
			pos.bottom -= moveAmount;
			pos.right += moveAmount;
			pos.top -= moveAmount;
			break;
		default:
			break;
		}
	}

	void zoomIn()
	{
		pos.left -= moveAmount;
		pos.bottom -= moveAmount;
		pos.right += moveAmount;
		pos.top += moveAmount;
	}

	void zoomOut()
	{
		pos.left += moveAmount;
		pos.bottom += moveAmount;
		pos.right -= moveAmount;
		pos.top -= moveAmount;
	}

	bool isMaxSize()
	{
		if (abs(pos.right - pos.left) > 0.3f && abs(pos.top - pos.bottom) > 0.3f)
			return true;
	}

	bool isMinSize()
	{
		if (abs(pos.right - pos.left) <= 0.1f && abs(pos.top - pos.bottom) <= 0.1f)
			return true;
	}

	void expandWidth()
	{
		pos.left -= moveAmount;
		pos.right += moveAmount;
	}

	void contractWidth()
	{
		pos.left += moveAmount;
		pos.right -= moveAmount;
	}

	bool isMaxWidth()
	{
		if (abs(pos.right - pos.left) >= 1.0f)
			return true;
	}
	
	bool isMinWidth()
	{
		if (abs(pos.right - pos.left) <= 0.1f)
			return true;
	}

	void  expandHeight()
	{
		pos.bottom -= moveAmount;
		pos.top += moveAmount;
	}

	void contractHeight()
	{
		pos.bottom += moveAmount;
		pos.top -= moveAmount;
	}

	bool isMaxHeight()
	{
		if (abs(pos.top - pos.bottom) >= 1.0f)
			return true;
	}

	bool isMinHeight()
	{
		if (abs(pos.top - pos.bottom) <= 0.1f)
			return true;
	}

	void zigzag()
	{
		if (!zigzagFlag) {
			pos.left -= 0.05f;
			pos.right -= 0.05f;
			tempZigzag += 0.05f;
			if (tempZigzag >= 0.15f) {
				zigzagFlag = true;
				tempZigzag = 0;
			}
		}
		else {
			pos.left += 0.05f;
			pos.right += 0.05f;
			tempZigzag += 0.05f;
			if (tempZigzag >= 0.15f) {
				zigzagFlag = false;
				tempZigzag = 0;
			}
		}
	}
};

constexpr unsigned int winWidth{ 800 };
constexpr unsigned int winHeight{ 600 };

int Rect::nRect = 0;
const float Rect::moveAmount = 0.075f;

bool g_onMoveCross{ false };
bool g_changeSize{ false };
bool g_onMoveZigZag{ false };

bool g_onTimer{ false };

Rect* pRect[5];

GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid TimerFunc(int);

void ConvertDeviceXYOpenGLXY(const int&, const int&, GLfloat*, GLfloat*);

int main(int argc, char** argv)
{
	constexpr unsigned int winPosX{ 0 };
	constexpr unsigned int winPosY{ 0 };
	std::mt19937 mersenne{ std::random_device{}() };
	std::uniform_real_distribution<GLfloat> uiColor{ 0.0f,1.0f };


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
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(150, TimerFunc, 1);
	glutMainLoop();
}

GLvoid DrawScene()
{
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < Rect::nRect; ++i)
		pRect[i]->render();

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
	std::mt19937 mersenne{ std::random_device{}() };
	std::uniform_int_distribution<int> uiDir{ 1,4 };
	std::uniform_int_distribution<int> uiRandom{ 1,3 };
	std::uniform_real_distribution<GLfloat> uiColor{ 0.0f,1.0f };
	ConvertDeviceXYOpenGLXY(x, y, &mx, &my);

	if (GLUT_LEFT_BUTTON == button && GLUT_DOWN == state) {
		if (Rect::nRect < 5) {
			pRect[Rect::nRect] = new Rect{ Position2D{mx - 0.05f,my - 0.05f,mx + 0.05f,my + 0.05f},Color(uiColor(mersenne),uiColor(mersenne),uiColor(mersenne)),
		static_cast<Direction>(uiDir(mersenne)),uiRandom(mersenne)};
			Rect::nRect++;
		}
	}
}
void ConvertDeviceXYOpenGLXY(const int& x, const int& y, GLfloat* pMx, GLfloat* pMy)
{
	int w = winWidth;
	int h = winHeight;

	*pMx = GLfloat((x - GLfloat(w) / 2.0) * GLfloat((1.0 / GLfloat(w / 2.0))));
	*pMy = -GLfloat((y - GLfloat(h) / 2.0) * GLfloat((1.0 / GLfloat(h / 2.0))));
}

GLvoid Keyboard(unsigned char key, int, int)
{
	switch (key)
	{
	case 'a':
		g_onMoveCross = !g_onMoveCross;
		g_onTimer = true;
		break;
	case 'i':
		g_onMoveZigZag = !g_onMoveZigZag;
		g_onTimer = true;
		break;
	case 'c':
		g_changeSize = !g_changeSize;
		g_onTimer = true;
		break;
	case 's':
		g_onTimer = !g_onTimer;
		break;
	case 'm':
		for (int i = 0; i < Rect::nRect; ++i)
			pRect[i]->setPos(pRect[i]->getTempPos());
		break;
	case 'r':
		for (int i = 0; i < Rect::nRect; ++i) {
			delete pRect[i];
		}
		Rect::nRect = 0;
		g_onMoveCross = false;
		g_changeSize = false;
		g_onMoveZigZag = false;
		g_onTimer = false;
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid TimerFunc(int value)
{

	if (g_onTimer) {
		if (g_onMoveZigZag) {
			for (int i = 0; i < Rect::nRect; ++i) {
				pRect[i]->zigzag();
			}
		}


		if (g_onMoveCross) {
			for (int i = 0; i < Rect::nRect; ++i)
				pRect[i]->move();
		}

		if (g_changeSize) {
			for (int i = 0; i < Rect::nRect; ++i) {
				if (1 == pRect[i]->getRandomNum()) {
					if (!pRect[i]->sizeFlag) {
						pRect[i]->expandWidth();
						if (pRect[i]->isMaxWidth()) {
							pRect[i]->sizeFlag = true;
						}
					}
					else {
						pRect[i]->contractWidth();
						if (pRect[i]->isMinWidth()) {
							pRect[i]->sizeFlag = false;
						}
					}
				}
				else if (2 == pRect[i]->getRandomNum()) {
					if (!pRect[i]->sizeFlag) {
						pRect[i]->expandHeight();
						if (pRect[i]->isMaxHeight()) {
							pRect[i]->sizeFlag = true;
						}
					}
					else {
						pRect[i]->contractHeight();
						if (pRect[i]->isMinHeight()) {
							pRect[i]->sizeFlag = false;
						}
					}
				}
				else if (3 == pRect[i]->getRandomNum()) {
					if (!pRect[i]->sizeFlag) {
						pRect[i]->zoomIn();
						if (pRect[i]->isMaxSize()) {
							pRect[i]->sizeFlag = true;
						}
					}
					else {
						pRect[i]->zoomOut();
						if (pRect[i]->isMinSize()) {
							pRect[i]->sizeFlag = false;
						}
					}
				}
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(150, TimerFunc, 1);
}