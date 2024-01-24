#include "pch.h"
#include <Windows.h>


constexpr int KEY_W{ 0x57 };
constexpr int KEY_A{ 0x41 };
constexpr int KEY_S{ 0x53 };
constexpr int KEY_D{ 0x44 };

std::mt19937 mersenne{ std::random_device{}() };
std::uniform_real_distribution<GLfloat> randomColor{ 0.0f,1.0f };

constexpr GLfloat Velocity = 1.5f;
constexpr GLfloat Gravity = 0.2f;

class Shader;
class CollisionManager;

class CoordSystem {
private:
	friend class Shader;
	static CoordSystem* pInst;
	const GLfloat vertex[6][3]{
		{-2.0f,0.0f,0.0f}, {2.0f,0.0f,0.0f},
		{0.0f,-2.0f,0.0f}, {0.0f,2.0f,0.0f},
		{0.0f,0.0f,-2.0f}, {0.0f,0.0f,2.0f} };
	const GLfloat color[6][3]{
		{1.0f,0.0f,0.0f}, {1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f}, {0.0f,1.0f,0.0f},
		{0.0f,0.0f,1.0f}, {0.0f,0.0f,1.0f} };
	glm::vec3 positionVector{ 0.0f,0.0f,0.0f };
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

	glm::vec3& getPositionVector() { return positionVector; }

	void render() const { glDrawArrays(GL_LINES, 0, 6); }
};

class Stage {
private:
	friend class Shader;
	static Stage* pInst;
	GLfloat vertex[8][3]{
{-2.0f,2.0f,-2.0f}
,{-2.0f,2.0f,2.0f}
,{2.0f,2.0f,2.0f}
,{2.0f,2.0f,-2.0f}
,{-2.0f,-2.0f,-2.0f}
,{-2.0f,-2.0f,2.0f}
,{2.0f,-2.0f,2.0f}
,{2.0f,-2.0f,-2.0f} };
	unsigned int index[36]{ 0,1,2,0,2,3,4,5,6,4,6,7,0,1,5,0,5,4,3,2,6,3,6,7,1,5,6,1,6,2,0,4,7,0,7,3 };
	const GLfloat color[8][3]{
		{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f},{1.0f,0.0f,1.0f},{1.0f,1.0f,0.0f},{0.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f}
	};
	glm::vec3 frontPositionVector{ 0.0f,0.0f,0.0f };
	bool openFrontSide{ false };
private:
	Stage()
	{

	}
public:
	static Stage* getInstance()
	{
		if (nullptr == pInst)
			pInst = new Stage;

		return pInst;
	}

	glm::vec3& getFrontPositionVector() { return frontPositionVector; }

	bool& isOpenFrontSide() { return openFrontSide; }

	void render(const int index) const
	{
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*>(index * sizeof(int)));
	}
};

class Robot {
private:
	friend class CollisionManager;
	friend class Shader;
	static Robot* pInst;
	unsigned int index[36]{ 0,1,2,0,2,3,4,5,6,4,6,7,0,1,5,0,5,4,3,2,6,3,6,7,1,5,6,1,6,2,0,4,7,0,7,3 };
	GLfloat headVertices[8][3]{
	{-0.2f,-0.4f,-0.2f}
	,{-0.2f,-0.4f,0.2f}
	,{0.2f,-0.4f,0.2f}
	,{0.2f,-0.4f,-0.2f}
	,{-0.2f,-0.8f,-0.2f}
	,{-0.2f,-0.8f,0.2f}
	,{0.2f,-0.8f,0.2f}
	,{0.2f,-0.8f,-0.2f} };
	GLfloat headColor[8][3]{ 
	{0.0f,0.5f,1.0f}, 
	{0.0f,0.5f,1.0f},
	{0.0f,0.5f,1.0f},
	{0.0f,0.5f,1.0f},
	{0.0f,0.5f,1.0f},
	{0.0f,0.5f,1.0f},
	{0.0f,0.5f,1.0f},
	{0.0f,0.5f,1.0f} };

	GLfloat bodyVerticies[8][3]{
	{-0.3f,-0.8f,-0.3f},
	{-0.3f,-0.8f,0.3f},
	{0.3f,-0.8f,0.3f},
	{0.3f,-0.8f,-0.3f},
	{-0.3f,-1.5f,-0.3f},
	{-0.3f,-1.5f,0.3f},
	{0.3f,-1.5f,0.3f},
	{0.3f,-1.5f,-0.3f} };
	GLfloat bodyColor[8][3]{
	{0.3f,1.0f,0.3f},
	{0.3f,1.0f,0.3f},
	{0.3f,1.0f,0.3f},
	{0.3f,1.0f,0.3f},
	{0.3f,1.0f,0.3f},
	{0.3f,1.0f,0.3f}, 
	{0.3f,1.0f,0.3f},
	{0.3f,1.0f,0.3f} };

	GLfloat noseVerticies[8][3]{
	{-0.3f,-0.6f,-0.05f}
	,{-0.3f,-0.6f,0.05f}
	,{-0.2f,-0.6f,0.05f}
	,{-0.2f,-0.6f,-0.05f}
	,{-0.3f,-0.7f,-0.05f}
	,{-0.3f,-0.7f,0.05f}
	,{-0.2f,-0.7f,0.05f}
	,{-0.2f,-0.7f,-0.05f} };
	GLfloat noseColor[8][3]{
	{1.0f,0.1f,0.1f},
	{1.0f,0.1f,0.1f},
	{1.0f,0.1f,0.1f},
	{1.0f,0.1f,0.1f},
	{1.0f,0.1f,0.1f},
	{1.0f,0.1f,0.f},
	{1.0f,0.1f,0.1f},
	{1.0f,0.1f,0.1f} };

	GLfloat leftArmVerticies[8][3]{
	{-0.05f,-0.9f,0.3f}
	,{-0.05f,-0.9f,0.4f}
	,{0.05f,-0.9f,0.4f}
	,{0.05f,-0.9f,0.3f}
	,{-0.05f,-1.4f,0.3f}
	,{-0.05f,-1.4f,0.4f}
	,{0.05f,-1.4f,0.4f}
	,{0.05f,-1.4f,0.3f} };
	GLfloat leftArmColor[8][3]{
	{1.0f,0.5f,0.2f},
	{1.0f,0.5f,0.2f},
	{1.0f,0.5f,0.2f},
	{1.0f,0.5f,0.2f},
	{1.0f,0.5f,0.2f},
	{1.0f,0.5f,0.2f},
	{1.0f,0.5f,0.2f},
	{1.0f,0.5f,0.2f} };

