#include "avatarTranstexhterJsonCore.h"

// saveJsonへオブジェクトを渡す
int avatarTranstexhterJsonCore::setJsonDocument(JsonDocument saveJsonObject, String* errorKey){
  return 0;
}

// 持っているJsonオブジェクトを渡す
JsonDocument avatarTranstexhterJsonCore::getJsonDocument(){
  return saveJsonDoc;
}

// ポーズの有無
bool avatarTranstexhterJsonCore::isPose(String poseKey){
  return true;
}

// ポーズ情報を追加・上書きする
bool avatarTranstexhterJsonCore::setPose(String poseKey, String jointKey, int value){
  // 指定の関節キーが存在しない
  bool isJointKey = false;
  for(int i=0;i<JOINT_TOTAL;i++){
    if(jointKey.equals(jointKeys[i].c_str()) == true){
      isJointKey = true;
      break;
    }
  }
  if(isJointKey == false){
    // 存在しない関節キーを指定したため終了
    return false;
  }
  // 指定のポーズは存在するか
  if(isPose(poseKey) == false){
    // 新規作成
    initJson();
  }
  // 指定のキーの値を更新
  return true;
}

// ポーズタイプを追加・上書きする
bool avatarTranstexhterJsonCore::setPoseType(String poseKey, poseType value){
  return true;
}

// ポーズ情報を取得する
int avatarTranstexhterJsonCore::getPose(String poseKey, String jointKey, int value){
  return true;
}

// ポーズタイプを取得する
poseType avatarTranstexhterJsonCore::getPoseType(String poseKey){
  return POSE;
}

// ポーズの総数と全キーを返す
int avatarTranstexhterJsonCore::wholePose(String* poseKeys){
  return 0;
}

// ポーズを追加する
void avatarTranstexhterJsonCore::addPose(String poseKey, poseType type){

}

// ポーズを削除する
void avatarTranstexhterJsonCore::removePose(String poseKey){

}

// モーションの有無
bool avatarTranstexhterJsonCore::isMotion(String motionKey){
  return true;
}

// モーション情報をセットする
bool avatarTranstexhterJsonCore::setMotion(String motionKey, int index, String poseName, int moveTime, int eyeType, int blinkEyeTime, int mouthType, int blinkMotuTime){
  return true;
}

// モーション名を取得する
String avatarTranstexhterJsonCore::getMotionName(String motionKey, int index){
  return "";
}

// モーション稼働時間を取得する
int avatarTranstexhterJsonCore::getMotionMoveTime(String motionKey, int index){
  return 0;
}

// 実行アイモーションを取得する
int avatarTranstexhterJsonCore::getMotionEyeType(String motionKey, int index){
  return 0;
}

// 瞬き実行周期時間を取得する
int avatarTranstexhterJsonCore::getMotionEyeBlinkTime(String motionKey, int index){
  return 0;
}

// 実行マウスモーションを取得する
int avatarTranstexhterJsonCore::getMotionMouthType(String motionKey, int index){
  return 0;
}

// 口パク実行周期時間を取得する
int avatarTranstexhterJsonCore::getMotionMouthBlinkTime(String motionKey, int index){
  return 0;
}

// モーションのポーズ総数を取得する
int avatarTranstexhterJsonCore::getMotionIndexes(String motionKey){
  return 0;
}

// モーション総数と全モーション名を取得する
int avatarTranstexhterJsonCore::wholeMotion(String* motionKeys){
  return 0;
}

// モーションを追加する
bool avatarTranstexhterJsonCore::addMotion(String motionKey, String startPose, String finishPose, int eyeType, int blinkEyeTime, int mouthType, int blinkMouthTime){
  return true;
}

bool avatarTranstexhterJsonCore::addMotion(String motionKey, String startPose, int eyeType, int blinkEyeTime, int mouthType, int blinkMouthTime){
  return addMotion(motionKey, startPose, startPose, eyeType, blinkEyeTime, mouthType, blinkMouthTime);
}

// モーションを削除する
void removeMotion(String motionKey){

}

// JSONファイル作成
void avatarTranstexhterJsonCore::initJson(){
  // リセット
  saveJsonDoc.clear();
  // 型作成
  saveJsonDoc[POSE_KEY].to<JsonArray>();
  saveJsonDoc[MOTION_KEY].to<JsonArray>();
  // ポーズ情報
  JsonArray poseArray = saveJsonDoc[POSE_KEY];
  JsonObject poseNameObj = poseArray.add<JsonObject>();
  poseNameObj[POSE_NAME_KEY] = "root";
  JsonObject poseValueObj = poseNameObj[POSE_VALUE_KEY].to<JsonObject>();
  for(int i=0;i<JOINT_TOTAL;i++){
    poseValueObj[jointKeys[i]] = 0;
  }
  poseValueObj[MOTION_TYPE_KEY] = ROOT;
  // モーション情報
  JsonArray motionArray = saveJsonDoc[MOTION_KEY];
  JsonObject motionNameObj = motionArray.add<JsonObject>();
  motionNameObj[MOTION_NAME_KEY] = "init";
  JsonObject motionValueObj = motionNameObj[MOTION_ARRAY_KEY].to<JsonObject>();
  for(int i=0;i<2;i++){
    motionValueObj[MOTION_POSE_KEY] = "root";
    motionValueObj[MOVE_TIME_KEY] = 0;
    motionValueObj[EYE_TYPE_KEY] = 0;
    motionValueObj[BLINK_EYE_KEY] = 1000;
    motionValueObj[MOUTH_TYPE_KEY] = 0;
    motionValueObj[BLINK_MOUTH_KEY] = 1000;
  }
}