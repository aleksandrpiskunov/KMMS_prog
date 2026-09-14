#define _XOPEN_SOURCE_EXTENDED 1

#include <algorithm>
#include <locale.h>
#include <ncurses.h>
#include <unistd.h>
#include <wchar.h>
#include <string>
#include <cmath>
#include <sstream>

#include "Game.hpp"
#include "Brick.hpp"
#include "MovingItems.hpp"
#include "Mario.hpp"
#include "Enemy.hpp"
#include "Money.hpp"

namespace pav {

Game::Game(int width, int height)
    : map(height, std::vector<char>(width + 1, ' ')),
      mapWidth(width),
      mapHeight(height),
      level(1),
      score(0),
      maxLvl(0),
      brickLength(0),
      movingLength(0) {
  mario = std::make_unique<Mario>(39, 10, 3, 3, PLAYER);
}

Game::~Game() = default;

void Game::clear_map() {
		for (auto &row : map) {
			std::fill(row.begin(), row.end() - 1, ' ');
			row.back() = '\0';
		}
}

void Game::show_map() const {
		for (int j = 0; j < mapHeight; ++j) {
			mvprintw(j, 0, "%s", map[j].data());
		}
		refresh();
}

void Game::put_score_on_map() {
		std::string s = "Score: " + std::to_string(score);
		for (std::size_t i = 0; i < s.size() && i < static_cast<std::size_t>(mapWidth); ++i) {
			map[1][i + 5] = s[i];
		}
}

void Game::create_level(int lvl) {
		level = lvl;
		score = 0;
		maxLvl = 3;
		brick.clear();
		moving.clear();
		brickLength = 0;
		movingLength = 0;

		if (mario) {
			mario->reset(39, 10, 3, 3, PLAYER);
		} else {
			mario = std::make_unique<Mario>(39, 10, 3, 3, PLAYER);
		}

		clear_map();

		switch (level) {
			case 1:
			create_brick(15, 20, 3, 5, '+');
			create_brick(20, 20, 40, 5, '#');
			create_money(30, 12, 5, 3);
			create_money(50, 12, 5, 3);
			create_brick(60, 15, 40, 10, '#');
			create_brick(60, 5, 10, 3, '-');
			create_money(70, 5, 5, 3);
			create_brick(75, 5, 5, 3, '-');
			create_money(80, 5, 5, 3);
			create_brick(85, 10, 10, 3, '-');
			create_brick(100, 20, 20, 5, '#');
			create_brick(120, 15, 20, 10, '#');
			create_brick(150, 20, 40, 5, '#');
			create_brick(200, 15, 10, 10, '+');

			create_enemy(25, 10, 3, 2);
			create_enemy(80, 10, 3, 2);
			break;
		case 2:
			create_brick(15, 20, 3, 5, '+');
			create_brick(20, 20, 40, 5, '#');
			create_brick(60, 15, 10, 10, '#');
			create_brick(80, 20, 20, 5, '#');
			create_brick(105, 15, 10, 10, '#');
			create_brick(120, 20, 40, 5, '#');
			create_brick(165, 15, 10, 10, '+');

			create_enemy(25, 10, 3, 2);
			create_enemy(80, 10, 3, 2);
			create_enemy(65, 10, 3, 2);
			create_enemy(120, 10, 3, 2);
			create_enemy(175, 10, 3, 2);
			break;
		case 3:
			create_brick(5, 20, 3, 5, '+');
			create_brick(10, 20, 60, 5, '#');
			create_brick(75, 16, 12, 2, '#');
			create_brick(95, 13, 12, 2, '#');
			create_brick(115, 10, 12, 2, '#');
			create_brick(135, 15, 14, 2, '#');
			create_brick(152, 12, 10, 2, '+');

			create_enemy(18, 10, 3, 2);
			create_enemy(72, 10, 3, 2);
			create_enemy(98, 7, 3, 2);
			create_enemy(128, 8, 3, 2);
			create_enemy(156, 10, 3, 2);
			break;
		default:
			break;
		}
}

void Game::horizon_move_map(const float dx) {
	if (!mario) {
		return;
	}

	auto is_collision = [](float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
		return (x1 + w1 > x2) && (x1 < (x2 + w2)) && ((y1 + h1) > y2) && (y1 < (y2 + h2));
	};

	float testX = mario->get_x() - dx;
	for (const auto &block : brick) {
		if (is_collision(testX, mario->get_y(), mario->get_width(), mario->get_height(),
		                 block->get_x(), block->get_y(), block->get_width(), block->get_height())) {
			return;
		}
	}

	for (const auto &block : brick) {
		block->set_pos(block->get_x() + dx, block->get_y());
	}

	for (const auto &item : moving) {
		item->set_pos(item->get_x() + dx, item->get_y());
	}
}

BaseObject* Game::create_brick(const float x, const float y, const float w, const float h, const char type) {
	brick.emplace_back(std::make_unique<pav::Brick>(x, y, w, h, type));
	++brickLength;
	return brick.back().get();
}

BaseObject* Game::create_moving(const float x, const float y, const float w, const float h, const char type) {
	moving.emplace_back(std::make_unique<pav::MovingItem>(x, y, w, h, type));
	moving.back()->set_horiz_speed(0.2f);
	++movingLength;
	return moving.back().get();
}

BaseObject* Game::create_enemy(const float x, const float y, const float w, const float h){
	enemy.emplace_back(std::make_unique<pav::Enemy>(x, y, w, h));
	enemy.back()->set_horiz_speed(0.2f);
	++enemyLength;
	return enemy.back().get();
}

BaseObject* Game::create_money(const float x, const float y, const float w, const float h){
	money.emplace_back(std::make_unique<pav::Money>(x, y, w, h));
	money.back()->set_horiz_speed(0.2f);
	++moneyLength;
	return money.back().get();
}


void Game::delete_moving(std::size_t index) {
	if (index < moving.size()) {
		moving.erase(moving.begin() + index);
		movingLength = static_cast<int>(moving.size());
	}
}

void Game::delete_enemy(std::size_t index) {
	if (index < enemy.size()) {
		enemy.erase(enemy.begin() + index);
		enemyLength = static_cast<int>(enemy.size());
	}
}

void Game::delete_money(std::size_t index) {
	if (index < money.size()) {
		money.erase(enemy.begin() + index);
		moneyLength = static_cast<int>(enemy.size());
	}
}

void Game::put_object_on_map(const BaseObject &obj) {
	int left = static_cast<int>(std::round(obj.get_x()));
	int top = static_cast<int>(std::round(obj.get_y()));
	int right = static_cast<int>(std::round(obj.get_x() + obj.get_width()));
	int bottom = static_cast<int>(std::round(obj.get_y() + obj.get_height()));

	for (int j = top; j < bottom; ++j) {
		if (j < 0 || j >= mapHeight) continue;
		for (int i = left; i < right; ++i) {
			if (i < 0 || i >= mapWidth) continue;
			map[j][i] = obj.get_type();
		}
		map[j][mapWidth] = '\0';
	}
}

void Game::put_object_on_map(const Mario &player) {
	int left = static_cast<int>(std::round(player.get_x()));
	int top = static_cast<int>(std::round(player.get_y()));
	int right = static_cast<int>(std::round(player.get_x() + player.get_width()));
	int bottom = static_cast<int>(std::round(player.get_y() + player.get_height()));

	for (int j = top; j < bottom; ++j) {
		if (j < 0 || j >= mapHeight) continue;
		for (int i = left; i < right; ++i) {
			if (i < 0 || i >= mapWidth) continue;
			map[j][i] = player.get_type();
		}
		map[j][mapWidth] = '\0';
	}
}

void Game::keyboard_detect(int &moveDirection, bool &jumpRequested, bool &shouldExit) {
	wint_t ch = 0;
	jumpRequested = false;
	shouldExit = false;

	while (get_wch(&ch) != ERR) {
		if (ch == 27) {
			shouldExit = true;
			break;
		}

		if (ch == L' ') {
			jumpRequested = true;
		}

		if (ch == L'a' || ch == L'A' || ch == L'ф' || ch == L'Ф' || ch == KEY_LEFT) {
			if (moveDirection == -1)
				moveDirection = 0;
			else if (moveDirection == 0)
				moveDirection = 1;
		}

		if (ch == L'd' || ch == L'D' || ch == L'в' || ch == L'В' || ch == KEY_RIGHT) {
			if (moveDirection == 1)
				moveDirection = 0;
			else if (moveDirection == 0)
				moveDirection = -1;
		}
	}
}

void Game::run() {
	setlocale(LC_ALL, "");

	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);

