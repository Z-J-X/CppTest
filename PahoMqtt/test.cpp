#if 0
#include"MqttHandle.h"

int main()
{
	mqtt::const_message_ptr retData = nullptr;
	if (retData == nullptr)
	{
		std::cout << "aa" << std::endl;
	}
	auto data = mqtt::make_message("a", "a", 1, false);

	std::string str = "";
	if(str.empty())
		std::cout << str.size() << " " << str.length();
	
}
#endif