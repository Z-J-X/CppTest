
#include<iostream>
#include"thread_queue.h"
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

std::string_view strMsg1;
void func(std::string_view ss)
{
	std::string s = "dasd";
	std::string_view strMsg = s +"1234";
	strMsg1 = strMsg;
}

std::string_view PrintStringView()
{
	std::string s = "How are you..";

	std::string_view str_view = s;
	return str_view;
}

std::string GetTime()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> tpNow =
		std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
	time_t tt = std::chrono::system_clock::to_time_t(tpNow);//获取时间戳精确到秒

	tm now{ 0 };
	char res[24] = { 0 };
#if defined WIN32 || WIN64
	localtime_s(&now, &tt);
	sprintf_s(res, _countof(res), "%02d%02d%02d%02d%02d%02d", (now.tm_year + 1900)%100, now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);
#else
	localtime_r(&tt, &now);
	sprintf(res, "%02d%02d%02d%02d%02d%02d", (now.tm_year + 1900) % 100, now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);
#endif
	return std::string(res);
}

class A:public enable_shared_from_this<A>
{
public:
	std::function<void()> func()
	{
		auto self = shared_from_this();
		return [this, self]() {
			std::cout << a << std::endl;;
		};
	}
public:
	std::string a;
};

int main()
{
	std::function<void()> ff;
	{
		auto a = std::make_shared<A>();
		a->a = "sdaasdas";
		ff =  a->func();
	}

	ff();
	


}