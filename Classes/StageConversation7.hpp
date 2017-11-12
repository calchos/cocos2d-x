#ifndef StageConversation7_hpp
#define StageConversation7_hpp


#include <stdio.h>


#include "cocos2d.h" // cocos2d.hインクルード
#include "BaseChara.hpp"// BaseChara.hppインクルード

class StageConversation7 : public cocos2d::Layer // 派生クラス HelloWorld作成
{
    
public:
    
    static cocos2d::Scene* createScene(); // publicでcreateScene()を継承
    virtual bool init(); // 仮想関数でオーバーライド
    
    // ステージ4に遷移
    void nextSceneCallback(cocos2d::Ref* pSender);
        
    // implement the "static create()" method manually インターフェース
    CREATE_FUNC(StageConversation7);
    
    // キャラクター関連
    BaseChara* _character1;
    BaseChara* _character2;
    BaseChara* _character3;
    BaseChara* _character4;
    
    // 敵キャラクター
    BaseChara* _enemy;
    
    
};


#endif /* StageConversation7_hpp */
