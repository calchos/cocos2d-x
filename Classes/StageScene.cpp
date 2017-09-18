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
    listener->onTouchBegan = CC_CALLBACK_2(StageScene::onTouchBegan, this);//タッチしたときに1回だけ処理を実行
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);// イベントリスナーの組み込み
    
    // BGMプリロード
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/first encounter.m4a");
    
    // BGM再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/first encounter.m4a", true);
    

    
    // チョコさん
    _character1 = BaseChara::create("res/chocoto.png");// スプライト画像読み込み
    _character1->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
    _character1->setPosition(Vec2(origin.x + 400, origin.y + visibleSize.height / 2 + 100));// 位置指定
    _character1->setScale(2.0);// スプライトの拡大率を2.0倍に指定
    
    _character1->_powerPoint = 0;
    this->addChild(_character1,1);// 画面描画
    
    /* todo HP実装
    Label* charaHp1 = Label::createWithTTF("HP", "fonts/ヒラギノ明朝 ProN W3.ttc" , 20);// HPフォント指定
    charaHp1->setColor(cocos2d::Color3B::BLACK);// フォントカラー指定
    charaHp1->setPosition(Vec2(510,140));// HPの文字位置指定
    this->addChild(charaHp1, 1, 0);// HPの文字描画
    */
    
    /*
    _character1->_hpLabelPosX = 545;// HP数値X座標指定
    _character1->_hpLabelPosY = 140;// HP数値Y座標指定
    _character1->_hpLabel = _character1->createHpLabel();// HPラベル生成
    this->addChild(_character1->_hpLabel, 1, 0);// HP数値描画
    */

    // 真紅さん
    _character2 = BaseChara::create("res/sinku.png");
    _character2->setAnchorPoint(Vec2(1.0,1.0));
    _character2->setPosition(Vec2(origin.x + 400, origin.y + visibleSize.height / 2 - 20));
    _character2->setScale(2.0);
    
    _character2->_powerPoint = 10;
    this->addChild(_character2,1);
    
    /* todo HP実装
    Label* charaHp2 = Label::createWithTTF("HP", "fonts/ヒラギノ明朝 ProN W3.ttc" , 20);
    charaHp2->setColor(cocos2d::Color3B::BLACK);
    charaHp2->setPosition(Vec2(525,50));
    this->addChild(charaHp2, 1, 0);
    
    _character2->_hpLabelPosX = 560;
    _character2->_hpLabelPosY = 50;
    _character2->_hpLabel = _character2->createHpLabel();
    this->addChild(_character2->_hpLabel, 1, 0);
    */
    
    // しーやさん
    _character3 = BaseChara::create("res/syiya.png");
    _character3->setAnchorPoint(Vec2(1.0,1.0));
    _character3->setPosition(Vec2(origin.x + 550, origin.y + visibleSize.height / 2 - 20));
    
    
    _character3->_powerPoint = 10;
    _character3->setScale(2.0);
    
    this->addChild(_character3,1);
    
    /* todo HP実装
    Label* charaHp3 = Label::createWithTTF("HP", "fonts/ヒラギノ明朝 ProN W3.ttc" , 20);
    charaHp3->setColor(cocos2d::Color3B::BLACK);
    charaHp3->setPosition(Vec2(520,250));
    this->addChild(charaHp3, 1, 0);
    
    _character3->_hpLabelPosX = 555;
    _character3->_hpLabelPosY = 250;
    _character3->_hpLabel = _character3->createHpLabel();
    this->addChild(_character3->_hpLabel, 1, 0);
    */
    
    // ミラさん
    _character4 = BaseChara::create("res/mira.png");
    _character4->setAnchorPoint(Vec2(1.0,1.0));
    _character4->setPosition(Vec2(origin.x + 550, origin.y + visibleSize.height / 2 + 100));
    _character4->setScale(2.0);
    
    
    _character4->_powerPoint = 10;
    this->addChild(_character4, 1);
    
    /* todo HP実装
    Label* charaHp4 = Label::createWithTTF("HP", "fonts/ヒラギノ明朝 ProN W3.ttc" , 20);
    charaHp4->setColor(cocos2d::Color3B::BLACK);
    charaHp4->setPosition(Vec2(510,320));
    this->addChild(charaHp4, 1, 0);
    
    _character4->_hpLabelPosX = 545;
    _character4->_hpLabelPosY = 320;
    _character4->_hpLabel = _character4->createHpLabel();
    this->addChild(_character4->_hpLabel, 1, 0);
    */
     
    // エネミー1
    _enemy1 = BaseChara::create("res/cactuar.png");
    _enemy1->setAnchorPoint(Vec2(1.0,1.0));
    _enemy1->setPosition(Vec2(origin.x + 150, origin.y + visibleSize.height / 2 - 10));
    _enemy1->setScale(2.0);
    // _enemy1->_hp = 100;
    //_enemy1->_attackPoint = 10 * arc4random_uniform(10);// 敵の攻撃力設定 0〜90で変化
    this->addChild(_enemy1,1);
    
    /* HP実装
    Label* enemyHp1 = Label::createWithTTF("HP", "fonts/ヒラギノ明朝 ProN W3.ttc" , 20);
    enemyHp1->setColor(cocos2d::Color3B::BLACK);
    enemyHp1->setPosition(Vec2(45,180));
    this->addChild(enemyHp1, 1, 0);
    
    _enemy1->_hpLabelPosX = 80;
    _enemy1->_hpLabelPosY = 180;
    _enemy1->_hpLabel = _enemy1->createHpLabel();
    this->addChild(_enemy1->_hpLabel, 1, 0);
    */

    // 敵出現テキスト
    auto _text1 = Label::createWithSystemFont("ソダテンダーがあらわれた！▼", "fonts/ヒラギノ明朝 ProN W3.ttc",18);
    _text1->setPosition(Point(visibleSize.width / 2 + origin.x - 60, visibleSize.height / 2 + origin.y - 180));
    _text1->setTag(1);// text1をタグ指定
    this->addChild(_text1,2);
    
    // テキスト表示ウィンドウ
    auto window = Sprite::create("res/menu_window_small.png");
    window->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 180));
    this->addChild(window,1);
    
    
    // ステージ1背景表示
    auto background2 = Sprite::create("res/knowledge_plain.png");
    background2->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background2,0);
    
    // 更新メソッド定期呼び出し
    this->scheduleUpdate();

    
    return true;

}


