#include <iostream>
#include <AiCore.h>
#include <Shader.h>
#include <Texture.h>

#include <thread>

void addObjectsFunction() {
	std::chrono::seconds waitTime(1);
	Ai::addTriangle(0, 0.5f, 0.5f, 0.25f, 0.25f);
	std::this_thread::sleep_for(waitTime);
	Ai::addTriangle(1, 0.25f, 0.25f, 0.5f, 0.5f);
	std::this_thread::sleep_for(waitTime);
	Ai::addTriangle(2, 0.25f, 0.25f, 0.75f, 0.5f);
	std::this_thread::sleep_for(waitTime);
	Ai::addSquare(3, 0.25f, 0.25f, 0.5f, 0.75f, 0.0f, 0.0f, 1.0f);
	std::this_thread::sleep_for(waitTime);
	Ai::addSquare(4, 0.25f, 0.25f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f);
	std::this_thread::sleep_for(waitTime);
	Ai::addSquare(5, 0.25f, 0.25f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f);
	std::this_thread::sleep_for(waitTime);
	Ai::addLine(6, -0.9f, -0.9f, 0.9f, -0.9f, 1.0f, 1.0f, 0.0f);
	std::this_thread::sleep_for(waitTime);
	Ai::addCircle(7, 2.0f, 2.0f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f);
}

int main() {
	Ai::renderAiInit();

	std::thread t(addObjectsFunction);
	t.detach();

	// TODO::Replace with template.
	Ai::addTriangle(0, 0.5f, 0.5f, 0.25f, 0.25f);
	//Ai::addTriangle(1, 0.25f, 0.25f, 0.5f, 0.5f);
	//Ai::addTriangle(2, 0.25f, 0.25f, 0.75f, 0.5f);
	//Ai::addSquare(3, 0.25f, 0.25f, 0.5f, 0.75f, 0.0f, 0.0f, 1.0f);
	//Ai::addSquare(4, 0.25f, 0.25f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f);
	//Ai::addSquare(5, 0.25f, 0.25f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f);
	//Ai::addLine(6, -0.9f, -0.9f, 0.9f, -0.9f, 1.0f, 1.0f, 0.0f);
	//Ai::addCircle(7, 2.0f, 2.0f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f);	
	Ai::renderAi();

	Texture2D tex("resources/textures/azi1.jpg");

	std::cout << "Waiting...Waiting..." << std::endl;
	std::cout << "Here has a window now..." << std::endl;
}