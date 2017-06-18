#ifndef  _APP_DELEGATE_H_ // 重複定義の回避 _APP_DELEGATE_H_ は記号定数
#define  _APP_DELEGATE_H_ //

#include "cocos2d.h" // cocos2d.hインクルード

/**
@brief    The cocos2d Application.

Private inheritance here hides part of interface from Director.
*/
class  AppDelegate : private cocos2d::Application // cocos2d::Applicationクラスから派生 AppDelegateクラス作成
{
public:
    AppDelegate();// コンストラクタ呼び出し
    virtual ~AppDelegate();// デストラクタが発生している仮想関数を呼び出す

    virtual void initGLContextAttrs(); // OpenGLに関する各種設定を行う

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching(); // アプリケーションが起動された時の処理を行う

    /**
    @brief  Called when the application moves to the background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground(); // アプリケーションがバックグラウンドに回った際の処理を用意する

    /**
    @brief  Called when the application reenters the foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground(); // アプリケーションがバックグラウンドからフォアグラウンドに戻った時の処理を用意する 一時停止中の状態からゲームを再開する場合に必要な処理はこの仮想関数で用意する
    
};

#endif // _APP_DELEGATE_H_

