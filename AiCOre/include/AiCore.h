#ifndef AI_CORE
#define AI_CORE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <vector>
#include <map>
#include <string>

namespace Ai {
	enum class ObjectType : unsigned int {
		TRIANGLE,
		SQUARE
	};

	void glfwWindowInit();

	void renderAiInit();

	void renderAi();

	void addShader();

	void addObject(ObjectType type);

	void addTriangle();
}

#endif