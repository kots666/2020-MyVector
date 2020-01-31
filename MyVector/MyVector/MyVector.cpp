#include "MyVector.h"

template<typename T>
void MyVector<T>::CheckCapacity() {
	if (size >= capacity) {
		if (capacity < 2) ++capacity;
		else capacity += (capacity / 2);
		IncreaseCapacity();
	}
}

template<typename T>
void MyVector<T>::IncreaseCapacity() {
	T* newData = new T[capacity];
	//T* newData = static_cast<T*>(malloc(sizeof(T)*capacity));

	for (size_t i = 0; i < size; ++i) {
		newData[i] = std::move(data[i]);
	}

	if (data != nullptr) delete[] data;

	data = newData;
}

template<typename T>
MyVector<T>::MyVector(size_t s) : size(s), capacity(s)
{
	if (s < 1) data = nullptr;
	else data = new T[s];
}

template<typename T>
MyVector<T>::~MyVector()
{
	Clear();
}

template<typename T>
MyVector<T>::Iterator::Iterator(T* p) : pointer(p) {}

template<typename T>
MyVector<T>::Iterator::Iterator(const Iterator & iter) : pointer(iter.pointer) {}

template<typename T>
T& MyVector<T>::Iterator::operator*() {
	return *pointer;
}

template<typename T>
MyVector<T>::template Iterator& MyVector<T>::Iterator::operator++() {
	++pointer;
	return *this;
}

template<typename T>
const MyVector<T>::template Iterator MyVector<T>::Iterator::operator++(int) {
	const Iterator temp(*this);
	++pointer;
	return temp;
}

template<typename T>
MyVector<T>::template Iterator & MyVector<T>::Iterator::operator--() {
	--pointer;
	return *this;
}

template<typename T>
const MyVector<T>::template Iterator MyVector<T>::Iterator::operator--(int)
{
	const Iterator temp(*this);
	--pointer;
	return temp;
}

template<typename T>
bool MyVector<T>::Iterator::operator!=(const Iterator & iter)
{
	return pointer != iter.pointer;
}

template<typename T>
bool MyVector<T>::Iterator::operator==(const Iterator & iter)
{
	return pointer == iter.pointer;
}

template<typename T>
MyVector<T>::ReverseIterator::ReverseIterator(T * p) : pointer(p) {}

template<typename T>
MyVector<T>::ReverseIterator::ReverseIterator(const ReverseIterator & iter) : pointer(iter.pointer) {}

template<typename T>
T& MyVector<T>::ReverseIterator::operator *() { return *pointer; };

template<typename T>
MyVector<T>::template ReverseIterator& MyVector<T>::ReverseIterator::operator++()
{
	--pointer;
	return *this;
}

template<typename T>
const MyVector<T>::template ReverseIterator MyVector<T>::ReverseIterator::operator++(int)
{
	const ReverseIterator temp(*this);
	--pointer;
	return temp;
}

template<typename T>
MyVector<T>::template ReverseIterator & MyVector<T>::ReverseIterator::operator--() {
	++pointer;
	return *this;
}

template<typename T>
const MyVector<T>::template ReverseIterator MyVector<T>::ReverseIterator::operator--(int)
{
	const ReverseIterator temp(*this);
	++pointer;
	return temp;
}

template<typename T>
bool MyVector<T>::ReverseIterator::operator!=(const ReverseIterator & iter)
{
	return pointer != iter.pointer;
}

template<typename T>
bool MyVector<T>::ReverseIterator::operator==(const ReverseIterator & iter)
{
	return pointer == iter.pointer;
}

template<typename T>
MyVector<T>::template Iterator MyVector<T>::Begin()
{
	return Iterator(data);
}

template<typename T>
MyVector<T>::template Iterator MyVector<T>::End()
{
	return Iterator(data + size);
}

template<typename T>
MyVector<T>::template ReverseIterator MyVector<T>::RBegin()
{
	return ReverseIterator(data + size - 1);
}

template<typename T>
MyVector<T>::template ReverseIterator MyVector<T>::REnd()
{
	return ReverseIterator(data - 1);
}

template<typename T>
void MyVector<T>::Clear()
{
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
}

template<typename T>
void MyVector<T>::Push_Back(const T & other)
{
	CheckCapacity();
	data[size++] = other;
}

template<typename T>
void MyVector<T>::Push_Back(T && other)
{
	CheckCapacity();
	data[size++] = std::move(other);
}

template<typename T>
void MyVector<T>::Reserve(size_t n)
{
	if (n > capacity) {
		capacity = n;
		IncreaseCapacity();
	}
}

template<typename T>
size_t MyVector<T>::Capacity() const
{
	return capacity;
}

template<typename T>
size_t MyVector<T>::Size() const
{
	return size;
}

template<typename T>
T & MyVector<T>::operator[](const size_t n) const
{
	if (n < 0) std::abort();
	if (n >= size) std::abort();
	/*try {
		if (n >= size) throw std::out_of_range("Out of Range");
	}
	catch (typename std::out_of_range e) {
		std::cerr << e.what() << std::endl;
	}*/
	return data[n];
}