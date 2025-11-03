#include "avatarTranstexhterJsonCore.h"

// saveJsonへオブジェクトを渡す
void avatarTranstexhterJsonCore::setJsonDocument(JsonDocument saveJsonObject){
  saveJsonDoc = saveJsonObject;
}

// 持っているJsonオブジェクトを渡す
JsonDocument avatarTranstexhterJsonCore::getJsonDocument(){
  return saveJsonDoc;
}

// ポーズの有無
bool avatarTranstexhterJsonCore::isPose(String poseKey){
  JsonObject obj;
  return getPoseJson(poseKey, &obj);
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
    addPoseJson(poseKey, POSE);
  }
  // 指定のキーの値を更新
  JsonObject updateJsonObj;
  if(getJointJson(poseKey, &updateJsonObj) == true){
    updateJsonObj[jointKey] = value;
    return true;
  }else{
    return false;
  }
}

// ポーズタイプを追加・上書きする
bool avatarTranstexhterJsonCore::setPoseType(String poseKey, poseType value){
  // 指定のポーズは存在するか
  if(isPose(poseKey) == false){
    // 新規作成
    addPoseJson(poseKey, POSE);
  }
  // 指定のキーの値を更新
  JsonObject updateJsonObj;
  if(getJointJson(poseKey, &updateJsonObj) == true){
    if(value == ROOT){
      // ROOTは重複させない
      std::vector<String> poseKeys;
      int max = wholePose(poseKeys);
      for(const String& key : poseKeys){
        if(getPoseType(key) == ROOT){
          setPoseType(key, POSE);
        }
      }
    }
    updateJsonObj[POSE_TYPE_KEY] = value;
    return true;
  }else{
    return false;
  }
}

// ポーズ情報を取得する
int avatarTranstexhterJsonCore::getPose(String poseKey, String jointKey, int value){
  return true;
}

// ポーズタイプを取得する
poseType avatarTranstexhterJsonCore::getPoseType(String poseKey){
  JsonObject poseObj;
  if (getPoseJson(poseKey, &poseObj) == true){
    JsonObject poseValue = poseObj[POSE_VALUE_KEY].as<JsonObject>();
    return static_cast<poseType>(poseValue[POSE_TYPE_KEY].as<int>());
  }
  return NONE;
}

// ポーズの総数と全キーを返す
int avatarTranstexhterJsonCore::wholePose(std::vector<String>& poseKeys){
  JsonArray poseArray = saveJsonDoc[POSE_KEY];
  for(JsonObject poseObj : poseArray){
    poseKeys.push_back(poseObj[POSE_NAME_KEY].as<String>());
  }
  return poseKeys.size();
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
int avatarTranstexhterJsonCore::wholeMotion(std::vector<String>& motionKeys){
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
  addPoseJson("root", ROOT);
  // モーション情報
  addMotionJson("initMotion", "root", 0, 0, 0, 0);
}

// ポーズの追加
void avatarTranstexhterJsonCore::addPoseJson(String poseeName, poseType type){
  // ポーズ情報
  JsonArray poseArray = saveJsonDoc[POSE_KEY];
  JsonObject poseNameObj = poseArray.add<JsonObject>();
  poseNameObj[POSE_NAME_KEY] = poseeName;
  JsonObject poseValueObj = poseNameObj[POSE_VALUE_KEY].to<JsonObject>();
  for(int i=0;i<JOINT_TOTAL;i++){
    poseValueObj[jointKeys[i]] = 0;
  }
  poseValueObj[POSE_TYPE_KEY] = type;
}

// モーションの追加
void avatarTranstexhterJsonCore::addMotionJson(String motionKey, String startPose, int eyeType, int blinkEyeTime, int mouthType, int blinkMouthTime){
  JsonArray motionArray = saveJsonDoc[MOTION_KEY];
  JsonObject motionNameObj = motionArray.add<JsonObject>();
  motionNameObj[MOTION_NAME_KEY] = motionKey;
  JsonObject motionValueObj = motionNameObj[MOTION_ARRAY_KEY].to<JsonObject>();
  for(int i=0;i<2;i++){
    motionValueObj[MOTION_POSE_KEY] = startPose;
    motionValueObj[MOVE_TIME_KEY] = 0;
    motionValueObj[EYE_TYPE_KEY] = eyeType;
    motionValueObj[BLINK_EYE_KEY] = blinkEyeTime;
    motionValueObj[MOUTH_TYPE_KEY] = mouthType;
    motionValueObj[BLINK_MOUTH_KEY] = blinkMouthTime;
  }
}

// ポーズの編集対象を渡す
bool avatarTranstexhterJsonCore::getPoseJson(String poseKey, JsonObject* obj){
  JsonArray poseArray = saveJsonDoc[POSE_KEY];
  for(JsonObject poseObj : poseArray){
    if(poseObj[POSE_NAME_KEY].as<String>() == poseKey){
      *obj = poseObj;
      return true;
    }
  }
  return false;
}

// ジョイントの編集対象を渡す
bool avatarTranstexhterJsonCore::getJointJson(String poseKey, JsonObject* obj){
  JsonArray poseArray = saveJsonDoc[POSE_KEY];
  for(JsonObject poseObj : poseArray){
    if(poseObj[POSE_NAME_KEY] == poseKey){
      *obj = poseObj[POSE_VALUE_KEY].as<JsonObject>();
      return true;
    }
  }
  return false;
}