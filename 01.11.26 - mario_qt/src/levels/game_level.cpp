#include "game_level.hpp"

using biv::GameLevel;

GameLevel::GameLevel(UIFactory* ui_factory) : ui_factory(ui_factory) {}

void GameLevel::restart() {
	clear_data();
	init_data();
}

bool GameLevel::is_final() const noexcept {
	return false;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void GameLevel::clear_data() {
	ui_factory->clear_data();
}
