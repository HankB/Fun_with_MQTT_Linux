# Fun_with_MQTT_Linux

Explore MQTT publish and subscribe on Linux.

## 2025-12-15 Scope

This is a continuation of work started in <https://github.com/HankB/MQTT_publish_C>. I felt the title did not accurately describe the intended expansion of the scope. Rather than renaming that repo I archived it and may copy some of the code there here.

The present desire is to get working publish using C++ on Linux. I also work with microcontrollers such as the ESP family but will not include that here. I also plan to explore retaining the connection vs. opening a connection for each message as I have run into iussues when the latter is not handled properly.

At some point I may wish to code stuff like this in Rust or Go.

## 2025-12-15 Motivation

I will be recoding some applications that run on a Raspberry Pi and iterface with GPIO. The library I'm using has seem a major revision and it is easier to code using C++, necessitating the need (desire?) to code the MQTT publish stuff in C++ as well. (See <https://github.com/HankB/GPIOD_Debian_Raspberry_Pi/tree/main> for more on that.) I have previous work in C++ at <https://github.com/HankB/MQTT_will> and will revisit that first.
