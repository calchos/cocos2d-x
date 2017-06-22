#pragma execution_character_set("utf-8") // 文字コード指定
#include "OpeningTitle.h" // OpeningTitle.h 読み込み
#include "StageScene2.h" // StageScene2.h 読み込み
#include "SimpleAudioEngine.h"// SimpleAudioEngine.h 読み込み

USING_NS_CC; // #define USING_NS_CC using namespace cocos2d


Opening::Opening(){} // コンストラクタ：オブジェクトが生成されたときに最初に実行される

// デストラクタ：オブジェクトが破棄されるときに実行される
Opening::~Opening(){
    removeAllChildrenWithCleanup(true); // 親クラスにaddChildされたノードを全て削除 画面遷移時に不要になったオブジェクトを削除しメモリリークを防止する
}

Scene* Opening::createScene() // シーン生成処理
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
bool Opening::init() // 初期化処理
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
    
    // スタートボタン表示
    // MenuItemImageでメニューボタン追加 引数にはボタンを押した時の動作を指定
    auto startItem = MenuItemImage::create("res/start.png","res/start_pushed.png",CC_CALLBACK_1(Opening::nextSceneCallback, this));
    startItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4));// ボタンの位置を画面中央に指定
    auto menu = Menu::create(startItem, NULL);//
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1, 0);
    
    
    // BGMプリロード
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/feeling_for_crystal.m4a");
    
    // BGM再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/feeling_for_crystal.m4a", true);
    
    // タップイベントを取得する
    /*
    auto listener = EventListenerTouchOneByOne::create();// シングルタッチ
    listener->onTouchBegan = CC_CALLBACK_2(Opening::onTouchBegan, this);//タッチしたときに1回だけ処理を実行
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);// イベントリスナーの組み込み
     */
    
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
    _character3->setPosition(Vec2(origin.x + 615, origin.y + visibleSize.height / 2 - 20));
    _character3->setScale(2.0);
    this->addChild(_character3,1);
    
    // ミラさんスプライト表示
    _character4 = BaseChara::create("res/mira.png");
    _character4->setAnchorPoint(Vec2(1.0,1.0));
    _character4->setPosition(Vec2(origin.x + 580, origin.y + visibleSize.height / 2 + 230));
    _character4->setScale(2.0);
    this->addChild(_character4, 1);
    

    // オープニング背景
    auto background = Sprite::create("res/crystal_tower.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);
    
    return true;
    
}


void Opening::nextSceneCallback(Ref* pSender){
    
    // BGMの停止
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    
    // 効果音再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/button_push.m4a");
    
    // replaceSceneで画面遷移を行う Openingを破棄して0.5秒かけてホワイトアウトしてStage2に遷移する
    Director::getInstance()->replaceScene(TransitionFade::create(0.5,Stage2::createScene(),Color3B::WHITE));
}



