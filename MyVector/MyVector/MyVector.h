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
		T& operator *() const;
		int operator -(const Iterator& iter);
		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator--();
		Iterator operator--(int);
		bool operator !=(const Iterator& iter) const;
		bool operator ==(const Iterator& iter) const;
	};

	class ReverseIterator {
	private:
		T* pointer;
	public:
		ReverseIterator(T* p = nullptr);
		ReverseIterator(const ReverseIterator& iter);
		T& operator *() const;
		int operator -(const ReverseIterator& iter);
		ReverseIterator& operator++();
		ReverseIterator operator++(int);
		ReverseIterator& operator--();
		ReverseIterator operator--(int);
		bool operator !=(const ReverseIterator& iter) const;
		bool operator ==(const ReverseIterator& iter) const;
	};


	Iterator begin() noexcept;
	Iterator end() noexcept;
	ReverseIterator rbegin() noexcept;
	ReverseIterator rend() noexcept;

	void clear();

	Iterator erase(Iterator at);

	Iterator insert(Iterator at, const T& input);

	Iterator insert(Iterator at, T&& input);

	void push_back(const T& other);

	void push_back(T&& other);

	void reserve(size_t n);

	size_t capacity() const;

	size_t size() const;

	T& operator[] (const size_t n) const;
};
#endif