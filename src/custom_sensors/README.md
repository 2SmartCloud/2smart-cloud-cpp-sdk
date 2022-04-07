# Validation

***
On the received message, in case of incorrect values, the error body should be sent to a topic like `errors/sweet-home/<device-id>/node...`
The error body should be in the JSON format of the string `"{"code":"error_code","message":"error message"}`.
(For example, if an incorrect value has come to the topic `<user-hash>/sweet-home/<device-id>/<node-id>/<sensor-id>/set`,
then the error should be sent to the topic `<user-hash>/errors/sweet-home/<device-id>/<node-id>/<sensor-id>`).

The class for validating received values from the broker, derivated from `class Property`.
***

## Usage

To make custom value-validation case You should rewrite the `bool Validate(String value)` method in derivated class on Your own as it shown in this example.

***
### bool Validate(String value)

- `String value` - value from `void Property::SetValue(String value)` method, received from the broker.
- If `value` is not valid, `bool Validate()` should set an error with code and error-message (as described below) and return `false`.
- Values `error_code` and `error_message` can be modified as given arguments in method `void Property::SetError(String code, String message)`.