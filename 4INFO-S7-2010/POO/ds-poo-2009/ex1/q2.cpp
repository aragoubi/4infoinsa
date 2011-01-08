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
};
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
