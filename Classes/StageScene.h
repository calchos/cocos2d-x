// 重複定義の回避 __HELLOWORLD_SCENE_H__は記号定数
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h" // cocos2d.hインクルード
#include "BaseChara.hpp"// BaseChara.hppインクルード


class StageScene : public cocos2d::Layer // 派生クラス HelloWorld作成
{
    
public:
    static cocos2d::Scene* createScene(); // publicでcreateScene()を継承
    virtual bool init(); // 仮想関数でオーバーライド
    
    // ゲームの状態遷移をenum(列挙型)で持たせる
    enum State{
        TYPE_PLAYER_TURN, // プレイヤーのターン
        TYPE_ENEMY_TURN, // 敵のターン
        TYPE_WIN, // 勝利イベント
        TYPE_LOSE, // 敗北イベント
    };
    
    State _state = TYPE_PLAYER_TURN; // 最初はプレイヤーのターンから開始
    bool _gameEndEvent = false; // 勝利イベント・敗北イベントを一回のみ実行するフラグ
    bool _player1Turn = false;// プレイヤー1のターンフラグ
    bool _player2Turn = false;// プレイヤー2のターンフラグ
    bool _player3Turn = false;// プレイヤー3のターンフラグ
    bool _player4Turn = false;// プレイヤー4のターンフラグ
    
    // クリスタル数値(複数メソッドで使うのでグローバルで定義しておく)
    int _crystalPower1;
    int _crystalPower2;
    int _crystalPower3;
    int _crystalPower4;
    int _enemyCrystalPower;
    int playerAttack();// プレイヤーキャラクターのトータルダメージ数
    int enemyAttack();// 敵キャラクターのトータルダメージ数
    
    int playerPredefense();// プレイヤーキャラクターの先制防御
    int enemyPreemptiveAttack();// 敵キャラクターの先制攻撃

    bool _preemptive_attack; // 敵の先制攻撃フラグ
    
    void update(float delta);// 更新処理定義
    
    // 画面タップ処理
    virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);// タップした瞬間に1回だけ実行する処理
    virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);// タップを離した瞬間に1回だけ実行する処理
    
    void intervalDeleteAction(float delta);// 一定時間後に削除する処理
    
    // コンストラクタ
    StageScene();
    
    // デストラクタ
    virtual ~StageScene();
    
    // implement the "static create()" method manually インターフェース
    CREATE_FUNC(StageScene);
    
    // キャラクター関連
    BaseChara* _character1;
    BaseChara* _character2;
    BaseChara* _character3;
    BaseChara* _character4;
    BaseChara* _character5;
    BaseChara* _character6;
    BaseChara* _character7;
    BaseChara* _character8;
    
    // 敵キャラクター
    BaseChara* _enemy1;
    BaseChara* _enemy2;
    
};

#endif // __HELLOWORLD_SCENE_H__
