#include "ValueTest.h"
#include "MoveTest.h"
#include "ForwardTest.h"
typedef int &  lRef;
typedef int && rRef;

typedef const int &  lcRef;
typedef const int && rcRef;


int main()
{

	int i = 0;
	int & j = i;
	int&& k = 0;

	int   t1;         // 类型 T
	int&  t2 = t1;    // T&  表示 T 的左值引用类型，t2 是左值引用类型的变量，它引用的是一个左值
	int&& t3 = int();   // T&& 表示 T 的右值引用类型，t3 是右值引用类型的变量，它引用的是一个右值

	//int&  t4 = int();   // err: 左值引用 不能绑定一个 右值
	//int&& t5 = t1;    // err: 右值引用 不能绑定一个 左值

	const int& t6 = t1;   // const T& 表示 T 的常量（左值）引用
	const int& t7 = int();  // 常量引用类型是“万能”的引用类型

	// 不能把 常量类型 绑定到 非常量引用类型 上
	//int&& t8 = t6;        // err: 不能把常量类型绑定到 右值引用类型
	//int&  t9 = t6;        // err: 也不能把常量类型绑定到 左值引用类型

	// 合法
	cs _cs = get_cs();
	//(get_cs() = cs(2)).change(323);
	//get_cs() = cs(2);// operator=()
	//get_cs().change(32);

	//const cs& ref = get_cs();


	//引用折叠
	cout << "reference collapsing example" << endl;
	int a = 10;

	// 左值引用
	lRef    b = a;    // T&
	lRef &  c = a;    // T& &
	lRef && d = a;    // T& &&
	rRef &  e = a;    // T&& &

	// 右值引用
	rRef    f = 10;   // T&&   
	rRef && g = 10;   // T&& &&

	// 左值引用
	lcRef     b2 = a;    // const T&
	lcRef &   c2 = a;    // const T& &
	lcRef &&  d2 = a;    // const T& &&
	rcRef &   e2 = a;    // const T&& &

	// 右值引用
	rcRef     f2 = 10;   // const T&&
	rcRef &&  g2 = 10;   // const T&& &&

	//move 移动引用，避免拷贝
	cout << "move example" << endl;
	MoveTest a1;                                 // construct
	a1.set_data(1);
	cout << a1.get_data() << endl;  // 1

	MoveTest a2 = a1;                            // copy construct
	cout << a2.get_data() << endl;  // 1
	a2.set_data(2);
	cout << a2.get_data() << endl;  // 2
	cout << a1.get_data() << endl;  // 1

	MoveTest a3 = move(a1);                      // move construct
	a3.set_data(3);
	cout << a3.get_data() << endl;  // 3
	cout << a1.get_data() << endl;  // 3: 因为没有深拷贝，指向的是同一块地址

	//forward 完美转发
	cout << "forward example" << endl;
	int to_forward = 1;
	forwardValue_fail(to_forward);    // 传入一个左值
						// val 会被推断为是一个左值引用类型

	forwardValue_fail(1);    // 传入一个右值
						// 虽然 val 会被推断为是一个右值引用类型，但它本身是一个左值

	forwardValue_success(to_forward);    // 传入一个左值

	forwardValue_success(1);    // 传入一个右值

	return 0;
}
