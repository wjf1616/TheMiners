#ifndef		__CHALLENGECOUNT_H__
#define		__CHALLENGECOUNT_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class Prop;

class ChallengeCount :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	ChallengeCount(void);
	~ChallengeCount(void);

	virtual void OnExit(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ChallengeCount, create);

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
	void onMenuItemMenuClicked(cocos2d::CCObject * pSender);
	void onMenuItemReplayClicked(cocos2d::CCObject * pSender);
	void onMenuItemShopClicked(cocos2d::CCObject * pSender);

	void switchRender(float dt);
	void onMenuItemPaySuccess(void);
	// 计费相关添加
	void onMenuItemPayFailed(void);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager, cocos2d::CCLayer *_ccLayer);


private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// 动画管理器

	Prop * propControl;
	//cocos2d::CCLayer * ccLayer;
	int timeCount;
	bool isCount;
	bool isZhuan;
	bool isBackGround;
	bool isFoodFull;

	//float time;
	cocos2d::CCParticleSystemQuad * liZiTeXiao;
	cocos2d::CCParticleSystemQuad * liZiTeXiaoResult;
	cocos2d::CCParticleSystemQuad * liZiTeXiaoYanHua;
	CCNode* m_pParent1;
	CCNode* m_pParent2;

	cocos2d::CCLabelAtlas * level;
	cocos2d::CCLabelAtlas * coins;
	cocos2d::CCLabelAtlas * ingots;
	cocos2d::CCLabelAtlas * foods;

	int xiaoshiType;// 消失类型

	int selectGoodsIndex;
	cocos2d::CCSprite * kuangSprites;
	cocos2d::CCArray * goodsSprites;
	cocos2d::CCArray * goodsNames;
	cocos2d::CCArray * goodsId;
	cocos2d::CCArray * goodsIntroduces;

	void addInformationAboutGoods(void);
	void removeInformationAboutGoods(void);
};

#endif