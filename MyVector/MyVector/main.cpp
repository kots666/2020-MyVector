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

	//MyVector<int> vec;
	MyVector<int> vec;

	for (int i = 0; i < 10; ++i) {
		vec.Push_Back(i);
	}

	for (auto p = vec.RBegin(); p != vec.REnd(); ++p) {
		cout << *p << endl;
	}

	cout << vec.Size() << endl;
	cout << vec.Capacity() << endl;
}