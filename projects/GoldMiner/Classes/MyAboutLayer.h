#ifndef			__MYMYABOUTLAYER_H__
#define			__MYMYABOUTLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class MyAboutLayer:
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	MyAboutLayer(void);
	~MyAboutLayer(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MyAboutLayer, create);

	virtual void onEnter(void);
	virtual void onExit(void);

	virtual void keyBackClicked(void);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void onMenuItemOffClicked(cocos2d::CCObject * pSender);
	void calXiaoShiFinish(CCNode* sender);

	void setForwardLayer(cocos2d::CCLayer * _ccLayer, int _layerType);
	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);
	void doAnimationCompleted(void);

private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ∂Øª≠π‹¿Ì∆˜

	cocos2d::CCLayer * forwardLayer;
	int forwardType;
	bool isDoAction;
};

#endif