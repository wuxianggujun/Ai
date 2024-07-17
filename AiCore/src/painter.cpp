#include "painter.h"

namespace Ai {
	std::pair<float, float>& Painter::getScale() {
		return std::pair<float, float>(scale.first, scale.second);
	}

	std::pair<float, float>& Painter::getPosition() {
		return std::pair<float, float>(pos.first, pos.second);
	}

	std::tuple<float, float, float>& Painter::getColor() {
		return color;
	}

	ObjectType Triangle::getObjectType() {
		return ObjectType::TRIANGLE;
	}

	ObjectType Square::getObjectType() {
		return ObjectType::SQUARE;
	}
}
