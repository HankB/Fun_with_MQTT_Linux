/*
Simple example to publish to broker.

Work here will lean heavily on
https://github.com/HankB/MQTT_will/blob/main/C%2B%2B/MQTT_will.cpp
https://github.com/eclipse-paho/paho.mqtt.cpp/blob/master/examples/topic_publish.cpp

Build:
g++ -Wall -o publish publish.cpp -lpaho-mqttpp3 -lpaho-mqtt3as -lpthread
*/
#include <iostream>
#include <atomic>

#include "mqtt/async_client.h"

using namespace std;

namespace
{

	const string DFLT_SERVER_ADDRESS{"tcp://localhost:1883"};
	const string CLIENT_ID{"paho_cpp_async_publish"};
	const string TOPIC{"test"};
	const int QOS = 0;

	const char *PAYLOADS[] = {
		"Hello World!", "Hi there!", "Is anyone listening?", "Someone is always listening.",
		nullptr};

	const auto TIMEOUT = std::chrono::seconds(10);

}

int main(int argc, char *argv[])
{
	cout << "hello world" << endl;
	// A client that just publishes normally doesn't need a persistent
	// session or Client ID unless it's using persistence, then the local
	// library requires an ID to identify the persistence files.
	// HB: Note - no current plan to use persistence

	string address = (argc > 1) ? string(argv[1]) : DFLT_SERVER_ADDRESS,
		   clientID = (argc > 2) ? string(argv[2]) : CLIENT_ID;

	cout << "Initializing for server '" << address << "'..." << endl;
    mqtt::async_client client(address, "");

	try
	{
		cout << "\nConnecting..." << endl;
		client.connect()->wait();
		cout << "  ...OK" << endl;

		cout << "\nPublishing messages..." << endl;

		mqtt::topic top(client, "Cpp_test", QOS);
		mqtt::token_ptr tok;

		size_t i = 0;
		while (PAYLOADS[i])
		{
			tok = top.publish(PAYLOADS[i++]);
		}
		tok->wait(); // Just wait for the last one to complete.
		cout << "OK" << endl;

		// Disconnect
		cout << "\nDisconnecting..." << endl;
		client.disconnect()->wait();
		cout << "  ...OK" << endl;
	}
	catch (const mqtt::exception &exc)
	{
		cerr << exc << endl;
		return 1;
	}
	return 0;
}