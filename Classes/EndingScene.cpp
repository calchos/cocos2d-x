#pragma execution_character_set("utf-8") // 文字コード指定
#include "SplashScene.h"
#include "EndingConversation.hpp"
#include "EndingScene.h"
#include "ui/UIVideoPlayer.h"


USING_NS_CC; // #define USING_NS_CC using namespace cocos2d
using namespace experimental::ui;
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
    videoPlayer->setPosition(Vec2(visibleSize.width / 2  + origin.x , visibleSize.height / 2 + origin.y));
    videoPlayer->setFullScreenEnabled(true);
    videoPlayer->setKeepAspectRatioEnabled(true);
    videoPlayer->setScale(2.0);
    videoPlayer->addEventListener([](Ref *sender,VideoPlayer::EventType eventType){
        // イベントタイプによって処理分岐
        switch(eventType){
            case VideoPlayer::EventType::PLAYING:
                break;
            case VideoPlayer::EventType::PAUSED:
                break;
            case VideoPlayer::EventType::STOPPED:
                break;
            case VideoPlayer::EventType::COMPLETED:
                Director::getInstance()->replaceScene(TransitionFade::create(1.5
                                                                             , SplashScene::createScene()
                                                                             , Color3B::WHITE));
                break;
            default:
                break;
                
        }

     
    });
    videoPlayer->setFileName("movie/test_movie.mp4");
    videoPlayer->play();
    this->addChild(videoPlayer);
    
    return true;
    
}


