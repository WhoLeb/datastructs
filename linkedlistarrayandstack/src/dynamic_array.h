#pragma once
#include <stdlib.h>
#include <iostream>

namespace WhoLeb
{
	template<class T>
	class dynamic_array
	{
	public:
		dynamic_array(unsigned const int size);
		dynamic_array();

		void push_back(T element);
		void pop_back();
		void add_elements(unsigned const int place, unsigned const int count);
		void remove_elements(unsigned const int place, unsigned const int count);
		void print_array();
		T operator[](size_t place);

	private:
		void double_size();
		void reduce_size();
		size_t element_size();

		size_t current_count;
		size_t current_size;
		T* arr;
	};

	template<class T> dynamic_array<T>::dynamic_array(unsigned const int size)
	{
		arr = (T*)malloc(size * element_size());
		for (unsigned int i = 0; i < size; i++)
		{
			std::cout << "Enter the value: ";
			std::cin >> arr[i];
		}
		current_count = size;
		int k = 0;
		unsigned int csize = size;
		while (csize)
		{
			csize /= 2;
			k++;
		}
		current_size = 1 << k;
	}

	template<class T> dynamic_array<T>::dynamic_array()
	{
		arr = (T*)malloc(element_size());
		std::cout << "Enter the value: ";
		std::cin >> arr[0];
		current_size = current_count = 1;
	}

	template<class T> void dynamic_array<T>::push_back(T element)
	{
		if (current_count == current_size)
			double_size();
		arr[current_count] = element;
		current_count++;
	}

	template<class T> void dynamic_array<T>::pop_back()
	{
		arr[current_count] = 0;
		current_count--;
		if (current_count < current_size / 2)
			reduce_size();
	}

	template<class T> void dynamic_array<T>::add_elements(unsigned const int place, unsigned const int count)
	{
		T* tmp = new T[current_count - place + 1];
		for (int i = 0, j = place; j < current_count; i++, j++)
			tmp[i] = arr[j];
		if (current_count + count > current_size) double_size();
		for (int i = place; i < place + count; i++) 
		{
			std::cout << "Enter the value: ";
			std::cin >> arr[i];
		}
		for (int i = place + count, j = 0; i < current_count + count; i++, j++)
			arr[i] = tmp[j];
		delete[] tmp;
		current_count = current_count + count;
	}

	template<class T> void dynamic_array<T>::remove_elements(unsigned const int place, unsigned const int count)
	{
		T* tmp = new T[current_count - place - count + 1];
		for (int i = 0, j = place + count; j < current_count; i++, j++)
			tmp[i] = arr[j];
		for (int i = place, j = 0; i < current_count; i++, j++)
			arr[i] = tmp[j];
		for (int i = current_count - count; i < current_count; i++)
			arr[i] = 0;
		delete[] tmp;
		current_count -= count;
		while (current_count < current_size / 2)
			reduce_size();
	}

	template<class T> void dynamic_array<T>::print_array()
	{
		std::cout << std::endl;
		for (int i = 0; i < current_count; i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}

	template<class T> T dynamic_array<T>::operator[](size_t place)
	{
		return arr[place];
	}

	template<class T> void dynamic_array<T>::double_size()
	{
		current_size <<= 1;
		/*T* tmp = (T*)malloc(current_size * element_size());
		memcpy(tmp, arr, current_count * element_size());
		free(arr);
		arr = tmp;*/
		T* tmp = new T[current_size];
		for (int i = 0; i < current_size; i++)
			tmp[i] = arr[i];
		std::swap(arr, tmp);
		delete[] tmp;
	}

	template<class T> void dynamic_array<T>::reduce_size()
	{
		current_size >>= 1;
		T* tmp = new T[current_size];
		for (int i = 0; i < current_size; i++)
			tmp[i] = arr[i];
		std::swap(arr, tmp);
		delete[] tmp;
	}

	template<class T> size_t dynamic_array<T>::element_size()
	{
		return size_t(sizeof(T));
	}
}