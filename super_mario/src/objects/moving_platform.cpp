#include "moving_platform.hpp"

#include "map_movable.hpp"

#include <cmath>

using biv::MovingPlatform;

MovingPlatform::MovingPlatform(
	const Coord& top_left,
	const int width,
	const int height,
	const int travel_radius
) : RectMapMovableAdapter(top_left, width, height),
	start_pos_(top_left),
	travel_radius_(travel_radius) {
	vspeed = 0;
	hspeed = 0.2f;
}

biv::Rect MovingPlatform::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed MovingPlatform::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void MovingPlatform::move_map_left() noexcept {
	top_left.x -= MapMovable::MAP_STEP;
	start_pos_.x -= MapMovable::MAP_STEP;
}

void MovingPlatform::move_map_right() noexcept {
	top_left.x += MapMovable::MAP_STEP;
	start_pos_.x += MapMovable::MAP_STEP;
}

void MovingPlatform::move_horizontally() noexcept {
	const float next_x = top_left.x + hspeed;
	const float distance_from_start = std::abs(next_x - start_pos_.x);

	if (distance_from_start >= travel_radius_) {
		const float direction = std::copysign(1.0f, hspeed);
		hspeed = -hspeed;
		top_left.x = start_pos_.x + direction * static_cast<float>(travel_radius_);
		return;
	}

	top_left.x = next_x;
}

void MovingPlatform::move_vertically() noexcept {
	vspeed = 0;
}

void MovingPlatform::process_horizontal_static_collision(Rect* obj) noexcept {
	(void)obj;
	hspeed = -hspeed;
	move_horizontally();
}

void MovingPlatform::process_mario_collision(Collisionable* mario) noexcept {
	mario->process_platform_collision(this);
}

void MovingPlatform::process_platform_collision(Collisionable* platform) noexcept {
	// Platforms don't interact with other platforms
	(void)platform;
}

void MovingPlatform::process_vertical_static_collision(Rect* obj) noexcept {
	(void)obj;
}
