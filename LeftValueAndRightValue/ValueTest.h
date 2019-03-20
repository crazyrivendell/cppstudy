#pragma once

#include <iostream>
using namespace std;
class cs
{
public:
	cs(int i) : i_(i) { 
		cout << "cs(" << i << ") constructor!" << endl; 
	}
	~cs() { 
		cout << "cs destructor,i(" << i_ << ")" << endl; 
	}

	cs& operator=(const cs& other)
	{
		i_ = other.i_;
		cout << "cs operator=()" << endl;
		return *this;
	}

	int get_i() const { return i_; }
	void change(int i) { i_ = i; }

private:
	int i_;
};

cs get_cs()
{
	static int i = 0;  //static类型，初始化一次，后续值不消失
	return cs(i++);
}

