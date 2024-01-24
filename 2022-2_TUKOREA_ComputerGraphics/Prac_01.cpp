#include <iostream>
#include <cstdlib>
#include <random>
#include <gl/glew.h>
#include <gl\freeglut.h>
#include <gl\freeglut_ext.h>

class Color {
private:
	GLfloat r{1.0f}, g{1.0f}, b{1.0f}, alpha{1.0f};
public:
	Color() { }

	void setColor(const GLfloat& rIn, const GLfloat& gIn, const GLfloat& bIn)
	{
		r = rIn;
		g = gIn;
		b = bIn;
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

	const GLfloat& getAlpha() const
	{
		return alpha;
	}
};

Color* pColor = new Color;
bool g_onMoveCross{ false };
GLvoid DrawScene();
GLvoid Reshape(int,int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid TimerFunc(int value);

int main(int argc, char** argv)
{
	constexpr unsigned int winWidth{ 800 };
	constexpr unsigned int winHeight{ 600 };
	constexpr unsigned int winPosX{ 0 };
	constexpr unsigned int winPosY{ 0 };

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(winPosX, winPosY);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Prac_01");

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		std::cerr << "Unalbe to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}

GLvoid DrawScene()
{
	glClearColor(pColor->getRed(), pColor->getGreen(), pColor->getBlue(),pColor->getAlpha());
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y) 
{
	switch (key) {
	case 'R':
		pColor->setColor(1.0f, 0.0f, 0.0f);
		break;
	case 'G':
		pColor->setColor(0.0f, 1.0f, 0.0f);
		break;
	case 'B':
		pColor->setColor(0.0f, 0.0f, 1.0f);
		break;
	case 'A':
	{
		std::mt19937 mersenne{ std::random_device{}() };
		std::uniform_real_distribution<GLfloat> uiColor{ 0.0f,1.0f };
		pColor->setColor(uiColor(mersenne), uiColor(mersenne), uiColor(mersenne));
		break;
	}
	case 'W':
		pColor->setColor(1.0f, 1.0f, 1.0f);
		break;
	case 'K':
		pColor->setColor(0.0f, 0.0f, 0.0f);
		break;
	case 'T':
		g_onMoveCross = !g_onMoveCross;
		if(g_onMoveCross)
			glutTimerFunc(1000, TimerFunc, 1);
		break;
	case 'S':
		g_onMoveCross = !g_onMoveCross;
		break;
	case 'Q':
		glutLeaveMainLoop();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid TimerFunc(int value)
{
	if (g_onMoveCross) {
		std::mt19937 mersenne{ std::random_device{}() };
		std::uniform_real_distribution<GLfloat> uiColor{ 0.0f,1.0f };
		pColor->setColor(uiColor(mersenne), uiColor(mersenne), uiColor(mersenne));
		glutPostRedisplay();
		glutTimerFunc(1000, TimerFunc, 1);
	}
}