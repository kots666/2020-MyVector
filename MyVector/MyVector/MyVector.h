#ifndef MYVECTOR
#define MYVECTOR

template <typename T>
class MyVector {
private:
	size_t vecCapacity;
	size_t vecSize;
	T* vecData;

	void CheckCapacity();
	void IncreaseCapacity();
public:
	MyVector(size_t s = 0);

	~MyVector();

	class Iterator {
	private:
		T* pointer;
	public:
		Iterator(T* p = nullptr);
		Iterator(const Iterator& iter);
		T& operator *();
		int operator -(const Iterator& iter);
		Iterator& operator++();
		const Iterator operator++(int);
		Iterator& operator--();
		const Iterator operator--(int);
		bool operator !=(const Iterator& iter);
		bool operator ==(const Iterator& iter);
	};

	class ReverseIterator {
	private:
		T* pointer;
	public:
		ReverseIterator(T* p = nullptr);
		ReverseIterator(const ReverseIterator& iter);
		T& operator *();
		int operator -(const ReverseIterator& iter);
		ReverseIterator& operator++();
		const ReverseIterator operator++(int);
		ReverseIterator& operator--();
		const ReverseIterator operator--(int);
		bool operator !=(const ReverseIterator& iter);
		bool operator ==(const ReverseIterator& iter);
	};


	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	void clear();

	Iterator erase(Iterator at);

	void push_back(const T& other);

	void push_back(T&& other);

	void reserve(size_t n);

	size_t capacity() const;

	size_t size() const;

	T& operator[] (const size_t n) const;
};
#endif