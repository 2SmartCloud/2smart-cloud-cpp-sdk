# Homie

A class for controlling Homie entities and ensuring their interaction with the MQTT broker.

## Platforms

This sdk currently support ESP32 platform.

## Examples

- [2Smart Cloud Relay](https://github.com/2SmartCloud/2smart-cloud-esp32-relay)
- [2Smart Cloud Led Strip](https://github.com/2SmartCloud/2smart-cloud-esp32-led)
- [2Smart Cloud AlexGyver Lamp](https://github.com/2SmartCloud/2smart-cloud-esp32-alexgyver-lamp)

***
## API

- Homie(MqttClient* mqtt_client)
- void SetDevice(Device* device);
- bool Init(String user_hash, String host, String broker_port, String token, std::function<void(char*, uint8_t*, unsigned int)> callback)
- bool Publish(const Device& device, String attribute, String value, bool retained)
- bool Publish(const Node& node, String attribute, String value, bool retained)
- bool Publish(const Property& property, String attribute, String value, bool retained)
- bool SubscribeTopic(const Property& property)
- void HandleMessage(String topic, byte* payload, unsigned int length)
- void HandleCurrentState()

***

**Homie(MqttClient\* mqtt_client)**

Creates a homie object, accepts an MQTT client object

- mqtt_client:[MQTT client](mqtt_client/README.md) object to be assigned.

***

**void SetDevice(Device\* device)**

Assigns a device object to the current homie object

- device: the device object to be assigned.

***

**bool Init(String user_hash, String host, String broker_port, String token, std::function<void(char\*, uint8_t\*, unsigned int)> callback)**

Connects to MQTT broker and initiates the device initialization.

- user_hash: user ID, generated based on the email.
- host: the address where the MQTT broker is installed.
- broker_port: the port on which the broker is located.
- token: password for connecting to a broker, generated when creating a user.
- callback: a function that will be called to accept new messages from the broker. 

Returns the initialization status.

***

**bool Publish(const Device& device, String attribute, String value, bool retained)**

Publishes the value of a device attribute to the broker.

- device: pointer to [device](device/README.md) object.
- attribute: the attribute that is being published.
- value: parameter value.
- retained: flag responsible for storing messages in topics.

Returns the status of posting a message to a topic.

***

**bool Publish(const Node& node, String attribute, String value, bool retained)**

Publishes the value of a node's attribute to the broker.

- node: pointer to [node](node/README.md) object.
- attribute: the attribute that is being published.
- value: parameter value.
- retained: flag responsible for storing messages in topics.

Returns the status of posting a message to a topic.

***

**bool Publish(const Property& property, String attribute, String value, bool retained)**

Publishes the value of a property attribute to the broker.

- property: pointer to [property](property/README.md) object.
- attribute: the attribute that is being published.
- value: parameter value.
- retained: flag responsible for storing messages in topics.

Returns the status of posting a message to a topic.

***

**bool SubscribeTopic(const Property& property)**

Subscribes to /set topic of property value.

Example: 
```
For a sensor that has a topic of value 73062d872926c2a556f17b36f50e328ddf9bff9d403939bd14b6c3b7f5a33fc2/sweet-home/device-id/node-id/sensor-id
when calling SubscribeTopic homie will subscribe to the topic 73062d872926c2a556f17b36f50e328ddf9bff9d403939bd14b6c3b7f5a33fc2/sweet-home/device-id/node-id/sensor-id/set
```

- property: pointer to the [property](property/README.md) object.

Returns the subscription status.

***

**void HandleMessage(String topic, byte\* payload, unsigned int length)**

Accepts a message and calls a handler on the required [property](property/README.md)

- topic: topic where the message came from.
- payload: message text.
- length: the length of the message.

***

**void HandleCurrentState()**

Calls a loop on the MQTT client, and processes the current state of the device


***

## To Do
* [ ] ESP8266 platform support
* [ ] TLS support

Read our docs about [2Smart Cloud protocol](https://github.com/2SmartCloud/2smart-cloud-docs#2smart-cloud-protocol)
