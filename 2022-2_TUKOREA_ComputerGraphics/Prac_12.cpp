#include "pch.h"

enum class KeyType{ Idle=0, Key_One, Key_Two, Key_Three, Key_Four, Key_Five, Key_Six, Key_Seven,Key_Eight,Key_Nine,Key_Zero,
	Key_A, Key_B, Key_C, Key_E, Key_F, Key_G };

std::mt19937 mersenne{ std::random_device{}() };
std::uniform_real_distribution<GLfloat> urColor{ 0.0f,1.0f };

class Shader;

class CoordSystem {
private:
	friend class Shader;
	static CoordSystem* pInst;
	const GLfloat vertex[6][3]{
		{-1.0f,0.0f,0.0f}, {1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f}, {0.0f,-1.0f,0.0f},
		{0.0f,0.0f,1.0f}, {0.0f,0.0f,-1.0f} };
	const GLfloat color[6][3]{
	{urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)},
	{urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)},
	{urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)} };
private:
	CoordSystem()
	{
		
	}
public:
	static CoordSystem* getInstance()
	{
		if (nullptr == pInst)
			pInst = new CoordSystem;

		return pInst;
	}

	void render() const
	{
		glDrawArrays(GL_LINES, 0, 4);
	}
};

class Hexahedron {
private:
	friend class Shader;
	static Hexahedron* pInst;
	GLfloat vertex[8][3]{
	{-0.5f,0.5f,-0.5f}
	,{-0.5f,0.5f,0.5f}
	,{0.5f,0.5f,0.5f}
	,{0.5f,0.5f,-0.5f}
	,{-0.5f,-0.5f,-0.5f}
	,{-0.5f,-0.5f,0.5f}
	,{0.5f,-0.5f,0.5f}
	,{0.5f,-0.5f,-0.5f} };
	const GLfloat color[8][3]
	{ {urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)}
		, {urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)},
		{urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)},
		{urColor(mersenne),urColor(mersenne),urColor(mersenne)}, {urColor(mersenne),urColor(mersenne),urColor(mersenne)} };
	const unsigned int index[36]{ 0,1,2,0,2,3,4,5,6,4,6,7,0,1,5,0,5,4,3,2,6,3,6,7,1,5,6,1,6,2,0,4,7,0,7,3 };
private:
	Hexahedron()
	{

	}
public:
	static Hexahedron* getInstance()
	{
		if (nullptr == pInst)
			pInst = new Hexahedron;

		return pInst;
	}

	void render(const int& index) const
	{
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>(index * sizeof(int)));
	}
};

class Tetrahedron {
private:
	friend class Shader;
	static Tetrahedron* pInst;
	GLfloat vertex[4][3]{
		{0.0f,0.5f,0.0f},
		{0.0f,-0.5f,-0.5f},
		{-0.5f,-0.5f, +0.5f},
		{0.5f, -0.5f, +0.5f}
	};
	const GLfloat color[4][3]{ {urColor(mersenne),urColor(mersenne),urColor(mersenne)} ,{urColor(mersenne),urColor(mersenne),urColor(mersenne)} ,
		{urColor(mersenne),urColor(mersenne),urColor(mersenne)} ,{urColor(mersenne),urColor(mersenne),urColor(mersenne)} };
	const unsigned int index[12]{ 0,2,1,0,2,3,0,3,1,1,2,3 };
private:
	Tetrahedron()
	{

	}
public:
	static Tetrahedron* getInstance()
	{
		if (nullptr == pInst)
			pInst = new Tetrahedron;

		return pInst;
	}

	void render(const int& index) const
	{
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, reinterpret_cast<void*>(index * sizeof(int)));
	}
};

class Shader {
private:
	friend class CoordSystem;
	friend class Hexahedron;
	friend class Tetrahedron;
	static Shader* pInst;
	enum { MaxVao = 3, MaxVbo = 6, MaxEbo = 2 };
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

	// ***************************************************************************************************
	void initBuffer()
	{
		glBindVertexArray(vao[0]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CoordSystem::getInstance()->vertex), CoordSystem::getInstance()->vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CoordSystem::getInstance()->color), CoordSystem::getInstance()->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[1]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Hexahedron::getInstance()->vertex), Hexahedron::getInstance()->vertex, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Hexahedron::getInstance()->index), Hexahedron::getInstance()->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Hexahedron::getInstance()->color), Hexahedron::getInstance()->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[2]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Tetrahedron::getInstance()->vertex), Tetrahedron::getInstance()->vertex, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Tetrahedron::getInstance()->index), Tetrahedron::getInstance()->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Tetrahedron::getInstance()->color), Tetrahedron::getInstance()->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}
	// ***************************************************************************************************

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
			ptr = nullptr;
		}
	}
};

constexpr GLuint wWidth{ 800 };
constexpr GLuint wHeight{ 600 };

