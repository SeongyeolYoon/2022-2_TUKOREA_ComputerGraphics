#include "pch.h"
#include "Shader.h"

constexpr GLuint wWidth{ 1200 };
constexpr GLuint wHeight{ 800 };

std::vector<Pillar*> pPillar;
std::vector<Snow*> pSnow;

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
	
	for (size_t i = 0; i < PILLARS; ++i) {
		pPillar.emplace_back(new Pillar);
		pPillar[i]->initialize("cube.obj");
	}

	for (size_t i = 0; i < SNOWS; ++i) {
		pSnow.emplace_back(new Snow);
		pSnow[i]->initialize("sphere.obj");
	}

	Shader::getInstance()->glGenerate(pPillar,pSnow);
	Shader::getInstance()->initShader();
	Shader::getInstance()->initTexture(pPillar,pSnow);
	Shader::getInstance()->initBuffer(pPillar,pSnow);

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
	Shader::getInstance()->initBuffer(pPillar, pSnow);

	Floor::getInstance()->render();
	Pyramid::getInstance()->render();

	for (size_t i = 0; i < SNOWS; ++i)
		pSnow[i]->render();
	
	// 불투명한 오브젝트 먼저 그리기
	// 투명한 오프젝트들을 정렬하여 먼 순서대로 그리기 

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (size_t i = 0; i < PILLARS; ++i)
		pPillar[i]->render();

	glDisable(GL_BLEND);
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
		Light::getInstance()->getLightColor() = glm::vec3{ 1.0f,1.0f,1.0f };
		break;
	case 'M':
		Light::getInstance()->getLightColor() = glm::vec3{ 0.0f,0.0f,0.0f };
		break;
	case 's':
		for (size_t i = 0; i < SNOWS; ++i) {
			pSnow[i]->setState(State::FALL);
		}
		break;
	case 'S':
		for (size_t i = 0; i < SNOWS; ++i) {
			pSnow[i]->setState(State::IDLE);
		}
		break;
	case 'y':
		Camera::getInstance()->isOnRotation() = true;
		break;
	case 'Y':
		Camera::getInstance()->isOnRotation() = false;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

GLvoid TimerFunc(int)
{
	Camera::getInstance()->update();


	for (size_t i = 0; i < SNOWS; ++i) {
		pSnow[i]->update();
	}

	glutTimerFunc(10, TimerFunc, 1);
	glutPostRedisplay();
}