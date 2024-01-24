#include "pch.h"
enum class RenderType { Solid = 0, Wire };
enum class ProjectionType { Ortho = 0, Perspective };
std::mt19937 mersenne{ std::random_device{}() };
std::uniform_real_distribution<GLfloat> urd{ 0.0f,1.0f };
std::uniform_real_distribution<GLfloat> randomDegree{ 0.0f,359.0f };
std::uniform_real_distribution<GLfloat> randomMoveAmount{ 1.0f,4.0f };
enum { MaxDegree = 360 };

class Shader;

class Planet {
private:
	friend class Shader;
	GLUquadric* pObj;
	glm::vec3 positionVector{ 0.0f,0.0f,0.0f };
	RenderType planetRenderType{ RenderType::Wire };
	std::vector<float> pointsVertexes;
	std::vector<float> pointsColors;
	GLfloat planetRadian{ 0.0f };
	GLfloat orbitRadian{ 0.0f };
	GLfloat revolutionDegree{ 0.0f };
	GLfloat distanceFromParentPlanet{ 0.0f };
	GLfloat moveAmount{ randomMoveAmount(mersenne) };
	glm::vec3 planetColor{ 1.0f,1.0f,0.0f };
	const float PI = 3.141592f;
	const float deg2Rad = PI / 180.0f;
	bool onRevolution{ false };
private:
public:
	Planet(const GLfloat& pRadian, const GLfloat& oRadian, const GLfloat& revDegree, const GLfloat& distance)
		: planetRadian{ pRadian }, orbitRadian{ oRadian }, revolutionDegree{ revDegree },
		distanceFromParentPlanet{ distance }, pObj{ gluNewQuadric() }
	{
		gluQuadricNormals(pObj, GLU_SMOOTH);
		gluQuadricOrientation(pObj, GLU_OUTSIDE);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_3D);
		glColor3f(0.0f, 0.0f, 1.0f);
	}

	glm::vec3& getPositionVector() { return positionVector; }

	GLfloat& getRevolutionDegree() { return revolutionDegree; }

	const GLfloat& getDistanceFromParentPlanet() const { return distanceFromParentPlanet; }

	GLfloat& getMoveAmount() { return moveAmount; }

	RenderType& getPlanetRenderType() { return planetRenderType; }

	bool& isOnRevolution() { return onRevolution; }

	void renderPlanet() const
	{
		switch (planetRenderType)
		{
		case RenderType::Solid:
			gluQuadricDrawStyle(pObj, GLU_FILL);
			break;
		case RenderType::Wire:
			gluQuadricDrawStyle(pObj, GLU_LINE);
			break;
		default:
			break;
		}
		gluSphere(pObj, planetRadian, 50, 50);
	}
};

Planet* pCenterPlanet;
Planet* pNormalPlanet[3];
Planet* pMiniPlanet[3];

class Orbit {
private:
	friend class Shader;
	GLfloat vertex[3]{ 0.0f,0.0f,0.0f };
	GLfloat color[3]{ 0.0f,0.0f,1.0f };
	GLfloat degree{ 0.0f };
public:
	Orbit()
	{

	}

	void setDegree(const GLfloat& degreeIn) { degree = degreeIn; }

	const GLfloat& getDegree() const { return degree; };

	void render() const
	{
		glPointSize(2.0f);
		glDrawArrays(GL_POINTS, 0, 1);
	}
};

Orbit* centerXYOrbit[360];
Orbit* centerCWXYOrbit[360];
Orbit* centerCCWXYOrbit[360];
Orbit* normalXYPlanetOrbit[360];
Orbit* normalCCWXYPlanetOrbit[360];
Orbit* normalCWXYPlanetOrbit[360];

class Shader {
private:
	friend class Orbit;
	static Shader* pInst;
	enum { MaxVao = 2160, MaxVbo = 4320, MaxEbo = 1 };
private:
	GLuint* vao, * vbo, * ebo;
	GLchar* vertexSource, * fragmentSource;
	GLchar vertexShader, fragmentShader;
	GLuint shaderProgram;
private:
	Shader()
	{
		vao = new GLuint[MaxVao];
		vbo = new GLuint[MaxVbo];
		ebo = new GLuint[MaxEbo];
	}
public:
	static Shader* getInstance()
	{
		if (nullptr == pInst)
			pInst = new Shader;

		return pInst;
	}

