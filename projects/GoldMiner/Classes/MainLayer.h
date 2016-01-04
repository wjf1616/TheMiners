#ifndef		__MAINLAYER_H__
#define		__MAINLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class MainLayer :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	MainLayer(void);
	~MainLayer(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainLayer, create);

	virtual void onEnter(void);
	virtual void onEnterTransitionDidFinish(void);
	virtual void onExit(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	//virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	//void calChuXianFinish(CCNode* sender);

	void setIsBackGround(bool _isGrey);

	void doAnimationCompleted(void);

	void startSelf(void);

	void setIsFrist(bool _b);

	bool getIsCheckRegister(void);

	void registerReBack(bool _b);
	void exitReBack(bool _b);
	void exitInit(void);

	cocos2d::CCLayer * getLoadingLayer(void);

	void setLoadingLayer(cocos2d::CCLayer * _layer);

	virtual void keyBackClicked(void);

	bool isExit;
private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ∂Øª≠π‹¿Ì∆˜

	cocos2d::CCLayer * loadingLayer;

	cocos2d::CCLayer * registerLayer;
	cocos2d::CCLayer * appendLayer;

	cocos2d::CCLayerColor * greyLayer;

	bool isInChuXian;

	bool isFrist;

	bool isCheckRegister;

	bool isCanTouch;

	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
};

#endif