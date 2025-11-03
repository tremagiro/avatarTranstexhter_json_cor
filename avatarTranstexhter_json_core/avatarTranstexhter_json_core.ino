#include "avatarTranstexhterJsonCore.h"


avatarTranstexhterJsonCore tester = avatarTranstexhterJsonCore();

void setup() {
  delay(5000);
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // setPoseテスト
  Serial.println("setPose test#######################");
  tester.setPose("add0", "right-shoulder-roll", 100);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");

  Serial.end();
}

void loop() {}