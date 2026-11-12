#pragma once

#include "console_ui_obj_rect_adapter.hpp"
#include "money.hpp"

namespace biv {
	class ConsoleMoney : public Money, public ConsoleUIObjectRectAdapter {
		public:
			ConsoleMoney(const Coord& top_left, const int width, const int height);

			char get_brush() const noexcept override;
	};
}
