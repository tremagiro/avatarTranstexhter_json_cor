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
  Serial.println("setPose test 1#######################");
  tester.setPose("add0", "right-shoulder-roll", 100);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // setPoseテスト
  Serial.println("setPose test 2#######################");
  tester.setPose("add0", "left-shoulder-roll", 134);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // setPoseTypeテスト
  Serial.println("setPose test 2#######################");
  tester.setPoseType("add0", ROOT);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
}

void loop() {}