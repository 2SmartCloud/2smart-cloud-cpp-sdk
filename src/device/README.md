# DeviceData

The structure that contains the necessary data for the device

## Properties

- const char* name - device name
- const char* fw_ver - firmware version
- const char* fw_name - firmware name
- const char* ip - device IP address
- const char* impl - identifier for the Homie implementation (for example, "esp-32")
- const char* mac - MAC address of the device
- const char* state - device state
- const char* id - device id

***

# Device

A class for working with a device.

***
## API

- Device(Homie* homie)
- void SetCredentials(DeviceData device_data)
- bool Init()
- void AddNode(Node* node)
- void AddProperty(Property* property)
- String GetId() const
- String GetFirmwareVersion() const
- Node* GetNode(String id)
- void SetNotifier(Notifier* notifier)
- void HandleCurrentState()
- bool SendNotification(String text)
- bool IsSysNotifyEnabled()
- bool IsFwNotifyEnabled()

***

**Device(Homie\* homie)**

Creates a device object.

- homie: pointer to the [homie](../README.md) object.

***

**void SetCredentials(DeviceData device_data)**

Assigns the required data to the device.

- device_data: structure with data for the device.

***

**bool Init()**

Initializes the device by publishing the required attributes. Causes initialization of [nodes](../node/README.md) and [properties](../property/README.md).

Returns the initialization status.

***

**void AddNode(Node\* node)**

Adds a pointer to a node to the list of nodes for further reference.

- node: node pointer.

***

**void AddProperty(Property\* property)**

Adds a pointer to the property to the property list for further reference.

- property: pointer to the [property](../property/README.md).

***

**String GetId() const**

Returns the device identifier.

***

**String GetFirmwareVersion() const**

Returns the firmware version.

***

**Node\* GetNode(String id)**

Returns a pointer to a node by identifier.

- id: identifier of the [node](../node/README.md).

***

**void SetNotifier(Notifier\* notifier)**

Stores a pointer to the notification module.

- notifier: pointer to the [notification module](../notifier/README.md) object.

***

**void HandleCurrentState()**

Calls processing of the current states of [nodes](../node/README.md) and [properties](../property/README.md). Sends the heartbeat.

***

**bool SendNotification(String text)**

Sends a notification with the received text.

- text: message text.

Returns the status of sending the notification.

***

**bool IsSysNotifyEnabled()**

Returns the status of system notifications.

***

**bool IsFwNotifyEnabled()**

Returns the status of update notifications.
