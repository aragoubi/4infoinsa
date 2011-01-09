#include <iostream>
using namespace std;

class A {
private:
	int * _a;

public:
	A(int a) {
		cout << "Creation A " << a << endl;
		_a = new int;
		*_a = a;
	}

	int get() { return *_a; }
	void set(int a) { *_a = a++; }
	void modification(int &a) { *_a = a++; }

	A operator+(const A &a) {
		A ret (*_a+*a._a);
		return ret;
	}

	A(const A &a) {
		_a = new int;
		*_a = *a._a;
		cout << "Creation A Recopie " << *a._a << endl;
	}
};


int main(void) {
	A a1(1);
	A a2(2);
	A a3 = a2 + 4;
	int i = a1.get();
	A a4(a1);
	A a5 = a4;
	a1.modification(i);
	a5.set(i);

	cout << "i " << i << endl;
	cout << "a1 " << a1.get() << endl;
        cout << "a2 " << a2.get() << endl;
        cout << "a3 " << a3.get() << endl;
        cout << "a4 " << a4.get() << endl;
        cout << "a5 " << a5.get() << endl;
	return 0;
}
