#if 0
#include <iostream>
#include <string>
#include <mqtt/client.h>

using namespace std;
using namespace std::chrono;

const string SERVER_ADDRESS{ "ws://10.32.233.80:8080" };
const string CLIENT_ID{ "paho_cpp_sync_consume" };
const string TOPIC{ "Test" };
const int QOS = 1;
/////////////////////////////////////////////////////////////////////////////

const char* PAYLOADS[] = {
	"Hello World!",
	"Hi there!",
	"Is anyone listening?",
	"Someone is always listening.",
	nullptr
};

int main(int argc, char* argv[])
{
	try {
		mqtt::client cli(SERVER_ADDRESS, CLIENT_ID);

		auto connOpts = mqtt::connect_options_builder()
			.clean_session(false)
			.finalize();


		cout << "Connecting to the MQTT server..." << flush;
		mqtt::connect_response rsp = cli.connect(connOpts);
		cout << "OK\n" << endl;

		int i = 0;

		while (PAYLOADS[i]) {

			cli.publish(mqtt::message(TOPIC, std::string(PAYLOADS[i]), QOS, false));
			i++;
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

	return 0;
}




#endif