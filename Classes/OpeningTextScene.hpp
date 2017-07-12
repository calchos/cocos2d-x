#ifndef OpeningTextScene_hpp
#define OpeningTextScene_hpp

#include <stdio.h>

class OpeningText : public cocos2d::Layer // 派生クラス HelloWorld作成
{
    
public:
    
    static cocos2d::Scene* createScene(); // publicでcreateScene()を継承
    virtual bool init(); // 仮想関数でオーバーライド
    
    // オープニングテキストに遷移するためのコールバック関数
    void nextSceneCallback(cocos2d::Ref* pSender);
    
    
    // implement the "static create()" method manually インターフェース
    CREATE_FUNC(OpeningText);
    
};


#endif /* OpeningTextScene_hpp */
