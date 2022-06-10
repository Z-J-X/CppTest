#include <boost/asio.hpp> 
#include <boost/asio/ip/tcp.hpp>
#include <iostream>

int main11(int argc, char** argv)
{
    try
    {
        boost::asio::io_service io;
        boost::asio::ip::address addr;
        addr = addr.from_string("10.32.155.5");
        boost::asio::ip::tcp::endpoint ep(addr, 8888);
       
        for (int i = 0; i < std::stoi(argv[1]); i++)
        {
            auto ptrSock = new boost::asio::ip::tcp::socket(io);

            boost::system::error_code ec;
            ptrSock->connect(ep, ec);
            if (ec)
                std::cout << ec.message() << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "error:" << e.what() << std::endl;
    }

    return 0;
}
