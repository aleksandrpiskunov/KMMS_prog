#pragma once

#include "rect.hpp"

namespace biv {
	class Movable : virtual public Rect {
		protected:
			static constexpr float JUMP_SPEED = -1.0f;
			static constexpr float MAX_V_SPEED = 0.98f;
			static constexpr float V_ACCELERATION = 0.05f;

			float vspeed = 0;
			float hspeed = 0;

		protected:
			Movable() = default;
			Movable(
				const Coord& top_left, 
				const int width, const int height, 
				const float vspeed, const float hspeed
			);

		public:
			float get_vspeed() const noexcept;
			void jump() noexcept;
			void move_horizontal_offset(const float offset) noexcept;
			void move_vertical_offset(const float offset) noexcept;
			
			virtual void move_horizontally() noexcept;
			virtual void move_vertically() noexcept;
	};
}
