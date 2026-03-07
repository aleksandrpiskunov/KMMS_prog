#include "menu_items.hpp"

#include <cstddef>

#include "menu_func.hpp"

namespace {
    const pav::MenuItem* const main_children[] = {
        &pav::EXIT,
        &pav::STUDY
    };

    const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

namespace {
    const pav::MenuItem* const study_children[] = {
        &pav::STUDY_GO_BACK,
        &pav::STUDY_ALGEBRA,
        &pav::STUDY_MATH_AN
    };
    const int study_size = sizeof(study_children) / sizeof(study_children[0]);
}

pav::MenuItem pav::MAIN = {
    nullptr, pav::show_menu, main_children, main_size, nullptr
};

pav::MenuItem pav::STUDY = {
    "1 - Хочу учиться математике!", pav::show_menu, study_children, study_size, nullptr
};
pav::MenuItem pav::EXIT = {
    "0 - Я лучше пойду погулять...", pav::exit, nullptr, 0, nullptr
};
pav::MenuItem pav::STUDY_GO_BACK = {
    "0 - Войти в главное меню", pav::study_go_back, nullptr, 0, nullptr
};

namespace {
    const pav::MenuItem* const alg_children[] = {
        &pav::ALGEBRA_go_back,
        &pav::STUDY_SUMM,
        &pav::STUDY_SUBSTRACT,
        &pav::STUDY_MULTIPLY,
        &pav::STUDY_DIVIDE
    };
    const int alg_size = sizeof(alg_children) / sizeof(alg_children[0]);
}
pav::MenuItem pav::STUDY_ALGEBRA = {
    "1 - Хочу учиться алгебре!", pav::study_algebra, alg_children, alg_size, nullptr
};

namespace {
    const pav::MenuItem* const math_an_children[] = {
        &pav::MATH_AN_go_back,
        &pav::STUDY_DIFF_CALC,
        &pav::INTEGRAL_CALC
    };
    const int math_an_size = sizeof(math_an_children) / sizeof(math_an_children[0]);
}
pav::MenuItem pav::STUDY_MATH_AN = {
    "2 - Хочу учиться математическому анализу!", pav::study_math_an, math_an_children, math_an_size, nullptr
};

pav::MenuItem pav::STUDY_SUMM = {
    "1 - Хочу научиться складывать!", pav::study_summ, nullptr, 0, nullptr
};
pav::MenuItem pav::STUDY_SUBSTRACT = {
    "2 - Хочу научиться вычитать!", pav::study_substract, nullptr, 0, nullptr
};
pav::MenuItem pav::STUDY_MULTIPLY = {
    "3 - Хочу научиться умножать!", pav::study_multiply, nullptr, 0, nullptr
};
pav::MenuItem pav::STUDY_DIVIDE = {
    "4 - Хочу научиться делить!", pav::study_divide, nullptr, 0, nullptr
};
pav::MenuItem pav::ALGEBRA_go_back = {
    "5 - Перейти к выбору предмета", pav::study_go_back, nullptr, 0, nullptr
};

pav::MenuItem pav::STUDY_DIFF_CALC = {
    "1 - Хочу научиться вычислять разность!", nullptr, nullptr, 0, nullptr
};
pav::MenuItem pav::INTEGRAL_CALC = {
    "2 - Хочу научиться вычислять интегралы!", nullptr, nullptr, 0, nullptr
};
pav::MenuItem pav::MATH_AN_go_back = {
    "3 - Перейти к выбору предмета", pav::study_go_back, nullptr, 0, nullptr
};

namespace {
    void setup_parents() {
        // MAIN children
        pav::STUDY.parent = &pav::MAIN;
        pav::EXIT.parent = &pav::MAIN;

        pav::STUDY_GO_BACK.parent = &pav::STUDY;
        pav::ALGEBRA_go_back.parent = &pav::STUDY;
        pav::MATH_AN_go_back.parent = &pav::STUDY;
        
        // STUDY children
        pav::STUDY_ALGEBRA.parent = &pav::STUDY;
        pav::STUDY_MATH_AN.parent = &pav::STUDY;
        
        // STUDY_ALGEBRA children
        pav::STUDY_SUMM.parent = &pav::STUDY_ALGEBRA;
        pav::STUDY_SUBSTRACT.parent = &pav::STUDY_ALGEBRA;
        pav::STUDY_MULTIPLY.parent = &pav::STUDY_ALGEBRA;
        pav::STUDY_DIVIDE.parent = &pav::STUDY_ALGEBRA;
        
        // STUDY_MATH_AN children
        pav::STUDY_DIFF_CALC.parent = &pav::STUDY_MATH_AN;
        pav::INTEGRAL_CALC.parent = &pav::STUDY_MATH_AN;
    }
    
    // Call setup on program start
    int dummy = (setup_parents(), 0);
}
