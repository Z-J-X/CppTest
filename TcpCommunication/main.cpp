#include"TcpServer.h"


int main()
{
	try
	{
		auto ptrSessionManager = std::make_shared<SessionManager>();
		auto ptrSer = std::make_shared<TcpServer>("0.0.0.0", 8888, ptrSessionManager);

		ptrSer->SetLogHandle([](std::string strInfo, std::string strTitle) {
			std::cout << "[" + strTitle + "]: " + strInfo << std::endl;
			});
		ptrSer->run();
	}
	catch (std::exception& ec)
	{
		std::cout << ec.what() << std::endl;
	}
	return 0;
}