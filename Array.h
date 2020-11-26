#pragma once
#include<fstream>

template <typename T>
class Array
{
private:
	unsigned size, 	num; //Size and number of elements
	T* arr;

	void copy(const Array &other);
public:
	

	Array();
	//
	Array& operator=(const Array &other);
	~Array();

	void resize(unsigned toAdd = 0);
	unsigned gSize()const;
	unsigned gNum()const;
	void push(const T&);
	void remove(const unsigned id);

	T& operator[](const unsigned i);
	T& operator[](const unsigned i)const;
	Array& operator+=(const Array &other);
};



template <typename T>
Array<T>::Array() :
	size(0),
	num(0),
	arr(nullptr)
{}

template <typename T>
Array<T>& Array<T>::operator=(const Array &other)
{
	copy(other);
	return *this;
}

template <typename T>
Array<T>::~Array()
{
	delete[] arr;
}



template <typename T>
void Array<T>::resize(unsigned toAdd)
{
	toAdd = toAdd ? toAdd : size / 2;
	T *temp = new T[num];
	for (unsigned i = 0; i < num; ++i)
		temp[i] = arr[i];
	delete[] arr;
	arr = new T[size + toAdd + 1];
	for (unsigned i = 0; i < num; ++i)
		arr[i]=temp[i];
	size += toAdd + 1;
	delete[] temp;
}

template <typename T>
unsigned Array<T>::gSize()const
{
	return size;
}

template <typename T>
unsigned Array<T>::gNum()const
{
	return num;
}

template <typename T>
void Array<T>::copy(const Array &other)
{
	if (size < other.num)
	{
		delete[] arr;
		arr = new T[other.num];
		size = other.num;
	}
	for (unsigned i = 0; i < other.num; ++i)
		arr[i] = other.arr[i];
	num = other.num;
}

template <typename T>
void Array<T>::push(const T& newEl)
{
	if (num >= size)
		resize();
	arr[num] = newEl;
	++num;
}

template <typename T>
void Array<T>::remove(const unsigned id)
{
	--num;
	arr[id] = arr[num];
}



template <typename T>
T& Array<T>::operator[](const unsigned i)
{
	return arr[i];
}

template <typename T>
T& Array<T>::operator[](const unsigned i)const
{
	return arr[i];
}

template <typename T>
Array<T>& Array<T>::operator+=(const Array &other)
{
	if (size < other.num + num)
		resize(other.num);
	unsigned i = 0;
	for (; i < other.num; ++i)
		arr[num + i] = other.arr[i];
	num += i;
	return *this;
}
