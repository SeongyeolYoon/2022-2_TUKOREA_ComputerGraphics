#include "pch.h"

enum class Sequence { ONE, TWO, THREE, FOUR };
Sequence sequence = Sequence::ONE;

std::random_device rd;
std::mt19937 mersenne{ rd() };
std::uniform_real_distribution<GLfloat> uid{ 0.0f,1.0f };

GLfloat triShape[12][3]{
{-0.75f,0.25f,0.0f},{-0.25f,0.25f,0.0f},{-0.5f,0.75f,0.0f},
{0.25f,0.25f,0.0f},{0.75f,0.25f,0.0f},{0.5f,0.75f,0.0f},
{-0.75f,-0.75f,0.0f},{-0.25f,-0.75f,0.0f},{-0.5f,-0.25f,0.0f},
{ 0.25f,-0.75,0.0f},{0.75f,-0.75f,0.0f},{0.5f,-0.25f,0.0f}
};

const GLfloat colors[12][3]
{ {1.0f,0.0f,0.0f},{1.0f,0.0f,0.0f},{1.0f,0.0f,0.0f},
{0.0f,1.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,1.0f,0.0f},
{0.0f,0.0f,1.0f},{0.0f,0.0f,1.0f},{0.0f,0.0f,1.0f},
{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},{1.0f,1.0f,1.0f}
};

const int WINDOW_WIDTH{ 800 };
const int WINDOW_HEIGHT{ 600 };

GLchar* vertexSource, * fragmentSource;
GLuint vertexShader, fragmentShader;
GLuint vao, vbo[2];
GLuint shaderProgram;

bool g_isLine = false;

GLfloat sizeAmount{ 0.0f };
bool sizeFlag{ false };

void MakeVertexShader();
void MakeFragmentShader();

void CheckCompileError(GLuint, const char*);

void InitBuffer();
void InitShader();

void Keyboard(unsigned char, int, int);

GLvoid DrawScene();
GLvoid Reshape(int, int);

char* filetobuf(const char* file);

void Mouse(int, int, int, int);
void ConvertDeviceXYOpenGLXY(int, int, GLfloat*, GLfloat*);
int main(int argc, char** argv)							// 윈도우 출력하고 콜백함수 설정 
{
	// Create Window
	glutInit(&argc, argv);								// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);		// 디스플레이 모드 설정
	glutInitWindowPosition(0, 0);						// 윈도우의 위치 지정
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);	// 윈도우의 크기 지정
	glutCreateWindow("Example");						// 윈도우 생성 (윈도우 이름)

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {						// glew 초기화
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	InitShader();
	InitBuffer();

	glutDisplayFunc(DrawScene);							// 출력 함수의 지정
	glutReshapeFunc(Reshape);							// 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();												// 이벤트 처리 시작
}

void MakeVertexShader()
{
	vertexSource = filetobuf("vertex.glsl");

	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, (const GLchar**)(&vertexSource), 0);

	glCompileShader(vertexShader);

	CheckCompileError(vertexShader, "vertex");
}

void MakeFragmentShader()
{
	fragmentSource = filetobuf("fragment.glsl");

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, (const GLchar**)(&fragmentSource), 0);

	glCompileShader(fragmentShader);

	CheckCompileError(fragmentShader, "fragment");
}

void CheckCompileError(GLuint shaderType, const char* name)
{
	GLint result;

	GLchar errorLog[512];

	glGetShaderiv(shaderType, GL_COMPILE_STATUS, &result);

	if (!result) {
		glGetShaderInfoLog(shaderType, 512, NULL, errorLog);
		std::cerr << "ERROR:" << name << " shader complie Failed!\n" << errorLog << std::endl;
	}
}

char* filetobuf(const char* file)
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

void InitBuffer()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(2, vbo);

	// 버텍스 속성(좌표값)
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), triShape, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// 버텍스 속성(색상)
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

void InitShader()
{
	MakeVertexShader();
	MakeFragmentShader();

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	CheckCompileError(shaderProgram, "Shader Program");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgram);
}

void Keyboard(unsigned char key, int x, int y)
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

