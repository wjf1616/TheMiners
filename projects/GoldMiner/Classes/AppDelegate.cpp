#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "GoldenMinerScene.h"
#include "Global.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();// ����CCEGLView* ����
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(800, 480);
	pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);//������ƽ�������Ĵ�С

	CCSize frameSize = pEGLView->getFrameSize();//��õ�ǰ��������ʵ����Ļ�Ŀ��

    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //CCScene *pScene = HelloWorld::scene();
    CCLog("app-a");
	Global::getInstance()->s = new GoldenMinerScene();
	//GoldenMinerScene *s = new GoldenMinerScene();

    // run
    pDirector->runWithScene(Global::getInstance()->s->getSence());
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
