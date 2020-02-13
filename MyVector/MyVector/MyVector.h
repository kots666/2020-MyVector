#ifndef MYVECTOR
#define MYVECTOR

template <typename T>
class MyVector {
private:
	size_t vecCapacity;
	size_t vecSize;
	T* vecData;

	// 미리 할당한 capacity가 비어있는지 체크
	void CheckCapacity();

	// 미리 할당한 capacity의 증설.
	void IncreaseCapacity();
public:
	MyVector(size_t newSize = 0);

	~MyVector();

	// 반복자 패턴을 위한 iterator 선언
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

	// vector의 반복자 반환
	Iterator begin() noexcept;
	Iterator end() noexcept;
	ReverseIterator rbegin() noexcept;
	ReverseIterator rend() noexcept;

	// vector의 data를 모두 비운다.
	void clear();

	// 가변인자 템플릿을 사용하여 인자값을 이용한 생성자 호출
	template<typename ...Args>
	void emplace_back(Args&& ...args);

	// at 지점을 지우고 그 위치를 다시 반환
	Iterator erase(Iterator at);

	// at 지점에 새로운 데이터를 넣고 그 위치를 반환
	Iterator insert(Iterator at, const T& input);
	Iterator insert(Iterator at, T&& input);

	// 새로운 값을 복사 or 이동해서 넣는다.
	void push_back(const T& other);
	void push_back(T&& other);

	// newSize 만큼 capacity를 예약(미리 할당)해준다.
	void reserve(size_t newSize);

	// capacity와 size 값을 반환
	size_t capacity() const;
	size_t size() const;

	// []을 사용한 임의 접근 지정자
	T& operator[] (const size_t index) const;
};
#endif