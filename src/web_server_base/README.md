# WebServerBase

## API

- WebServerBase(Device \*device);
- void Init()

***

**WebServerBase(Device \*device)**

Creates asynchronous web server object.

***

**void Init()**

Setting up web server.
Setting up web server. Setting up handlers for the next methods.

**GET** /  
Opens the admin page index.html.

**GET** /index.html  
Opens the admin page index.html.

**GET** /wifi.html  
Opens the wifi network connection page wifi.html

**GET** /static/favicon.png  
Returns the favicon.png file.

**GET** /static/logo.svg  
Returns the file logo.svg.

**GET** /styles.css  
Returns the styles.css file.

**GET** /healthcheck  
Returns code 200.

**GET** /reboot  
Reboots the ESP.

**GET** /resetdefault  
Clears user parameters from memory.

**GET** /newauthpass  
Sets a new password and reboots the ESP to apply the changes.
Query params:
  - newpass - new password to be set

**GET** /setwifi  
Saves the login and password for the wifi network. Reboots the ESP to apply the changes.
Query params:
  - ssid - the name of the wifi network;
  - pass - password.

**GET** /scan  
Scans and returns a list of wifi networks.

**GET** /connectedwifi  
Returns the name of the wifi network to which the device is connected.

**GET** /setcredentials  
A method that saves new parameters from the admin panel. Reboots the ESP to apply the changes.
Query params:
  - mail - user's email.
  - token - user's password.
  - brokerPort - MQTT port of the broker.
  - productId - product identifier.
  - hostname - the address where the MQTT broker is installed.
  - deviceId - device identifier.

**GET** /pair  
A method that saves new parameters from a mobile application. Reboots the ESP to apply the changes.
Query params:
  - ssid - user's email.
  - psk - user's password.
  - wsp - MQTT port of the broker.
  - token - user's password.
  - host - the address where the MQTT broker is installed.
  - brport - MQTT port of the broker.

**POST** /firmware/upload  
Receives the new firmware file and updates the firmware, then reboots the ESP.