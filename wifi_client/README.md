# WifiClient

A class for working with a Wi-Fi client.

***

## API

- WifiClient()
- void SetCredentials(String ssid_name, String ssid_password)
- bool Connect()

***

**MqttClient()**

Creates a Wi-Fi client object.

***

**void SetCredentials(String ssid_name, String ssid_password)**

Method for setting Wi-Fi username and password.

- ssid_name: the name of the network.
- ssid_password: network password.

***

**Connect()**

Connects to the network if the connection has not yet been established.

Returns the connection status.
