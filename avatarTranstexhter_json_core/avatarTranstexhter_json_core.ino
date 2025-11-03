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
  Serial.println("setPoseType test #######################");
  tester.setPoseType("add0", ROOT);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // addPoseテスト
  Serial.println("addPose test #######################");
  tester.addPose("add2", STATE);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // removePoseテスト1 
  Serial.println("addPose test 1#######################");
  tester.removePose("add2");
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // removePoseテスト2
  Serial.println("addPose test 2#######################");
  tester.removePose("add0");
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
}

void loop() {}