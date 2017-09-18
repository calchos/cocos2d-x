#ifndef BaseChara_hpp
#define BaseChara_hpp

#include <stdio.h>

class BaseChara : public cocos2d::Sprite{
 
public:
    
    // チャレンジポイント初期値
    int _powerPoint = 0; // POW
    int _dexturePoint = 0; // DEX
    int _intelligencePoint = 0; // INT
    int _charmPoint = 0; // CHA
    int _luckyPoint = 0; // LUK
    
    // クラス生成
    virtual bool init();
    static BaseChara* create(std::string imageFilePath);// スプライト画像生成
 
    
    // 表示
    cocos2d::Label* _hpLabel = nullptr; // HPを表示するラベル
    float _hpLabelPosX; // HPラベルの表示位置X
    float _hpLabelPosY; // HPラベルの表示位置Y
    cocos2d::Label* createHpLabel(); // HPラベルを生成して返却する
    
    bool _doAttack = false; // 攻撃を行っているかどうかを判断するフラグ
    
};

#endif /* BaseChara_hpp */
