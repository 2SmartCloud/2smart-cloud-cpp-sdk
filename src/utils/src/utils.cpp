#include "utils.h"

#include <cstdlib>

#include "sha256/src/mbdtls.h"

std::string RandomString(uint8_t length) {
    uint32_t seed = esp_random();
    return RandomString(seed, length);
}

std::string RandomString(uint32_t seed, uint8_t length) {
    srand(seed);
    const char *letters[62] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p",
                               "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "1", "2", "3", "4", "5", "6",
                               "7", "8", "9", "0", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
                               "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    std::string randString = "";
    for (int i = 0; i < length; i++) {
        randString.append(letters[rand() % 61]);
    }
    return randString;
}

String TimeToStr(uint8_t hours, uint8_t minutes) {
    String result = "";
    if (hours < 10) result += "0";
    result += hours;
    result += ":";
    if (minutes < 10) result += "0";
    result += minutes;
    return result;
}

String Sha256(String data) {
    const char *payload = data.c_str();
    byte shaResult[32];

    mbedtls_md_context_t ctx;
    mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;

    const size_t payloadLength = strlen(payload);

    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
    mbedtls_md_starts(&ctx);
    mbedtls_md_update(&ctx, (const unsigned char *)payload, payloadLength);
    mbedtls_md_finish(&ctx, shaResult);
    mbedtls_md_free(&ctx);

    Serial.print("Hash: ");
    String result = "";
    for (int i = 0; i < sizeof(shaResult); i++) {
        char str[3];
        snprintf(str, sizeof(shaResult), "%02x", static_cast<int>(shaResult[i]));
        Serial.print(str);
        result = result + str;
    }
    return result;
}

uint8_t RSSIToPercent(int8_t dBm) {
    uint8_t wifiQuality = 2 * (dBm + 100);
    if (wifiQuality > 100) wifiQuality = 100;

    return wifiQuality;
}
