#ifndef		__PAUSEMENU_H__
#define		__PAUSEMENU_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class PauseMenu :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	PauseMenu(void);
	~PauseMenu(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PauseMenu, create);

	virtual void onExit(void);

	virtual void keyBackClicked(void);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	
	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void setForwardLayer(cocos2d::CCLayer *_ccLayer);

	void onMenuItemShopClicked(cocos2d::CCObject * pSender);
	void onMenuItemMenuClicked(cocos2d::CCObject * pSender);
	void onMenuItemReplayClicked(cocos2d::CCObject * pSender);
	void onMenuItemContinueClicked(cocos2d::CCObject * pSender);
	void onMenuItemSetClicked(cocos2d::CCObject * pSender);
	void onMenuItemHelpClicked(cocos2d::CCObject * pSender);

	void doAnimationCompleted(void);

	void reBack(void);

	void reBackWithVisiable(void);

	void reBack2(bool _b);

	void doAction(float _f);

private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ∂Øª≠π‹¿Ì∆˜

	bool isDoAction;

	int xiaoshiType;
	//int currSceneId;
	bool isChallenge;
	bool isGuide;


	cocos2d::CCSprite * trySprite;
	cocos2d::CCSprite * tryNum;

	cocos2d::CCSprite * level;
	cocos2d::CCLabelAtlas * levelNum;
	cocos2d::CCLabelAtlas * currMapIdLabel;
	cocos2d::CCLabelAtlas * currSceneIdLabel;
	int currSceneIdLabelControl;
	cocos2d::CCSprite * hengGang;

	cocos2d::CCLayer * forwardLayer;

	void doXiaoShiAnimation(void);
	void setIsDoAction(bool _b);
};

#endif