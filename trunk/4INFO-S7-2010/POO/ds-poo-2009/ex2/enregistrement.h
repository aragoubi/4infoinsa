#ifndef	ENREGISTREMENT_H
#define ENREGISTREMENT_H

template <class T> class Enregistrement{
private:
	int critere;
	T* ptr;
public:
	Enregistrement(int i,T* p);
	int getCrit();
};

template <class T> Enregistrement<T>::Enregistrement(int i,T* p){
	critere = i;
	ptr = p;
}

template <class T> int Enregistrement<T>::getCrit(){
	return critere;
}

#endif
