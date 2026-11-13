#include "app_factory.hpp"

#ifdef QT_UI
	#include "qt_keyboard.hpp"
#elif defined(WINDOWS_CONSOLE)
	#include "windows_control_settings.hpp"
	#include "windows_keyboard.hpp"
#elif defined(LINUX_CONSOLE)
	#include "linux_control_settings.hpp"
	#include "linux_keyboard.hpp"
#endif

using biv::AppFactory;

AppFactory::AppFactory(int map_height, int map_width) {
#ifdef WINDOWS_CONSOLE
	control_settings_ = new biv::WindowsControlSettings();
	keyboard_ = new biv::WindowsKeyBoard();
#elif defined(LINUX_CONSOLE)
	control_settings_ = new biv::LinuxControlSettings(map_height, map_width);
	keyboard_ = new biv::LinuxKeyboard();
#endif
}

#ifdef QT_UI
AppFactory::AppFactory(int, int, QCoreApplication* application) {
	keyboard_ = new biv::QtKeyboard(application);
}
#endif

AppFactory::~AppFactory() {
	delete keyboard_;
	delete control_settings_;
}

biv::OSControlSettings* AppFactory::get_control_settings() const noexcept {
	return control_settings_;
}

biv::KeyBoard* AppFactory::get_keyboard() const noexcept {
	return keyboard_;
}
