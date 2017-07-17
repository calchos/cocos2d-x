#pragma execution_character_set("utf-8") // 文字コード指定
#include "StageConversation.hpp" 
#include "StageScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC; // #define USING_NS_CC using namespace cocos2d

Scene* StageConversation::createScene() // シーン生成処理
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StageConversation::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StageConversation::init() // 初期化処理
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
    listener->onTouchBegan = CC_CALLBACK_2(StageConversation::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    // BGMプリロード
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/chocoto_tambourine.m4a");
    
    // BGM再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/chocoto_tambourine.m4a", true);
    
    
    // テキストの内容
    auto _text1 = Label::createWithTTF("あれぇ〜？ここどこだろう？？\nチョコちゃんﾉｼ\nあっ！ミラさんだ！\nあれ？ここどこだろう？\n夢ノ国なのかしら？\nあっ！真紅さんにしーちゃんだ！！\nチョコちゃんうしろ！うしろ！⬇\n","fonts/ヒラギノ明朝 ProN W6.ttc", 20);
    // テキストの位置指定
    _text1->setPosition(Vec2(visibleSize.width / 2 - 50 , visibleSize.height / 4));
    // テキストの文字色指定
    _text1->setColor(Color3B::WHITE);
    _text1->setOpacity(0);// テキストの透明化
    _text1->setTag(1);// _text1をタグ指定
    this->addChild(_text1,1);// テキストを表示
    
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
        //
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
    _character1->setFlippedX(true);// スプライトの向き反転
    this->addChild(_character1,1);// 画面描画
    
    // 真紅さん
    _character2 = BaseChara::create("res/sinku.png");
    _character2->setAnchorPoint(Vec2(1.0,1.0));
    _character2->setPosition(Vec2(origin.x + 580, origin.y + visibleSize.height / 2 - 50));
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
    _character4->setPosition(Vec2(origin.x + 590, origin.y + visibleSize.height / 2 + 50));
    _character4->setScale(2.0);
    this->addChild(_character4, 1);
    
    
    // 背景
    auto background = Sprite::create("res/knowledge_plain.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);
    
    return true;
    
}


bool StageConversation::onTouchBegan(Touch* pTouch, Event* pEvent){
    
    
    // 画面サイズ指定
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    Director::getInstance()->setDisplayStats(false); // stats OFF*
    
    auto _text1 = this->getChildByTag(1);
    _text1->setVisible(false);

    // テキストの内容
    auto _text2 = Label::createWithTTF("えっ？あっ！なにあのサボテンみたいなの！？\nよーし！みんなであのサボテンさんを\nチョコっとやっつけちゃおう！\n","fonts/ヒラギノ明朝 ProN W6.ttc", 20);
    // テキストの位置指定
    _text2->setPosition(Vec2(visibleSize.width / 2 - 50 , visibleSize.height / 4));
    // テキストの文字色指定
    _text2->setColor(Color3B::WHITE);
    _text2->setOpacity(0);// テキストの透明化
    this->addChild(_text2,1);// テキストを表示
    
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
        //
        auto delay = DelayTime::create(.2 * i);
        // 複数のアクションを順番に実行 delay→func
        auto seq = Sequence::create(delay, func, nullptr);
        // テキスト文字列がヌルポインタではない場合はアクション実行
        if(_text2->getLetter(i) != nullptr){
            _text2->getLetter(i)->runAction(seq);
        }
        
    }
    
    // チョコさん向き反転
    _character1->setFlippedX(false);// スプライトの向き反転

    // MenuItemImageでメニューボタン追加 引数にはボタンを押した時の動作を指定
     auto nextButton = MenuItemImage::create("res/next.png","res/next_pushed.png",CC_CALLBACK_1(StageConversation::nextSceneCallback, this));
     nextButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4 - 140));// ボタンの位置を画面中央に指定
     auto menu = Menu::create(nextButton, NULL);//
     menu->setPosition(Vec2::ZERO);
     this->addChild(menu, 1, 0);
     
    
    // エネミー1
    _enemy1 = BaseChara::create("res/cactuar.png");
    _enemy1->setAnchorPoint(Vec2(1.0,1.0));
    _enemy1->setPosition(Vec2(origin.x + 400, origin.y + visibleSize.height / 2 ));
    _enemy1->setScale(2.0);
    this->addChild(_enemy1,1);
    
    
    // 背景
    auto background = Sprite::create("res/knowledge_plain.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);
    
    return true;
}




void StageConversation::nextSceneCallback(Ref* pSender){
    
    // 効果音再生
    // CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/button_push.m4a");
    
    // BGMの停止
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    // replaceSceneで画面遷移を行う Openingを破棄して0.5秒かけてホワイトアウトしてStageに遷移する
    Director::getInstance()->replaceScene(TransitionRotoZoom::create(0.5,StageScene::createScene()));
}
