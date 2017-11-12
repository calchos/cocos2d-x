#pragma execution_character_set("utf-8") // 文字コード指定
#include "StageScene3.h" // StageScene3.h読み込み
#include "StageConversation5.hpp" // StageConversation3.hpp読み込み
#include "StageConversation6.hpp" // StageConversation4.hpp読み込み
#include "SimpleAudioEngine.h"// SimpleAudioEngine.h読み込み

USING_NS_CC; // #define USING_NS_CC using namespace cocos2d

Scene* StageScene3::createScene() //
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StageScene3::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


StageScene3::StageScene3(){
    // 何もしない
}

StageScene3::~StageScene3(){
    // シーンを移動するときに子をすべてremoveする
    removeAllChildrenWithCleanup(true);
}


// on "init" you need to initialize your instance
bool StageScene3::init()
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
    listener->onTouchBegan = CC_CALLBACK_2(StageScene3::onTouchBegan, this);// タップした瞬間に1回だけ処理を実行
    listener->onTouchEnded = CC_CALLBACK_2(StageScene3::onTouchEnded, this);// タップを離した瞬間に１回だけ実行
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);// イベントリスナーの組み込み
    
    // BGMプリロード
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/gurdians_fight.m4a");
    
    // BGM再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/gurdians_fight.m4a", true);
    
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
    
    
    // デルゼウム
    _enemy1 = BaseChara::create("res/delzeum.png");
    _enemy1->setAnchorPoint(Vec2(1.0,1.0));
    _enemy1->setPosition(Vec2(origin.x + visibleSize.height / 2 - 30, origin.y + visibleSize.height / 2 + 100));
    _enemy1->setScale(4.0);
    _enemy1->setTag(4);
    this->addChild(_enemy1,1);
    
    
    // 敵出現テキスト
    auto _text1 = Label::createWithSystemFont("デルゼウムがあらわれた！▼", "fonts/ヒラギノ明朝 ProN W6.ttc",15);
    _text1->setPosition(Point(visibleSize.width / 2 + origin.x - 60, visibleSize.height / 2 + origin.y - 180));
    _text1->setTag(5);// text1をタグ指定
    this->addChild(_text1,2);
    
    // テキスト表示ウィンドウ
    auto window = Sprite::create("res/menu_window_small.png");
    window->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 180));
    this->addChild(window,1);
    
    // ステージ2背景表示
    auto background2 = Sprite::create("res/central_crystal.png");
    background2->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background2,0);
    
    return true;
    
}


