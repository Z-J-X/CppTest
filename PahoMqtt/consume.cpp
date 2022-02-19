#if 1
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include <mqtt/client.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
const string SERVER_ADDRESS{ "192.168.10.144:1883" };



class SpendTime
{
public:
	SpendTime() :_curTimePoint(std::chrono::steady_clock::now())
	{
	}

	~SpendTime() {
		auto curTime = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(curTime - _curTimePoint);
		std::cout << "SpendTime = " << duration.count() << "ms" << std::endl;
	}

private:
	std::chrono::steady_clock::time_point _curTimePoint;
};



int main1()
{
	mqtt::client cli(SERVER_ADDRESS, "consume11");

	auto connOpts = mqtt::connect_options_builder()
		.keep_alive_interval(seconds(30))
		.automatic_reconnect(true)
		.clean_session(false)	
		.finalize();


	const vector<string> TOPICS{ "Test" };
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
		SpendTime STime;
		std::thread t1([&] {
			int i = 10000;
			while (i) {
				auto msg = cli.consume_message();

				if (msg) {
					i--;
				}
				else if (!cli.is_connected()) {
					cout << "Lost connection" << endl;
					while (!cli.is_connected()) {
						this_thread::sleep_for(milliseconds(250));
					}
					cout << "Re-established connection" << endl;
				}
			}
			});
		std::thread t2([&] {
			int i = 10000;
			while (i) {
				auto msg = cli.consume_message();

				if (msg) {
					i--;
				}
				else if (!cli.is_connected()) {
					cout << "Lost connection" << endl;
					while (!cli.is_connected()) {
						this_thread::sleep_for(milliseconds(250));
					}
					cout << "Re-established connection" << endl;
				}
			}
			});

		t1.join();
		t2.join();
		//t3.join();
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

#endif