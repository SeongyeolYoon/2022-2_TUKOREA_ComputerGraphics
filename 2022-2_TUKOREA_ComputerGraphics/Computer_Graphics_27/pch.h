#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define PILLARS 6
#define SNOWS 50

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