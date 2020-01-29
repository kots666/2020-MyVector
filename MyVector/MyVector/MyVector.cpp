#include "MyVector.h"

void MyVector::Grow()
{
	_capacity *= 2;
	MyObject* newManager = new MyObject[_capacity]{};
	for (size_t i = 0; i < _vectorSize; ++i)
	{
		newManager[i] = _objectManager[i];
	}
	delete[] _objectManager;

	_objectManager = newManager;
}

void MyVector::DeleteAllManager()
{
	if (_objectManager != nullptr)
	{
		delete[] _objectManager;
		_objectManager = nullptr;
	}
}

void MyVector::Sort()
{
	std::sort(&_objectManager[0], &_objectManager[_vectorSize], [](const MyObject& lhs, const MyObject& rhs) -> bool
	{
		return lhs._id < rhs._id;
	});

	size_t sumSize = 0;

	for (size_t i = 0; i < _capacity; ++i) {
		if (_objectManager[i].isWorthy) ++sumSize;
	}

	_vectorSize = sumSize;
}

MyVector::MyVector() : _vectorSize(0), _capacity(1)
{
	_objectManager = new MyObject[1];
}

MyVector::MyVector(int capacity) : _capacity(capacity)
{
	_objectManager = new MyObject[capacity] {};
}

MyVector::MyVector(const MyVector & other) : _vectorSize(other._vectorSize), _capacity(other._capacity)
{
	_objectManager = new MyObject[_capacity];
	for (size_t i = 0; i < _vectorSize; ++i)
	{
		_objectManager[i] = other._objectManager[i];
	}
}

MyVector::MyVector(MyVector && other) noexcept : _vectorSize(other._vectorSize), _capacity(other._capacity), _objectManager(other._objectManager)
{
	other._vectorSize = 0;
	other._capacity = 0;
	other._objectManager = nullptr;
}

MyVector & MyVector::operator=(const MyVector & other)
{
	if (this == &other) return *this;

	DeleteAllManager();

	_vectorSize = other._vectorSize;
	_capacity = other._capacity;
	_objectManager = new MyObject[_capacity];
	for (size_t i = 0; i < _vectorSize; ++i)
	{
		_objectManager[i] = other._objectManager[i];
	}

	return *this;
}

MyVector MyVector::operator=(MyVector && other) noexcept
{
	if (this == &other) return *this;

	DeleteAllManager();

	_vectorSize = other._vectorSize;
	_capacity = other._capacity;
	_objectManager = other._objectManager;

	other._vectorSize = 0;
	other._capacity = 0;
	other._objectManager = nullptr;
	
	return *this;
}

MyVector::~MyVector()
{
	DeleteAllManager();
}

int MyVector::GetCapacity() const
{
	return _capacity;
}

int MyVector::GetSize() const
{
	return _vectorSize;
}

void MyVector::Add(int id)
{
	if (_vectorSize >= _capacity) Grow();
	_objectManager[_vectorSize]._id = id;
	_objectManager[_vectorSize++].isWorthy = true;
}

MyObject * MyVector::FindById(int MyObjectId) const
{
	for (size_t i = 0; i < _vectorSize; ++i)
	{
		if (MyObjectId == _objectManager[i]._id)
		{
			return &_objectManager[i];
		}
	}
	return nullptr;
}

void MyVector::TrimToSize()
{
	_capacity = _vectorSize;
	MyObject* newManager = new MyObject[_capacity];
	for (size_t i = 0; i < _vectorSize; ++i)
	{
		newManager[i] = _objectManager[i];
	}
	delete[] _objectManager;

	_objectManager = newManager;
}

MyObject & MyVector::operator[](size_t index)
{
	return _objectManager[index];
}

std::string MyVector::ToString() const
{
	std::string myVectorString;
	for (size_t i = 0; i < _vectorSize; ++i)
	{
		myVectorString.append(std::to_string(_objectManager[i]._id));
		myVectorString.append(" ");
	}
	return myVectorString;
}

void MyVector::RemoveAll(int MyObjectId)
{
	for (size_t i = 0; i < _vectorSize; ++i)
	{
		if (MyObjectId == _objectManager[i]._id) {
			_objectManager[i].isWorthy = false;
			_objectManager[i]._id = INT_MAX;
		}
	}
	Sort();
}

MyVector * MyVector::GroupById(int * numGroups)
{
	if (_objectManager != nullptr)
	{
		int oldID(INT_MAX);
		int count(0);

		for (size_t i = 0; i < _vectorSize; ++i)
		{
			if (_objectManager[i].isWorthy)
			{
				if (_objectManager[i]._id != oldID)
				{
					oldID = _objectManager[i]._id;
					++count;
				}
			}
			break;
		}
		*numGroups = count;

		MyVector* vectorManager = new MyVector[count];

		oldID = INT_MAX;
		int i = 0;
		int k = -1;

		while (_objectManager[i].isWorthy)
		{
			if (_objectManager[i]._id != oldID)
			{
				++k;
				oldID = _objectManager[i]._id;
			}
			vectorManager[k].Add(_objectManager[i++]._id);
		}

		return vectorManager;
	}
	return nullptr;
}