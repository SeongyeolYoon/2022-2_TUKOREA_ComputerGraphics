#pragma once

#include "pch.h"
#include "Object.h"
#include "Shader.h"

class Floor : public Object {
private:
	static Floor* pInst;
private:
	Floor();
public:
	static Floor* getInstance();

	virtual void initialize(const char* objName);

	virtual void readObj(const char* objName);

	virtual void update();

	virtual void render();

	virtual void release();

	friend class Shader;
};