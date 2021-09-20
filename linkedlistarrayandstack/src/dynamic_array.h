#pragma once
#include <stdlib.h>
#include <iostream>
#include <cstdarg>

namespace WhoLeb
{
	template<class T>
	class dynamic_array
	{
	public:
		dynamic_array(const size_t size, ...);
		dynamic_array();
		
		inline T get(size_t place);
		void add_element(const size_t, T value);
		T remove_element(const size_t place);
		T operator[](size_t place);
		size_t size();

	protected:
		void double_size();
		void reduce_size();
		size_t element_size();

		size_t current_count;
		size_t current_size;
		T* arr;
	};

	template<class T> dynamic_array<T>::dynamic_array()
	{
		current_size = 1;
		current_count = 0;
		arr = new T[0];
	}
	
	template<class T> T dynamic_array<T>::get(size_t place)
	{
		return arr[place];
	}

	template<class T> dynamic_array<T>::dynamic_array(const size_t size, ...)
	{
		int k = 0;
		unsigned int csize = size;
		while (csize)
		{
			csize /= 2;
			k++;
		}
		current_size = 1 << k;

		arr = new T[current_size];
		std::va_list args;
		va_start(args, size);

		for (size_t i = 0; i < size; i++)
			arr[i] = va_arg(args, T);
		
		va_end(args);
		
		current_count = size;
	}

	template<class T> void dynamic_array<T>::add_element(const size_t place, T value)
	{
		if (current_count + 1 > current_size) double_size();
		for (int i = current_count; i > place; i--)
			arr[i] = arr[i - 1];
		arr[place] = value;
		current_count++;
	}

	template<class T> T dynamic_array<T>::remove_element(const size_t place)
	{
		T v = arr[place];
		for (int i = place; i < current_count - 1; i++)
			arr[i] == arr[i + 1];
		current_count--;
		while (current_count < current_size / 2)
			reduce_size();
	}

	template<class T> T dynamic_array<T>::operator[](size_t place)
	{
		if (place > current_count)
		{
			std::cout << "Bad input ";
			return -1;
		}
		return arr[place];
	}

	template<class T> size_t dynamic_array<T>::size()
	{
		return current_count;
	}

	template<class T> void dynamic_array<T>::double_size()
	{
		current_size <<= 1;
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

