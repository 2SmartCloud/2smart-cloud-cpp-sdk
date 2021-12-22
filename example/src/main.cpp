#include "main.h"

#include "2smart.h"

String product_id = "Your_product_id";  // production id

const char *device_name = "2Smart example";
const char *device_version = "1";

Cloud2Smart smartcloud;

void setup() {
    /* -------------------- Start init your nodes and properties --------------------*/

    /* -------------------- End init your nodes and properties --------------------*/
    smartcloud.setup();
}
void loop() { smartcloud.loop(); }
