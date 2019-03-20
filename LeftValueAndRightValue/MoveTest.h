#pragma once
#include <iostream>
using namespace std;

class MoveTest {
public:
	MoveTest() : m_ptr(new int(0)) {                    // new 堆内存
		cout << "construct" << endl;
	}

	MoveTest(const MoveTest& a) : m_ptr(new int(*a.m_ptr)) {   // 深拷贝构造函数
		cout << "copy construct" << endl;
	}

	MoveTest(MoveTest&& a) : m_ptr(a.m_ptr) {                  // 移动构造函数
												 //a.m_ptr = nullptr;      // 为了实验，这里没有把参数对象的指针指向 nullptr
		cout << "move construct" << endl;
	}

	~MoveTest() {
		cout << "destruct" << endl;
		delete m_ptr;   // 析构函数，释放堆内存的资源
	}

	int get_data() {
		return *m_ptr;
	}

	void set_data(int v) {
		*m_ptr = v;
	}
private:
	int* m_ptr;         // 成员指针变量
};