#pragma execution_character_set("utf-8") // 文字コード指定
#include "StageConversation7.hpp"
#include "StageScene4.h"
#include "SimpleAudioEngine.h"


USING_NS_CC; // #define USING_NS_CC using namespace cocos2d

Scene* StageConversation7::createScene() // シーン生成処理
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StageConversation7::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StageConversation7::init() // 初期化処理
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
    listener->onTouchBegan = CC_CALLBACK_2(StageConversation7::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    // 現在流れている音楽を停止
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    // 効果音再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/before_final_battle.m4a");
    
    // テキストの内容
    auto _text1 = Label::createWithTTF("チョコっと「ここはどこなの？それになんなのこの空間？」\n？？？「世界の中心ーーセントラル・ゼロへようこそ！クリスタルセイヴァーの諸君！」\nチョコっと「もう一度聞きます！あなたは何者なのですか！？」\n？？？「わたしの名はゼローーゼロ・クリエイト。\n零を創りし者。キミたちのクリスタルの力今ここで試させてもらおう！」","fonts/ヒラギノ明朝 ProN W6.ttc",15);
    // テキストの位置指定
    _text1->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 4 - 80));
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
    
    // チョコさん
    _character1 = BaseChara::create("res/chocoto.png");// スプライト画像読み込み
    _character1->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
    _character1->setPosition(origin.x + 500, origin.y + visibleSize.height / 2 );// 位置指定
    _character1->setScale(2.0);// スプライトの拡大率を2.0倍に指定
    _character1->setTag(1);
    this->addChild(_character1,1);// 画面描画
    
    // 真紅さん
    _character2 = BaseChara::create("res/sinku.png");
    _character2->setAnchorPoint(Vec2(1.0,1.0));
    _character2->setPosition(Vec2(origin.x + 580, origin.y + visibleSize.height / 2 - 45));
    _character2->setScale(2.0);
    _character2->setTag(2);
    this->addChild(_character2,1);
    
    
    // しーやさん
    _character3 = BaseChara::create("res/syiya.png");
    _character3->setAnchorPoint(Vec2(1.0,1.0));
    _character3->setPosition(Vec2(origin.x + 640, origin.y + visibleSize.height / 2 - 30));
    _character3->setScale(2.0);
    _character3->setTag(3);
     this->addChild(_character3,1);
    
    
    // ミラさん
    _character4 = BaseChara::create("res/mira.png");
    _character4->setAnchorPoint(Vec2(1.0,1.0));
    _character4->setPosition(Vec2(origin.x + 540, origin.y + visibleSize.height / 2 + 10));
    _character4->setScale(2.0);
    _character4->setTag(4);
    this->addChild(_character4, 1);
    
    
        // ゼロ表示
        _enemy = BaseChara::create("res/zero.png");// スプライト画像読み込み
        _enemy->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
        _enemy->setPosition(Vec2(origin.x + 200, origin.y + visibleSize.height / 2 - 20));// 位置指定
        _enemy->setFlippedX(true);
        _enemy->setScale(2.0);// スプライトの拡大率を2.0倍に指定
        this->addChild(_enemy,1);// 画面描画
    
    
    // テキスト表示ウィンドウ
    auto _window = Sprite::create("res/menu_window_small.png");
    _window->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 180));
    this->addChild(_window,1);

    // 背景
    auto background = Sprite::create("res/central_zero.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);
    
    // MenuItemImageでメニューボタン追加 引数にはボタンを押した時の動作を指定
    auto _nextButton = MenuItemImage::create("res/skip_button.png","res/skip_button_pushed.png",CC_CALLBACK_1(StageConversation7::nextSceneCallback, this));
    _nextButton->setPosition(Vec2(visibleSize.width / 2 + 150, visibleSize.height / 4 - 120));// ボタンの位置を画面中央に指定
    auto _menu = Menu::create(_nextButton, NULL);//
    _menu->setPosition(Vec2::ZERO);
    this->addChild(_menu, 1, 0);
    
     // 15秒後にステージ4に自動で遷移させる
     this->runAction(Sequence::create(DelayTime::create(15),CallFunc::create([this](){
        // 効果音再生
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/battle_encount.m4a");
        
        // ステージシーン4へ遷移
        Director::getInstance()->replaceScene(TransitionRotoZoom::create(1.0,StageScene4::createScene()));
    
      }), NULL));
    
    return true;
    
}


// 次のシーンへ遷移するためのコールバック関数
void StageConversation7::nextSceneCallback(Ref* pSender){
    
    // 効果音再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/battle_encount.m4a");
    
    // BGMの停止
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    // ステージ4に遷移
    Director::getInstance()->replaceScene(TransitionRotoZoom::create(2.0,StageScene4::createScene()));
}

