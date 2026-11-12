#pragma once

#include "console_ui_obj_rect_adapter.hpp"
#include "flyable_enemy.hpp"

namespace biv {
	class ConsoleFlyableEnemy : public FlyableEnemy, public ConsoleUIObjectRectAdapter {
		public:
			ConsoleFlyableEnemy(
				const Coord& top_left,
				const int width,
				const int height,
				const int flying_height,
				const int flying_radius
			);

			char get_brush() const noexcept override;
	};
}
