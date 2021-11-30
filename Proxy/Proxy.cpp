#include "Proxy.h"
#include<iostream>
#include <iomanip>
Proxy::Proxy(int lport, std::string fepIp, int fepPort):
	m_acceptor(m_io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), lport)),
	m_msock(new boost::asio::ip::tcp::socket(m_io)), 	
	m_fsock(new boost::asio::ip::tcp::socket(m_io)),
	m_ep(boost::asio::ip::address::from_string(fepIp), fepPort),
	m_fepBuf(1024 * 4, 0),
	m_meterBuf(1024 * 4, 0)
{
	boost::asio::io_service::work work(m_io);
	/*Òì²½¼àÌý*/
	m_acceptor.async_accept(*m_msock, boost::bind(&Proxy::accept_handler, this, boost::asio::placeholders::error));
	m_io.run();
}

void Proxy::accept_handler(const boost::system::error_code& ec)
{
	if (ec)
	{
		std::cout << ec << std::endl;
		return;
	}
	
	m_fsock->async_connect(m_ep, boost::bind(&Proxy::conn_handler, this, boost::asio::placeholders::error));
	m_msock->async_read_some(boost::asio::buffer(m_meterBuf), boost::bind(&Proxy::read_handler_meter, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}
//fep
void Proxy::conn_handler(const boost::system::error_code& ec)
{
	if (ec)
	{
		std::cout << ec.message() << std::endl;
		return;
	}
	m_fsock->async_read_some(boost::asio::buffer(m_fepBuf), boost::bind(&Proxy::read_handler_fep, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}
void Proxy::read_handler_fep(const boost::system::error_code& ec, std::size_t n)
{
	if (ec )
	{
		std::cout << ec.message() << std::endl;
		return;
	}
	std::cout << "read from fep "  <<n << " bytes" << std::endl;
	for (int i = 0; i < n; i++)
	{
		int tmp = m_fepBuf[i]&0xff;
		std::cout << std::setiosflags(std::ios::uppercase) << std::hex << std::setw(2) << std::setfill('0') << tmp;
		std::cout << " ";
	}
	std::cout << std::endl;
	
	m_msock->async_write_some(boost::asio::buffer(m_fepBuf,n), boost::bind(&Proxy::write_handler_meter, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	
}

void Proxy::write_handler_meter(const boost::system::error_code& ec, std::size_t n)
{
	if (ec)
	{
		std::cout << ec.value() << std::endl;
		return;
	}
	
	m_fsock->async_read_some(boost::asio::buffer(m_fepBuf), boost::bind(&Proxy::read_handler_fep, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	
}


//meter
void Proxy::read_handler_meter(const boost::system::error_code& ec, std::size_t n)
{
	if (ec)
	{
		std::cout << ec.message() << std::endl;
		return;
	}
	std::cout << "read from meter " <<  n << " bytes" << std::endl;
	for (int i = 0; i < n; i++)
	{
		int tmp = m_meterBuf[i] & 0xff;
		std::cout << std::setiosflags(std::ios::uppercase) << std::hex << std::setw(2) << std::setfill('0') << tmp;
		std::cout << " ";
	}
	std::cout << std::endl;
	m_fsock->async_write_some(boost::asio::buffer(m_meterBuf,n), boost::bind(&Proxy::write_handler_fep, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}
void Proxy::write_handler_fep(const boost::system::error_code& ec, std::size_t n)
{
	if (ec)
	{
		std::cout << ec.value() << std::endl;
		return;
	}
	//m_meterBuf.clear();
	m_msock->async_read_some(boost::asio::buffer(m_meterBuf), boost::bind(&Proxy::read_handler_meter, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}