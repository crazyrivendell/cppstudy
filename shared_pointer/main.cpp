/*
shared_pointer study
*/

#include <iostream>
#include <memory>  //ʹ��shared_ptr��Ҫ
#include <thread>
#include <chrono>
#include <mutex>

struct Base
{
	Base() { std::cout << "  Base::Base()\n"; }
	// ע�⣺�˴������������� OK
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
	std::shared_ptr<Base> lp = p; // �̰߳�ȫ����Ȼ��������� use_count
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
	std::shared_ptr<Person> p1(new Person(1));// Person(1)�����ü���Ϊ1

	std::shared_ptr<Person> p2 = std::make_shared<Person>(2);

	p1.reset(new Person(3));// ���������¶���Ȼ�����ü�����1�����ü���Ϊ0��������Person(1)
							// ����¶����ָ�뽻������ָ��

	std::shared_ptr<Person> p3 = p1;//����p1��p3ͬʱָ��Person(3)��Person(3)�����ü���Ϊ2

	p1.reset();//Person(3)�����ü���Ϊ1
	p3.reset();//Person(3)�����ü���Ϊ0������Person(3)
}

void shared_ptr_count()
{
	std::shared_ptr<Base> p = std::make_shared<Derived>();

	std::cout << "Created a shared Derived (as a pointer to Base)\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << '\n';
	std::thread t1(thr, p), t2(thr, p), t3(thr, p);
	p.reset(); // �� main �ͷ�����Ȩ
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