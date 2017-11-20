#pragma execution_character_set("utf-8") // 文字コード指定
#include "StageConversation6.hpp"
#include "StageConversation7.hpp"
#include "SimpleAudioEngine.h"


USING_NS_CC; // #define USING_NS_CC using namespace cocos2d

Scene* StageConversation6::createScene() // シーン生成処理
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StageConversation6::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StageConversation6::init() // 初期化処理
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
    listener->onTouchBegan = CC_CALLBACK_2(StageConversation6::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    // テキストの内容
    auto _text1 = Label::createWithTTF("チョコっと「あなたは一体？」\n？？？「自分…いや私か？」\nチョコっと「えっ？」\nしーや・真紅「！？」\n？？？「クリスタル・・・そうか彼らこそ\n選ばれし者にふさわしい」\n","fonts/ヒラギノ明朝 ProN W6.ttc", 14);
    // テキストの位置指定
    _text1->setPosition(Vec2(visibleSize.width / 2 - 60, visibleSize.height / 4 - 90));
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
    _character4->setPosition(Vec2(origin.x + 540, origin.y + visibleSize.height / 2 + 10));
    _character4->setScale(2.0);
    _character4->setTag(4);
    this->addChild(_character4, 1);
    
    
    // カルチョス？
    _character5 = BaseChara::create("res/calchos.png");// スプライト画像読み込み
    _character5->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
    _character5->setPosition(Vec2(origin.x + 320, origin.y + visibleSize.height / 2 - 20));// 位置指定
    _character5->setScale(2.0);// スプライトの拡大率を2.0倍に指定
    _character5->setTag(5);
    this->addChild(_character5,1);// 画面描画
    
    // 3秒後カルチョスと思しき人物がこちらを振り向く
    this->runAction(Sequence::create(DelayTime::create(3),CallFunc::create([this](){
        
        _character5->setFlippedX(true);
        
    }), NULL));
    
    // 6秒後に正体を現しゼロ登場
    this->runAction(Sequence::create(DelayTime::create(6),CallFunc::create([this](){
        
        auto _character5 = this->getChildByTag(5);
        _character5->setVisible(false);
        
        // 画面サイズ指定
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Point origin = Director::getInstance()->getVisibleOrigin();
        
        Director::getInstance()->setDisplayStats(false); // stats OFF*
        
        // 効果音再生
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/unveil.m4a");
        
        // BGMプリロード
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/zero_create.m4a");
        
        // ゼロのテーマ再生
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/zero_create.m4a", true);
        
        // ゼロ
        _enemy = BaseChara::create("res/zero.png");// スプライト画像読み込み
        _enemy->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
        _enemy->setPosition(Vec2(origin.x + 320, origin.y + visibleSize.height / 2 - 20));// 位置指定
        _enemy->setFlippedX(true);
        _enemy->setScale(2.0);// スプライトの拡大率を2.0倍に指定
        this->addChild(_enemy,1);// 画面描画
        
    }), NULL));
    
    // 8秒後にプレイヤーキャラクター4人が消える
    this->runAction(Sequence::create(DelayTime::create(8),CallFunc::create([this](){
        
        // キャラクタータグ呼び出し
        auto _character1 = this->getChildByTag(1);
        _character1->setVisible(false);
        auto _character2 = this->getChildByTag(2);
        _character2->setVisible(false);
        auto _character3 = this->getChildByTag(3);
        _character3->setVisible(false);
        auto _character4 = this->getChildByTag(4);
        _character4->setVisible(false);
        
    }), NULL));
    
    
    // 39秒後に会話シーン7に遷移
    this->runAction(Sequence::create(DelayTime::create(39),CallFunc::create([this](){

        // BGMの停止
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        
        // 会話シーン7へ遷移
        Director::getInstance()->replaceScene(TransitionFade::create(2.0,StageConversation7::createScene(),Color3B::BLACK));
        
    }), NULL));
    
    
    // テキスト表示ウィンドウ
    auto _window = Sprite::create("res/menu_window_small.png");
    _window->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 180));
    _window->setTag(6);
    this->addChild(_window,1);
    
    // MenuItemImageでメニューボタン追加 引数にはボタンを押した時の動作を指定
    auto _nextButton = MenuItemImage::create("res/skip_button.png","res/skip_button_pushed.png",CC_CALLBACK_1(StageConversation6::nextSceneCallback, this));
    _nextButton->setPosition(Vec2(visibleSize.width / 2 + 150, visibleSize.height / 4 - 120));// ボタンの位置を画面中央に指定
    auto _menu = Menu::create(_nextButton, NULL);//
    _menu->setPosition(Vec2::ZERO);
    this->addChild(_menu, 1, 0);
    
    
    // 背景
    auto _background = Sprite::create("res/central_crystal.png");
    _background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(_background,0);
    
    return true;
    
}

// 次のシーンへ遷移するためのコールバック関数
void StageConversation6::nextSceneCallback(Ref* pSender){
    
    // BGMの停止
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    // 会話シーン7へ遷移
    Director::getInstance()->replaceScene(TransitionFade::create(2.0,StageConversation7::createScene(),Color3B::BLACK));
}
