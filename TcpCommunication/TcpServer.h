#pragma once
#include <boost/asio.hpp> 
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include "SessionManager.h"

class TcpServer
{
public:
	TcpServer(std::string strIpAddr, unsigned short iport, std::shared_ptr<SessionManager> ptrSessionManager = nullptr);
	void run();
	void SetLogHandle(std::function<void(std::string, std::string)> fLogHandle);

private:
	void Accept();

private:
	boost::asio::io_service         m_io;
	boost::asio::ip::tcp::acceptor  m_acceptor;
	std::function<void(std::string, std::string)> m_fLogHandle;
	std::shared_ptr<SessionManager> m_ptrSessionManager;
};