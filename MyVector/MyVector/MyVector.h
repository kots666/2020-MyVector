#ifndef MYVECTOR
#define MYVECTOR

#include <cassert>

template <typename T>
class MyVector {
private:
	size_t vecCapacity;
	size_t vecSize;
	T* vecData;

	// �̸� �Ҵ��� capacity�� ����ִ��� üũ
	void CheckCapacity()
	{
		if (vecSize >= vecCapacity)
		{
			if (vecCapacity < 2) ++vecCapacity;
			else vecCapacity += (vecCapacity / 2);
			IncreaseCapacity();
		}
	}

	// �̸� �Ҵ��� capacity�� ����.
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

	// �ݺ��� ������ ���� iterator ����
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

	// vector�� �ݺ��� ��ȯ
	Iterator begin() noexcept { return Iterator(vecData); }
	Iterator end() noexcept { return Iterator(vecData + vecSize); }
	ReverseIterator rbegin() noexcept { return ReverseIterator(vecData + vecSize - 1); }
	ReverseIterator rend() noexcept { return ReverseIterator(vecData - 1); }

	// vector�� data�� ��� ����.
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

	// �������� ���ø��� ����Ͽ� ���ڰ��� �̿��� ������ ȣ��
	template<typename ...Args>
	void emplace_back(Args&& ...args)
	{
		CheckCapacity();
		T* newData = &vecData[vecSize];
		new(newData) T(std::forward<Args>(args)...);
		++vecSize;
	}

	// at ������ ����� �� ��ġ�� �ٽ� ��ȯ
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

	// at ������ ���ο� �����͸� �ְ� �� ��ġ�� ��ȯ
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

	// ���ο� ���� ���� or �̵��ؼ� �ִ´�.
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

	// newSize ��ŭ capacity�� ����(�̸� �Ҵ�)���ش�.
	void reserve(size_t newSize)
	{
		if (newSize > vecCapacity)
		{
			vecCapacity = newSize;
			IncreaseCapacity();
		}
	}

	// capacity�� size ���� ��ȯ
	size_t capacity() const { return vecCapacity; }
	size_t size() const { return vecSize; }

	// []�� ����� ���� ���� ������
	T& operator[] (const size_t index) const
	{
		assert(0 <= index && index < vecSize);
		return vecData[index];
	}
};
#endif