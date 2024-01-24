#include "pch.h"
#include "Shader.h"

constexpr GLuint wWidth{ 1200 };
constexpr GLuint wHeight{ 800 };

std::vector<Snow*> pSnows;
std::vector<Pillar*> pPillar;

GLvoid RenderScene();
GLvoid Reshape(int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid TimerFunc(int);

int main(int argc, char** argv)
{
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

	Floor::getInstance()->initialize("cube.obj");

	for (size_t i = 0; i < NumOfSnow; ++i) {
		pSnows.emplace_back(new Snow);
		pSnows[i]->initialize("sphere.obj");
	}

	//for (size_t i = 0; i < NumOfPillar; ++i) {
	//	pPillar.emplace_back(new Pillar);
	//	pPillar[i]->initialize("cube.obj");
	//}

	Shader::getInstance()->glGenerate(pSnows,pPillar);
	Shader::getInstance()->initShader();
	Shader::getInstance()->initTexture(pSnows,pPillar);
	Shader::getInstance()->initBuffer(pSnows,pPillar);

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, TimerFunc, 1);
	glutMainLoop();
}

GLvoid RenderScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	Shader::getInstance()->initBuffer(pSnows,pPillar);
	
	Floor::getInstance()->render();

	for (size_t i = 0; i < NumOfSnow; ++i)
		pSnows[i]->render();

	//for (size_t i = 0; i < NumOfPillar; ++i)
	//	pPillar[i]->render();
	//
	
	Pyramid::getInstance()->render();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'm':
		break;
	case 'M':
		break;
	case 's':
		for (size_t i = 0; i < NumOfSnow; ++i) {
			pSnows[i]->setState(State::FALL);
		}
		break;
	case 'S':
		for (size_t i = 0; i < NumOfSnow; ++i) {
			pSnows[i]->setState(State::IDLE);
		}
		break;
	case 'y':
		break;
	case 'Y':
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

GLvoid TimerFunc(int)
{
	Camera::getInstance()->update();

	for (size_t i = 0; i < NumOfSnow; ++i)
		pSnows[i]->update();

	glutTimerFunc(10, TimerFunc, 1);
	glutPostRedisplay();
}