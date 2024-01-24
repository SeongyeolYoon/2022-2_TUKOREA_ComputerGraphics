#include "pch.h"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "Floor.h"
#include "Snow.h"
#include "Planet.h"
constexpr size_t wWidth{ 1200 };
constexpr size_t wHeight{ 800 };

std::vector<Snow*> pSnows;
std::vector<Planet*> pPlanets;

GLvoid RenderScene();
GLvoid Reshape(int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid UpdateScene(int);

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
	Light::getInstance()->initialize("cube.obj");

	for (size_t i = 0; i < NumOfSnow; ++i) {
		pSnows.push_back(new Snow);
		pSnows[i]->initialize("sphere.obj");
	}

	pPlanets.push_back(new Planet);
	pPlanets[0]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	pPlanets[0]->initialize("sphere.obj");
	pPlanets[0]->setPositionVector(glm::vec3(0.0f,3.0f,-1.0f));
	pPlanets[0]->setOrbitDirection(glm::vec3(0.0f, 1.0f, 1.0f));

	pPlanets.push_back(new Planet);
	pPlanets[1]->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
	pPlanets[1]->initialize("sphere.obj");
	pPlanets[1]->setPositionVector(glm::vec3(-1.0f,3.0f,-1.5f));
	pPlanets[1]->setOrbitDirection(glm::vec3(1.0f, 1.0f, 0.0f));

	pPlanets.push_back(new Planet);
	pPlanets[2]->setColor(glm::vec3(0.0f, 0.0f, 1.0f));
	pPlanets[2]->initialize("sphere.obj");
	pPlanets[2]->setPositionVector(glm::vec3(-2.0f,3.0f,-2.0f));
	pPlanets[2]->setOrbitDirection(glm::vec3(1.0f, 0.0f, 1.0f));

	Shader::getInstance()->glGenerate(pSnows,pPlanets);
	Shader::getInstance()->initShader();
	Shader::getInstance()->initBuffer(pSnows,pPlanets);

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, UpdateScene, 1);
	glutMainLoop();
}

GLvoid RenderScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	Shader::getInstance()->initBuffer(pSnows,pPlanets);
	
	// Camera
	{
		Camera::getInstance()->update();
	}

	// Light
	{
		Light::getInstance()->render();
	}

	// Floor
	{
		Floor::getInstance()->render();
	}

	// Snow
	{
		for (size_t i = 0; i < NumOfSnow; ++i)
			pSnows[i]->render();
	}

	// Planet
	{
		for (size_t i = 0; i < NumOfPlanet; ++i) {
			pPlanets[i]->render();
		}
	}

	// Pyramid
	{
		SquarePyramid::getInstance()->render();
	}

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
	case 's':
		for (size_t i = 0; i < NumOfSnow; ++i)
			pSnows[i]->setState(State::FALL);
		break;
	case 'S':
		for (size_t i = 0; i < NumOfSnow; ++i)
			pSnows[i]->setState(State::IDLE);
		break;
	case 'r':
		Light::getInstance()->getState() = State::REVOLVE;
		break;
	case 'R':
		Light::getInstance()->getState() = State::IDLE;
		break;
	case '0':


		break;
	case '1':
		break;
	case '2':
		break;
	case '3':
		break;
	case '4':
		break;
	case '5':
		break;
	case 'i':
	{
		glm::vec3 direciton = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f) - Light::getInstance()->getLightPositionVector());
		Light::getInstance()->getLightPositionVector() += direciton * Light::getInstance()->getMoveAmount();
		break;
	}
	case 'o':
	{
		glm::vec3 direciton = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f) - Light::getInstance()->getLightPositionVector());
		Light::getInstance()->getLightPositionVector() -= direciton * Light::getInstance()->getMoveAmount();
		break;
	}
	case '+':
		Light::getInstance()->getLightColor().x += 0.1f;
		Light::getInstance()->getLightColor().y += 0.1f;
		Light::getInstance()->getLightColor().z += 0.1f;
		break;
	case '-':
		Light::getInstance()->getLightColor().x -= 0.1f;
		Light::getInstance()->getLightColor().y -= 0.1f;
		Light::getInstance()->getLightColor().z -= 0.1f;
		break;
	default:
		break;
	case 'q':
		break;
	}
	glutPostRedisplay();
}

GLvoid UpdateScene(int)
{
	// Snow
	{
		for (size_t i = 0; i < NumOfSnow; ++i)
			pSnows[i]->update();
	}
	
	// Light
	{
		Light::getInstance()->update();
	}
	
	// Planet
	{
		for (size_t i = 0; i < NumOfPlanet; ++i) {
			pPlanets[i]->update();
		}
	}

	glutTimerFunc(10, UpdateScene, 1);
	glutPostRedisplay();
}