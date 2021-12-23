# file_system

A class for working with file system.

***

## API

- bool InitFiles()
- bool LoadConfig()
- bool SaveConfig()
- bool EraseFlash()
- bool WriteSettings(const char *file_path, uint8_t *data, size_t - size_of_data)
- bool ReadSettings(const char *file_path, uint8_t *data, size_t - size_of_data)

***

**bool InitFiles()**

Initialize file system.

***

**bool LoadConfig()**

Read config file.

***

**bool SaveConfig()**

Save config file.

***

**bool EraseFlash()**

Erase config from file system.

***

**bool WriteSettings(const char \*file_path, uint8_t \*data, size_t - size_of_data)**

Write data to file.

- file_path: path to file.
- data: data to write.
- size_of_data: size of data to write.

Returns write status.

***

**bool ReadSettings(const char \*file_path, uint8_t \*data, size_t - size_of_data)**

Read data from file.

- file_path: path to file.
- data: data to read.
- size_of_data: size of data to read.

Returns read status.

***
