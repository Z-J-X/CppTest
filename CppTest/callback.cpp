#if 0
#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

typedef std::function<void(int, int)> Fun;

class B {
private:
	Fun func;
public:
	void set_func(Fun f)
	{
		func = f;
	}
public:
	void call(int a)
	{
		func(a, 2);
	}
};

class Test :public std::enable_shared_from_this<Test>
{
private:
	int x;
private:
	void callback(int a, int b)
	{
		cout << a << "+" << b << "=" << a + b << endl;
		cout << x << endl;
	}
public:
	void set_x(int x)
	{
		this->x = x;
	}
public:
	void bind()
	{
		Fun fun = std::bind(&Test::callback, shared_from_this(), _1, _2);
		B b;
		b.set_func(fun);
		b.call(1);
	}

};

int main()
{
	std::shared_ptr<Test>test(new Test) ;
	test->set_x(100);
	test->bind();
	return 0;
}

#endif