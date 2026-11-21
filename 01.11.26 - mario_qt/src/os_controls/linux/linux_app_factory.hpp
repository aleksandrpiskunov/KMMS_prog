#pragma once

#include "keyboard.hpp"
#include "os_control_settings.hpp"

namespace biv {
	class LinuxAppFactory {
		private:
			OSControlSettings* control_settings_ = nullptr;
			KeyBoard* keyboard_ = nullptr;

		public:
			LinuxAppFactory(int map_height, int map_width);
			~LinuxAppFactory();

			OSControlSettings* get_control_settings() const noexcept;
			KeyBoard* get_keyboard() const noexcept;
	};
}
