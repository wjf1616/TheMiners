#ifndef		__COUNTDOWN_EFFECT_H__
#define		__COUNTDOWN_EFFECT_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class CountDownEffect :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	CountDownEffect(void);
	~CountDownEffect(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CountDownEffect, create);

	virtual void onExit(void);
	virtual void onEnter(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void calThree(CCNode* sender);
	
	void calTwo(CCNode* sender);
	
	void calOne(CCNode* sender);
	
	void calStart(CCNode* sender);

	void setForwardLayer(cocos2d::CCLayer *_ccLayer);

	void doCountDownEffect(int _roleId);

	void doAction(float _f);

	void onMenuItemShopClicked(cocos2d::CCObject * pSender);

	void doAnimationCompleted(void);
private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ∂Øª≠π‹¿Ì∆˜
	cocos2d::CCLayer * forwardLayer;

	cocos2d::CCSprite * target;
	cocos2d::CCSprite * jifen;
	cocos2d::CCLabelAtlas * num;

	bool isCount;
	int count;
};

#endif
