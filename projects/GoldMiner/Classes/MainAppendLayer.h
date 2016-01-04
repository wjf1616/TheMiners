#ifndef		__MainAppendLayer_H__
#define		__MainAppendLayer_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class MainAppendLayer :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	MainAppendLayer(void);
	~MainAppendLayer(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainAppendLayer, create);

	virtual void onEnter(void);
	virtual void onExit(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager, cocos2d::CCLayer * _ccLayer);

	void onMenuItemPlayClicked(cocos2d::CCObject * pSender);
	void onMenuItemSetupClicked(cocos2d::CCObject * pSender);
	void onMenuItemShopClicked(cocos2d::CCObject * pSender);
	void onMenuItemBattleClicked(cocos2d::CCObject * pSender);
	void onMenuItemStoryClicked(cocos2d::CCObject * pSender);
	void onMenuItemHelpClicked(cocos2d::CCObject * pSender);
	void onMenuItemAboutClicked(cocos2d::CCObject * pSender);
	void onMenuItemMonsterClicked(cocos2d::CCObject * pSender);
	void onMenuItemMoreClicked(cocos2d::CCObject * pSender);
	void onMenuItemBackClicked(cocos2d::CCObject * pSender);
	void onMenuItemOffClicked(cocos2d::CCObject * pSender);
	void onMenuItemRankClicked(cocos2d::CCObject * pSender);
	void onMenuItemMoreGameClicked(cocos2d::CCObject * pSender);
	void onMenuItemExitClicked(cocos2d::CCObject * pSender);



	void onGetChallengeDateCompleted(cocos2d::CCNode *sender, void *data);

	void startSelf(void);

	void calJiXuFinish(CCNode* sender);

	void doAnimationCompleted(void);

	void reBack(void);

	void reBackWithVisiable(void);

	void doAction(float _f);

	virtual void keyBackClicked(void);
	void setBackGround(bool _b);

	void spotLighLayerCallBack(void);
private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// 动画管理器

	bool isSpot;
	CCObject * spotLighLayer;

	bool isDoAction;

	bool isBackGround;

	bool isDianJiContinues;// 记录是否点击了继续

	bool isSelectModel;
	bool isCanExit;

	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	cocos2d::CCLayer * forward;
	cocos2d::CCLayer * grey;
};

#endif