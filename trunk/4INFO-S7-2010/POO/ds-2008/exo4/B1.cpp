#include "B1.h"

B1::B1(const A1& agr, A1* rel){
	std::cout << "New B1 : vals : (" << agr.att << "," << rel->att << ")" << std::endl;
	agregation=agr.clone();
	relation=rel;
}
B1::B1(const B1& x){
	agregation=x.agregation->clone();
	relation=x.relation;
}
B1::~B1(){
	std::cout << "destruction agr" << std::endl;
	delete agregation;
	std::cout << "destruction rel" << std::endl;
	if(relation) delete relation;
	std::cout << "Appuyer sur une touche pour quitter" << std::endl;
	char car = getchar();
}
bool B1::operator==(const B1& x) const{
	return(agregation->att == x.agregation->att && relation->att == x.relation->att);
}

B1& B1::operator=(const B1& x){
	agregation=x.agregation->clone();
	relation=x.relation;
	return (*this);
}