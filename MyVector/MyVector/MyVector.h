#pragma once
template <typename T>
class MyVector {
private:
	size_t capacity;
	size_t size;
	T* data;

	void IncreaseCapacity() {
		T* newData = new T[capacity];
		for (size_t i = 0; i < size; ++i) {
			newData[i] = data[i];
		}
		delete[] data;

		data = newData;
	}
public:
	MyVector() : size(0), capacity(0), data(nullptr) {}

	~MyVector() {
		Clear();
	}

	MyVector(size_t s = 1) : size(s), capacity(s), data(new T[s]) {}


	void Clear() {
		if (data != nullptr) {
			delete[] data;
			data = nullptr;
		}
	}

	void Reserve(size_t n) {
		if (n > capacity) {
			capacity = n;
			IncreaseCapacity();
		}
	}
};

