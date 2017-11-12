#pragma execution_character_set("utf-8") // 文字コード指定
#include "StageConversation2.hpp"
#include "StageConversation3.hpp"
#include "SimpleAudioEngine.h"


USING_NS_CC; // #define USING_NS_CC using namespace cocos2d

Scene* StageConversation2::createScene() // シーン生成処理
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StageConversation2::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StageConversation2::init() // 初期化処理
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
    listener->onTouchBegan = CC_CALLBACK_2(StageConversation2::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    // BGMプリロード
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/chocoto_tambourine.m4a");
    
    // BGM再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/chocoto_tambourine.m4a", true);
    
    
    // テキストの内容
    auto _text1 = Label::createWithTTF("チョコっと「サボテンさん逃げちゃった！\nあれ？あれは異界の扉かな？」\n真紅「入ってみましょうか？」\nしーや「みましょう！みましょう！」\nミラ「ノシ」⬇\n","fonts/ヒラギノ明朝 ProN W6.ttc", 14);
    // テキストの位置指定
    _text1->setPosition(Vec2(visibleSize.width / 2 - 55, visibleSize.height / 4 - 80));
    // テキストの文字色指定
    _text1->setColor(Color3B::WHITE);
    _text1->setOpacity(0);// テキストの透明化
    _text1->setTag(0);// _text1をタグ指定
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
    _character4->setPosition(Vec2(origin.x + 590, origin.y + visibleSize.height / 2 + 50));
    _character4->setScale(2.0);
    _character4->setTag(4);
    this->addChild(_character4, 1);
    
    // エネミー1
    _enemy1 = BaseChara::create("res/cactuar.png");
    _enemy1->setAnchorPoint(Vec2(1.0,1.0));
    _enemy1->setPosition(Vec2(origin.x + 400, origin.y + visibleSize.height / 2 ));
    _enemy1->setScale(2.0);
    _enemy1->runAction(MoveTo::create(2.0f,Vec2(origin.x - 100, origin.y + visibleSize.height / 2 )));
    this->addChild(_enemy1,1);
    
    
    
    // テキスト表示ウィンドウ
    auto _window = Sprite::create("res/menu_window_small.png");
    _window->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 180));
    _window->setTag(5);
    this->addChild(_window,1);
    
    
    // 背景
    auto background = Sprite::create("res/knowledge_plain.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);
    
    // 5秒後に異界の扉出現
    this->runAction(Sequence::create(DelayTime::create(5),CallFunc::create([this](){
        
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Point origin = Director::getInstance()->getVisibleOrigin();
        
        Director::getInstance()->setDisplayStats(false); // stats OFF*
    
        auto _door = Sprite::create("res/the_next_world_door.png");
        _door->setPosition(Point(visibleSize.width / 2  - 200 + origin.x, visibleSize.height / 2 + origin.y - 30));
        _door->setScale(2.5);
        this->addChild(_door,0);
    
    }), NULL));
        
    return true;
    
}

// 画面を1回タップしたときの処理
bool StageConversation2::onTouchBegan(Touch* pTouch, Event* pEvent){
    
    
    // 画面サイズ指定
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    Director::getInstance()->setDisplayStats(false); // stats OFF*
    
    // 1秒後にボタン表示
    this->runAction(Sequence::create(DelayTime::create(1),CallFunc::create([this](){
        
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Point origin = Director::getInstance()->getVisibleOrigin();
        
        Director::getInstance()->setDisplayStats(false); // stats OFF*
        
        
        // BGMの停止
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        
        // 効果音再生
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/stage_clear.m4a");
        
        // StageClear画像
        auto _stageClear = Sprite::create("res/stage_clear.png");
        _stageClear->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 120));
        _stageClear->setScale(1.5f);
        this->addChild(_stageClear,1);
    
        auto nextButton = MenuItemImage::create("res/next.png","res/next_pushed.png",CC_CALLBACK_1(StageConversation2::nextSceneCallback, this));
        nextButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4 - 120));// ボタンの位置を画面中央に指定
        auto menu = Menu::create(nextButton, NULL);//
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1, 0);
        
        }), NULL));
    
    // テキストタグ呼び出し
    auto _text1 = this->getChildByTag(0);
    
    // キャラクタータグ呼び出し
    auto _character1 = this->getChildByTag(1);
    auto _character2 = this->getChildByTag(2);
    auto _character3 = this->getChildByTag(3);
    auto _character4 = this->getChildByTag(4);
    
    // ウィンドウタグ呼び出し
    auto _window = this->getChildByTag(5);
    
    _text1->setVisible(false);
    
    _character1->setVisible(false);
    _character2->setVisible(false);
    _character3->setVisible(false);
    _character4->setVisible(false);
    
    _window->setVisible(false);
    
    _character1 = BaseChara::create("res/chocoto.png");// スプライト画像読み込み
    _character1->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
    _character1->setPosition(origin.x + 500, origin.y + visibleSize.height / 2 );// 位置指定
    _character1->setScale(2.0);// スプライトの拡大率を2.0倍に指定
    this->addChild(_character1,2);// 画面描画
    
    // 真紅さん
    _character2 = BaseChara::create("res/sinku.png");
    _character2->setAnchorPoint(Vec2(1.0,1.0));
    _character2->setPosition(Vec2(origin.x + 580, origin.y + visibleSize.height / 2 - 45));
    _character2->setScale(2.0);
    this->addChild(_character2,2);
    
    
    // しーやさん
    _character3 = BaseChara::create("res/syiya.png");
    _character3->setAnchorPoint(Vec2(1.0,1.0));
    _character3->setPosition(Vec2(origin.x + 640, origin.y + visibleSize.height / 2 - 30));
    _character3->setScale(2.0);
    this->addChild(_character3,2);
    
    
    // ミラさん
    _character4 = BaseChara::create("res/mira.png");
    _character4->setAnchorPoint(Vec2(1.0,1.0));
    _character4->setPosition(Vec2(origin.x + 590, origin.y + visibleSize.height / 2 + 50));
    _character4->setScale(2.0);
    this->addChild(_character4, 2);
    
    // 異界の扉
    auto _door = Sprite::create("res/the_next_world_door.png");
    _door->setPosition(Point(visibleSize.width / 2  - 200 + origin.x, visibleSize.height / 2 + origin.y - 30));
    _door->setScale(2.5);
    this->addChild(_door,1);
    
    
    // 背景
    auto background = Sprite::create("res/knowledge_plain.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);
    
    return true;
}

// 次のシーンへ遷移するためのコールバック関数
void StageConversation2::nextSceneCallback(Ref* pSender){
    
    // 効果音再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/button_push.m4a");
    
    // BGMの停止
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    // replaceSceneで画面遷移を行う StageConversation2を破棄して0.7秒かけてホワイトアウトしてStageConversation3に遷移する
    Director::getInstance()->replaceScene(TransitionFade::create(0.7,StageConversation3::createScene()));
}