	GLfloat rightArmVerticies[8][3]{
	{-0.05f,-0.9f,-0.4f}
	,{-0.05f,-0.9f,-0.3f}
	,{0.05f,-0.9f,-0.3f}
	,{0.05f,-0.9f,-0.4f}
	,{-0.05f,-1.4f,-0.4f}
	,{-0.05f,-1.4f,-0.3f}
	,{0.05f,-1.4f,-0.3f}
	,{0.05f,-1.4f,-0.4f} };
	GLfloat rightArmColor[8][3]{
	{1.0,1.0f,0.5f},
	{1.0f,1.0f,0.5f},
	{1.0f,1.0f,0.5f},
	{1.0f,1.0f,0.5f},
	{1.0f,1.0f,0.5f},
	{1.0f,1.0f,0.5f},
	{1.0f,1.0f,0.5f},
	{1.0f,1.0f,0.5f} };

	GLfloat leftLegVerticies[8][3]{
	{-0.05f,-1.5f,0.12f}
	,{-0.05f,-1.5f,0.2f}
	,{0.05f,-1.5f,0.2f}
	,{0.05f,-1.5f,0.12f}
	,{-0.05f,-2.0f,0.12f}
	,{-0.05f,-2.0f,0.2f}
	,{0.05f,-2.0f,0.2f}
	,{0.05f,-2.0f,0.12f} };
	GLfloat leftLegColor[8][3]{
	{0.1f,1.0f,0.5f},
	{0.1f,1.0f,0.5f},
	{0.1f,1.0f,0.5f},
	{0.1f,1.0f,0.5f},
	{0.1f,1.0f,0.5f},
	{0.1f,1.0f,0.5f},
	{0.1f,1.0f,0.5f},
	{0.1f,1.0f,0.5f} };

	GLfloat rightLegVerticies[8][3]{
	{-0.05f,-1.5f,-0.2f}
	,{-0.05f,-1.5f,-0.12f}
	,{0.05f,-1.5f,-0.12f}
	,{0.05f,-1.5f,-0.2f}
	,{-0.05f,-2.0f,-0.2f}
	,{-0.05f,-2.0f,-0.12f}
	,{0.05f,-2.0f,-0.12f}
	,{0.05f,-2.0f,-0.2f} };
	GLfloat rightLegColor[8][3]{
	{0.5f,0.5f,1.0f},
	{0.5f,0.5f,1.0f},
	{0.5f,0.5f,1.0f},
	{0.5f,0.5f,1.0f},
	{0.5f,0.5f,1.0f},
	{0.5f,0.5f,1.0f},
	{0.5f,0.5f,1.0f},
	{0.5f,0.5f,1.0f} };

	glm::vec3 positionVector{ 0.0f,0.0f,0.0f };
	glm::vec3 directionVector{ 0.0f, 0.0f, 0.0f };
	glm::vec3 velocity{ 0.0f,0.0f,0.0f };
	glm::vec3 legPositionVecotr{ 0.0f,-2.0f,0.0f };
	GLfloat speed{ 0.05f };
	GLfloat jumpVelocity{ Velocity };
	GLfloat jumpForce{ 0.0f };
	GLfloat rotationDegree{ 0.0f };
	GLfloat legDegreeAmount{ 1.0f };
	GLfloat armDegreeAmount{ 1.0f };
	GLfloat rightDegreeAmount{ 1.0f };
	GLfloat leftArmDegree{ 0.0f };
	GLfloat rightArmDegree{ 0.0f };
	GLfloat leftLegDegree{ 0.0f };
	GLfloat rightLegDegree{ 0.0f };

	bool isJump{ false };

private:
	Robot()
	{

	}
public:
	static Robot* getInstance()
	{
		if (nullptr == pInst)
			pInst = new Robot;

		return pInst;
	}
	
	glm::vec3& getPositionVector() { return positionVector; }

	glm::vec3& getLegPositionVector() { return legPositionVecotr; }

	glm::vec3& getDirectionVector() { return directionVector; }

	glm::vec3& getVelocity() { return velocity; }

	const GLfloat& getSpeed() const { return speed; }

	GLfloat& getLegDegreeAmount() { return legDegreeAmount; }

	GLfloat& getArmDegreeAmount() { return armDegreeAmount; }

	GLfloat& getRightDegreeAmount() { return rightDegreeAmount; }
	
	GLfloat& getRotationDegree() { return rotationDegree; }

	GLfloat& getLeftArmDegree() { return leftArmDegree; }
	GLfloat& getRightArmDegree() { return rightArmDegree; }
	GLfloat& getLeftLegDegree() { return leftLegDegree; }
	GLfloat& getRightLegDegree() { return rightLegDegree; }
	
	bool& isOnJump() { return isJump; }


	GLfloat& getJumpVelocity() { return jumpVelocity; }

	GLfloat& getJumpForce() { return jumpForce; }


	void jump()
	{
		if (jumpVelocity > 0.0f)
			jumpForce = (0.5f * Gravity * jumpVelocity * jumpVelocity);
		else
			jumpForce = -(0.5f * Gravity * jumpVelocity * jumpVelocity);

		positionVector.y += jumpForce;

		jumpVelocity -= 0.1f;
	}

	void render() const{ glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);}
};

class Obstacle {
private:
	friend class CollisionManager;
	friend class Shader;
	static Obstacle* pInst;
	std::uniform_real_distribution<GLfloat> randomPos{ -1.0f,1.0f };
	std::uniform_real_distribution<GLfloat> randomHeight{ 0.2f,0.4f };
	std::uniform_real_distribution<GLfloat> randomWidth{ 0.3f,0.6f };
	GLfloat WIDTH{ randomWidth(mersenne)};
	GLfloat HEIGHT{ randomHeight(mersenne)};
	GLfloat centerPos{ randomPos(mersenne) };
	GLfloat verticies[8][3]{
	{centerPos - WIDTH, -2.0f + HEIGHT, centerPos - WIDTH},
	{centerPos - WIDTH,-2.0f + HEIGHT,centerPos +  WIDTH},
	{centerPos + WIDTH,-2.0f + HEIGHT,centerPos + WIDTH},
	{centerPos + WIDTH,-2.0f + HEIGHT,centerPos - WIDTH},
	{centerPos - WIDTH, -2.0f, centerPos - WIDTH},
	{centerPos - WIDTH,-2.0f, centerPos + WIDTH},
	{centerPos + WIDTH,-2.0f, centerPos + WIDTH},
	{centerPos + WIDTH,-2.0f,centerPos - WIDTH} };
	GLfloat color[8][3]{ 
	{0.5f,0.5f,0.5f},
	{0.5f,0.5f,0.5f}, 
	{0.5f,0.5f,0.5f}, 
	{0.5f,0.5f,0.5f}, 
	{0.5f,0.5f,0.5f}, 
	{0.5f,0.5f,0.5f}, 
	{0.5f,0.5f,0.5f}, 
	{0.5f,0.5f,0.5f}};

