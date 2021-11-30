#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include <mqtt/client.h>
#include <json/json.h>

using namespace std;
using namespace std::chrono;
const string SERVER_ADDRESS{ "10.32.233.195:1889" };

Json::Value readFromString(string & rawJson)
{
	const auto rawJsonLength = static_cast<int>(rawJson.length());

	JSONCPP_STRING err;
	Json::Value root;

	Json::CharReaderBuilder builder;
	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root, &err)) //解析
	{
		std::cout << "error" << std::endl;
		return false;
	}

	return root;
}

string writeToString(Json::Value root)
{

	Json::StreamWriterBuilder builder;
	const std::string json_file = Json::writeString(builder, root);

	return json_file;
}


int run()
{
	mqtt::client cli(SERVER_ADDRESS, "consume");

	auto connOpts = mqtt::connect_options_builder()
		.keep_alive_interval(seconds(30))
		.automatic_reconnect(true)
		.clean_session(false)
		.finalize();
	

	const vector<string> TOPICS{ "KaifaMqttTestPubish" };
	const vector<int> QOS{ 1 };



	try {
		cout << "Connecting to the MQTT server..." << flush;
		mqtt::connect_response rsp = cli.connect(connOpts);
		cout << "OK\n" << endl;

		if (!rsp.is_session_present()) {
			std::cout << "Subscribing to topics..." << std::flush;
			cli.subscribe(TOPICS, QOS);
			std::cout << "OK" << std::endl;
		}
		else {
			cout << "Session already present. Skipping subscribe." << std::endl;
		}

		// Consume messages

		while (true) {
			auto msg = cli.consume_message();

			if (msg) {
				//cout << msg->get_topic() << ": " << msg->to_string() << endl;
				//string src = msg->to_string().c_str();
				string src = msg->to_string();
				Json::Value des = readFromString(src);
				std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::now();//stl库获取当前时间
				std::time_t newTime = std::chrono::system_clock::to_time_t(timePoint);//转换为旧式接口，单位:秒
				std::cout << newTime<<":" <<des["type"].asString() << std::endl;
				if (des["type"].asString() == "downlink_request")
				{
					string str_src = R"({"meta":{"network":"a653ee9da56a43b9ab308c3b2f06eb81","packet_hash":"1","application":"0000000000000000","device_addr":"1648938e","time":1634029914.95,"device":"0000000000000211","packet_id":"e17843a405b1603d73f88cd957ad5931","gateway":"80029cf7bd0d0000","history":true},"type":"downlink_response","params":{"pending":false,"confirmed":false,"counter_down":4,"port":20,"payload":"MTExMTEx"}})";
					Json::Value js_des = readFromString(str_src);
					js_des["meta"]["network"] = des["meta"]["network"];
					js_des["meta"]["packet_hash"] = des["meta"]["packet_hash"];
					js_des["meta"]["application"] = des["meta"]["application"];
					js_des["meta"]["device_addr"] = des["meta"]["device_addr"];
					js_des["meta"]["time"] = newTime;
					js_des["meta"]["packet_id"] = des["meta"]["packet_id"];
					js_des["meta"]["gateway"] = des["meta"]["gateway"];
					js_des["params"]["counter_down"] = des["params"]["counter_down"].asInt() + 1;
					string a = writeToString(js_des);
					cli.publish(mqtt::message("KaifaMqttTestSubscribe", a, 1, false));
				}
			}
			else if (!cli.is_connected()) {
				cout << "Lost connection" << endl;
				while (!cli.is_connected()) {
					static int i = 0;
					this_thread::sleep_for(seconds(1));
				}
				cout << "Re-established connection" << endl;
				cout << cli.get_client_id() << std::endl;
			}
		}

		// Disconnect

		cout << "\nDisconnecting from the MQTT server..." << flush;
		cli.disconnect();
		cout << "OK" << endl;
	}
	catch (const mqtt::exception& exc) {
		cerr << exc.what() << endl;
		return 1;
	}
	catch (exception& ec)
	{
		cerr << ec.what() << endl;
		return 1;
	}
}

int main()
{
	run();
}