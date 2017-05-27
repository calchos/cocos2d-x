#ifndef BaseChara_h
#define BaseChara_h

// HP表示
cocos2d::Label* _hpLabel = nullptr; // HPを表示するラベル
float _hpLabelPosX; // HPラベルの表示位置X
float _hpLabelPosY; // HPラベルの表示位置Y
cocos2d::Label* createHpLabel(); // HPラベルを生成して返却する

bool _doAttack = false; // 攻撃を行っているかどうかを判断するフラグ

#endif /* BaseChara_h */
