#include "flyable_enemy.hpp"

#include "map_movable.hpp"

#include <cmath>

using biv::FlyableEnemy;

FlyableEnemy::FlyableEnemy(
	const Coord& top_left,
	const int width,
	const int height,
	const int flying_height,
	const int flying_radius
) : RectMapMovableAdapter(top_left, width, height),
	flying_height(flying_height),
	flying_radius(flying_radius),
	start_pos_(top_left) {
	vspeed = 0;
	hspeed = 0.2f;
}

biv::Rect FlyableEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed FlyableEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void FlyableEnemy::move_map_left() noexcept {
	top_left.x -= MapMovable::MAP_STEP;
	start_pos_.x -= MapMovable::MAP_STEP;
}

void FlyableEnemy::move_map_right() noexcept {
	top_left.x += MapMovable::MAP_STEP;
	start_pos_.x += MapMovable::MAP_STEP;
}

void FlyableEnemy::move_horizontally() noexcept {
	const float next_x = top_left.x + hspeed;
	const float distance_from_start = std::abs(next_x - start_pos_.x);

	if (distance_from_start >= flying_radius) {
		const float direction = std::copysign(1.0f, hspeed);
		hspeed = -hspeed;
		top_left.x = start_pos_.x + direction * static_cast<float>(flying_radius);
		return;
	}

	top_left.x = next_x;
}

void FlyableEnemy::move_vertically() noexcept {
	// Flyable enemies ignore gravity and keep their y-position stable.
	vspeed = 0;
}

void FlyableEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	(void)obj;
	hspeed = -hspeed;
	move_horizontally();
}

void FlyableEnemy::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		vspeed = 0.15f;
		hspeed = 0.0f;
		kill();
	} else {
		mario->kill();
	}
}

void FlyableEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	(void)obj;
	// Flying enemies do not use ground collision logic.
}

void FlyableEnemy::process_platform_collision(Collisionable* platform) noexcept {
	if (platform == nullptr) {
		return;
	}

	if (get_speed().v < 0) {
		return;
	}

	const Rect platform_rect = platform->get_rect();
	if (get_rect().get_bottom() < platform_rect.get_top() - 1 || get_rect().get_bottom() > platform_rect.get_top() + 1) {
		return;
	}

	move_horizontal_offset(platform->get_speed().h);
}