// 画面をタッチした時の処理
bool StageScene::onTouchBegan(Touch* pTouch, Event* pEvent){
    
    // 画面サイズ指定
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    Director::getInstance()->setDisplayStats(false); // stats OFF*
    
    // _text1をタグを指定して呼び出す
    auto _text1 = this->getChildByTag(1);
    // _text1を非表示にする
    _text1->setVisible(false);

    auto _text2 = Label::createWithSystemFont("クリスタルがチョコっとに力を与える▼", "fonts/ヒラギノ明朝 ProN W3.ttc",18);
    _text2->setPosition(Point(visibleSize.width / 2 + origin.x - 30, visibleSize.height / 2 + origin.y - 180));
    this->addChild(_text2,2);

    
    

    return true;
}


// バトル更新処理
void StageScene::update(float delta){
    
    // 味方のターン
    if(_state == TYPE_PLAYER_TURN){
        
 
        // 攻撃処理
        
        
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
    
    m = 0;// 乱数用変数の初期値
    r = rand()%(m+1); // 0～1の乱数を発生させrに代入
    
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
    
    m = 0;// 乱数用変数の初期値
    r = rand()%(m+1); // 0～1の乱数を発生させrに代入
    
    // 先制攻撃するか？
    if(r == 1){
        _preemptive_attack = true; // 先制攻撃フラグをtrueにする
        auto text = Label::createWithSystemFont("ソダテンダーは針を100本飛ばしてきた！", "fonts/ヒラギノ明朝 ProN W3.ttc", 48);
        text->setPosition(Point(300, 200));
        this->addChild(text,1);
    }
    
    return true;
}






