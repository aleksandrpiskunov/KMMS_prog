#include "menu_items.hpp"
#include "menu_func.hpp"

#include <iostream>
#include <cstdlib>

namespace {
    const pav::MenuItem* const main_children[] = {
        &pav::EXIT,
        &pav::STUDY
    };

    int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

namespace {
    const pav::MenuItem* const study_children[] = {
        &pav::BACK_TO_MAIN_MENU,
        &pav::LEARN_PROG_LANGUAGES,
        &pav::LEARN_ALGORITHMS, 
        &pav::LEARN_OTH_TECHNOLOGIES
    };
    int study_size = sizeof(study_children) / sizeof(study_children[0]);
}

pav::MenuItem pav::MAIN = {
    nullptr, pav::show_menu, main_children, main_size, nullptr
};
pav::MenuItem pav::STUDY = {
    "1 - Изучать программирование", pav::study, study_children, study_size, nullptr
};
pav::MenuItem pav::EXIT = {
    "0 - Пойти играть в футбол", pav::exit, nullptr, 0, nullptr
};


namespace{
    const pav::MenuItem* const oth_tech_children[] = {
        &pav::BACK_TO_2ND_MENU,
        &pav::LEARN_DB,
        &pav::LEARN_MULTI_THREADING,
        &pav::LEARN_NET_TECHNOLOGIES
    };
    const int oth_tech_size = sizeof(oth_tech_children) / sizeof(oth_tech_children[0]);
    
}


pav::MenuItem pav::LEARN_PROG_LANGUAGES = {
    "1 - Изучать языки программирования", pav::learn_prog_languages, nullptr, 0, &pav::STUDY
};
pav::MenuItem pav::LEARN_ALGORITHMS = {
    "2 - Изучать алгоритмы", pav::learn_algorithms, nullptr, 0, &pav::STUDY
};
pav::MenuItem pav::LEARN_OTH_TECHNOLOGIES = {
    "3 - Изучать другие технологии", pav::learn_oth_technologies, oth_tech_children, oth_tech_size, &pav::STUDY
};
pav::MenuItem pav::BACK_TO_MAIN_MENU = {
    "0 - Войти в главное меню", pav::back_to_main_menu, nullptr, 0, nullptr
};

pav::MenuItem pav::LEARN_DB = {
    "1 - Изучать базы данных", pav::learn_DB, nullptr, 0, &pav::LEARN_OTH_TECHNOLOGIES
};
pav::MenuItem pav::LEARN_MULTI_THREADING = {
    "2 - Изучать многопоточность", pav::learn_multi_threading, nullptr, 0, &pav::LEARN_OTH_TECHNOLOGIES
};
pav::MenuItem pav::LEARN_NET_TECHNOLOGIES = {
    "3 - Изучать сетевые технологии", pav::learn_net_technologies, nullptr, 0, &pav::LEARN_OTH_TECHNOLOGIES
};
pav::MenuItem pav::BACK_TO_2ND_MENU = {
    "0 - Назад ко второму меню", pav::back_to_2nd_menu, nullptr, 0, &pav::LEARN_OTH_TECHNOLOGIES
};

namespace{
    int setup_parents(){
        pav::STUDY.parent = &pav::MAIN;
        pav::EXIT.parent = &pav::MAIN;

        pav::LEARN_ALGORITHMS.parent = &pav::STUDY;
        pav::LEARN_PROG_LANGUAGES.parent = &pav::STUDY;
        pav::LEARN_OTH_TECHNOLOGIES.parent = &pav::STUDY;
        pav::BACK_TO_MAIN_MENU.parent = &pav::STUDY;

        pav::LEARN_DB.parent = &pav::LEARN_OTH_TECHNOLOGIES;
        pav::LEARN_MULTI_THREADING.parent = &pav::LEARN_OTH_TECHNOLOGIES;
        pav::LEARN_NET_TECHNOLOGIES.parent = &pav::LEARN_OTH_TECHNOLOGIES;
        pav::BACK_TO_2ND_MENU.parent = &pav::LEARN_OTH_TECHNOLOGIES;  
        
        return 0;
    }
    bool a = setup_parents();
}