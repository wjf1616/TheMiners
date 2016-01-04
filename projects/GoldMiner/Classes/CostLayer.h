#ifndef		__COSTLAYER_H__
#define		__COSTLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class CostLayer :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	CostLayer(void);
	~CostLayer(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CostLayer, create);

	virtual void onExit(void);
	virtual void onEnter(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void setForwardLayer(cocos2d::CCLayer *_ccLayer, int _type);

	void onMenuItemOpenClicked(cocos2d::CCObject * pSender);
	void onMenuItemBuyClicked(cocos2d::CCObject * pSender);
	void onMenuItemOffClicked(cocos2d::CCObject * pSender);

	void costGenuine(int _index, cocos2d::CCCallFunc * _success, cocos2d::CCCallFunc * _false);	// 正版验证


	void costById(int _costId, cocos2d::CCCallFunc * _success, cocos2d::CCCallFunc * _false);// 根据付费id获得付费值

	void doAnimationCompleted(void);
private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// 动画管理器
	cocos2d::CCLayer * forwardLayer;
	int forwardType;

	bool isCostGenuine;
	bool isCost;

	cocos2d::CCCallFunc* paySuccess;
	cocos2d::CCCallFunc* payFailed;

	int costId;
};

#endif

