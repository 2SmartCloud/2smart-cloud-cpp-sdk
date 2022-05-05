
#include "main.h"

#include "2smart.h"

String product_id = "Your_product_id";  // product id
const char *device_name = "2Smart example";
const char *device_version = "1";

Cloud2Smart smartcloud;

void setup() {
    smartcloud.setup();
}
void loop() { smartcloud.loop(); }
