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
    bool _gameEvent = false; // 勝利イベント・敗北イベントを一回のみ実行するフラグ
    
    void update(float delta);// 更新処理定義
    
    int playerAttack();// プレイヤーキャラクターのトータルダメージ数
    int playerPredefense();// プレイヤーキャラクターの先制防御
    
    int enemyPreemptiveAttack();// 敵キャラクターの先制攻撃
    int enemyAttack();// 敵キャラクターのトータルダメージ数
    int m,r; // 乱数用の変数
    
    bool _preemptive_attack; // 敵の先制攻撃フラグ
    
    // タッチ処理
    virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);// タッチしたときに1回だけ実行する処理
    
    
    // implement the "static create()" method manually インターフェース
    CREATE_FUNC(StageScene);
    
    // キャラクター関連
    BaseChara* _character1;
    BaseChara* _character2;
    BaseChara* _character3;
    BaseChara* _character4;
    
    // 敵キャラクター
    BaseChara* _enemy1;
    BaseChara* _enemy2;
    
};

#endif // __HELLOWORLD_SCENE_H__
