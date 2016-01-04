#ifndef			__REGISTERLAYER_H__
#define			__REGISTERLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class RegisterLayer:
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	RegisterLayer(void);
	~RegisterLayer(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(RegisterLayer, create);

	virtual void onEnter(void);
	virtual void onExit(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void onMenuItemKnowClicked(cocos2d::CCObject * pSender);
	void onMenuItemReceiveClicked(cocos2d::CCObject * pSender);

	void setForwardLayer(cocos2d::CCLayer * _ccLayer);
	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void doAnimationCompleted(void);
	void getRegisterWard(int _count);

	void startSelf(void);

	void setBackGround(bool _b);

	void tempPromptReBack(void);

private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ∂Øª≠π‹¿Ì∆˜

	cocos2d::CCLayer * forwardLayer;

	int day;

	int registerCount;
	bool isFull;
	bool isBackGround;

	void initByCount(int _count);
};

#endif