	glm::vec3 positionVector {centerPos};
	unsigned int index[36]{ 0,1,2,0,2,3,4,5,6,4,6,7,0,1,5,0,5,4,3,2,6,3,6,7,1,5,6,1,6,2,0,4,7,0,7,3 };


private:
	Obstacle()
	{

	}
public:

	static Obstacle* getInstance()
	{
		if (nullptr == pInst)
			pInst = new Obstacle;

		return pInst;
	}

	void reset()
	{
		WIDTH = randomWidth(mersenne);
		HEIGHT = randomHeight(mersenne);
		centerPos = randomPos(mersenne);
		positionVector = glm::vec3{centerPos};

		verticies[0][0] = centerPos - WIDTH;
		verticies[0][1] = -2.0f + HEIGHT;
		verticies[0][2] = centerPos - WIDTH;
		verticies[1][0] = centerPos - WIDTH;
		verticies[1][1] = -2.0f + HEIGHT;
		verticies[1][2] = centerPos + WIDTH;
		verticies[2][0] = centerPos + WIDTH;
		verticies[2][1] = -2.0f + HEIGHT;
		verticies[2][2] = centerPos + WIDTH;
		verticies[3][0] = centerPos + WIDTH;
		verticies[3][1] = -2.0f + HEIGHT;
		verticies[3][2] = centerPos - WIDTH;
		verticies[4][0] = centerPos - WIDTH;
		verticies[4][1] = -2.0f;
		verticies[4][2] = centerPos - WIDTH;
		verticies[5][0] = centerPos - WIDTH;
		verticies[5][1] = -2.0f;
		verticies[5][2] = centerPos + WIDTH;
		verticies[6][0] = centerPos + WIDTH;
		verticies[6][1] = -2.0f;
		verticies[6][2] = centerPos + WIDTH;
		verticies[7][0] = centerPos + WIDTH;
		verticies[7][1] = -2.0f;
		verticies[7][2] = centerPos - WIDTH;
	}
	GLfloat& getVertex(int row, int col) { return verticies[row][col]; }

	glm::vec3& getPositionVector() { return positionVector; }

	const GLfloat getWidth() const { return WIDTH; }

	const GLfloat getHeight() { return HEIGHT; }

	void render() const{ glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); }
};


class Shader {
private:
	friend class CoordSystem;
	friend class Stage;
	friend class Robot;
	friend class Obstacle;
	static Shader* pInst;
	enum { MaxVao = 11, MaxVbo = 22, MaxEbo = 1 };
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(Stage::getInstance()->vertex), Stage::getInstance()->vertex, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Stage::getInstance()->index), Stage::getInstance()->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Stage::getInstance()->color), Stage::getInstance()->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[2]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Robot::getInstance()->headVertices), Robot::getInstance()->headVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Robot::getInstance()->index), Robot::getInstance()->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Robot::getInstance()->headColor), Robot::getInstance()->headColor, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[3]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[6]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Robot::getInstance()->noseVerticies), Robot::getInstance()->noseVerticies, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Robot::getInstance()->index), Robot::getInstance()->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[7]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Robot::getInstance()->noseColor), Robot::getInstance()->noseColor, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[4]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[8]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Robot::getInstance()->bodyVerticies), Robot::getInstance()->bodyVerticies, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Robot::getInstance()->index), Robot::getInstance()->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[9]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Robot::getInstance()->bodyColor), Robot::getInstance()->bodyColor, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[5]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[10]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Robot::getInstance()->leftArmVerticies), Robot::getInstance()->leftArmVerticies, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Robot::getInstance()->index), Robot::getInstance()->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[11]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Robot::getInstance()->leftArmColor), Robot::getInstance()->leftArmColor, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[6]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[12]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Robot::getInstance()->rightArmVerticies), Robot::getInstance()->rightArmVerticies, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Robot::getInstance()->index), Robot::getInstance()->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[13]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Robot::getInstance()->rightArmColor), Robot::getInstance()->rightArmColor, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[7]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[14]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Robot::getInstance()->leftLegVerticies), Robot::getInstance()->leftLegVerticies, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Robot::getInstance()->index), Robot::getInstance()->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[15]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Robot::getInstance()->leftLegColor), Robot::getInstance()->leftLegColor, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[8]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[16]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Robot::getInstance()->rightLegVerticies), Robot::getInstance()->rightLegVerticies, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Robot::getInstance()->index), Robot::getInstance()->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[17]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Robot::getInstance()->rightLegColor), Robot::getInstance()->rightLegColor, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(vao[9]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[18]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Obstacle::getInstance()->verticies), Obstacle::getInstance()->verticies, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Obstacle::getInstance()->index), Obstacle::getInstance()->index, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[19]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Obstacle::getInstance()->color), Obstacle::getInstance()->color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
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
	glm::vec3 positionVector{ glm::vec3{0.0f,0.0f,5.0f } };
	glm::vec3 targetVector{ glm::vec3{0.0f,0.0f,0.0f} };
	//glm::vec3 directionVector{ glm::vec3{0.0f,0.0f,0.0f} };
	glm::vec3 directionVector{ glm::normalize(targetVector - positionVector)};
	glm::vec3 defaultUpVector{ glm::vec3{ 0.0f,1.0f,0.0f } };
	glm::vec3 rightVector{ glm::normalize(glm::cross(defaultUpVector, directionVector)) };
	glm::vec3 upVector{ glm::cross(directionVector, rightVector) };
	glm::vec3 front{ glm::vec3{ 0.0f,0.0f,-1.0f } };
	glm::mat4 viewMatrix{ 1.0f };
	glm::mat4 projectionMatrix{ 1.0f };
	GLfloat speed{ 0.1f };
