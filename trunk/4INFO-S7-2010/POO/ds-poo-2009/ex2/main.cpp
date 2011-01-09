#include "index.h"
#include <stdlib.h>
#include <iostream>

int main(void){
	int ent1=2;
	Enregistrement<int> e1(1,&ent1);
	int ent2=4;
	Enregistrement<int> e2(1,&ent1);
	int ent3=3;
	Enregistrement<int> e3(1,&ent1);
	int ent4=1;
	Enregistrement<int> e4(1,&ent1);
	Index<Enregistrement<int>> i;
	i.inserer(&e1);
	//i.inserer(e2);
	std::cout << "Appuyer sur une touche pour quitter" << std::endl;
	char car = getchar();
	return 0;
}