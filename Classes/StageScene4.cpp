#pragma execution_character_set("utf-8") // 文字コード指定
#include "StageScene4.h"
#include "StageConversation7.hpp"
#include "EndingConversation.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC; // #define USING_NS_CC using namespace cocos2d

Scene* StageScene4::createScene() //
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StageScene4::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


StageScene4::StageScene4(){
    // 何もしない
}

StageScene4::~StageScene4(){
    // シーンを移動するときに子をすべてremoveする
    removeAllChildrenWithCleanup(true);
}


// on "init" you need to initialize your instance
bool StageScene4::init()
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
    listener->onTouchBegan = CC_CALLBACK_2(StageScene4::onTouchBegan, this);// タップした瞬間に1回だけ処理を実行
    listener->onTouchEnded = CC_CALLBACK_2(StageScene4::onTouchEnded, this);// タップを離した瞬間に１回だけ実行
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);// イベントリスナーの組み込み
    
    // BGMプリロード
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/crystal_duel_crystal_fade_version.m4a");
    
    // BGM再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/crystal_duel_crystal_fade_version.m4a", true);
    
    // チョコっとさん
    _character1 = BaseChara::create("res/chocoto.png");// スプライト画像読み込み
    _character1->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
    _character1->setPosition(Vec2(origin.x + 400, origin.y + visibleSize.height / 2 + 100));// 位置指定
    _character1->setScale(2.0);// スプライトの拡大率を2.0倍に指定
    _character1->setTag(0);// タグ指定
    this->addChild(_character1,1);// 画面描画
    
    
    // 真紅さん
    _character2 = BaseChara::create("res/sinku.png");
    _character2->setAnchorPoint(Vec2(1.0,1.0));
    _character2->setPosition(Vec2(origin.x + 400, origin.y + visibleSize.height / 2 - 20));
    _character2->setScale(2.0);
    _character2->setTag(1);// タグ指定
    this->addChild(_character2,1);
    
    // しーやさん
    _character3 = BaseChara::create("res/syiya.png");
    _character3->setAnchorPoint(Vec2(1.0,1.0));
    _character3->setPosition(Vec2(origin.x + 550, origin.y + visibleSize.height / 2 - 20));
    _character3->setTag(2);// タグ指定
    _character3->setScale(2.0);
    this->addChild(_character3,1);
    
    // ミラさん
    _character4 = BaseChara::create("res/mira.png");
    _character4->setAnchorPoint(Vec2(1.0,1.0));
    _character4->setPosition(Vec2(origin.x + 550, origin.y + visibleSize.height / 2 + 100));
    _character4->setScale(2.0);
    _character4->setTag(3);// タグ指定
    this->addChild(_character4, 1);
    
    
    // ゼロ
    _enemy = BaseChara::create("res/zero.png");
    _enemy->setAnchorPoint(Vec2(1.0,1.0));
    _enemy->setPosition(Vec2(origin.x + visibleSize.height / 2 - 90, origin.y + visibleSize.height / 2 + 90));
    _enemy->setScale(2.0);
    _enemy->setFlippedX(true);
    this->addChild(_enemy,1);
    
    
    // 敵出現テキスト
    auto _text1 = Label::createWithTTF("次元超越者ゼロ・クリエイトがあらわれた！▼", "fonts/ヒラギノ明朝 ProN W6.ttc",14);
    _text1->setPosition(Point(visibleSize.width / 2 + origin.x - 30, visibleSize.height / 2 + origin.y - 180));
    _text1->setTag(5);// text1をタグ指定
    this->addChild(_text1,2);
    
    // テキスト表示ウィンドウ
    auto _window = Sprite::create("res/menu_window_small.png");
    _window->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 180));
    this->addChild(_window,1);
    
    // ステージ4背景表示
    auto background2 = Sprite::create("res/central_zero.png");
    background2->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background2,0);
    
    return true;
    
}


