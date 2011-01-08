#ifndef MEMENTOA_H
#define MEMENTOA_H

#include "A.h"
class MementoA {
	private:
		int _etat;
	public:
		MementoA(int etat):_etat(etat){ }
		int getEtat()
		{
			return _etat;
		}
};
#endif
