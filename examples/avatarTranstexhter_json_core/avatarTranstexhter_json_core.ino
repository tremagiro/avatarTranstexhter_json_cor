#include <avatarTranstexhterJsonCore.h>

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
        "left-shoulder-rollEnable": 0,
        "eyeBrightness": 255
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
            "pupilTypeL": 0,
            "pupilTypeR": 0,
            "eyelidTypeL": 0,
            "eyelidTypeR": 0,
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
            "pupilTypeL": 0,
            "pupilTypeR": 0,
            "eyelidTypeL": 0,
            "eyelidTypeR": 0,
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
  Serial.println();
  Serial.println("###################################");
  // 目の明るさテスト
  // (ポーズの poseValue 内に "eyeBrightness" として保存される。値がないポーズは初期値 EYE_BRIGHTNESS_DEFAULT になる)
  Serial.println("setPoseEyeBrightness test#######################");
  tester.setPoseEyeBrightness("add0", 128);
  tester.setPoseEyeBrightness("root", 200);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println();
  Serial.printf("add0 eyeBrightness:%d\n", tester.getPoseEyeBrightness("add0"));
  Serial.printf("root eyeBrightness:%d\n", tester.getPoseEyeBrightness("root"));
  Serial.printf("存在しないポーズ eyeBrightness:%d\n", tester.getPoseEyeBrightness("none"));
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
  // (先頭のステップはROOTかSTATEのポーズである必要がある。add0は削除済みのためrootを指定する)
  tester.setMotion("initMotion", 0, "root", 1000, 1, 2, 0, 1, 3000, 0, 0);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // 各getテスト
  Serial.println("get Motion Infos#######################");
  Serial.printf("initMotion motionPose:%s\n", tester.getMotionPoseName("initMotion", 0).c_str());
  Serial.printf("initMotion moveTime:%d\n", tester.getMotionMoveTime("initMotion", 0));
  Serial.printf("initMotion pupilTypeL:%d\n", tester.getMotionPupilTypeL("initMotion", 0));
  Serial.printf("initMotion pupilTypeR:%d\n", tester.getMotionPupilTypeR("initMotion", 0));
  Serial.printf("initMotion eyelidTypeL:%d\n", tester.getMotionEyelidTypeL("initMotion", 0));
  Serial.printf("initMotion eyelidTypeR:%d\n", tester.getMotionEyelidTypeR("initMotion", 0));
  Serial.printf("initMotion eyeBlinkTime:%d\n", tester.getMotionEyeBlinkTime("initMotion", 0));
  Serial.printf("initMotion mouthType%d\n", tester.getMotionMouthType("initMotion", 0));
  Serial.printf("initMotion mouthBlinkTime:%d\n", tester.getMotionMouthBlinkTime("initMotion", 0));
  Serial.println("###################################");
  // addMotionテスト
  Serial.println("addMotion test 1#######################");
  tester.addMotions("addMotion0", "add0", "root", 0, 0, 0, 0, 1000, 1, 1500);
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println("###################################");
  // addMotionテスト
  Serial.println("addMotion test 2#######################");
  tester.addPose("add3");
  tester.addMotion("addMotion0", "add3", 1, 2500, 0, 0, 0, 0, 1000, 1, 1500);
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
  // モーション名変更テスト(モーション名で始まるステップ名も変わる)
  Serial.println("renameMotion test#######################");
  Serial.printf("addMotion0 -> walk : %d\n", tester.renameMotion("addMotion0", "walk"));
  Serial.printf("none -> x(存在しない) : %d\n", tester.renameMotion("none", "x"));
  Serial.printf("walk ポーズ総数:%d\n", tester.getMotionIndexes("walk"));
  Serial.println("###################################");
  // ポーズ名変更テスト(モーションのステップが参照しているポーズ名も変わる)
  Serial.println("renamePose test#######################");
  Serial.printf("add0 -> add0renamed : %d\n", tester.renamePose("add0", "add0renamed"));
  Serial.printf("root -> add3(同名あり) : %d\n", tester.renamePose("root", "add3"));
  Serial.printf("none -> x(存在しない) : %d\n", tester.renamePose("none", "x"));
  Serial.printf("walk step0 motionPose:%s\n", tester.getMotionPoseName("walk", 0).c_str());
  // モーション名・ステップ名・ステップが参照するポーズ名の変更をまとめて確認する
  serializeJsonPretty(tester.getJsonDocument(), Serial);
  Serial.println();
  Serial.println("###################################");

}

void loop() {}