// 画面をタップした瞬間に1回だけ実行する時の処理
bool StageScene4::onTouchBegan(Touch* pTouch, Event* pEvent){
    
    // イベント終了後、エンディング会話シーンの画面に遷移する
    if(_state == TYPE_EVENT_END){
    
        // 現在流れている音楽を停止
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        
        Director::getInstance()->replaceScene(TransitionFade::create(2.0
                                                                     ,EndingConversation::createScene()
                                                                     , Color3B::WHITE));
    }
    
    // キャラクタータグ呼び出し
    auto _character1 = this->getChildByTag(0);
    auto _character2 = this->getChildByTag(1);
    auto _character3 = this->getChildByTag(2);
    auto _character4 = this->getChildByTag(3);
    
    // 画面サイズ指定
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    Director::getInstance()->setDisplayStats(false); // stats OFF*
    
    // _text1タグ呼び出し
    auto _text1 = this->getChildByTag(5);
    // _text1を非表示にする
    _text1->setVisible(false);
    
    // 効果音再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/crystal_sound.m4a");
    
    // タップした座標を取得
    Vec2 touchPoint = convertTouchToNodeSpace(pTouch);
    
    
    // チョコっとさんのスプライト範囲をタップしたときの処理
    if(_character1->getBoundingBox().containsPoint(touchPoint) && _player1Turn == false){
        
        // _character1を非表示
        _character1->setVisible(false);
        // クリスタル力1
        _crystalPower1 = 0;
        
        // チョコっとさんの武器攻撃
        _character1 = BaseChara::create("res/chocoto_attack_01.png");// スプライト画像読み込み
        _character1->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
        _character1->setPosition(Vec2(origin.x + 400, origin.y + visibleSize.height / 2 + 100));// 位置指定
        _character1->setScale(2.0);// スプライトの拡大率を2.0倍に指定
        _character1->setTag(14);
        this->addChild(_character1,1);// 画面描画
        
        auto _text2 = Label::createWithTTF("チョコっとの武器攻撃。\nしかしクリスタルが衰えてしまい\n本来の力が出せない！▼", "fonts/ヒラギノ明朝 ProN W6.ttc",14);
        _text2->setPosition(Point(visibleSize.width / 2 + origin.x - 85, visibleSize.height / 2 + origin.y - 190));
        _text2->setTag(6);
        this->addChild(_text2,2);
        
        
        // クリスタル画像
        auto _crystal = Sprite::create("res/crystal_light_fade.png");
        _crystal->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 155));
        _crystal->setScale(1.5f);
        _crystal->setTag(7);
        this->addChild(_crystal,0);
        
        // クリスタルパワー
        auto _crystalValue = Label::createWithTTF(StringUtils::toString(_crystalPower1),"fonts/ヒラギノ明朝 ProN W6.ttc",30);
        _crystalValue->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystalValue->setTag(8);
        this->addChild(_crystalValue,2);
        
        // プレイヤー1ターンフラグをTRUEにセット
        _player1Turn = true;
        
    }
    
    // 真紅さんのスプライト範囲をタップしたときの処理
    if(_character2->getBoundingBox().containsPoint(touchPoint) && _player2Turn == false){
        
        // _character2を非表示
        _character2->setVisible(false);
        // クリスタル力2
        _crystalPower2 = 0;
        
        // 真紅さんの歌う攻撃
        _character2 = BaseChara::create("res/sinku_attack_01.png");// スプライト画像読み込み
        _character2->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
        _character2->setPosition(Vec2(origin.x + 400, origin.y + visibleSize.height / 2 - 20));// 位置指定
        _character2->setScale(2.0);// スプライトの拡大率を2.0倍に指定
        _character2->setTag(18);
        this->addChild(_character2,1);// 画面描画
        
        auto _text2 = Label::createWithTTF("真紅の歌う攻撃。\nしかしクリスタルが衰えてしまい\n本来の力が出せない！▼", "fonts/ヒラギノ明朝 ProN W6.ttc",14);
        _text2->setPosition(Point(visibleSize.width / 2 + origin.x - 85, visibleSize.height / 2 + origin.y - 190));
        _text2->setTag(6);
        this->addChild(_text2,2);
        
        
        // クリスタル画像
        auto _crystal = Sprite::create("res/crystal_fire_fade.png");
        _crystal->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 155));
        _crystal->setScale(1.5f);
        _crystal->setTag(7);
        this->addChild(_crystal,0);
        
        // クリスタルパワー
        auto _crystalValue = Label::createWithTTF(StringUtils::toString(_crystalPower2),"fonts/ヒラギノ明朝 ProN W6.ttc",30);
        _crystalValue->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystalValue->setTag(8);
        this->addChild(_crystalValue,2);
        
        // プレイヤー2ターンフラグをTRUEにセット
        _player2Turn = true;
        
    }
    
    
    // しーやさんのスプライト範囲をタップしたときの処理
    if(_character3->getBoundingBox().containsPoint(touchPoint) && _player3Turn == false){
        
        // _character3を非表示
        _character3->setVisible(false);
        
        // クリスタルパワー
        _crystalPower3 = 0;
        
        // しーやさんの魔法攻撃
        _character3 = BaseChara::create("res/syiya_attack_01.png");// スプライト画像読み込み
        _character3->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
        _character3->setPosition(Vec2(origin.x + 550, origin.y + visibleSize.height / 2 - 20));// 位置指定
        _character3->setScale(2.0);// スプライトの拡大率を2.0倍に指定
        _character3->setTag(19);
        this->addChild(_character3,1);// 画面描画
        
        auto _text2 = Label::createWithTTF("しーやの魔法攻撃。\nしかしクリスタルが衰えてしまい\n本来の力が出せない！▼", "fonts/ヒラギノ明朝 ProN W6.ttc",14);
        _text2->setPosition(Point(visibleSize.width / 2 + origin.x - 85, visibleSize.height / 2 + origin.y - 190));
        _text2->setTag(6);//タグ付け
        this->addChild(_text2,2);
        
        
        // クリスタル画像
        auto _crystal = Sprite::create("res/crystal_water_fade.png");
        _crystal->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 155));
        _crystal->setScale(1.5f);
        _crystal->setTag(7);
        this->addChild(_crystal,0);
        
        // クリスタルパワー表示
        auto _crystalValue = Label::createWithTTF(StringUtils::toString(_crystalPower3),"fonts/ヒラギノ明朝 ProN W6.ttc",30);
        _crystalValue->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystalValue->setTag(8);
        this->addChild(_crystalValue,2);
        
        // プレイヤー3ターンフラグをTRUEにセット
        _player3Turn = true;
        
    }
    
    // ミラさんをタップした場合の処理
    if(_character4->getBoundingBox().containsPoint(touchPoint) && _player4Turn == false){
        
        // _character4を非表示
        _character4->setVisible(false);
        // クリスタル力4
        _crystalPower4 = 0;
        
        // ミラさんのジャンプ攻撃
        _character4 = BaseChara::create("res/mira_attack_01.png");// スプライト画像読み込み
        _character4->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
        _character4->setPosition(Vec2(origin.x + 550, origin.y + visibleSize.height / 2 + 100));// 位置指定
        _character4->setScale(2.0);// スプライトの拡大率を2.0倍に指定
        _character4->setTag(16);
        this->addChild(_character4,1);// 画面描画
        
        auto _text2 = Label::createWithTTF("ミラのジャンプ攻撃。\nしかしクリスタルが衰えてしまい\n本来の力が出せない！▼", "fonts/ヒラギノ明朝 ProN W6.ttc",14);
        _text2->setPosition(Point(visibleSize.width / 2 + origin.x - 85, visibleSize.height / 2 + origin.y - 190));
        _text2->setTag(6);//タグ付け
        this->addChild(_text2,2);
        
        
        // クリスタル画像
        auto _crystal = Sprite::create("res/crystal_earth.png");
        _crystal->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 155));
        _crystal->setScale(1.5f);
        _crystal->setTag(7);
        this->addChild(_crystal,0);
        
        // クリスタルパワー
        auto _crystalValue = Label::createWithTTF(StringUtils::toString(_crystalPower4),"fonts/ヒラギノ明朝 ProN W6.ttc",30);
        _crystalValue->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystalValue->setTag(8);
        this->addChild(_crystalValue,2);
        
        // プレイヤー4ターンフラグをTRUEにセット
        _player4Turn = true;
        
    }
    
    // 1秒後にintervalDeleteActionメソッドを呼ぶ
    this->scheduleOnce(schedule_selector(StageScene4::intervalDeleteAction),1.0f);
    
    // 更新メソッド定期呼び出し
    this->scheduleUpdate();
    
    return true;
}




