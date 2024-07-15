#include <iostream>
#include <AiCore.h>

int main() {
	Ai::renderAiInit();
	//Ai::addObject(Ai::ObjectType::TRIANGLE);
	Ai::renderAi();
	std::cout << "Waiting...Waiting..." << std::endl;
	std::cout << "Here has a window now..." << std::endl;
}