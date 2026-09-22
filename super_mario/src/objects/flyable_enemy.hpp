#pragma once

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect.hpp"
#include "rect_map_movable_adapter.hpp"
#include "speed.hpp"

namespace biv {
	class FlyableEnemy : public RectMapMovableAdapter, public Movable, public Collisionable {
		private:
			const int flying_height;
			const int flying_radius;
			Coord start_pos_;

		public:
			FlyableEnemy(
				const Coord& top_left,
				const int width,
				const int height,
				const int flying_height,
				const int flying_radius
			);

			Rect get_rect() const noexcept override;
			Speed get_speed() const noexcept override;

			int get_flying_height() const noexcept {
				return flying_height;
			}
			int get_flying_radius() const noexcept {
				return flying_radius;
			}

			void move_map_left() noexcept override;
			void move_map_right() noexcept override;
			void move_horizontally() noexcept override;
			void move_vertically() noexcept override;
			void process_horizontal_static_collision(Rect*) noexcept override;
			void process_mario_collision(Collisionable*) noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
			void process_platform_collision(Collisionable* platform) noexcept override;
	};
}