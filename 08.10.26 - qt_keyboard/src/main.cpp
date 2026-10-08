#include <QApplication>

#include "keyboard_window.hpp"
#include "welcome_window.hpp"

int main(int argc, char* argv[]) {
    // QApplication обслуживает очередь событий и жизненный цикл Qt-приложения.
    QApplication app(argc, argv);

    // Оба окна создаются заранее, чтобы переход между ними выполнялся без пересоздания.
    biv::WelcomeWindow welcome_window;
    biv::KeyBoardWindow keyboard_window;

    // Сигнал приветственного окна скрывает его и показывает окно клавиатуры.
    QObject::connect(
        &welcome_window,
        &biv::WelcomeWindow::keyboard_requested,
        &welcome_window,
        &QWidget::hide
    );
    QObject::connect(
        &welcome_window,
        &biv::WelcomeWindow::keyboard_requested,
        &keyboard_window,
        &QWidget::show
    );

    // При запуске пользователь видит только приветственное окно.
    welcome_window.show();

    return app.exec();
}
