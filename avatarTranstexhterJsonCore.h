#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <vector>

// ジョイントの総数
#define JOINT_TOTAL 17
// JOSNファイルキー
#define POSE_KEY  "pose"
#define MOTION_KEY  "motion"
#define POSE_NAME_KEY  "poseName"
#define POSE_VALUE_KEY  "poseValue"
#define MOTION_NAME_KEY "motionName"
#define POSE_TYPE_KEY "poseType"
#define MOTION_ARRAY_KEY  "motionArrayKey"
#define MOTION_POSE_KEY  "motionPose"
#define MOVE_TIME_KEY  "moveTime"
#define EYE_TYPE_KEY  "eyeType"
#define BLINK_EYE_KEY "blinkEyeTime"
#define MOUTH_TYPE_KEY "mouthType"
#define BLINK_MOUTH_KEY "blinkMouthTime"
#define MOTION_NAME_TURN_KEY "motionNameTurn"
#define MOTION_VALUE_KEY "motionValue"
#define POSE_ENABLE_KEY "Enable"

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
  "right-eye-roll",
  "left-eye-roll",
  "right-motor-speed",
  "left-motor-speed"
};

class avatarTranstexhterJsonCore{
  private:
    JsonDocument saveJsonDoc;
    void initJson();
  public:
    avatarTranstexhterJsonCore(){
      // 初期化
      initJson();
    }
    // saveJsonへオブジェクトを渡す
    void setJsonDocument(JsonDocument saveJsonDocument);
    // 持っているJsonオブジェクトを渡す
    JsonDocument getJsonDocument();
    // ポーズの有無
    bool isPose(String poseKey);
    // ポーズ情報を追加・上書きする
    bool setPose(String poseKey, String jointKey, int value, bool enable = true);
    // ポーズタイプを追加・上書きする
    bool setPoseType(String poseKey, poseType value);
    // ポーズ情報を取得する
    int getPose(String poseKey, String jointKey);
    // ポーズ情報が有効かを取得する
    bool getEnablePose(String poseKey, String jointKey);
    // ポーズタイプを取得する
    poseType getPoseType(String poseKey);
    // ポーズの総数と全キーを返す
    int wholePose(std::vector<String>& poseKeys);
    // ポーズを追加する
    bool addPose(String poseKey, poseType type = POSE);
    // ポーズを削除する
    bool removePose(String poseKey);
    // モーションの有無
    bool isMotion(String motionKey);
    // モーション情報をセットする
    bool setMotion(String motionKey, int index, String poseName, int moveTime, int eyeType, int blinkEyeTime, int mouthType, int blinkMouthTime, String motionNameTurn = "");
    // モーション名を取得する
    String getMotionPoseName(String motionKey, int index);
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
    int wholeMotion(std::vector<String>& motionKeys);
    // モーションを追加する
    bool addMotions(String motionKey, String startPose, String finishPose, int eyeType, int blinkEyeTime, int mouthType, int blinkMouthTime);
    bool addMotions(String motionKey, String startPose, int eyeType, int blinkEyeTime, int mouthType, int blinkMouthTime);
    bool addMotion(String motionKey, String poseName, int index, int moveTime, int eyeType, int blinkEyeTime, int mouthType, int blinkMouthTime);
    // 指定したインデックスのモーションを削除する
    bool removeMotion(String motionKey, int index);
    // モーションを削除する
    void removeMotions(String motionKey);
    // ポーズを追加
    void addPoseJson(String poseeName, poseType type);
    // モーションを追加
    void addMotionJson(String motionKey, String startPose, int eyeType, int blinkEyeTime, int mouthType, int blinkMouthTime);
    // ポーズの編集対象を渡す
    bool getPoseJson(String poseKey, JsonObject* obj);
    // 関節の編集対象を渡す
    bool getJointJson(String poseKey, JsonObject* obj);
    // モーションの編集対象を渡す
    bool getMotionJson(String motionKey, JsonArray* obj);
    // 指定モーションインデックスの編集対象を渡す
    bool getMotionJson(String motionKey, int index, JsonObject* obj);
};