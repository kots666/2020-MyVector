#include <iostream>
#include <crtdbg.h>
#include "MyVector.h"
#include "MyVector.cpp"

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

using namespace std;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MyVector<int> vec;

	for (int i = 0; i < 30; ++i) {
		vec.push_back(i);
	}

	int a = 38;

	auto p = vec.begin();

	vec.insert(p, a);

	vec.insert(vec.begin(), 10);


	for (auto p = vec.begin(); p != vec.end(); ++p) {
		if ((*p) % 3 == 0)
			p = vec.erase(p);
	}

	for (auto p = vec.rbegin(); p != vec.rend(); ++p) {
		cout << *p << endl;
	}

	cout << "size : " << vec.size() << endl;
	cout << "capacity : " << vec.capacity() << endl;
}