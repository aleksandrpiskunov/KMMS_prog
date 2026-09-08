#pragma once

#include "rect.hpp"
#include "speed.hpp"

namespace biv {
	class Collisionable {
		protected:
			bool is_active_ = true;

		public:
			bool has_collision(Rect*) const noexcept;
			bool is_active() const noexcept;
			void kill() noexcept;

			virtual Rect get_rect() const noexcept = 0;
			virtual Speed get_speed() const noexcept = 0;

			virtual void process_horizontal_static_collision(Rect*) noexcept = 0;
			virtual void process_mario_collision(Collisionable*) noexcept = 0;
			virtual void process_vertical_static_collision(Rect*) noexcept = 0;
	};
}
