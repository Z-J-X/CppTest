#include<thread>
#include"MqttHandle.h"


MqttHandle::MqttHandle():m_nQos (1) {}

MqttHandle::~MqttHandle(){};

void MqttHandle::SetQos(int nQos)
{
	m_nQos = nQos;
}

void MqttHandle::SetSubTopics(std::vector<std::string>& vecTopics)
{
	m_vecSubTopics = vecTopics;
}

void MqttHandle::Init(std::string strAddress, std::string strClientID)
{
	mqtt::connect_options m_mqConnOpts = mqtt::connect_options_builder()
		.keep_alive_interval(std::chrono::seconds(60))
		.automatic_reconnect(true)
		.clean_session(true)
		.finalize();
	m_ptrMqClient = std::make_shared<mqtt::async_client>(strAddress, strClientID);

	std::vector<int> vecSubQos;
	for (int i = 0; i < m_vecSubTopics.size(); i++)
	{
		vecSubQos.push_back(m_nQos);
	}


	std::cout << "============================================" << std::endl;
	std::cout << "Connecting to the MQTT server " + strAddress + " ... ";
	mqtt::token_ptr tok = m_ptrMqClient->connect(m_mqConnOpts);
	mqtt::connect_response rsp = tok->get_connect_response();
	// Getting the connect response will block waiting for the
	// connection to complete.
	
	std::cout << "OK" << std::endl;
	if (!rsp.is_session_present())
	{
		std::cout << "Subscribing to topics ... ";
		m_ptrMqClient->subscribe(mqtt::string_collection::create(m_vecSubTopics), vecSubQos);
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "Session already present. Skipping subscribe." << std::endl;
	}
	std::cout << "============================================\n" << std::endl;
}

mqtt::const_message_ptr MqttHandle::MqttConsume(int milliseconds)
{
	mqtt::const_message_ptr retData;
	if (milliseconds < 0)
	{
		retData = m_ptrMqClient->consume_message();
	}
	else if (milliseconds == 0)
	{
		m_ptrMqClient->try_consume_message(&retData);
	}
	else
	{
		m_ptrMqClient->try_consume_message_for(&retData,std::chrono::milliseconds(milliseconds));
	}
	return retData;
}


void MqttHandle::MqttPublish(std::string strTopic, std::string strToShchData)
{
	while (true)
	{
		try {
			m_ptrMqClient->publish(mqtt::make_message(strTopic, strToShchData, m_nQos, false));
			break;
		}
		catch (const mqtt::exception& exc) {

			if (exc.get_return_code() == -12)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}
	}
}