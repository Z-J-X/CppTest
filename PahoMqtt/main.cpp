#if 1
#include <iostream>
#include <string>
#include <chrono>
#include <future>
#include <mqtt/async_client.h>

using namespace std;


class SpendTime
{
public:
	SpendTime() :_curTimePoint(std::chrono::steady_clock::now())
	{
	}

	~SpendTime() {
		auto curTime = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(curTime - _curTimePoint);
		std::cout << "SpendTime = " << duration.count() << "us" << std::endl;
	}

private:
	std::chrono::steady_clock::time_point _curTimePoint;
};

void run(string strAddress, string strCliId, string strTopic)
{
	const int QOS = 1;
	mqtt::binary payload;
	for (size_t i = 0; i < 1024; ++i)
		payload.push_back('a' + i % 26);

	auto msg = mqtt::make_message(strTopic, std::move(payload), QOS, false);
	mqtt::connect_options m_mqConnOpts = mqtt::connect_options_builder()
		.keep_alive_interval(std::chrono::seconds(60))
		.automatic_reconnect(true)
		.clean_session(true)
		.finalize();
	auto cli = std::make_shared<mqtt::async_client>(strAddress, strCliId);
	try {
		cli->connect(m_mqConnOpts)->wait();
		cout << "  ...OK" << endl;
		{
			SpendTime tt;
			mqtt::token_ptr tok;
			size_t i = 30000;
			int failNum = 0;
			while (true) {//i--
				try {
					std::this_thread::sleep_for(chrono::seconds(1));
					tok = cli->publish(msg);
					
				}
				catch (const mqtt::exception& exc) {
					std::cout << "Error:" << exc.get_return_code() << ":" << exc.what() << std::endl;
					if (exc.get_return_code() == -12)
					{
						i++;
						failNum++;
						std::this_thread::sleep_for(chrono::milliseconds(10));
					}
					else if (exc.get_return_code() == -3)
					{
						while (!cli->is_connected()) {
							std::this_thread::sleep_for(std::chrono::milliseconds(250));
						}
						std::cout << "Re-established connection" << std::endl;
					}
					
				}
			}
			std::cout << "num: " << failNum << endl;;
			tok->wait();

		}

		cout << "\nDisconnecting..." << endl;
		cli->disconnect()->wait();

		cout << "  ...OK" << endl;
	}
	catch (const mqtt::exception& exc) {
		cerr << exc << endl;
	}
}

int main(int argc, char* argv[])
{

	//std::thread T1(std::bind(run, "10.32.233.80:1883", "6Test1", "Test"));
	//std::thread T2(std::bind(run, "10.32.233.80:1883", "6Test2", "Test"));
	//std::thread T3(std::bind(run, "10.32.233.80:1883", "6Test3", "Test"));
	//std::thread T4(std::bind(run, "10.32.233.80:1883", "6Test4", "Test"));
	//std::thread T5(std::bind(run, "10.32.233.80:1883", "6Test5", "Test"));
	//std::thread T6(std::bind(run, "10.32.233.80:1883", "6Test6", "Test"));
	//std::thread T7(std::bind(run, "10.32.233.80:1883", "6Test7", "Test"));
	//std::thread T8(std::bind(run, "10.32.233.80:1883", "6Test8", "Test"));
	//std::thread T9(std::bind(run, "10.32.233.80:1883", "6Test9", "Test"));
	//T1.join();
	//T2.join();
	//T3.join();
	//T4.join();
	//T5.join();
	//T6.join();
	//T7.join();
	//T8.join();
	//T9.join();
	run("10.32.233.80:1883", "Test1", "Test");
	return 0;
}

#endif