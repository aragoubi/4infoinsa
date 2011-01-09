#ifndef A1_H
#define A1_H
#include <iostream>

class A1{
public :
	int att;
	A1(int a);
	bool operator==(const A1& x) const;
	A1* clone() const;
};

#endif