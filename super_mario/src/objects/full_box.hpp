#pragma once

#include "box.hpp"
#include "collisionable.hpp"
#include "ui_factory.hpp"

namespace biv {
	class FullBox : public Box, public Collisionable {
		protected:
			UIFactory* ui_factory;

		public:
			FullBox(
				const Coord& top_left, 
				const int width, const int height,
				UIFactory* ui_factory
			);
			
			Rect get_rect() const noexcept override;
			Speed get_speed() const noexcept override;
			
			void process_horizontal_static_collision(Rect*) noexcept override;
			void process_mario_collision(Collisionable*) noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
	};
}
