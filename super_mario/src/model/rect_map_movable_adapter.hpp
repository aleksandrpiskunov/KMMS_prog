/**
	- Почему класс Rect наследуется виртуальным образом?
	: To avoid the problem of multiple inheritance. Without it Enemy and money can get to copies of Rect base class

	- Что такое паттерн адаптер?
	
	- Для чего он применяется здесь?
	: MapMovable is object that is moving with a map - attachment objects to map
 	: Movable is object that can move itself - object physics
	: That adapter is needed to link Rect and MapMovable classes. 

	- Какую ещё роль выполняет этот класс?
	: Avoiding copying move_map_left/right logic in Enemy, Money etc. classes, that a virtual method from MapMovable class
*/

#pragma once

#include "map_movable.hpp"
#include "rect.hpp"

namespace biv {
	class RectMapMovableAdapter : virtual public Rect, public MapMovable {
		public:
			RectMapMovableAdapter(const Coord& top_left, const int width, const int height);
			
			void move_map_left() noexcept override;
			void move_map_right() noexcept override;
	};
}