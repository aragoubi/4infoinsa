#ifndef A_H
#define A_H

#include "MementoA.h"

class A {
	private:
		int _val;
	public:
		A(int v):_val(v)
		{
		}
		void doubler(){
			_val*=2;
		}
		void trippler(){
			_val*=3;
		}
		int getVal()
		{
			return _val;
		}
		MementoA* creerMementoA()
		{
			return new MementoA(_val);
		}
		void restorerMementoA(MementoA* mem)
		{
			_val = mem->getEtat();
		}
};
#endif
