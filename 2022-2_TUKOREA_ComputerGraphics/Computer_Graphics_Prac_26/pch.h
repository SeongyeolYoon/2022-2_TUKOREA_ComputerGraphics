#pragma once

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

enum class Axis { NONE = 0, X, Y };
enum class Direction{ NONE = 0, POSITIVE, NEGATIVE };
enum class Shape{ NONE = 0, CUBE, PYRAMID };