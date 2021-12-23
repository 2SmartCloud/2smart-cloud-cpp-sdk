# 2Smart Cloud

A class for controlling Homie entities and ensuring their interaction with the MQTT broker.

## Platforms

This sdk currently support ESP32 platform.

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


## Examples

- [2Smart Cloud Blinker](https://github.com/2SmartCloud/2smart-cloud-esp32-blinker)
- [2Smart Cloud Relay](https://github.com/2SmartCloud/2smart-cloud-esp32-relay)
- [2Smart Cloud Led Strip](https://github.com/2SmartCloud/2smart-cloud-esp32-led)
- [2Smart Cloud AlexGyver Lamp](https://github.com/2SmartCloud/2smart-cloud-esp32-alexgyver-lamp)

## To Do
* [ ] ESP8266 platform support
* [ ] TLS support


## Docs

Read our docs about [2Smart Cloud protocol](https://github.com/2SmartCloud/2smart-cloud-docs#2smart-cloud-protocol)