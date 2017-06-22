// 重複定義の回避 __OPENING__TITLE_H__は記号定数
#ifndef __OPENING_TITLE_H__
#define __OPENING_TITLE_H__

#include "cocos2d.h" // cocos2d.hインクルード
#include "BaseChara.hpp"// BaseChara.hppインクルード


class Opening : public cocos2d::Layer // 派生クラス HelloWorld作成
{
    
public:

    // コンストラクタ
    Opening();
    
    // デストラクタ
    virtual ~Opening();
    
    static cocos2d::Scene* createScene(); // publicでcreateScene()を継承
    virtual bool init(); // 仮想関数でオーバーライド
    
    // バトル画面(ステージ2)に遷移
    void nextSceneCallback(cocos2d::Ref* pSender);

    
    // implement the "static create()" method manually インターフェース
    CREATE_FUNC(Opening);
    
    // キャラクター関連
    BaseChara* _character1;
    BaseChara* _character2;
    BaseChara* _character3;
    BaseChara* _character4;
    

};

#endif // __OPENING_TITLE_H__
