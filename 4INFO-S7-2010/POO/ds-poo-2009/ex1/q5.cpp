#include <list>
#include <iostream>

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
typedef void (A::*Action)();
class CommandA {
	private:
		Action _action;
		static std::list<CommandA* > _commandList;
		static std::list<MementoA* > _mementoList;
		A* _receveur;
	public:
		CommandA(A* receveur,Action action  ):_action(action),_receveur(receveur)
		{
		}
		void execute()
		{
			_mementoList.push_back(_receveur->creerMementoA());
			_commandList.push_back(this);
			(_receveur->*_action)();
		}
		static void undo()
		{
			(_commandList.back())->_receveur->restorerMementoA(_mementoList.back());
			_commandList.pop_back();
			_mementoList.pop_back();
		}
};
std::list<CommandA* > CommandA::_commandList;
std::list<MementoA* > CommandA::_mementoList;
int main()
{
	A* obj = new A(1);
	std::cout << "A(" << obj->getVal() << ")" << std::endl;
	CommandA* c1 = new CommandA(obj, &A::doubler );
	c1->execute();
	std::cout << "A(" << obj->getVal() << ")" << std::endl;
	CommandA* c2 = new CommandA(obj, &A::trippler);
	c2->execute();
	std::cout << "A(" << obj->getVal() << ")" << std::endl;
	CommandA::undo();
	std::cout << "A(" << obj->getVal() << ")" << std::endl;
	CommandA::undo();
	std::cout << "A(" << obj->getVal() << ")" << std::endl;
	return 0;
}
