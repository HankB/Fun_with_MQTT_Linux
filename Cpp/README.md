# Paho MQTT client

Provide a simple client to publish to an MQTT broker. Previous example in <https://github.com/HankB/MQTT_will/tree/main/C%2B%2B> is rather involved. This example will not include the last will and testament functionality.

## 2025-12-15 requirements

```text
apt install libpaho-mqtt-dev libpaho-mqtt1.3 libpaho-mqttpp-dev libpaho-mqttpp3-1
```

## 2025-12-15 Status

The example from <https://github.com/eclipse-paho/paho.mqtt.cpp/blob/master/examples/topic_publish.cpp> has been morphed:

* callable publish function.
* loops and publishes indefinitely
* attempts to restore connection if dropped.

Not tested if a message is published at after a long delay, will a timed out connection be restored and the message published?

At present the code will not use a different broker URI if the connection is dropped despite that the URI is passed in to every publish call. This could be fixed using `client::connect( connect_options  	options	)` vs. `client::connect()` to connect.

This effort is complete at this time.

## Build

```text
g++ -Wall -o publish publish.cpp -lpaho-mqttpp3 -lpaho-mqtt3as -lpthread
```
