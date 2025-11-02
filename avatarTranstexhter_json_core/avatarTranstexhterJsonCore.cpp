#include "avatarTranstexhterJsonCore.h"

// saveJsonへオブジェクトを渡す
int avatarTranstexhterJsonCore::setJsonObject(JsonObject saveJsonObject, String* errorKey){
  return 0;
}

// 持っているJsonオブジェクトを渡す
JsonObject avatarTranstexhterJsonCore::getJsonObject(){
  return saveJson;
}

// ポーズの有無
bool avatarTranstexhterJsonCore::isPose(String poseKey){
  return true;
}

// ポーズ情報を追加・上書きする
bool avatarTranstexhterJsonCore::setPose(String poseKey, String jointKey, int value){
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