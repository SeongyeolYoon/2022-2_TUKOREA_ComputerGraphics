#include "pch.h"
#include "Shader.h"
#include "Light.h"
#include "Camera.h"
#include "Sphere.h"

constexpr size_t wWidth{ 1200 };
constexpr size_t wHeight{ 800 };
constexpr size_t MaxSpheres{ 3 };

std::vector<Sphere*> pSphere;
Camera* Camera::pInst = nullptr;
Shader* Shader::pInst = nullptr;
Light* Light::pInst = nullptr;

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

	pSphere.push_back(new Sphere);
	pSphere[0]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
	pSphere[0]->setPositionVector(glm::vec3(0.0f, 0.0f, 0.0f));

	pSphere.push_back(new Sphere);
	pSphere[1]->setColor(glm::vec3(0.0f, 1.0f, 0.0f));
	pSphere[1]->setPositionVector(glm::vec3(-2.0f, 0.0f, -1.0f));

	pSphere.push_back(new Sphere);
	pSphere[2]->setColor(glm::vec3(0.0f, 0.0f, 1.0f));
	pSphere[2]->setPositionVector(glm::vec3(-4.0f, 0.0f, -2.0f));

	Light::getInstance()->readObj("cube.obj");
	
	for (size_t i = 0; i < MaxSpheres; ++i)
		pSphere[i]->readObj("sphere.obj");

	Shader::getInstance()->glGenerate(pSphere);
	Shader::getInstance()->initBuffer(pSphere);
	Shader::getInstance()->initShader();

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
	Shader::getInstance()->initBuffer(pSphere);
	Camera::getInstance()->update();
	glm::mat4 parent{1.0f};
	Light::getInstance()->render(parent); 

	for (size_t i = 0; i < MaxSpheres; ++i)
		pSphere[i]->render(parent);

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
	case 'c':
		if (LightColor::NONE == Light::getInstance()->getLightColorType()) {
			Light::getInstance()->getLightColorType() = LightColor::WHITE;
		}
		else if (LightColor::WHITE == Light::getInstance()->getLightColorType()) {
			Light::getInstance()->getLightColorType() = LightColor::RED;
		}
		else if (LightColor::RED == Light::getInstance()->getLightColorType()) {
			Light::getInstance()->getLightColorType() = LightColor::GREEN;
		}
		else if (LightColor::GREEN == Light::getInstance()->getLightColorType()) {
			Light::getInstance()->getLightColorType() = LightColor::BLUE;
		}
		else {
			Light::getInstance()->getLightColorType() = LightColor::NONE;
		}

		switch (Light::getInstance()->getLightColorType())
		{
		case LightColor::NONE:
			Light::getInstance()->getLightColor() = glm::vec3(0.0f, 0.0f, 0.0f);
			break;
		case LightColor::WHITE:
			Light::getInstance()->getLightColor() = glm::vec3(1.0f, 1.0f, 1.0f);
			break;
		case LightColor::RED:
			Light::getInstance()->getLightColor() = glm::vec3(1.0f, 0.0f, 0.0f);
			break;
		case LightColor::GREEN:
			Light::getInstance()->getLightColor() = glm::vec3(0.0f, 1.0f, 0.0f);
			break;
		case LightColor::BLUE:
			Light::getInstance()->getLightColor() = glm::vec3(0.0f, 0.0f, 1.0f);
			break;
		default:
			break;
		}
		break;
	case 'r':
		Light::getInstance()->getRevolutionDirection() = Direction::POSITIVE;
		Light::getInstance()->isOnRevolution() = true;
		break;
	case 'R':
		Light::getInstance()->getRevolutionDirection() = Direction::NEGATIVE;
		Light::getInstance()->isOnRevolution() = true;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid TimerFunc(int value)
{
	if (Light::getInstance()->isOnRevolution()) {
		GLfloat distance = sqrtf(powf(0 - Light::getInstance()->getPositionVector().x, 2) + powf(0 - Light::getInstance()->getPositionVector().y, 2) + powf(0 - Light::getInstance()->getPositionVector().z, 2));

		switch (Light::getInstance()->getRevolutionDirection())
		{
		case Direction::POSITIVE:
			Light::getInstance()->getRevolutionDegree() += 1.0f;
			Light::getInstance()->getLightPos().x = distance * cosf(glm::radians(Light::getInstance()->getRevolutionDegree()));
			Light::getInstance()->getLightPos().z = distance * sinf(glm::radians(Light::getInstance()->getRevolutionDegree()));
			break;
		case Direction::NEGATIVE:
			Light::getInstance()->getRevolutionDegree() -= 1.0f;
			Light::getInstance()->getLightPos().x = distance * cosf(glm::radians(Light::getInstance()->getRevolutionDegree()));
			Light::getInstance()->getLightPos().z = distance * sinf(glm::radians(Light::getInstance()->getRevolutionDegree()));
			break;
		default:
			break;
		}
	}

	glutTimerFunc(10, TimerFunc, 1);
	glutPostRedisplay();
}