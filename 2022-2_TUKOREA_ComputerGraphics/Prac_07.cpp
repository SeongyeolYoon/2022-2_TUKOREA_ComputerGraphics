#include "pch.h"

class Shader;

class Triangle {
private:
	friend class Shader;
	GLfloat vertex[3][3]{ 0.0f };
	GLfloat color[3][3]{ 0.0f };
	GLfloat degree{ 0.0f };
	GLfloat xMoveAmount{ 0.03f };
	GLfloat yMoveAmount{ 0.03f};
public:
	Triangle()
	{

	}
	void setVertex(const GLfloat& tx, const GLfloat& ty, const GLfloat& tz, const GLfloat& lbx, const GLfloat& lby, const GLfloat& lbz,
		const GLfloat& rbx, const GLfloat& rby, const GLfloat& rbz)
	{
		vertex[0][0] = tx;
		vertex[0][1] = ty;
		vertex[0][2] = tz;
		vertex[1][0] = lbx;
		vertex[1][1] = lby;
		vertex[1][2] = lbz;
		vertex[2][0] = rbx;
		vertex[2][1] = rby;
		vertex[2][2] = rbz;
	}

	void setColor(const GLfloat& vx1, const GLfloat& vy1, const GLfloat& vz1, const GLfloat& vx2, const GLfloat& vy2, const GLfloat& vz2,
		const GLfloat& vx3, const GLfloat& vy3, const GLfloat& vz3)
	{
		color[0][0] = vx1;
		color[0][1] = vy1;
		color[0][2] = vz1;
		color[1][0] = vx2;
		color[1][1] = vy2;
		color[1][2] = vz2;
		color[2][0] = vx3;
		color[2][1] = vy3;
		color[2][2] = vz3;
	}

	void setXMoveAmount(const GLfloat& amount)
	{
		xMoveAmount = amount;
	}

	void setYMoveAmount(const GLfloat& amount)
	{
		yMoveAmount = amount;
	}

	GLfloat& getDegree() 
	{
		return degree;
	}

	decltype(auto) getColor(const int& i)
	{
		return color[i];
	}

	decltype(auto) getVertex(const int& i)
	{
		return vertex[i];
	}

	const GLfloat& getDegree() const
	{
		return degree;
	}

	const GLfloat& getXMoveAmount() const
	{
		return xMoveAmount;
	}

	const GLfloat& getYMoveAmount() const
	{
		return yMoveAmount;
	}

	void render() const
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void move()
	{
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if(0==j)
					vertex[i][j] += xMoveAmount;		
				else if(1==j)
					vertex[i][j] += yMoveAmount;
			}
		}

		// 좌우 충돌
		for (int i = 0; i < 3; ++i) {
			if (vertex[i][0] <= -1.0f) {
				xMoveAmount = -xMoveAmount;
				degree = 270.0f;
			}
			else if (vertex[i][0] >= 1.0f) {
				xMoveAmount = -xMoveAmount;
				degree = 90.0f;
			}
	
		}


		// 상하 충돌
		for (int i = 0; i < 3; ++i) {
			if (vertex[i][1] <= -0.9f) {
				yMoveAmount = -yMoveAmount;
				degree = 0.0f;
			}
			if (vertex[i][1] >= 1.0f) {
				yMoveAmount = -yMoveAmount;
				degree = 180.0f;
			}
		}


	}
};
Triangle* triangles[4];
class Shader {
private:
	friend class Triangle;
	// *******************************
	enum { maxVao = 4, maxVbo =8, maxEbo =1};
	// *******************************
public:
	GLuint* vao, * vbo, * ebo;
	GLchar* vertexSource, * fragmentSource;
	GLchar vertexShader, fragmentShader;
	GLuint shaderProgram;
public:
	Shader() 
	{
		vao = new GLuint[maxVao];
		vbo = new GLuint[maxVbo];
		ebo = new GLuint[maxEbo];
	}

	~Shader()
	{
		safeDeleteArray(vao);
		safeDeleteArray(vbo);
		safeDeleteArray(ebo);
		safeDeleteArray(vertexSource);
		safeDeleteArray(fragmentSource);
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
		glGenVertexArrays(maxVao, vao);
		glGenBuffers(maxVbo, vbo);
		glGenBuffers(maxEbo, ebo);
	}

	// ***************************************************************************************************
	void initBuffer()
	{
		glBindVertexArray(vao[0]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[0]->vertex), triangles[0]->vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[0]->color), triangles[0]->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[1]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[1]->vertex), triangles[1]->vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[1]->color), triangles[1]->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[2]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[2]->vertex), triangles[2]->vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[2]->color), triangles[2]->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[3]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[6]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[3]->vertex), triangles[3]->vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[7]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[3]->color), triangles[3]->color, GL_STATIC_DRAW);
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
	void safeDeleteArray(T* pUint)
	{
		if (pUint) {
			delete[] pUint;
			pUint = nullptr;
		}
	}
};

Shader shader;

bool leftButton{ false };
bool g_isLine{ false };

constexpr unsigned wWidth = 800;
constexpr unsigned wHeight = 600;

constexpr float PI = 3.141592f;
constexpr float deg2Rad = PI / 180.0f;

GLvoid RenderScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid TimerFunc(int);
void ConvertDeviceXYOpenGLXY(int, int, GLfloat*, GLfloat*);

