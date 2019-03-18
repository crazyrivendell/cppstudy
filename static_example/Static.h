#pragma once

#include <iostream>
using namespace std;

class Static
{
public:
	Static(int value);
	static void print();//静态成员函数
	static void setStaticValue();
	int get() { return c; }
private:
	static int a;//静态数据成员的声明
	static const int b;//常量静态数据成员（可以在构造函数中初始化）
	const int c;//常量数据成员
	int d;
};
int Static::a = 0;//静态成员的定义+初始化
const int Static::b = 25;//静态常量成员定义+初始化


Static::Static(int value) :c(value)//常量成员的初始化
{
	a += 1;
}

void Static::print()
{
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	//cout << "c=" << c <<endl; //error,不能访问非静态成员illegal reference to non - static member 'Static::c'
	//cout << "d=" << d << endl; 
}
//类内给出实现，与类外实现并声明为inline函数都是相同的，均为内联函数
inline void Static::setStaticValue() {
	a += 2;
}