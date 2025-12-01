#include "menu_func.hpp"

#include <cstdlib>
#include <iostream>

const pav::MenuItem* pav::show_menu(const MenuItem* current) {
    std::cout << "Обучайка приветствует тебя, мой юный ученик!" << std::endl;
    for (int i = 1; i < current->children_count; i++) {
        std::cout << current->children[i]->title << std::endl;
    }
    std::cout << current->children[0]->title << std::endl;
    std::cout << "Обучайка > ";

    int user_input;
    std::cin >> user_input;
    std::cout << std::endl;

    return current->children[user_input];
}

const pav::MenuItem* pav::exit(const MenuItem* current) {
    std::exit(0);
}

const pav::MenuItem* pav::study_go_back(const MenuItem* current) {
    return current->parent;
}


const pav::MenuItem* pav::study_algebra(const MenuItem* current) {
    for (int i = 1; i < current->children_count; i++) {
        std::cout << current->children[i]->title << std::endl;
    }
    std::cout << current->children[0]->title << std::endl;
    std::cout << "Алгебра > ";

    int user_input;
    std::cin >> user_input;
    std::cout << std::endl;

    return current->children[user_input];
}
const pav::MenuItem* pav::study_summ(const MenuItem* current) {
    std::cout << current->title << std::endl;
    std::cout << "https://onlineschool-1.ru/glossary/matematika/summa/" << std::endl;
    return current->parent;
}

const pav::MenuItem* pav::study_substract(const MenuItem* current) {
    std::cout << current->title << std::endl;
    std::cout << "https://onlineschool-1.ru/glossary/matematika/raznost/" << std::endl;
    return current->parent;
}

const pav::MenuItem* pav::study_multiply(const MenuItem* current) {
    std::cout << current->title << std::endl;
    std::cout << "https://www.banki.ru/wikibank/tablicza_umnozhenij/" << std::endl;
    return current->parent;
}

const pav::MenuItem* pav::study_divide(const MenuItem* current) {
    std::cout << current->title << std::endl;
    std::cout << "https://repetitor.1c.ru/arithmetic/delenie-chisel-primery-i-pravila/" << std::endl;
    return current->parent;
}


const pav::MenuItem* pav::study_math_an(const MenuItem* current) {
    for (int i = 1; i < current->children_count; i++) {
        std::cout << current->children[i]->title << std::endl;
    }
    std::cout << current->children[0]->title << std::endl;
    std::cout << "Математический анализ > ";

    int user_input;
    std::cin >> user_input;
    std::cout << std::endl;

    return current->children[user_input];
}
const pav::MenuItem* pav::study_diff_calc(const MenuItem* current) {
    std::cout << current->title << std::endl;
    std::cout << "https://bigenc.ru/c/differentsial-noe-ischislenie-5ba9f4" << std::endl;
    return current->parent;
}
const pav::MenuItem* pav::integral_calc(const MenuItem* current) {
    std::cout << current->title << std::endl;
    std::cout << "https://kpfu.ru/portal/docs/F1839677910/Integralnoe.ischislenie.funkcii.odnoi_.peremennoi_.pdf" << std::endl;
    return current->parent;
}