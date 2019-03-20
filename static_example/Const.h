#pragma once
#include <iostream>
using namespace std;

class Const {
public:  
	Const() {
	}
	~Const() {
		delete []sName;
		sName = NULL;
	}
	void fun()  //const成员函数可以被对应的具有相同形参列表的非const成员函数重载,但声明为const的成员函数只能被一个const类对象调用
	{
		cout << "non const" << endl;
	}

	void fun() const
	{
		cout << "const" << endl;
	}

	void fun1() const
	{
		cout << "const 1" << endl;
	}

	void fun2()
	{
		cout << "non const 1" << endl;
	}

	void fun(const string & str) const  //如果类中存在指针类型的数据成员即便是const函数只能保证不修改该指针的值，并不能保证不修改指针指向的对象。不推荐
	{
		//sName = str.c_str(); // error:expression must be a modifiable lvalue 不能修改sName;
		for (int i = 0; i < str.size(); ++i){
			sName[i]= str[i];    // 不好的风格，但不是错误的
		}
	}

private:    
	int iValue;
	char *sName;
};

