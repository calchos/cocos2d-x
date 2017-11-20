#ifndef EndingConversation_h
#define EndingConversation_h


#include <stdio.h>


#include "cocos2d.h" // cocos2d.hインクルード
#include "BaseChara.hpp"// BaseChara.hppインクルード

class EndingScene : public cocos2d::Layer // 派生クラス HelloWorld作成
{
    
public:
    
    static cocos2d::Scene* createScene(); // publicでcreateScene()を継承
    virtual bool init(); // 仮想関数でオーバーライド
    
    // EndingSceneに遷移
    void nextSceneCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually インターフェース
    CREATE_FUNC(EndingScene);

    
    
};


#endif /* EndingScene_h */
