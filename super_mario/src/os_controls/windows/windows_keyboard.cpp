#include "windows_keyboard.hpp"

#include <windows.h>

using biv::UserInput;
using biv::WindowsKeyBoard;

UserInput WindowsKeyBoard::get_user_input() {
	if (GetKeyState('A') < 0) {
		return UserInput::MAP_RIGHT;
	} else if (GetKeyState('D') < 0) {
		return UserInput::MAP_LEFT;
	} else if (GetKeyState(VK_SPACE) < 0) {
		return UserInput::MARIO_JUMP;
	} else if (GetKeyState('Q') < 0) {
		return UserInput::EXIT;
	} else {
		return UserInput::NO_INPUT;
	}
}

void WindowsKeyBoard::on() {}
void WindowsKeyBoard::off() {}
