#include "pch.h"
#include "Hexahedron.h"
#include "Shader.h"
#include "Light.h"
#include "Camera.h"
#include "CoordSystem.h"
#include "Orbit.h"
#include "Sphere.h"

enum class ModelType{NONE=0, HEXAHEDRON, SQUAREPYRAMID };

constexpr size_t wWidth{ 1200 };
constexpr size_t wHeight{ 800 };

std::vector<Orbit*> pOrbit;
CoordSystem* CoordSystem::pInst = nullptr;
Hexahedron* Hexahedron::pInst = nullptr;
Camera* Camera::pInst = nullptr;
Shader* Shader::pInst = nullptr;
Light* Light::pInst = nullptr;
Sphere* Sphere::pInst = nullptr;
ModelType modelType{ ModelType::NONE };

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

	GLfloat degree{ 0.0f };

	for(size_t i =0; i < MaxOrbit; ++i){
		pOrbit.push_back(new Orbit{degree});
		pOrbit[i]->initialize("sphere.obj");
		degree += 0.5f;
	}

	Hexahedron::getInstance()->readObj("cube.obj");
	Light::getInstance()->readObj("cube.obj");
	Sphere::getInstance()->readObj("sphere.obj");

	Shader::getInstance()->initShader();
	Shader::getInstance()->glGenerate(pOrbit);
	Shader::getInstance()->initBuffer(pOrbit);

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, TimerFunc, 1);
	glutMainLoop();
}

GLvoid RenderScene()
{
	Shader::getInstance()->initBuffer(pOrbit);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glm::mat4 parent = CoordSystem::getInstance()->render();

	for (size_t i = 0; i < MaxOrbit; ++i) {
		pOrbit[i]->render(parent);
	}
	switch (modelType)
	{
	case ModelType::NONE:
		break;
	case ModelType::HEXAHEDRON:
		Hexahedron::getInstance()->render(parent);
		break;
	case ModelType::SQUAREPYRAMID:
		SquarePyramid::getInstance()->render(parent);
		break;
	default:
		break;
	}
	Camera::getInstance()->update();
	Light::getInstance()->render(parent);
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
	case 'n':
		switch (modelType)
		{
		case ModelType::NONE:
			modelType = ModelType::HEXAHEDRON;
			break;
		case ModelType::HEXAHEDRON:
			modelType = ModelType::SQUAREPYRAMID;
			break;
		case ModelType::SQUAREPYRAMID:
			modelType = ModelType::NONE;
			break;
		default:
			break;
		}
		break;
	case 'm':
		Light::getInstance()->isOnRight() = !Light::getInstance()->isOnRight();
		if (Light::getInstance()->isOnRight())
			Light::getInstance()->on();
		else
			Light::getInstance()->off();
		break;
	case 'y':
		switch (modelType)
		{
		case ModelType::NONE:
			break;
		case ModelType::HEXAHEDRON:
			Hexahedron::getInstance()->isOnRotation() = true;
			break;
		case ModelType::SQUAREPYRAMID:
			//Sphere::getInstance()->isOnRotation() = true;
			SquarePyramid::getInstance()->isOnRotation() = true;
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
	case 'z':
	{
		glm::vec3 directionVector = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - Light::getInstance()->getLightPosition());
		Light::getInstance()->getLightPosition() += directionVector * Light::getInstance()->getMoveAmount();
		Light::getInstance()->getRadian() -= 0.3f;
		for (size_t i = 0; i < MaxOrbit; ++i)
			pOrbit[i]->getRadian() -= 5.0f;
		break;
	}
	case 'Z':
	{
		glm::vec3 directionVector = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - Light::getInstance()->getLightPosition());
		Light::getInstance()->getLightPosition() += directionVector * (-Light::getInstance()->getMoveAmount());
		Light::getInstance()->getRadian() += 0.3f;
		for (size_t i = 0; i < MaxOrbit; ++i)
			pOrbit[i]->getRadian() += 5.0f;
		break;
	}
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

	for (size_t i = 0; i < MaxOrbit; ++i)
		pOrbit[i]->update();

	if (Light::getInstance()->isOnRevolution()) {	
		switch (Light::getInstance()->getRevolutionDirection())
		{
		case Direction::POSITIVE:
		{
			Light::getInstance()->getRevolutionDegree() += 1.0f;
			Light::getInstance()->getLightPosition().x = Light::getInstance()->getRadian() * cosf(glm::radians(Light::getInstance()->getRevolutionDegree()));
			Light::getInstance()->getLightPosition().z = Light::getInstance()->getRadian() * sinf(glm::radians(Light::getInstance()->getRevolutionDegree()));
			break;
		}
		case Direction::NEGATIVE:
		{
			Light::getInstance()->getRevolutionDegree() -= 1.0f;
			Light::getInstance()->getLightPosition().x = Light::getInstance()->getRadian() * cosf(glm::radians(Light::getInstance()->getRevolutionDegree()));
			Light::getInstance()->getLightPosition().z = Light::getInstance()->getRadian() * sinf(glm::radians(Light::getInstance()->getRevolutionDegree()));
			break;
		}
		default:
			break;
		}
	}

	switch (modelType)
	{
	case ModelType::NONE:
		break;
	case ModelType::HEXAHEDRON:
		if (Hexahedron::getInstance()->isOnRotation()) {
			Hexahedron::getInstance()->getRotationDegree() += 1.0f;
		}
		break;
	case ModelType::SQUAREPYRAMID:
		//if (Sphere::getInstance()->isOnRotation()) {
		//	Sphere::getInstance()->getRotationDegree() += 1.0f;
		//}
		if (SquarePyramid::getInstance()->isOnRotation()) {
			SquarePyramid::getInstance()->getRotationDegree() += 1.0;
		}
		break;
	default:
		break;
	}

	glutTimerFunc(10, TimerFunc, 1);
	glutPostRedisplay();
}