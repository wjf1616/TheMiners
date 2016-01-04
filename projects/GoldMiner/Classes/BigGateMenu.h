#ifndef		__BIGMENU_H__
#define		__BIGMENU_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class BigGateMenu :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	BigGateMenu(void);
	~BigGateMenu(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(BigGateMenu, create);

	virtual void onEnter(void);
	void onEnterTransitionDidFinish(void);
	virtual void onExit(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void doAction(float _f);

	void setBackGround(bool _b);

	void reBackWithVisiable(void);

	void reBackBackClicked(bool _b);

	virtual void keyBackClicked(void);

	void onMenuItemBackClicked(CCObject* pSender);
	void onMenuItemShopClicked(CCObject* pSender);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void startSelf(void);
	void setLoadingLayer(cocos2d::CCLayer * _layer);
	void doAnimationCompleted(void);

	void setCurrPageIndex(bool _isXiangZuo);
private:
	bool isDoAction;
	bool isBackGround;
	
	cocos2d::CCLayer * loadingLayer;
	
	cocos2d::CCLayerColor * greyLayer;// 灰色层

	int currPageIndex;// 当前的页面值

	cocos2d::CCArray * pointSprites; // 灰色小点
	cocos2d::CCSprite * pointIndexSprite;// 亮的小点

	bool isSelectMyButton;

	cocos2d::CCRect * myButton;//中心检测按钮的矩阵 

	cocos2d::CCArray * selectGateSprites;// 人物形象
	cocos2d::CCArray * selectFrameSprites;// 框的形象
	cocos2d::CCArray * selectSuoSprites;// 框的形象
	cocos2d::CCSprite * selectGateTitleSprites;// 人物形象

	cocos2d::CCArray * gateSprites;// 关卡对应的显示
	cocos2d::CCArray * gateFrameSprites;// 关卡框的形象
	cocos2d::CCArray * gateSuoSprites;// 关卡框的形象
	cocos2d::CCArray * gateTitleSprites;// 人物形象

	cocos2d::extension::CCBAnimationManager *mAnimationManager;// 动画管理器

	cocos2d::CCPoint m_touchBeginPos; // 开始触摸的位置
	cocos2d::CCPoint m_touchEndPos;// 结束触摸的位置
	bool m_touchMove;// 是否滑动或

	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void checkButtonEvent(void);
	void setNodeBySelectIndex(bool _isXiangZuo);
};

#endif

