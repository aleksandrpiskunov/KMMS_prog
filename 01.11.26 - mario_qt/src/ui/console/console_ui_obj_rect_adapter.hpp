#pragma once

#include "console_ui_obj.hpp"
#include "rect.hpp"

namespace biv {
	class ConsoleUIObjectRectAdapter : virtual public Rect, public ConsoleUIObject {
		public:
			ConsoleUIObjectRectAdapter() = default;
			ConsoleUIObjectRectAdapter(
				const Coord& top_left, const int width, const int height
			);
		
			int get_bottom() const noexcept override;
			int get_height() const noexcept override;
			int get_left() const noexcept override;
			int get_right() const noexcept override;
			int get_top() const noexcept override;
			
			virtual char get_brush() const noexcept = 0;
	};
}
