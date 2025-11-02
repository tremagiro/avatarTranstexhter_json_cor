#include "avatarTranstexhterJsonCore.h"


avatarTranstexhterJsonCore tester = avatarTranstexhterJsonCore();

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  serializeJsonPretty(tester.getJsonDocument(), Serial);
}

void loop() {}