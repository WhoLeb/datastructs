#pragma once
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
		int find_first_of(T value);
		size_t size();
		virtual bool empty();

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
		arr = new T[1];
	}

	template<class T> T dynamic_array<T>::get(size_t place)
	{
		if (place == -1) std::cout << "bad input";
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
		for (size_t i = current_count; i > place; i--)
			arr[i] = arr[i - 1];
		arr[place] = value;
		current_count++;
	}

	template<class T> T dynamic_array<T>::remove_element(const size_t place)
	{
		T v = arr[place];
		if (place < 0) return 0;
		for (size_t i = place; i < current_count - 1; i++)
			arr[i] = arr[i + 1];
		current_count--;
		while (current_count < current_size / 2)
			reduce_size();
		return v;
	}

	template<class T> T dynamic_array<T>::operator[](size_t place)
	{
		if (place > current_count)
		{
			std::cout << "Bad input ";
		}
		return arr[place];
	}

	template<class T> size_t dynamic_array<T>::size()
	{
		return current_count;
	}

	template<class T> int dynamic_array<T>::find_first_of(T val)
	{
		for (int i = 0; i < size(); i++)
			if (arr[i] == val) return i;
		return -1;
	}

	template<class T> bool dynamic_array<T>::empty()
	{
		const bool val = static_cast<bool>(size());
		return !val;
	}

	template<class T> void dynamic_array<T>::double_size()
	{
		current_size <<= 1;
		T* tmp = new T[current_size];
		for (int i = 0; i < current_count; i++)
			tmp[i] = arr[i];
		
		delete[] arr;
		arr = tmp;
	}

	template<class T> void dynamic_array<T>::reduce_size()
	{
		T* tmp = new T[current_size];
		if (current_size != 1) current_size >>= 1;
		else return;
		for (int i = 0; i < current_count; i++)
			tmp[i] = arr[i];

		delete[] arr;
		arr = tmp;
	}

	template<class T> size_t dynamic_array<T>::element_size()
	{
		return size_t(sizeof(T));
	}
}

