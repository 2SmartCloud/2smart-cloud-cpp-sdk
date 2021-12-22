# Cloud2Smart

A class for controlling Homie entities and ensuring their interaction with the MQTT broker.

## Platforms

This sdk currently support ESP32 platform.

## Examples

- [2Smart Cloud Relay](https://github.com/2SmartCloud/2smart-cloud-esp32-relay)
- [2Smart Cloud Led Strip](https://github.com/2SmartCloud/2smart-cloud-esp32-led)
- [2Smart Cloud AlexGyver Lamp](https://github.com/2SmartCloud/2smart-cloud-esp32-alexgyver-lamp)

***
## API

- Cloud2Smart()
- void setup()
- Device\* GetDevice()
- void loop()

***

**Cloud2Smart()**

Creates a Cloud2Smart object.

***

**void setup()**

Setting up base features.

***

**Device\* GetDevice() **

Returns a pointer to the [device](src/device/README.md) object.

***

**void loop()**

Handles the current state of the device.

***

## To Do
* [ ] ESP8266 platform support
* [ ] TLS support

