#ifndef		__PROMPTLAYER_H__
#define		__PROMPTLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class PromptLayer :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	PromptLayer(void);
	~PromptLayer(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PromptLayer, create);

	virtual void onExit(void);
	virtual void onEnter(void);

	virtual void keyBackClicked(void);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void onMenuItemOffClicked(cocos2d::CCObject * pSender);
	void onMenuItemConfirmClicked(cocos2d::CCObject * pSender);

	void setForwardLayer(cocos2d::CCLayer *_ccLayer, int _type);

	void doGuideAward(int _guideId);// 获得引导奖励提示

	void doGamingTip(int _tipId);// 获得引导奖励提示

	void doGuideWin(void);// 获得引导奖励提示

	void miaoZhunXianInformation(void);// 瞄准线提示

	void miaoBuddahaInformation(void);// 佛光提示

	void bigGateNotOpen(void);// 大关卡没有开启

	void simleGateNotOpen(void);// 小关卡没有开启

	void hideGateNotOpen(int _hideGateId, cocos2d::CCArray * _array);// 隐藏没有开启

	void notOpen(void); // 暂未开放

	void challengeGateNotOpen(void); // 挑战模式没有开启

	void challengeGateOpen(void); // 挑战模式没有开启

	void challengeGateOut(void);// 挑战模式推出提示

	void challengeGateReplay(void);// 挑战模式重玩提示

	void addNewRole(void);// 开启新的人物角色

	void payRoleIsHaving(void);// 计费点任务已经拥有

	void addNewGate(int _mapId);// 开启新的人物角色

	void addNewHideGate(int _hideGateId);// 开始隐藏关卡

	void targetInformationByTargetId(int targetId);// 道具介绍

	void specailFood(void);// 是否要人生果提示
	
	void isCheer(void);// 是否助阵提示

	void isChallengeShopBack(void);

	void isBack(void);// 是否确定返回

	void isReplay(void);// 是否确定重玩

	void jewelInformation(void);// 宝石技能信息
	void moonLightInformation(void);// 宝石技能信息
	void roleIntruduceById(int _roleId);

	void petParkInformation(void);// 宠物窝相关说明

	void drawOpenCost(const char _cost[]);// 开宝箱提示

	void doAnimationCompleted(void);
private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// 动画管理器
	cocos2d::CCLayer * forwardLayer;
	int forwardType;

	int type;

	bool isAward;
	float timeCount;
};

#endif

