#ifndef		__GAMEOVERMENU_H__
#define		__GAMEOVERMENU_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class Prop;


class GameOverMenu :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	GameOverMenu(void);
	~GameOverMenu(void);

	virtual void onExit(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameOverMenu, create);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void setBackGround(bool _b);

	void reBackWithVisiable(void);

	void doAnimationCompleted(void);

	void doAction(float _f);

	void onMenuItemSelect1Clicked(cocos2d::CCObject * pSender);// 商城1
	void onMenuItemSelect2Clicked(cocos2d::CCObject * pSender);// 商品2
	void onMenuItemSelect3Clicked(cocos2d::CCObject * pSender);// 商品3
	void onMenuItemSelect4Clicked(cocos2d::CCObject * pSender);// 商品4
	void onMenuItemBuyClicked(cocos2d::CCObject * pSender);
	void onMenuItemNextClicked(cocos2d::CCObject * pSender);
	void onMenuItemMenuClicked(cocos2d::CCObject * pSender);
	void onMenuItemReplayClicked(cocos2d::CCObject * pSender);
	void onMenuItemShopClicked(cocos2d::CCObject * pSender);

	void calStar1(CCNode* sender);
	void calStar2(CCNode* sender);
	void calStar3(CCNode* sender);
	void switchRender(float dt);
	void onMenuItemPaySuccess(void);
	// 计费相关添加
	void onMenuItemPayFailed(void);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager, cocos2d::CCLayer *_ccLayer, bool _isWin);


private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// 动画管理器

	Prop * propControl;

	cocos2d::CCLayer * ccLayer;
	float f_timeCount;
	int timeCount;
	bool isCount;
	bool isZhuan;
	//int upDateCount;
	//int upDateStand;
	//bool isInitLiZiTeXiao;
	bool isBackGround;
	int isWin;

	//float time;
	cocos2d::CCParticleSystemQuad * liZiTeXiao;
	cocos2d::CCParticleSystemQuad * liZiTeXiaoResult;
	//cocos2d::CCArray * liZiTeXiaos;
	cocos2d::CCParticleSystemQuad * liZiTeXiaoYanHua;
	CCNode* m_pParent1;
	CCNode* m_pParent2;

	cocos2d::CCLabelAtlas * coins;
	cocos2d::CCArray * coinsZhuan;
	cocos2d::CCLabelAtlas * ingots;
	cocos2d::CCArray * ingotsZhuan;
	cocos2d::CCLabelAtlas * maxContinuesCount;
	cocos2d::CCArray * maxContinuesCountZhuan;
	cocos2d::CCLabelAtlas * getJewelCount;
	cocos2d::CCArray * getJewelCountZhuan;
	cocos2d::CCSprite * jiahao;

	int xiaoshiType;// 消失类型

	int selectGoodsIndex;
	cocos2d::CCSprite * kuangSprites;
	cocos2d::CCArray * goodsSprites;
	cocos2d::CCArray * goodsNames;
	cocos2d::CCArray * goodsId;
	cocos2d::CCArray * goodsIntroduces;

	cocos2d::CCArray * makeZhuan(double _x, double _y, int _type, cocos2d::CCNode * _node);

	void addInformationAboutGoods(void);
	void removeInformationAboutGoods(void);
};

#endif