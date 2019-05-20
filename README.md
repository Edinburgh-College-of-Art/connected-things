# Product Design: Connected Things

Code resources for Product Design: Connected Things course

* * *

# Contents

## Feather M0

Code relating to using the Adafruit Feather M0 ATWINC1500 micro-controller.

[Visit Adafruit for comprehensive setup instructions for the Feather M0](https://learn.adafruit.com/adafruit-feather-m0-wifi-atwinc1500/)

### Setup

Visit Adafruit for comprehensive setup instructions for the Feather M0

### Thing Speak

Code related to connecting to communicating with ThingSpeak. Make sure to download the ThingSpeak library in the Arduino IDE

### IFTTT

[If this then that webhook examples](https://arduinodiy.wordpress.com/2018/01/03/ifttt-webhooks/).

### JSON

[Say hello to JSON isaacs](https://raw.githubusercontent.com/keikoro/isaacs.JSON/master/isaacs.JSON)

### Web Server

Code relating to setting the Feather M0 as web server, serving html webpages and providing a wireless access point.

### Timer Interrupts

Code demonstrating how to use the timers available on the Feather M0. This differs from the approach you would take if using an Arduino Uno, but the code has been structured in such a way that you shouldn't have to worry to much about what is happening under-the-hood. Timer interrupts are used to make actions happen at regular intervals. This means that you won't be able to use the `delay()` function.

Download the [Adafruit ZeroTimer Library](https://github.com/adafruit/Adafruit_ZeroTimer) for greater control.

* * *

## Feather HUZZAH

Code relating to using the Adafruit Feather HUZZAH ESP8266 micro-controller.

[Visit Adafruit for comprehensive setup instructions for the Feather ESP8266](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide)

###### TIPS

-   Don't open Serial Monitor when uploading

* * *

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
