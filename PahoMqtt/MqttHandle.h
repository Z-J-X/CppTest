#pragma once
#include<string>
#include<mqtt/async_client.h>

class MqttHandle
{
public:
	MqttHandle();
	~MqttHandle();
	void SetQos(int nQos);
	void SetSubTopics(std::vector<std::string>& vecTopics);
	void Init(std::string strAddress, std::string strClientID);
	mqtt::const_message_ptr MqttConsume(int milliseconds = -1);
	void MqttPublish(std::string strTopic, std::string strToShchData);

private:
	int m_nQos;
	std::shared_ptr<mqtt::async_client> m_ptrMqClient;
	std::vector<std::string> m_vecSubTopics;
};