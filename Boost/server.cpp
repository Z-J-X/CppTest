#include <boost/asio.hpp> 
#include <boost/asio/ip/udp.hpp>
#include <iostream>
#include <iomanip>

int main1(int argc,char** argv)
{
    try
    {
        boost::asio::io_service m_io;
        /*创建UDP的sock对象使用ipv4协议，端口8888*/
        auto addr = boost::asio::ip::address::from_string(argv[1]);
        boost::asio::ip::udp::endpoint ep(addr, atoi(argv[2]));
        boost::asio::ip::udp::socket sock(m_io, ep);
        for (;;)
        {
            char buf[128] = { 0 };//接收数据缓冲区
            boost::asio::ip::udp::endpoint cep;//用于保存客户端端点信息
            boost::system::error_code ec;
            size_t size = sock.receive_from(boost::asio::buffer(buf), cep, 0, ec);//阻塞等待，0是flags
            if (ec && ec != boost::asio::error::message_size)
            {
                throw std::system_error(ec);
            }
            buf[size] = '\0';
            std::cout << "Receive from : " << cep << std::endl;
            std::cout << "Plaintext : " << buf << std::endl;
            std::cout << "Hex : ";
            for (int i = 0; i < size; i++)
            {
                std::cout << std::setiosflags(std::ios::uppercase) << std::hex << std::setw(8) << std::setfill('0') << buf[i]<<" ";
            }
            std::cout << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}