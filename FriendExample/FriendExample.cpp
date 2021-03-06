#include <iostream>
using namespace std;


class A;    // 类 A 的声明，因为 A 的友元函数，即 B 的成员函数要用到 A，所以必须先声明类 A
			// 但此时还不能定义 A，因为 B 还没有定义，B 的成员函数就无从谈起
class B {   // 类 B 的定义
public:
	void set_A_data(int x, A &a);   // 类 A 的友元函数，同时是 B 的成员函数
									// 但只能声明，还不能定义，因为 A 还没有定义，访问 A 的成员就无从谈起
};


class A {
public:
	friend class C;  // // 友元类的声明：C 是 A 的友元类
	friend void set_data(int x, A &a);      // 友元函数的声明
	friend void B::set_A_data(int x, A &a);   // 将 B 的成员函数声明为 A 的友元成员函数；所以必须先定义 B
	int get_data() { return data; }
private:
	int data;
	void print_data() { cout << data << endl; }
};

void set_data(int x, A &a) {                // 友元函数的定义
	a.data = x;
	cout << a.data << endl;                 // 无障碍读写类的私有成员
}

void B::set_A_data(int x, A &a) {   // 只有在定义类 A 后才能定义该函数
	a.data = x;          // 访问 A 的私有成员变量
	a.print_data();      // 访问 A 的私有成员函数
}

class C {              // 友元类的定义，可以访问 A 中的成员
public:
	void set_A_data(int x, A &a) {
		a.data = x;
	}

	int get_A_data(A& a) {
		return a.data;
	}
};

int main(void) {
	//友元函数
	class A a;
	set_data(1, a);
	// cout << a.data;  // err
	cout << a.get_data() << endl; //1

	//友元类
	class C c;
	c.set_A_data(2, a);
	cout << c.get_A_data(a) << endl;  // 2

	//友元成员函数
	class B b;
	b.set_A_data(3, a);
	cout << a.get_data() << endl; //3
	return 0;
}


