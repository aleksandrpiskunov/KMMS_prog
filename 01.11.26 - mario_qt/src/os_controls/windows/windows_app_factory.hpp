#pragma once

#include "keyboard.hpp"
#include "os_control_settings.hpp"

namespace biv {
	class WindowsAppFactory {
		private:
			OSControlSettings* control_settings_ = nullptr;
			KeyBoard* keyboard_ = nullptr;

		public:
			WindowsAppFactory();
			~WindowsAppFactory();

			OSControlSettings* get_control_settings() const noexcept;
			KeyBoard* get_keyboard() const noexcept;
	};
}
