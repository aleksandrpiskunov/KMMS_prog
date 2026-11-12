#include "second_level.hpp"

#include "third_level.hpp"

using biv::SecondLevel;

SecondLevel::SecondLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool SecondLevel::is_final() const noexcept {
	return false;
}

biv::GameLevel* SecondLevel::get_next() {
	if (!next) {
		clear_data();
		next = new biv::ThirdLevel(ui_factory);
	}
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void SecondLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);
	
	ui_factory->create_ship({20, 25}, 40, 2);
	ui_factory->create_full_box({42, 18}, 6, 3);
	//ui_factory->create_moving_platform({56, 24}, 12, 2, 5);
	ui_factory->create_ship({70, 20}, 12, 7);
	ui_factory->create_enemy({72, 18}, 3, 2);
	ui_factory->create_ship({92, 25}, 18, 2);
	ui_factory->create_jumping_enemy({96, 23}, 3, 2);
	ui_factory->create_moving_platform({114, 23}, 10, 2, 6);
	ui_factory->create_full_box({118, 18}, 5, 3);
	ui_factory->create_ship({142, 25}, 24, 2);
	ui_factory->create_enemy({150, 23}, 3, 2);
	ui_factory->create_full_box({154, 17}, 5, 3);
	ui_factory->create_ship({176, 20}, 12, 7);
	ui_factory->create_final_ship({210, 20}, 10, 7);
}
