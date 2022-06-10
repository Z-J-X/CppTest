#include"Session.h"
#include<iostream>
#include<sstream>

using namespace std::placeholders;


Session::Session(boost::asio::ip::tcp::socket socket):m_socket(std::move(socket)),m_buffer(1024), m_vecHearbeat(0), m_timerDeadline(m_socket.get_executor()), m_timerHearbeat(m_socket.get_executor()), m_msDeadline(0), m_msHearbeat(0)
{
	
}

void Session::Error(const boost::system::error_code& ec, std::string strMsg)
{
	m_fLogHandle(strMsg + ":" + ec.message(), "Error");
	stop();
}

void Session::start()
{
	if (m_msDeadline) //�Ƿ�ʱ
	{
		m_timerDeadline.expires_after(std::chrono::milliseconds::max());// m_timerDeadline init
		m_timerDeadline.async_wait(std::bind(&Session::CheckTimeout, shared_from_this()));
	}

	if(m_msHearbeat) // �Ƿ�������
		Write();

	Read();
}

void Session::stop()
{
	if (m_socket.is_open())
		m_socket.close();

	m_timerDeadline.cancel();
	m_timerHearbeat.cancel();
}

void Session::SetDeadline(long long ms)
{
	if (ms > 0)
		m_msDeadline = ms;
}

void Session::SetHearbeat(long long ms, std::vector<char> vecHearbeat)
{
	if (ms > 0 && !vecHearbeat.empty())
	{
		m_msHearbeat = ms;
		m_vecHearbeat = vecHearbeat;
	}
}

void Session::SetLogHandle(std::function<void(std::string, std::string)> fLogHandle)
{
	m_fLogHandle = fLogHandle;
}

void Session::SetConsumeHandle(std::function<void(const boost::system::error_code&, std::shared_ptr<Message>)> fConsumeHandle)
{
	m_fConsumeHandle = fConsumeHandle;
}

void Session::Read()
{
	if(m_msDeadline) //�Ƿ�ʱ
		m_timerDeadline.expires_after(std::chrono::milliseconds(m_msDeadline));
	m_socket.async_read_some(boost::asio::buffer(m_buffer), std::bind((void(Session::*)(const boost::system::error_code & ec, std::size_t bytes_transferred)) & Session::Read, shared_from_this(), _1, _2));
}

void Session::Read(const boost::system::error_code& ec, std::size_t bytes_transferred)
{	
	// do something or callback
	if (m_fConsumeHandle != nullptr)
	{
		auto ptrMsg = std::make_shared<Message>();
		ptrMsg->m_ptrSession = shared_from_this();
		ptrMsg->m_ptrPayload = std::make_shared<std::vector<char>>(m_buffer.begin(), m_buffer.begin() + bytes_transferred);
		m_fConsumeHandle(ec,ptrMsg);
	}
	if (ec)
		return stop();
	Read();
}

void Session::Write()
{
	if (!m_socket.is_open())
		return;

	auto self = shared_from_this();
	boost::asio::async_write(m_socket, boost::asio::buffer(m_vecHearbeat),
		[this, self](const boost::system::error_code& error, std::size_t n) {
			if (error)
				return Error(error,"Write heartbeat");

			m_timerHearbeat.expires_after(std::chrono::milliseconds(m_msHearbeat));
			m_timerHearbeat.async_wait(std::bind((void(Session::*)()) & Session::Write, self));
		});
}

bool Session::Write(std::shared_ptr<std::vector<char>> ptrBuffer, std::function<void(const boost::system::error_code&, std::shared_ptr<Message>)> handle)
{
	if (!m_socket.is_open())
		return false;

	if (ptrBuffer == nullptr)
		return false;

	auto self = shared_from_this();
	boost::asio::async_write(m_socket, boost::asio::buffer(*ptrBuffer), [this, self,ptrBuffer, handle](const boost::system::error_code& ec, std::size_t n) {
		auto ptrMsg = std::make_shared<Message>();
		ptrMsg->m_ptrSession = self;
		ptrMsg->m_ptrPayload = ptrBuffer;
		handle(ec, ptrMsg);
		if (ec)
			stop();
		});
	return true;
}

void Session::CheckTimeout()
{
	if (!m_socket.is_open())
		return;

	if (m_timerDeadline.expiry() <= boost::asio::steady_timer::clock_type::now())
	{
		m_socket.close();
		return;
	}

	m_timerDeadline.async_wait(std::bind(&Session::CheckTimeout, shared_from_this()));
}