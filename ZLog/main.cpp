#include"ZLog.h"
#include<thread>
#include<iostream>
 int q = 1;
void func()
{
	while (q)
	{
		ZLog::Instance.writeLog("helloworld","INFO");
	}
}

int main()
{
	try
	{
		std::thread T1(func);

		std::cin >> q;
		T1.join();
	}
	catch (const std::exception& ec)
	{
		std::cout << ec.what() << std::endl;
	}

}