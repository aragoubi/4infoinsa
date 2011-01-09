/************************ Classe Element ************************/

template <class T> class Element{

public:
	T _valeur;
	Element* _suiv;

public:
	Element(const T &valeur, Element *s);
	Element(const T &valeur);
};

template <class T>	Element<T>::Element(const T &valeur, Element* s){
	_valeur = valeur;
	_suiv = s;
}
	
template <class T>	Element<T>::Element(const T &valeur){
	_valeur = valeur;
	_suiv = this;
}

/************************ Classe Anneau ************************/

template <class T> class Anneau{

private :
	Element<T> *_courant;

public:
	Anneau();
	~Anneau();
	T& valeurCourante();
	void afficher();
	void ajouter(const T &valeur);
	void positionner(const T &valeur);
};


template <class T> Anneau<T>::Anneau(){
	_courant = NULL;
}

	template <class T> T Anneau<T>::valeurCourante(){
	return _courant->_valeur;
}

template <class T> void Anneau<T>::ajouter( const T& valeur){
	Element* elt = new Element(valeur);
	elt->_suiv= _courant->_suiv;
	_courant->_suiv = elt;
	_courant = elt;
}

template <class T> Anneau<T>::~Anneau(){
	while(_courant->_suiv != _courant){
		_courant->_suiv = _courant->_suiv->_suiv ;
		delete _courant->_suiv ;
	}
	delete _courant;
}

template <class T>void Anneau<T>::positionner(const T& valeur){
	Element* elt_depart = _courant;
	while(_courant->_valeur != valeur){
		_courant = _courant->_suiv;
		if(_courant == elt_depart){
			throw std::string("Tour de l'anneau effectué, element non trouvé");
			break;
		}
	}
}


