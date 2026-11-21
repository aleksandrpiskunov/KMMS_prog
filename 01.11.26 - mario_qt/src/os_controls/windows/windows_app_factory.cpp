#include "windows_app_factory.hpp"

#include "windows_control_settings.hpp"
#include "windows_keyboard.hpp"

using biv::WindowsAppFactory;

WindowsAppFactory::WindowsAppFactory() {
	control_settings_ = new biv::WindowsControlSettings();
	keyboard_ = new biv::WindowsKeyBoard();
}

WindowsAppFactory::~WindowsAppFactory() {
	delete keyboard_;
	delete control_settings_;
}

biv::OSControlSettings* WindowsAppFactory::get_control_settings() const noexcept {
	return control_settings_;
}

biv::KeyBoard* WindowsAppFactory::get_keyboard() const noexcept {
	return keyboard_;
}
