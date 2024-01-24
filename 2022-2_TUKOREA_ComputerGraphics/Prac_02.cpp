#include <iostream>
#include <random>
#include <gl\glew.h>
#include <gl\freeglut.h>
#include <gl\freeglut_ext.h>

class Color {
private:
	GLfloat r, g, b;
public:
	Color(const GLfloat& r_in = 0.0f, const GLfloat& g_in = 0.0f, const GLfloat& b_in = 0.0f)
		:r{r_in}, g{g_in}, b{b_in}
	{

	}

	void setColor(const Color& color_in)
	{
		r = color_in.r;
		g = color_in.g;
		b = color_in.b;
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
};

class Position2D {
private:
	GLfloat left, bottom, right, top;

public:
	Position2D(const GLfloat& left_in = -0.5f, const GLfloat& bottom_in = -0.5f, const GLfloat& right_in = 0.5f, const GLfloat& top_in = 0.5f)
		: left{left_in}, bottom{bottom_in}, right{right_in}, top{top_in}
	{ }

	void setPos(const Position2D& pos_in)
	{
		left = pos_in.left;
		bottom = pos_in.bottom;
		right = pos_in.right;
		top = pos_in.top;
	}

	void zoomIn()
	{
		left -= 0.1f;
		bottom -= 0.1f;
		right += 0.1f;
		top += 0.1f;
	}

	void zoomOut()
	{
		left += 0.1f;
		bottom += 0.1f;
		right -= 0.1f;
		top -= 0.1f;
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
};

class BackGround : public Color {
public:
	BackGround(const Color& color_in)
		:Color(color_in)
	{

	}
};

class Rect : public Color, public Position2D{
public:
	Rect(const Color& color_in, const Position2D& pos_in)
		: Color(color_in), Position2D(pos_in)
	{ }

	void render()
	{
		glColor3f(getRed(), getGreen(), getBlue());
		glRectf(getLeft(), getBottom(), getRight(), getTop());
	}
};

Rect* pRect;
BackGround* pBackGround;

constexpr unsigned int winWidth{ 800 };
constexpr unsigned int winHeight{ 600 };

GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
void ConvertDeviceXYOpenGLXY(const int&, const int&, GLfloat*, GLfloat*);
bool IsInRect(const GLfloat&, const GLfloat&);

int main(int argc, char** argv)
{
	constexpr unsigned int winPosX{ 0 };
	constexpr unsigned int winPosY{ 0 };
	std::mt19937 mersenne{ std::random_device{}() };
	std::uniform_real_distribution<GLfloat> uiColor{ 0.0f,1.0f };
	pRect = new Rect{ Color(uiColor(mersenne),uiColor(mersenne),uiColor(mersenne)),Position2D(-0.5f,-0.5f,0.5f,0.5f) };
	pBackGround = new BackGround{ Color(uiColor(mersenne),uiColor(mersenne),uiColor(mersenne)) };
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(winPosX, winPosY);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Prac_02");

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
	glutMainLoop();
}

GLvoid DrawScene()
{
	glClearColor(pBackGround->getRed(), pBackGround->getGreen(), pBackGround->getBlue(), 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	pRect->render();
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
	std::uniform_real_distribution<GLfloat> uiColor{ 0.0f,1.0f };
	ConvertDeviceXYOpenGLXY(x, y, &mx, &my);

	if (GLUT_LEFT_BUTTON == button && GLUT_DOWN == state) {
		if (IsInRect(mx, my))
			pRect->setColor(Color(uiColor(mersenne),uiColor(mersenne), uiColor(mersenne)));
		else
			pBackGround->setColor(Color(uiColor(mersenne), uiColor(mersenne), uiColor(mersenne)));
	}

	if (GLUT_RIGHT_BUTTON == button && GLUT_DOWN == state) {
		if (IsInRect(mx, my))
			pRect->zoomIn();
		else
			pRect->zoomOut();
	}
}

void ConvertDeviceXYOpenGLXY(const int& x, const int& y, GLfloat* pMx, GLfloat* pMy)
{
	int w = winWidth;
	int h = winHeight;

	*pMx = GLfloat((x - GLfloat(w) / 2.0) * GLfloat((1.0 / GLfloat(w / 2.0))));
	*pMy = -GLfloat((y - GLfloat(h) / 2.0) * GLfloat((1.0 / GLfloat(h / 2.0))));
}

bool IsInRect(const GLfloat& x, const GLfloat& y)
{
	return ((pRect->getLeft() < x && x < pRect->getRight()) && (pRect->getBottom() < y && y < pRect->getTop())) ? true : false;
}