#pragma execution_character_set("utf-8") // 文字コード指定
#include "EndingConversation.hpp"
#include "EndingScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC; // #define USING_NS_CC using namespace cocos2d

Scene* EndingConversation::createScene() // シーン生成処理
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = EndingConversation::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EndingConversation::init() // 初期化処理
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
    listener->onTouchBegan = CC_CALLBACK_2(EndingConversation::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    // BGMプリロード
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/ending_scene.m4a");
    
    // BGM再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/ending_scene.m4a", true);
    
    
    // テキストの内容
    auto _text1 = Label::createWithTTF("るりす「クリスタルの光が消えていく・・・\n一体何が起ころうとしているの・・・」⬇\n","fonts/ヒラギノ明朝 ProN W6.ttc", 14);
    // テキストの位置指定
    _text1->setPosition(Vec2(visibleSize.width / 2 - 50, visibleSize.height / 4 - 50));
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
    
    // るりすさん
    _character1 = BaseChara::create("res/lelys.png");// スプライト画像読み込み
    _character1->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
    _character1->setPosition(origin.x + 350, origin.y + visibleSize.height / 2 + 200);// 位置指定
    _character1->setScale(2.0);// スプライトの拡大率を2.0倍に指定
    _character1->setTag(2);
    this->addChild(_character1,1);// 画面描画
    
 
    // テキスト表示ウィンドウ
    auto window = Sprite::create("res/menu_window_small.png");
    window->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 180));
    this->addChild(window,1);
    
    
    // 背景
    auto background = Sprite::create("res/crescent_shrine.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);
    
    return true;
    
}

// 画面を1回タップしたときの処理
bool EndingConversation::onTouchBegan(Touch* pTouch, Event* pEvent){
    
    
    // 画面サイズ指定
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    Director::getInstance()->setDisplayStats(false); // stats OFF*
    
    // _text1をタグを指定して呼び出す
    auto _text1 = this->getChildByTag(1);
    // _text1を非表示にする
    _text1->setVisible(false);
    
    // _character1をタグを指定して呼び出す
    auto _character1 = this->getChildByTag(2);
    // _character1を非表示にする
    _character1->setVisible(false);

    // テキストの内容
    auto _text2 = Label::createWithTTF("リサ「遅かった・・・\nクリスタルの力で呼びかけたけど間に合わなかった・・・\nみんな待ってて！私が必ず・・・」\nゼロ「セイヴァー覚醒を促したのはキミの力か・・・」\nリサ「は！！あなたは・・・」\n","fonts/ヒラギノ明朝 ProN W6.ttc",14);
    // テキストの位置指定
    _text2->setPosition(Vec2(visibleSize.width / 2 - 10 , visibleSize.height / 4 - 80));
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

    // リサさん
    _character2 = BaseChara::create("res/lisa.png");// スプライト画像読み込み
    _character2->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
    _character2->setPosition(origin.x + 250, origin.y + visibleSize.height / 2 );// 位置指定
    _character2->setScale(2.0);// スプライトの拡大率を2.0倍に指定
    this->addChild(_character2,1);// 画面描画
    
    
    // MenuItemImageでメニューボタン追加 引数にはボタンを押した時の動作を指定
     auto _nextButton = MenuItemImage::create("res/skip_button.png","res/skip_button_pushed.png",CC_CALLBACK_1(EndingConversation::nextSceneCallback, this));
     _nextButton->setPosition(Vec2(visibleSize.width / 2 + 150, visibleSize.height / 4 - 120));// ボタンの位置を画面中央に指定
     auto _menu = Menu::create(_nextButton, NULL);//
     _menu->setPosition(Vec2::ZERO);
     this->addChild(_menu, 1, 0);
    
    // 12秒後にゼロ出現
    this->runAction(Sequence::create(DelayTime::create(12),CallFunc::create([this](){
        
        // 効果音再生
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/enemy_appear.m4a");
        
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Point origin = Director::getInstance()->getVisibleOrigin();
        Director::getInstance()->setDisplayStats(false); // stats OFF*
        
        // ゼロ
        _enemy = BaseChara::create("res/zero.png");
        _enemy->setAnchorPoint(Vec2(1.0,1.0));
        _enemy->setPosition(Vec2(origin.x + 450, origin.y + visibleSize.height / 2));
        _enemy->setScale(2.0);
        this->addChild(_enemy,1);
        
        
    }), NULL));
   
    // 15秒後にリサさん向き反転
    this->runAction(Sequence::create(DelayTime::create(15),CallFunc::create([this](){
        
        // リサさん向き反転
        _character2->setFlippedX(true);// スプライトの向き反転
        
    }), NULL));
  
    
    // 背景
    auto background = Sprite::create("res/central_crystal.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);
    
    // 23秒後にエンディングシーンに自動で遷移させる
    this->runAction(Sequence::create(DelayTime::create(23),CallFunc::create([this](){
        
        // BGMの停止
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        
        // replaceSceneで画面遷移を行う StageConversationを破棄、2.0秒かけてホワイトアウトしてStageSceneに遷移する
        Director::getInstance()->replaceScene(TransitionFade::create(2.0,EndingScene::createScene(),Color3B::WHITE));
        
    }), NULL));
    
    return true;
}

// 次のシーンへ遷移するためのコールバック関数
void EndingConversation::nextSceneCallback(Ref* pSender){
    
    
    // BGMの停止
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    // replaceSceneで画面遷移を行う StageConversationを破棄、0.5秒かけてホワイトアウトしてStageSceneに遷移する
    Director::getInstance()->replaceScene(TransitionFade::create(2.0,EndingScene::createScene(),Color3B::WHITE));
}
