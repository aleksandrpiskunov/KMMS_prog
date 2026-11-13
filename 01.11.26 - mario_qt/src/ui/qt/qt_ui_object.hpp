#pragma once

#include "rect.hpp"

namespace biv {
	enum class QtObjectKind {
		Mario,
		Enemy,
		FlyingEnemy,
		JumpingEnemy,
		Box,
		FullBox,
		Money,
		MovingPlatform,
		Ship
	};

	class QtUIObject {
		public:
			// Виртуальный деструктор позволяет безопасно удалять Qt-обёртки через интерфейс.
			virtual ~QtUIObject() = default;
			// Возвращают координаты объекта модели для расчёта области спрайта.
			virtual int get_bottom() const noexcept = 0;
			virtual int get_left() const noexcept = 0;
			virtual int get_right() const noexcept = 0;
			virtual int get_top() const noexcept = 0;
			virtual QtObjectKind get_kind() const noexcept = 0;
			// Дополнительное состояние блока; по умолчанию объект не является пустым.
			virtual bool is_empty() const noexcept { return false; }
			// Дополнительное состояние финишной платформы.
			virtual bool is_final() const noexcept { return false; }
	};

	class QtUIObjectRectAdapter : virtual public Rect, public QtUIObject {
		public:
			// Связывает координаты модели Rect с интерфейсом Qt-представления.
			QtUIObjectRectAdapter(const Coord& top_left, const int width, const int height)
				: Rect(top_left, width, height) {}

			// Передают Qt-представлению координаты из модели без копирования состояния.
			int get_bottom() const noexcept override { return Rect::get_bottom(); }
			int get_left() const noexcept override { return Rect::get_left(); }
			int get_right() const noexcept override { return Rect::get_right(); }
			int get_top() const noexcept override { return Rect::get_top(); }
	};
}