	if (has_colors()) {
		start_color();
		use_default_colors();
		init_pair(COLOR_NORMAL, COLOR_WHITE, COLOR_BLUE);
		init_pair(COLOR_DEAD, COLOR_WHITE, COLOR_RED);
		init_pair(COLOR_COMPLETE, COLOR_WHITE, COLOR_GREEN);
		wbkgd(stdscr, COLOR_PAIR(COLOR_NORMAL));
		clear();
	}

	create_level(1);

	int moveDirection = 0;
	bool jumpRequested = false;

	do {
		bool shouldExit = false;
		keyboard_detect(moveDirection, jumpRequested, shouldExit);

		if (mario->get_y() > mapHeight) {
			mario->player_dead(*this);
		}

		if (shouldExit) {
			break;
		}

		if (jumpRequested && !mario->is_flying()) {
			mario->jump(JUMP_SPEED);
		}

		jumpRequested = false;

		if (moveDirection != 0) {
			horizon_move_map(static_cast<float>(moveDirection) * HORIZONTAL_SPEED);
		}

		clear();
		clear_map();

		mario->update(*this);
		mario->mario_collision(*this);

		for (int i = 0; i < brickLength; ++i) {
			put_object_on_map(*brick[i]);
		}

		for (int i = 0; i < enemyLength; ++i) {
			enemy[i]->update(*this);
			if (enemy[i]->get_y() > mapHeight) {
				delete_enemy(i);
				--i;
				continue;
			}
			put_object_on_map(*enemy[i]);
		}

		for (int i = 0; i < movingLength; ++i) {
			moving[i]->update(*this);
			if (moving[i]->get_y() > mapHeight) {
				delete_moving(i);
				--i;
				continue;
			}
			put_object_on_map(*moving[i]);
		}

		for (int i = 0; i < moneyLength; ++i) {
			money[i]->update(*this);
			if (money[i]->get_y() > mapHeight) {
				delete_money(i);
				--i;
				continue;
			}
			put_object_on_map(*money[i]);
		}

		put_object_on_map(*mario);
		put_score_on_map();
		show_map();

		usleep(10000);
	} while (true);

	endwin();
}

} // namespace pav

