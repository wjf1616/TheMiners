#ifndef		__SELECTROLEANDPROPMENU_H__
#define		__SELECTROLEANDPROPMENU_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Prop.h"


class SelectRoleAndPropMenu :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	SelectRoleAndPropMenu(void);
	~SelectRoleAndPropMenu(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SelectRoleAndPropMenu, create);

	virtual void onEnter(void);
	void onEnterTransitionDidFinish(void);
	virtual void onExit(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	virtual void keyBackClicked(void);

	void doAction(float _f);

	void onMenuItemShopClicked(cocos2d::CCObject * pSender);
	void onMenuItemBackClicked(cocos2d::CCObject * pSender);
	void onMenuItemPlayClicked(cocos2d::CCObject * pSender);
	void onMenuItemPlusClicked(cocos2d::CCObject * pSender);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void doAnimationCompleted(void);

	void reBack(int _type, bool _b);

	void startSelf(void);
	void setLoadingLayer(cocos2d::CCLayer * _layer);
private:
	cocos2d::CCLayer * loadingLayer;

	bool isBackGround;
	cocos2d::CCLayerColor * greyLayer;// 灰色层

	cocos2d::extension::CCBAnimationManager *mAnimationManager;// 动画管理器
	
	int currButtonIndex;// 检测按钮的index
	bool isFristRolePage;
	bool isFristPropPage;
	bool isRolePage;// 是否是在选人的界面上
	bool isCheckButtonIsSelected;// 是否去要判断button被选择了
	int currRoleIndex;
	int currPropIndex;
	Prop * propControl;

	cocos2d::CCSprite * coupletSelect;// 已上阵
	cocos2d::CCSprite * coupletAbout;// 未解锁
	cocos2d::CCLabelAtlas * ingotNum;// 元宝值显示
	cocos2d::CCSprite * rolePageButton;// 人物选择按钮
	cocos2d::CCSprite * propPageButton;// 道具选择按钮

	cocos2d::CCArray * selectRoleSpritesName;// 任务名字
	cocos2d::CCArray * selectRoleSprites;// 人物形象
	cocos2d::CCArray * selectRoleSpritesIsHaving;// 是否拥有对象
	cocos2d::CCArray * selectRoleSpritesIsOpen;// 对象是否开启 illusioncui
	cocos2d::CCArray * selectRoleSpritesSpeed;// 对象是否开启 illusioncui
	cocos2d::CCArray * selectRoleSpritesPower;// 对象是否开启 illusioncui
	cocos2d::CCArray * selectRoleSpritesIntroduce;// 对象是否开启 illusioncui

	cocos2d::CCArray * pointRoleSprites;

	cocos2d::CCArray * selectPropSprites;// 道具形象
	cocos2d::CCArray * selectPropIntroduce;// 道具形象
	cocos2d::CCArray * selectPropPrice;//
	cocos2d::CCArray * selectPropName;//
	cocos2d::CCArray * selectPropId;

	cocos2d::CCArray * pointPropSprites;

	cocos2d::CCSprite * pointIndexSprite;// 亮的小点
	cocos2d::CCArray * currSelectSprites;// 当前node的精灵
	cocos2d::CCArray * currSelectSpritesIntroduce;// 对象是否开启 illusioncui
	cocos2d::CCArray * currSelectRoleSpritesIsHaving;// 是否拥有对象
	cocos2d::CCArray * currSelectRoleSpritesIsOpen;// 对象是否开启 illusioncui
	cocos2d::CCArray * currSelectPropPrice;// 
	cocos2d::CCArray * currSelectPropName;// 

	cocos2d::CCArray * currSelectYunSprites;// 当前的yun的精灵
	cocos2d::CCArray * currSelectRoleSpeedBackground;// 
	cocos2d::CCArray * currSelectRolePowerBackground;// 
	cocos2d::CCArray * currSelectRoleSpeed;// 
	cocos2d::CCArray * currSelectRolePower;// 
	cocos2d::CCArray * currSelectPropFrameSprites;// 当前道具框架的精灵 illusioncui
	cocos2d::CCArray * currSelectButtonSelectSprites;// 当前的上阵按钮的精灵 illusioncui
	cocos2d::CCArray * currSelectGetSelectSprites;// 当前的解锁按钮的精灵
	cocos2d::CCArray * currSelectAboutSelectSprites;// 当前的招募按钮的精灵
	cocos2d::CCArray * currSelectFrameSprites;// 当前的yun的精灵
	cocos2d::CCArray * currSelectButtonBuySprites;// 当前的购买道具按钮的精灵

	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	cocos2d::CCPoint m_touchBeginPos; // 开始触摸的位置
	cocos2d::CCPoint m_touchEndPos;// 结束触摸的位置
	bool m_touchMove;// 是否滑动或

	void changeCurrPage(void);// 选人和道具页面切换
	void setCurrRole(bool _isXiangZuo);
	void setCurrProp(bool _isXiangZuo);
	void setPageButton(bool _isRolePage);
	void setNodeBySelectIndex(bool _isXiangZuo);
	void checkButtonEvent(void);
	void initSprites(void);
	void setBackGround(bool _b);

	void menuSelect1Callback(cocos2d::CCObject* pSender);
	void menuSelect2Callback(cocos2d::CCObject* pSender);
	void menuSelect3Callback(cocos2d::CCObject* pSender);
	void menuSelect4Callback(cocos2d::CCObject* pSender);
	void menuGet1Callback(cocos2d::CCObject* pSender);
	void menuGet2Callback(cocos2d::CCObject* pSender);
	void menuGet3Callback(cocos2d::CCObject* pSender);
	void menuGet4Callback(cocos2d::CCObject* pSender);
	void menuBuy1Callback(cocos2d::CCObject* pSender);
	void menuBuy2Callback(cocos2d::CCObject* pSender);
	void menuBuy3Callback(cocos2d::CCObject* pSender);
	void menuBuy4Callback(cocos2d::CCObject* pSender);
	void menuAbout1Callback(CCObject* pSender);
	void menuAbout2Callback(CCObject* pSender);
	void menuAbout3Callback(CCObject* pSender);
	void menuAbout4Callback(CCObject* pSender);
};

#endif
