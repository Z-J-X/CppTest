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

private:
	using log_handle = std::function<void(std::string, std::string)>;
	using msg_handle = std::function<void(const boost::system::error_code&, std::shared_ptr<Message>)>;

public:
	Session(boost::asio::ip::tcp::socket&& socket);
	void start();
	void stop();
	bool Write(std::shared_ptr<std::vector<char>> ptrBuffer, msg_handle handle);
	void SetDeadline(long long ms);
	void SetHearbeat(long long ms, std::vector<char> vecHearbeat);
	void SetLogHandle(log_handle fLogHandle);
	void SetConsumeHandle(msg_handle fMsgHandle);
	void SetCloseSocketCb(msg_handle fMsgHandle);

private:
	void Error(const boost::system::error_code& ec, std::string strMsg);
	void Write();
	void Read();
	void Read(const boost::system::error_code& ec, std::size_t bytes_transferred);
	void CheckTimeout();

private:
	long long						m_msDeadline;
	long long						m_msHearbeat;
	boost::asio::ip::tcp::socket	m_socket;
	boost::asio::steady_timer		m_timerDeadline;
	boost::asio::steady_timer		m_timerHearbeat;
	std::vector<char>				m_vecBuffer;
	std::vector<char>				m_vecHearbeat;
	log_handle						m_fLogHandle;
	msg_handle						m_fConsumeHandle;
	msg_handle						m_fClseSocketCb;
};