#pragma once

#include "keyboard.hpp"

namespace biv {
	class LinuxKeyboard : public KeyBoard {
		private:
			UserInput prev_input;

		public:
			UserInput get_user_input() override;
			void on() override;
			void off() override;
	};
}
