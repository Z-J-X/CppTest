#pragma once
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/asio.hpp> 
#include <boost/asio/ip/tcp.hpp>
#include <thread>


class Proxy
{
public:
	Proxy(int lport,std::string fepIp,int fepPort);
public:
	void accept_handler(const boost::system::error_code& ec);
	void conn_handler(const boost::system::error_code& ec);
	void read_handler_fep(const boost::system::error_code& ec, std::size_t n);
	void write_handler_meter(const boost::system::error_code& ec, std::size_t n);
	void read_handler_meter(const boost::system::error_code& ec, std::size_t n);
	void write_handler_fep(const boost::system::error_code& ec, std::size_t n);

private:
	boost::asio::io_service							m_io;
	boost::asio::io_service							m_io2;
	boost::asio::ip::tcp::acceptor					m_acceptor;
	boost::shared_ptr<boost::asio::ip::tcp::socket> m_msock;

	std::vector<unsigned char>						m_fepBuf;
	std::vector<unsigned char>						m_meterBuf;
	boost::asio::ip::tcp::endpoint					m_ep;
	boost::shared_ptr<boost::asio::ip::tcp::socket> m_fsock;
};