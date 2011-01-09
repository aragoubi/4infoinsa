#ifndef ELEMENT_H
#define ELEMENT_H

template <class T>
class Element {
public:
	T _valeur;
	Element *_suiv;
	Element(const T &valeur, Element *s);
	Element(const T &valeur);
	~Element();
};

template <class T> Element<T>::Element(const T &valeur, Element<T> *s){
	_valeur = valeur;
	_suiv = s;
}

template <class T> Element<T>::Element(const T &valeur){
	_valeur = valeur;
	_suiv = this;
}

template <class T> Element<T>::~Element(){
	std::cout << "Appel destructeur de l'element : " << _valeur << std::endl;
	Element<T> *t = this;
	while(t->_valeur != t->_suiv->_valeur){
		Element<T> *s = t->_suiv;
		std::cout << "Destruction de l'élément : " << t->_valeur << std::endl;
		delete t;
		t=s;
	}
	//delete t;
	std::cout << "Fin destruction" << std::endl;
	char car = getchar();
}

#endif