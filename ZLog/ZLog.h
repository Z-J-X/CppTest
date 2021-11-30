#pragma once
#include<boost/noncopyable.hpp>
#include<boost/asio.hpp>
#include<fstream>

class ZLog :boost::noncopyable
{
private:
	ZLog();
	std::string fileName();
public:
	~ZLog();
	static ZLog& Instance;
	static ZLog& getInstance();
	bool writeLog(std::string str, std::string title);
private:
	boost::asio::io_context m_io;
	std::shared_ptr<boost::asio::io_service::work> ptr_work;
	std::shared_ptr<std::thread> ptr_thread;
	std::ofstream outfile;
	static std::string str_fileName;
};