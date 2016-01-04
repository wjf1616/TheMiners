#ifndef								__SLIP_GUIDE_LAYER__
#define								__SLIP_GUIDE_LAYER__

#include "cocos2d.h"
#include "cocos-ext.h"



class SlipGuide:
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	SlipGuide(void);
	~SlipGuide(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SlipGuide, create);

	virtual void onEnter(void);
	virtual void onExit(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void setForwardLayer(cocos2d::CCLayer * _ccLayer, int _type);
	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);
	void doAnimationCompleted(void);

private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// 动画管理器

	cocos2d::CCLayer * forwardLayer;
	int forwardType;

	int isLeft;

	cocos2d::CCPoint m_touchBeginPos; // 开始触摸的位置
	cocos2d::CCPoint m_touchEndPos;// 结束触摸的位置
	bool m_touchMove;// 是否滑动或

	void setIsLeft(int _i);

	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
};

//class SlipGuide;
class CCBReader;

class SlipGuideLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SlipGuideLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SlipGuide);
};

#endif
