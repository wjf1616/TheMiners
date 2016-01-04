#ifndef		__SHOP_H__
#define		__SHOP_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class Prop;
class ShopCeilSpecail;
class ShopCeilBase;

class Shop :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	Shop(void);
	~Shop(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Shop, create);

	virtual void onEnter(void);
	void onEnterTransitionDidFinish(void);
	virtual void onExit(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	virtual void keyBackClicked(void);
	
	void reBackBackClicked(bool _b);
	void onMenuItemBackClicked(cocos2d::CCObject * pSender);
	void onMenuItemPlayClicked(cocos2d::CCObject * pSender);
	void onMenuItemPlusClicked(cocos2d::CCObject * pSender);
	void onMenuItemPersonClicked(cocos2d::CCObject * pSender);
	void onMenuItemOffClicked(cocos2d::CCObject * pSender);
	void onMenuItemBuyClicked(cocos2d::CCObject * pSender);

	void onMenuItemButtonClicked(void);
	void onMenuItemPayButtonClicked(void);
	void onMenuItemPaySuccess(void);
	void onMenuItemPayFailed(void);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void doAnimationCompleted(void);

	void setPropInformation(int _id, ShopCeilBase * _ceil, bool _isPay);

	void reBack(int _type, bool _b);

	void startSelf(void);
	void setLoadingLayer(cocos2d::CCLayer * _layer);
	void setForwardLayer(cocos2d::CCLayer * _ccLayer, int _layerType);

	void doAction(float _f);

	Prop * propControl;
	void setBackGround2(bool _b);
	void clearPropInformation(void);
	void spotLighLayerCallBack(void);

	cocos2d::CCMenu * getPageMenu(void);
private:
	bool isDoAction;
	bool myItemIsCanTouched;

	float startTimeCount;

	bool isSpot;
	CCLayer * spotLighLayer;

	cocos2d::CCLayer * forwardLayer;
	int forwardType;
	cocos2d::CCLayer * loadingLayer;

	bool isBuy;

	int selectId;
	ShopCeilBase * selectCeil;

	bool isBackGround;
	bool isBackGround2;
	cocos2d::CCLayerColor * greyLayer;// 灰色层

	cocos2d::CCSprite * propName;
	cocos2d::CCSprite * propIntroduce;
	cocos2d::CCLabelAtlas * propPrice;
	cocos2d::CCLabelAtlas * propIngotNum;
	cocos2d::CCLabelAtlas * propBuyNum;

	cocos2d::CCArray * pages1;

	cocos2d::CCArray * pages2;

	cocos2d::CCMenu * pageMenu;
	//bool isCheck;

	cocos2d::extension::CCBAnimationManager *mAnimationManager;// 动画管理器

	cocos2d::CCLabelAtlas * ingotNum;// 元宝值显示

	void setIsDoaction(bool _b);
	void setBackGround(bool _b);
	void setIngotNum(void);
};

#define					SHOP_CEIL_WITHOUT_INGOT				1
#define					SHOP_CEIL_WITH_INGOT				2
class ShopCeilBase
{
public:
	ShopCeilBase(){};
	~ShopCeilBase(){};

	virtual void setIsRecommend(bool _b){};
	virtual void setIsDisCount(bool _b){};

	virtual cocos2d::CCLabelAtlas * getNum(void){return NULL;};
	virtual void updateNum(void){};

	virtual int getId(void){return 0;};

	virtual bool getIsPay(void){return false;};
};


class ShopCeil :
	public cocos2d::CCLayer
	, ShopCeilBase
{
public:
	ShopCeil(int _type, int _id, Shop * _shop, bool _isPay);
	~ShopCeil(void);

	virtual void setIsRecommend(bool _b);
	virtual void setIsDisCount(bool _b);

	virtual cocos2d::CCLabelAtlas * getNum(void);
	virtual void updateNum(void);

	virtual void setTouchEnabled(bool _b);

	virtual int getId(void);

	virtual bool getIsPay(void);

	void menuButtonCallback(CCObject* pSender);

	cocos2d::CCMenuItem * getMenuItem(void);
private:
	bool isButtonTouchEnabled;
	bool isPay;

	cocos2d::CCNode * nodeImage;
	cocos2d::CCSprite * recommend;
	cocos2d::CCSprite * disCount;
	//cocos2d::CCSprite * frame;
	cocos2d::CCSprite * image;
	cocos2d::CCMenuItem* pMenuItem;

	Shop * shop;
	cocos2d::CCLabelAtlas * ingotNum;

	int id;
	int type;

	void setImageAndPriceById(int _id);
};

class ShopCeilSpecail :
	public cocos2d::CCLayer
	, ShopCeilBase
{
public:
	ShopCeilSpecail(int _type, int _id, Shop * _shop, bool _isPay);
	~ShopCeilSpecail(void);

	virtual void setIsRecommend(bool _b);
	virtual void setIsDisCount(bool _b);

	virtual cocos2d::CCLabelAtlas * getNum(void);
	virtual void updateNum(void);

	virtual void setTouchEnabled(bool _b);

	virtual int getId(void);

	virtual bool getIsPay(void);

	void menuButtonCallback(CCObject* pSender);

private:
	bool isButtonTouchEnabled;
	bool isPay;

	cocos2d::CCNode * nodeImage;
	cocos2d::CCSprite * recommend;
	cocos2d::CCSprite * disCount;
	//cocos2d::CCSprite * frame;
	cocos2d::CCSprite * image;
	cocos2d::CCMenu* pMenu;

	Shop * shop;
	cocos2d::CCLabelAtlas * ingotNum;

	int id;
	int type;

	void setImageAndPriceById(int _id);
};

#endif
