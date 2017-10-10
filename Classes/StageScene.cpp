#pragma execution_character_set("utf-8") // 文字コード指定
#include "StageScene.h" // HelloWorldScene.h読み込み
#include "SimpleAudioEngine.h"// SimpleAudioEngine.h読み込み

USING_NS_CC; // #define USING_NS_CC using namespace cocos2d

Scene* StageScene::createScene() //
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StageScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StageScene::init()
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
    listener->onTouchBegan = CC_CALLBACK_2(StageScene::onTouchBegan, this);// タップした瞬間に1回だけ処理を実行
    listener->onTouchEnded = CC_CALLBACK_2(StageScene::onTouchEnded, this);// タップを離した瞬間に１回だけ実行
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);// イベントリスナーの組み込み
    
    // BGMプリロード
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/first encounter.m4a");
    
    // BGM再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/first encounter.m4a", true);
    
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
    

    // エネミー1(ここではソダテンダー)
    _enemy1 = BaseChara::create("res/cactuar.png");
    _enemy1->setAnchorPoint(Vec2(1.0,1.0));
    _enemy1->setPosition(Vec2(origin.x + 150 + 50, origin.y + visibleSize.height / 2 ));
    _enemy1->setScale(2.0);
    this->addChild(_enemy1,1);

    // 敵出現テキスト
    auto _text1 = Label::createWithSystemFont("ソダテンダーがあらわれた！▼", "fonts/ヒラギノ明朝 ProN W3.ttc",18);
    _text1->setPosition(Point(visibleSize.width / 2 + origin.x - 60, visibleSize.height / 2 + origin.y - 180));
    _text1->setTag(4);// text1をタグ指定
    this->addChild(_text1,2);
    
    // テキスト表示ウィンドウ
    auto window = Sprite::create("res/menu_window_small.png");
    window->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 180));
    this->addChild(window,1);

    // ステージ1背景表示
    auto background2 = Sprite::create("res/knowledge_plain.png");
    background2->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background2,0);
    
    
    return true;

}


// 画面をタップした瞬間に1回だけ実行する時の処理
bool StageScene::onTouchBegan(Touch* pTouch, Event* pEvent){
    
    // キャラクタータグ呼び出し
    auto _character1 = this->getChildByTag(0);
    auto _character2 = this->getChildByTag(1);
    auto _character3 = this->getChildByTag(2);
    auto _character4 = this->getChildByTag(3);
    
    // 画面サイズ指定
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    Director::getInstance()->setDisplayStats(false); // stats OFF*
    
    // 乱数初期化
    srand((unsigned int)time(NULL));
    
    int m = 0;// 乱数用変数の初期値
    int _crystalPower = rand()%(m+99); // 0～100の乱数を発生させrに代入
    
    // _text1タグ呼び出し
    auto _text4 = this->getChildByTag(4);
    // _text1を非表示にする
    _text4->setVisible(false);
    
    // 効果音再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/crystal_sound.m4a");
    
    // タップした座標を取得
    Vec2 touchPoint = convertTouchToNodeSpace(pTouch);
    
    
    // チョコっとさんのスプライト範囲をタップしたときの処理
    if(_character1->getBoundingBox().containsPoint(touchPoint)){
        
        _character1->setVisible(false);
        
        // チョコっとさんの武器攻撃
        _character5 = BaseChara::create("res/chocoto_attack_01.png");// スプライト画像読み込み
        _character5->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
        _character5->setPosition(Vec2(origin.x + 400, origin.y + visibleSize.height / 2 + 100));// 位置指定
        _character5->setScale(2.0);// スプライトの拡大率を2.0倍に指定
        this->addChild(_character5,1);// 画面描画
        
        auto _text2 = Label::createWithSystemFont("チョコっとの武器攻撃。\nクリスタルがチョコっとに力を与える▼", "fonts/ヒラギノ明朝 ProN W3.ttc",18);
        _text2->setPosition(Point(visibleSize.width / 2 + origin.x - 30, visibleSize.height / 2 + origin.y - 180));
        _text2->setTag(5);
        this->addChild(_text2,2);
        
        
        // クリスタル画像
        auto _crystal = Sprite::create("res/crystal_light.png");
        _crystal->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystal->setScale(1.5f);
        _crystal->setTag(6);
        this->addChild(_crystal,0);
        
        // クリスタルパワー
        auto _crystalValue = Label::createWithSystemFont(StringUtils::toString(_crystalPower),"fonts/ヒラギノ明朝 ProN W3.ttc",30);
        _crystalValue->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystalValue->setTag(7);
        this->addChild(_crystalValue,2);
        
    }
    
    // 真紅さんのスプライト範囲をタップしたときの処理
    if(_character2->getBoundingBox().containsPoint(touchPoint)){
        
        auto _text2 = Label::createWithSystemFont("真紅の武器攻撃。\nクリスタルが真紅に力を与える▼", "fonts/ヒラギノ明朝 ProN W3.ttc",18);
        _text2->setPosition(Point(visibleSize.width / 2 + origin.x - 30, visibleSize.height / 2 + origin.y - 180));
        _text2->setTag(5);
        this->addChild(_text2,2);
        
        
        // クリスタル画像
        auto _crystal = Sprite::create("res/crystal_light.png");
        _crystal->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystal->setScale(1.5f);
        _crystal->setTag(6);
        this->addChild(_crystal,0);
        
        // クリスタルパワー
        auto _crystalValue = Label::createWithSystemFont(StringUtils::toString(_crystalPower),"fonts/ヒラギノ明朝 ProN W3.ttc",30);
        _crystalValue->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystalValue->setTag(7);
        this->addChild(_crystalValue,2);
        
    }
    

    // しーやさんのスプライト範囲をタップしたときの処理
    if(_character3->getBoundingBox().containsPoint(touchPoint)){
        
        auto _text2 = Label::createWithSystemFont("しーやの魔法攻撃。\nクリスタルがしーやに力を与える▼", "fonts/ヒラギノ明朝 ProN W3.ttc",18);
        _text2->setPosition(Point(visibleSize.width / 2 + origin.x - 30, visibleSize.height / 2 + origin.y - 180));
        _text2->setTag(5);//タグ付け
        this->addChild(_text2,2);
        
        
        // クリスタル画像
        auto _crystal = Sprite::create("res/crystal_light.png");
        _crystal->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystal->setScale(1.5f);
        _crystal->setTag(6);
        this->addChild(_crystal,0);
        
        // クリスタルパワー
        auto _crystalValue = Label::createWithSystemFont(StringUtils::toString(_crystalPower),"fonts/ヒラギノ明朝 ProN W3.ttc",30);
        _crystalValue->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystalValue->setTag(7);
        this->addChild(_crystalValue,2);
        
    }
    
    // ミラさんをタップした場合の処理
    if(_character4->getBoundingBox().containsPoint(touchPoint)){
        
        auto _text2 = Label::createWithSystemFont("ミラのジャンプ攻撃。\nクリスタルがミラに力を与える▼", "fonts/ヒラギノ明朝 ProN W3.ttc",18);
        _text2->setPosition(Point(visibleSize.width / 2 + origin.x - 30, visibleSize.height / 2 + origin.y - 180));
        _text2->setTag(5);//タグ付け
        this->addChild(_text2,2);
        
        
        // クリスタル画像
        auto _crystal = Sprite::create("res/crystal_light.png");
        _crystal->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystal->setScale(1.5f);
        _crystal->setTag(6);
        this->addChild(_crystal,0);
        
        // クリスタルパワー
        auto _crystalValue = Label::createWithSystemFont(StringUtils::toString(_crystalPower),"fonts/ヒラギノ明朝 ProN W3.ttc",30);
        _crystalValue->setPosition(Point(visibleSize.width / 2 + origin.x - 2, visibleSize.height / 2 + origin.y + 150));
        _crystalValue->setTag(7);
        this->addChild(_crystalValue,2);
        
    }

    // 更新メソッド定期呼び出し
    this->scheduleUpdate();
    
    

    return true;
}

