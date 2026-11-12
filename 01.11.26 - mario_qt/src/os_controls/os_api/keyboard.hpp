#pragma once

namespace biv {
	enum class UserInput {
		EXIT,
		MAP_LEFT,
		MAP_RIGHT,
		MARIO_JUMP,
		NO_INPUT
	};

	class KeyBoard {
		public:
			virtual UserInput get_user_input() = 0;
			virtual void off() = 0;
			virtual void on() = 0;
	};
}
