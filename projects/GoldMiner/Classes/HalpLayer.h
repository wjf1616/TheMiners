#ifndef			__HALPLAYER_H__
#define			__HALPLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class HalpLayer:
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	HalpLayer(void);
	~HalpLayer(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(HalpLayer, create);

	virtual void onEnter(void);
	virtual void onExit(void);

	virtual void keyBackClicked(void);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void PlayAnimation(int _id);

	void onMenuItemOffClicked(cocos2d::CCObject * pSender);
	void onMenuItemLeftClicked(cocos2d::CCObject * pSender);
	void onMenuItemRightClicked(cocos2d::CCObject * pSender);

	void setForwardLayer(cocos2d::CCLayer * _ccLayer, int _layerType);
	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);
	void calXiaoShiFinish(CCNode* sender);

	void doAnimationCompleted(void);

private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// 动画管理器

	cocos2d::CCLayer * forwardLayer;

	bool isDoAction;

	cocos2d::CCArray * helpsSprite;
	int currIndex;
	int forwardType;
	cocos2d::CCArray * pointSprites;

	cocos2d::CCSprite * pointIndexSprite;// 亮的小点

	cocos2d::CCSprite * getSpriteByIndex(int _index);
	void setInformation(int _index);
};

#endif