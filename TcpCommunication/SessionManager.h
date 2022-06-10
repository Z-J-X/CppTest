#pragma once
#include<iostream>
#include<unordered_map>
#include"Session.h"

class SessionManager :public std::enable_shared_from_this<SessionManager>
{
public:
	SessionManager();
	void Register(std::shared_ptr<Session> ptrSession);
	void SetLogHandle(std::function<void(std::string, std::string)> fLogHandle);
	void Consume(const boost::system::error_code& ec,std::shared_ptr<Message> ptrMessage);

private:
	std::unordered_map<std::string, std::shared_ptr<Session>> m_mapSession;
	std::function<void(std::string, std::string)> m_fLogHandle;
};