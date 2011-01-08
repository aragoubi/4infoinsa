/*
 * Inspired from http://cs.fit.edu/~mmahoney/cse2050/how2cpp.html
 */

/*
::m            Global name m when otherwise hidden by a local declaration
i++            Add 1 to i, result is original value of i
++i            Add 1 to i, result is the new i
throw x        Throw exception x (any type)
x,y            Evaluate x and y (any types), result is y

(a+=b)+=c;   // Legal, add b to a, then add c to a

  >Static  cast
static_cast<T>(x) converts x to type T if a conversion is defined. Usually the value of x is preserved if possible
  double d; d=static_cast<double>(3);  // Explicit 3 to 3.0
  d=3;                                 // Implicit conversion
  d=sqrt(3);                           // Implicit 3.0, sqrt() expects double
  vector<int> v(5);                    // This constructor is explicit
  v=5;                                 // Error, no implicit conversion
  v=static_cast<vector<int> >(5);      // OK

  >Declaration
string s1, s2="xxx", s3("xxx"), s4(3,'x'), *p, a[5], next_Word();
  declares s1 to be a string with initial value "", s2, s3, and s4 to be strings with initial value "xxx", p to be a pointer to string, a to be an array of 5 strings (a[0] to a[4] with initial values ""), and next_Word to be a function that takes no parameters and returns a string.

  >Modifiers
In a declaration, modifiers before the type name apply to all objects in the list. Otherwise they apply to single objects.
  int* p, q;           // p is a pointer, q is an int
  const int a=0, b=0;  // a and b are both const

  >Const
const objects cannot be modified once created.
A pointer to a const object of type T must also be const, of type const T*, meaning that the pointer may be assigned to but its contents may not.
  const double PI=3.1415926535898;
  double* p=&PI;              // Error, would allow *p=4 to change PI
  const double* p=&PI;        // OK, can't assign to *p (but may assign to p)
  double* const p=&PI;        // Error, may assign to *p (but not to p)
  const double* const p=&PI;  // OK, both *p and p are const

  >Reference
A reference creates an alias for an object that already exists. It must be initialized. A reference to a const object must also be const.

  int i=3;
  int& r=i;         // r is an alias for i
  r=4;              // i=4;
  double& pi=PI;    // Error, would allow PI to be modified
  const double& pi=PI;  // OK

  >Function pointers
A function name used without parenthesis is a pointer to a function. Function pointers can be assigned values and called.
  int f(double);     // functions f and g take double and return int
  int g(double);
  int *h(double);    // function h takes double and returns pointer to int
  int (*p)(double);  // p is a pointer to a function that takes double and returns int
  p=f; p(3.0);     // calls f(3.0)
  p=g; p(3.0);     // calls g(3.0)
  p=h;             // Error, type mismatch

  >Templates
Templates can have default arguments and int parameters. The argument to an int parameter must be a value known at compile time.
  template <class T, class U=T, int n=0> class V {};
  V<double, string, 3> v1;
  V<char> v2;  // V<char, char, 0>
  
  >Inheritance
  class B {
    protected: int x;
   } b;                            // Declare class B and object b
   b.x=1;                          // Error, x is protected

   class D: public B {
    void f() {x=1;}               // OK
   };
By default, a base class is private, making all inherited members private. Private base classes are rare and typically used as implementations rather than specializations (A string is a vector, but a stack is not).
  class Stack: Vector<int> {  // or class Stack: private Vector<int>
    public:
      bool empty() const {return size()==0;}  // OK
    } s;
    s.size();   // Error, private
    s.empty();  // OK, public

  >Polymophism
A derived class may redefine inherited member functions, overriding any function with the same name, parameters, return type, and const-ness (and hiding other functions with the same name, thus the overriding function should not be overloaded). The function call is resolved at compile time. This is incorrect in case of a base pointer or reference to a derived object. To allow run time resolution, the base member function should be declared virtual. Since the default destructor is not virtual, a virtual destructor should be added to the base class. If empty, no copy constructor or assignment operator is required. Constructors and = are never virtual.
  class Shape {
   public:
   virtual void draw() const;
   virtual ~Shape() {}
  };
  class Circle: public Shape {
   public:
    void draw() const;      // Must use same parameters, return type, and const
  };

  Shape s; s.draw();        // Shape::draw()
  Circle c; c.draw();       // Circle::draw()
  Shape& r=c; r.draw();     // Circle::draw() if virtual
  Shape* p=&c; p->draw();   // Circle::draw() if virtual
  p=new Circle; p->draw();  // Circle::draw() if virtual
  delete p; 
An abstract base class defines an interface for one or more derived classes, which are allowed to instantiate objects. Abstractness can be enforced by using protected (not private) constructors or using pure virtual member functions, which must be overridden in the derived class or else that class is abstract too. A pure virtual member function is declared =0; and has no code defined.

  >Run time type identification
C++ provides for run time type identification, although this usually indicates a poor design. dynamic_cast<T>(x) checks at run time whether a base pointer or reference is to a derived object, and if so, does a conversion. The base class must have at least one virtual function to use run time type checking.
  #include <typeinfo>    // For typeid()
  typeid(*p)==typeid(T)  // true if p points to a T
  dynamic_cast<T*>(p)    // Convert base pointer to derived T* or 0.
  dynamic_cast<T&>(r)    // Convert base reference to derived T& or throw bad_cast()
*/
