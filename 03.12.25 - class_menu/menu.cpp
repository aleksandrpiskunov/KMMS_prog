#include <iostream>

#include "menu.hpp"
#include "menu_func.hpp"
#include "menu_items.hpp"

int main() {
    const pav::MenuItem* current = &pav::MAIN;
    do {
        current = current->func(current);
    } while (true);

    return 0;
}
