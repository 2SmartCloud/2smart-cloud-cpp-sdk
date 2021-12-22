# Notifier

Class for working with notifications.

***
## API

- Notifier(MqttClient* mqtt_client)
- void SetUserHash(String user_hash)
- bool CreateNotification(String text)

***

**Notifier(MqttClient\* mqtt_client)**

Creates a module object for notifications.

- mqtt_client: pointer to the [MQTT client](../../mqtt_client/src/README.md) object.

***

**void SetUserHash(String user_hash)**

Remembers the user ID.

- user_hash: user ID.

***

**bool CreateNotification(String text)**

Publishes a notification to a topic `<user_hash>/notifications/create` 

- text: JSON string with notification parameters.

Returns the status of publishing notifications.