void Mouse(int button, int state, int x, int y)
{
	GLfloat mx{ 0.0f };
	GLfloat my{ 0.0f };
	ConvertDeviceXYOpenGLXY(x, y, &mx, &my);

	if ((-1.0f <= mx) && (1.0f >= mx) && (-1.0f <= my) && (1.0f >= my)) {
		if (GLUT_LEFT_BUTTON == button && GLUT_DOWN == state) {
			if (!sizeFlag) {
				sizeAmount += 0.01f;
				if (sizeAmount >= 0.2f) {
					sizeFlag = true;
					sizeAmount = 0.0f;
				}
			}
			else {
				sizeAmount += 0.01f;
				if (sizeAmount <= 0.2f) {
					sizeFlag = false;
					sizeAmount = 0.0f;
				}
			}
			switch (sequence)
			{
			case Sequence::ONE:
				if (!sizeFlag) {
					triShape[0][0] = (mx - 0.25f) - sizeAmount;
					triShape[0][1] = (my - 0.25f);
					triShape[1][0] = (mx + 0.25f) + sizeAmount;
					triShape[1][1] = (my - 0.25f);
					triShape[2][0] = mx;
					triShape[2][1] = (my + 0.25f) + sizeAmount;
				}
				else {
					triShape[0][0] = (mx - 0.25f) + sizeAmount;
					triShape[0][1] = (my - 0.25f);
					triShape[1][0] = (mx + 0.25f) - sizeAmount;
					triShape[1][1] = (my - 0.25f);
					triShape[2][0] = mx;
					triShape[2][1] = (my + 0.25f) - sizeAmount;
				}
				sequence = Sequence::TWO;
				break;
			case Sequence::TWO:
				if (!sizeFlag) {
					triShape[3][0] = (mx - 0.25f) - sizeAmount;
					triShape[3][1] = (my - 0.25f);
					triShape[4][0] = (mx + 0.25f) + sizeAmount;
					triShape[4][1] = (my - 0.25f);
					triShape[5][0] = mx;
					triShape[5][1] = (my + 0.25f) + sizeAmount;
				}
				else {
					triShape[3][0] = (mx - 0.25f) + sizeAmount;
					triShape[3][1] = (my - 0.25f);
					triShape[4][0] = (mx + 0.25f) - sizeAmount;
					triShape[4][1] = (my - 0.25f);
					triShape[5][0] = mx;
					triShape[5][1] = (my + 0.25f) - sizeAmount;
				}
				sequence = Sequence::THREE;
				break;
			case Sequence::THREE:
				if (!sizeFlag) {
					triShape[6][0] = (mx - 0.25f) - sizeAmount;
					triShape[6][1] = (my - 0.25f);
					triShape[7][0] = (mx + 0.25f) + sizeAmount;
					triShape[7][1] = (my - 0.25f);
					triShape[8][0] = mx;
					triShape[8][1] = (my + 0.25f) + sizeAmount;
				}
				else {
					triShape[6][0] = (mx - 0.25f) + sizeAmount;
					triShape[6][1] = (my - 0.25f);
					triShape[7][0] = (mx + 0.25f) - sizeAmount;
					triShape[7][1] = (my - 0.25f);
					triShape[8][0] = mx;
					triShape[8][1] = (my + 0.25f) - sizeAmount;
				}
				sequence = Sequence::FOUR;
				break;
			case Sequence::FOUR:
				if (!sizeFlag) {
					triShape[9][0] = (mx - 0.25f) - sizeAmount;
					triShape[9][1] = (my - 0.25f);
					triShape[10][0] = (mx + 0.25f) + sizeAmount;
					triShape[10][1] = (my - 0.25f);
					triShape[11][0] = mx;
					triShape[11][1] = (my + 0.25f) + sizeAmount;
				}
				else {
					triShape[9][0] = (mx - 0.25f) + sizeAmount;
					triShape[9][1] = (my - 0.25f);
					triShape[10][0] = (mx + 0.25f) - sizeAmount;
					triShape[10][1] = (my - 0.25f);
					triShape[11][0] = mx;
					triShape[11][1] = (my + 0.25f) - sizeAmount;
				}
				sequence = Sequence::ONE;
				break;
			default:
				break;
			}
			InitBuffer();
		}
	}
}

void ConvertDeviceXYOpenGLXY(int x, int y, GLfloat* ox, GLfloat* oy)
{
	int w = WINDOW_WIDTH;
	int h = WINDOW_HEIGHT;

	*ox = GLfloat((x - GLfloat(w) / 2.0) * GLfloat((1.0 / GLfloat(w / 2.0))));
	*oy = -GLfloat((y - GLfloat(h) / 2.0) * GLfloat((1.0 / GLfloat(h / 2.0))));
}

GLvoid DrawScene()										// 콜백 함수: 그리기 콜백 함수
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// 바탕색 지정
	// glClear(GL_COLOR_BUFFER_BIT);						// 설정된 색으로 전체를 칠하기
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 그리기 부분 구현
	// 그리기 관련 부분이 여기에 포함된다
	// 	
	//glDrawArrays(GL_TRIANGLES, 0, 12);

	if (g_isLine) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(5.0f);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glm::mat4 model = glm::mat4(1.0f);
	unsigned int transformLocation = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(model));
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	glutSwapBuffers();									// 화면에 출력하기 
}

GLvoid Reshape(int w, int h)							// 콜백 함수: 다시 클리기 콜백 함수
{
	float a;
	if (h == 0)
		h = 1;

	a = (GLfloat)h / (GLfloat)w;
	glViewport(0, 0, (GLint)w, (GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -a, a, 5.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
}