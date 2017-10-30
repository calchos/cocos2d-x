#pragma execution_character_set("utf-8") // 文字コード指定
#include "OpeningTextScene.hpp"
#include "StageConversation.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC; // #define USING_NS_CC using namespace cocos2d

Scene* OpeningText::createScene() // シーン生成処理
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = OpeningText::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool OpeningText::init() // 初期化処理
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
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/to_the_future_with_light.m4a");
    
    // BGM再生
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/to_the_future_with_light.m4a", true);
    
    // テキストの内容
    auto text = Label::createWithTTF("セントラルタワーの天辺に出現したクリスタル。\nそれは世界の全てをコントロールする力を持っており\nセントラルクリスタルと呼ばれていた。\nそのクリスタルから突如闇の力が解き放たれ\n世界に魔物が溢れようとしていた。\nこの危機に4人のクリスタルを守護する者\nーークリスタルセイヴァーが召喚される。\n果たして彼らは世界の危機を救うことができるのだろうか…。\n","fonts/ヒラギノ明朝 ProN W3.ttc", 20);
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
    
    // MenuItemImageでメニューボタン追加 引数にはボタンを押した時の動作を指定
    
    auto nextButton = MenuItemImage::create("res/next.png","res/next_pushed.png",CC_CALLBACK_1(OpeningText::nextSceneCallback, this));
    nextButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4 - 140));// ボタンの位置を画面中央に指定
    auto menu = Menu::create(nextButton, NULL);//
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1, 0);
    
    

    // オープニングテキスト背景
    auto background = Sprite::create("res/crystal_tower_shadow.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background,0);
    
    return true;
    
}

// 次のシーンへ遷移するためのコールバック関数
void OpeningText::nextSceneCallback(Ref* pSender){
    
    
    // BGMの停止
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    // replaceSceneで画面遷移を行う Openingを破棄して0.7秒かけてホワイトアウトしてStageConvasationに遷移する
    Director::getInstance()->replaceScene(TransitionFade::create(0.7,StageConversation::createScene()));
}
