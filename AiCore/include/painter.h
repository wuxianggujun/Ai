#pragma once
#ifndef PAINTER_H
#define PAINTER_H

#include <utility>
#include <tuple>

namespace Ai {
	enum class ObjectType : unsigned int {
		LINE,
		TRIANGLE,
		SQUARE
	};

	class Painter {
	public:
		unsigned int m_id;
		Painter(unsigned int id)
			: m_id(id){}

		virtual ObjectType getObjectType() = 0;
		virtual unsigned int getId() = 0;
	};

	class Line : public Painter {
	private:
		std::pair<float, float> startPoint;
		std::pair<float, float> endPoint;
		std::tuple<float, float, float> color;
	public:
		Line(unsigned int id, float startPointX, float startPointY, float endPointX, float endPointY)
			: Painter(id), startPoint(startPointX, startPointY), endPoint(endPointX, endPointY), color(1.0f, 1.0f, 1.0f){}

		Line(unsigned int id, float startPointX, float startPointY, float endPointX, float endPointY,
			float red, float green, float blue)
			: Painter(id), startPoint(startPointX, startPointY), endPoint(endPointX, endPointY), color(red, green, blue) {}

		virtual ObjectType getObjectType() override;
		virtual unsigned int getId() override;
		std::pair<float, float>& getStartPoint();
		std::pair<float, float>& getEndPoint();
		virtual std::tuple<float, float, float>& getColor();
	};

	class Polygon : public Painter {
	private:
		std::pair<float, float> scale;
		std::pair<float, float> pos;
		std::tuple<float, float, float> color;
	public:
		Polygon(unsigned int id, float xscale, float yscale, float xpos, float ypos)
			: Painter(id), scale(xscale, yscale), pos(xpos, ypos), color(1.0f, 1.0f, 1.0f){}

		Polygon(unsigned int id, float xscale, float yscale, float xpos, float ypos, float red, float green, float blue)
			:Painter(id), scale(xscale, yscale), pos(xpos, ypos), color(red, green, blue) {}

		virtual ObjectType getObjectType() = 0;
		virtual unsigned int getId() = 0;

		virtual std::pair<float, float>& getScale();
		virtual std::pair<float, float>& getPosition();
		virtual std::tuple<float, float, float>& getColor();
	};

	class Triangle : public Polygon {
	public:
		Triangle(unsigned int id, float xscale, float yscale, float xpos, float ypos)
		: Polygon(id, xscale, yscale, xpos, ypos){}

		Triangle(unsigned int id, float xscale, float yscale, float xpos, float ypos, float red, float green, float blue)
			: Polygon(id, xscale, yscale, xpos, ypos, red, green, blue) {}

		virtual ObjectType getObjectType() override;

		virtual unsigned int getId() override;
	};

	class Square : public Polygon {
	public:
		Square(unsigned int id, float xscale, float yscale, float xpos, float ypos)
		: Polygon(id, xscale, yscale, xpos, ypos) {}

		Square(unsigned int id, float xscale, float yscale, float xpos, float ypos, float red, float green, float blue)
			: Polygon(id, xscale, yscale, xpos, ypos, red, green, blue) {}

		virtual ObjectType getObjectType() override;

		virtual unsigned int getId() override;
	};
}
#endif