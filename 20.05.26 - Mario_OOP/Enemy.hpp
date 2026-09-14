#pragma once 
#include "MovingItems.hpp"
#include "Constants.hpp"

namespace pav{
	class Enemy: public MovingItem {
	public:
		Enemy(const float xPos, const float yPos, 
		           const float oWidth, const float oHeight)
			: MovingItem(xPos, yPos, oWidth, oHeight, ENEMY) {}

		~Enemy() override = default;

	};

}