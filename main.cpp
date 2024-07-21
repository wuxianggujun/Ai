#include <iostream>
#include <AiCore.h>
#include <Shader.h>

int main() {
	Ai::renderAiInit();
	// TODO::Replace with template.
	Ai::addTriangle(0, 0.5f, 0.5f, 0.25f, 0.25f);
	Ai::addTriangle(1, 0.25f, 0.25f, 0.5f, 0.5f);
	Ai::addTriangle(2, 0.25f, 0.25f, 0.75f, 0.5f);
	Ai::addSquare(3, 0.25f, 0.25f, 0.5f, 0.75f, 0.0f, 0.0f, 1.0f);
	Ai::addSquare(4, 0.25f, 0.25f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f);
	Ai::addSquare(5, 0.25f, 0.25f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f);
	Ai::addLine(6, -0.9f, -0.9f, 0.9f, -0.9f, 1.0f, 1.0f, 0.0f);
	Ai::addCircle(7, 2.0f, 2.0f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f);
	Ai::renderAi();

	std::cout << "Waiting...Waiting..." << std::endl;
	std::cout << "Here has a window now..." << std::endl;
	Shader myShader("resources/shaders/test.vs", "resources/shaders/test.fs");
}