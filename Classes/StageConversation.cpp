#pragma execution_character_set("utf-8") // 文字コード指定
#include "StageConversation.hpp" 
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
    
    // BGMプリロード
    // CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/to_the_future_with_light.m4a");
    
    // BGM再生
    // CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/to_the_future_with_light.m4a", true);
    
    // テキストの内容
    auto text = Label::createWithTTF("チョコっと「あれぇ〜？ここどこだろう？？」","fonts/ヒラギノ明朝 ProN W3.ttc", 20);
    // テキストの位置指定
    text->setPosition(Vec2(visibleSize.width / 2 + 30 , visibleSize.height / 4));
    // テキストの文字色指定
    text->setColor(Color3B::WHITE);
    text->setOpacity(0);// テキストの透明化
    this->addChild(text,1);// テキストを表示
    
    // テキストの透明化解除
    // テキストの長さ分 forループ回す
    for(int i = 0; i < text->getStringLength(); i++){
        
        // ラムダ式 []はキャプチャ
        auto func = CallFunc::create([this, i, text](){
            // 指定の文字列を返す
            Sprite* sp = text->getLetter(i);
            // spがヌルポインタでない場合
            if(sp != nullptr){
                text->getLetter(i)->setOpacity(255); //テキストを1文字ずつ透明化解除
            }
        });
        //
        auto delay = DelayTime::create(.2 * i);
        // 複数のアクションを順番に実行 delay→func
        auto seq = Sequence::create(delay, func, nullptr);
        // テキスト文字列がヌルポインタではない場合はアクション実行
        if(text->getLetter(i) != nullptr){
            text->getLetter(i)->runAction(seq);
        }
        
    }
    
    // チョコさん
    _character1 = BaseChara::create("res/chocoto.png");// スプライト画像読み込み
    _character1->setAnchorPoint(Vec2(1.0,1.0));// アンカーポイント指定
    _character1->setPosition(origin.x + 500, origin.y + visibleSize.height / 2 );// 位置指定
    _character1->setScale(2.0);// スプライトの拡大率を2.0倍に指定
    this->addChild(_character1,1);// 画面描画
    
    // MenuItemImageでメニューボタン追加 引数にはボタンを押した時の動作を指定
    /*
    auto nextButton = MenuItemImage::create("res/next.png","res/next_pushed.png",CC_CALLBACK_1(OpeningText::nextSceneCallback, this));
    nextButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4 - 140));// ボタンの位置を画面中央に指定
    auto menu = Menu::create(nextButton, NULL);//
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1, 0);
    */
    
    
    // オープニングテキスト背景
    auto background = Sprite::create("res/knowledge_plain.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);
    
    return true;
    
}

/*
void StageConversation::nextSceneCallback(Ref* pSender){
    
    // 効果音再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/button_push.m4a");
    
    // BGMの停止
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    // replaceSceneで画面遷移を行う Openingを破棄して0.5秒かけてホワイトアウトしてStageに遷移する
    Director::getInstance()->replaceScene(TransitionFade::create(0.5,Stage::createScene(),Color3B::WHITE));
}
 */
