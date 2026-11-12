#include "linux_keyboard.hpp"

#include <ncurses.h>

using biv::LinuxKeyboard;
	
biv::UserInput LinuxKeyboard::get_user_input() {
	int c = getch();
	
	switch (c) {
		case 'd':
			prev_input = UserInput::MAP_LEFT;
			return UserInput::MAP_LEFT;
		case 'a':
			prev_input = UserInput::MAP_RIGHT;
			return UserInput::MAP_RIGHT;
		case 's':
			prev_input = UserInput::NO_INPUT;
			return UserInput::NO_INPUT;
		case ' ':
			return UserInput::MARIO_JUMP;
		case 'q':
			return UserInput::EXIT;
	}
    
	switch (prev_input) {
		case UserInput::MAP_LEFT:
			return UserInput::MAP_LEFT;
		case UserInput::MAP_RIGHT:
			return UserInput::MAP_RIGHT;
		default:
			return UserInput::NO_INPUT;
	}
}

void LinuxKeyboard::on() {}

void LinuxKeyboard::off() {
	prev_input = UserInput::NO_INPUT;
}
