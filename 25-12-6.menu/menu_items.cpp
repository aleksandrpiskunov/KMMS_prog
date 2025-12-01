#include "menu_items.hpp"

#include <cstddef>

#include "menu_func.hpp"

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
pav::MenuItem pav::STUDY_GO_BACK = {
    "0 - Войти в главное меню", pav::study_go_back, nullptr, 0, nullptr
};

namespace {
    const pav::MenuItem* const study_children[] = {
        &pav::STUDY_GO_BACK,
        &pav::STUDY_SUMM,
        &pav::STUDY_SUBSTRACT,
        &pav::STUDY_MULTIPLY,
        &pav::STUDY_DIVIDE
    };
    const int study_size = sizeof(study_children) / sizeof(study_children[0]);
}

pav::MenuItem pav::STUDY = {
    "1 - Хочу учиться математике!", pav::show_menu, study_children, study_size, nullptr
};
pav::MenuItem pav::EXIT = {
    "0 - Я лучше пойду погулять...", pav::exit, nullptr, 0, nullptr
};

namespace {
    const pav::MenuItem* const main_children[] = {
        &pav::EXIT,
        &pav::STUDY
    };

    const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

pav::MenuItem pav::MAIN = {
    nullptr, pav::show_menu, main_children, main_size, nullptr
};

// Setup parent pointers
namespace {
    void setup_parents() {
        // STUDY children
        pav::STUDY_SUMM.parent = &pav::STUDY;
        pav::STUDY_SUBSTRACT.parent = &pav::STUDY;
        pav::STUDY_MULTIPLY.parent = &pav::STUDY;
        pav::STUDY_DIVIDE.parent = &pav::STUDY;
        pav::STUDY_GO_BACK.parent = &pav::STUDY;
        
        // MAIN children
        pav::STUDY.parent = &pav::MAIN;
        pav::EXIT.parent = &pav::MAIN;
    }
    
    // Call setup on program start
    int dummy = (setup_parents(), 0);
}
