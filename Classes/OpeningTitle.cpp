#pragma execution_character_set("utf-8") // 文字コード指定
#include "OpeningTitle.h" // BattleScene.h 読み込み
#include "SimpleAudioEngine.h"// SimpleAudioEngine.h 読み込み

USING_NS_CC; // #define USING_NS_CC using namespace cocos2d

Scene* Opening::createScene() //
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Opening::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Opening::init()
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
    
    
    // タップイベントを取得する
    auto listener = EventListenerTouchOneByOne::create();// シングルタッチ
    listener->onTouchBegan = CC_CALLBACK_2(Opening::onTouchBegan, this);//タッチしたときに1回だけ処理を実行
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);// イベントリスナーの組み込み
    
    // チョコさんスプライト表示
    _character1 = BaseChara::create("res/chocoto.png");// スプライト画像読み込み
    _character1->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
    _character1->setPosition(Vec2(origin.x + 150, origin.y + visibleSize.height / 2 + 300));// 位置指定
    _character1->setScale(2.0);// スプライトの拡大率を2.0倍に指定
    this->addChild(_character1,1);// 画面描画
    

    // 真紅さんスプライト表示
    _character2 = BaseChara::create("res/sinku.png");
    _character2->setAnchorPoint(Vec2(1.0,1.0));
    _character2->setPosition(Vec2(origin.x + 170, origin.y + visibleSize.height / 2 - 8));
    _character2->setScale(2.0);
    this->addChild(_character2,1);
    
    // しーやさんスプライト表示
    _character3 = BaseChara::create("res/syiya.png");
    _character3->setAnchorPoint(Vec2(1.0,1.0));
    _character3->setPosition(Vec2(origin.x + 600, origin.y + visibleSize.height / 2 - 20));
    _character3->setScale(2.0);
    this->addChild(_character3,1);
    
    // ミラさんスプライト表示
    _character4 = BaseChara::create("res/mira.png");
    _character4->setAnchorPoint(Vec2(1.0,1.0));
    _character4->setPosition(Vec2(origin.x + 580, origin.y + visibleSize.height / 2 + 230));
    _character4->setPosition(Vec2(origin.x + 550, origin.y + visibleSize.height / 2 + 100));
    _character4->setScale(2.0);
    this->addChild(_character4, 1);
    

    // オープニング背景
    auto background = Sprite::create("res/crystalTower.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);
  
    return true;
    
}


// 画面をタッチした時の処理
bool Opening::onTouchBegan(Touch* pTouch, Event* pEvent){
    
    Vec2 touchPoint = convertTouchToNodeSpace(pTouch);// タッチした画面の座標(X,Y)を取得
    if(touchPoint.x < 0 || touchPoint.x > 600){// 画面外をタッチすると無効
        log("タッチ無効範囲です");
    } else {
        
        
    // todo 次の画面に遷移
        
        
    }
    
    return true;
}




