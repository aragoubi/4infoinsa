#ifndef INDEX_H
#define INDEX_H

#include "enregistrement.h"
#include <list>

using namespace std;

template <class T> class Index{
private:
	list<T> l;
public:
	void inserer(T* enr) const;
};

template <class T> void Index<T>::inserer(T* enr) const{
	int crit = enr->getCrit();
	//list<T>::iterator it;
	const list<T>::const_iterator i=l.cbegin();
	while(i!=l.cend()){
		i++;
	}
	l.insert(i,enr);
}
#endif