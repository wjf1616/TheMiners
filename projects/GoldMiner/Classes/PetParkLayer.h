#ifndef			__PET_PARK_LAYER_H__
#define			__PET_PARK_LAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class Pet;

class PetParkLayer:
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	PetParkLayer(void);
	~PetParkLayer(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PetParkLayer, create);

	virtual void onEnter(void);
	virtual void onEnterTransitionDidFinish(void);

	virtual void keyBackClicked(void);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	
	void reBackBackClicked(bool _b);

	void onMenuItemBackClicked(cocos2d::CCObject * pSender);
	void onMenuItemPlus1Clicked(cocos2d::CCObject * pSender);
	void onMenuItemPlus2Clicked(cocos2d::CCObject * pSender);
	void onMenuItemCheerClicked(cocos2d::CCObject * pSender);
	void onMenuItemTeachClicked(cocos2d::CCObject * pSender);
	void onMenuItemMeatClicked(cocos2d::CCObject * pSender);
	void onMenuItemRiceClicked(cocos2d::CCObject * pSender);
	void onMenuItemDevelopClicked(cocos2d::CCObject * pSender);
	void onMenuItemQuitClicked(cocos2d::CCObject * pSender);
	void onMenuItemHelpClicked(cocos2d::CCObject * pSender);

	void calXiaoShiFinish(CCNode* sender);

	void setForwardLayer(cocos2d::CCLayer * _ccLayer, int _layerType);
	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);
	//void doAnimationCompleted(void);
	void setBackGround(bool _b, int _type, bool _typeB);

	void startSelf(void);

	void onMenuItemPaySuccess(void);
	void onMenuItemPayFailed(void);

	void setLoadingLayer(cocos2d::CCLayer * _layer);

	void doAction(float _f);
private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// 动画管理器

	cocos2d::CCLayer * loadingLayer;
	
	bool isBackGround;

	cocos2d::CCLayerColor * greyLayer;// 灰色层

	bool isTouch1;
	int currTouchIndex;
	bool isTouch2;

	cocos2d::CCLayer * forwardLayer;
	cocos2d::CCArray * pets;
	Pet * cheerPet;

	cocos2d::CCLabelAtlas * meetNum;
	cocos2d::CCLabelAtlas * foodNum;
	cocos2d::CCSprite * selectLight;

	int forwardType;

	cocos2d::CCSprite * aiXin;
	cocos2d::CCSprite * xieXian;
	cocos2d::CCSprite * shuXing;
	cocos2d::CCSprite * currhand;
	cocos2d::CCSprite * currName;
	cocos2d::CCLabelAtlas * currHeart;
	cocos2d::CCLabelAtlas * currHeartFull;
	cocos2d::CCSprite * currAdd;

	cocos2d::CCRect * quence;

	void setRiceNum(int _num);
	void setMeetNum(int _num);
	void setCurrHeart(int _type);
	void updateTeach(void);
	void petMove(float _f, CCObject * p);
	void initCurrSelectPet(void);
	void setCurrSelectPet(int _touchIndex);

	cocos2d::CCPoint m_touchBeginPos; // 开始触摸的位置
	cocos2d::CCPoint m_touchEndPos;// 结束触摸的位置
	bool m_touchMove;// 是否滑动或
	bool isTouchTarget;
	int touchIndex;

	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	bool isCheckHideGateOpen;
	int hideGateIndex;
	int hideGates[15];
	void checkHideGateOpen(int _gateId);
};

#endif

