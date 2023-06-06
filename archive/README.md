**Github Repo pre course moving to M5StickC-Plus (22/23)**

__________________________________________________________

# Product Design: Connected Things

Code resources for Product Design: Connected Things course

* * *

# Contents

<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Product Design: Connected Things](#product-design-connected-things)
- [Contents](#contents)
	- [labs](#labs)
	- [examples-code](#examples-code)
	- [Boards](#boards)
		- [Arduino Nano 33 IoT](#arduino-nano-33-iot)
		- [Feather M0](#feather-m0)
		- [Setup](#setup)
	- [Concepts](#concepts)
		- [Thing Speak](#thing-speak)
		- [IFTTT](#ifttt)
		- [JSON](#json)
	- [Sensors](#sensors)
		- [OLED Feather Wing](#oled-feather-wing)
		- [37 Sensors](#37-sensors)
		- [Grove Sensors](#grove-sensors)
		- [Neo Pixels](#neo-pixels)
	- [Communication](#communication)
		- [MQTT](#mqtt)
			- [ThingSpeak](#thingspeak)

<!-- /TOC -->

***

## labs

Code relating to each week's labs.

## examples-code

General examples for covering various programming concepts and breakout boards available at ECA.

## Boards

The following boards will be used throughout the course.

### Arduino Nano 33 IoT

### Feather M0

Code relating to using the Adafruit Feather M0 ATWINC1500 micro-controller.

[Visit Adafruit for comprehensive setup instructions for the Feather M0](https://learn.adafruit.com/adafruit-feather-m0-wifi-atwinc1500/)

### Setup

Visit Adafruit for comprehensive setup instructions for the Feather M0

***

## Concepts

### Thing Speak

Code related to connecting to communicating with ThingSpeak. Make sure to download the ThingSpeak library in the Arduino IDE

### IFTTT

[If this then that webhook examples](https://arduinodiy.wordpress.com/2018/01/03/ifttt-webhooks/).

### JSON

JSON Test is a handy place to start with grabbing JSON data. The time example is handy in and off itself (http://date.jsontest.com), or you can [say hello to JSON Isaacs](https://raw.githubusercontent.com/Edinburgh-College-of-Art/Connected-Things/master/example-code/json/example-data.json)

***

## Sensors

### OLED Feather Wing

Code relating to using the Adafruit OLED Feather wing.

[Visit Adafruit for comprehensive setup instructions for the OLED Feather Wing](https://learn.adafruit.com/adafruit-oled-featherwing?view=all)

### 37 Sensors

Code relating to using the [Keyestudio 37 sensor kit](https://wiki.keyestudio.com/Ks0068_keyestudio_37_in_1_Sensor_Kit_for_Arduino_Starters#kesestudio_37_in_1_Sensor_Kit_for_Arduino_Starters). [Documentation is already available elsewhere](https://www.instructables.com/id/Arduino-37-in-1-Sensors-Kit-Explained/), so the examples contained in this repository focus on best practice and clarity in coding.

For the IR sensors, we recommend using the [IRRemote Library](http://z3t0.github.io/Arduino-IRremote/) available through the Arduino IDE library manager.

### Grove Sensors

Similar to the Keyestudio sensors, this relates to examples of using the SEEED Studio range of grove sensors.

### Neo Pixels

Reference for using the Adafruit addressable LEDs NeoPixels.

* * *

## Communication

### MQTT

- [Public MQTT Brokers](https://github.com/mqtt/mqtt.github.io/wiki/public_brokers)
- [Public MQTT Brokers](http://moxd.io/2015/10/17/public-mqtt-brokers/)

#### ThingSpeak

- go to [ThingSpeak](https://thingspeak.com/)
  - [sign in](https://thingspeak.com/login) OR [sign-up](https://thingspeak.com/users/sign_up)
- Go to [`Account | My Profile`](https://thingspeak.com/account/profile)
- Generate New MQTT API Key
![](https://uk.mathworks.com/help/thingspeak/mqtt_api_key_combod8225de3d105532c6e244c43db7e231d.png)
- Copy MQTT API Key and paste into your sketch
- Go to your Channel
  - go to API keys
  - copy read API Key and paste into your sketch
