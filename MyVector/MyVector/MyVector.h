#ifndef MYVECTOR
#define MYVECTOR

template <typename T>
class MyVector {
private:
	size_t capacity;
	size_t size;
	T* data;

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
		T& operator -(const Iterator& iter) { return pointer - iter.pointer; }
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
		//T& operator -(const ReverseIterator& iter);
		ReverseIterator& operator++();
		const ReverseIterator operator++(int);
		ReverseIterator& operator--();
		const ReverseIterator operator--(int);
		bool operator !=(const ReverseIterator& iter);
		bool operator ==(const ReverseIterator& iter);
	};


	Iterator Begin();
	Iterator End();
	ReverseIterator RBegin();
	ReverseIterator REnd();

	void Clear();

	void Push_Back(const T& other);

	void Push_Back(T&& other);

	void Reserve(size_t n);

	size_t Capacity() const;

	size_t Size() const;

	T& operator[] (const size_t n) const;
};
#endif