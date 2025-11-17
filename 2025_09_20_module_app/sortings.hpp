#ifndef SORTINGS_HPP
#define SORTINGS_HPP

namespace pav {
	namespace sortings {
		void bubble_sort(int* const arr, const int size);
		void shaker_sort(int* const arr, const int size);
		void odd_even_sort(int* const arr, const int size);
		void comb_sort(int* const arr, const int size);
		void quick_sort(int* const arr, const int left, const int right);
		void merge(int* const arr, int* const buf, const int beg, const int mid, const int end);
		void merge_reqursive(int* const arr, int* const buf,  const  int beg, const int end);
		void selection_sort(int* const arr, const int size);
		void insertion_sort(int* const arr, const int size);
		void shell_sort(int* const arr, const int size);
		void heapify(int* const arr, const int size, int root);
		void heap_sort(int* const arr, const int size);
	}

#endif