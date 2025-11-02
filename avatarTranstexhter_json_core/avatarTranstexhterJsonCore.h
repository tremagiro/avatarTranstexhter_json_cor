#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

// ジョイントの総数
#define JOINT_TOTAL 15
// ポーズの種類
enum poseType{ROOT, STATE, POSE, NONE};
// ジョイントのキー
static const String jointKeys[JOINT_TOTAL] = {
  "right-shoulder-roll",
  "right-shoulder-pitch",
  "right-elbow-pitch",
  "body-lift",
  "right-foot-yaw",
  "right-foot-roll",
  "body-pitch",
  "left-foot-roll",
  "left-foot-yaw",
  "backpack-pitch",
  "left-elbow-pitch",
  "left-shoulder-pitch",
  "left-shoulder-roll",
  "right-motor-speed",
  "left-motor-speed"
};

class avatarTranstexhterJsonCore{
  private:
    JsonObject saveJson;
  public:
    // saveJsonへオブジェクトを渡す
    int setJsonObject(JsonObject saveJsonObject, String* errorKey);
    // 持っているJsonオブジェクトを渡す
    JsonObject getJsonObject();
    // ポーズの有無
    bool isPose(String poseKey);
    // ポーズ情報を追加・上書きする
    bool setPose(String poseKey, String jointKey, int value);
    // ポーズタイプを追加・上書きする
    bool setPoseType(String poseKey, poseType value);
    // ポーズ情報を取得する
    int getPose(String poseKey, String jointKey, int value);
    // ポーズタイプを取得する
    poseType getPoseType(String poseKey);
    // ポーズの総数と全キーを返す
    int wholePose(String* poseKeys);
    // ポーズを追加する
    void addPose(String poseKey, poseType type = POSE);
    // ポーズを削除する
    void removePose(String poseKey);
    // モーションの有無
    bool isMotion(String motionKey);
    // モーション情報をセットする
    bool setMotion(String motionKey, int index, String poseName, int moveTime, int eyeType, int blinkEyeTime, int mouthType, int blinkMotuTime);
    // モーション名を取得する
    String getMotionName(String motionKey, int index);
    // モーション稼働時間を取得する
    int getMotionMoveTime(String motionKey, int index);
    // 実行アイモーションを取得する
    int getMotionEyeType(String motionKey, int index);
    // 瞬き実行周期時間を取得する
    int getMotionEyeBlinkTime(String motionKey, int index);
    // 実行マウスモーションを取得する
    int getMotionMouthType(String motionKey, int index);
    // 口パク実行周期時間を取得する
    int getMotionMouthBlinkTime(String motionKey, int index);
    // モーションのポーズ総数を取得する
    int getMotionIndexes(String motionKey);
    // モーション総数と全モーション名を取得する
    int wholeMotion(String* motionKeys);
    // モーションを追加する
    bool addMotion(String motionKey, String startPose, String finishPose, int eyeType, int blinkEyeTime, int mouthType, int blinkMouthTime);
    bool addMotion(String motionKey, String startPose, int eyeType, int blinkEyeTime, int mouthType, int blinkMouthTime);
    // モーションを削除する
    void removeMotion(String motionKey);
};