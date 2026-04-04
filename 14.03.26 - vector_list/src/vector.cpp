#include "vector.hpp"

#include <iostream>

using pav::Vector;

template<typename T>
const std::size_t pav::Vector<T>::START_CAPACITY = 4;

template<typename T>
Vector<T>::Vector() : capacity(START_CAPACITY), size(0) {
    arr = new T[capacity];
}

template<typename T>
Vector<T>::~Vector() {
	delete[] arr;
	size = 0;
	capacity = START_CAPACITY;
}

template<typename T>
std::size_t Vector<T>::get_size() const noexcept {
	return size;
}

template<typename T>
bool Vector<T>::has_item(const T& value) const noexcept {
	for (std::size_t i = 0; i < size; ++i) {
		if (arr[i] == value) return true;
	}
	return false;
}

template<typename T>
bool Vector<T>::insert(const std::size_t position, const T& value) {
	if (position > size) return false;
	if (size == capacity ){
		std::size_t new_capacity = capacity * 2;
		T* new_arr = new T[new_capacity];
		for ( size_t i = 0; i < position - 1; ++i){
			new_arr[i] = arr[i]; 
		}
		T v_prev = value;
		for (std::size_t i = position - 1; i < size - 1; ++i){
			arr[i+1] = v_prev;
			v_prev = arr[i];
		}

		delete[] arr;

		arr = new_arr;
		size++;
		capacity = new_capacity;
		return true;
	}
	else {
		T v_prev = value;
		for (std::size_t i = position - 1; i < size - 1; ++i){
			arr[i+1] = v_prev;
			v_prev = arr[i];
		}
		size ++;
		return true;
	}
}

template<typename T>
void Vector<T>::print() const noexcept {
	for (std::size_t i = 0; i < size; ++i){
		std:: cout << arr[i] << std::endl;
	}
}

template<typename T>
void Vector<T>::push_back(const T& value) {
	Vector<T>::increase_capacity();
	arr[size] = value; 
	size ++;
	for (std::size_t i = 0; i < size; ++i){ 
		std::cout <<  arr[i] << std::endl;
	}
}

template<typename T>
bool Vector<T>::remove_first(const T& value) {
	if (size*4 > capacity){
		for (std::size_t i = 0; i < size; ++i){
			if ( arr[i] == value){
				for (std::size_t i_2 = i ; i_2 < size-1; ++i_2){
					arr[i_2] = arr[i_2 + 1];
				
				}
				size --;
				return true;
			}
		}
		return false;
	}
	
	else{
		bool res = false;

		std::size_t new_capacity = capacity / 2;
		T* new_arr = new T[new_capacity];

		for (std::size_t i = 0; i < size; ++i){
			if ( arr[i] == value){
				bool res = true;
				size --;
				for (std::size_t i_2 = i; i_2 < size - 1; i_2++){
					new_arr[i_2] = arr[i_2 + 1];
				}
				break;
			}
			else
				new_arr[i] = arr[i];
		}
		delete[] arr;
		arr = new_arr;
		capacity = new_capacity;

		return res;
	}
}

template<typename T>
void Vector<T>::increase_capacity(){
	if (size == capacity ){
		std::size_t new_capacity = capacity * 2;
		T* new_arr = new T[new_capacity];
		for ( size_t i = 0; i < size; ++i){
			new_arr[i] = arr[i]; 
		}

		delete[] arr;

		arr = new_arr;
		capacity = new_capacity;
	}
}

