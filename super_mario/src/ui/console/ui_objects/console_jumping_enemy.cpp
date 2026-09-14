#include "console_jumping_enemy.hpp"

using biv::ConsoleJumpingEnemy;

ConsoleJumpingEnemy::ConsoleJumpingEnemy(
	const Coord& top_left,
	const int width,
	const int height
) : JumpingEnemy(top_left, width, height) {}

char ConsoleJumpingEnemy::get_brush() const noexcept {
	return 'J';
}
