# AutoUpdateFw

The class that performs the firmware update procedure.

***
**Init(Homie* homie)**

Initializes firmware parameters from the MQTT broker.

***
**HandleCurrentState()**

Monitors current state of firmware parameters (auto update, staging firmware, version, update status)

***

**CheckFirmware(uint8_t firmwareVer)**

Method to check for the firmware updates

***

**CheckFirmwareVersion()**

Is used to get current firmware version from the server

***

**UpdateFirmware()**

Method to perform the firmware update getting the **.bin** from the provided URL

### NOTE
If `staging` option is `true`, the path for the **.bin** will be changed to [kUrlStagingFirmwareFilePath_](./auto_upd_firmw.h#L38)

***

**LoadFwSettings()**

Method to load firmware settings from `fwconf.txt` file from SPIFFS

***

**SetUpdateTime(String time)**

Sets time to perform the firmware update

***

**SaveFwSettings()**

Writes firmware settings to `fwconf.txt` file from SPIFFS

***


