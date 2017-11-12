#ifndef StageConversation6_hpp
#define StageConversation6_hpp


#include <stdio.h>


#include "cocos2d.h" // cocos2d.hインクルード
#include "BaseChara.hpp"// BaseChara.hppインクルード

class StageConversation6 : public cocos2d::Layer // 派生クラス HelloWorld作成
{
    
public:
    
    static cocos2d::Scene* createScene(); // publicでcreateScene()を継承
    virtual bool init(); // 仮想関数でオーバーライド
    
    // 会話シーン6に遷移
    void nextSceneCallback(cocos2d::Ref* pSender);
    
    // タッチ処理
    // virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);// タップしたときに1回だけ実行する処理
    
    // implement the "static create()" method manually インターフェース
    CREATE_FUNC(StageConversation6);
    
    // キャラクター関連
    BaseChara* _character1;
    BaseChara* _character2;
    BaseChara* _character3;
    BaseChara* _character4;
    BaseChara* _character5;
    
    // 敵キャラクター
    BaseChara* _enemy;
    
    
};


#endif /* StageConversation6_hpp */
