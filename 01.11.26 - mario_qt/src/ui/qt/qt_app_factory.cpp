#include "qt_app_factory.hpp"

#include "qt_keyboard.hpp"

using biv::QtAppFactory;

QtAppFactory::QtAppFactory(QCoreApplication* application) {
	keyboard_ = new biv::QtKeyboard(application);
}

QtAppFactory::~QtAppFactory() {
	delete keyboard_;
	delete control_settings_;
}

biv::OSControlSettings* QtAppFactory::get_control_settings() const noexcept {
	return control_settings_;
}

biv::KeyBoard* QtAppFactory::get_keyboard() const noexcept {
	return keyboard_;
}
