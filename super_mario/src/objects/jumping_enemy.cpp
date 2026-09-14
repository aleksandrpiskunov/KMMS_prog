#include "jumping_enemy.hpp"

#include "map_movable.hpp"

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(
	const Coord& top_left,
	const int width,
	const int height
) : RectMapMovableAdapter(top_left, width, height) {
	vspeed = 0;
	hspeed = 0;
}

biv::Rect JumpingEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed JumpingEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void JumpingEnemy::move_map_left() noexcept {
	top_left.x -= MapMovable::MAP_STEP;
}

void JumpingEnemy::move_map_right() noexcept {
	top_left.x += MapMovable::MAP_STEP;
}

void JumpingEnemy::move_horizontally() noexcept {
	// Enemy stands in place horizontally, but still moves with the map as usual.
}

void JumpingEnemy::move_vertically() noexcept {
	if (on_ground_ && !jump_started_) {
		vspeed = JUMP_SPEED * 0.65f;
		jump_started_ = true;
		on_ground_ = false;
	}

	if (vspeed < MAX_V_SPEED) {
		vspeed += V_ACCELERATION;
	}
	top_left.y += vspeed;
}

void JumpingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	(void)obj;
	hspeed = -hspeed;
}

void JumpingEnemy::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		vspeed = 0.15f;
		hspeed = 0.0f;
		kill();
	} else {
		mario->kill();
	}
}

void JumpingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	if (vspeed >= 0) {
		top_left.y = obj->get_top() - height;
		vspeed = 0.0f;
		on_ground_ = true;
		jump_started_ = false;
	} else {
		top_left.y = obj->get_bottom();
	}
}
