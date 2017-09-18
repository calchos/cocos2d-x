#include "StageConversation4.hpp"


#pragma execution_character_set("utf-8") // 文字コード指定
#include "StageConversation.hpp"
#include "StageScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC; // #define USING_NS_CC using namespace cocos2d

Scene* StageConversation::createScene() // シーン生成処理
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StageConversation::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StageConversation::init() // 初期化処理
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
    
    // イベントリスナー(画面をタッチした時の処理)
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(StageConversation::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    // BGMプリロード
    //CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/chocoto_tambourine.m4a");
    
    // BGM再生
    //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/chocoto_tambourine.m4a", true);
    
    
    // テキストの内容
    auto _text1 = Label::createWithTTF("？？？「クリスタル・・・ そうか 彼らこそ選ばれし者にふさわしい・・・\n","fonts/ヒラギノ明朝 ProN W6.ttc", 15);
    // テキストの位置指定
    _text1->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 4 - 105));
    // テキストの文字色指定
    _text1->setColor(Color3B::WHITE);
    _text1->setOpacity(0);// テキストの透明化
    _text1->setTag(1);// _text1をタグ指定
    this->addChild(_text1,2);// テキストを表示
    
    // テキストの透明化解除
    // テキストの長さ分 forループ回す
    for(int i = 0; i < _text1->getStringLength(); i++){
        
        // ラムダ式 []はキャプチャ
        auto func = CallFunc::create([this, i, _text1](){
            // 指定の文字列を返す
            Sprite* sp = _text1->getLetter(i);
            // spがヌルポインタでない場合
            if(sp != nullptr){
                _text1->getLetter(i)->setOpacity(255); //テキストを1文字ずつ透明化解除
            }
        });
        // DelayTimeで待ち時間を設定
        auto delay = DelayTime::create(.2 * i);
        // 複数のアクションを順番に実行 delay→func
        auto seq = Sequence::create(delay, func, nullptr);
        // テキスト文字列がヌルポインタではない場合はアクション実行
        if(_text1->getLetter(i) != nullptr){
            _text1->getLetter(i)->runAction(seq);
        }
        
    }
    
    
    // テキスト表示ウィンドウ
    auto window = Sprite::create("res/menu_window_small.png");
    window->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 180));
    this->addChild(window,1);
    
    
    // 背景
    auto background = Sprite::create("res/.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);
    
    return true;
    
}
