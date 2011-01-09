#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Anneau.h"

void main(void){
	Anneau<double> ano;
	ano.afficher();
	ano.ajouter(1.01);
	ano.afficher();
	ano.ajouter(2.02);
	ano.afficher();
	ano.ajouter(3.03);
	ano.afficher();
	ano.positionner(2.02);
	ano.afficher();
	std::cout << "Appuyer sur une touche pour quitter" << std::endl;
	char car = getchar();
}