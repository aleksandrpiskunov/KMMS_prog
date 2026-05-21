#include <algorithm>
#include <ncurses.h>
#include "Game.hpp"
#include "Brick.hpp"
#include "MovingItems.hpp"
#include "Mario.hpp"
#include <string>
#include <cmath>
#include <sstream>

using pav::Game;

Game::Game(int width, int height)
    : map(height, std::vector<char>(width + 1, ' ')),
      mapWidth(width),
      mapHeight(height),
      level(1),
      score(1),
      maxLvl(0),
      brickLength(0),
      movingLength(0) {
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
  std::string s = "Score:" + std::to_string(score);
  for (std::size_t i = 0; i < s.size() && i < static_cast<std::size_t>(mapWidth); ++i) {
    map[0][i] = s[i];
  }
}

void Game::create_level(int lvl) {
  level = lvl;
  maxLvl = std::max(maxLvl, lvl);
  clear_map();
  int groundY = mapHeight - 2; 
  for (int x = 0; x < mapWidth; ++x) {
    map[groundY][x] = '#';
  }
}

void Game::horizon_move_map(const float dx) {
  int shift = static_cast<int>(dx);
  if (shift == 0) return;
  for (auto &row : map) {
    if (shift > 0) {
      for (int k = 0; k < shift; ++k) {
        for (int i = mapWidth - 1; i > 0; --i) row[i] = row[i - 1];
        row[0] = ' ';
      }
    } else {
      for (int k = 0; k < -shift; ++k) {
        for (int i = 0; i < mapWidth - 1; ++i) row[i] = row[i + 1];
        row[mapWidth - 1] = ' ';
      }
    }
    row[mapWidth] = '\0';
  }
}

pav::TObject* Game::create_brick(const float x, const float y, const float w, const float h, const char type) {
  brick.emplace_back(std::make_unique<pav::Brick>(x, y, w, h, type));
  ++brickLength;
  return brick.back().get();
}

pav::TObject* Game::create_moving(const float x, const float y, const float w, const float h, const char type) {
  moving.emplace_back(std::make_unique<pav::MovingItem>(x, y, w, h, type));
  ++movingLength;
  return moving.back().get();
}

void Game::delete_moving(std::size_t index) {
  if (index < moving.size()) {
    moving.erase(moving.begin() + index);
    movingLength = static_cast<int>(moving.size());
  }
}

void Game::put_object_on_map(const TObject &obj) {
  int left = static_cast<int>(std::floor(obj.get_x()));
  int top = static_cast<int>(std::floor(obj.get_y()));
  int right = static_cast<int>(std::floor(obj.get_x() + obj.get_width()));
  int bottom = static_cast<int>(std::floor(obj.get_y() + obj.get_height()));

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
  int left = static_cast<int>(std::floor(player.get_x()));
  int top = static_cast<int>(std::floor(player.get_y()));
  int right = static_cast<int>(std::floor(player.get_x() + player.get_width()));
  int bottom = static_cast<int>(std::floor(player.get_y() + player.get_height()));

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
  int ch = getch();
  moveDirection = 0;
  jumpRequested = false;
  shouldExit = false;

  if (ch == ERR) return; 
  switch (ch) {
    case KEY_LEFT: moveDirection = -1; break;
    case KEY_RIGHT: moveDirection = 1; break;
    case 'q': shouldExit = true; break;
    case ' ': jumpRequested = true; break;
    default: break;
  }
}

