#pragma once

#define NumOfSnow 150
#define NumOfPillar 6

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")

#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

enum class State { IDLE = 0, ROTATE, REVOLVE, FALL };