	~Shader()
	{
		safeDeleteArray(vao);
		safeDeleteArray(vbo);
		safeDeleteArray(ebo);
	}

	GLuint& getShaderProgram()
	{
		return shaderProgram;
	}

	decltype(auto) getVao()
	{
		return vao;
	}

	char* file2Buffer(const char* file)
	{
		FILE* fptr;
		long length;
		char* buf;

		fptr = fopen(file, "rb");
		if (!fptr)
			return NULL;
		fseek(fptr, 0, SEEK_END);
		length = ftell(fptr);
		buf = (char*)malloc(length + 1);
		fseek(fptr, 0, SEEK_SET);
		fread(buf, length, 1, fptr);
		fclose(fptr);
		buf[length] = 0;

		return buf;
	}

	void makeVertexShader()
	{
		vertexSource = file2Buffer("vertex.glsl");

		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertexShader, 1, (const GLchar**)(&vertexSource), 0);

		glCompileShader(vertexShader);

		checkCompileError(vertexShader, "vertex");
	}

	void makeFragmentShader()
	{
		fragmentSource = file2Buffer("fragment.glsl");

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(fragmentShader, 1, (const GLchar**)(&fragmentSource), 0);

		glCompileShader(fragmentShader);

		checkCompileError(fragmentShader, "fragment");
	}

	void checkCompileError(const GLuint& shaderType, const char* name)
	{
		GLint result;

		GLchar errorLog[512];

		glGetShaderiv(shaderType, GL_COMPILE_STATUS, &result);

		if (!result) {
			glGetShaderInfoLog(shaderType, 512, NULL, errorLog);
			std::cerr << "ERROR:" << name << " complie Failed!\n" << errorLog << std::endl;
		}
	}

	void glGenerate()
	{
		glGenVertexArrays(MaxVao, vao);
		glGenBuffers(MaxVbo, vbo);
		glGenBuffers(MaxEbo, ebo);
	}

	// **************************************************************************************************************************************
	void initBuffer()
	{
		for (int i = 0; i < MaxDegree; ++i) {
			glBindVertexArray(vao[i]);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[i * 2]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(centerXYOrbit[i]->vertex), centerXYOrbit[i]->vertex, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[i * 2 + 1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(centerXYOrbit[i]->color), centerXYOrbit[i]->color, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);

			glBindVertexArray(vao[i + (1 * 360)]);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[(i + (1 * 360)) * 2]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(centerCCWXYOrbit[i]->vertex), centerCCWXYOrbit[i]->vertex, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[(i + (1 * 360)) * 2 + 1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(centerCCWXYOrbit[i]->color), centerCCWXYOrbit[i]->color, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);

			glBindVertexArray(vao[i + 2 * 360]);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[(i + 2 * 360) * 2]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(centerCWXYOrbit[i]->vertex), centerCWXYOrbit[i]->vertex, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[(i + 2 * 360) * 2 + 1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(centerCWXYOrbit[i]->color), centerCWXYOrbit[i]->color, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);

			glBindVertexArray(vao[i + 3 * 360]);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[(i + 3 * 360) * 2]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(normalXYPlanetOrbit[i]->vertex), normalXYPlanetOrbit[i]->vertex, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[(i + 3 * 360) * 2 + 1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(normalXYPlanetOrbit[i]->color), normalXYPlanetOrbit[i]->color, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);


			glBindVertexArray(vao[i + 4 * 360]);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[(i + 4 * 360) * 2]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(normalCCWXYPlanetOrbit[i]->vertex), normalCCWXYPlanetOrbit[i]->vertex, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[(i + 4 * 360) * 2 + 1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(normalCCWXYPlanetOrbit[i]->color), normalCCWXYPlanetOrbit[i]->color, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);

			glBindVertexArray(vao[i + 5 * 360]);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[(i + 5 * 360) * 2]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(normalCWXYPlanetOrbit[i]->vertex), normalCWXYPlanetOrbit[i]->vertex, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[(i + 5 * 360) * 2 + 1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(normalCWXYPlanetOrbit[i]->color), normalCWXYPlanetOrbit[i]->color, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);

		}
	}
	// **************************************************************************************************************************************


	void initShader()
	{
		makeVertexShader();
		makeFragmentShader();

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		checkCompileError(shaderProgram, "shader program");

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glUseProgram(shaderProgram);
	}

	template<typename T>
	void safeDeleteArray(T* ptr)
	{
		if (nullptr != ptr) {
			delete[] ptr;
			//ptr = nullptr;
		}
	}
};

