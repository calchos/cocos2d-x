#ifndef BaseChara_hpp
#define BaseChara_hpp

#include <stdio.h>

class BaseChara : public cocos2d::Sprite{
 
public:
    
    int _hp = 0; // HP
    int _attackPoint = 0; // 攻撃力
    
    // クラス生成
    virtual bool init();
    static BaseChara* create(std::string imageFilePath);// スプライト画像生成
 
    
    // HP表示
    cocos2d::Label* _hpLabel = nullptr; // HPを表示するラベル
    float _hpLabelPosX; // HPラベルの表示位置X
    float _hpLabelPosY; // HPラベルの表示位置Y
    cocos2d::Label* createHpLabel(); // HPラベルを生成して返却する
    
    bool _doAttack = false; // 攻撃を行っているかどうかを判断するフラグ
};

#endif /* BaseChara_hpp */
