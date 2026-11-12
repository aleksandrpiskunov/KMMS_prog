#pragma once

#include "box.hpp"
#include "enemy.hpp"
#include "flyable_enemy.hpp"
#include "full_box.hpp"
#include "jumping_enemy.hpp"
#include "mario.hpp"
#include "money.hpp"
#include "moving_platform.hpp"
#include "ship.hpp"
#include "qt_ui_object.hpp"

namespace biv {
	#define QT_OBJECT_CLASS(name, model, kind) \
		class name final : public model, public QtUIObjectRectAdapter { \
			public: \
				name(const Coord& pos, const int width, const int height) \
					: Rect(pos, width, height), model(pos, width, height), QtUIObjectRectAdapter(pos, width, height) {} \
				QtObjectKind get_kind() const noexcept override { return QtObjectKind::kind; } \
		}

	QT_OBJECT_CLASS(QtBox, Box, Box);
	QT_OBJECT_CLASS(QtEnemy, Enemy, Enemy);
	class QtFlyableEnemy final : public FlyableEnemy, public QtUIObjectRectAdapter {
		public:
			QtFlyableEnemy(const Coord& pos, int width, int height, int flying_height, int flying_radius)
				: Rect(pos, width, height), FlyableEnemy(pos, width, height, flying_height, flying_radius),
				  QtUIObjectRectAdapter(pos, width, height) {}
			QtObjectKind get_kind() const noexcept override { return QtObjectKind::FlyingEnemy; }
	};
	QT_OBJECT_CLASS(QtJumpingEnemy, JumpingEnemy, JumpingEnemy);
	QT_OBJECT_CLASS(QtMario, Mario, Mario);
	QT_OBJECT_CLASS(QtMoney, Money, Money);
	class QtMovingPlatform final : public MovingPlatform, public QtUIObjectRectAdapter {
		public:
			QtMovingPlatform(const Coord& pos, int width, int height, int travel_radius)
				: Rect(pos, width, height), MovingPlatform(pos, width, height, travel_radius),
				  QtUIObjectRectAdapter(pos, width, height) {}
			QtObjectKind get_kind() const noexcept override { return QtObjectKind::MovingPlatform; }
	};

	class QtFullBox final : public FullBox, public QtUIObjectRectAdapter {
		public:
			QtFullBox(const Coord& pos, const int width, const int height, UIFactory* factory)
				: Rect(pos, width, height), FullBox(pos, width, height, factory),
				  QtUIObjectRectAdapter(pos, width, height) {}
			QtObjectKind get_kind() const noexcept override { return QtObjectKind::FullBox; }
			bool is_empty() const noexcept override { return FullBox::is_empty(); }
	};

	class QtShip final : public Ship, public QtUIObjectRectAdapter {
		public:
			QtShip(const Coord& pos, const int width, const int height)
				: Rect(pos, width, height), Ship(pos, width, height),
				  QtUIObjectRectAdapter(pos, width, height) {}
			QtObjectKind get_kind() const noexcept override { return QtObjectKind::Ship; }
			bool is_final() const noexcept override { return Ship::is_final(); }
	};

	#undef QT_OBJECT_CLASS
}
