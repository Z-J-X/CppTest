#include <boost/asio.hpp> 
#include <boost/asio/ip/udp.hpp>
#include <iostream>
#include <iomanip>

int main1(int argc,char** argv)
{
    try
    {
        boost::asio::io_service m_io;
        /*����UDP��sock����ʹ��ipv4Э�飬�˿�8888*/
        auto addr = boost::asio::ip::address::from_string(argv[1]);
        boost::asio::ip::udp::endpoint ep(addr, atoi(argv[2]));
        boost::asio::ip::udp::socket sock(m_io, ep);
        for (;;)
        {
            char buf[128] = { 0 };//�������ݻ�����
            boost::asio::ip::udp::endpoint cep;//���ڱ���ͻ��˶˵���Ϣ
            boost::system::error_code ec;
            size_t size = sock.receive_from(boost::asio::buffer(buf), cep, 0, ec);//�����ȴ���0��flags
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