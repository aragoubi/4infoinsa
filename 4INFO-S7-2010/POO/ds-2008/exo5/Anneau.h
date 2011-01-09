#ifndef ANNEAU_H
#define ANNEAU_H

#include "Element.h"
#include <stdlib.h>

template <class T>
class Anneau{
private :
	Element<T> *_courant;
public:
	Anneau();
	~Anneau();
	T& valeurCourante() { return _courant->_valeur;}
	void afficher();
	void ajouter(const T &valeur);
	void positionner(const T &valeur);
};

template <class T> Anneau<T>::Anneau(void){
	_courant = NULL;
}

template <class T> void Anneau<T>::afficher(){
	if(_courant == NULL){
		std::cout << "VIDE" << std::endl;
	} else
		std::cout << valeurCourante() << std::endl;
}

template <class T> void Anneau<T>::ajouter(const T &valeur){
	Element<T> *e;
	if(_courant == NULL) e = new Element<T>(valeur);
	else {
		e = new Element<T>(valeur,_courant->_suiv); //nouvel elt inséré
		_courant->_suiv = e;
	}
	_courant = e;
}

template <class T> void Anneau<T>::positionner(const T &valeur){
	Element<T> *t = _courant;
	while(t->_valeur != valeur){
		std::cout << "Passage au suivant de "<< t->_valeur << " qui est " << t->_suiv->_valeur << std::endl;
		t = t->_suiv;
		char car = getchar();
	}
	_courant = t;
}

template <class T> Anneau<T>::~Anneau(void){
	std::cout << "Appel destructeur de l'anneau courant" << std::endl;
	delete _courant;
}

#endif