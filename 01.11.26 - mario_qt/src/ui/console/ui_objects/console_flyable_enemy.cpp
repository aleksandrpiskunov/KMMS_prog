#include "console_flyable_enemy.hpp"

using biv::ConsoleFlyableEnemy;

ConsoleFlyableEnemy::ConsoleFlyableEnemy(
	const Coord& top_left,
	const int width,
	const int height,
	const int flying_height,
	const int flying_radius
) : FlyableEnemy(top_left, width, height, flying_height, flying_radius) {}

char ConsoleFlyableEnemy::get_brush() const noexcept {
	return 'F';
}
