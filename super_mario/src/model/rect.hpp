#pragma once

#include "coord.hpp"
//Класс для позиционирования всех объектов
namespace biv {
	class Rect {
		protected:
			Coord top_left; // Левый верхний угол объекта
			int width;
			int height;

		public:
			Rect() = default;
			Rect(const Coord& top_left, const int width, const int height);

			int get_bottom() const noexcept;
			int get_height() const noexcept;
			int get_left() const noexcept;
			int get_right() const noexcept;
			int get_top() const noexcept;
			float get_x() const noexcept;
			float get_y() const noexcept;
	};
}
