#pragma warning (disable:4996)
#include <boost/asio.hpp> 
#include <boost/asio/ip/udp.hpp>
#include <iostream>
#include <iomanip>


int main(int argc, char** argv)
{
    try
    {
        if (argc == 3)
        {
            boost::asio::io_service m_io;
            /*创建UDP的sock对象使用ipv4协议，端口8888*/
            auto addr = boost::asio::ip::address::from_string(argv[1]);
            boost::asio::ip::udp::endpoint ep(addr, atoi(argv[2]));
            boost::asio::ip::udp::socket sock(m_io, ep);
            for (;;)
            {
                char buf[1500] = { 0 };//接收数据缓冲区
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
                    unsigned int data = buf[i] &0xff;
                    std::cout << std::setiosflags(std::ios::uppercase) << std::hex << std::setw(2) << std::setfill('0') << data << " ";
                }
                std::cout << std::endl;
            }
        }
        else if (argc >= 6)
        {
            boost::asio::io_service m_io;
            auto localAddr = boost::asio::ip::address::from_string(argv[1]);
            auto clientAddr = boost::asio::ip::address::from_string(argv[3]);

            boost::asio::ip::udp::endpoint localEp(localAddr, atoi(argv[2]));
            boost::asio::ip::udp::endpoint clientEp(clientAddr, atoi(argv[4]));

            boost::asio::ip::udp::socket sock(m_io, localEp);
            if (argc == 6)
            {
                sock.send_to(boost::asio::buffer(std::string(argv[5])), clientEp);
            }
            else if (argc > 6)
            {
                std::vector<unsigned char> data;
                for (int i = 5; i < argc; i++)
                {
                    unsigned int tmp = 0;
                    if (sscanf(argv[i], "%x", &tmp) != 1)
                    {
                        std::logic_error ec("To hex error!");
                        throw ec;
                    }
                    tmp = tmp & 0xff;
                    data.push_back(tmp);
                }
                sock.send_to(boost::asio::buffer(data), clientEp);
            }
        }
        else
        {
            std::cout << "Parameter error:\n";
            std::cout << "Server example : ./udp localhost port\n";
            std::cout << "Client example (String) : ./udp localhost srcPort desHost desPort \"hello world\"\n";
            std::cout << "Client example (Hex) : ./udp localhost srcPort desHost desPort 00 01 55 ff\n";
        }
    }
    catch (std::exception& e)
    {
        std::cout <<"Error:" << e.what() << std::endl;
        return -1;
    }
    return 0;
}