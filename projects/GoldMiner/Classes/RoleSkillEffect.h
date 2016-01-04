#ifndef		__ROLE_SKILL_EFFECT_H__
#define		__ROLE_SKILL_EFFECT_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class RoleSkillEffect :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	RoleSkillEffect(void);
	~RoleSkillEffect(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(RoleSkillEffect, create);

	virtual void onExit(void);
	virtual void onEnter(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void setForwardLayer(cocos2d::CCLayer *_ccLayer);

	void doSkillEffect(int _roleId);

	void calXiaoShiFinish(CCNode* sender);

	void doAnimationCompleted(void);
private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ∂Øª≠π‹¿Ì∆˜
	cocos2d::CCLayer * forwardLayer;
};

#endif
