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
      "motionArrayKey": [
        {
          "motionNameTurn": "initMotionStart",
          "motionValue": {
            "motionPose": "root",
            "moveTime": 0,
            "eyeType": 0,
            "blinkEyeTime": 0,
            "mouthType": 0,
            "blinkMouthTime": 0
          }
        },
        {
          "motionNameTurn": "initMotionFinish",
          "motionValue": {
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
  ]
}
)";

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  // serializeJsonPretty(tester.getJsonDocument(), Serial);
  // Serial.println("###################################");
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
    // getPoseテスト
  Serial.println("getPose test #######################");
  for(int i;i<JOINT_TOTAL;i++){
    Serial.printf("root %s : %d\n", jointKeys[i].c_str(), tester.getPose("add0", jointKeys[i]));
  }
  Serial.println("###################################");
  // setMotionテスト
  Serial.println("setMotion test#######################");
  tester.setMotion("initMotion", 0, "add0", 1000, 0, 0, 0, 0);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // 各getテスト
  Serial.println("get Motion Infos#######################");
  Serial.printf("initMotion motionPose:%s\n", tester.getMotionPoseName("initMotion", 0).c_str());
  Serial.printf("initMotion moveTime:%d\n", tester.getMotionMoveTime("initMotion", 0));
  Serial.printf("initMotion eyeType:%d\n", tester.getMotionEyeType("initMotion", 0));
  Serial.printf("initMotion eyeBlinkTime:%d\n", tester.getMotionEyeBlinkTime("initMotion", 0));
  Serial.printf("initMotion mouthType%d\n", tester.getMotionMouthType("initMotion", 0));
  Serial.printf("initMotion mouthBlinkTime:%d\n", tester.getMotionMouthBlinkTime("initMotion", 0));
  Serial.printf("initMotion ポーズ総数:%d\n", tester.getMotionIndexes("initMotion"));
  Serial.println("###################################");
  // addMotionテスト
  Serial.println("addMotion test#######################");
  // tester.setMotion("initMotion", 0, "add0", 1000, 0, 0, 0, 0);
  // serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // モーション総数取得
  Serial.println("get Motion times Infos#######################");
  std::vector<String> motionKeys;
  Serial.printf("モーション総数:%d\n", tester.wholeMotion(motionKeys));
  for(String s : motionKeys){
    Serial.println(s);
  }
  Serial.println("###################################");

}

void loop() {}