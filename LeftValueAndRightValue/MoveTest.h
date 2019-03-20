#pragma once
#include <iostream>
using namespace std;

class MoveTest {
public:
	MoveTest() : m_ptr(new int(0)) {                    // new ���ڴ�
		cout << "construct" << endl;
	}

	MoveTest(const MoveTest& a) : m_ptr(new int(*a.m_ptr)) {   // ������캯��
		cout << "copy construct" << endl;
	}

	MoveTest(MoveTest&& a) : m_ptr(a.m_ptr) {                  // �ƶ����캯��
												 //a.m_ptr = nullptr;      // Ϊ��ʵ�飬����û�аѲ��������ָ��ָ�� nullptr
		cout << "move construct" << endl;
	}

	~MoveTest() {
		cout << "destruct" << endl;
		delete m_ptr;   // �����������ͷŶ��ڴ����Դ
	}

	int get_data() {
		return *m_ptr;
	}

	void set_data(int v) {
		*m_ptr = v;
	}
private:
	int* m_ptr;         // ��Աָ�����
};