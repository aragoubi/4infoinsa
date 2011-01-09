#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "B1.h"


void main(void){
	A1* a1=new A1(1);
	A1* a2=new A1(2);
	A1* a3=new A1(1);
	A1* a4=new A1(2);
	B1 b1(*a1,a2);
	B1 b2(*a3,a4);
	B1 b3(*a1,a2);
	b3=b1;
	std::cout << "Appuyer sur une touche pour quitter" << std::endl;
	char car = getchar();
}