#pragma once

#include <iostream>
using namespace std;

class Static
{
public:
	Static(int value);
	static void print();//��̬��Ա����
	static void setStaticValue();
	int get() { return c; }
private:
	static int a;//��̬���ݳ�Ա������
	static const int b;//������̬���ݳ�Ա�������ڹ��캯���г�ʼ����
	const int c;//�������ݳ�Ա
	int d;
};
int Static::a = 0;//��̬��Ա�Ķ���+��ʼ��
const int Static::b = 25;//��̬������Ա����+��ʼ��


Static::Static(int value) :c(value)//������Ա�ĳ�ʼ��
{
	a += 1;
}

void Static::print()
{
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	//cout << "c=" << c <<endl; //error,���ܷ��ʷǾ�̬��Աillegal reference to non - static member 'Static::c'
	//cout << "d=" << d << endl; 
}
//���ڸ���ʵ�֣�������ʵ�ֲ�����Ϊinline����������ͬ�ģ���Ϊ��������
inline void Static::setStaticValue() {
	a += 2;
}