// 画面のタップを離した瞬間に1回だけ実行する処理
void StageScene4::onTouchEnded(Touch* pTouch, Event* pEvent){
    
    // 何もしない
}


// バトル更新処理
void StageScene4::update(float delta){
    
    // 味方のターン
    if(_state == TYPE_PLAYER_TURN){
        
        
        // プレイヤー1〜4のターンフラグが全てtrueであれば敵のターンに交代
        if(_player1Turn == true && _player2Turn == true && _player3Turn == true && _player4Turn == true){
            
            // ターン交代
            _state = TYPE_ENEMY_TURN;
            
        }
        
    }
    
    // 敵のターン
    if(_state == TYPE_ENEMY_TURN){
         // イベント発生
         _state = TYPE_EVENT_OCCURRED;
        
    }
    
    // イベント発生ターン
    else if(_state == TYPE_EVENT_OCCURRED){
        
        // _gameEndEventがfalseのときtrueにする
        if(!_gameEndEvent){
            _gameEndEvent = true;
 
            // 3秒後にテキスト表示
            this->runAction(Sequence::create(DelayTime::create(3),CallFunc::create([this](){
                
                // 画面サイズ指定
                auto visibleSize = Director::getInstance()->getVisibleSize();
                Point origin = Director::getInstance()->getVisibleOrigin();
                Director::getInstance()->setDisplayStats(false); // stats OFF*
                
                // チョコさんセリフ
                auto _text3 = Label::createWithTTF("チョコっと「そんな・・・\nクリスタルの力が発動できない！！」", "fonts/ヒラギノ明朝 ProN W6.ttc",14);
                _text3->setPosition(Point(visibleSize.width / 2 + origin.x - 70, visibleSize.height / 2 + origin.y - 180));
                _text3->setTag(9);
                this->addChild(_text3,2);
                
                }), NULL));
            
            
            // 6秒後にテキスト表示
            this->runAction(Sequence::create(DelayTime::create(6),CallFunc::create([this](){
                
                // _text3をタグを指定して呼び出す
                auto _text3 = this->getChildByTag(9);
                // _text3を非表示にする
                _text3->setVisible(false);
                
                // _character1をタグを指定して呼び出す
                auto _character1 = this->getChildByTag(14);
                // _character1を非表示にする
                _character1->setVisible(false);
                
                // 画面サイズ指定
                auto visibleSize = Director::getInstance()->getVisibleSize();
                Point origin = Director::getInstance()->getVisibleOrigin();
                Director::getInstance()->setDisplayStats(false); // stats OFF*
                
                // チョコさんクリスタル化
                _character1 = BaseChara::create("res/chocoto_crystalize.png");// スプライト画像読み込み
                _character1->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
                _character1->setPosition(Vec2(origin.x + 400, origin.y + visibleSize.height / 2 + 100));// 位置指定
                _character1->setScale(2.0);// スプライトの拡大率を2.0倍に指定
                _character1->setTag(15);
                this->addChild(_character1,1);// 画面描画
                
                
                // 効果音再生
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/crystalize.m4a");
                
                // チョコさんクリスタルに閉じ込められる
                auto _text4 = Label::createWithTTF("チョコっと「えっ？閉じ込められたの？\nちょっとここから出してよー！」", "fonts/ヒラギノ明朝 ProN W6.ttc",14);
                _text4->setPosition(Point(visibleSize.width / 2 + origin.x - 70, visibleSize.height / 2 + origin.y - 180));
                _text4->setTag(10);
                this->addChild(_text4,2);
                
            }), NULL));
            
       
            // 10秒後にテキスト表示
            this->runAction(Sequence::create(DelayTime::create(10),CallFunc::create([this](){
                
                // _text4をタグを指定して呼び出す
                auto _text4 = this->getChildByTag(10);
                // _text3を非表示にする
                _text4->setVisible(false);
                
                // 画面サイズ指定
                auto visibleSize = Director::getInstance()->getVisibleSize();
                Point origin = Director::getInstance()->getVisibleOrigin();
                Director::getInstance()->setDisplayStats(false); // stats OFF*
                
                // ゼロセリフ
                auto _text5 = Label::createWithTTF("ゼロ「セイヴァーチョコっと\nセイヴァーとしてキミの力見せてもらった\nだが今しばらくはクリスタルの中で眠っていてもらおうか！」", "fonts/ヒラギノ明朝 ProN W6.ttc",14);
                _text5->setPosition(Point(visibleSize.width / 2 + origin.x + 5 , visibleSize.height / 2 + origin.y - 190));
                _text5->setTag(11);
                this->addChild(_text5,2);
                
            }), NULL));
            
            // 15秒後にテキスト表示
            this->runAction(Sequence::create(DelayTime::create(15),CallFunc::create([this](){
            
                // _text5をタグを指定して呼び出す
                auto _text5 = this->getChildByTag(11);
                // _text5を非表示にする
                _text5->setVisible(false);
                
                // 画面サイズ指定
                auto visibleSize = Director::getInstance()->getVisibleSize();
                Point origin = Director::getInstance()->getVisibleOrigin();
                Director::getInstance()->setDisplayStats(false); // stats OFF*
                
                // チョコさぁーーーーーーーーん！！！ヽ(´Д`)ノ
                auto _text6 = Label::createWithTTF("チョコっと「きゃぁぁーーーーーーーー！！！！！」", "fonts/ヒラギノ明朝 ProN W6.ttc",14);
                _text6->setPosition(Point(visibleSize.width / 2 + origin.x - 25, visibleSize.height / 2 + origin.y - 180));
                _text6->setTag(12);
                this->addChild(_text6,2);
            
             }), NULL));
            
            // チョコさん消えちゃった・・・(´・ω・`)
            this->runAction(Sequence::create(DelayTime::create(18),CallFunc::create([this](){
                
                // 効果音再生
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/crystalize.m4a");
                
                // _text6をタグを指定して呼び出す
                auto _text6 = this->getChildByTag(12);
                // _text6を非表示にする
                _text6->setVisible(false);
                
                // _character1をタグ指定して呼び出す
                auto _character1 = this->getChildByTag(15);
                // _character1を非表示にする
                _character1->setVisible(false);
                
                
                
            }), NULL));
            
            
            
            // ミラさんもクリスタルに閉じ込められる
            this->runAction(Sequence::create(DelayTime::create(20),CallFunc::create([this](){
                
                // _character4をタグを指定して呼び出す
                auto _character4 = this->getChildByTag(16);
                // _character4を非表示にする
                _character4->setVisible(false);
                
                // 画面サイズ指定
                auto visibleSize = Director::getInstance()->getVisibleSize();
                Point origin = Director::getInstance()->getVisibleOrigin();
                Director::getInstance()->setDisplayStats(false); // stats OFF*
                
                // 効果音再生
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/crystalize.m4a");
                
                // ミラさんクリスタル化
                _character4 = BaseChara::create("res/mira_crystalize.png");// スプライト画像読み込み
                _character4->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
                _character4->setPosition(Vec2(origin.x + 550, origin.y + visibleSize.height / 2 + 100));// 位置指定
                _character4->setScale(2.0);// スプライトの拡大率を2.0倍に指定
                _character4->setTag(17);
                this->addChild(_character4,1);// 画面描画
                
                // ミラつぁーーーーーーーーん！！！ヽ(´Д`)ノ
                auto _text7 = Label::createWithTTF("ミラ「チョコちゃん！！うわぁっ！」\nゼロ「キミもだ！セイヴァーミラ！\n今のキミたちのクリスタルの力では私には敵わない！\n来るべき時まで眠りにつくといい！」", "fonts/ヒラギノ明朝 ProN W6.ttc",14);
                _text7->setPosition(Point(visibleSize.width / 2 + origin.x - 25, visibleSize.height / 2 + origin.y - 200));
                _text7->setTag(13);
                this->addChild(_text7,2);
                
            
            }), NULL));
            
            
            // ミラさん消えちゃった・・・(´・ω・`)
            this->runAction(Sequence::create(DelayTime::create(25),CallFunc::create([this](){
                
                // 効果音再生
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/crystalize.m4a");
                
                // _text7をタグを指定して呼び出す
                auto _text7 = this->getChildByTag(13);
                // _text7を非表示にする
                _text7->setVisible(false);
                
                // _character4をタグ指定して呼び出す
                auto _character1 = this->getChildByTag(17);
                // _character4を非表示にする
                _character1->setVisible(false);
                
                
            }), NULL));
            
            
            this->runAction(Sequence::create(DelayTime::create(30),CallFunc::create([this](){
                
                // 画面サイズ指定
                auto visibleSize = Director::getInstance()->getVisibleSize();
                Point origin = Director::getInstance()->getVisibleOrigin();
                Director::getInstance()->setDisplayStats(false); // stats OFF*
                
                // 真紅さん・しーやさん・ゼロセリフ
                auto _text8 = Label::createWithTTF("真紅「一体何が・・・」\nしーや「起こっているの？」\nゼロ「キミたちはセイヴァーの力に導かれて\nこの世界にやってきたのか・・・\nキミたちに用はない・・・大人しく消えるといい」\n真紅・しーや「！？」", "fonts/ヒラギノ明朝 ProN W6.ttc",14);
                _text8->setPosition(Point(visibleSize.width / 2 + origin.x - 25, visibleSize.height / 2 + origin.y - 225));
                _text8->setTag(20);
                this->addChild(_text8,2);
                
                
            }), NULL));
            
            
            // 真紅さんとしーやさんも消えちゃった・・・(´・ω・`)
            this->runAction(Sequence::create(DelayTime::create(35),CallFunc::create([this](){
            
                // _text8をタグを指定して呼び出す
                auto _text8 = this->getChildByTag(20);
                // _text8を非表示にする
                _text8->setVisible(false);
                
                // _character3をタグ指定して呼び出す
                auto _character3 = this->getChildByTag(18);
                // _character4を非表示にする
                _character3->setVisible(false);
                
                // _character4をタグ指定して呼び出す
                auto _character4 = this->getChildByTag(19);
                // _character4を非表示にする
                _character4->setVisible(false);

                // イベントエンドフラグ
                _state = TYPE_EVENT_END;
            
            }), NULL));
            
            
        }
        
    }
    

}


// 一定時間後に削除実行するアクション
void StageScene4::intervalDeleteAction(float delta){
    
    // テキストタグ呼び出し
    auto _text2 = this->getChildByTag(6);
    // テキスト削除
    if(_text2  != nullptr){
        _text2 ->removeFromParent();
        _text2  = nullptr;
    }
    
    // クリスタルタグ呼び出し
    auto _crystal = this->getChildByTag(7);
    // クリスタル画像削除
    if(_crystal  != nullptr){
        _crystal ->removeFromParent();
        _crystal  = nullptr;
    }
    
    // クリスタル数値タグ呼び出し
    auto _crystalValue = this->getChildByTag(8);
    // クリスタル数値削除
    if(_crystalValue  != nullptr){
        _crystalValue ->removeFromParent();
        _crystalValue  = nullptr;
    }
    
    
}





