#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "BaseChara.hpp"

class HelloWorld : public cocos2d::Layer
{
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    // ゲームの状態遷移を列挙型で持たせる
    enum State{
        TYPE_PLAYER_TURN, // プレイヤーのターン
        TYPE_ENEMY_TURN, // 敵のターン
        TYPE_WIN, // 勝利イベント
        TYPE_LOSE, // 敗北イベント
    };
    
    State _state = TYPE_PLAYER_TURN; // 最初はプレイヤーのターンから開始
    bool _gameEvent = false; // 勝利イベント・敗北イベントを一回のみ実行するフラグ
    
    void update(float delta);// 更新処理定義
    
    // タッチ処理
    virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);// タッチしたときに1回だけ実行する処理
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
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
