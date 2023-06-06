# Product Design: Connected Things

Code resources for Product Design: Connected Things course

# Contents

- [Product Design: Connected Things](#product-design-connected-things)
- [Contents](#contents)
	- [Hardware](#hardware)
		- [M5StickCPlus](#m5stickcplus)
	- [Communication](#communication)
		- [ESP-NOW](#esp-now)
		- [AdafruitIO](#adafruitio)


## Hardware
### M5StickCPlus

This course makes use of the M5StickC-Plus board from M5Stack. To learn more about the M5Stick, here are some video tutorials and a Github page on getting started.

- [Video tutorials](https://media.ed.ac.uk/playlist/dedicated/1_iv0d72hv/)
- [Getting started instructions](https://github.com/Edinburgh-College-of-Art/m5stickc-plus-introduction)

## Communication

For this course, you will have to get two devices communicating with eachother. Whether that is two M5Sticks or an M5Stick to some other device, you will have to choose the most appropriate method of communication.

- ESP-NOW - short distance communication (up to 200m). Does not require WiFi connection.
- AdafruitIO - connect to a cloud service. Ideal for connecting devices in different locations or for logging data. Requires WiFi connection.

### ESP-Now

[ESP-NOW](https://www.espressif.com/en/solutions/low-power-solutions/esp-now) is a wireless communication protocol created by Espressif, which enables quick, direct communication between ESP boards (ESP8266, ESP32, ESP32-S and ESP32-C) without the need of a WiFi router. The M5StickC-Plus is built around the ESP32 development board and is able to utilise ESP-NOW to send messages from:

- one device to another device.
- one device to multiple other devices.
- multiple devices to a single device.
- a combination of the above.

It should be noted that this is a short range form of communication with a range in the open of approx. 200m (650ft).

[Here are some examples and instructions on getting started.](https://github.com/Edinburgh-College-of-Art/m5stickc-plus-introduction/tree/main/example-code/ESP-NOW)

### AdafruitIO

[AdafruitIO](https://io.adafruit.com/) is a cloud service created by Adafruit for use in IoT projects. It allows you to set up online feeds to which you can store and retrieve data from your IoT devices.

As well as hosting data, AdafruitIO has options for creating custom UIs to visualize your data. You can also set up actions to notify you directly about your feeds.

[Here are some examples and instructions on getting started.](https://github.com/Edinburgh-College-of-Art/m5stickc-plus-introduction/tree/main/example-code/AdafruitIO)