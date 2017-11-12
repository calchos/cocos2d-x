#ifndef StageConversation5_hpp
#define StageConversation5_hpp


#include <stdio.h>


#include "cocos2d.h" // cocos2d.hインクルード
#include "BaseChara.hpp"// BaseChara.hppインクルード

class StageConversation5 : public cocos2d::Layer // 派生クラス HelloWorld作成
{
    
public:
    
    static cocos2d::Scene* createScene(); // publicでcreateScene()を継承
    virtual bool init(); // 仮想関数でオーバーライド
    
    // バトル画面(ステージ3)に遷移
    void nextSceneCallback(cocos2d::Ref* pSender);
    
    // タッチ処理
    virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);// タップしたときに1回だけ実行する処理
    
    // implement the "static create()" method manually インターフェース
    CREATE_FUNC(StageConversation5);
    
    // キャラクター関連
    BaseChara* _character1;
    BaseChara* _character2;
    BaseChara* _character3;
    BaseChara* _character4;
    
    // 敵キャラクター
    BaseChara* _enemy1;
    
    
};


#endif /* StageConversation5_hpp */
