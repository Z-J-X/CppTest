#if 0
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mqtt/async_client.h>

using namespace std;

const string SERVER_ADDRESS{ "tcp://10.32.233.80:1883" };
const string CLIENT_ID{ "paho_cpp_async_consume" };
const string TOPIC{ "Test" };

const int  QOS = 1;

/////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	mqtt::async_client cli(SERVER_ADDRESS, CLIENT_ID);

	auto connOpts = mqtt::connect_options_builder()
		.clean_session(true)
		.automatic_reconnect(true)
		.finalize();

	try {
		// Start consumer before connecting to make sure to not miss messages

		cli.start_consuming();//异步消费者必须执行这条语句，从而初始化消费队列

		// Connect to the server

		cout << "Connecting to the MQTT server..." << flush;
		auto tok = cli.connect(connOpts);

		// Getting the connect response will block waiting for the
		// connection to complete.
		auto rsp = tok->get_connect_response();

		// If there is no session present, then we need to subscribe, but if
		// there is a session, then the server remembers us and our
		// subscriptions.
		if (!rsp.is_session_present())
			cli.subscribe(TOPIC, QOS)->wait();

		cout << "OK" << endl;


		cout << "Waiting for messages on topic: '" << TOPIC << "'" << endl;

		while (true) {
			auto msg = cli.consume_message();
			if (msg)
			{
				cout << msg->get_topic() << ": " << msg->to_string() << endl;
			}
			else if (!cli.is_connected()) 
			{
				cout << "Lost connection" << endl;
				while (!cli.is_connected()) {
					this_thread::sleep_for(std::chrono::milliseconds(250));
				}
				//防止MQTT服务器未作持久化，重启后会话信息丢失导致重连没有订阅信息
				cli.subscribe(TOPIC, QOS);
				cout << "Re-established connection" << endl;
			}
			else
			{
				break;
			}
		}

		// If we're here, the client was almost certainly disconnected.
		// But we check, just to make sure.

		if (cli.is_connected()) {
			cout << "\nShutting down and disconnecting from the MQTT server..." << flush;
			cli.unsubscribe(TOPIC)->wait();
			cli.stop_consuming();
			cli.disconnect()->wait();
			cout << "OK" << endl;
		}
		else {
			cout << "\nClient was disconnected" << endl;
		}
	}
	catch (const mqtt::exception& exc) {
		cerr << "\n  " << exc << endl;
		return 1;
	}

	return 0;
}
#endif