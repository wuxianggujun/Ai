#ifndef AI_CORE
#define AI_CORE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

#include <vector>
#include <map>
#include <string>

#include <painter.h>

namespace Ai {
	void renderAiInit();

	void renderAi();

	void addCanvasShader();

	void addTriangle(float xscale, float yscale, float xpos, float ypos);

	void addTriangle();
}

#endif