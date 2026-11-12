#pragma once

#include "console_ui_obj_rect_adapter.hpp"
#include "mario.hpp"

namespace biv {
	class ConsoleMario : public Mario, public ConsoleUIObjectRectAdapter {
		public:
			ConsoleMario(const Coord& top_left, const int width, const int height);

			char get_brush() const noexcept override;
	};
}
