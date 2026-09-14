#pragma once 
#include "MovingItems.hpp"
#include "Constants.hpp"

namespace pav{
	class Money: public MovingItem {
	public:
		Money(const float xPos, const float yPos, 
		           const float oWidth, const float oHeight)
			: MovingItem(xPos, yPos, oWidth, oHeight, MYSTERY_BLOCK) {}

		~Money() override = default;
	};

}