// 画面をタップした瞬間に1回だけ実行する時の処理
bool StageScene3::onTouchBegan(Touch* pTouch, Event* pEvent){
    
    // 戦闘に勝利したら会話シーン6の画面に遷移する
    if(_state == TYPE_WIN){
    
        // 現在流れている音楽を停止
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        
        Director::getInstance()->replaceScene(TransitionFade::create(2.0
                                                                     , StageConversation6::createScene()
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
        
        // 乱数初期化
        srand((unsigned int)time(NULL));
        int m = 0;// 乱数用変数の初期値
        _crystalPower1 = rand()%(m+99);
        
        // チョコっとさんの武器攻撃
        _character1 = BaseChara::create("res/chocoto_attack_01.png");// スプライト画像読み込み
        _character1->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
        _character1->setPosition(Vec2(origin.x + 400, origin.y + visibleSize.height / 2 + 100));// 位置指定
        _character1->setScale(2.0);// スプライトの拡大率を2.0倍に指定
        _character1->setTag(14);
        this->addChild(_character1,1);// 画面描画
        
        auto _text2 = Label::createWithSystemFont("チョコっとの武器攻撃。\nクリスタルがチョコっとに力を与える▼", "fonts/ヒラギノ明朝 ProN W6.ttc",18);
        _text2->setPosition(Point(visibleSize.width / 2 + origin.x - 30, visibleSize.height / 2 + origin.y - 180));
        _text2->setTag(6);
        this->addChild(_text2,2);
        
        
        // クリスタル画像
        auto _crystal = Sprite::create("res/crystal_light.png");
        _crystal->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystal->setScale(1.5f);
        _crystal->setTag(7);
        this->addChild(_crystal,0);
        
        // クリスタルパワー
        auto _crystalValue = Label::createWithSystemFont(StringUtils::toString(_crystalPower1),"fonts/ヒラギノ明朝 ProN W6.ttc",30);
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
        
        // 乱数初期化
        srand((unsigned int)time(NULL));
        int m = 0;// 乱数用変数の初期値
        _crystalPower2 = rand()%(m+99);
        
        // 真紅さんの歌う攻撃
        _character2 = BaseChara::create("res/sinku_attack_01.png");// スプライト画像読み込み
        _character2->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
        _character2->setPosition(Vec2(origin.x + 400, origin.y + visibleSize.height / 2 - 20));// 位置指定
        _character2->setScale(2.0);// スプライトの拡大率を2.0倍に指定
        this->addChild(_character2,1);// 画面描画
        
        auto _text2 = Label::createWithSystemFont("真紅の歌う攻撃。\nクリスタルが真紅に力を与える▼", "fonts/ヒラギノ明朝 ProN W6.ttc",18);
        _text2->setPosition(Point(visibleSize.width / 2 + origin.x - 50, visibleSize.height / 2 + origin.y - 180));
        _text2->setTag(6);
        this->addChild(_text2,2);
        
        
        // クリスタル画像
        auto _crystal = Sprite::create("res/crystal_fire.png");
        _crystal->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystal->setScale(1.5f);
        _crystal->setTag(7);
        this->addChild(_crystal,0);
        
        // クリスタルパワー
        auto _crystalValue = Label::createWithSystemFont(StringUtils::toString(_crystalPower2),"fonts/ヒラギノ明朝 ProN W6.ttc",30);
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
        
        // 乱数初期化
        srand((unsigned int)time(NULL));
        int m = 0;// 乱数用変数の初期値
        _crystalPower3 = rand()%(m+99);
        
        // しーやさんの魔法攻撃
        _character3 = BaseChara::create("res/syiya_attack_01.png");// スプライト画像読み込み
        _character3->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
        _character3->setPosition(Vec2(origin.x + 550, origin.y + visibleSize.height / 2 - 20));// 位置指定
        _character3->setScale(2.0);// スプライトの拡大率を2.0倍に指定
        this->addChild(_character3,1);// 画面描画
        
        auto _text2 = Label::createWithSystemFont("しーやの魔法攻撃。\nクリスタルがしーやに力を与える▼", "fonts/ヒラギノ明朝 ProN W6.ttc",18);
        _text2->setPosition(Point(visibleSize.width / 2 + origin.x - 50, visibleSize.height / 2 + origin.y - 180));
        _text2->setTag(6);//タグ付け
        this->addChild(_text2,2);
        
        
        // クリスタル画像
        auto _crystal = Sprite::create("res/crystal_water.png");
        _crystal->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystal->setScale(1.5f);
        _crystal->setTag(7);
        this->addChild(_crystal,0);
        
        // クリスタルパワー
        auto _crystalValue = Label::createWithSystemFont(StringUtils::toString(_crystalPower3),"fonts/ヒラギノ明朝 ProN W6.ttc",30);
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
        
        // 乱数初期化
        srand((unsigned int)time(NULL));
        int m = 0;// 乱数用変数の初期値
        _crystalPower4 = rand()%(m+99);
        
        // ミラさんのジャンプ攻撃
        _character4 = BaseChara::create("res/mira_attack_01.png");// スプライト画像読み込み
        _character4->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
        _character4->setPosition(Vec2(origin.x + 550, origin.y + visibleSize.height / 2 + 100));// 位置指定
        _character4->setScale(2.0);// スプライトの拡大率を2.0倍に指定
        this->addChild(_character4,1);// 画面描画
        
        auto _text2 = Label::createWithSystemFont("ミラのジャンプ攻撃。\nクリスタルがミラに力を与える▼", "fonts/ヒラギノ明朝 ProN W6.ttc",18);
        _text2->setPosition(Point(visibleSize.width / 2 + origin.x - 50, visibleSize.height / 2 + origin.y - 180));
        _text2->setTag(6);//タグ付け
        this->addChild(_text2,2);
        
        
        // クリスタル画像
        auto _crystal = Sprite::create("res/crystal_earth.png");
        _crystal->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystal->setScale(1.5f);
        _crystal->setTag(7);
        this->addChild(_crystal,0);
        
        // クリスタルパワー
        auto _crystalValue = Label::createWithSystemFont(StringUtils::toString(_crystalPower4),"fonts/ヒラギノ明朝 ProN W6.ttc",30);
        _crystalValue->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystalValue->setTag(8);
        this->addChild(_crystalValue,2);
        
        // プレイヤー4ターンフラグをTRUEにセット
        _player4Turn = true;
        
    }
    
    // 1秒後にintervalDeleteActionメソッドを呼ぶ
    this->scheduleOnce(schedule_selector(StageScene3::intervalDeleteAction),1.0f);
    
    // 更新メソッド定期呼び出し
    this->scheduleUpdate();
    
    return true;
}




// 画面のタップを離した瞬間に1回だけ実行する処理
void StageScene3::onTouchEnded(Touch* pTouch, Event* pEvent){
    
    // 何もしない
}


// バトル更新処理
void StageScene3::update(float delta){
    
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
        // 敵1がまだ攻撃していないとき
        if(!_enemy1->_doAttack){
            
            // 敵の先制攻撃処理呼び出し
            _preemptive_attack = enemyPreemptiveAttack();
            
            
            if(_preemptive_attack == true){
                // 攻撃フラグをtrueにする
                _enemy1->_doAttack = true;
            }
            
            // 2秒後にラムダ式を実行
            this->runAction(Sequence::create(DelayTime::create(2),CallFunc::create([this](){
                
                // 画面サイズ指定
                auto visibleSize = Director::getInstance()->getVisibleSize();
                Point origin = Director::getInstance()->getVisibleOrigin();
                Director::getInstance()->setDisplayStats(false); // stats OFF*
                
                // 効果音再生
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/crystal_sound.m4a");
                
                auto _text3 = Label::createWithSystemFont("デルゼウムのアームドブレイク。\nクリスタルがデルゼウムに力を与える▼", "fonts/ヒラギノ明朝 ProN W6.ttc",18);
                _text3->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 180));
                _text3->setTag(10);//タグ付け
                this->addChild(_text3,2);
                
                
                // クリスタル画像
                auto _enemyCrystal = Sprite::create("res/crystal_light.png");
                _enemyCrystal->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
                _enemyCrystal->setScale(1.5f);
                _enemyCrystal->setTag(11);
                this->addChild(_enemyCrystal,0);
                
                // 敵のクリスタルパワー
                auto _enemyCrystalValue = Label::createWithSystemFont(StringUtils::toString(_enemyCrystalPower),"fonts/ヒラギノ明朝 ProN W6.ttc",30);
                _enemyCrystalValue->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
                _enemyCrystalValue->setTag(12);
                this->addChild(_enemyCrystalValue,2);
                
                log("敵のクリスタル力");
                log("%i",_enemyCrystalPower);
                
                
                
            }), NULL));
            
            
            // プレイヤーのトータルクリスタル数値計算処理
            int _totalCrystalPower = playerAttack();
            
            log("プレイヤーの総合クリスタルパワー");
            log("%i",_totalCrystalPower);
            // 敵のトータルクリスタル数値計算処理
            int _totalEnemyCrystalPower = enemyAttack();
            // デバッグログ
            log("敵の総合クリスタルパワー");
            log("%i",_totalEnemyCrystalPower);
            
            
            // イベント発生
            _state = TYPE_EVENT_OCCURRED;

            
        }
        
    }
    
    // イベント発生ターン
    else if(_state == TYPE_EVENT_OCCURRED){
        
        if(!_gameEndEvent){
            _gameEndEvent = true;
            
            
            // 4秒後にテキスト表示
            this->runAction(Sequence::create(DelayTime::create(4),CallFunc::create([this](){
            
            
                // _text3をタグを指定して呼び出す
                auto _text3 = this->getChildByTag(10);
                // _text3を非表示にする
                _text3->setVisible(false);
                
                auto _enemyCrystal = this->getChildByTag(11);
                _enemyCrystal->setVisible(false);
                
                auto _enemyCrystalValue = this->getChildByTag(12);
                _enemyCrystalValue->setVisible(false);

                
                // 画面サイズ指定
                auto visibleSize = Director::getInstance()->getVisibleSize();
                Point origin = Director::getInstance()->getVisibleOrigin();
                Director::getInstance()->setDisplayStats(false); // stats OFF*
                
                // チョコさんピンチ！(；´Д｀)
                auto _text4 = Label::createWithTTF("チョコっと「強い…このままじゃ私たちやられちゃう…」", "fonts/ヒラギノ明朝 ProN W6.ttc",15);
                _text4->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 180));
                _text4->setTag(13);
                this->addChild(_text4,2);
                
                }), NULL));
            
            // 6秒後に誰かの声が聞こえてくる
            this->runAction(Sequence::create(DelayTime::create(6),CallFunc::create([this](){
                
                auto visibleSize = Director::getInstance()->getVisibleSize();
                Point origin = Director::getInstance()->getVisibleOrigin();
                Director::getInstance()->setDisplayStats(false); // stats OFF*
                
                auto _text4 = this->getChildByTag(13);
                _text4->setVisible(false);
                
                // 効果音再生
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/crystal_sound.m4a");
                
                auto _text5 = Label::createWithTTF("？？？「あきらめないで…今一度クリスタルをかかげるのよ…」", "fonts/ヒラギノ明朝 ProN W6.ttc",20);
                _text5->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 200));
                _text5->setTag(15);
                this->addChild(_text5,2);
                
                
                
            }), NULL));
            
            
            // 8秒後にクリスタル展開！！タンバリン♪と叫ぶ！
            this->runAction(Sequence::create(DelayTime::create(8),CallFunc::create([this](){
                
                auto visibleSize = Director::getInstance()->getVisibleSize();
                Point origin = Director::getInstance()->getVisibleOrigin();
                Director::getInstance()->setDisplayStats(false); // stats OFF*
                
                auto _text5 = this->getChildByTag(15);
                _text5->setVisible(false);
                
                auto _text6 = Label::createWithSystemFont("チョコっと「うん！わかった！クリスタル展開！！タンバリン♪」", "fonts/ヒラギノ明朝 ProN W6.ttc",15);
                _text6->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 180));
                _text6->setTag(16);
                this->addChild(_text6,2);
                
                
            }), NULL));
            
            // 10秒後にチョコさん姿が変わる！
            this->runAction(Sequence::create(DelayTime::create(10),CallFunc::create([this](){
                
                auto visibleSize = Director::getInstance()->getVisibleSize();
                Point origin = Director::getInstance()->getVisibleOrigin();
                Director::getInstance()->setDisplayStats(false); // stats OFF*
                
                auto _character1 = this->getChildByTag(14);
                _character1->setVisible(false);
                
                auto _text6 = this->getChildByTag(16);
                _text6->setVisible(false);
                
                // 効果音再生
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/crystal_sound.m4a");
            
                // セイヴァーチョコさん
                _character1 = BaseChara::create("res/crystal_deploy_chocoto.png");// スプライト画像読み込み
                _character1->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
                _character1->setPosition(Vec2(origin.x + 400, origin.y + visibleSize.height / 2 + 100));// 位置指定
                _character1->setScale(2.0);// スプライトの拡大率を2.0倍に指定
                this->addChild(_character1,1);// 画面描画
                
            }), NULL));
            
            //  セイヴァーマスターカルチョス？登場
            this->runAction(Sequence::create(DelayTime::create(12),CallFunc::create([this](){
                
                auto visibleSize = Director::getInstance()->getVisibleSize();
                Point origin = Director::getInstance()->getVisibleOrigin();
                Director::getInstance()->setDisplayStats(false); // stats OFF*
                
                // 効果音再生
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/suppress.m4a");

                _character5 = BaseChara::create("res/crystal_deploy_calchos.png");// スプライト画像読み込み
                _character5->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
                _character5->setPosition(Vec2(origin.x + 320, origin.y + visibleSize.height / 2 - 20));// 位置指定
                _character5->setScale(2.0);// スプライトの拡大率を2.0倍に指定
                this->addChild(_character5,1);// 画面描画
                
                auto _text7 = Label::createWithSystemFont("？？？「間に合ったか！こいつは自分が抑える！\n今のうちにクリスタルの力を使うんだ！」", "fonts/ヒラギノ明朝 ProN W6.ttc",15);
                _text7->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 180));
                _text7->setTag(17);
                this->addChild(_text7,2);
                
                
            }), NULL));
            
            // チョコさんクリスタル展開
            this->runAction(Sequence::create(DelayTime::create(15),CallFunc::create([this](){
                
                auto visibleSize = Director::getInstance()->getVisibleSize();
                Point origin = Director::getInstance()->getVisibleOrigin();
                Director::getInstance()->setDisplayStats(false); // stats OFF*
                
                auto _text7 = this->getChildByTag(17);
                _text7->setVisible(false);
                
                // 効果音再生
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/crystal_sound.m4a");
                
                auto _text8 = Label::createWithTTF("チョコっとのライトバードウェーブ。\nクリスタルがチョコっとに力を与える▼", "fonts/ヒラギノ明朝 ProN W6.ttc",15);
                _text8->setPosition(Point(visibleSize.width / 2 + origin.x - 50, visibleSize.height / 2 + origin.y - 180));
                _text8->setTag(18);//タグ付け
                this->addChild(_text8,2);
                
                
                // クリスタル画像
                auto _crystal = Sprite::create("res/crystal_light.png");
                _crystal->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
                _crystal->setScale(1.5f);
                _crystal->setTag(19);
                this->addChild(_crystal,0);
                
                // クリスタル展開時のクリスタルパワー
                _crystalPower1 = 700;
                
                // クリスタルパワー
                auto _crystalValue = Label::createWithSystemFont(StringUtils::toString(_crystalPower1),"fonts/ヒラギノ明朝 ProN W6.ttc",30);
                _crystalValue->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
                _crystalValue->setTag(20);
                this->addChild(_crystalValue,2);
                
                
                
            }), NULL));
            
            
            // デルゼウム消滅
            this->runAction(Sequence::create(DelayTime::create(18),CallFunc::create([this](){
               
                auto visibleSize = Director::getInstance()->getVisibleSize();
                Point origin = Director::getInstance()->getVisibleOrigin();
                Director::getInstance()->setDisplayStats(false); // stats OFF*
                
                // テキスト8非表示
                auto _text8 = this->getChildByTag(18);
                _text8->setVisible(false);
                
                // クリスタル画像非表示
                auto _crystal = this->getChildByTag(19);
                _crystal->setVisible(false);
                
                // クリスタル数値非表示
                auto _crystalValue = this->getChildByTag(20);
                _crystalValue->setVisible(false);
                
                // デルゼウム非表示
                auto _enemy1 = this->getChildByTag(4);
                _enemy1->setVisible(false);
                
                // 勝利メッセージ
                auto _text9 = Label::createWithSystemFont("デルゼウムをやっつけた！▼", "fonts/ヒラギノ明朝 ProN W6.ttc",18);
                _text9->setPosition(Point(visibleSize.width / 2 + origin.x - 60, visibleSize.height / 2 + origin.y - 180));
                this->addChild(_text9,2);
                
                // プレイヤー勝利
                 _state = TYPE_WIN;
                
            
            }), NULL));
            
        }
        
    }
    

}


