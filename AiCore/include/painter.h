#pragma once
#ifndef PAINTER_H
#define PAINTER_H

#include <utility>

namespace Ai {
	enum class ObjectType : unsigned int {
		TRIANGLE,
		SQUARE
	};

	class Painter {
	private:
		std::pair<float, float> scale;
		std::pair<float, float> pos;
	public:
		Painter(float xscale, float yscale, float xpos, float ypos) 
		: scale(xscale, yscale), pos(xpos, ypos) {}

		virtual std::pair<float, float> getScale();
		virtual std::pair<float, float> getPosition();
		virtual ObjectType getObjectType() = 0;
	};

	class Triangle : public Painter {
	public:
		Triangle(float xscale, float yscale, float xpos, float ypos)
		: Painter(xscale, yscale, xpos, ypos){}

		virtual ObjectType getObjectType() override;
	};

	class Square : public Painter {
	public:
		Square(float xscale, float yscale, float xpos, float ypos)
		: Painter(xscale, yscale, xpos, ypos) {}

		virtual ObjectType getObjectType() override;
	};
}
#endif