#include "doubly_linked_list.hpp"

#include <iostream>

using pav::DoublyLinkedList;


template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node* current = begin;
	while (current != nullptr){
		Node* next = current -> next;
		delete current;
		current = next;
	}
	begin = nullptr;
	end = nullptr;
}

template<typename T>
std::size_t DoublyLinkedList<T>::get_size() const noexcept {
	Node* current = begin;
	int counter = 0;
	while (current != nullptr){
		counter++;
		current = current -> next;
	}
	return counter;
}

template<typename T>
bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
	Node* current = begin;
	while ( current != nullptr){
		if (current -> value == value){
			return 1;
		}
		current = current -> next;
	}
	return 0;
}

template<typename T>
void DoublyLinkedList<T>::print() const noexcept {
	Node* current = begin;
	while ( current != nullptr){
		 std::cout << current->value<< std::endl;
		 current = current ->next;
	}
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
	Node* new_node = new Node(value);

	if (begin == nullptr){
		begin = end = new_node;
		return;
	}
	new_node->prev = end;
	end->next = new_node;
	end = new_node;
}

template<typename T>
bool DoublyLinkedList<T>::remove_first(const T& value) noexcept {
    Node* current = begin;
    while (current != nullptr) {
        if (current->value == value) {
            if (current->prev != nullptr)
                current->prev->next = current->next;
            else
                begin = current->next;
                
            if (current->next != nullptr)
                current->next->prev = current->prev;
            else
                end = current->prev;
            
            Node* nextNode = current->next;
            
            current->prev = current->next = nullptr;
            delete current;
            
            return true; 
        }
        current = current->next;
    }
    return false;  
}