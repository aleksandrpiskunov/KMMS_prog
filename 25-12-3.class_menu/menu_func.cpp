#include "menu_func.hpp"

#include <iostream>
#include <cstdlib>

namespace {
    const pav::MenuItem* print_children(const pav::MenuItem* current){
        for (int i = 1; i < current->children_count; i++) {
            std::cout << current->children[i]->title << std::endl;
        }
        std::cout << current->children[0]->title << std::endl;
        std::cout << "Поле ввода> ";

        int user_input;
        std::cin >> user_input;
        std::cout << std::endl;

        return current->children[user_input];
    }
}

const pav::MenuItem* pav::show_menu(const MenuItem* current){
    std::cout << "Главное меню"<<std::endl;
    return print_children(current);
}

const pav::MenuItem* pav::study(const MenuItem* current){
    std::cout << "второй уровень меню"<<std::endl;
    return print_children(current);
}

const pav::MenuItem* pav::exit(const MenuItem* current){
    std::exit(0);
}
const pav::MenuItem* pav::back_to_main_menu(const MenuItem* current) {
    return current->parent->parent;
}

const pav::MenuItem* pav::learn_algorithms(const MenuItem* current) {
    std::cout << current->title << std::endl;
    std::cout << "ALGHORITMS.com" << std::endl;
    return current->parent;
}
const pav::MenuItem* pav::learn_prog_languages(const MenuItem* current) {
    std::cout << current->title << std::endl;
    std::cout << "programming_languages.com" << std::endl;
    return current->parent;
}


const pav::MenuItem* pav::learn_oth_technologies(const MenuItem* current){
    std::cout << "третий уровень Другие Технологии"<<std::endl;
    return print_children(current);
    
}

const pav::MenuItem* pav::learn_DB(const MenuItem* current) {
    std::cout << current->title << std::endl;
    std::cout << "DATA_BASES.com" << std::endl;
    return current->parent;
}
const pav::MenuItem* pav::learn_multi_threading(const MenuItem* current) {
    std::cout << current->title << std::endl;
    std::cout << "multi_threading.com" << std::endl;
    return current->parent;
}
const pav::MenuItem* pav::learn_net_technologies(const MenuItem* current) {
    std::cout << current->title << std::endl;
    std::cout << "net_technologies.com" << std::endl;
    return current->parent;
}
const pav::MenuItem* pav::back_to_2nd_menu(const MenuItem* current) {
    return current->parent->parent;
}


