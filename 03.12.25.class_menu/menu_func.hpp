#pragma once

#include "menu.hpp"

namespace pav {
    const MenuItem* show_menu(const MenuItem* current);

    const MenuItem* study(const MenuItem* current);
    const MenuItem* exit(const MenuItem* current);

    const MenuItem* back_to_main_menu(const MenuItem* current);

    const MenuItem* learn_prog_languages(const MenuItem* current);
    const MenuItem* learn_algorithms(const MenuItem* current);
    const MenuItem* learn_oth_technologies(const MenuItem* current);
    
    const MenuItem* learn_DB(const MenuItem* current);
    const MenuItem* learn_multi_threading(const MenuItem* current);
    const MenuItem* learn_net_technologies(const MenuItem* current);
    const MenuItem* back_to_2nd_menu(const MenuItem* current);
}