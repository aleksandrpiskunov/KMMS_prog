#pragma once

#include "rect.hpp"

namespace biv {
	class ConsoleUIObject {
		public:
			virtual int get_bottom() const noexcept = 0;
			virtual char get_brush() const noexcept = 0;
			virtual int get_height() const noexcept = 0;
			virtual int get_left() const noexcept = 0;
			virtual int get_right() const noexcept = 0;
			virtual int get_top() const noexcept = 0;
	};
}
