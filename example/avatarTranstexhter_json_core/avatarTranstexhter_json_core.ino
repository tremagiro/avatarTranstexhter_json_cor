#include "avatarTranstexhterJsonCore.h"

avatarTranstexhterJsonCore tester = avatarTranstexhterJsonCore();

const char initialJson[] PROGMEM = R"(
{
  "pose": [
    {
      "poseName": "root",
      "poseValue": {
        "Enable": 1,
        "poseType": 0,
        "right-shoulder-roll": 90,
        "right-shoulder-rollEnable": 0,
        "right-shoulder-pitch": 90,
        "right-shoulder-pitchEnable": 1,
        "right-elbow-pitch": 90,
        "right-elbow-pitchEnable": 0,
        "body-lift": 4000,
        "body-liftEnable": 1,
        "right-foot-yaw": 90,
        "right-foot-yawEnable": 0,
        "right-foot-roll": 90,
        "right-foot-rollEnable": 1,
        "body-pitch": 90,
        "body-pitchEnable": 0,
        "left-foot-roll": 90,
        "left-foot-rollEnable": 1,
        "left-foot-yaw": 90,
        "left-foot-yawEnable": 0,
        "backpack-pitch": 90,
        "backpack-pitchEnable": 1,
        "left-elbow-pitch": 90,
        "left-elbow-pitchEnable": 0,
        "left-shoulder-pitch": 90,
        "left-shoulder-pitchEnable": 0,
        "left-shoulder-roll": 90,
        "left-shoulder-rollEnable": 0
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
  Serial.println("###################################");
  // setJsonDocument・getJsonDocumentのテスト
  JsonDocument initJsonDoc;
  deserializeJson(initJsonDoc, initialJson);
  serializeJsonPretty(initJsonDoc, Serial);
  tester.setJsonDocument(initJsonDoc);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // setPoseテスト
  Serial.println("setPose test 1#######################");
  tester.setPose("add0", "right-shoulder-roll", 100);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // setPoseテスト2
  Serial.println("setPose test 2#######################");
  tester.setPose("root", "left-shoulder-roll", 134);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // setPoseテスト3
  Serial.println("setPose test 3#######################");
  tester.setPose("add0", "left-shoulder-roll", 134, false);
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
  for(int i = 0;i<JOINT_TOTAL;i++){
    Serial.printf("root %s : %d\n", jointKeys[i].c_str(), tester.getPose("root", jointKeys[i]));
  }
  // getEnablePoseテスト
  Serial.println("getPose test #######################");
  for(int i = 0;i<JOINT_TOTAL;i++){
    Serial.printf("root %s : %d\n", jointKeys[i].c_str(), tester.getEnablePose("root", jointKeys[i]));
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
  Serial.println("###################################");
  // addMotionテスト
  Serial.println("addMotion test 1#######################");
  tester.addMotions("addMotion0", "add0", "root", 0, 1000, 1, 1500);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // addMotionテスト
  Serial.println("addMotion test 2#######################");
  tester.addPose("add3");
  tester.addMotion("addMotion0", "add3", 1, 2500, 0, 1000, 1, 1500);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // モーション総数取得
  Serial.println("get Motion times Infos#######################");
  Serial.printf("addMotion0 ポーズ総数:%d\n", tester.getMotionIndexes("addMotion0"));
  std::vector<String> motionKeys;
  Serial.printf("モーション総数:%d\n", tester.wholeMotion(motionKeys));
  for(String s : motionKeys){
    Serial.println(s);
  }
  Serial.println("###################################");
  // モーション削除
  Serial.println("remove Motion times Infos#######################");
  tester.removeMotion("addMotion0", 1);
  tester.removeMotions("initMotion");
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  // モーション総数取得
  Serial.printf("addMotion0 ポーズ総数:%d\n", tester.getMotionIndexes("addMotion0"));
  motionKeys.clear();
  Serial.printf("モーション総数:%d\n", tester.wholeMotion(motionKeys));
  for(String s : motionKeys){
    Serial.println(s);
  }
  Serial.println("###################################");

}

void loop() {}