Shader* Shader::pInst = nullptr;
CoordSystem* CoordSystem::pInst = nullptr;
Hexahedron* Hexahedron::pInst = nullptr;
Tetrahedron* Tetrahedron::pInst = nullptr;
KeyType keyType{ KeyType::Idle };


GLvoid RenderScene();
GLvoid Reshape(int, int);
GLvoid Keyboard(unsigned char, int, int);

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

	Shader::getInstance()->glGenerate();
	Shader::getInstance()->initBuffer();
	Shader::getInstance()->initShader();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}

GLvoid RenderScene()
{
	Shader::getInstance()->initBuffer();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 model = glm::mat4(1.0f);
	glEnable(GL_DEPTH_TEST);
	unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "model");
	{
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(Shader::getInstance()->getVao()[0]);
		CoordSystem::getInstance()->render();
	}

	model = glm::rotate(model, glm::radians(10.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
	model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(model));

	switch (keyType)
	{
	case KeyType::Idle:
		break;
	case KeyType::Key_One:
		glBindVertexArray(Shader::getInstance()->getVao()[1]);
		Hexahedron::getInstance()->render(0);
		break;
	case KeyType::Key_Two:
		glBindVertexArray(Shader::getInstance()->getVao()[1]);
		Hexahedron::getInstance()->render(6);
		break;
	case KeyType::Key_Three:
		glBindVertexArray(Shader::getInstance()->getVao()[1]);
		Hexahedron::getInstance()->render(12);
		break;
	case KeyType::Key_Four:
		glBindVertexArray(Shader::getInstance()->getVao()[1]);
		Hexahedron::getInstance()->render(18);
		break;
	case KeyType::Key_Five:
		glBindVertexArray(Shader::getInstance()->getVao()[1]);
		Hexahedron::getInstance()->render(24);
		break;
	case KeyType::Key_Six:
		glBindVertexArray(Shader::getInstance()->getVao()[1]);
		Hexahedron::getInstance()->render(30);
		break;
	case KeyType::Key_Seven:
		glBindVertexArray(Shader::getInstance()->getVao()[2]);
		Tetrahedron::getInstance()->render(0);
		break;
	case KeyType::Key_Eight:
		glBindVertexArray(Shader::getInstance()->getVao()[2]);
		Tetrahedron::getInstance()->render(3);
		break;
	case KeyType::Key_Nine:
		glBindVertexArray(Shader::getInstance()->getVao()[2]);
		Tetrahedron::getInstance()->render(6);
		break;
	case KeyType::Key_Zero:
		glBindVertexArray(Shader::getInstance()->getVao()[2]);
		Tetrahedron::getInstance()->render(9);
		break;
	case KeyType::Key_A:
		glBindVertexArray(Shader::getInstance()->getVao()[1]);
		Hexahedron::getInstance()->render(0);
		Hexahedron::getInstance()->render(6);
		break;
	case KeyType::Key_B:
		glBindVertexArray(Shader::getInstance()->getVao()[1]);
		Hexahedron::getInstance()->render(12);
		Hexahedron::getInstance()->render(18);
		break;
	case KeyType::Key_C:
		glBindVertexArray(Shader::getInstance()->getVao()[1]);
		Hexahedron::getInstance()->render(24);
		Hexahedron::getInstance()->render(30);
		break;
	case KeyType::Key_E:
		glBindVertexArray(Shader::getInstance()->getVao()[2]);
		Tetrahedron::getInstance()->render(0);
		Tetrahedron::getInstance()->render(9);
		break;
	case KeyType::Key_F:
		glBindVertexArray(Shader::getInstance()->getVao()[2]);
		Tetrahedron::getInstance()->render(3);
		Tetrahedron::getInstance()->render(9);
		break;
	case KeyType::Key_G:
		glBindVertexArray(Shader::getInstance()->getVao()[2]);
		Tetrahedron::getInstance()->render(6);
		Tetrahedron::getInstance()->render(9);
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

GLvoid Keyboard(unsigned char key, int w, int h)
{
	switch (key)
	{
	case '1':
		keyType = KeyType::Key_One;
		break;
	case '2':
		keyType = KeyType::Key_Two;
		break;
	case '3':
		keyType = KeyType::Key_Three;
		break;
	case '4':
		keyType = KeyType::Key_Four;
		break;
	case '5':
		keyType = KeyType::Key_Five;
		break;
	case '6':
		keyType = KeyType::Key_Six;
		break;
	case '7':
		keyType = KeyType::Key_Seven;
		break;
	case '8':
		keyType = KeyType::Key_Eight;
		break;
	case '9':
		keyType = KeyType::Key_Nine;
		break;
	case '0':
		keyType = KeyType::Key_Zero;
		break;
	case 'a':
		keyType = KeyType::Key_A;
		break;
	case 'b':
		keyType = KeyType::Key_B;
		break;
	case 'c':
		keyType = KeyType::Key_C;
		break;
	case 'e':
		keyType = KeyType::Key_E;
		break;
	case 'f':
		keyType = KeyType::Key_F;
		break;
	case 'g':
		keyType = KeyType::Key_G;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}