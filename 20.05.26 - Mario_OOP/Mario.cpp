#include "Mario.hpp"
#include "Game.hpp"
#include "Constants.hpp"

#include <ncurses.h>
#include <unistd.h>

namespace pav {

void Mario::update(Game &game) {
	IsFly = true;
	vertSpeed += GRAVITY;
	y += vertSpeed;

	if (game.get_brick_length() == 0) {
		return;
	}

	for (int i = 0; i < game.get_brick_length(); ++i) {
		const auto &brick = *game.get_bricks()[i];
		if (!is_collision(*this, brick)) {
			continue;
		}

		if ((brick.get_cType() == MYSTERY_BLOCK) && (vertSpeed < 0)) {
			game.get_bricks()[i]->set_cType(EMPTY_BLOCK);
			BaseObject *newMoving = game.create_moving(brick.get_x(), brick.get_y() - 3, 3, 2, COLLECTIBLE);
			newMoving->set_vert_speed(ITEM_BOUNCE_SPEED);
		}

		y -= vertSpeed;
		vertSpeed = 0;
		IsFly = false;

		if (brick.get_cType() == EXIT_BLOCK) {
			game.rise_level();
			if (game.get_level() > game.get_maxLvl()) {
				game.reset_level();
			}

			if (has_colors()) {
				wbkgd(stdscr, COLOR_PAIR(COLOR_COMPLETE));
				clear();
				game.show_map();
				refresh();
			}

			usleep(50000);
			game.create_level(game.get_level());

			if (has_colors()) {
				wbkgd(stdscr, COLOR_PAIR(COLOR_NORMAL));
				clear();
			}
			return;
		}

		break;
	}
}

void Mario::mario_collision(Game &game) {
	constexpr char ENEMY = 'o';
	constexpr char COLLECTIBLE = '$';
	constexpr int ENEMY_KILL_POINTS = 50;
	constexpr int COLLECTIBLE_POINTS = 100;
	constexpr float TOP_COLLISION_THRESHOLD = 0.5f;

	for (int i = 0; i < game.get_moving_length(); ++i) {
		const auto &moving = *game.get_moving()[i];
		if (!is_collision(*this, moving)) {
			continue;
		}

		switch (moving.get_cType()) {
			case ENEMY:
				if ((IsFly == true) &&
					(vertSpeed > 0) &&
					(get_y() + get_height() < moving.get_y() + moving.get_height() * TOP_COLLISION_THRESHOLD)) {
					game.set_score(game.get_score() + ENEMY_KILL_POINTS);
					game.delete_moving(i);
					--i;
				} else {
					player_dead(game);
					return;
				}
				break;
			case COLLECTIBLE:
				game.set_score(game.get_score() + COLLECTIBLE_POINTS);
				game.delete_moving(i);
				--i;
				break;
			default:
				break;
		}
	}
}

void Mario::player_dead(Game &game) {
	constexpr int DEATH_DELAY_US = 500000;

	if (has_colors()) {
		wbkgd(stdscr, COLOR_PAIR(COLOR_DEAD));
		clear();
		game.show_map();
		refresh();
	}

	usleep(DEATH_DELAY_US);
	game.create_level(game.get_level());

	if (has_colors()) {
		wbkgd(stdscr, COLOR_PAIR(COLOR_NORMAL));
		clear();
	}
}

} // namespace pav