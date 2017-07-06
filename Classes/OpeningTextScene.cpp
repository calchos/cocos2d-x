#pragma execution_character_set("utf-8") // 文字コード指定
#include "OpeningTextScene.hpp" // OpeningTitle.h 読み込み
#include "SimpleAudioEngine.h"// SimpleAudioEngine.h 読み込み

USING_NS_CC; // #define USING_NS_CC using namespace cocos2d

Scene* OpeningText::createScene() // シーン生成処理
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = OpeningText::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool OpeningText::init() // 初期化処理
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
    
    // テキストの内容
    auto text = Label::createWithTTF("セントラルタワーの天辺に出現したクリスタル。\nそれは世界の全てをコントロールする力を持っておりセントラルクリスタルと呼ばれていた。\nそのクリスタルから突如闇の力が解き放たれ世界に魔物が溢れようとしていた。\nこの危機に4人のクリスタルを守護する者ーークリスタルセイヴァーが召喚される。\n果たして彼らは世界の危機を救うことができるのだろうか…。\n","fonts/ヒラギノ明朝 ProN W3.ttc", 20);
    // テキストの位置指定
    text->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 4));
    // テキストの文字色指定
    text->setColor(Color3B::WHITE);
    text->setOpacity(0);// テキストの透明化
    this->addChild(text);// テキストを表示
    
    // テキストの透明化解除
    for(int i = 0; i < text->getStringLength(); i++){
        
        auto func = CallFunc::create([this, i, text](){
            Sprite* sp = text->getLetter(i);
            if(sp != nullptr){
                text->getLetter(i)->setOpacity(255); //テキストを1文字ずつ透明化解除
            }
        });
        
        auto delay = DelayTime::create(.1 * i);
        auto seq = Sequence::create(delay, func, nullptr);
        
        if(text->getLetter(i) != nullptr){
            text->getLetter(i)->runAction(seq);
        }
        
    }
    
    // スタートボタン表示
    // MenuItemImageでメニューボタン追加 引数にはボタンを押した時の動作を指定
    /*
    auto startItem = MenuItemImage::create("res/start.png","res/start_pushed.png",CC_CALLBACK_1(OpeningText::nextSceneCallback, this));
    startItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4));// ボタンの位置を画面中央に指定
    auto menu = Menu::create(startItem, NULL);//
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1, 0);
    */
    
    
    // BGMプリロード
    //CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/feeling_for_crystal.m4a");
    
    // BGM再生
    //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/feeling_for_crystal.m4a", true);
    

    
    
    // オープニング背景
    /*
    auto background = Sprite::create("res/crystal_tower.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);
     */
    
    return true;
    
}
