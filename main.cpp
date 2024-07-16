#include <iostream>
#include <AiCore.h>

int main() {
	Ai::renderAiInit();
	Ai::addTriangle(0.5f, 0.5f, 0.25f, 0.25f);
	Ai::addTriangle(0.25f, 0.25f, 0.5f, 0.5f);
	Ai::addTriangle(0.25f, 0.25f, 0.75f, 0.5f);
	Ai::addTriangle(0.25f, 0.25f, 0.5f, 0.75f);
	Ai::addTriangle(0.25f, 0.25f, -0.5f, -0.5f);
	Ai::renderAi();
	std::cout << "Waiting...Waiting..." << std::endl;
	std::cout << "Here has a window now..." << std::endl;
}