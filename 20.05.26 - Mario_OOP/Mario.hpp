#pragma once
#include "MovingItems.hpp"

namespace pav{
	class Game;
	class Mario : public MovingItem {

	public:
		Mario(const float xPos, const float yPos,
		      const float oWidth, const float oHeight,
		      const char inType)
			: MovingItem(xPos, yPos, oWidth, oHeight, inType) {}
		~Mario() = default;
		
		void reset(const float xPos, const float yPos,
		           const float oWidth, const float oHeight,
		           const char inType) {
			x = xPos;
			y = yPos;
			width = oWidth;
			height = oHeight;
			vertSpeed = 0.0f;
			IsFly = false;
			cType = inType;
			horizSpeed = 0.0f;
		}

		void update(Game &game);

		void jump(const float speed) {
			if (!IsFly) {
				vertSpeed = speed;
			}
		}

		bool is_flying() const {
			return IsFly;
		}

		void mario_collision(Game &game);
		void player_dead(Game &game);
	};

}