public:
	glm::vec3& getPositionVector() { return positionVector; }
	glm::vec3& getTargetVector() { return targetVector; }
	glm::vec3& getDirectionVector() { return directionVector; }
	glm::vec3& getUpVector() { return upVector; }
	glm::vec3& getRightVector() { return rightVector; }
	glm::vec3& getDefaultUpVector() { return defaultUpVector;  }
	void update()
	{
		//directionVector = glm::normalize(targetVector - positionVector);
		//rightVector = glm::normalize(glm::cross(defaultUpVector, directionVector));
		//upVector = glm::cross(directionVector, rightVector);
		viewMatrix = glm::lookAt(positionVector, directionVector, upVector);
		projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 50.0f);
		projectionMatrix = glm::translate(projectionMatrix, glm::vec3(0.0f, 0.0f, -5.0f));
		unsigned int viewTrasnformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "viewTransform");
		unsigned int projectionTransformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "projectionTransform");
		glUniformMatrix4fv(viewTrasnformLocation, 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
	}
};

class CollisionManager
{
private:
	static 
	friend class Robot;
	friend class Obstacle;
	static CollisionManager* pInst;
	Robot* pRobot{ nullptr };
	Obstacle* pObstacle{ nullptr };
private:
	CollisionManager()
	{

	}
public:
	static CollisionManager* getInstance()
	{
		if (nullptr == pInst)
			pInst = new CollisionManager;

		return pInst;
	}

	void initObjects(Robot* robot, Obstacle* obstacle)
	{
		pRobot = robot;
		pObstacle = obstacle;
	}

	void checkColiision()
	{
		if (pRobot->getLegPositionVector().x < pObstacle->getPositionVector().x + pObstacle->getWidth() &&
			pObstacle->getPositionVector().x - pObstacle->getWidth() < pRobot->getLegPositionVector().x &&
			pRobot->getLegPositionVector().z < pObstacle->getPositionVector().z + pObstacle->getWidth() &&
			pObstacle->getPositionVector().z - pObstacle->getWidth() < pRobot->getLegPositionVector().z) {
			pRobot->getPositionVector().y = 0.3f;
		}
		else {
			pRobot->getPositionVector().y = 0.0f;
		}
		//else {
		//	pRobot->getPositionVector().y = 0.0f;
		//}
	}
};

constexpr GLuint wWidth{ 1200 };
constexpr GLuint wHeight{ 800 };

Camera* pCamera;
Shader* Shader::pInst = nullptr;
CoordSystem* CoordSystem::pInst = nullptr;
Stage* Stage::pInst = nullptr;
Robot* Robot::pInst = nullptr;
Obstacle* Obstacle::pInst = nullptr;
CollisionManager* CollisionManager::pInst = nullptr;
GLfloat degree{ 0.0f };

