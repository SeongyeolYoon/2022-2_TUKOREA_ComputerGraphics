#include "Light.h"

Light* Light::pInst = nullptr;

Light::Light()
{

}

Light* Light::getInstance()
{
	if (nullptr == pInst)
		pInst = new Light;

	return pInst;
}

void Light::initialize()
{

}

glm::vec3& Light::getLightColor()
{
	return lightColor;
}

glm::vec3 Light::getPosition()
{
	return positionVector;
}
