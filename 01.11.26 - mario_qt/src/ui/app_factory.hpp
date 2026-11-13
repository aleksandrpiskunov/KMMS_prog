#pragma once

#include "keyboard.hpp"
#include "os_control_settings.hpp"

class QCoreApplication;

namespace biv {
	class AppFactory {
		private:
			OSControlSettings* control_settings_ = nullptr;
			KeyBoard* keyboard_ = nullptr;

		public:
			AppFactory(int map_height, int map_width);
#ifdef QT_UI
			AppFactory(int map_height, int map_width, QCoreApplication* application);
#endif
			~AppFactory();

			OSControlSettings* get_control_settings() const noexcept;
			KeyBoard* get_keyboard() const noexcept;
	};
}
