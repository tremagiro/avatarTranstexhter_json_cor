#include "avatarTranstexhterJsonCore.h"

avatarTranstexhterJsonCore tester = avatarTranstexhterJsonCore();

const char initialJson[] PROGMEM = R"(
{
  "pose": [
    {
      "poseName": "root",
      "poseValue": {
        "right-shoulder-roll": 90,
        "right-shoulder-pitch": 90,
        "right-elbow-pitch": 90,
        "body-lift": 1000,
        "right-foot-yaw": 90,
        "right-foot-roll": 90,
        "body-pitch": 90,
        "left-foot-roll": 90,
        "left-foot-yaw": 90,
        "backpack-pitch": 90,
        "left-elbow-pitch": 90,
        "left-shoulder-pitch": 90,
        "left-shoulder-roll": 90,
        "right-motor-speed": 90,
        "left-motor-speed": 90,
        "poseType": 0
      }
    }
  ],
  "motion": [
    {
      "motionName": "initMotion",
      "motionArrayKey": {
        "motionPose": "root",
        "moveTime": 0,
        "eyeType": 0,
        "blinkEyeTime": 0,
        "mouthType": 0,
        "blinkMouthTime": 0
      }
    }
  ]
}
)";

void setup() {
  delay(5000);
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  // setJsonDocument・getJsonDocumentのテスト
  JsonDocument initJsonDoc;
  deserializeJson(initJsonDoc, initialJson);
  tester.setJsonDocument(initJsonDoc);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // setPoseテスト
  Serial.println("setPose test 1#######################");
  tester.setPose("add0", "right-shoulder-roll", 100);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // setPoseテスト
  Serial.println("setPose test 2#######################");
  tester.setPose("root", "left-shoulder-roll", 134);
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