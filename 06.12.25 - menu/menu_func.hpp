#pragma once

#include "menu.hpp"

namespace pav {
    const MenuItem* show_menu(const MenuItem* current);

    const MenuItem* study(const MenuItem* current);

    const MenuItem* exit(const MenuItem* current);

    const MenuItem* study_algebra(const MenuItem* current);
    const MenuItem* study_math_an(const MenuItem* current);
    
    const MenuItem* study_go_back(const MenuItem* current);

    const MenuItem* study_summ(const MenuItem* current);
    const MenuItem* study_substract(const MenuItem* current);
    const MenuItem* study_multiply(const MenuItem* current);
    const MenuItem* study_divide(const MenuItem* current);

    const MenuItem* study_diff_calc(const MenuItem* current);
    const MenuItem* integral_calc(const MenuItem* current);
}