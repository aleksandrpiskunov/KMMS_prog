#pragma once

#include "console_ui_obj_rect_adapter.hpp"
#include "ship.hpp"

namespace biv {
	class ConsoleShip : public Ship, public ConsoleUIObjectRectAdapter {
		public:
			ConsoleShip(const Coord& top_left, const int width, const int height);
			
			char get_brush() const noexcept override;
	};
}