// 一定時間後に削除実行するアクション
void StageScene3::intervalDeleteAction(float delta){
    
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

// プレイヤーのトータルダメージ計算処理
int StageScene3::playerAttack(){
    
    int _crystalValueArray[] = {_crystalPower1,_crystalPower2,_crystalPower3,_crystalPower4};// クリスタル値を配列に格納する
    
    int _crystalPowers = 0;
    // _tatalCrystalValueを出力する
    for(int _totalCrystalValue : _crystalValueArray){
        
        // デバッグログ
        //log("%i",_totalCrystalValue);
        // 総合クリスタル値
        _crystalPowers += _totalCrystalValue;
        // デバッグログ
        //log("%i",_crystalPowers);
        
    }
    
    return _crystalPowers;
}

// 敵のトータルダメージ計算処理
int StageScene3::enemyAttack(){
    
    // 乱数初期化
    srand((unsigned int)time(NULL));
    // 敵のクリスタル数値
    _enemyCrystalPower = 600;
    
    int _enemyCrystalValueArray[] = {_enemyCrystalPower};// クリスタル値を配列に格納する
    int _enemyCrystalPowers = 0;
    // _tatalCrystalValueを出力する
    for(int _totalEnemyCrystalValue : _enemyCrystalValueArray){
        
        // 総合クリスタル値
        _enemyCrystalPowers += _totalEnemyCrystalValue;
        // デバッグログ
        //log("%i",_enemyCrystalPowers);
        
    }
    
    return _enemyCrystalPowers;
}

// 先制防御
int StageScene3::playerPredefense(){
    
    // 乱数初期化
    srand((unsigned int)time(NULL));
    
    int m = 0;// 乱数用変数の初期値
    int r = rand()%(m+1); // 0～1の乱数を発生させrに代入
    
    // 敵の攻撃を避けれるか
    if(r == 1){
        _preemptive_attack = true; // 先制攻撃フラグをtrueにする
        auto _text4 = Label::createWithSystemFont("味方たちは敵の攻撃を避けた！", "fonts/ヒラギノ明朝 ProN W6.ttc", 48);
        _text4->setPosition(Point(300, 200));
        this->addChild(_text4,1);
    }
    
    return 0;
    
}


// 敵キャラクターの先制攻撃処理
int StageScene3::enemyPreemptiveAttack(){
    
    // 乱数初期化
    srand((unsigned int)time(NULL));
    
    int m = 0;// 乱数用変数の初期値
    int r = rand()%(m+1); // 0～1の乱数を発生させrに代入
    
    // 先制攻撃するか？
    if(r == 1){
        _preemptive_attack = true; // 先制攻撃フラグをtrueにする
        auto _text5 = Label::createWithSystemFont("デルゼウムは全身を震わせ雄叫びを唱えた！", "fonts/ヒラギノ明朝 ProN W6.ttc", 48);
        _text5->setPosition(Point(300, 200));
        this->addChild(_text5,1);
    }
    
    return 0;
    
    
}
