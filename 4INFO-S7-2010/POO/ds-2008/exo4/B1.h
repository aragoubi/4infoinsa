#ifndef B1_H
#define B1_H

#include "A1.h"

class B1{
public :
	A1* relation;
	A1* agregation;
	B1(const A1& agr, A1* rel);
	B1(const B1& x);
	~B1();
	bool operator==(const B1& x) const;
	B1& operator=(const B1& x);
};

#endif