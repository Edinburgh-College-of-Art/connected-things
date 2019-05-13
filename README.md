# Product Design: Connected Things

Code resources for Product Design: Connected Things course

# Contents

## Feather M0

Code relating to using the Adafruit Feather M0 micro-controller.

### Thing Speak

Code related to connecting to communicating with ThingSpeak. Make sure to download the ThingSpeak library in the Arduino IDE

### Web Server

Code relating to setting the Feather M0 as web server, serving html webpages and providing a wireless access point.

### Timer Interrupts

Code demonstrating how to use the timers available on the Feather M0. This differs from the approach you would take if using an Arduino Uno, but the code has been structured in such a way that you shouldn't have to worry to much about what is happening under-the-hood. Timer interrupts are used to make actions happen at regular intervals. This means that you won't be able to use the `delay()` function.

Download the [Adafruit ZeroTimer Library](https://github.com/adafruit/Adafruit_ZeroTimer) for greater control.

## 37 Sensors

Code relating to using the [Keyestudio 37 sensor kit](https://wiki.keyestudio.com/Ks0068_keyestudio_37_in_1_Sensor_Kit_for_Arduino_Starters#kesestudio_37_in_1_Sensor_Kit_for_Arduino_Starters). [Documentation is already available elsewhere](https://www.instructables.com/id/Arduino-37-in-1-Sensors-Kit-Explained/), so the example contained in this repository focus on best practice and clarity in coding.

For the IR sensors, we recommend using the [IRRemote Library](http://z3t0.github.io/Arduino-IRremote/) available through the Arduino IDE library manager.

## Grove Sensors

Similar to the Keyestudio sensors, this relates to examples of using the SEEED Studio range of grove sensors.

## Neo Pixels

Reference for using the Adafruit addressable LEDs NeoPixels.
