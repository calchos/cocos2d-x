// 重複定義の回避 __HELLOWORLD_SCENE_H__は記号定数
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h" // cocos2d.hインクルード
#include "BaseChara.hpp"// BaseChara.hppインクルード


class Opening : public cocos2d::Layer // 派生クラス HelloWorld作成
{
    
public:
    static cocos2d::Scene* createScene(); // publicでcreateScene()を継承
    virtual bool init(); // 仮想関数でオーバーライド
    
    
    //void update(float delta);// 更新処理定義
    
    // タッチ処理
    virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);// タッチしたときに1回だけ実行する処理
    
    
    // implement the "static create()" method manually インターフェース
    CREATE_FUNC(Opening);
    
    // キャラクター関連
    BaseChara* _character1;
    BaseChara* _character2;
    BaseChara* _character3;
    BaseChara* _character4;
    

};

#endif // __HELLOWORLD_SCENE_H__
