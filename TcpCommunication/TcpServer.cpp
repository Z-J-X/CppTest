#include"TcpServer.h"
#include"Session.h"

TcpServer::TcpServer(std::string strAddr, unsigned short iport, std::shared_ptr<SessionManager> ptrSessionManager) :m_acceptor(m_io, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(strAddr), iport)), m_fLogHandle([](std::string, std::string) {})
{
	m_ptrSessionManager = ptrSessionManager;
}

void TcpServer::run()
{
	Accept();
	m_io.run();
}

void TcpServer::SetLogHandle(std::function<void(std::string, std::string)> fLogHandle)
{
	if (fLogHandle != nullptr)
		m_fLogHandle = fLogHandle;
}

void TcpServer::Accept()
{
	/*Òì²½¼àÌý*/
	m_acceptor.async_accept(m_io, [this](const boost::system::error_code& ec, boost::asio::ip::tcp::socket socket) {
		if (ec)
		{
			m_fLogHandle("accept:" + ec.message(), "Error");
			return;
		}
		std::stringstream Info;

		Info << socket.remote_endpoint() << ", connected.";
		m_fLogHandle(Info.str(), "Info");

		/*auto ptrSession = std::make_shared<Session>(std::move(socket));
		ptrSession->SetLogHandle(m_fLogHandle);
		ptrSession->SetDeadline(5000);
		ptrSession->SetHearbeat(5000);
		ptrSession->start();*/

		if (m_ptrSessionManager != nullptr)
			m_ptrSessionManager->Register(std::make_shared<Session>(std::move(socket)));

		Accept();
		});
}
