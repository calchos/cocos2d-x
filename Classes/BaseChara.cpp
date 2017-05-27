#include "BaseChara.hpp"

bool BaseChara::init(){
    return true;
}

cocos2d::Label* BaseChara::createHpLabel(){
    if(_hpLabel != nullptr){
        _hpLabel->removeFromParent();
    }
    
    _hpLabel = cocos2d::Label::createWithTTF(std::to_string(_hp), "fonts/ヒラギノ明朝 ProN W3.ttc" , 20);
    _hpLabel->setColor(cocos2d::Color3B::BLACK);
    _hpLabel->setPosition(cocos2d::Vec2(_hpLabelPosX, _hpLabelPosY));
    
    return _hpLabel;
}

BaseChara* BaseChara::create(std::string imageFilePath){

    BaseChara* pRet = new BaseChara();
    if(pRet && pRet->initWithFile(imageFilePath) && pRet->init()){
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }

}

