#pragma once

#include "rect_map_movable_adapter.hpp"

namespace biv {
	class Ship : public RectMapMovableAdapter {
		public:
			Ship(
				const Coord& top_left, const int width, const int height
			) : RectMapMovableAdapter(top_left, width, height) {}
	};
}
