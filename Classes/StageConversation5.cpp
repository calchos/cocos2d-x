#pragma execution_character_set("utf-8") // 文字コード指定
#include "StageConversation5.hpp"
#include "StageScene3.h"
#include "SimpleAudioEngine.h"


USING_NS_CC; // #define USING_NS_CC using namespace cocos2d

Scene* StageConversation5::createScene() // シーン生成処理
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StageConversation5::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StageConversation5::init() // 初期化処理
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
    listener->onTouchBegan = CC_CALLBACK_2(StageConversation5::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    // BGMプリロード
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/central_crystal.m4a");
    
    // BGM再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/central_crystal.m4a", true);
    
    
    // テキストの内容
    auto _text1 = Label::createWithTTF("チョコっと「ここはどこだろう？」\nミラ「なんかいる？」\nチョコっと「えっ？きゃぁ！！なに？」\n真紅「なにかいる！！」\nしーや「敵！？」⬇\n","fonts/ヒラギノ明朝 ProN W6.ttc", 14);
    // テキストの位置指定
    _text1->setPosition(Vec2(visibleSize.width / 2 - 65, visibleSize.height / 4 - 80));
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
    this->addChild(_character1,1);// 画面描画
    
    // 真紅さん
    _character2 = BaseChara::create("res/sinku.png");
    _character2->setAnchorPoint(Vec2(1.0,1.0));
    _character2->setPosition(Vec2(origin.x + 580, origin.y + visibleSize.height / 2 - 45));
    _character2->setScale(2.0);
    this->addChild(_character2,1);
    
    
    // しーやさん
    _character3 = BaseChara::create("res/syiya.png");
    _character3->setAnchorPoint(Vec2(1.0,1.0));
    _character3->setPosition(Vec2(origin.x + 640, origin.y + visibleSize.height / 2 - 30));
    _character3->setScale(2.0);
     this->addChild(_character3,1);
    
    
    // ミラさん
    _character4 = BaseChara::create("res/mira.png");
    _character4->setAnchorPoint(Vec2(1.0,1.0));
    _character4->setPosition(Vec2(origin.x + 540, origin.y + visibleSize.height / 2 + 10));
    _character4->setScale(2.0);
    this->addChild(_character4, 1);
    
    // テキスト表示ウィンドウ
    auto window = Sprite::create("res/menu_window_small.png");
    window->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 180));
    this->addChild(window,1);
    
    
    // 背景
    auto background = Sprite::create("res/central_crystal.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);
    
    return true;
    
}

// 画面を1回タップしたときの処理
bool StageConversation5::onTouchBegan(Touch* pTouch, Event* pEvent){
    
    
    // 画面サイズ指定
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    Director::getInstance()->setDisplayStats(false); // stats OFF*
    
    
    // 効果音再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/enemy_appear.m4a");
    
    
    // _text1をタグを指定して呼び出す
    auto _text1 = this->getChildByTag(1);
    // _text1を非表示にする
    _text1->setVisible(false);

    // テキストの内容
    auto _text2 = Label::createWithTTF("チョコっと「すごく強そう！\nみんな気をつけて！！」\n","fonts/ヒラギノ明朝 ProN W6.ttc",14);
    // テキストの位置指定
    _text2->setPosition(Vec2(visibleSize.width / 2 - 90 , visibleSize.height / 4 - 50));
    // テキストの文字色指定
    _text2->setColor(Color3B::WHITE);
    _text2->setOpacity(0);// テキストの透明化
    this->addChild(_text2,2);// テキストを表示
    
    // テキストの透明化解除
    // テキストの長さ分 forループ回す
    for(int i = 0; i < _text2->getStringLength(); i++){
        
        // ラムダ式 []はキャプチャ
        auto func = CallFunc::create([this, i, _text2](){
            // 指定の文字列を返す
            Sprite* sp = _text2->getLetter(i);
            // spがヌルポインタでない場合
            if(sp != nullptr){
                _text2->getLetter(i)->setOpacity(255); //テキストを1文字ずつ透明化解除
            }
        });
        // 0.2秒遅らせる
        auto delay = DelayTime::create(.2 * i);
        // 複数のアクションを順番に実行 delay→func
        auto seq = Sequence::create(delay, func, nullptr);
        // テキスト文字列がヌルポインタではない場合はアクション実行
        if(_text2->getLetter(i) != nullptr){
            _text2->getLetter(i)->runAction(seq);
        }
        
    }

    
    // MenuItemImageでメニューボタン追加 引数にはボタンを押した時の動作を指定
     auto _nextButton = MenuItemImage::create("res/skip_button.png","res/skip_button_pushed.png",CC_CALLBACK_1(StageConversation5::nextSceneCallback, this));
     _nextButton->setPosition(Vec2(visibleSize.width / 2 + 150, visibleSize.height / 4 - 120));// ボタンの位置を画面中央に指定
     auto _menu = Menu::create(_nextButton, NULL);//
     _menu->setPosition(Vec2::ZERO);
     this->addChild(_menu, 1, 0);
    
    
    
    
    // エネミー1
    _enemy1 = BaseChara::create("res/delzeum.png");
    _enemy1->setAnchorPoint(Vec2(1.0,1.0));
    _enemy1->setPosition(Vec2(origin.x + 300, origin.y + visibleSize.height / 2 + 100 ));
    _enemy1->setScale(4.0);
    this->addChild(_enemy1,1);
    
    // 背景
    auto background = Sprite::create("res/central_crystal.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);
    
    // 10秒後にステージ3に自動で遷移させる
    this->runAction(Sequence::create(DelayTime::create(10),CallFunc::create([this](){
        
        // 効果音再生
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/battle_encount.m4a");
        
        // BGMの停止
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        
        // replaceSceneで画面遷移を行う StageConversationを破棄して0.5秒かけてホワイトアウトしてStageに遷移する
        Director::getInstance()->replaceScene(TransitionRotoZoom::create(0.5,StageScene3::createScene()));
        
    }), NULL));
    
    return true;
}

// 次のシーンへ遷移するためのコールバック関数
void StageConversation5::nextSceneCallback(Ref* pSender){
    
    // 効果音再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/battle_encount.m4a");
    
    // BGMの停止
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    // replaceSceneで画面遷移を行う StageConversationを破棄、0.5秒かけてホワイトアウトしてStageSceneに遷移する
    Director::getInstance()->replaceScene(TransitionRotoZoom::create(0.5,StageScene3::createScene()));
}
