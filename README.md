# AvatarTranstexhter_json_core
アバタートランステクターの保存形式や取得、書き込み手段を提供するライブラリ。
## JSON構造
### 全体構造
```
{
    "pose": [ポーズ情報...]、
    "motion": [モーション情報...]
}
```
### ポーズ情報
```
{
    "poseName": ポーズ名(String)
    "poseValue": 各関節の値
}
```
### 各関節の値
```
{
    "right-shoulder-roll": 右肩ロール軸動作角度(int: [°]),
    "right-shoulder-pitch": 右肩ピッチ軸動作角度(int: [°]),
    "right-elbow-pitch": 右肘ピッチ軸動作角度(int: [°]),
    "body-lift": ステッピングモーター回転角度(int: [step]),
    "right-foot-yaw": 右足ヨー軸動作角度(int: [°]),
    "right-foot-roll": 右足ロール軸動作角度(int: [°]),
    "body-pitch": ボディピッチ軸動作角度(int: [°]),
    "left-foot-roll": 左足ロール軸動作角度(int: [°]),
    "left-foot-yaw": 左足ヨー軸動作角度(int: [°]),
    "backpack-pitch": バックパックピッチ軸動作角度(int: [°]),
    "left-elbow-pitch": 左肘ピッチ軸動作角度(int: [°]),
    "left-shoulder-pitch": 左肩ピッチ軸動作角度(int: [°]),
    "left-shoulder-roll":　左肩ロール軸動作角度(int: [°]),
    "right-motor-speed": 右モーター回転速度(int: ),
    "left-motor-speed": 左モーター回転速度(int: ),
    "poseType": ポーズタイプ(enum poseType: ROOT or STATE or POSE or NONE)
}
```
### モーション情報
```
{
    "motionName": モーション名(String),
    "motionArray": [動作情報...]
}
```
### 動作情報
```
{
    "motionPose": ポーズ名(String),
    "moveTime": 稼働時間(int: [ms]),
    "eyeType": 実行アイモーション(int),
    "blinkEyeTime": 瞬き実行周期(int: [ms]),
    "mouthType": 実行マウスモーション(int),
    "blinkMouthTime": 口パク実行周期(int: [ms])
}
```
## メソッド
### setJsonDocument
インスタンスにJSONオブジェクトを渡すと保持する。
```
void isMatchTemplate(JsonDocument saveJsonDocument)
```
### getJsonDocument
インスタンスで保持しているJSONオブジェクトを渡す。
```
JsonDocument getJsonDocument()
```
### isPose
指定したポーズ名の情報があるかどうかを判定する。
```
bool isPose(String poseKey)
```
### setPose
ポーズ情報をインスタンスに保持するJSONオブジェクトに追加する。もし指定したポーズ名がある場合は指定した関節キーの値を上書きする。該当するポーズ名がない場合は新たにポーズ情報を追加する。追加するポーズ情報のポーズタイプは「POSE」である。指定した関節キーが存在しない場合はfalseを返す。
```
bool setPose(String poseKey, String jointKey, int value)
```
### setPoseType
ポーズタイプをインスタンスに保持するJSONオブジェクトに追加する。もし指定したポーズ名がある場合は指定したポーズタイプの値を上書きする。該当するポーズ名がない場合は新たにポーズ情報を追加する。指定した関節キーが存在しない場合はfalseを返す。またvalueに「ROOT」を渡した場合、元の「ROOT」を保持していたポーズは「STATE」に書き換わる。
```
bool setPoseType(String poseKey, poseType value)
```
### getPose
指定したポーズの値を返す。指定したポーズに該当がない場合は「0」を返す。
```
int getPose(String poseKey, String jointKey, int value)
```
### getPoseType
指定したポーズタイプの値を返す。指定したポーズが該当しない場合は「NONE」を返す。
```
poseType getPoseType(String poseKey)
```
### wholePose
インスタンスが保持する全ポーズ数を返す。また、渡したString型ポインタに全ポーズ名を渡す。
```
int wholePose(String* poseKeys)
```
### addPose
ポーズを追加する。
```
void addPose(String poseKey, poseType type = POSE) 
```
### removePose
指定したポーズを削除する。
```
void removePose(String poseKey)
```

### isMotion
指定したモーション名の情報があるかどうかを判定する。
```
bool isMotion(String motionKey)
```
### setMotion
モーション情報をインスタンスに保持するJSONオブジェクトに追加する。もし指定したモーション名がある場合は指定した関節キーの値を上書きする。該当するポーズ名がない場合、渡したポーズタイプが「POSE」でない場合はfalseを返す。また、indexで指定した箇所にモーション情報が追加される。もしindexが指定したモーション数より超過した数を代入した場合は、配列の最後尾より一つ前に追加される。
```
bool setMotion(String motionKey, int index, String poseName, int moveTime, int eyeType, int blinkEyeTime, int mouthType, int blinkMotuTime)
```
### getMotionName
指定したモーションのポーズ名を返す。指定したモーションが該当しない場合は「””」を返す。
```
String getMotionName(String motionKey, int index)
```
### getMotionMoveTime
指定したモーションの稼働時間を返す。指定したモーションが該当しない場合は「0」を返す。
```
int getMotionMoveTime(String motionKey, int index)
```
### getMotionEyeType
指定したモーションの実行アイモーションを返す。指定したモーションが該当しない場合は「0」を返す。
```
int getMotionEyeType(String motionKey, int index)
```
### getMotionEyeBlinkTime
指定したモーションの瞬き周期時間を返す。指定したモーションが該当しない場合は「0」を返す。
```
int getMotionEyeBlinkTime(String motionKey, int index)
```
### getMotionMouthType
指定したモーションの実行マウスモーションを返す。指定したモーションが該当しない場合は「0」を返す。
```
int getMotionMouthType(String motionKey, int index)
```
### getMotionMouthBlinkTime
指定したモーションの口パク周期時間を返す。指定したモーションが該当しない場合は「0」を返す。
```
int getMotionMouthBlinkTime(String motionKey, int index)
```
### getMotionIndexes
指定したモーションの配列数を返す。
```
int getMotionIndexes(String motionKey)
```
### wholeMotion
インスタンスが保持する全モーション数を返す。また、渡したString型ポインタに全モーション名を渡す。
```
int wholeMotion(String* motionKeys)
```
### addMotion
モーションを追加する。startPoseおよびfinishPoseのポーズタイプが「POSE」の場合はfalseを返し、モーション追加を行わない。finishPoseの記載がない場合はfinishPose=startPoseと追加する。
```
bool addMotion(String motionKey, String startPose, String finishPose, int eyeType, int blinkEyeTime, int mouthType, int blinkMouthTime) 
bool addMotion(String motionKey, String startPose, int eyeType, int blinkEyeTime, int mouthType, int blinkMouthTime) 
```
### removeMotion
指定したをモーション削除する。
```
void removeMotion(String motionKey)
```
