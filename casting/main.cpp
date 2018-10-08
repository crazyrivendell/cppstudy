/*
cast study:
static_cast,dynamic_cast, reinterpret_cast, const_cast
*/

#include <stdlib.h>
#include <iostream>
using namespace std;

class Base
{
public:
    int m_iNum;
	virtual void foo() {};
};
class Derived :public Base
{
public:
	char *m_szName[100];
};
class Derived1 : public Base
{
public:
	int v1 = 1;
	void foo() {
		cout << "Derived1" << endl;
	}

	void showOne() {
		cout << "Yes! It's Derived1." << endl;
	}
};
class Derived2 : public Base
{
public:
	int v2 = 2;
	void foo() {
		cout << "Derived2" << endl;
	}

	void showTwo() {
		cout << "Yes! It's Derived2." << endl;
		//cout << v2 << endl;  //running error
	}
};

struct Foo { virtual ~Foo() {} };
struct Bar { virtual ~Bar() {} };

void static_cast_fun()
{
	/*
	static_cast
	编译时类型检查
	*/
	int num = 0;
	double number = 3.14;
	num = number; // [Warning] converting to `int' from `double' 
	cout << num <<endl;

	int num_ = 0;
	double number_ = 3.14;
	num_ = static_cast<int>(number_);
	cout << num << endl;

	int number1 = 10;
	cout << static_cast<double>(number1) / 3 << endl;

	int number2 = 10;
	cout << (double)number2 / 3 << endl;

	/*
	Bar b;
	try {
	    // static_cast and safe_cast to reference can only be used
		// for valid initializations or for lvalue casts between related classes
		Foo& f = static_cast<Foo&>(b); //compile error
	}
	catch (const std::bad_cast& e)
	{
		std::cout << e.what() << '\n';
	}
	*/
}

void dynamic_cast_fun(Base *pb)
{
	Derived *pd1 = static_cast<Derived *>(pb);
	Derived *pd2 = dynamic_cast<Derived *>(pb);
	if (pd2) {
		/*
		如果pe实际指向一个Derived对象,
		dynamic_cast成功，并且开始指向Derived对象起始处
		*/
		cout <<"dynamic_cast success." << endl;
	}
	else {
		/*
		//如果pe不是实际指向Programmer对象，
		dynamic_cast失败，并且pm = 0
		*/
		cout<<"dynamic_cast fail."<<endl;
	}

}

void cross_cast_fun()
{
	/*
	dynamic_cast还支持交叉转换（cross cast）
	使用static_cast进行转换是不被允许的，将在编译时出错；
	而使用 dynamic_cast的转换则是允许的，但结果是空指针。
	*/
	Derived1 *pd1 = new Derived1;
    pd1->m_iNum = 100;
    //Derived2 *pd2 = static_cast<Derived2 *>(pd1); //compile error
    Derived2 *pd2 = dynamic_cast<Derived2 *>(pd1); //pd2 is NULL
	if (pd2 == nullptr) {
		cout << "cross cast success" << endl;
	}
    delete pd1;

	Derived1 *pd1_ = new Derived1;
	try {
		Derived2 *pd2_ = dynamic_cast<Derived2 *>(pd1_); //pd2_ is NULL
		pd2_->showTwo();
		//cout << pd2_->v2 << endl; //running error
	}
	catch(const std::bad_cast& e)
	{
		cout << e.what() << endl;
	}
	delete pd1_;

	Bar b;
	try {
		// static_cast and safe_cast to reference can only be used
		// for valid initializations or for lvalue casts between related classes
		Foo& f = dynamic_cast<Foo&>(b); //compile error
	}
	catch (const std::bad_cast& e)
	{
		std::cout << e.what() << '\n';
	}
}

int reinterpret_cast_fun() {
	int i = 0;
	char* str = "test";

	i = reinterpret_cast<int>(str);//指针地址转成int

	cout << i << endl;

	int *ip;
	ip = reinterpret_cast<int*>(str);
	cout << ip << endl;

	return 0;
}

void const_cast_fun(const int* p)
{
	int *v = const_cast<int *>(p);
	*v = 20;
}

void main()
{
	/*static_cast*/
	static_cast_fun();

	/*dynamic_cast*/
	Base *pb = new Derived;
	dynamic_cast_fun(pb);
	delete pb;

	Base *pb_ = new Base;
	dynamic_cast_fun(pb_);
	delete pb_;

	cross_cast_fun();

	/*reinterpret_cast*/
	reinterpret_cast_fun();

	/*const_cast*/
	int var = 10;
	cout << var << endl;
	const_cast_fun(&var);
	cout << var << endl;
}