// 画面のタップを離した瞬間に1回だけ実行する処理
void StageScene::onTouchEnded(Touch* pTouch, Event* pEvent){
    
    // テキストタグ呼び出し
    auto _text2 = this->getChildByTag(5);
     // テキスト削除
    if(_text2  != nullptr){
        _text2 ->removeFromParent();
        _text2  = nullptr;
    }

    // クリスタルタグ呼び出し
    auto _crystal = this->getChildByTag(6);
    // クリスタル画像削除
    if(_crystal  != nullptr){
        _crystal ->removeFromParent();
        _crystal  = nullptr;
    }
    
    // クリスタル数値タグ呼び出し
    auto _crystalValue = this->getChildByTag(7);
    // クリスタル数値削除
    if(_crystalValue  != nullptr){
        _crystalValue ->removeFromParent();
        _crystalValue  = nullptr;
    }
}


// バトル更新処理
void StageScene::update(float delta){
    
    // 味方のターン
    if(_state == TYPE_PLAYER_TURN){
        
        

        
        
        // ターン交代
        _state = TYPE_ENEMY_TURN;
        
        
        
        
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

            
            
      
            
            
            

            // ターン交代
            _state = TYPE_PLAYER_TURN;
            
        }
        
        
    }
    
    
    // 勝利イベント
    else if(_state == TYPE_WIN){
        
    }
    
    
    // 敗北イベント
    else if(_state == TYPE_LOSE){
        
    }
}


// プレイヤーのトータルダメージ計算処理
int StageScene::playerAttack(){
    
    // 乱数初期化
    srand((unsigned int)time(NULL));
    

    
    
    
    
    return true;
}

// 先制防御
int StageScene::playerPredefense(){
    
    // 乱数初期化
    srand((unsigned int)time(NULL));
    
    int m = 0;// 乱数用変数の初期値
    int r = rand()%(m+1); // 0～1の乱数を発生させrに代入
    
    // 敵の攻撃を避けれるか
    if(r == 1){
        _preemptive_attack = true; // 先制攻撃フラグをtrueにする
        auto text = Label::createWithSystemFont("味方たちは敵の攻撃を避けた！", "fonts/ヒラギノ明朝 ProN W3.ttc", 48);
        text->setPosition(Point(300, 200));
        this->addChild(text,1);
    }
    
    return true;
}


// 敵キャラクターの先制攻撃処理
int StageScene::enemyPreemptiveAttack(){
    
    // 乱数初期化
    srand((unsigned int)time(NULL));
    
    int m = 0;// 乱数用変数の初期値
    int r = rand()%(m+1); // 0～1の乱数を発生させrに代入
    
    // 先制攻撃するか？
    if(r == 1){
        _preemptive_attack = true; // 先制攻撃フラグをtrueにする
        auto text = Label::createWithSystemFont("ソダテンダーは針を100本飛ばしてきた！", "fonts/ヒラギノ明朝 ProN W3.ttc", 48);
        text->setPosition(Point(300, 200));
        this->addChild(text,1);
    }
    
    return true;
}






