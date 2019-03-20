#pragma once

#include <iostream>
using namespace std;

void processValue(int& a) { cout << "lvalue" << endl; }
void processValue(int&& a) { cout << "rvalue" << endl; }

template <typename T>
void forwardValue_fail(T&& val) {
	processValue(val);      // 因为 val 本身是一个左值
							// 所以无论 val 是左值引用类型还是右值引用类型的变量
							// 都只会调用 processValue(int& a)
}

template <typename T>
void forwardValue_success(T&& val){
	processValue(forward<T>(val));   // 利用 forward 保持对象的左右值特性

									 // 必须把 forward<T>(val) 打包作为参数，否则都达不到完美转发的目的
									 // auto v = forward<T>(val);
									 // processValue(v);

									 // auto&& v = forward<T>(val);
									 // processValue(v);
}