#pragma execution_character_set("utf-8") // 文字コード指定
#include "HelloWorldScene.h" // HelloWorldScene.h読み込み
#include "SimpleAudioEngine.h"// SimpleAudioEngine.h読み込み

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
    
    // チョコさん
    _character1 = BaseChara::create("res/chocoto.png");// スプライト画像読み込み
    _character1->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
    //_character1->setPosition(Vec2(origin.x + 150, origin.y + visibleSize.height / 2 + 300));// チョコっとコメントアウト
    _character1->setPosition(Vec2(origin.x + 550, origin.y + visibleSize.height / 2 - 80));// 位置指定
    _character1->setScale(2.0);// スプライトの拡大率を2.0倍に指定
    
    _character1->_hp = 100;// HP
    _character1->_attackPoint = 10;// 攻撃力
    this->addChild(_character1,1);// 画面描画
    
    Label* charaHp1 = Label::createWithTTF("HP", "fonts/ヒラギノ明朝 ProN W3.ttc" , 20);// HPフォント指定
    charaHp1->setColor(cocos2d::Color3B::BLACK);// フォントカラー指定
    charaHp1->setPosition(Vec2(510,140));// HPの文字位置指定
    this->addChild(charaHp1, 1, 0);// HPの文字描画
    
    _character1->_hpLabelPosX = 545;// HP数値X座標指定
    _character1->_hpLabelPosY = 140;// HP数値Y座標指定
    _character1->_hpLabel = _character1->createHpLabel();// HPラベル生成
    this->addChild(_character1->_hpLabel, 1, 0);// HP数値描画

    // 真紅さん
    _character2 = BaseChara::create("res/sinku.png");
    _character2->setAnchorPoint(Vec2(1.0,1.0));
    //sprite2->setPosition(Vec2(origin.x + 170, origin.y + visibleSize.height / 2 - 8));// チョコっとコメントアウト
    _character2->setPosition(Vec2(origin.x + 550, origin.y + visibleSize.height / 2 - 180));
    _character2->setScale(2.0);
    _character2->_hp = 100;
    _character2->_attackPoint = 10;
    this->addChild(_character2,1);

    Label* charaHp2 = Label::createWithTTF("HP", "fonts/ヒラギノ明朝 ProN W3.ttc" , 20);
    charaHp2->setColor(cocos2d::Color3B::BLACK);
    charaHp2->setPosition(Vec2(525,50));
    this->addChild(charaHp2, 1, 0);
    
    _character2->_hpLabelPosX = 560;
    _character2->_hpLabelPosY = 50;
    _character2->_hpLabel = _character2->createHpLabel();
    this->addChild(_character2->_hpLabel, 1, 0);
    
    // しーやさん
    _character3 = BaseChara::create("res/syiya.png");
    _character3->setAnchorPoint(Vec2(1.0,1.0));
    //sprite3->setPosition(Vec2(origin.x + 600, origin.y + visibleSize.height / 2 - 20));// チョコっとコメントアウト
    _character3->setPosition(Vec2(origin.x + 550, origin.y + visibleSize.height / 2 + 10));
    _character3->_hp = 100;
    _character3->_attackPoint = 10;
    _character3->setScale(2.0);
    
    this->addChild(_character3,1);
    
    Label* charaHp3 = Label::createWithTTF("HP", "fonts/ヒラギノ明朝 ProN W3.ttc" , 20);
    charaHp3->setColor(cocos2d::Color3B::BLACK);
    charaHp3->setPosition(Vec2(520,250));
    this->addChild(charaHp3, 1, 0);
    
    _character3->_hpLabelPosX = 555;
    _character3->_hpLabelPosY = 250;
    _character3->_hpLabel = _character3->createHpLabel();
    this->addChild(_character3->_hpLabel, 1, 0);
    
    // ミラさん
    _character4 = BaseChara::create("res/mira.png");
    _character4->setAnchorPoint(Vec2(1.0,1.0));
    //sprite4->setPosition(Vec2(origin.x + 580, origin.y + visibleSize.height / 2 + 230)); // チョコっとコメントアウト
    _character4->setPosition(Vec2(origin.x + 550, origin.y + visibleSize.height / 2 + 100));
    _character4->setScale(2.0);
    _character4->_hp = 100;
    _character4->_attackPoint = 10;
    this->addChild(_character4, 1);
    
    Label* charaHp4 = Label::createWithTTF("HP", "fonts/ヒラギノ明朝 ProN W3.ttc" , 20);
    charaHp4->setColor(cocos2d::Color3B::BLACK);
    charaHp4->setPosition(Vec2(510,320));
    this->addChild(charaHp4, 1, 0);
    
    _character4->_hpLabelPosX = 545;
    _character4->_hpLabelPosY = 320;
    _character4->_hpLabel = _character4->createHpLabel();
    this->addChild(_character4->_hpLabel, 1, 0);
    
    
    // エネミー1
    _enemy1 = BaseChara::create("res/Cactuar.png");
    _enemy1->setAnchorPoint(Vec2(1.0,1.0));
    _enemy1->setPosition(Vec2(origin.x + 150, origin.y + visibleSize.height / 2 - 150));
    _enemy1->setScale(2.0);
    //sprite->setRotation(90.0); // チョコっとコメントアウト
    _enemy1->_hp = 100;
    _enemy1->_attackPoint = 10 * arc4random_uniform(10);// 敵の攻撃力設定 0〜90で変化
    this->addChild(_enemy1,1);
    
    Label* enemyHp1 = Label::createWithTTF("HP", "fonts/ヒラギノ明朝 ProN W3.ttc" , 20);
    enemyHp1->setColor(cocos2d::Color3B::BLACK);
    enemyHp1->setPosition(Vec2(45,180));
    this->addChild(enemyHp1, 1, 0);
    
    _enemy1->_hpLabelPosX = 80;
    _enemy1->_hpLabelPosY = 180;
    _enemy1->_hpLabel = _enemy1->createHpLabel();
    this->addChild(_enemy1->_hpLabel, 1, 0);

    
    // エネミー2
    _enemy2 = BaseChara::create("res/Cactuar.png");
    _enemy2->setAnchorPoint(Vec2(1.0,1.0));
    _enemy2->setPosition(Vec2(origin.x + 150, origin.y + visibleSize.height / 2));
    _enemy2->setScale(2.0);
    //sprite->setRotation(90.0); // チョコっとコメントアウト
    _enemy2->_hp = 100;
    _enemy2->_attackPoint = 10 * arc4random_uniform(10);// 敵の攻撃力設定 0〜90で変化
    this->addChild(_enemy2,1);
    
    Label* enemyHp2 = Label::createWithTTF("HP", "fonts/ヒラギノ明朝 ProN W3.ttc" , 20);
    enemyHp2->setColor(cocos2d::Color3B::BLACK);
    enemyHp2->setPosition(Vec2(45,30));
    this->addChild(enemyHp2, 1, 0);
    
    _enemy2->_hpLabelPosX = 80;
    _enemy2->_hpLabelPosY = 30;
    _enemy2->_hpLabel = _enemy2->createHpLabel();
    this->addChild(_enemy2->_hpLabel, 1, 0);

    
    // オープニング背景
    /* チョコっとコメントアウト
    auto background = Sprite::create("res/crystalTower.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);
    */
    
    // ステージ1背景表示
    auto background2 = Sprite::create("res/knowledge_plain.png");
    background2->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background2,0);
    
    // 更新メソッド定期呼び出し
    this->scheduleUpdate();

    
    return true;

}

// バトル更新処理
void HelloWorld::update(float delta){
    
    // 味方のターン
    if(_state == TYPE_PLAYER_TURN){
        
        
    }
    
    // 敵のターン
    if(_state == TYPE_ENEMY_TURN){
        
        
    }
    
}



