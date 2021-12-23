# Utils

Library with utility functions.

***

## API

- std::string RandomString(uint8_t seed, uint8_t length)
- String TimeToStr(uint8_t hours, uint8_t minutes)
- String Sha256(String rec_data)

***

**std::string RandomString(uint8_t seed, uint8_t length)**

Generates a string of the specified length with random letters and numbers.

- seed: the number that is used to create the string.
- length: the length of the desired string.

Returns a string with random letters and numbers.

***

**String TimeToStr(uint8_t hours, uint8_t minutes)**

Concatenates hours and minutes into a string.

Example: `"15:37"`.

- hours: hours.
- minutes: minutes.

Returns a string with time. 

***

**String Sha256(String data)**

Computes a hash from a string using the SHA256 hashing algorithm.

- data: the string from which the hash is calculated.

Returns the computed hash.
