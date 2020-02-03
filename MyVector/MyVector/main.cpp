#include <iostream>
#include <crtdbg.h>
#include <string>
#include "MyVector.h"
#include "MyVector.cpp"

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

using namespace std;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MyVector<string> vec;

	string s1("Hee Jae");
	string s2("Kang");

	vec.emplace_back("Hi");
	vec.emplace_back("My name is");
	vec.push_back(s1);
	vec.push_back(s2);

	for (auto p = vec.begin(); p != vec.end(); ++p) {
		cout << *p << endl;
	}
	cout << "size : " << vec.size() << endl;
	cout << "capacity : " << vec.capacity() << endl;
}