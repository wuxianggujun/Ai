#include <iostream>
#include <AiCore.h>
#include <Shader.h>

#include <Texture.h>

#include <thread>

void addObjectsFunction() 
{
	// TODO::Replace with template.
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

void rotateTex(std::shared_ptr<Ai::AiTexQuadObject> obj) 
{
	auto& rotate = obj->getRotate();
	auto& scale = obj->getScale();
	scale.x = 1.2f;
	std::chrono::milliseconds waitTime(10);
	while(true){
		std::this_thread::sleep_for(waitTime);
		rotate.z += 1.0f;
	}
}

int main() 
{
	Ai::renderAiInit();

	//// Demo1
	//std::thread t(addObjectsFunction);
	//t.detach();

	// Demo2
	std::shared_ptr<Ai::AiTexQuadObject> tex = Ai::addTex(8, "azibao", "resources/textures/azi1.jpg");
	auto tex2 = Ai::addTex(9, "azibao", "resources/textures/azibao.jpg");
	auto& translation = tex2->getTranslate();
	translation.x = 2.0f;
	std::thread t2(rotateTex, tex);
	t2.detach();

	// Demo3
	auto cube = Ai::addPureCube(9);
	auto& scale = cube->getScale();
	scale *= 0.1;
	auto& position = cube->getTranslate();
	position.x = -2.0f;
	cube->setColor(1.0f, 0.0f, 0.0f);

	// RenderLoop
	Ai::renderAi();

	std::cout << "Waiting...Waiting..." << std::endl;
	std::cout << "Here has a window now..." << std::endl;
}
