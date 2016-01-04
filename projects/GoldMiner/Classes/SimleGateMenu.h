#ifndef			__SIMLEGATEMENU_H__
#define			__SIMLEGATEMENU_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Global.h"


class SimleGateMenu :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	SimleGateMenu(void);
	~SimleGateMenu(void);
	void onEnterTransitionDidFinish(void);

	virtual void onExit();

	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SimleGateMenu, create);
	//static SimleGateMenu * create(int _bigGateIndex) {
	//	SimleGateMenu * ptr = new SimleGateMenu(_bigGateIndex); 
	//	if(ptr != NULL && ptr->init()) { 
	//		ptr->autorelease(); 
	//		return ptr; 
	//	} 
	//	CC_SAFE_DELETE(ptr); 
	//	return NULL;
	//}
	virtual void keyBackClicked(void);

	virtual void onEnter(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);


	void onMenuItemBackClicked(cocos2d::CCObject * pSender);
	void onMenuItemNextClicked(cocos2d::CCObject * pSender);
	void onMenuItemForwardClicked(cocos2d::CCObject * pSender);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void startSelf(void);
	void setLoadingLayer(cocos2d::CCLayer * _layer);

	void setBackGround(bool _b);
private:
	bool isBackGround;

	cocos2d::CCLayer * loadingLayer;

	cocos2d::CCLayerColor * greyLayer;// 灰色层
	//bool isStartPosition;// 是否是1-6node为可显示状态
	bool isFrist;// 是否是刚进来

	int currPageIndex;// 当前的页面值
	int smileGateNum;//小关数量
	int pageNum;// 页面数

	bool isInitRect;

	cocos2d::CCArray * pointSprites; // 灰色小点
	cocos2d::CCSprite * pointIndexSprite;// 亮的小点

	cocos2d::CCArray * smileGateId;//小关对象的gateid
	cocos2d::CCArray * smileGateIdOpen;// 小关对象的gateid信息
	cocos2d::CCArray * smileGateIdStar;// 小关对象的gateid信息

	cocos2d::CCArray * gateNum;
	cocos2d::CCArray * gateOpenItems;	// 关卡item显示sprite
	cocos2d::CCArray * gateCloseItems;	// 关卡item显示sprite
	cocos2d::CCArray * gateItemGetStars;// 关卡item星星显示sprite
	cocos2d::CCArray * gateItemUnGetStars;// 关卡item星星显示sprite
	cocos2d::CCArray * pageSprites;

	//cocos2d::CCArray * hidePets;// 隐藏关卡需要的宠物个数

	cocos2d::extension::CCBAnimationManager * mAnimationManager;// 动画管理器

	cocos2d::CCPoint m_touchBeginPos; // 开始触摸的位置
	cocos2d::CCPoint m_touchEndPos;// 结束触摸的位置
	cocos2d::CCRect mButton[6];//自己button的位置
	bool m_touchMove;// 是否滑动或
	int selectSimleGateButtonIndex;

	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void initGateIdInformation(void);
	void setCurrPageIndex(bool _isXiangZuo);
	void initItemSprite(void);
	void doAction(float _f);
	void checkButtonEvent(void);
	void initHidePets(void);
};

#endif
