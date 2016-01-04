#ifndef		__ROLE_INFORMATION_H__
#define		__ROLE_INFORMATION_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class RoleInformation :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	RoleInformation(void);
	~RoleInformation(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(RoleInformation, create);

	virtual void onExit(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	
	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void setForwardLayer(cocos2d::CCLayer *_ccLayer);

	void onMenuItemUnlockClicked(cocos2d::CCObject * pSender);
	void onMenuItemBuyClicked(cocos2d::CCObject * pSender);
	void onMenuItemOffClicked(cocos2d::CCObject * pSender);

	void doAnimationCompleted(void);

	void InformationReBack(void);

	void getRoleAboutInfromationByRoleId(int _roleId);
	void getRoleGetInfromationByRoleId(int _roleId);

private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ∂Øª≠π‹¿Ì∆˜

	bool isBackGround;
	bool isBuy;

	int roleId;

	cocos2d::CCLayer * forwardLayer;
};

#endif
