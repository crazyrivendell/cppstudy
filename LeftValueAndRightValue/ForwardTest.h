#pragma once

#include <iostream>
using namespace std;

void processValue(int& a) { cout << "lvalue" << endl; }
void processValue(int&& a) { cout << "rvalue" << endl; }

template <typename T>
void forwardValue_fail(T&& val) {
	processValue(val);      // ��Ϊ val ������һ����ֵ
							// �������� val ����ֵ�������ͻ�����ֵ�������͵ı���
							// ��ֻ����� processValue(int& a)
}

template <typename T>
void forwardValue_success(T&& val){
	processValue(forward<T>(val));   // ���� forward ���ֶ��������ֵ����

									 // ����� forward<T>(val) �����Ϊ���������򶼴ﲻ������ת����Ŀ��
									 // auto v = forward<T>(val);
									 // processValue(v);

									 // auto&& v = forward<T>(val);
									 // processValue(v);
}