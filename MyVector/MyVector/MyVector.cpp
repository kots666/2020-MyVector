#include <cassert>
#include "MyVector.h"

template<typename T>
void MyVector<T>::CheckCapacity() {
	if (vecSize >= vecCapacity) {
		if (vecCapacity < 2) ++vecCapacity;
		else vecCapacity += (vecCapacity / 2);
		IncreaseCapacity();
	}
}

template<typename T>
void MyVector<T>::IncreaseCapacity() {
	T* newData = static_cast<T*>(operator new(sizeof(T) * vecCapacity));

	for (size_t i = 0; i < vecSize; ++i) {
		T* moveData = &newData[i];
		new(moveData) T(std::forward<T>(vecData[i]));
	}

	clear();

	vecData = newData;
}

template<typename T>
MyVector<T>::MyVector(size_t newSize) : vecSize(newSize), vecCapacity(newSize) {
	if (newSize < 1) vecData = nullptr;
	else vecData = static_cast<T*>(operator new(sizeof(T) * newSize));
}

template<typename T>
MyVector<T>::~MyVector() {
	clear();
}

template<typename T>
MyVector<T>::Iterator::Iterator(T* p) : pointer(p) {}

template<typename T>
MyVector<T>::Iterator::Iterator(const Iterator& iter) : pointer(iter.pointer) {}

template<typename T>
T& MyVector<T>::Iterator::operator*() const {
	return *pointer;
}

template<typename T>
int MyVector<T>::Iterator::operator-(const Iterator& iter) {
	return pointer - iter.pointer;
}

template<typename T>
MyVector<T>::template Iterator& MyVector<T>::Iterator::operator++() {
	++pointer;
	return *this;
}

template<typename T>
MyVector<T>::template Iterator MyVector<T>::Iterator::operator++(int) {
	const Iterator temp(*this);
	++pointer;
	return temp;
}

template<typename T>
MyVector<T>::template Iterator& MyVector<T>::Iterator::operator--() {
	--pointer;
	return *this;
}

template<typename T>
MyVector<T>::template Iterator MyVector<T>::Iterator::operator--(int) {
	const Iterator temp(*this);
	--pointer;
	return temp;
}

template<typename T>
bool MyVector<T>::Iterator::operator!=(const Iterator& iter) const {
	return pointer != iter.pointer;
}

template<typename T>
bool MyVector<T>::Iterator::operator==(const Iterator& iter) const {
	return pointer == iter.pointer;
}

template<typename T>
MyVector<T>::ReverseIterator::ReverseIterator(T * p) : pointer(p) {}

template<typename T>
MyVector<T>::ReverseIterator::ReverseIterator(const ReverseIterator& iter) : pointer(iter.pointer) {}

template<typename T>
T& MyVector<T>::ReverseIterator::operator *() const {
	return *pointer;
}

template<typename T>
int MyVector<T>::ReverseIterator::operator-(const ReverseIterator& iter) {
	return pointer - iter.pointer;
}
;

template<typename T>
MyVector<T>::template ReverseIterator& MyVector<T>::ReverseIterator::operator++() {
	--pointer;
	return *this;
}

template<typename T>
MyVector<T>::template ReverseIterator MyVector<T>::ReverseIterator::operator++(int) {
	const ReverseIterator temp(*this);
	--pointer;
	return temp;
}

template<typename T>
MyVector<T>::template ReverseIterator& MyVector<T>::ReverseIterator::operator--() {
	++pointer;
	return *this;
}

template<typename T>
MyVector<T>::template ReverseIterator MyVector<T>::ReverseIterator::operator--(int) {
	const ReverseIterator temp(*this);
	++pointer;
	return temp;
}

template<typename T>
bool MyVector<T>::ReverseIterator::operator!=(const ReverseIterator& iter) const {
	return pointer != iter.pointer;
}

template<typename T>
bool MyVector<T>::ReverseIterator::operator==(const ReverseIterator& iter) const {
	return pointer == iter.pointer;
}

template<typename T>
MyVector<T>::template Iterator MyVector<T>::begin() noexcept {
	return Iterator(vecData);
}

template<typename T>
MyVector<T>::template Iterator MyVector<T>::end() noexcept {
	return Iterator(vecData + vecSize);
}

template<typename T>
MyVector<T>::template ReverseIterator MyVector<T>::rbegin() noexcept {
	return ReverseIterator(vecData + vecSize - 1);
}

template<typename T>
MyVector<T>::template ReverseIterator MyVector<T>::rend() noexcept {
	return ReverseIterator(vecData - 1);
}

template<typename T>
void MyVector<T>::clear() {
	if (vecData != nullptr) {
		for (size_t i = 0; i < vecSize; ++i) {
			vecData[i].~T();
		}
		operator delete (vecData);
		vecData = nullptr;
	}
}

template<typename T>
template<typename ...Args>
void MyVector<T>::emplace_back(Args && ...args)
{
	CheckCapacity();
	T* p = &vecData[vecSize];
	new(p) T(std::forward<Args>(args)...);
	++vecSize;
}

template<typename T>
MyVector<T>::template Iterator MyVector<T>::erase(Iterator at) {
	int whereIndex = at - vecData;
	--vecSize;
	for (size_t i = whereIndex; i < vecSize; ++i) {
		vecData[i] = vecData[i + 1];
	}

	return Iterator(vecData + whereIndex - 1);
}

template<typename T>
MyVector<T>::template Iterator MyVector<T>::insert(Iterator at, const T& input) {
	CheckCapacity();
	int whereIndex = at - vecData;

	for (size_t i = vecSize; i > whereIndex; --i) {
		vecData[i] = vecData[i - 1];
	}

	vecData[whereIndex] = input;

	++vecSize;

	return Iterator(vecData + whereIndex);
}

template<typename T>
MyVector<T>::template Iterator MyVector<T>::insert(Iterator at, T&& input) {
	CheckCapacity();
	int whereIndex = at - vecData;

	for (size_t i = vecSize; i > whereIndex; --i) {
		vecData[i] = vecData[i - 1];
	}

	vecData[whereIndex] = std::move(input);

	++vecSize;
	return Iterator(vecData + whereIndex);
}

template<typename T>
void MyVector<T>::push_back(const T& other) {
	CheckCapacity();
	T* p = &vecData[vecSize];
	new(p) T(other);
	++vecSize;
}

template<typename T>
void MyVector<T>::push_back(T&& other) {
	CheckCapacity();
	T* p = &vecData[vecSize];
	new(p) T(std::move(other));
	++vecSize;
}

template<typename T>
void MyVector<T>::reserve(size_t newSize) {
	if (newSize > vecCapacity) {
		vecCapacity = newSize;
		IncreaseCapacity();
	}
}

template<typename T>
size_t MyVector<T>::capacity() const {
	return vecCapacity;
}

template<typename T>
size_t MyVector<T>::size() const {
	return vecSize;
}

template<typename T>
T& MyVector<T>::operator[](const size_t index) const {
	assert(0 <= index && index < vecSize);
	return vecData[index];
}