int main(int argc, char** argv)
{
	triangles[0] = new Triangle();
	triangles[0]->setVertex(-0.5f, 0.5f, 0.0f, -0.6f, 0.25f, 0.0f, -0.4f, 0.25f, 0.0f);
	triangles[0]->setColor(1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f);
	triangles[0]->setXMoveAmount(0.1f);
	triangles[0]->setXMoveAmount(0.1f);

	triangles[1] = new Triangle();
	triangles[1]->setVertex( 0.5f,0.5f,0.0f ,0.4f,0.25f,0.0f , 0.6f,0.25f,0.0f);
	triangles[1]->setColor(0.0f,1.0f,0.0f ,0.0f,1.0f,0.0f, 0.0f,1.0f,0.0f);
	triangles[1]->setXMoveAmount(0.15f);
	triangles[1]->setXMoveAmount(0.15f);

	triangles[2] = new Triangle();
	triangles[2]->setVertex(-0.5f,-0.5f,0.0f ,-0.6f,-0.75f,0.0f ,-0.4f,-0.75f,0.0f );
	triangles[2]->setColor(0.0f,0.0f,1.0f ,0.0f,0.0f,1.0f , 0.0f,0.0f,1.0f);
	triangles[2]->setXMoveAmount(0.2f);
	triangles[2]->setXMoveAmount(0.2f);

	triangles[3] = new Triangle();
	triangles[3]->setVertex(0.5f,-0.5f,0.0f , 0.4f,-0.75,0.0f, 0.6f,-0.75f,0.0f);
	triangles[3]->setColor(1.0f,1.0f,1.0f , 1.0f,1.0f,1.0f, 1.0f,1.0f,1.0f);
	triangles[3]->setXMoveAmount(0.25f);
	triangles[3]->setXMoveAmount(0.25f);
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

	shader.glGenerate();
	shader.initBuffer();
	shader.initShader();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunc, 1);
	glutMainLoop();
}

GLvoid RenderScene()
{
	shader.initBuffer();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (g_isLine) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(5.0f);
	}

	for (int i = 0; i < 4; ++i) {
		GLfloat cx = (triangles[i]->getVertex(0)[0] + triangles[i]->getVertex(1)[0] + triangles[i]->getVertex(2)[0]) / 3.0f;
		GLfloat cy = (triangles[i]->getVertex(0)[1] + triangles[i]->getVertex(1)[1] + triangles[i]->getVertex(2)[1]) / 3.0f;
		glm::mat4 rotate = glm::mat4(1.0f);
		glm::mat4 trans1 = glm::mat4(1.0f);
		glm::mat4 trans2 = glm::mat4(1.0f);
		glm::mat4 model = glm::mat4(1.0f);
		trans1 = glm::translate(trans1, glm::vec3(-cx, -cy, 0.0f));
		trans2 = glm::translate(trans2, glm::vec3(+cx, +cy, 0.0f));
		rotate = glm::rotate(rotate, triangles[i]->getDegree() * deg2Rad, glm::vec3(0.0f, 0.0f, 1.0f));
		model = trans2 * rotate * trans1;
		unsigned int transformLocation = glGetUniformLocation(shader.shaderProgram, "model");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(shader.vao[i]);
		//switch (i)
		//{
		//case 0:
		//{
	
		//	break;
		//}
		//case 1:
		//{
		//	rotate = glm::rotate(rotate, triangles[i]->getDegree() * deg2Rad, glm::vec3(0.0f, 0.0f, 1.0f));
		//	model = trans2 * rotate * trans1;
		//	unsigned int transformLocation = glGetUniformLocation(shader.shaderProgram, "model");
		//	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(model));
		//	glBindVertexArray(shader.vao[i]);
		//	break;
		//}
		//case 2:
		//{
		//	rotate = glm::rotate(rotate, triangles[i]->getDegree() * deg2Rad, glm::vec3(0.0f, 0.0f, 1.0f));
		//	model = trans2 * rotate * trans1;
		//	unsigned int transformLocation = glGetUniformLocation(shader.shaderProgram, "model");
		//	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(model));
		//	glBindVertexArray(shader.vao[i]);
		//	break;
		//}
		//case 3:
		//{
		//	rotate = glm::rotate(rotate, triangles[i]->getDegree() * deg2Rad, glm::vec3(0.0f, 0.0f, 1.0f));
		//	model = trans2 * rotate * trans1;
		//	unsigned int transformLocation = glGetUniformLocation(shader.shaderProgram, "model");
		//	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(model));
		//	glBindVertexArray(shader.vao[i]);
		//}
		//default:
		//	break;
		//}
		triangles[i]->render();
	}

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	GLfloat mx{ 0.0f };
	GLfloat my{ 0.0f };
	ConvertDeviceXYOpenGLXY(x, y, &mx, &my);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		g_isLine = true;
		break;
	case 'b':
		g_isLine = false;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void ConvertDeviceXYOpenGLXY(int x, int y, GLfloat* pMx, GLfloat* pMy)
{
	int w = wWidth;
	int h = wHeight;

	*pMx= GLfloat((x - GLfloat(w) / 2.0) * GLfloat((1.0 / GLfloat(w / 2.0))));
	*pMy= -GLfloat((y - GLfloat(h) / 2.0) * GLfloat((1.0 / GLfloat(h / 2.0))));
}

void TimerFunc(int value)
{
	for (int i = 0; i < 4; ++i) 
		triangles[i]->move();

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}