GLvoid RenderScene();
GLvoid Reshape(int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid TimerFunc(int);

void PrintLog();


void PrintCameraLog();

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

	pCamera = new Camera;
	Shader::getInstance()->glGenerate();
	Shader::getInstance()->initBuffer();
	Shader::getInstance()->initShader();
	CollisionManager::getInstance()->initObjects(Robot::getInstance(), Obstacle::getInstance());
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
	//glEnable(GL_CULL_FACE);
	pCamera->update();

	{
		glm::mat4 transformMatrix{ 1.0f };
		glm::mat4 parentMatrix{ 1.0f };
		glm::mat4 revolutionMatrix{ 1.0f };
		glm::mat4 translationMatrix{ 1.0f };
		glm::mat4 rotationMatrix{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		glm::mat4 rotY{ 1.0f };
		glm::mat4 revY{ 1.0f };
		glm::mat4 revX{ 1.0f };
		glm::mat4 revZ{ 1.0f };
		rotationMatrix = rotY;
		translationMatrix = glm::translate(translationMatrix, degree * glm::vec3(CoordSystem::getInstance()->getPositionVector()));
		transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
		unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glBindVertexArray(Shader::getInstance()->getVao()[0]);
		CoordSystem::getInstance()->render();
	}

	// Stage
	{
		glm::mat4 transformMatrix{ 1.0f };
		glm::mat4 parentMatrix{ 1.0f };
		glm::mat4 revolutionMatrix{ 1.0f };
		glm::mat4 translationMatrix{ 1.0f };
		glm::mat4 rotationMatrix{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		glm::mat4 rotY{ 1.0f };
		glm::mat4 revY{ 1.0f };
		glm::mat4 revX{ 1.0f };
		glm::mat4 revZ{ 1.0f };
		rotationMatrix = rotY;
		//translationMatrix = glm::translate(translationMatrix, glm::vec3(Stage::getInstance()->getPositionVector()));
		transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
		unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glBindVertexArray(Shader::getInstance()->getVao()[1]);
		Stage::getInstance()->render(0); // ceiling
		Stage::getInstance()->render(6); // floor
		Stage::getInstance()->render(12); // left
		Stage::getInstance()->render(18); // right
		Stage::getInstance()->render(30); // rear
		
		// Front
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			glm::mat4 revY{ 1.0f };
			glm::mat4 revX{ 1.0f };
			glm::mat4 revZ{ 1.0f };
			translationMatrix = glm::translate(translationMatrix, Stage::getInstance()->getFrontPositionVector());
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[1]);
			Stage::getInstance()->render(24); // front
		}
	}

	// Robot
	{
		// Head
		glm::mat4 headTransformMatrix{ 1.0f };
		{
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			glm::mat4 revY{ 1.0f };
			glm::mat4 revX{ 1.0f };
			glm::mat4 revZ{ 1.0f };
			//scaleMatrix = glm::scale(scaleMatrix, glm::vec3(-0.5f, -0.5f, -0.5f));
			translationMatrix = glm::translate(translationMatrix, Robot::getInstance()->getPositionVector());
			rotationMatrix = glm::rotate(rotationMatrix, glm::radians(Robot::getInstance()->getRotationDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
			headTransformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(headTransformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[2]);
			Robot::getInstance()->render(); // front
		}

		// Nose->Head
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			glm::mat4 revY{ 1.0f };
			glm::mat4 revX{ 1.0f };
			glm::mat4 revZ{ 1.0f };
			//scaleMatrix = glm::scale(scaleMatrix, glm::vec3(-0.5f, -0.5f, -0.5f));
			parentMatrix = headTransformMatrix;
		//	translationMatrix = glm::translate(translationMatrix, glm::radians(degree) * Robot::getInstance()->getPositionVector());
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[3]);
			Robot::getInstance()->render(); // front
		}

		// Body -> Head
		glm::mat4 bodyTransformMatrix{ 1.0f };
		{
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			glm::mat4 revY{ 1.0f };
			glm::mat4 revX{ 1.0f };
			glm::mat4 revZ{ 1.0f };
			//scaleMatrix = glm::scale(scaleMatrix, glm::vec3(1.0f, -0.5f, -0.5f));
			parentMatrix = headTransformMatrix;
			//rotationMatrix = glm::rotate(rotationMatrix, glm::radians(Robot::getInstance()->getRotationDegree()), glm::vec3(0.0f, 1.0f, 0.0f));
		//	translationMatrix = glm::translate(translationMatrix, glm::radians(degree) * Robot::getInstance()->getPositionVector());
			bodyTransformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(bodyTransformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[4]);
			Robot::getInstance()->render(); // front
		}

		// LeftArm ->Body
		{
		glm::mat4 transformMatrix{ 1.0f };
		glm::mat4 parentMatrix{ 1.0f };
		glm::mat4 revolutionMatrix{ 1.0f };
		glm::mat4 translationMatrix{ 1.0f };
		glm::mat4 rotationMatrix{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		glm::mat4 rotY{ 1.0f };
		glm::mat4 revY{ 1.0f };
		glm::mat4 revX{ 1.0f };
		glm::mat4 revZ{ 1.0f };
		glm::mat4 firstTrans{ 1.0f };
		glm::mat4 lastTrans{ 1.0f };
		parentMatrix = bodyTransformMatrix;
		revZ = glm::rotate(revZ, glm::radians(Robot::getInstance()->getLeftArmDegree()), glm::vec3(0.0f, 0.0f, 1.0f));
		rotationMatrix = lastTrans * revZ * firstTrans;
		transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
		unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glBindVertexArray(Shader::getInstance()->getVao()[5]);
		Robot::getInstance()->render(); // front
		}

		// rightArm->Body
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			glm::mat4 revY{ 1.0f };
			glm::mat4 revX{ 1.0f };
			glm::mat4 revZ{ 1.0f };
			glm::mat4 firstTrans{ 1.0f };
			glm::mat4 lastTrans{ 1.0f };
			//revX = glm::translate(revX, glm::vec3(-0.5f, 0.0f, 0.0f));
			//revX = glm::rotate(revX, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			revolutionMatrix = revX;
			revZ = glm::rotate(revZ, glm::radians(Robot::getInstance()->getRightArmDegree()), glm::vec3(0.0f, 0.0f, 1.0f));
			rotationMatrix = lastTrans * revZ * firstTrans;
			parentMatrix = bodyTransformMatrix;
			rotationMatrix = lastTrans * revZ * firstTrans;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[6]);
			Robot::getInstance()->render(); // front
		}

		// LeftLeg->Body
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			glm::mat4 revY{ 1.0f };
			glm::mat4 revX{ 1.0f };
			glm::mat4 revZ{ 1.0f };
			glm::mat4 firstTrans{ 1.0f };
			glm::mat4 lastTrans{ 1.0f };
			parentMatrix = bodyTransformMatrix;
		//	translationMatrix = glm::translate(translationMatrix, glm::radians(degree) * Robot::getInstance()->getPositionVector());
			lastTrans = glm::translate(lastTrans, glm::vec3((0.0f, -1.2f,0.0f)));
			revZ = glm::rotate(revZ, glm::radians(Robot::getInstance()->getLeftLegDegree()), glm::vec3(0.0f, 0.0f, 1.0f));
			firstTrans = glm::translate(firstTrans, glm::vec3((0.0f, +1.2f, 0.0f)));
			rotationMatrix = lastTrans * revZ * firstTrans;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[7]);
			Robot::getInstance()->render(); // front
		}

		// RightLeg->Body
		{
			glm::mat4 transformMatrix{ 1.0f };
			glm::mat4 parentMatrix{ 1.0f };
			glm::mat4 revolutionMatrix{ 1.0f };
			glm::mat4 translationMatrix{ 1.0f };
			glm::mat4 rotationMatrix{ 1.0f };
			glm::mat4 scaleMatrix{ 1.0f };
			glm::mat4 rotY{ 1.0f };
			glm::mat4 revY{ 1.0f };
			glm::mat4 revX{ 1.0f };
			glm::mat4 revZ{ 1.0f };
			glm::mat4 firstTrans{ 1.0f };
			glm::mat4 lastTrans{ 1.0f };
			parentMatrix = bodyTransformMatrix;
			lastTrans = glm::translate(lastTrans, glm::vec3((0.0f, -1.15f, 0.0f)));
			revZ = glm::rotate(revZ, glm::radians(Robot::getInstance()->getRightLegDegree()), glm::vec3(0.0f, 0.0f, 1.0f));
			firstTrans = glm::translate(firstTrans, glm::vec3((0.0f, 1.15f, 0.0f)));
			rotationMatrix = lastTrans * revZ * firstTrans;
			transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
			unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
			glBindVertexArray(Shader::getInstance()->getVao()[8]);
			Robot::getInstance()->render(); // front
		}
	}

	// Obstacle
	{
		glm::mat4 transformMatrix{ 1.0f };
		glm::mat4 parentMatrix{ 1.0f };
		glm::mat4 revolutionMatrix{ 1.0f };
		glm::mat4 translationMatrix{ 1.0f };
		glm::mat4 rotationMatrix{ 1.0f };
		glm::mat4 scaleMatrix{ 1.0f };
		glm::mat4 rotY{ 1.0f };
		glm::mat4 revY{ 1.0f };
		glm::mat4 revX{ 1.0f };
		glm::mat4 revZ{ 1.0f };
		// translationMatrix = glm::translate(translationMatrix, glm::vec3(Obstacle::getInstance()->getPositionVector()));
		transformMatrix = parentMatrix * revolutionMatrix * translationMatrix * rotationMatrix * scaleMatrix;
		unsigned int transformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "modelTransform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glBindVertexArray(Shader::getInstance()->getVao()[9]);
		Obstacle::getInstance()->render(); // front
	}

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);

	switch (key)
	{
	case 'r':
		// close front 
		Stage::getInstance()->isOpenFrontSide() = false;
		Stage::getInstance()->getFrontPositionVector().y = 0.0f;
		// camera pos reset 
		pCamera->getPositionVector() = glm::vec3{ 0.0f,0.0f,5.0f };
		pCamera->getTargetVector() = glm::vec3{ 0.0f,0.0f,0.0f };
		pCamera->getDirectionVector() = glm::normalize(pCamera->getTargetVector() - pCamera->getPositionVector());
		pCamera->getRightVector() = glm::normalize(glm::cross(pCamera->getDefaultUpVector(), pCamera->getDirectionVector()));
		pCamera->getUpVector() = glm::cross(pCamera->getDirectionVector(), pCamera->getRightVector());

		// robot pos reset 
		Robot::getInstance()->getPositionVector() = glm::vec3{ 0.0f,0.0f,0.0f };
		Robot::getInstance()->getLegPositionVector() = glm::vec3{ 0.0f,0.0f,0.0f };

		// obstacle pos reset 
		Obstacle::getInstance()->reset();
		break;
	case 'o':
		Stage::getInstance()->isOpenFrontSide() = true;
		break;
	case 'O':
		Stage::getInstance()->isOpenFrontSide() = false;
		break;
	case 'i':
		break;
	case 'z':
		//pCamera->getPositionVector() += 0.1f * pCamera->getDirectionVector();
		pCamera->getPositionVector().z -= 0.1f;
		pCamera->getDirectionVector().z -= 0.1f;
		PrintCameraLog();
		break;
	case 'Z':
		//pCamera->getPositionVector() -= 0.1f * pCamera->getDirectionVector();
		pCamera->getPositionVector().z += 0.1f;
		pCamera->getDirectionVector().z += 0.1f;
		PrintCameraLog();
		break;
	case 'x':
		//glm::vec3 target{ glm::vec3(pCamera->getPositionVector().x +0.1f,pCamera->getPositionVector().y,pCamera->getPositionVector().z) };
		//pCamera->getTargetVector() = target;
		//pCamera->getDirectionVector() = glm::normalize(target - pCamera->getPositionVector());
		//pCamera->getPositionVector() += pCamera->getDirectionVector() * 0.1f;
		pCamera->getPositionVector().x += 0.1f;
		pCamera->getTargetVector().x += 0.1f;
		pCamera->getDirectionVector().x += 0.1f;
		//pCamera->getRightVector() = glm::normalize(glm::cross(pCamera->getDefaultUpVector(), pCamera->getDirectionVector()));
		//pCamera->getUpVector() = glm::cross(pCamera->getDirectionVector(), pCamera->getRightVector());
		PrintCameraLog();
		break;
	case 'X':
		//pCamera->getDirectionVector().x += 0.1f;
		//pCamera->getPositionVector().x += 0.1f;
		pCamera->getPositionVector().x -= 0.1f;
		pCamera->getTargetVector().x -= 0.1f;
		pCamera->getDirectionVector().x -= 0.1f;
		PrintCameraLog();
		break;
	case 'y':
		// 바라보는 방향 - 카메라 벡터 = > 방향 
		// 회전 공식 
		pCamera->getPositionVector() += glm::normalize(glm::cross(pCamera->getDirectionVector(), pCamera->getUpVector())) * 0.1f;
		pCamera->getDirectionVector() = glm::normalize(pCamera->getTargetVector() - pCamera->getPositionVector());
		pCamera->getRightVector() = glm::normalize(glm::cross(pCamera->getDefaultUpVector(), pCamera->getDirectionVector()));
		pCamera->getUpVector() = glm::cross(pCamera->getDirectionVector(), pCamera->getRightVector());
		PrintCameraLog();
		break;
	case 'Y':
		pCamera->getPositionVector() -= glm::normalize(glm::cross(pCamera->getDirectionVector(), pCamera->getUpVector())) * 0.1f;
		pCamera->getDirectionVector() = glm::normalize(pCamera->getTargetVector() - pCamera->getPositionVector());
		pCamera->getRightVector() = glm::normalize(glm::cross(pCamera->getDefaultUpVector(), pCamera->getDirectionVector()));
		pCamera->getUpVector() = glm::cross(pCamera->getDirectionVector(), pCamera->getRightVector());
		PrintCameraLog();
		break;
	case 'b':
		///*pCamera->getPositionVector().x = cosf(glm::radians(degree));
		//pCamera->getPositionVector().z = sinf(glm::radians(degree));
		//pCamera->getTargetVector().x = cosf(glm::radians(degree));
		//pCamera->getTargetVector().z = sinf(glm::radians(degree));
		//pCamera->getDirectionVector().x = cosf(glm::radians(degree));
		//pCamera->getDirectionVector().z = sinf(glm::radians(degree));*/
		//// 쿼터니언 
		//pCamera->getTargetVector().z = cosf(glm::radians(degree))+sinf(glm::radians(degree));
		//pCamera->getPositionVector().x = cosf(glm::radians(degree)) - sinf(glm::radians(degree));
		//pCamera->getPositionVector().z = cosf(glm::radians(degree)) + sinf(glm::radians(degree));
		//pCamera->getTargetVector().x = cosf(glm::radians(degree)) - sinf(glm::radians(degree));
		//pCamera->getDirectionVector().x -= pCamera->getPositionVector().x;
		//pCamera->getDirectionVector().x= cosf(glm::radians(degree)) - pCamera->getDirectionVector().z* sinf(glm::radians(degree));
		//pCamera->getDirectionVector().x += pCamera->getPositionVector().x;
		//pCamera->getDirectionVector().z -= pCamera->getPositionVector().z;
		//pCamera->getDirectionVector().z = cosf(glm::radians(degree))+ pCamera->getDirectionVector().z*sinf(glm::radians(degree));
		//pCamera->getDirectionVector().z += pCamera->getPositionVector().z;
		//degree += 1.0f;
		//PrintCameraLog();
		break;
	case 'B':
		break;
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
	if (!Robot::getInstance()->isOnJump()) {
		// -------------------------------------------------------
		CollisionManager::getInstance()->checkColiision();
		// -------------------------------------------------------
	}
	if (GetAsyncKeyState(KEY_W)) {
		Robot::getInstance()->getLeftLegDegree() += Robot::getInstance()->getLegDegreeAmount();
		Robot::getInstance()->getRightLegDegree() -= Robot::getInstance()->getLegDegreeAmount();
		Robot::getInstance()->getLeftArmDegree() -= Robot::getInstance()->getArmDegreeAmount();
		Robot::getInstance()->getRightArmDegree() += Robot::getInstance()->getArmDegreeAmount();

		if (Robot::getInstance()->getLeftLegDegree() > 7.0f || Robot::getInstance()->getLeftLegDegree() < -7.0f) {
			Robot::getInstance()->getLegDegreeAmount() = -Robot::getInstance()->getLegDegreeAmount();
		}
		if (Robot::getInstance()->getLeftArmDegree() > 7.0f || Robot::getInstance()->getLeftArmDegree() < -7.0f) {
			Robot::getInstance()->getArmDegreeAmount() = -Robot::getInstance()->getArmDegreeAmount();
		}

		if (Robot::getInstance()->getPositionVector().z < -2.0f) {
			Robot::getInstance()->getPositionVector().z = 2.0f;
			Robot::getInstance()->getLegPositionVector().z = 2.0f;
		}

		Robot::getInstance()->getRotationDegree() = 270.0f;
		glm::vec3 target{ glm::vec3{Robot::getInstance()->getPositionVector().x, Robot::getInstance()->getPositionVector().y,Robot::getInstance()->getPositionVector().z - 0.1f} };
		//	glm::vec3 target{ glm::vec3{Robot::getInstance()->getPositionVector().x, Robot::getInstance()->getPositionVector().y,-3.0f}};
		Robot::getInstance()->getDirectionVector() = glm::normalize(target - Robot::getInstance()->getPositionVector());
		Robot::getInstance()->getVelocity() = Robot::getInstance()->getDirectionVector() * Robot::getInstance()->getSpeed();
		Robot::getInstance()->getPositionVector() += Robot::getInstance()->getVelocity();
		Robot::getInstance()->getLegPositionVector() += Robot::getInstance()->getVelocity();
		PrintLog();
	}

	if (GetAsyncKeyState(KEY_A)) {
		Robot::getInstance()->getLeftLegDegree() += Robot::getInstance()->getLegDegreeAmount();
		Robot::getInstance()->getRightLegDegree() -= Robot::getInstance()->getLegDegreeAmount();
		Robot::getInstance()->getLeftArmDegree() -= Robot::getInstance()->getArmDegreeAmount();
		Robot::getInstance()->getRightArmDegree() += Robot::getInstance()->getArmDegreeAmount();

		if (Robot::getInstance()->getLeftLegDegree() > 7.0f || Robot::getInstance()->getLeftLegDegree() < -7.0f) {
			Robot::getInstance()->getLegDegreeAmount() = -Robot::getInstance()->getLegDegreeAmount();
		}
		if (Robot::getInstance()->getLeftArmDegree() > 7.0f || Robot::getInstance()->getLeftArmDegree() < -7.0f) {
			Robot::getInstance()->getArmDegreeAmount() = -Robot::getInstance()->getArmDegreeAmount();
		}

		if (Robot::getInstance()->getPositionVector().x < -2.0f) {
			Robot::getInstance()->getPositionVector().x = 2.0f;
			Robot::getInstance()->getLegPositionVector().x = 2.0f;
		}
		Robot::getInstance()->getRotationDegree() = 0.0f;
		glm::vec3 target{ glm::vec3{Robot::getInstance()->getPositionVector().x - 0.1f, Robot::getInstance()->getPositionVector().y,Robot::getInstance()->getPositionVector().z} };
		//glm::vec3 target{ glm::vec3{-3.0f, Robot::getInstance()->getPositionVector().y,Robot::getInstance()->getPositionVector().z} };
		Robot::getInstance()->getDirectionVector() = glm::normalize(target - Robot::getInstance()->getPositionVector());
		Robot::getInstance()->getVelocity() = Robot::getInstance()->getDirectionVector() * Robot::getInstance()->getSpeed();
		Robot::getInstance()->getPositionVector() += Robot::getInstance()->getVelocity();
		Robot::getInstance()->getLegPositionVector() += Robot::getInstance()->getVelocity();
		PrintLog();
	}


	if (GetAsyncKeyState(KEY_S)) {
		Robot::getInstance()->getLeftLegDegree() += Robot::getInstance()->getLegDegreeAmount();
		Robot::getInstance()->getRightLegDegree() -= Robot::getInstance()->getLegDegreeAmount();
		Robot::getInstance()->getLeftArmDegree() -= Robot::getInstance()->getArmDegreeAmount();
		Robot::getInstance()->getRightArmDegree() += Robot::getInstance()->getArmDegreeAmount();

		if (Robot::getInstance()->getLeftLegDegree() > 7.0f || Robot::getInstance()->getLeftLegDegree() < -7.0f) {
			Robot::getInstance()->getLegDegreeAmount() = -Robot::getInstance()->getLegDegreeAmount();
		}
		if (Robot::getInstance()->getLeftArmDegree() > 7.0f || Robot::getInstance()->getLeftArmDegree() < -7.0f) {
			Robot::getInstance()->getArmDegreeAmount() = -Robot::getInstance()->getArmDegreeAmount();
		}

		if (Robot::getInstance()->getPositionVector().z > 2.0f) {
			Robot::getInstance()->getPositionVector().z = -2.0f;
			Robot::getInstance()->getLegPositionVector().z = -2.0f;
		}

		Robot::getInstance()->getRotationDegree() = 90.0f;
		glm::vec3 target{ glm::vec3{Robot::getInstance()->getPositionVector().x, Robot::getInstance()->getPositionVector().y,Robot::getInstance()->getPositionVector().z + 0.1f} };
		Robot::getInstance()->getDirectionVector() = glm::normalize(target - Robot::getInstance()->getPositionVector());
		Robot::getInstance()->getVelocity() = Robot::getInstance()->getDirectionVector() * Robot::getInstance()->getSpeed();
		Robot::getInstance()->getPositionVector() += Robot::getInstance()->getVelocity();
		Robot::getInstance()->getLegPositionVector() += Robot::getInstance()->getVelocity();
		PrintLog();
	}

	if (GetAsyncKeyState(KEY_D)) {
			Robot::getInstance()->getLeftLegDegree() += Robot::getInstance()->getLegDegreeAmount();
		Robot::getInstance()->getRightLegDegree() -= Robot::getInstance()->getLegDegreeAmount();
		Robot::getInstance()->getLeftArmDegree() -= Robot::getInstance()->getArmDegreeAmount();
		Robot::getInstance()->getRightArmDegree() += Robot::getInstance()->getArmDegreeAmount();

		if (Robot::getInstance()->getLeftLegDegree() > 7.0f || Robot::getInstance()->getLeftLegDegree() < -7.0f) {
			Robot::getInstance()->getLegDegreeAmount() = -Robot::getInstance()->getLegDegreeAmount();
		}
		if (Robot::getInstance()->getLeftArmDegree() > 7.0f || Robot::getInstance()->getLeftArmDegree() < -7.0f) {
			Robot::getInstance()->getArmDegreeAmount() = -Robot::getInstance()->getArmDegreeAmount();
		}

		if (Robot::getInstance()->getPositionVector().x > 2.0f) {
			Robot::getInstance()->getPositionVector().x = -2.0f;
			Robot::getInstance()->getLegPositionVector().x = -2.0f;

		}
		Robot::getInstance()->getRotationDegree() = 180.0f;
		glm::vec3 target{ glm::vec3{Robot::getInstance()->getPositionVector().x + 0.1f, Robot::getInstance()->getPositionVector().y,Robot::getInstance()->getPositionVector().z} };
		Robot::getInstance()->getDirectionVector() = glm::normalize(target - Robot::getInstance()->getPositionVector());
		Robot::getInstance()->getVelocity() = Robot::getInstance()->getDirectionVector() * Robot::getInstance()->getSpeed();
		Robot::getInstance()->getPositionVector() += Robot::getInstance()->getVelocity();
		Robot::getInstance()->getLegPositionVector() += Robot::getInstance()->getVelocity();
		PrintLog();
	}

	if (GetAsyncKeyState(VK_SPACE)) {
		Robot::getInstance()->isOnJump() = true;
		std::cout << Robot::getInstance()->getPositionVector().y << "\n";
	}

	if (Robot::getInstance()->isOnJump()) {

		std::cout << "Robot jumpForce: " << Robot::getInstance()->getJumpForce() << '\n';
		std::cout << "Robot jumpVelocity: " << Robot::getInstance()->getJumpVelocity() << '\n';
		std::cout << "Robot y: " << Robot::getInstance()->getPositionVector().y << '\n';
		std::cout << "Robot Leg Y : " << Robot::getInstance()->getLegPositionVector().y << "\n";
		//Robot::getInstance()->getJumpVelocity() = Velocity;
		
		if(Robot::getInstance()->getJumpVelocity() > 0.0f)
			Robot::getInstance()->getJumpForce() = (0.5f * Gravity * powf(Robot::getInstance()->getJumpVelocity(), 2));
		else
			Robot::getInstance()->getJumpForce() = -(0.5f * Gravity * powf(Robot::getInstance()->getJumpVelocity(), 2));
		
		Robot::getInstance()->getPositionVector().y += Robot::getInstance()->getJumpForce();
		Robot::getInstance()->getLegPositionVector().y += Robot::getInstance()->getJumpForce();
		Robot::getInstance()->getJumpVelocity() -= 0.1f;

		if (Robot::getInstance()->getPositionVector().y < 0.0f) {
			Robot::getInstance()->isOnJump() = false;
			Robot::getInstance()->getJumpVelocity() = Velocity;
		}
	}

	if (Stage::getInstance()->isOpenFrontSide()) {
		if (Stage::getInstance()->getFrontPositionVector().y <= 3.95f) {
	//	std::cout << Stage::getInstance()->getFrontPositionVector().y << '\n';
			Stage::getInstance()->getFrontPositionVector().y += 0.05f;
		}
	}
	else {
		if (Stage::getInstance()->getFrontPositionVector().y >= 0.0f) {
			Stage::getInstance()->getFrontPositionVector().y -= 0.05f;
		}
	}
	glutTimerFunc(10, TimerFunc, 1);
	glutPostRedisplay();
}

