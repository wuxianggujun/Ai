#include <Painter.h>

namespace Ai {
	ObjectType Line::getObjectType() {
		return ObjectType::LINE;
	}

	unsigned int Line::getId() {
		return m_id;
	}

	std::pair<float, float>& Line::getStartPoint() {
		return startPoint;
	}

	std::pair<float, float>& Line::getEndPoint() {
		return endPoint;
	}

	std::tuple<float, float, float>& Line::getColor() {
		return color;
	}

	unsigned int Polygon::getId() {
		return m_id;
	}

	std::pair<float, float>& Polygon::getScale() {
		return scale;
	}

	std::pair<float, float>& Polygon::getPosition() {
		return pos;
	}

	std::tuple<float, float, float>& Polygon::getColor() {
		return color;
	}

	ObjectType Triangle::getObjectType() {
		return ObjectType::TRIANGLE;
	}

	unsigned int Triangle::getId() {
		return m_id;
	}

	ObjectType Square::getObjectType() {
		return ObjectType::SQUARE;
	}

	unsigned int Square::getId() {
		return m_id;
	}
}
