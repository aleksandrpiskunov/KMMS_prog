#pragma once

#include "console_ui_obj_rect_adapter.hpp"
#include "full_box.hpp"

namespace biv {
	class ConsoleFullBox : public FullBox, public ConsoleUIObjectRectAdapter {
		public:
			ConsoleFullBox(
				const Coord& top_left, 
				const int width, const int height,
				UIFactory* ui_factory
			);
			
			char get_brush() const noexcept override;
	};
}
