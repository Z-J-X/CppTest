#include"SessionManager.h"
#include <iomanip>

SessionManager::SessionManager() : m_fLogHandle([](std::string, std::string) {}) {}

void SessionManager::Register(std::shared_ptr<Session> ptrSession)
{
	auto self = shared_from_this();
	ptrSession->SetLogHandle(m_fLogHandle);
	ptrSession->SetDeadline(5000);
	std::vector<char> vecHeartbeat = { 0x11,0x22,0x33,0x44 };
	ptrSession->SetHearbeat(5000, vecHeartbeat);
	ptrSession->SetConsumeHandle(std::bind(&SessionManager::Consume, self, std::placeholders::_1, std::placeholders::_2));
	
	auto ptrBuf = std::make_shared<std::vector<char>>();
	*ptrBuf = { 0x11,0x11,0x11,0x11 };
	ptrSession->Write(ptrBuf, [this, self](const boost::system::error_code& ec, std::shared_ptr<Message> ptrMsg) {
		if (ec)
			std::cout << ec.message() << std::endl;
		std::cout << "send ok " << ptrMsg->m_ptrPayload->size() << " bytes" << std::endl;
		});

	ptrSession->start();
}

void SessionManager::Consume(const boost::system::error_code& ec,std::shared_ptr<Message> ptrMessage)
{
	if (ec)
	{
		std::cout << ec.message() << std::endl;
		return;
	}
	std::cout <<"Session Id: "<< ptrMessage ->m_ptrSession.get() << " receive " << ptrMessage->m_ptrPayload->size() << " bytes: ";
	for (auto i : *(ptrMessage->m_ptrPayload))
		std::cout << std::setiosflags(std::ios::uppercase) << std::hex << std::setw(2) << std::setfill('0') << (i & 0xff) << " ";
	std::cout << std::endl;
}

void SessionManager::SetLogHandle(std::function<void(std::string, std::string)> fLogHandle)
{
	if (fLogHandle != nullptr)
		m_fLogHandle = fLogHandle;
}