#pragma once

#include "rect_map_movable_adapter.hpp"

namespace biv {
	class Ship : public RectMapMovableAdapter {
		private:
			bool is_final_ = false;

		public:
			Ship(
				const Coord& top_left, const int width, const int height
			) : RectMapMovableAdapter(top_left, width, height) {}

			void set_final(bool value) noexcept {
				is_final_ = value;
			}

			bool is_final() const noexcept {
				return is_final_;
			}
	};
}
