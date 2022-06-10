#pragma once
#include <pqxx/pqxx>
#include <boost/asio.hpp>

class IResCb
{
public:
	virtual void res_cb(std::shared_ptr<pqxx::result> ptrRes,std::string strError) = 0;
	virtual ~IResCb(){}
};

class PqxxHandle
{
public:
	PqxxHandle();
	~PqxxHandle();
	void Init(std::string_view strUrl,int iNums = std::thread::hardware_concurrency());
	void GetDevInfo(std::string_view strEui,std::shared_ptr<IResCb> ptrIResCb = nullptr);

private:
	static thread_local std::shared_ptr<pqxx::connection> ptrConnect;
	static thread_local std::shared_ptr<pqxx::work> ptrWork;
	std::string_view m_strUrl;

	boost::asio::io_context m_io;
	std::shared_ptr<boost::asio::io_service::work> m_ptrWork;
	std::vector<std::shared_ptr<std::thread>> m_vecThreads;
};