# AvatarTranstexhter_json_core
アバタートランステクターの保存形式や取得、書き込み手段を提供するライブラリ。
## JSON構造
### 全体構造
```
{
    pose: ポーズ情報、
    motion: モーション情報
}
```
### ポーズ情報
```
{
    (String: ポーズ名): 各関節の値,
    poseType: ポーズタイプ(typedef poseType: ROOT or STATE or POSE)
}
```
### 各関節の値
```
{
    "right-shoulder-roll": 右肩ロール軸動作角度(int: [°]),
    "right-sholder-pitch": 右肩ピッチ軸動作角度(int: [°]),
    "right-elbow-pitch": 右肘ピッチ軸動作角度(int: [°]),
    "body-lift": ステッピングモーター回転角度(int: [step]),
    "right-foot-yaw": 右足ヨー軸動作角度(int: [°]),
    "right-foot-roll": 右足ロール軸動作角度(int: [°]),
    "body-pitch": ボディピッチ軸動作角度(int: [°]),
    "left-foot-roll": 左足ロール軸動作角度(int: [°]),
    "left-foot-yaw": 左足ヨー軸動作角度(int: [°]),
    "backpack-pitch": バックパックピッチ軸動作角度(int: [°]),
    "left-elbow-pitch": 左肘ピッチ軸動作角度(int: [°]),
    "left-sholder-pitch": 左肩ピッチ軸動作角度(int: [°]),
    "left-sholder-roll":　左肩ロール軸動作角度(int: [°]),
    "right-motor-speed": 右モーター回転速度(int: ),
    "left-motor-speed": 左モーター回転速度(int: )
}
```
### モーション情報
```
{
    startState: ポーズ名(String),
    motionArray: [動作情報...],
    finishState: ポーズ名(String)
}
```
### 動作情報
```
{
    startState: ポーズ名(String),
    moveTime: 稼働時間(int: [ms]),
    eyeType: 実行アイモーション(int),
    blinkEyeTime: 瞬き実行周期(int: [ms]),
    mouthType: 実行マウスモーション(int),
    blinkMouthTime: 口パク実行周期(int: [ms])
}
```
## メソッド