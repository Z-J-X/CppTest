#if 0
#include<msgpack.hpp>
#include<iostream>
#include<fstream>
class Base
{
public:
	Base()
	{
		va1 = 1;
		str1 = "Base";
		va2 = 2.1;
	}
public:
	int va1;
	std::string str1;
	double va2;
	MSGPACK_DEFINE_MAP(va1, str1, va2);
};

class Friend
{
public:
	Friend()
	{
		ff = 100;
	}
	int ff;
	MSGPACK_DEFINE_MAP(ff);
};
class Son :public Base
{
public:
	Son()
	{
		va3 = 3;
		str2 = "Son";
		va4 = 4.1;
	}
public:
	int va3;
	std::string str2;
	double va4;
	Friend a;
	MSGPACK_DEFINE_MAP(va3, str2, va4, a, MSGPACK_BASE_MAP(Base));
};


int main()
{
	try
	{
		Son  son;
		msgpack::sbuffer sbuf;
		msgpack::pack(sbuf, son);

		msgpack::object_handle oh =
			msgpack::unpack(sbuf.data(), sbuf.size());
		std::cout << oh.get() << std::endl;

	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return 0;
}

#endif