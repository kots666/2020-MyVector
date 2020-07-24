#ifndef MYVECTOR
#define MYVECTOR

#include <cassert>

template <typename T>
class MyVector {
private:
	size_t vecCapacity;
	size_t vecSize;
	T* vecData;

	// 미리 할당한 capacity가 비어있는지 체크
	void CheckCapacity()
	{
		if (vecSize >= vecCapacity)
		{
			if (vecCapacity < 2) ++vecCapacity;
			else vecCapacity += (vecCapacity / 2);
			IncreaseCapacity();
		}
	}

	// 미리 할당한 capacity의 증설.
		void IncreaseCapacity()
		{
			T* newData = static_cast<T*>(operator new(sizeof(T) * vecCapacity));

			for (size_t i = 0; i < vecSize; ++i)
			{
				T* moveData = &newData[i];
				new(moveData) T(std::forward<T>(vecData[i]));
			}

			clear();

			vecData = newData;
		}
public:
	MyVector(size_t newSize = 0) : vecSize(newSize), vecCapacity(newSize)
	{
		if (newSize < 1) vecData = nullptr;
		else vecData = static_cast<T*>(operator new(sizeof(T) * newSize));
	}

	~MyVector()
	{
		clear();
	}

	// 반복자 패턴을 위한 iterator 선언
	class Iterator {
	private:
		T* pointer;
	public:
		Iterator(T* p = nullptr) : pointer(p) {}
		Iterator(const Iterator& iter) : pointer(iter.pointer) {}
		T& operator *() const { return *pointer; }
		int operator -(const Iterator& iter) { return pointer - iter.pointer; }
		Iterator& operator++()
		{
			++pointer;
			return *this;
		}
		Iterator operator++(int)
		{
			const Iterator temp(*this);
			++pointer;
			return temp;
		}
		Iterator& operator--()
		{
			--pointer;
			return *this;
		}
		Iterator operator--(int)
		{
			const Iterator temp(*this);
			--pointer;
			return temp;
		}
		bool operator !=(const Iterator& iter) const { return pointer != iter.pointer; }
		bool operator ==(const Iterator& iter) const { return pointer == iter.pointer; }
	};

	class ReverseIterator {
	private:
		T* pointer;
	public:
		ReverseIterator(T* p = nullptr) : pointer(p) {}
		ReverseIterator(const ReverseIterator& iter) : pointer(iter.pointer) {}
		T& operator *() const { return *pointer; }
		int operator -(const ReverseIterator& iter) { return pointer - iter.pointer; }
		ReverseIterator& operator++()
		{
			--pointer;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			const ReverseIterator temp(*this);
			--pointer;
			return temp;
		}
		ReverseIterator& operator--()
		{
			++pointer;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			const ReverseIterator temp(*this);
			++pointer;
			return temp;
		}
		bool operator !=(const ReverseIterator& iter) const { return pointer != iter.pointer; }
		bool operator ==(const ReverseIterator& iter) const { return pointer == iter.pointer; }
	};

	// vector의 반복자 반환
	Iterator begin() noexcept { return Iterator(vecData); }
	Iterator end() noexcept { return Iterator(vecData + vecSize); }
	ReverseIterator rbegin() noexcept { return ReverseIterator(vecData + vecSize - 1); }
	ReverseIterator rend() noexcept { return ReverseIterator(vecData - 1); }

	// vector의 data를 모두 비운다.
	void clear()
	{
		if (vecData != nullptr)
		{
			for (size_t i = 0; i < vecSize; ++i)
			{
				vecData[i].~T();
			}
			operator delete (vecData);
			vecData = nullptr;
		}
	}

	// 가변인자 템플릿을 사용하여 인자값을 이용한 생성자 호출
	template<typename ...Args>
	void emplace_back(Args&& ...args)
	{
		CheckCapacity();
		T* newData = &vecData[vecSize];
		new(newData) T(std::forward<Args>(args)...);
		++vecSize;
	}

	// at 지점을 지우고 그 위치를 다시 반환
	Iterator erase(Iterator at)
	{
		int whereIndex = at - vecData;
		--vecSize;
		for (size_t i = whereIndex; i < vecSize; ++i)
		{
			vecData[i] = vecData[i + 1];
		}

		return Iterator(vecData + whereIndex - 1);
	}

	// at 지점에 새로운 데이터를 넣고 그 위치를 반환
	Iterator insert(Iterator at, const T& input)
	{
		CheckCapacity();
		int whereIndex = at - vecData;

		for (size_t i = vecSize; i > whereIndex; --i)
		{
			vecData[i] = vecData[i - 1];
		}

		vecData[whereIndex] = input;

		++vecSize;

		return Iterator(vecData + whereIndex);
	}
	Iterator insert(Iterator at, T&& input)
	{
		CheckCapacity();
		int whereIndex = at - vecData;

		for (size_t i = vecSize; i > whereIndex; --i)
		{
			vecData[i] = vecData[i - 1];
		}

		vecData[whereIndex] = std::forward(input);

		++vecSize;
		return Iterator(vecData + whereIndex);
	}

	// 새로운 값을 복사 or 이동해서 넣는다.
	void push_back(const T& other)
	{
		CheckCapacity();
		T* newData = &vecData[vecSize];
		new(newData) T(other);
		++vecSize;
	}
	void push_back(T&& other)
	{
		CheckCapacity();
		T* newData = &vecData[vecSize];
		new(newData) T(std::forward(other));
		++vecSize;
	}

	// newSize 만큼 capacity를 예약(미리 할당)해준다.
	void reserve(size_t newSize)
	{
		if (newSize > vecCapacity)
		{
			vecCapacity = newSize;
			IncreaseCapacity();
		}
	}

	// capacity와 size 값을 반환
	size_t capacity() const { return vecCapacity; }
	size_t size() const { return vecSize; }

	// []을 사용한 임의 접근 지정자
	T& operator[] (const size_t index) const
	{
		assert(0 <= index && index < vecSize);
		return vecData[index];
	}
};
#endif