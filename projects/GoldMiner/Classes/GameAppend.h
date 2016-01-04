#ifndef		__GAMEAPPEDN_H__
#define		__GAMEAPPEDN_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class GameAppend :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	GameAppend(void);
	~GameAppend(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameAppend, create);

	virtual void onExit(void);
	virtual void onEnter(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void doGuideInformation(int _guideId, int _step);

	void onMenuItemOffClicked(cocos2d::CCObject * pSender);

	void calFangShe1(CCNode* sender);
	void calFangShe2(CCNode* sender);

	void setForwardLayer(cocos2d::CCLayer *_ccLayer);

	void doJewelSkillEffect(int _jewelSkillId);

	void doAction(float _f);

	void doAnimationCompleted(void);
private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ∂Øª≠π‹¿Ì∆˜
	cocos2d::CCLayer * forwardLayer;
	bool isJewel;
	cocos2d::CCArray * texiaos;


	float xx[5];
	float yy[5];
	bool isCanTouch;
	bool isIntroduce;
	float timeCount;
	int introduceStep;
	virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* pevent);
};

#endif