class Camera {
private:
	glm::vec3 positionVector{ glm::vec3{0.0f,0.0f,1.0f} };
	glm::vec3 targetVector{ glm::vec3{0.0f,0.0f,0.0f} };
	glm::vec3 directionVector{ glm::normalize(targetVector - positionVector) };
	glm::vec3 defaultUpVector{ glm::vec3{0.0f, 1.0f, 0.0f} };
	glm::vec3 rightVector{ glm::normalize(glm::cross(defaultUpVector,directionVector)) };
	glm::vec3 upVector{ glm::cross(directionVector,rightVector) };
public:
	glm::vec3& getPositionVector() { return positionVector; }
	glm::vec3& getTargetVector() { return targetVector; }
	glm::vec3& getDirectionVector() { return directionVector; }
	glm::vec3& getUpVector() { return upVector; }
};

constexpr GLuint wWidth{ 800 };
constexpr GLuint wHeight{ 600 };
GLfloat testDegree{ 0.0f };
Shader* Shader::pInst = nullptr;
Camera* pCamera;
ProjectionType projectionType{ ProjectionType::Perspective };
GLvoid RenderScene();
GLvoid Reshape(int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid TimerFunc(int);

int main(int argc, char** argv)
{
	constexpr unsigned winXPos = 0;
	constexpr unsigned winYPos = 0;
	const char winName[]{ "Example" };
	GLfloat degree{ 0.0f };
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

	pCenterPlanet = new Planet(0.5f, 1.0f, 0.0f, 0.0f);
	for (int i = 0; i < 3; ++i) {
		pNormalPlanet[i] = new Planet(0.3f, 1.0f, randomDegree(mersenne), 1.5f);
		pMiniPlanet[i] = new Planet(0.1f, 1.0f, randomDegree(mersenne), 0.6f);
	}

	for (int i = 0; i < MaxDegree; ++i) {
		centerXYOrbit[i] = new Orbit;
		centerCCWXYOrbit[i] = new Orbit;
		centerCWXYOrbit[i] = new Orbit;
		normalXYPlanetOrbit[i] = new Orbit;
		normalCCWXYPlanetOrbit[i] = new Orbit;
		normalCWXYPlanetOrbit[i] = new Orbit;

		centerXYOrbit[i]->setDegree(degree);
		centerCCWXYOrbit[i]->setDegree(degree);
		centerCWXYOrbit[i]->setDegree(degree);
		normalXYPlanetOrbit[i]->setDegree(degree);
		normalCCWXYPlanetOrbit[i]->setDegree(degree);
		normalCWXYPlanetOrbit[i]->setDegree(degree);

		degree += 1.0f;
	}

	pNormalPlanet[0]->getPositionVector() = glm::vec3(-2.0f, 0.0f, 0.0f);
	pNormalPlanet[1]->getPositionVector() = glm::vec3(-1.0f, 0.0f, 0.0f);
	pNormalPlanet[2]->getPositionVector() = glm::vec3(1.0f, 0.0f, 0.0f);

	pCamera = new Camera;
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
	Shader::getInstance()->initBuffer();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// ---------------------------------------------------------------------------------------------------------------------------------------
	glm::mat4 viewMatrix{ 1.0f };
	glm::mat4 projectionMatrix{ 1.0f };
	viewMatrix = glm::lookAt(pCamera->getPositionVector(), pCamera->getDirectionVector(), pCamera->getUpVector());
	if (ProjectionType::Ortho == projectionType)
		projectionMatrix = glm::ortho(-3.0f, 3.0f, -3.0f, 3.0f, -3.0f, 3.0f);
	if (ProjectionType::Perspective == projectionType) {
		projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 50.0f);
		projectionMatrix = glm::translate(projectionMatrix, glm::vec3(0.0f, 0.0f, -5.0f));
	}
	unsigned int viewTrasnformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "viewTransform");
	unsigned int projectionTransformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "projectionTransform");
	glUniformMatrix4fv(viewTrasnformLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
	// ---------------------------------------------------------------------------------------------------------------------------------------
	
	
	glm::mat4 centerPlanetTransformMatrix{ 1.0f };
	// centerPlanet
	{
		glm::mat4 parentMatrix{ 1.0f };
		glm::mat4 revolutionMatrix{ 1.0f };
		glm::mat4 translationMatrix{ 1.0f };
		glm::mat4 rotationMatrix{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		translationMatrix = glm::translate(translationMatrix, glm::vec3(pCenterPlanet->getPositionVector()));
		revolutionMatrix = glm::rotate(revolutionMatrix, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		centerPlanetTransformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
		unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(centerPlanetTransformMatrix));
		pCenterPlanet->renderPlanet();

		glm::mat4 orbitXZTransformMatrix{ 1.0f };
		glm::mat4 orbitParentMatrix{ 1.0f };
		glm::mat4 orbitTranslationMatrix{ 1.0f };

		glm::mat4 orbitCCWXZTransformMatrix{ 1.0f };
		glm::mat4 orbitCCWXZParentMatrix{ 1.0f };
		glm::mat4 orbitCCWXZTranslationMatrix{ 1.0f };
		glm::mat4 orbitCCWXZRevolutionMatrix{ 1.0f };

		glm::mat4 orbitCWXZTransformMatrix{ 1.0f };
		glm::mat4 orbitCWXZParentMatrix{ 1.0f };
		glm::mat4 orbitCWXZTranslationMatrix{ 1.0f };
		glm::mat4 orbitCWXZRevolutionMatrix{ 1.0f };
		
		// XZORBIT
		for (int i = 0; i < 360; ++i) {
			orbitParentMatrix = centerPlanetTransformMatrix;
			orbitParentMatrix = glm::translate(orbitParentMatrix, glm::vec3(0.0f, 0.0f, -1.0f));
			orbitTranslationMatrix = glm::translate(orbitTranslationMatrix, glm::vec3(0.025f * std::cosf(glm::radians(centerXYOrbit[i]->getDegree())),
				0.0f, 0.025f * std::sinf(glm::radians(normalXYPlanetOrbit[i]->getDegree()))));
			orbitXZTransformMatrix = orbitParentMatrix * orbitTranslationMatrix;
			transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(orbitXZTransformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[i]);
			centerXYOrbit[i]->render();
		}

		// XZCCWORBIT
		for (int i = 0; i < 360; ++i) {
			orbitCCWXZParentMatrix = centerPlanetTransformMatrix;
			orbitCCWXZParentMatrix = glm::rotate(orbitCCWXZParentMatrix, glm::radians(45.0f), glm::vec3(1.0, 0.0f, 0.0f));
			orbitCCWXZParentMatrix = glm::translate(orbitCCWXZParentMatrix, glm::vec3(0.0f, -0.5f, 0.0f));
			orbitCCWXZTranslationMatrix = glm::translate(orbitCCWXZTranslationMatrix, glm::vec3(0.025f * std::cosf(glm::radians(centerCCWXYOrbit[i]->getDegree())),
				0.003f * std::sinf(glm::radians(centerCCWXYOrbit[i]->getDegree())), 0.015f * std::cosf(glm::radians(centerCCWXYOrbit[i]->getDegree()))));
			orbitCCWXZTransformMatrix = orbitCCWXZParentMatrix * orbitCCWXZRevolutionMatrix * orbitCCWXZTranslationMatrix;
			transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(orbitCCWXZTransformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[i + (360 * 1)]);
			centerCCWXYOrbit[i]->render();
		}

		// XZCWORBIT
		for (int i = 0; i < 360; ++i) {
			orbitCWXZParentMatrix = centerPlanetTransformMatrix;
			orbitCWXZParentMatrix = glm::rotate(orbitCWXZParentMatrix, glm::radians(-45.0f), glm::vec3(1.0, 0.0f, 0.0f));
			orbitCWXZParentMatrix = glm::translate(orbitCWXZParentMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
			orbitCWXZTranslationMatrix = glm::translate(orbitCWXZTranslationMatrix, glm::vec3(0.025f * std::cosf(glm::radians(centerCWXYOrbit[i]->getDegree())),
				0.015f * std::cosf(glm::radians(centerCWXYOrbit[i]->getDegree())), 0.003f * std::sinf(glm::radians(centerCWXYOrbit[i]->getDegree()))));
			orbitCWXZTransformMatrix = orbitCWXZParentMatrix * orbitCWXZRevolutionMatrix * orbitCWXZTranslationMatrix;
			transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(orbitCWXZTransformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[i + (360 * 2)]);
			centerCWXYOrbit[i]->render();
		}
	}

	// XZ
	// Normal 1, Mini 1

	 {
		// Normal 1
		glm::mat4 normal1TransformMatrix{ 1.0f };
		glm::mat4 normal1ParentMatrix{ 1.0f };
		glm::mat4 normal1RevolutionMatrix{ 1.0f };
		glm::mat4 revolutionToMini{ 1.0f };
		glm::mat4 normal1TranslationMatrix{ 1.0f };
		glm::mat4 normal1RotationMatrix{ 1.0f };
		glm::mat4 normal1ScaleMatrix{ 1.0f };
		glm::mat4 normal1ToMini1{ 1.0f };
		normal1ParentMatrix = centerPlanetTransformMatrix;
		normal1TranslationMatrix = glm::translate(normal1TranslationMatrix, glm::vec3(pNormalPlanet[0]->getPositionVector()));
		normal1TransformMatrix = normal1ParentMatrix * normal1RevolutionMatrix * normal1TranslationMatrix * normal1RotationMatrix * normal1ScaleMatrix;
		unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(normal1TransformMatrix));
		pNormalPlanet[0]->renderPlanet();

		// Mini 1
		glm::mat4 mini1TransformMatrix{ 1.0f };
		glm::mat4 mini1ParentMatrix{ 1.0f };
		glm::mat4 mini1RevolutionMatrix{ 1.0f };
		glm::mat4 mini1TranslationMatrix{ 1.0f };
		glm::mat4 mini1RotationMatrix{ 1.0f };
		glm::mat4 miniScaleMatrix{ 1.0f };
		mini1ParentMatrix = normal1TransformMatrix;
		mini1TranslationMatrix = glm::translate(mini1TranslationMatrix, glm::vec3(pMiniPlanet[0]->getPositionVector()));
		mini1TransformMatrix = mini1ParentMatrix * mini1RevolutionMatrix * mini1TranslationMatrix * mini1RotationMatrix * miniScaleMatrix;
		transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(mini1TransformMatrix));
		pMiniPlanet[0]->renderPlanet();

		// Normal1 Orbit
		glm::mat4 normalXZOrbitTransformMatrix{ 1.0f };
		glm::mat4 normalXZOrbitParentMatrix{ 1.0f };
		glm::mat4 normalXZOrbitTranslationMatrix{ 1.0f };
		for (int i = 0; i < 360; ++i) {
			normalXZOrbitParentMatrix = normal1TransformMatrix;
			normalXZOrbitParentMatrix = glm::translate(normalXZOrbitParentMatrix, glm::vec3(0.0f, 0.0f, -0.5f));
			normalXZOrbitTranslationMatrix = glm::translate(normalXZOrbitTranslationMatrix, glm::vec3(0.010f * std::cosf(glm::radians(normalXYPlanetOrbit[i]->getDegree())),
				0.0f, 0.010f * std::sinf(glm::radians(normalXYPlanetOrbit[i]->getDegree()))));
			normalXZOrbitTransformMatrix = normalXZOrbitParentMatrix * normalXZOrbitTranslationMatrix;
			transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(normalXZOrbitTransformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[i + 3 * 360]);
			normalXYPlanetOrbit[i]->render();
		}
	}


	// CCW
	// Normal2, Mini 2
	{
		// Normal 2
		glm::mat4 normal1TransformMatrix{ 1.0f };
		glm::mat4 normal1ParentMatrix{ 1.0f };
		glm::mat4 normal1RevolutionMatrix{ 1.0f };
		glm::mat4 revolutionToMini{ 1.0f };
		glm::mat4 normal1TranslationMatrix{ 1.0f };
		glm::mat4 normal1RotationMatrix{ 1.0f };
		glm::mat4 normal1ScaleMatrix{ 1.0f };
		glm::mat4 normal1ToMini1{ 1.0f };
		normal1ParentMatrix = centerPlanetTransformMatrix;
		normal1RevolutionMatrix = glm::rotate(normal1RevolutionMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		normal1TranslationMatrix = glm::translate(normal1TranslationMatrix, glm::vec3(pNormalPlanet[1]->getPositionVector()));
		normal1TransformMatrix = normal1ParentMatrix * normal1RevolutionMatrix * normal1TranslationMatrix * normal1RotationMatrix * normal1ScaleMatrix;
		unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(normal1TransformMatrix));
		pNormalPlanet[1]->renderPlanet();

		// Mini 2
		glm::mat4 mini1TransformMatrix{ 1.0f };
		glm::mat4 mini1ParentMatrix{ 1.0f };
		glm::mat4 mini1RevolutionMatrix{ 1.0f };
		glm::mat4 mini1TranslationMatrix{ 1.0f };
		glm::mat4 mini1RotationMatrix{ 1.0f };
		glm::mat4 miniScaleMatrix{ 1.0f };
		mini1ParentMatrix = normal1TransformMatrix;
		mini1RevolutionMatrix = glm::rotate(mini1RevolutionMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		mini1TranslationMatrix = glm::translate(mini1TranslationMatrix, glm::vec3(pMiniPlanet[1]->getPositionVector()));
		mini1TransformMatrix = mini1ParentMatrix * mini1RevolutionMatrix * mini1TranslationMatrix * mini1RotationMatrix * miniScaleMatrix;
		transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(mini1TransformMatrix));
		pMiniPlanet[1]->renderPlanet();

		// CCWPLANET ORBIT
		glm::mat4 normalCWXZOrbitTransformMatrix{ 1.0f };
		glm::mat4 normalCWXZOrbitParentMatrix{ 1.0f };
		glm::mat4 normalCWXZOrbitTranslationMatrix{ 1.0f };

		for (int i = 0; i < 360; ++i) {
			normalCWXZOrbitParentMatrix = normal1TransformMatrix;
			normalCWXZOrbitParentMatrix = glm::translate(normalCWXZOrbitParentMatrix, glm::vec3(-0.1f, -0.3f, -0.5f));
			normalCWXZOrbitParentMatrix = glm::rotate(normalCWXZOrbitParentMatrix, glm::radians(-45.0f), (glm::vec3(1.0f, 0.0f, 1.0f)));
			normalCWXZOrbitTranslationMatrix = glm::translate(normalCWXZOrbitTranslationMatrix, glm::vec3(0.01f * std::cosf(glm::radians(normalCWXYPlanetOrbit[i]->getDegree())),
				0.0f, 0.01f * std::sinf(glm::radians(normalCWXYPlanetOrbit[i]->getDegree()))));
			normalCWXZOrbitTransformMatrix = normalCWXZOrbitParentMatrix * normalCWXZOrbitTranslationMatrix;
			transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(normalCWXZOrbitTransformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[i + 4 * 360]);
			normalCWXYPlanetOrbit[i]->render();
		}

	}
	//// CW
	{
	// Normal2 
		glm::mat4 normal1TransformMatrix{ 1.0f };
		glm::mat4 normal1ParentMatrix{ 1.0f };
		glm::mat4 normal1RevolutionMatrix{ 1.0f };
		glm::mat4 revolutionToMini{ 1.0f };
		glm::mat4 normal1TranslationMatrix{ 1.0f };
		glm::mat4 normal1RotationMatrix{ 1.0f };
		glm::mat4 normal1ScaleMatrix{ 1.0f };
		glm::mat4 normal1ToMini1{ 1.0f };
		normal1ParentMatrix = centerPlanetTransformMatrix;
		normal1RotationMatrix = glm::rotate(normal1RotationMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		normal1TranslationMatrix = glm::translate(normal1TranslationMatrix, glm::vec3(pNormalPlanet[2]->getPositionVector()));
		normal1TransformMatrix = normal1ParentMatrix * normal1RevolutionMatrix * normal1TranslationMatrix * normal1RotationMatrix * normal1ScaleMatrix;
		unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(normal1TransformMatrix));
		pNormalPlanet[2]->renderPlanet();

		// Mini 2
		glm::mat4 mini1TransformMatrix{ 1.0f };
		glm::mat4 mini1ParentMatrix{ 1.0f };
		glm::mat4 mini1RevolutionMatrix{ 1.0f };
		glm::mat4 mini1TranslationMatrix{ 1.0f };
		glm::mat4 mini1RotationMatrix{ 1.0f };
		glm::mat4 miniScaleMatrix{ 1.0f };
		mini1ParentMatrix = normal1TransformMatrix;
		mini1RevolutionMatrix = glm::rotate(mini1RevolutionMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		mini1TranslationMatrix = glm::translate(mini1TranslationMatrix, glm::vec3(pMiniPlanet[2]->getPositionVector()));
		mini1TransformMatrix = mini1ParentMatrix * mini1RevolutionMatrix * mini1TranslationMatrix * mini1RotationMatrix * miniScaleMatrix;
		transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(mini1TransformMatrix));
		pMiniPlanet[2]->renderPlanet();

		glm::mat4 normalCCWXZOrbitTransformMatrix{ 1.0f };
		glm::mat4 normalCCWXZOrbitParentMatrix{ 1.0f };
		glm::mat4 normalCCWXZOrbitTranslationMatrix{ 1.0f };
		glm::mat4 normalCCWXZOrbitRevolutionMatrix{ 1.0f };

		// CWPLANET ORBIT
		for (int i = 0; i < 360; ++i) {
			normalCCWXZOrbitParentMatrix = normal1TransformMatrix;
			normalCCWXZOrbitParentMatrix = glm::translate(normalCCWXZOrbitParentMatrix, glm::vec3(-0.1f, 0.3f, -0.5f));
			normalCCWXZOrbitParentMatrix = glm::rotate(normalCCWXZOrbitParentMatrix, glm::radians(45.0f), (glm::vec3(1.0f, 0.0f, 1.0f)));
			normalCCWXZOrbitTranslationMatrix = glm::translate(normalCCWXZOrbitTranslationMatrix, glm::vec3(0.010f * std::cosf(glm::radians(normalCCWXYPlanetOrbit[i]->getDegree())),
				0.0f, 0.010f * std::sinf(glm::radians(normalCCWXYPlanetOrbit[i]->getDegree()))));
			normalCCWXZOrbitTransformMatrix = normalCCWXZOrbitParentMatrix * normalCCWXZOrbitTranslationMatrix;
			transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(normalCCWXZOrbitTransformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[i + 5 * 360]);
			normalCCWXYPlanetOrbit[i]->render();
		}
	}
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid TimerFunc(int value)
{
	for (int i = 0; i < 3; ++i) {
		if (pNormalPlanet[i]->getRevolutionDegree() < 359.0f) {
			pNormalPlanet[i]->getRevolutionDegree() += pNormalPlanet[i]->getMoveAmount();
		}
		else {
			pNormalPlanet[i]->getRevolutionDegree() = 0.0f;
		}

		switch (i)
		{
		case 0: // XZ
			pNormalPlanet[i]->getPositionVector().x = pNormalPlanet[i]->getDistanceFromParentPlanet() * cosf(glm::radians(pNormalPlanet[i]->getRevolutionDegree()));
			pNormalPlanet[i]->getPositionVector().y = 0.0f;
			pNormalPlanet[i]->getPositionVector().z = pNormalPlanet[i]->getDistanceFromParentPlanet() * sinf(glm::radians(pNormalPlanet[i]->getRevolutionDegree()));
			break;
		case 1:// CCWXZ
			pNormalPlanet[i]->getPositionVector().x = pNormalPlanet[i]->getDistanceFromParentPlanet() * cosf(glm::radians(pNormalPlanet[i]->getRevolutionDegree()));
			pNormalPlanet[i]->getPositionVector().y = pNormalPlanet[i]->getDistanceFromParentPlanet() * sinf(glm::radians(pNormalPlanet[i]->getRevolutionDegree()));
			pNormalPlanet[i]->getPositionVector().z = pNormalPlanet[i]->getDistanceFromParentPlanet() * cosf(glm::radians(pNormalPlanet[i]->getRevolutionDegree()));
			break;
		case 2:// CWXZ
			pNormalPlanet[i]->getPositionVector().x = pNormalPlanet[i]->getDistanceFromParentPlanet() * cosf(glm::radians(pNormalPlanet[i]->getRevolutionDegree()));
			pNormalPlanet[i]->getPositionVector().y = pNormalPlanet[i]->getDistanceFromParentPlanet() * cosf(glm::radians(pNormalPlanet[i]->getRevolutionDegree()));
			pNormalPlanet[i]->getPositionVector().z = pNormalPlanet[i]->getDistanceFromParentPlanet() * sinf(glm::radians(pNormalPlanet[i]->getRevolutionDegree()));
			break;
		default:
			break;
		}

		if (pMiniPlanet[i]->getRevolutionDegree() < 359.0f) {
			pMiniPlanet[i]->getRevolutionDegree() += pMiniPlanet[i]->getMoveAmount();
		}
		else {
			pMiniPlanet[i]->getRevolutionDegree() = 0.0f;
		}
		pMiniPlanet[i]->getPositionVector().x = pMiniPlanet[i]->getDistanceFromParentPlanet() * cosf(glm::radians(pMiniPlanet[i]->getRevolutionDegree()));
		pMiniPlanet[i]->getPositionVector().y = 0.0f;
		pMiniPlanet[i]->getPositionVector().z = pMiniPlanet[i]->getDistanceFromParentPlanet() * sinf(glm::radians(pMiniPlanet[i]->getRevolutionDegree()));
	}

	glutPostRedisplay();
	glutTimerFunc(10, TimerFunc, 1);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'p':
		projectionType = ProjectionType::Ortho;
		break;
	case 'P':
		projectionType = ProjectionType::Perspective;
		break;
	case 'm':
		pCenterPlanet->getPlanetRenderType() = RenderType::Wire;
		for (int i = 0; i < 3; ++i) {
			pNormalPlanet[i]->getPlanetRenderType() = RenderType::Wire;
			pMiniPlanet[i]->getPlanetRenderType() = RenderType::Wire;
		}
		break;
	case 'M':
		pCenterPlanet->getPlanetRenderType() = RenderType::Solid;
		for (int i = 0; i < 3; ++i) {
			pNormalPlanet[i]->getPlanetRenderType() = RenderType::Solid;
			pMiniPlanet[i]->getPlanetRenderType() = RenderType::Solid;
		}
		break;
	case 'w':
		pCenterPlanet->getPositionVector().y += 0.1f;
		break;
	case 'a':
		pCenterPlanet->getPositionVector().x -= 0.1f;
		break;
	case 's':
		pCenterPlanet->getPositionVector().y -= 0.1f;
		break;
	case 'd':
		pCenterPlanet->getPositionVector().x += 0.1f;
		break;
	case 'z':
		pCenterPlanet->getPositionVector().z += 0.1f;
		break;
	case 'Z':
		pCenterPlanet->getPositionVector().z -= 0.1f;
		break;
	case 'y':
		for (int i = 0; i < 3; ++i) {
			pMiniPlanet[i]->getMoveAmount() = -pMiniPlanet[i]->getMoveAmount();
			pNormalPlanet[i]->getMoveAmount() = -pNormalPlanet[i]->getMoveAmount();
		}
		break;
	case 'Y':
		for (int i = 0; i < 3; ++i) {
			pMiniPlanet[i]->getMoveAmount() = -pMiniPlanet[i]->getMoveAmount();
			pNormalPlanet[i]->getMoveAmount() = -pNormalPlanet[i]->getMoveAmount();
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
}