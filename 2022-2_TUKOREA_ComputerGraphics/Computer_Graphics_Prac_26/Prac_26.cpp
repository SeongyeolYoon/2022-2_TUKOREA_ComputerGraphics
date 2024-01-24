#include "pch.h"
#include "Shader.h"

constexpr GLuint wWidth{ 1200 };
constexpr GLuint wHeight{ 800 };

Shape shape{ Shape::NONE};

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

	Cube::getInstance()->readObj("cube.obj");
	BackGround::getInstance()->readObj("cube.obj");

	Shader::getInstance()->glGenerate();
	Shader::getInstance()->initShader();
	Shader::getInstance()->initTexture();
	Shader::getInstance()->initBuffer();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, TimerFunc, 1);

	glutMainLoop();
}

GLvoid RenderScene()
{
	Shader::getInstance()->initBuffer();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	BackGround::getInstance()->render();
	glm::mat4 parent = CoordSystem::getInstance()->render();
	switch (shape)
	{
	case Shape::NONE:
		break;
	case Shape::CUBE:
		Cube::getInstance()->render(parent);
		break;
	case Shape::PYRAMID:
		Pyramid::getInstance()->render(parent);
		break;
	default:
		break;
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
	case 'c':
		shape = Shape::CUBE;
		break;
	case 'p':
		shape = Shape::PYRAMID;
		break;
	case 'x':
		switch (shape)
		{
		case Shape::NONE:
			break;
		case Shape::CUBE:
			if (!Cube::getInstance()->isOnRotation())
				Cube::getInstance()->isOnRotation() = true;
			Cube::getInstance()->getAxis() = Axis::X;
			Cube::getInstance()->getDirection() = Direction::POSITIVE;
			break;
		case Shape::PYRAMID:
			if (!Pyramid::getInstance()->isOnRotation())
				Pyramid::getInstance()->isOnRotation() = true;
			Pyramid::getInstance()->getAxis() = Axis::X;
			Pyramid::getInstance()->getDirection() = Direction::POSITIVE;
			break;
		default:
			break;
		}
		break;
	case 'X':
		switch (shape)
		{
		case Shape::NONE:
			break;
		case Shape::CUBE:
			if (!Cube::getInstance()->isOnRotation())
				Cube::getInstance()->isOnRotation() = true;
			Cube::getInstance()->getAxis() = Axis::X;
			Cube::getInstance()->getDirection() = Direction::NEGATIVE;
			break;
		case Shape::PYRAMID:
			if (!Pyramid::getInstance()->isOnRotation())
				Pyramid::getInstance()->isOnRotation() = true;
			Pyramid::getInstance()->getAxis() = Axis::X;
			Pyramid::getInstance()->getDirection() = Direction::NEGATIVE;
			break;
		default:
			break;
		}
		break;
	case 'y':
		switch (shape)
		{
		case Shape::NONE:
			break;
		case Shape::CUBE:
			if (!Cube::getInstance()->isOnRotation())
				Cube::getInstance()->isOnRotation() = true;
			Cube::getInstance()->getAxis() = Axis::Y;
			Cube::getInstance()->getDirection() = Direction::POSITIVE;
			break;
		case Shape::PYRAMID:
			if (!Pyramid::getInstance()->isOnRotation())
				Pyramid::getInstance()->isOnRotation() = true;
			Pyramid::getInstance()->getAxis() = Axis::Y;
			Pyramid::getInstance()->getDirection() = Direction::POSITIVE;
			break;
		default:
			break;
		}
		break;
	case 'Y':
		switch (shape)
		{
		case Shape::NONE:
			break;
		case Shape::CUBE:
			if (!Cube::getInstance()->isOnRotation())
				Cube::getInstance()->isOnRotation() = true;
			Cube::getInstance()->getAxis() = Axis::Y;
			Cube::getInstance()->getDirection() = Direction::NEGATIVE;
			break;
		case Shape::PYRAMID:
			if (!Pyramid::getInstance()->isOnRotation())
				Pyramid::getInstance()->isOnRotation() = true;
			Pyramid::getInstance()->getAxis() = Axis::Y;
			Pyramid::getInstance()->getDirection() = Direction::NEGATIVE;
			break;
		default:
			break;
		}
		break;
	case 's':
		switch (shape)
		{
		case Shape::NONE:
			break;
		case Shape::CUBE:
			if (Cube::getInstance()->isOnRotation())
				Cube::getInstance()->isOnRotation() = false;
			Cube::getInstance()->getAxis() = Axis::NONE;
			Cube::getInstance()->getDirection() = Direction::NONE;
			break;
		case Shape::PYRAMID:
			if (Pyramid::getInstance()->isOnRotation())
				Pyramid::getInstance()->isOnRotation() = false;
			Pyramid::getInstance()->getAxis() = Axis::NONE;
			Pyramid::getInstance()->getDirection() = Direction::NONE;
			break;
		default:
			break;
		}
		shape = Shape::NONE;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

GLvoid TimerFunc(int)
{
	Camera::getInstance()->update();
	Cube::getInstance()->update();
	Pyramid::getInstance()->update();
	glutTimerFunc(10, TimerFunc, 1);
	glutPostRedisplay();
}