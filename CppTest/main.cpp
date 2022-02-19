#pragma warning (disable:4996)
#include <iostream>
#include <string>
#include <fstream>
#include"base64.h"
using namespace std;

template<class T>
class Stream
{
public:
	Stream(T& t):handle(t)
	{
		 
	};
	template<class D>
	T& operator <<( D&& str)
	{
		handle << str;
		return handle;
	}
private:
	T& handle;
};

int main()
{
	
	//Stream<ostream> Test(std::cout);
	//Test << "hello";
	//Test << 10 << endl;
	//string str = "dasdas";
	//Test << str << endl;

	//std::cout << "---------------------------------" << endl;
	//fstream File;
	//File.open("file.txt", std::ios::app);
	//Stream<fstream> sTest(File);
	//sTest << "dadadsa" << endl;
	//sTest << "ok" << endl << "dasdasdasd" << endl;

	const std::string str = base64_decode("AAAACcqLyPg=");
	std::cout << str.size()<< std::endl;
	char buf[100] = {0};
	for (int i = 0; i < str.size(); i++)
	{
		sprintf_s(buf + 2 * i, 3,"%02X", str[i]&0xff);
	}
	std::string ret1(buf);
	std::cout << ret1<<ret1.length() << std::endl;

	std::string ss = "application/1/device/+/command/down";
	std::cout << ss.size() << ss.length() << std::endl;
	if (ss.rfind("down") != std::string::npos)
	{
		std::cout << "ok" << std::endl;
	}
	std::string str2;
	std::cout << str2.size() << str2.length() << std::endl;;

	char  ttt[] = "2022-02-08T02:54:22.179771394Z";
	char retv[13] = { 0 };
#if defined WIN32 || WIN64
	sscanf_s(ttt, "20%2s-%2s-%2sT%2s:%2s:%2s", retv,13, retv + 2,3, retv + 4, 3, retv + 6, 3, retv + 8, 3, retv + 10, 3);
#else
	sscanf(ttt, "20%2s-%2s-%2sT%2s:%2s:%2s", retv, retv + 2, retv + 4, retv + 6, retv + 8, retv + 10);
#endif
	
	std::string asdas(retv);
	std::cout << asdas.size() << std::endl;

	std::cout << "---------------------------------" << std::endl;
	int* a = new int(1);
	std::shared_ptr<int> ptr;
	if(ptr == nullptr)
	ptr = std::shared_ptr<int>(a);
	std::cout << *ptr << std::endl;

	int i = 0;
	do
	{
		i++;
		if (i == 1)
			continue;
	} while (0);
	std::cout << i << std::endl;
	throw runtime_error("das");
}
