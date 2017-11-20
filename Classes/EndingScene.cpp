#pragma execution_character_set("utf-8") // 文字コード指定
#include "EndingConversation.hpp"
#include "EndingScene.h"
#include "ui/UIVideoPlayer.h"


USING_NS_CC; // #define USING_NS_CC using namespace cocos2d

Scene* EndingScene::createScene() // シーン生成処理
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = EndingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EndingScene::init() // 初期化処理
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // 画面サイズ指定
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    Director::getInstance()->setDisplayStats(false); // stats OFF*
    
    auto videoPlayer = cocos2d::experimental::ui::VideoPlayer::create();
    videoPlayer->setContentSize(visibleSize);
    videoPlayer->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    videoPlayer->setFullScreenEnabled(true);
    videoPlayer->setFileName("test_movie.mp4");
    videoPlayer->play();
    this->addChild(videoPlayer);
    
    return true;
    
}


