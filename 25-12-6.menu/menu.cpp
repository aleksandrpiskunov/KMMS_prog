#include <clocale>
#include <iostream>

#include "menu.hpp"
#include "menu_func.hpp"
#include "menu_items.hpp"

int main() {
    std::setlocale(LC_ALL, "");

    const pav::MenuItem* current = &pav::MAIN;
    do {
        current = current->func(current);
    } while (true);

    return 0;
}
