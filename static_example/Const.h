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
	void fun()  //const��Ա�������Ա���Ӧ�ľ�����ͬ�β��б�ķ�const��Ա��������,������Ϊconst�ĳ�Ա����ֻ�ܱ�һ��const��������
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

	void fun(const string & str) const  //������д���ָ�����͵����ݳ�Ա������const����ֻ�ܱ�֤���޸ĸ�ָ���ֵ�������ܱ�֤���޸�ָ��ָ��Ķ��󡣲��Ƽ�
	{
		//sName = str.c_str(); // error:expression must be a modifiable lvalue �����޸�sName;
		for (int i = 0; i < str.size(); ++i){
			sName[i]= str[i];    // ���õķ�񣬵����Ǵ����
		}
	}

private:    
	int iValue;
	char *sName;
};

