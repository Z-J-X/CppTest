#include"ZLog.h"
#include<iostream>
#include<chrono>
#include<iomanip>
#include<thread>

std::string ZLog::str_fileName = "NSAdpter";
ZLog& ZLog::Instance = getInstance();
ZLog& ZLog::getInstance()
{
	ZLog::str_fileName = str_fileName;
	static ZLog instance;
	return instance;
}

static std::string getTime()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds> tpNow =
		std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
	auto tmp = std::chrono::duration_cast<std::chrono::microseconds>(tpNow.time_since_epoch());
	time_t tt = std::chrono::system_clock::to_time_t(tpNow);//获取时间戳精确到秒
	time_t ttm = tmp.count();//获取时间戳精确到微秒

	tm now{ 0 };
	char res[64] = { 0 };
#if defined WIN32 || WIN64
	localtime_s(&now, &tt);
	sprintf_s(res, _countof(res), "%4d-%02d-%02d %02d:%02d:%02d.%03d", now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec, static_cast<int>(ttm % 1000000));
#else
	localtime_r(&tt, &now);
	sprintf(res, "%4d-%02d-%02d %02d:%02d:%02d.%03d", now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec, static_cast<int>(ttm % 1000000));
#endif
	return std::string(res);
}

ZLog::ZLog() :ptr_work(new boost::asio::io_service::work(m_io))
{
	this->outfile.open(str_fileName + ".log");
	ptr_thread = std::make_shared<std::thread>([&]() {
		m_io.run();
		});
}
ZLog::~ZLog()
{
	ptr_work.reset();
	this->ptr_thread->join();
	this->outfile.close();
}
std::string ZLog::fileName()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t nowTime = std::chrono::system_clock::to_time_t(now);

	struct tm cutTm = { 0 };
	std::stringstream ss;
#if defined WIN32 || WIN64
	localtime_s(&cutTm, &nowTime);
#else
	localtime_r(&nowTime, &cutTm);
#endif
	static int nu = 0;
	ss << std::put_time(&cutTm, "%Y%m%d%H%M%S");
	ss << "." << nu;
	nu++;

	std::string file_name = str_fileName + ss.str() + ".log";
	return file_name;
}

bool ZLog::writeLog(std::string str, std::string title)
{
	std::string now = getTime();
	str = now + " : [" + title + "]\n" + str + "\n";
	try
	{
		this->m_io.post([=]() {
			static int size = 0;
			this->outfile << str << std::endl;
			size += str.length();
			if (size > 1024 * 1024 * 20)
			{
				size = 0;
				outfile.close();
				std::rename(std::string(str_fileName + ".log").c_str(), fileName().c_str());
				this->outfile.open(str_fileName + ".log");
			}
			});
	}
	catch (const std::exception& ec)
	{
		std::cout << ec.what() << std::endl;
	}
	return true;
}