void PrintLog()
{
	std::cout << "Robot x: " << Robot::getInstance()->getPositionVector().x << '\n';
	std::cout << "Robot y: " << Robot::getInstance()->getPositionVector().y << '\n';
	std::cout << "Robot z: " << Robot::getInstance()->getPositionVector().z << '\n';

	std::cout << "Robot Leg X : " << Robot::getInstance()->getLegPositionVector().x << "\n";
	std::cout << "Robot Leg Y : " << Robot::getInstance()->getLegPositionVector().y << "\n";
	std::cout << "Robot Leg Z : " << Robot::getInstance()->getLegPositionVector().z << "\n";
 
	std::cout << "Obstacle x: " << Obstacle::getInstance()->getPositionVector().x << '\n';
	std::cout << "Obstacle y: " << Obstacle::getInstance()->getPositionVector().y << '\n';
	std::cout << "Obstacle z: " << Obstacle::getInstance()->getPositionVector().z << '\n';

	std::cout << "Length: " << std::sqrtf(std::powf(Obstacle::getInstance()->getPositionVector().x - Robot::getInstance()->getPositionVector().x,2) +  std::powf(Obstacle::getInstance()->getPositionVector().z - Robot::getInstance()->getPositionVector().z, 2)) << '\n';
	
	std::cout << "Robot Leg Degree: " << Robot::getInstance()->getLeftLegDegree() << "\n";


	std::cout << "------------------------------------------------------" << '\n';
}

