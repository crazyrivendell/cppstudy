/*
shared_pointer study
*/

#include <iostream>
#include <memory>  //使用shared_ptr需要
#include <thread>
#include <chrono>
#include <mutex>

struct Base
{
	Base() { std::cout << "  Base::Base()\n"; }
	// 注意：此处非虚析构函数 OK
	~Base() { std::cout << "  Base::~Base()\n"; }
};

struct Derived : public Base
{
	Derived() { std::cout << "  Derived::Derived()\n"; }
	~Derived() { std::cout << "  Derived::~Derived()\n"; }
};

class Person
{
public:
	Person(int v) {
		value = v;
		std::cout << "Cons" << value << std::endl;
	}
	~Person() {
		std::cout << "Des" << value << std::endl;
	}

	int value;

};

void thr(std::shared_ptr<Base> p)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::shared_ptr<Base> lp = p; // 线程安全，虽然自增共享的 use_count
	{
		static std::mutex io_mutex;
		std::lock_guard<std::mutex> lk(io_mutex);
		std::cout << "local pointer in a thread:\n"
			<< "  lp.get() = " << lp.get()
			<< ", lp.use_count() = " << lp.use_count() << '\n';
	}
}

void shared_ptr_init()
{
	std::shared_ptr<Person> p1(new Person(1));// Person(1)的引用计数为1

	std::shared_ptr<Person> p2 = std::make_shared<Person>(2);

	p1.reset(new Person(3));// 首先生成新对象，然后引用计数减1，引用计数为0，故析构Person(1)
							// 最后将新对象的指针交给智能指针

	std::shared_ptr<Person> p3 = p1;//现在p1和p3同时指向Person(3)，Person(3)的引用计数为2

	p1.reset();//Person(3)的引用计数为1
	p3.reset();//Person(3)的引用计数为0，析构Person(3)
}

void shared_ptr_count()
{
	std::shared_ptr<Base> p = std::make_shared<Derived>();

	std::cout << "Created a shared Derived (as a pointer to Base)\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << '\n';
	std::thread t1(thr, p), t2(thr, p), t3(thr, p);
	p.reset(); // 从 main 释放所有权
	std::cout << "Shared ownership between 3 threads and released\n"
		<< "ownership from main:\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << '\n';
	t1.join(); t2.join(); t3.join();
	std::cout << "All threads completed, the last one deleted Derived\n";
}

int main()
{
	shared_ptr_init();
	shared_ptr_count();
}