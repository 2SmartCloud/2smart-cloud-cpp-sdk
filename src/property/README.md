# PROPERTY_TYPE

An enumeration for separating properties into types.

## values

- OPTION - property for options, settings, etc.
- TELEMETRY - a property that only publishes values and does not read them.
- SENSOR - properties for sensors.

***

# Property 

## API

Class for working with device and node properties.

***

- Property(const char* name, const char* id, Node* node, PROPERTY_TYPE type, bool settable, bool retained, const char* data_type)
- Property(const char* name, const char* id, Device* device,PROPERTY_TYPE type, bool settable, bool retained, const char* data_type)
- virtual bool Init(Homie* homie)
- String GetValue() const
- String GetId() const
- PROPERTY_TYPE GetType() const
- Node* GetNode() const
- Device* GetDevice() const
- bool HasNewValue()
- void SetValue(String value)
- void SetHasNewValue(bool has_new_value)
- virtual void HandleCurrentState()
- virtual void HandleSettingNewValue()

***

**Property(const char\* name, const char\* id, Node\* node, PROPERTY_TYPE type, bool settable, bool retained, const char\* data_type)**

Creates a property object.

- name: property name.
- id: property identifier.
- node: pointer to the [node](../node/README.md) object.
- type: property type.
- settable: flag responsible for the ability to change the value.
- retained: flag responsible for storing the message in the topic.
- data_type: message data type according to homie convention.

***

**Property(const char\* name, const char\* id, Device\* device, PROPERTY_TYPE type, bool settable, bool retained, const char\* data_type)**

Creates a property object.

- name: property name.
- id: property identifier.
- device: уpointer to the [device](../device/README.md) object.
- type: property type.
- settable: flag responsible for the ability to change the value.
- retained: flag responsible for storing the message in the topic.
- data_type: message data type according to homie convention.

***

**virtual bool Init(Homie\* homie)**

Initializes the property by publishing the required attributes. Subscribes to the topic if necessary. Stores a pointer to the [homie](../README.md) object.

- homie: pointer to the [homie](../README.md) object.

Returns the initialization status.

***

**String GetValue() const**

Returns the value of the property.

***

**String GetId() const**

Returns the identifier of the property.

***

**PROPERTY_TYPE GetType()**

Returns the type of the property.

***

**Node\* GetNode() const**

Returns a pointer to the [node](../node/README.md) object.

***

**Device\* GetDevice() const**

Returns a pointer to the [device](../device/README.md) object.

***

**bool HasNewValue()**

Returns a flag on whether the new value is explicitly for the property.

***

**void SetValue(String value)**

Sets a new value to the property and publishes it to the broker.

- value: new value.

***

**void SetHasNewValue(bool has_new_value)**

Sets the explicit flag for the new (not proccessed) property value.

- has_new_value: new state of the flag. 

***

**virtual void HandleCurrentState()**

Handler method for the current property value.

***

**virtual void HandleSettingNewValue()**

Handler method for the new property value. If specific handling of the new property value is required, it must be overridden in the inherited class.
