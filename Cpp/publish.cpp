/*
Simple example to publish to broker.

Work here will lean heavily on
https://github.com/eclipse-paho/paho.mqtt.cpp/blob/master/examples/topic_publish.cpp

Build:
g++ -Wall -o publish publish.cpp -lpaho-mqttpp3 -lpaho-mqtt3as -lpthread
*/
#include <iostream>
#include <atomic>
#include <unistd.h>

#include "mqtt/async_client.h"

using namespace std;

namespace
{

	const string DFLT_SERVER_ADDRESS{"tcp://localhost:1883"};
	const string CLIENT_ID{"paho_cpp_async_publish"};
	const int QOS = 0;

	const char *PAYLOADS[] = {
		"Hello World!", "Hi there!", "Is anyone listening?", "Someone is always listening.",
		nullptr};

	const auto TIMEOUT = std::chrono::seconds(10);

}

int publish_msg(const string &serverURI, const string &topic, const string &payload)
{
	cout << "Initializing for server '" << serverURI << "'..." << endl;
	static mqtt::async_client cli(serverURI, "");
	cout << "  ...OK" << endl;

	try
	{

		if (!cli.is_connected())
		{
			cout << "\nConnecting..." << endl;
			cli.connect()->wait();
			cout << "  ...OK2" << endl;
		}

		cout << "\nPublishing messages..." << endl;

		mqtt::topic top(cli, topic, QOS);
		mqtt::token_ptr tok;

		tok = top.publish(payload);
		tok->wait(); // Just wait for the last one to complete.
		cout << "OK" << endl;

		// Disconnect
		/*
		cout << "\nDisconnecting..." << endl;
		cli.disconnect()->wait();
		cout << "  ...OK3" << endl;
		*/
	}
	catch (const mqtt::exception &exc)
	{
		cerr << exc << endl;
		return 1;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	// A client that just publishes normally doesn't need a persistent
	// session or Client ID unless it's using persistence, then the local
	// library requires an ID to identify the persistence files.
	// HB: Note - no current plan to use persistence

	string address = (argc > 1) ? string(argv[1]) : DFLT_SERVER_ADDRESS,
		   clientID = (argc > 2) ? string(argv[2]) : CLIENT_ID;

	while (1)
	{
		size_t i = 0;
		while (PAYLOADS[i])
		{
			if(publish_msg(address, "my_topic", PAYLOADS[i++]))
			{
				cout << "unable to publish" << endl;
			}
			sleep(1);
		}
	}

	return 0;
}