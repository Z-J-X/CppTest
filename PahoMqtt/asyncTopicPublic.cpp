#if 0

#include <iostream>
#include <string>
#include <chrono>
#include <mqtt/async_client.h>

using namespace std;

const string DFLT_SERVER_ADDRESS{ "tcp://10.32.233.80:1883" };

const string TOPIC{ "Test" };
const int QOS = 1;

const char* PAYLOADS[] = {
	"Hello World!",
	"Hi there!",
	"Is anyone listening?",
	"Someone is always listening.",
	nullptr
};

const auto TIMEOUT = std::chrono::seconds(10);

/////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	string address = DFLT_SERVER_ADDRESS;

	mqtt::async_client cli(address, "");


	try {
		cout << "\nConnecting..." << endl;
		cli.connect()->wait();
		cout << "  ...OK" << endl;

		cout << "\nPublishing messages..." << endl;

		mqtt::topic top(cli, "Test", QOS);
		
		mqtt::token_ptr tok;

		size_t i = 0;
		while (PAYLOADS[i]) {
			tok = top.publish(PAYLOADS[i++]);
		}
		tok->wait();	// Just wait for the last one to complete.
		cout << "OK" << endl;

		// Disconnect
		cout << "\nDisconnecting..." << endl;
		cli.disconnect()->wait();
		cout << "  ...OK" << endl;
	}
	catch (const mqtt::exception& exc) {
		cerr << exc << endl;
		return 1;
	}

	return 0;
}


#endif