# MQTT
***
## ThingSpeak

### thingspeak-mqtt-subscribe Setup

- go to [ThingSpeak](https://thingspeak.com/)
  - [sign in](https://thingspeak.com/login) OR [sign-up](https://thingspeak.com/users/sign_up)
- Go to [`Account | My Profile`](https://thingspeak.com/account/profile)
- Generate New MQTT API Key
![](https://uk.mathworks.com/help/thingspeak/mqtt_api_key_combod8225de3d105532c6e244c43db7e231d.png)
- Copy MQTT API Key and paste into your `const char mqttApiKey[]`
- Go to your Channel
  - go to API keys
  - copy read API Key and paste into `String channelReadApiKey`
  - go to channel settings
  - copy ChannelID and paste into `String channelId`
