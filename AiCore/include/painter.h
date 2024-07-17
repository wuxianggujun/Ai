#pragma once
#ifndef PAINTER_H
#define PAINTER_H

#include <utility>
#include <tuple>

namespace Ai {
	enum class ObjectType : unsigned int {
		TRIANGLE,
		SQUARE
	};

	class Painter {
	private:
		std::pair<float, float> scale;
		std::pair<float, float> pos;
		std::tuple<float, float, float> color;
	public:
		Painter(float xscale, float yscale, float xpos, float ypos) 
		: scale(xscale, yscale), pos(xpos, ypos), color(1.0f, 1.0f, 1.0f) {}

		Painter(float xscale, float yscale, float xpos, float ypos, float red, float green, float blue)
			: scale(xscale, yscale), pos(xpos, ypos), color(red, green, blue) {}

		virtual std::pair<float, float>& getScale();
		virtual std::pair<float, float>& getPosition();
		virtual std::tuple<float, float, float>& getColor();
		virtual ObjectType getObjectType() = 0;
	};

	class Triangle : public Painter {
	public:
		Triangle(float xscale, float yscale, float xpos, float ypos)
		: Painter(xscale, yscale, xpos, ypos){}

		Triangle(float xscale, float yscale, float xpos, float ypos, float red, float green, float blue)
			: Painter(xscale, yscale, xpos, ypos, red, green, blue) {}

		virtual ObjectType getObjectType() override;
	};

	class Square : public Painter {
	public:
		Square(float xscale, float yscale, float xpos, float ypos)
		: Painter(xscale, yscale, xpos, ypos) {}

		Square(float xscale, float yscale, float xpos, float ypos, float red, float green, float blue)
			: Painter(xscale, yscale, xpos, ypos, red, green, blue) {}

		virtual ObjectType getObjectType() override;
	};
}
#endif