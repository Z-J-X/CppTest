#include <boost/asio.hpp> 
#include <boost/asio/ip/udp.hpp>
#include <iostream>


int main2(int argc,char** argv)
{
    try
    {
        boost::asio::io_service m_io;
        auto localAddr = boost::asio::ip::address::from_string(argv[1]);
        auto clientAddr = boost::asio::ip::address::from_string(argv[2]);
        
        boost::asio::ip::udp::endpoint localEp(localAddr, 8888);
        boost::asio::ip::udp::endpoint clientEp(clientAddr, 4059);

        boost::asio::ip::udp::socket sock(m_io, localEp);

        sock.send_to(boost::asio::buffer(std::string(argv[3])), clientEp);
    }
    catch (std::exception& ec)
    {
        std::cout << ec.what() << std::endl;
    }
    

    return 0;
}