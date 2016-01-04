#ifndef			__DRAWLAYER_H__
#define			__DRAWLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class DrawBox;

class DrawLayer:
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	DrawLayer(void);
	~DrawLayer(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(DrawLayer, create);

	virtual void onEnter(void);
	virtual void onExit(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void doAction(float _f);

	void onMenuItemOffClicked(cocos2d::CCObject * pSender);
	void onMenuItemConfirmClicked(cocos2d::CCObject * pSender);

	void setForwardLayer(cocos2d::CCLayer * _ccLayer);
	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);
	void doAnimationCompleted(void);

	void promptFinish(bool _isDraw);
private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// 动画管理器

	cocos2d::CCLayerColor * greyLayer;
	cocos2d::CCLayer * forwardLayer;
	cocos2d::CCSprite * awardImage;
	cocos2d::CCArray * boxs;
	cocos2d::CCSprite * costImage;
	cocos2d::CCLabelAtlas * costNum;
	cocos2d::CCParticleSystemQuad * mSystem;

	bool isBackGround;

	float timeCount;
	float timeCheckCount;
	bool isTimeCount;

	int drawCount;

	int step;

	int touchIndex;

	void initBoxs(void);
	void upDateCost(void);
	void setStep(int _step);


	cocos2d::CCPoint m_touchBeginPos; // 开始触摸的位置
	cocos2d::CCPoint m_touchEndPos;// 结束触摸的位置
	bool m_touchMove;// 是否滑动或

	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
};

class DrawBox:
	public cocos2d::CCNode
{
public:
	DrawBox(int _level, int _type);
	~DrawBox(void);

	int doAction(float _f);
	bool getIsGetAward(void);

	void openBox(void);
	void closeBox(void);
	cocos2d::CCSprite * getAward(void);
private: 
	cocos2d::CCSprite * awardImage;
	cocos2d::CCSprite * boxImage;

	bool isGetAward;

	float timeCount;
	int index;
	int status;// 宝箱的状态
	int level;// 宝箱等级
	int type;// 宝箱的类型
	void setImageByIndex(void);
};

#endif