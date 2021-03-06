// static_example.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "Const.h"
#include "Static.h"

using namespace std;


int static_cycle()
{
	static int a = 10; //static用于函数的局部变量，变量值不会因为函数消失而消失，会保存下来（只会初始化一次）
	a = a + 5;
	return a;
}

const int d = 10; //const全局变量
int main()
{
	//static example
	cout << static_cycle() << endl; //15
	cout << static_cycle() << endl; //20
	cout << static_cycle() << endl; //25

	//int Static::a = 5;        //错误！！static关键字限制了可视域！！ 
	Static::print();//通过类访问静态成员函数,所以静态成员函数不可以访问非静态成员变量
	Static _static(10);
	Static::print();//通过类访问静态成员函数
	_static.print();//通过对象访问静态成员函数
	_static.setStaticValue();
	_static.setStaticValue();
	_static.print();
	cout << "c="<< _static.get() << endl;

	Static _static2(20);  //静态变量只存储一处，但供所有对象使用 a = 6
	Static::print();

	const int c = 0; //const局部变量
	int* p = (int*)&c;  //使用&c时,会从符号表中取出c的值,并将0存在一个新的分配空间地址里,所以*p修改的只是分配出来的空间地址内容,而c还是常量
	*p = 5;          //通过指针修改const变量

	cout << c <<" "<< *p << endl; //0 5

	int *pp = (int*)&d; 
	//*pp = 5;  //段错误 : write access violation

	Const a;
	a.fun();
	a.fun1(); //如果只有const成员函数，非const对象是可以调用const成员函数的
	const Const &b = a; // 在C++中只有被声明为const的成员函数才能被一个const类对象调用。
	b.fun();
	//b.fun2();  //const对象不能调用非const函数 cannot convert 'this' pointer from 'const Const' to 'Const &'	
	//const Const *c = &a;
	//c->fun();
	Const *const d = &a; //const 修饰的是类的时候，才会调用const函数
	d->fun();
	Const *const e = d;
	e->fun();
	const Const *f = c;
	f->fun();

	//常量折叠
	const int constant = 26;
	const int* const_p = &constant; //看到这里能对constant进行取值，判断constant必然后自己的内存空间
	int* modifier = const_cast<int*>(const_p);
	*modifier = 3;
	cout << "constant:  " << constant << "  adderss:  " << &constant << endl; //常量折叠，编译阶段constant已经替换成26
	cout << "*modifier:  " << *modifier << "  adderss:  " << modifier << endl;

    return 0;
}

