#if 0
#include <boost/asio.hpp> 
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <thread>

int main()
{
	try
	{
		boost::asio::io_service io; 								 //asio程序必须的io_service对象
		//boost::asio::ip::address addr;
		//addr = addr.from_string("0.0.0.0");
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), 8888); //boost::asio::ip::tcp::v4()默认为0.0.0.0
		boost::asio::ip::tcp::acceptor acceptor(io, ep);
		std::cout << acceptor.local_endpoint().address() << std::endl; 		 //绑定的本地地址

		while (1)
		{
			try
			{
				boost::asio::ip::tcp::socket sock(io);
				acceptor.accept(sock); 									 //阻塞等待socket连接
				std::cout << "client--";
				std::cout << sock.remote_endpoint().address() << ":" << sock.remote_endpoint().port() << std::endl;//clien通信地址

				while (!sock.available())
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}

				for (int i = 0; i < 3; i++)
				{
					std::vector<char> reBuf(1024);
					char sendBuf[] = { 0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x25,0xC9,0x23,0x30,0x00,0x00,0x0B,0x72,0x22,0x5F,0xCE,0x90,0xB3,0x25,0x8F,0x25,0xE9,0xDF,0x27,0x6D,0xED,0x0D,0x9B,0xFB,0x73,0xF0,0x2C,0xDF,0xB7,0x8E,0x07,0x14,0x0F,0x5F,0xF4,0xD7,0xEA,0x34 };
					
					if (sock.available()) 
					{
						std::cout << "receive size: " << sock.receive(boost::asio::buffer(reBuf)) << std::endl;
					}
					
					//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					std::cout << "send size: " << sock.send(boost::asio::buffer(sendBuf, 45)) << std::endl;
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			}
			catch (std::exception& e) 										 //捕获异常
			{
				std::cout << e.what() << std::endl;
			}
		}
	}
	catch (std::exception& e) 										 //捕获异常
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
#endif