# Node 

Class for working with nodes.

***
## API

- Node(const char* name, const char* id, Device* device)
- virtual bool Init(Homie* homie)
- void AddProperty(Property* property)
- String GetId() const
- Device* GetDevice() const
- Property* GetProperty(String id)
- virtual void HandleCurrentState()


***

**Node(const char\* name, const char\* id, Device\* device)**

Creates a node object.

- name: node name.
- id: node id.
- device: pointer to the [device](../device/README.md) object.

***

**virtual bool Init(Homie\* homie)**

Initializes the node by publishing the required attributes. Calls initialization on [properties](../property/README.md). Stores a pointer to the [homie](../README.md) object.

- homie: pointer to the [homie](../README.md) object.

Returns the initialization status.

***

**void AddProperty(Property\* property)**

Adds a pointer to the property to the property list for further reference.

- property: pointer to the [property](../property/README.md).

***

**String GetId() const**

Returns the node identifier.

***

**Device\* GetDevice() const**

Returns a pointer to the [device](../device/README.md) object.

***

**Property\* GetProperty(String id)**

Returns a pointer to the property by identifier.

- id: identifier of the [property](../property/README.md).

***

**virtual void HandleCurrentState()**

Handles the current state of the node. Calls processing of the current states of [properties](../property/README.md).
