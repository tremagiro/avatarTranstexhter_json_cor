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
          setPoseType(key, STATE);
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
int avatarTranstexhterJsonCore::getPose(String poseKey, String jointKey){
  if(isPose(poseKey) == true){
    JsonObject resultObj;
    getJointJson(poseKey, &resultObj);
    // serializeJsonPretty(resultObj, Serial);
    for(int i=0;i<JOINT_TOTAL;i++){
      if(jointKey.equals(jointKeys[i].c_str()) == true){
        return resultObj[jointKeys[i].c_str()].as<int>();
      }
    }
  }
  return 0;
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
bool avatarTranstexhterJsonCore::addPose(String poseKey, poseType type){
  // 既存のポーズがある場合は追加しない
  if(isPose(poseKey) == false){
    addPoseJson(poseKey, type);
    return true;
  }
  return false;
}

// ポーズを削除する
bool avatarTranstexhterJsonCore::removePose(String poseKey){
  // ポーズが存在するか確認
  if(isPose(poseKey) == true){
    // ROOTではないか確認
    if(getPoseType(poseKey) != ROOT){
      // 削除
      JsonArray poseArray = saveJsonDoc[POSE_KEY];
      for (int i = 0; i < poseArray.size(); i++) {
        JsonObject poseObj = poseArray[i].as<JsonObject>();
        if (poseObj[POSE_NAME_KEY].as<String>() == poseKey) {
          poseArray.remove(i);
          return true;
        }
      }
    }
  }
  return false;
}

// モーションの有無
bool avatarTranstexhterJsonCore::isMotion(String motionKey){
  JsonArray obj;
  return getMotionJson(motionKey, &obj);
}

// モーション情報をセットする
bool avatarTranstexhterJsonCore::setMotion(String motionKey, int index, String poseName, int moveTime, int eyeType, int blinkEyeTime, int mouthType, int blinkMouthTime, String motionNameTurn){
  // JsonObject motionObj;
  // getMotionJson(motionKey, index, &motionObj);
  // serializeJsonPretty(motionObj, Serial);
  // return true;
  // 指定したモーションがあるか確認
  if(isMotion(motionKey) == false){
    return false;
  }
  JsonArray motionArray;
  getMotionJson(motionKey, &motionArray);
  if(index < motionArray.size()){
    // 既存データに上書き
    // 末尾と最初は「STATE」か「ROOT」である必要がある
    if(index == 0 || index == (motionArray.size() - 1)){
      poseType type = getPoseType(poseName);
      if(type != ROOT && type != STATE){
        return false;
      }
    }
    // 上書き
    JsonObject updateMotion;
    getMotionJson(motionKey, index, &updateMotion);
    if(motionNameTurn.equals("") == false){
      updateMotion[MOTION_NAME_TURN_KEY] = motionNameTurn.c_str();
    }
    JsonObject updateObj = updateMotion[MOTION_VALUE_KEY].as<JsonObject>();
    updateObj[MOTION_POSE_KEY] = poseName;
    updateObj[MOVE_TIME_KEY] = moveTime;
    updateObj[EYE_TYPE_KEY] = eyeType;
    updateObj[BLINK_EYE_KEY] = blinkEyeTime;
    updateObj[MOUTH_TYPE_KEY] = mouthType;
    updateObj[BLINK_MOUTH_KEY] = blinkMouthTime;
  }else{
    return false;
  }
  return true;
}

// モーション名を取得する
String avatarTranstexhterJsonCore::getMotionPoseName(String motionKey, int index){
  JsonObject getInfo;
  if(getMotionJson(motionKey, index, &getInfo) == true){
    JsonObject resultObj = getInfo[MOTION_VALUE_KEY].as<JsonObject>();
    return resultObj[MOTION_POSE_KEY].as<String>();
  }else{
    return "";
  }
}

// モーション稼働時間を取得する
int avatarTranstexhterJsonCore::getMotionMoveTime(String motionKey, int index){
  JsonObject getInfo;
  if(getMotionJson(motionKey, index, &getInfo) == true){
    JsonObject resultObj = getInfo[MOTION_VALUE_KEY].as<JsonObject>();
    return resultObj[MOVE_TIME_KEY].as<int>();
  }else{
    return 0;
  }
}

// 実行アイモーションを取得する
int avatarTranstexhterJsonCore::getMotionEyeType(String motionKey, int index){
  JsonObject getInfo;
  if(getMotionJson(motionKey, index, &getInfo) == true){
    JsonObject resultObj = getInfo[MOTION_VALUE_KEY].as<JsonObject>();
    return resultObj[EYE_TYPE_KEY].as<int>();
  }else{
    return 0;
  }
}

// 瞬き実行周期時間を取得する
int avatarTranstexhterJsonCore::getMotionEyeBlinkTime(String motionKey, int index){
  JsonObject getInfo;
  if(getMotionJson(motionKey, index, &getInfo) == true){
    JsonObject resultObj = getInfo[MOTION_VALUE_KEY].as<JsonObject>();
    return resultObj[BLINK_EYE_KEY].as<int>();
  }else{
    return 0;
  }
}

// 実行マウスモーションを取得する
int avatarTranstexhterJsonCore::getMotionMouthType(String motionKey, int index){
  JsonObject getInfo;
  if(getMotionJson(motionKey, index, &getInfo) == true){
    JsonObject resultObj = getInfo[MOTION_VALUE_KEY].as<JsonObject>();
    return resultObj[MOUTH_TYPE_KEY].as<int>();
  }else{
    return 0;
  }
}

// 口パク実行周期時間を取得する
int avatarTranstexhterJsonCore::getMotionMouthBlinkTime(String motionKey, int index){
  JsonObject getInfo;
  if(getMotionJson(motionKey, index, &getInfo) == true){
    JsonObject resultObj = getInfo[MOTION_VALUE_KEY].as<JsonObject>();
    return resultObj[BLINK_MOUTH_KEY].as<int>();
  }else{
    return 0;
  }
}

// モーションのポーズ総数を取得する
int avatarTranstexhterJsonCore::getMotionIndexes(String motionKey){
  JsonArray arrayObj;
  if(getMotionJson(motionKey, &arrayObj) == true){
    return arrayObj.size();
  }
  return 0;
}

// モーション総数と全モーション名を取得する
int avatarTranstexhterJsonCore::wholeMotion(std::vector<String>& motionKeys){
  JsonArray allMotions = saveJsonDoc[MOTION_KEY];
  for(JsonObject motionNameObj : allMotions){
    motionKeys.push_back(motionNameObj[MOTION_NAME_KEY].as<String>());
  }
  return motionKeys.size();
}

// モーションを追加する
bool avatarTranstexhterJsonCore::addMotions(String motionKey, String startPose, String finishPose, int eyeType, int blinkEyeTime, int mouthType, int blinkMouthTime){
  // JSONオブジェクトにモーションを追加
  addMotionJson(motionKey, startPose, eyeType, blinkEyeTime, mouthType, blinkMouthTime);
  // 最後尾のモーションポーズを編集
  setMotion(motionKey, 1, finishPose, getMotionMoveTime(motionKey, 0), eyeType, blinkEyeTime, mouthType, blinkMouthTime);
  return true;
}

bool avatarTranstexhterJsonCore::addMotions(String motionKey, String startPose, int eyeType, int blinkEyeTime, int mouthType, int blinkMouthTime){
  return addMotions(motionKey, startPose, startPose, eyeType, blinkEyeTime, mouthType, blinkMouthTime);
}

bool avatarTranstexhterJsonCore::addMotion(String motionKey, String poseName, int index, int moveTime, int eyeType, int blinkEyeTime, int mouthType, int blinkMouthTime){
  if(isMotion(motionKey) == false){
    return false;
  }
  // indexは現在の総数以上を指定しない
  if(index >= 0 && index <= getMotionIndexes(motionKey)){
    // 末尾と最初は「STATE」か「ROOT」である必要がある
    if(index == 0 || index == (getMotionIndexes(motionKey))){
      poseType type = getPoseType(poseName);
      if(type != ROOT && type != STATE){
        return false;
      }
    }
    // モーションの追加
    JsonArray editMotion;
    getMotionJson(motionKey, &editMotion);
    // 追加
    JsonObject editObj = editMotion.add<JsonObject>();
    JsonObject previousObj;
    for(int i = (editMotion.size() - 1);i > index; i--){
      previousObj = editMotion[i - 1].as<JsonObject>();
      editObj.set(previousObj);
      editObj = editMotion[i - 1].as<JsonObject>();
    }
    String motionNameTurn = motionKey + (String)editMotion.size();
    setMotion(motionKey, index, poseName, moveTime, eyeType, blinkEyeTime, mouthType, blinkMouthTime, motionNameTurn);
  }
  return false;
}

// 指定したインデックスのモーションを削除する
bool avatarTranstexhterJsonCore::removeMotion(String motionKey, int index){
  if(isMotion(motionKey) == true){
    if(index < getMotionIndexes(motionKey)){
      JsonArray editArray;
      getMotionJson(motionKey, &editArray);
      // 先頭・末尾も削除禁止
      if(index != 0 && index != (editArray.size() - 1)){
        editArray.remove(index);
        return true;
      }
    }
  }
  return false;
}

// モーションを削除する
void avatarTranstexhterJsonCore::removeMotions(String motionKey){
  if(isMotion(motionKey) == true){
    JsonArray editMotion = saveJsonDoc[MOTION_KEY].as<JsonArray>();
    for(int i=0;i<editMotion.size();i++){
      if(motionKey.equals(editMotion[i][MOTION_NAME_KEY].as<String>().c_str())){
        editMotion.remove(i);
      }
    }
  }
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
  JsonArray motionsArray = saveJsonDoc[MOTION_KEY];
  JsonObject motionObj = motionsArray.add<JsonObject>();
  motionObj[MOTION_NAME_KEY] = motionKey;
  JsonArray motionStepArray = motionObj[MOTION_ARRAY_KEY].to<JsonArray>();
  // 最初と最後の動作追加
  for(int i=0;i<2;i++){
    JsonObject stepObj = motionStepArray.add<JsonObject>();
    stepObj[MOTION_NAME_TURN_KEY] = motionKey + (String)motionStepArray.size();
    JsonObject motionValue = stepObj[MOTION_VALUE_KEY].to<JsonObject>();
    motionValue[MOTION_POSE_KEY] = startPose;
    motionValue[MOVE_TIME_KEY] = 0;
    motionValue[EYE_TYPE_KEY] = eyeType;
    motionValue[BLINK_EYE_KEY] = 0;
    motionValue[MOUTH_TYPE_KEY] = mouthType;
    motionValue[BLINK_MOUTH_KEY] = 0;
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

// モーションの編集対象を渡す
bool avatarTranstexhterJsonCore::getMotionJson(String motionKey, JsonArray* obj){
  JsonArray poseArray = saveJsonDoc[MOTION_KEY];
  for(JsonObject motionObj : poseArray){
    if(motionObj[MOTION_NAME_KEY].as<String>() == motionKey){
      *obj = motionObj[MOTION_ARRAY_KEY].as<JsonArray>();
      return true;
    }
  }
  return false;
}

bool avatarTranstexhterJsonCore::getMotionJson(String motionKey, int index, JsonObject* obj){
  JsonArray arrayObj ;
  if(getMotionJson(motionKey, &arrayObj) == false){
    return false;
  }else{
    if(index < 0 || index > (arrayObj.size() - 1)){
      return false;
    }
    *obj = arrayObj[index].as<JsonObject>();
    return true;
  }
}