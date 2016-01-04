#ifndef			__EXITLAYER_H__
#define			__EXITLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class ExitLayer:
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	ExitLayer(void);
	~ExitLayer(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ExitLayer, create);

	virtual void onEnter(void);
	virtual void onExit(void);

	virtual void keyBackClicked(void);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void onMenuItemExitClicked(cocos2d::CCObject * pSender);
	void onMenuItemContinueClicked(cocos2d::CCObject * pSender);

	void setForwardLayer(cocos2d::CCLayer * _ccLayer);
	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);
	void doAnimationCompleted(void);

private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ∂Øª≠π‹¿Ì∆˜

	cocos2d::CCLayer * forwardLayer;

	bool isAction;
	bool isExit;
};

#endif