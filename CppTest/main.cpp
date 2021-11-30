#if 1
#include<iostream>
#include<tuple>
#include<map>
#include<chrono>
//int func(int a)
//{
//	return a;
//}
//int main()
//{
//	int a = 100;
//	int& b = func(a);
//}


int main()
{
	std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::now();//stl库获取当前时间
	 int a = std::chrono::system_clock::to_time_t(timePoint);
	 std::cout << a << std::endl;
	return 0;
}
#endif