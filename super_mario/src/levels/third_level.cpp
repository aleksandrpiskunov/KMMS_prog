#include "third_level.hpp"

using biv::ThirdLevel;

ThirdLevel::ThirdLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool ThirdLevel::is_final() const noexcept {
	return true;
}

biv::GameLevel* ThirdLevel::get_next() { 
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void ThirdLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);

	ui_factory->create_ship({18, 25}, 34, 2);
	ui_factory->create_full_box({30, 18}, 6, 3); // first
	ui_factory->create_moving_platform({58, 24}, 10, 2, 5);
	//ui_factory->create_enemy({60, 22}, 3, 2);
	ui_factory->create_ship({72, 20}, 8, 7);
	ui_factory->create_jumping_enemy({78, 18}, 3, 2);
    ui_factory->create_jumping_enemy({44, 18}, 3, 2); // first
	ui_factory->create_full_box({58, 15}, 6, 3);  

	ui_factory->create_moving_platform({96, 22}, 12, 2, 8);
	ui_factory->create_ship({112, 25}, 10, 2);
	ui_factory->create_enemy({116, 23}, 3, 2);
	ui_factory->create_ship({126, 20}, 12, 7); 
	ui_factory->create_flyable_enemy({134, 17}, 3, 2, 3, 7);
	ui_factory->create_full_box({130, 12}, 5, 3);

	ui_factory->create_ship({154, 25}, 10, 2);
	ui_factory->create_moving_platform({166, 24}, 14, 2, 7);
	ui_factory->create_enemy({172, 22}, 3, 2);
	ui_factory->create_ship({184, 20}, 10, 7);
	ui_factory->create_full_box({188, 12}, 5, 3);

	ui_factory->create_moving_platform({198, 23}, 12, 2, 5);
	ui_factory->create_enemy({202, 21}, 3, 2);
	ui_factory->create_ship({214, 25}, 10, 2);
	ui_factory->create_jumping_enemy({218, 23}, 3, 2);
	ui_factory->create_final_ship({234, 20}, 12, 7);

	ui_factory->create_enemy({28, 23}, 3, 2);
	ui_factory->create_enemy({44, 23}, 3, 2);
	
	ui_factory->create_flyable_enemy({92, 19}, 3, 2, 2, 6);
	ui_factory->create_enemy({150, 23}, 3, 2);
	ui_factory->create_flyable_enemy({190, 18}, 3, 2, 2, 6);
	ui_factory->create_enemy({206, 19}, 3, 2);
}