#include "pch.h"
#include "Shader.h"
#include "Floor.h"
#include "Crane.h"
#include "Camera.h"
#include "Light.h"

constexpr size_t wWidth{ 1200 };
constexpr size_t wHeight{ 800 };

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
	Light::getInstance()->initialize("sphere.obj");
	Crane::getInstance()->initialize("cube.obj");

	Shader::getInstance()->glGenerate();
	Shader::getInstance()->initBuffer();
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

	Shader::getInstance()->initBuffer();

	Camera::getInstance()->update();
	Floor::getInstance()->render();
	Light::getInstance()->render();
	Crane::getInstance()->render();

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
		Light::getInstance()->getLightColor() = glm::vec3(1.0f, 1.0f, 1.0f);
		break;
	case 'M':
		Light::getInstance()->getLightColor() = glm::vec3(0.0f, 0.0f, 0.0f);
		break;
	case 'c':
		Light::getInstance()->getColor() += 1;
		switch (static_cast<Color>(Light::getInstance()->getColor() % 4))
		{
		case Color::WHITE:
			Light::getInstance()->getLightColor() = glm::vec3{ 1.0f,1.0f,1.0f };
			break;
		case Color::RED:
			Light::getInstance()->getLightColor() = glm::vec3{ 1.0f, 0.0f, 0.0f };
			break;
		case Color::GREEN:
			Light::getInstance()->getLightColor() = glm::vec3{ 0.0f, 1.0f, 0.0f };
			break;
		case Color::BLUE:
			Light::getInstance()->getLightColor() = glm::vec3{ 0.0f, 0.0f, 1.0f };
			break;
		default:
			break;
		}
		break;
	case 'r':
		Light::getInstance()->onRevolution() = true;
		Light::getInstance()->getRevolutionDirection() = Direction::POSITIVE;
		break;
	case 'R':
		Light::getInstance()->onRevolution() = true;
		Light::getInstance()->getRevolutionDirection() = Direction::NEGATIVE;
		break;
	case 's':
		Light::getInstance()->onRevolution() = false;
		Light::getInstance()->getRevolutionDirection() = Direction::NONE;
		break;
	case 'z':
		Camera::getInstance()->getPositionVector().z -= 0.1f;
		break;
	case 'Z':
		Camera::getInstance()->getPositionVector().z += 0.1f;
		break;
	case 'x':
		Camera::getInstance()->getPositionVector().x -= 0.1f;
		Camera::getInstance()->getLookVector().x -= 0.1f;
		break;
	case 'X':
		Camera::getInstance()->getPositionVector().x += 0.1f;
		Camera::getInstance()->getLookVector().x += 0.1f;
		break;
	case 'y':
		Camera::getInstance()->getDirectionVector() = glm::normalize(Camera::getInstance()->getLookVector() - Camera::getInstance()->getPositionVector());
		Camera::getInstance()->getPositionVector() -= glm::normalize(glm::cross(Camera::getInstance()->getDirectionVector(), Camera::getInstance()->getUpVector())) * 0.1f;
		Camera::getInstance()->getRightVector() = glm::normalize(glm::cross(Camera::getInstance()->getDefaultUpVector(), Camera::getInstance()->getDirectionVector()));
		Camera::getInstance()->getUpVector() = glm::cross(Camera::getInstance()->getDirectionVector(), Camera::getInstance()->getRightVector());
		break;
	case 'Y':
		Camera::getInstance()->getDirectionVector() = glm::normalize(Camera::getInstance()->getLookVector() - Camera::getInstance()->getPositionVector());
		Camera::getInstance()->getPositionVector() += glm::normalize(glm::cross(Camera::getInstance()->getDirectionVector(), Camera::getInstance()->getUpVector())) * 0.1f;
		Camera::getInstance()->getRightVector() = glm::normalize(glm::cross(Camera::getInstance()->getDefaultUpVector(), Camera::getInstance()->getDirectionVector()));
		Camera::getInstance()->getUpVector() = glm::cross(Camera::getInstance()->getDirectionVector(), Camera::getInstance()->getRightVector());
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid TimerFunc(int)
{
	Light::getInstance()->update();
	glutTimerFunc(10, TimerFunc, 1);
	glutPostRedisplay();
}