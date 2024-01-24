#include <iostream>
#include <random>
#include <gl\glew.h>
#include <gl\freeglut.h>
#include <gl\freeglut_ext.h>

class Rect {
private:
	GLfloat left, bottom , right, top;
	GLfloat r, g, b;
public:
	static int nRect;
public:
	Rect(const GLfloat& left_in, const GLfloat& bottom_in, const GLfloat& right_in, const GLfloat& top_in,
		const GLfloat& r_in, const GLfloat& g_in, const GLfloat& b_in)
		:left{left_in},bottom{bottom_in},right{right_in},top{top_in},r{r_in},g{g_in},b{b_in}
	{
			
	}

	void setPos(const GLfloat& left_in, const GLfloat& bottom_in, const GLfloat& right_in, const GLfloat& top_in)
	{
		left = left_in;
		bottom = bottom_in;
		right = right_in;
		top = top_in;
	}

	const GLfloat& getRed() const
	{
		return r;
	}

	const GLfloat& getGreen() const
	{
		return g;
	}

	const GLfloat& getBlue() const
	{
		return b;
	}

	const GLfloat& getLeft() const
	{
		return left;
	}

	const GLfloat& getBottom() const
	{
		return bottom;
	}

	const GLfloat& getRight() const
	{
		return right;
	}

	const GLfloat& getTop() const
	{
		return top;
	}

	void render() const
	{
		glColor3f(getRed(), getGreen(), getBlue());
		glRectf(getLeft(), getBottom(), getRight(), getTop());
	}

	bool isInRect(const GLfloat& mx, const GLfloat& my)
	{
		return ((left < mx && mx < right) && (bottom < my && my < top )) ? true : false;
	}
};

bool g_leftButton{ false };
constexpr unsigned int winWidth{ 800 };
constexpr unsigned int winHeight{ 600 };
int Rect::nRect = 0;
Rect* pRect[6];

GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid Motion(int x, int y);
void ConvertDeviceXYOpenGLXY(const int&, const int&, GLfloat*, GLfloat*);
void AddRect();

int main(int argc, char** argv)
{
	AddRect();
	constexpr unsigned int winPosX{ 0 };
	constexpr unsigned int winPosY{ 0 };
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(winPosX, winPosY);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Prac_03");

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
	glClearColor(0.15f,0.15f,0.15f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	pRect[0]->render();

	for (int i = 1; i < Rect::nRect; ++i) {
		pRect[i]->render();
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

	if (GLUT_LEFT_BUTTON == button && GLUT_DOWN == state) {
		g_leftButton = true;
	}
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
	{
		AddRect();
		break;
	}
	default:
		break;
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

GLvoid Motion(int x, int y)
{
	GLfloat mx{ 0.0f };
	GLfloat my{ 0.0f };
	ConvertDeviceXYOpenGLXY(x, y, &mx, &my);

	if (g_leftButton) {
		for (int i = Rect::nRect - 1; i >= 0; --i) {
			if (pRect[i]->isInRect(mx, my)) {
				pRect[i]->setPos(mx - 0.15f, my - 0.15f, mx + 0.15f, my + 0.15f);
				break;
			}
		}
	}

	glutPostRedisplay();
}


void AddRect()
{
	std::mt19937 mersenne{ std::random_device{}() };
	std::uniform_real_distribution<GLfloat> uiColor{ 0.0f,1.0f };
	if (Rect::nRect < 5) {
		pRect[Rect::nRect] = new Rect{ -0.15f,-0.15f,0.15f,0.15f,uiColor(mersenne),uiColor(mersenne),uiColor(mersenne) };
		Rect::nRect++;
	}
}