void PrintCameraLog()
{
	std::cout << "------------------------------------------------------" << '\n';
	std::cout << "Camera Position X:" << pCamera->getPositionVector().x << "\n";
	std::cout << "Camera Position Y:" << pCamera->getPositionVector().y << "\n";
	std::cout << "Camera Position Z:" << pCamera->getPositionVector().z << "\n"<<"\n";

	std::cout << "Camera Target X:" << pCamera->getTargetVector().x << "\n";
	std::cout << "Camera Target Y:" << pCamera->getTargetVector().y << "\n";
	std::cout << "Camera Target Z:" << pCamera->getTargetVector().z << "\n" << "\n";

	std::cout << "Camera Direction X:" << pCamera->getDirectionVector().x << "\n";
	std::cout << "Camera Direction Y:" << pCamera->getDirectionVector().y << "\n";
	std::cout << "Camera Direction Z:" << pCamera->getDirectionVector().z << "\n" << "\n";

	std::cout << "Camera UpVector X:" << pCamera->getUpVector().x << "\n";
	std::cout << "Camera UpVector Y:" << pCamera->getUpVector().y << "\n";
	std::cout << "Camera UpVector Z:" << pCamera->getUpVector().z << "\n" << "\n";

	std::cout << "Camera RightVector X:" << pCamera->getRightVector().x << "\n";
	std::cout << "Camera RightVector Y:" << pCamera->getRightVector().y << "\n";
	std::cout << "Camera RightVector Z:" << pCamera->getRightVector().z << "\n";
	std::cout << "------------------------------------------------------" << '\n' << "\n";
}

