#ifndef MYVECTOR
#define MYVECTOR

template <typename T>
class MyVector {
private:
	size_t vecCapacity;
	size_t vecSize;
	T* vecData;

	// �̸� �Ҵ��� capacity�� ����ִ��� üũ
	void CheckCapacity();

	// �̸� �Ҵ��� capacity�� ����.
	void IncreaseCapacity();
public:
	MyVector(size_t newSize = 0);

	~MyVector();

	// �ݺ��� ������ ���� iterator ����
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

	// vector�� �ݺ��� ��ȯ
	Iterator begin() noexcept;
	Iterator end() noexcept;
	ReverseIterator rbegin() noexcept;
	ReverseIterator rend() noexcept;

	// vector�� data�� ��� ����.
	void clear();

	// �������� ���ø��� ����Ͽ� ���ڰ��� �̿��� ������ ȣ��
	template<typename ...Args>
	void emplace_back(Args&& ...args);

	// at ������ ����� �� ��ġ�� �ٽ� ��ȯ
	Iterator erase(Iterator at);

	// at ������ ���ο� �����͸� �ְ� �� ��ġ�� ��ȯ
	Iterator insert(Iterator at, const T& input);
	Iterator insert(Iterator at, T&& input);

	// ���ο� ���� ���� or �̵��ؼ� �ִ´�.
	void push_back(const T& other);
	void push_back(T&& other);

	// newSize ��ŭ capacity�� ����(�̸� �Ҵ�)���ش�.
	void reserve(size_t newSize);

	// capacity�� size ���� ��ȯ
	size_t capacity() const;
	size_t size() const;

	// []�� ����� ���� ���� ������
	T& operator[] (const size_t index) const;
};
#endif