#include <iostream>
using namespace std;

class A {
public:
	A(int a1) : _a1(a1) { }
	int f1() const { return _a1; }
	virtual int f2() const {return _a1; }
protected:
	int _a1;
};

class B : public A {
public:
	B(int a1, int a2) : A(a1), _a2(a2) {}
	int f1() const { return _a2; }
	virtual int f2() const { return _a2; }
protected:
	int _a2;
};

int main(void) {
	B objB(1,2);
	A* ptrA = &objB;
	B* ptrB = &objB;
	B& refB = objB;

	cout << objB.f1() << endl;
	cout << ptrA->f1() << endl;
	cout << ptrB->f1() << endl;
	cout << refB.f1() << endl;

        cout << objB.f2() << endl;
        cout << ptrA->f2() << endl;
        cout << ptrB->f2() << endl;
        cout << refB.f2() << endl;

	return 0;
}
