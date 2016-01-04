#ifndef			__SETTINGMENU_H__
#define			__SETTINGMENU_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class SettingMenu:
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	SettingMenu(void);
	~SettingMenu(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SettingMenu, create);

	virtual void onEnter(void);
	virtual void onExit(void);

	virtual void keyBackClicked(void);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void PlayAnimation(int _id);

	void onMenuItemOffClicked(cocos2d::CCObject * pSender);

	void setForwardLayer(cocos2d::CCLayer * _ccLayer, int _layerType);
	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void musicValueChanged(CCObject* sender, cocos2d::extension::CCControlEvent controlEvent);
	void backMusicValueChanged(CCObject* sender, cocos2d::extension::CCControlEvent controlEvent);
	void doAnimationCompleted(void);

private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ∂Øª≠π‹¿Ì∆˜

	cocos2d::CCLayer * forwardLayer;
	int forwardType;

	cocos2d::extension::CCControlSwitch *music ;
	cocos2d::extension::CCControlSwitch *backMusic;

	bool isDoAction;

	bool musicBackGround;
	bool musicEffect;
};

#endif