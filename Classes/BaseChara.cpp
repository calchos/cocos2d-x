#include "BaseChara.hpp"// BaseChara.hpp読み込み

// 初期化処理
bool BaseChara::init(){
    return true;
}

// HPラベル生成処理
cocos2d::Label* BaseChara::createHpLabel(){
    // _hpLabelがヌルではないとき
    if(_hpLabel != nullptr){
        // _hpLabelの子スプライトを削除
        _hpLabel->removeFromParent();
    }
    // HPラベルを文字列に変換
    //_hpLabel = cocos2d::Label::createWithTTF(std::to_string(_hp), "fonts/ヒラギノ明朝 ProN W3.ttc" , 20);
    // 色指定
    _hpLabel->setColor(cocos2d::Color3B::BLACK);
    // 位置指定
    _hpLabel->setPosition(cocos2d::Vec2(_hpLabelPosX, _hpLabelPosY));
    // _hpLabelにリターン
    return _hpLabel;
}

// createメソッド
BaseChara* BaseChara::create(std::string imageFilePath){

    // BaseCharaを生成してポインタpRetに格納
    BaseChara* pRet = new BaseChara();
    // pRetが存在しかつファイルが存在しかつ初期化処理が行えるとき
    if(pRet && pRet->initWithFile(imageFilePath) && pRet->init()){
        // オブジェクト自動破棄
        pRet->autorelease();
        // pRetリターン
        return pRet;
    } else {
        // 削除したいオブジェクトを安全に削除
        CC_SAFE_DELETE(pRet);
        // nullptrにリターン
        return nullptr;
    }

}

