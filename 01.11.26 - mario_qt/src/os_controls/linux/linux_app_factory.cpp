#include "linux_app_factory.hpp"

#include "linux_control_settings.hpp"
#include "linux_keyboard.hpp"

using biv::LinuxAppFactory;

LinuxAppFactory::LinuxAppFactory(int map_height, int map_width) {
	control_settings_ = new biv::LinuxControlSettings(map_height, map_width);
	keyboard_ = new biv::LinuxKeyboard();
}

LinuxAppFactory::~LinuxAppFactory() {
	delete keyboard_;
	delete control_settings_;
}

biv::OSControlSettings* LinuxAppFactory::get_control_settings() const noexcept {
	return control_settings_;
}

biv::KeyBoard* LinuxAppFactory::get_keyboard() const noexcept {
	return keyboard_;
}
