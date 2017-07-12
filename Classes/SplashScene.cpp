#include "SplashScene.h"
#include "OpeningTitle.h"

cocos2d::Scene *SplashScene::createScene(){
    auto scene = cocos2d::Scene::create();
    auto layer = SplashScene::create();
    scene->addChild(layer);
    return scene;
}

bool SplashScene::init(){
    
    if (! Layer::init()) {
        return false;
    }
    
    // 画面サイズを取得
    cocos2d::Size winSize = cocos2d::Director::getInstance()->getWinSize();
    cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    
    //背景
    auto background = cocos2d::Sprite::create("HelloWorld.png");
    
    //中央に表示されるように座標を設定
    background->setPosition(cocos2d::Point(winSize.width /2 ,winSize.height/2));
    this->addChild(background, 0);
    
    // タイトル画面に画面遷移する
    this->scheduleOnce(schedule_selector(SplashScene::changeTitleScene),2.0f);
    
    return true;
}

void SplashScene::changeTitleScene(float millsecond){
    
    //画面遷移する。
    auto scene = Opening::createScene();
    
    // 0.5秒かけてホワイトアウトしてタイトルに移動する
    cocos2d::TransitionFade* fade = cocos2d::TransitionFade::create(0.5f, scene, cocos2d::Color3B::WHITE);
    
    //SplashSceneを破棄してTopSceneに遷移する
    cocos2d::Director::getInstance()->replaceScene(fade);
}
