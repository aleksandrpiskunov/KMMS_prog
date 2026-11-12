#pragma once

#include <QObject>

#include "keyboard.hpp"

class QCoreApplication;

namespace biv {
	class QtKeyboard final : public QObject, public KeyBoard {
		private:
			QCoreApplication* application;
			bool left = false;
			bool right = false;
			bool jump = false;
			bool exit = false;

		public:
			explicit QtKeyboard(QCoreApplication* application);
			UserInput get_user_input() override;
			void on() override;
			void off() override;

		protected:
			bool eventFilter(QObject*, QEvent*) override;
	};
}
