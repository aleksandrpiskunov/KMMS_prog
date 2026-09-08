#pragma once

#include "console_ui_obj_rect_adapter.hpp"
#include "box.hpp"

namespace biv {
	class ConsoleBox : public Box, public ConsoleUIObjectRectAdapter {
		public:
			ConsoleBox(const Coord& top_left, const int width, const int height);
			
			char get_brush() const noexcept override;
	};
}
