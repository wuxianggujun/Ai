#include <iostream>
#include <AiCore.h>

int main() {
	Ai::renderAiInit();

	Ai::addTriangle(0, 0.5f, 0.5f, 0.25f, 0.25f);
	Ai::addTriangle(1, 0.25f, 0.25f, 0.5f, 0.5f);
	Ai::addTriangle(2, 0.25f, 0.25f, 0.75f, 0.5f);
	Ai::addSquare(3, 0.25f, 0.25f, 0.5f, 0.75f, 0.0f, 0.0f, 1.0f);
	Ai::addSquare(4, 0.25f, 0.25f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f);
	Ai::addSquare(5, 0.25f, 0.25f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f);
	Ai::addLine(6, -0.9f, -0.9f, 0.9f, -0.9f, 1.0f, 1.0f, 0.0f);

	Ai::renderAi();
	std::cout << "Waiting...Waiting..." << std::endl;
	std::cout << "Here has a window now..." << std::endl;
}