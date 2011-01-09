#include "A1.h"

A1::A1(int a){
	std::cout << "New A1 : val : " << a << std::endl;
	att=a;
}
A1* A1::clone() const{
	return new A1(att);
}
bool A1::operator==(const A1& x) const{
	return att==x.att;
}