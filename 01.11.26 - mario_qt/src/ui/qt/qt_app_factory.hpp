#pragma once

#include "keyboard.hpp"
#include "os_control_settings.hpp"

class QCoreApplication;

namespace biv {
	class QtAppFactory {
		private:
			OSControlSettings* control_settings_ = nullptr;
			KeyBoard* keyboard_ = nullptr;

		public:
			explicit QtAppFactory(QCoreApplication* application);
			~QtAppFactory();

			OSControlSettings* get_control_settings() const noexcept;
			KeyBoard* get_keyboard() const noexcept;
	};
}
