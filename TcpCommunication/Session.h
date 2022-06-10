#pragma once
#include <boost/asio.hpp>

class Session;

struct Message
{
	std::shared_ptr<Session>		   m_ptrSession;
	std::shared_ptr<std::vector<char>> m_ptrPayload;
};

class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(boost::asio::ip::tcp::socket socket);
	void start();
	void stop();
	bool Write(std::shared_ptr<std::vector<char>> ptrBuffer, std::function<void(const boost::system::error_code&, std::shared_ptr<Message>)> handle);
	void SetDeadline(long long ms);
	void SetHearbeat(long long ms, std::vector<char> vecHearbeat);
	void SetLogHandle(std::function<void(std::string, std::string)> fLogHandle);
	void SetConsumeHandle(std::function<void(const boost::system::error_code&, std::shared_ptr<Message>)> fConsumeHandle);//后续改为模板

private:
	void Error(const boost::system::error_code& ec, std::string strMsg);
	void Write();
	void Read();
	void Read(const boost::system::error_code& ec, std::size_t bytes_transferred);
	void CheckTimeout();

private:
	boost::asio::ip::tcp::socket m_socket;
	boost::asio::steady_timer m_timerDeadline;
	boost::asio::steady_timer m_timerHearbeat;
	long long m_msDeadline;
	long long m_msHearbeat;
	std::vector<char> m_vecHearbeat;
	std::vector<char> m_buffer;
	std::function<void(std::string, std::string)>											m_fLogHandle;
	std::function<void(const boost::system::error_code&,std::shared_ptr<Message>)>			m_fConsumeHandle;
};