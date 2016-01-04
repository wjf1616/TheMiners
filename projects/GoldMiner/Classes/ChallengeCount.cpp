#include "ChallengeCount.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "GameControl.h"
#include "LoadingLayer.h"
#include "Prop.h"
#include "PromptLayer.h"
#include "TemporaryPromptLayer.h"
#include "CostLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define					GAME_OVER_WIN_SHINE_TAG							10086

#define					GAME_OVER_WIN_NUM_TIME							60

#define					GAME_OVER_GOODS_NUM								4
#define					GAME_OVER_WIN_SYSTEM_POSITION_NUM				8

static const ccColor3B myGrey={60,60,60};

enum
{
	ChallengeCount_XIAOSHI_TYPE_SHOP = 0,
	ChallengeCount_XIAOSHI_TYPE_MENU,
	ChallengeCount_XIAOSHI_TYPE_REPLAY,
	ChallengeCount_XIAOSHI_TYPE_NEXT
};

ChallengeCount::ChallengeCount(void)
	: mAnimationManager(NULL)
	//, ccLayer(NULL)
	//,liZiTeXiaos(NULL)
	,liZiTeXiaoResult(NULL)
	,isBackGround(false)
{
}

void ChallengeCount::OnExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);
	CCLayer::onExit();
}

ChallengeCount::~ChallengeCount(void)
{
	CCObject * p;
	CCARRAY_FOREACH(goodsSprites, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CCARRAY_FOREACH(goodsNames, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CCARRAY_FOREACH(goodsId, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CCARRAY_FOREACH(goodsIntroduces, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CC_SAFE_RELEASE(liZiTeXiaoResult);

	CC_SAFE_RELEASE_NULL(mAnimationManager);


	cs::ArmatureDataManager::sharedArmatureDataManager()->removeAll();
	cs::ArmatureDataManager::sharedArmatureDataManager()->purgeArmatureSystem();
	CCTextureCache::sharedTextureCache()->removeAllTextures();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
	CCLOG("ChallengeCount::~ChallengeCount");
}

SEL_MenuHandler ChallengeCount::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnShop", ChallengeCount::onMenuItemShopClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBuy", ChallengeCount::onMenuItemBuyClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnMenu", ChallengeCount::onMenuItemMenuClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnReplay", ChallengeCount::onMenuItemReplayClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnSelect1", ChallengeCount::onMenuItemSelect1Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnSelect2", ChallengeCount::onMenuItemSelect2Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnSelect3", ChallengeCount::onMenuItemSelect3Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnSelect4", ChallengeCount::onMenuItemSelect4Clicked);

	return NULL;
}

cocos2d::SEL_CallFuncN ChallengeCount::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler ChallengeCount::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool ChallengeCount::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void ChallengeCount::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager, cocos2d::CCLayer *_ccLayer)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;

	goodsSprites = new cocos2d::CCArray();
	goodsNames = new cocos2d::CCArray();
	goodsId = new CCArray();
	goodsIntroduces = new cocos2d::CCArray();

	// 商品初始化以及显示
	goodsSprites->addObject(CCSprite::create("shangcheng/jifei1.png"));
	((CCSprite *)goodsSprites->lastObject())->setScale(0.8);
	getChildByTag(3)->getChildByTag(9)->addChild((CCSprite *)goodsSprites->lastObject());
	goodsNames->addObject(CCSprite::create("slsb/jiaose.png"));
	goodsId->addObject(CCInteger::create(PAY_ID_SUNWUKONG));
	if(Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_SUNWUKONG))
	{
		((CCSprite *)goodsSprites->lastObject())->setColor(myGrey);
	}
	goodsIntroduces->addObject(CCSprite::create("slsb/kaiqi1.png"));
	((CCSprite *)goodsIntroduces->lastObject())->setPositionX(20);

	goodsSprites->addObject(CCSprite::create("shangcheng/jifei2.png"));
	((CCSprite *)goodsSprites->lastObject())->setScale(0.8);
	getChildByTag(3)->getChildByTag(10)->addChild((CCSprite *)goodsSprites->lastObject());
	goodsNames->addObject(CCSprite::create("slsb/foguang.png"));
	goodsId->addObject(CCInteger::create(PAY_ID_BUDDAHA));
	goodsIntroduces->addObject(CCSprite::create("slsb/kaiqi2.png"));
	((CCSprite *)goodsIntroduces->lastObject())->setPositionX(20);

	goodsSprites->addObject(CCSprite::create("shangcheng/jifei3.png"));
	((CCSprite *)goodsSprites->lastObject())->setScale(0.8);
	getChildByTag(3)->getChildByTag(11)->addChild((CCSprite *)goodsSprites->lastObject());
	goodsNames->addObject(CCSprite::create("slsb/huangjin.png"));
	goodsId->addObject(CCInteger::create(PAY_ID_MEET));
	goodsIntroduces->addObject(CCSprite::create("slsb/kaiqi4.png"));
	((CCSprite *)goodsIntroduces->lastObject())->setPositionX(20);

	goodsSprites->addObject(CCSprite::create("shangcheng/jifei5.png"));
	((CCSprite *)goodsSprites->lastObject())->setScale(0.8);
	getChildByTag(3)->getChildByTag(12)->addChild((CCSprite *)goodsSprites->lastObject());
	goodsNames->addObject(CCSprite::create("slsb/jiaose.png"));
	goodsId->addObject(CCInteger::create(PAY_ID_HULUWA));
	if(Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_HULUWA))
	{
		((CCSprite *)goodsSprites->lastObject())->setColor(myGrey);
	}
	goodsIntroduces->addObject(CCSprite::create("slsb/kaiqi3.png"));
	((CCSprite *)goodsIntroduces->lastObject())->setPositionX(20);
	//goodsSprites->addObject(CCSprite::create("xuanren/sl.png"));
	//getChildByTag(3)->getChildByTag(9)->addChild((CCSprite *)goodsSprites->lastObject());
	//goodsNames->addObject(CCSprite::create("xuanren/sl1.png"));
	//goodsId->addObject(CCInteger::create(PROP_TYPE_MOONLIGHT));
	//goodsIntroduces->addObject(CCSprite::create("xuanren/sl2.png"));

	//goodsSprites->addObject(CCSprite::create("xuanren/zd.png"));
	//getChildByTag(3)->getChildByTag(10)->addChild((CCSprite *)goodsSprites->lastObject());
	//goodsNames->addObject(CCSprite::create("xuanren/zhadan.png"));
	//goodsId->addObject(CCInteger::create(PROP_TYPE_GRENADE));
	//goodsIntroduces->addObject(CCSprite::create("xuanren/zd1.png"));

	//goodsSprites->addObject(CCSprite::create("xuanren/llys.png"));
	//getChildByTag(3)->getChildByTag(11)->addChild((CCSprite *)goodsSprites->lastObject());
	//goodsNames->addObject(CCSprite::create("xuanren/llys1.png"));
	//goodsId->addObject(CCInteger::create(PROP_TYPE_VIGOROUSLY_PILL));
	//goodsIntroduces->addObject(CCSprite::create("xuanren/dlys2.png"));

	//goodsSprites->addObject(CCSprite::create("xuanren/miaozhunjing.png"));
	//getChildByTag(3)->getChildByTag(12)->addChild((CCSprite *)goodsSprites->lastObject());
	//goodsNames->addObject(CCSprite::create("xuanren/miaozhunjing2.png"));
	//goodsId->addObject(CCInteger::create(PROP_TYPE_ALIGNMENT));
	//goodsIntroduces->addObject(CCSprite::create("xuanren/miaozhunjing1.png"));

	selectGoodsIndex = 0;
	kuangSprites = CCSprite::create("slsb/anniu2.png");
	getChildByTag(3)->getChildByTag(selectGoodsIndex+1+GAME_OVER_GOODS_NUM*2)->addChild(kuangSprites, -1);

	addInformationAboutGoods();

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_WIN);

	mAnimationManager->runAnimationsForSequenceNamed("win");

	//ccLayer = _ccLayer;
	isCount = true;
	isZhuan = true;

	char _s[32];
	// 层数显示
	sprintf(_s, "%d",Global::getInstance()->getChallengeLevel()-1);
	level = CCLabelAtlas::create(_s, "yindao/shuzi.png", 21, 30, '0');
	getChildByTag(3)->getChildByTag(1)->addChild(level,1);
	if (Global::getInstance()->getChallengeLevel() > 10)
	{
		level->setPosition(ccp(-20, -10));
	}
	else
	{
		level->setPosition(ccp(-10, -10));
	}
	// 获得元宝数
	int tmp = ((ChallengeLayer *) _ccLayer)->getChallengeAwardByPropId(PROP_TYPE_INGOT);
	Player::getInstance()->appendPropNum(PROP_TYPE_INGOT, tmp);
	Player::getInstance()->savePropNum(PROP_TYPE_INGOT, tmp);
	int _num = 1;
	while (tmp > 0)
	{
		tmp = tmp /10;
		if (tmp > 0)
		{
			_num++;
		}
	}
	sprintf(_s, "%d",((ChallengeLayer *) _ccLayer)->getChallengeAwardByPropId(PROP_TYPE_INGOT));
	ingots = CCLabelAtlas::create(_s, "slsb/yuanbaoshuzi.png", 24, 37, '0');
	getChildByTag(3)->getChildByTag(2)->addChild(ingots, 1);
	ingots->setPosition(ccp(80 -_num*24, -115));
	// 获得口粮数
	tmp = ((ChallengeLayer *) _ccLayer)->getChallengeAwardByPropId(PROP_TYPE_FOOD);
	isFoodFull = false;
	Player::getInstance()->appendPropNum(PROP_TYPE_FOOD, tmp);
	if (Player::getInstance()->getPropNum(PROP_TYPE_FOOD) > 98 && tmp>0)
	{
		isFoodFull = true;
	}


	_num = 1;
	while (tmp > 0)
	{
		tmp = tmp /10;
		if (tmp > 0)
		{
			_num++;
		}
	}
	sprintf(_s, "%d",((ChallengeLayer *) _ccLayer)->getChallengeAwardByPropId(PROP_TYPE_FOOD));
	foods = CCLabelAtlas::create(_s, "slsb/defenshuzi.png", 24, 37, '0');
	getChildByTag(3)->getChildByTag(2)->addChild(foods, 1);
	foods->setPosition(ccp(80 -_num*24 , -58));
	// 获得金币数
	tmp =Global::getInstance()->getChallengeCountSum();
	_num = 1;
	while (tmp > 0)
	{
		tmp = tmp /10;
		if (tmp > 0)
		{
			_num++;
		}
	}
	sprintf(_s, "%d",Global::getInstance()->getChallengeCountSum());
	coins = CCLabelAtlas::create(_s, "slsb/shuzi.png", 18, 26, '0');
	getChildByTag(3)->getChildByTag(2)->addChild(coins, 1);
	coins->setPosition(ccp(80 - _num*18 , -8));

	schedule( schedule_selector(ChallengeCount::doAction), 0);

	timeCount = 0;

	//// 转光
	//CCSprite* sp1 = CCSprite::create("shengli/guang.png");
	//CCRotateBy* rot = CCRotateBy::create(2, 360);
	//CCAction* forever = CCRepeatForever::create(rot);
	//sp1->runAction(forever);           
	//sp1->setPosition(ccp(400,375));   
	//addChild(sp1, -1, GAME_OVER_WIN_SHINE_TAG);

	liZiTeXiaoYanHua = CCParticleSystemQuad::create("lizitexiao/yanhua/yanhua.plist");
	liZiTeXiaoYanHua->retain();
	addChild(liZiTeXiaoYanHua,LAYER_ORDER_CONTROL);
	
	CC_SAFE_RETAIN(mAnimationManager);
}

void ChallengeCount::switchRender(float dt)
{
	bool usingBatch = ( liZiTeXiaoYanHua->getBatchNode() != NULL );
	liZiTeXiaoYanHua->removeFromParentAndCleanup(false);

	CCNode *newParent = (usingBatch ? m_pParent2  : m_pParent1 );
	newParent->addChild(liZiTeXiaoYanHua);

	int i = rand()%5;

	switch(i)
	{
	case 0:
		newParent->setPosition(ccp(100,120));
		break;
	case 1:
		newParent->setPosition(ccp(700,400));
		break;
	case 2:
		newParent->setPosition(ccp(700,120));
		break;
	case 3:
		newParent->setPosition(ccp(100,400));
		break;
	case 4:
		newParent->setPosition(ccp(400,240));
		break;
	}

}

// 商城1
void ChallengeCount::onMenuItemSelect1Clicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}	

	if (selectGoodsIndex == 0)
	{
		return;
	}	

	// 对应介绍更新
	getChildByTag(3)->getChildByTag(selectGoodsIndex+1+GAME_OVER_GOODS_NUM*2)->removeChild(kuangSprites,true);
	//((CCMenuItemImage *)getChildByTag(3)->getChildByTag(selectGoodsIndex + 1 + GAME_OVER_GOODS_NUM))->setNormalImage(CCSprite::create("slsb/anniu1.png"));
	removeInformationAboutGoods();
	
	//((CCMenuItemImage *)getChildByTag(3)->getChildByTag(5))->setNormalImage(CCSprite::create("slsb/anniu2.png"));
	selectGoodsIndex = 0;
	kuangSprites = CCSprite::create("slsb/anniu2.png");
	getChildByTag(3)->getChildByTag(selectGoodsIndex+1+GAME_OVER_GOODS_NUM*2)->addChild(kuangSprites, -1);
	addInformationAboutGoods();
}

// 商品2
void ChallengeCount::onMenuItemSelect2Clicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	if (selectGoodsIndex == 1)
	{
		return;
	}	

	// 对应介绍更新
	getChildByTag(3)->getChildByTag(selectGoodsIndex+1+GAME_OVER_GOODS_NUM*2)->removeChild(kuangSprites,true);
	//((CCMenuItemImage *)getChildByTag(3)->getChildByTag(selectGoodsIndex + 1 + GAME_OVER_GOODS_NUM))->setNormalImage(CCSprite::create("slsb/anniu1.png"));
	removeInformationAboutGoods();

	//((CCMenuItemImage *)getChildByTag(3)->getChildByTag(6))->setNormalImage(CCSprite::create("slsb/anniu2.png"));
	selectGoodsIndex = 1;
	kuangSprites = CCSprite::create("slsb/anniu2.png");
	getChildByTag(3)->getChildByTag(selectGoodsIndex+1+GAME_OVER_GOODS_NUM*2)->addChild(kuangSprites, -1);
	addInformationAboutGoods();
}

// 商品3
void ChallengeCount::onMenuItemSelect3Clicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	if (selectGoodsIndex == 2)
	{
		return;
	}	

	// 对应介绍更新
	getChildByTag(3)->getChildByTag(selectGoodsIndex+1+GAME_OVER_GOODS_NUM*2)->removeChild(kuangSprites,true);
	//((CCMenuItemImage *)getChildByTag(3)->getChildByTag(selectGoodsIndex + 1 + GAME_OVER_GOODS_NUM))->setNormalImage(CCSprite::create("slsb/anniu1.png"));
	removeInformationAboutGoods();

	//((CCMenuItemImage *)getChildByTag(3)->getChildByTag(7))->setNormalImage(CCSprite::create("slsb/anniu2.png"));
	selectGoodsIndex = 2;
	kuangSprites = CCSprite::create("slsb/anniu2.png");
	getChildByTag(3)->getChildByTag(selectGoodsIndex+1+GAME_OVER_GOODS_NUM*2)->addChild(kuangSprites, -1);
	addInformationAboutGoods();
}

// 商品4
void ChallengeCount::onMenuItemSelect4Clicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	if (selectGoodsIndex == 3)
	{
		return;
	}

	// 对应介绍更新
	getChildByTag(3)->getChildByTag(selectGoodsIndex+1+GAME_OVER_GOODS_NUM*2)->removeChild(kuangSprites,true);
	//((CCMenuItemImage *)getChildByTag(3)->getChildByTag(selectGoodsIndex + 1 + GAME_OVER_GOODS_NUM))->setNormalImage(CCSprite::create("slsb/anniu1.png"));
	removeInformationAboutGoods();

	//((CCMenuItemImage *)getChildByTag(3)->getChildByTag(8))->setNormalImage(CCSprite::create("slsb/anniu2.png"));
	selectGoodsIndex = 3;
	kuangSprites = CCSprite::create("slsb/anniu2.png");
	getChildByTag(3)->getChildByTag(selectGoodsIndex+1+GAME_OVER_GOODS_NUM*2)->addChild(kuangSprites, -1);
	addInformationAboutGoods();
}

// 商城
void ChallengeCount::onMenuItemShopClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	setVisible(false);
	setBackGround(true);
	Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getShopLayer(NULL, this, LAYER_ID_CHALLENGE_COUNT));
}


// 购买（计费点相关）
void ChallengeCount::onMenuItemBuyClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

/*	if (((CCSprite *)goodsSprites->objectAtIndex(selectGoodsIndex))->getColor().b == myGrey.b
		&& ((CCSprite *)goodsSprites->objectAtIndex(selectGoodsIndex))->getColor().g == myGrey.g
		&& ((CCSprite *)goodsSprites->objectAtIndex(selectGoodsIndex))->getColor().r == myGrey.r)
	{
		return;
	}*/	

	bool _flag = true;
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	setBackGround(true);
#ifdef						GOLDEN_MINER_2_VERSION_PAY
#ifdef						GOLDEN_MINER2_VERSION_PAY_SELF
	_flag = false;
	// 计费相关添加
	int _id = ((CCInteger *)goodsId->objectAtIndex(selectGoodsIndex))->getValue();

	if (_id == PAY_ID_BUDDAHA && (Player::getInstance()->getPropNum(PROP_TYPE_BUDDAHA) > 0))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_CHALLENGE_COUNT);
		//promptLayer->setForwardLayer(this);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->miaoZhunXianInformation();
	}
	else if (_id == PAY_ID_MEET && (Player::getInstance()->getPropNum(PROP_TYPE_MEET) > 99998))
	{
		// 道具到达上限
		TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_CHALLENGE_COUNT);
		_layer->doPromptByType(TEMP_PROMPT_FOOD_FULL);
		_layer->setPromptType2(1);
		Global::getInstance()->s->addLayerToRunningScene(_layer);
	}
	else if (_id == PAY_ID_SUNWUKONG && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_SUNWUKONG)))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_CHALLENGE_COUNT);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->payRoleIsHaving();
	}
	else if (_id == PAY_ID_HULUWA && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_HULUWA)))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_CHALLENGE_COUNT);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->payRoleIsHaving();
	}
	else
	{
		CostLayer * _layer = (CostLayer *)Global::getInstance()->s->getCostLayer(this, LAYER_ID_CHALLENGE_COUNT);
		_layer->costById(_id, CCCallFunc::create(this,callfunc_selector(ChallengeCount::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(ChallengeCount::onMenuItemPayFailed)));
		Global::getInstance()->s->addLayerToRunningScene(_layer);
	}
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
	_flag = false;
	// 计费相关添加
	int _id = ((CCInteger *)goodsId->objectAtIndex(selectGoodsIndex))->getValue();

	if (_id == PAY_ID_BUDDAHA && (Player::getInstance()->getPropNum(PROP_TYPE_BUDDAHA) > 0))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_CHALLENGE_COUNT);
		//promptLayer->setForwardLayer(this);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->miaoZhunXianInformation();
	}
	else if (_id == PAY_ID_MEET && (Player::getInstance()->getPropNum(PROP_TYPE_MEET) > 99998))
	{
		// 道具到达上限
		TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_CHALLENGE_COUNT);
		_layer->doPromptByType(TEMP_PROMPT_FOOD_FULL);
		_layer->setPromptType2(1);
		Global::getInstance()->s->addLayerToRunningScene(_layer);
	}
	else if (_id == PAY_ID_SUNWUKONG && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_SUNWUKONG)))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_CHALLENGE_COUNT);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->payRoleIsHaving();
	}
	else if (_id == PAY_ID_HULUWA && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_HULUWA)))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_CHALLENGE_COUNT);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->payRoleIsHaving();
	}
	else
	{
		if (_id == PAY_ID_BUDDAHA && _id == PAY_ID_MEET)
		{
			PayService::getInstance()->pay(_id, true,  CCCallFunc::create(this,callfunc_selector(GameOverMenu::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(GameOverMenu::onMenuItemPayFailed)));
		}
		else
		{
			PayService::getInstance()->pay(_id, true,  CCCallFunc::create(this,callfunc_selector(GameOverMenu::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(GameOverMenu::onMenuItemPayFailed)));
			//PayService::getInstance()->pay(selectId, false, CCCallFunc::create(this, callfunc_selector(Shop::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(Shop::onMenuItemPayFailed)));
		}
	}

#endif
#endif
#endif
	if (_flag)
	{
		int _id = ((CCInteger *)goodsId->objectAtIndex(selectGoodsIndex))->getValue();
		if (_id == PAY_ID_BUDDAHA && (Player::getInstance()->getPropNum(PROP_TYPE_BUDDAHA) == 1))
		{
			// 提示已经购买了瞄准线了 (瞄准线最多1个)
			PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_CHALLENGE_COUNT);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->miaoBuddahaInformation();
		}
		else if (_id == PAY_ID_MEET && (Player::getInstance()->getPropNum(PROP_TYPE_MEET) > 99998))
		{
			// 道具到达上限
			TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_CHALLENGE_COUNT);
			_layer->doPromptByType(TEMP_PROMPT_FOOD_FULL);
			_layer->setPromptType2(1);
			Global::getInstance()->s->addLayerToRunningScene(_layer);
		}
		else if (_id == PAY_ID_SUNWUKONG && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_SUNWUKONG)))
		{
			// 提示已经购买了瞄准线了 (瞄准线最多1个)
			PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_CHALLENGE_COUNT);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->payRoleIsHaving();
		}
		else if (_id == PAY_ID_HULUWA && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_HULUWA)))
		{
			// 提示已经购买了瞄准线了 (瞄准线最多1个)
			PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_CHALLENGE_COUNT);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->payRoleIsHaving();
		}
		else
		{
			onMenuItemPaySuccess();
		}
	}
	//if (_id == PROP_TYPE_ALIGNMENT && (Player::getInstance()->getPropNum(PROP_TYPE_ALIGNMENT) > 0))
	//{
	//	// 提示已经购买了瞄准线了 (瞄准线最多1个)
	//	PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_CHALLENGE_COUNT);
	//	setBackGround(true);
	//	//promptLayer->setForwardLayer(this);
	//	Global::getInstance()->s->addLayerToRunningScene(promptLayer);
	//	promptLayer->miaoZhunXianInformation();
	//}
	//else
	//{
	//	if (Player::getInstance()->getPropNum(PROP_TYPE_INGOT) >= propControl->getPrice(_id))
	//	{
	//		Player::getInstance()->appendPropNum(PROP_TYPE_INGOT ,-propControl->getPrice(_id));
	//		Player::getInstance()->savePropNum(PROP_TYPE_INGOT ,-propControl->getPrice(_id));
	//		Player::getInstance()->appendPropNum(_id ,1);
	//		Player::getInstance()->savePropNum(_id ,1);

	//		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FINISH);
	//	}
	//	else
	//	{
	//		// 钱不够购买
	//		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FAILED);
	//	}
	//}

}
// 计费相关添加
void ChallengeCount::onMenuItemPaySuccess(void)
{
	int selectId = ((CCInteger *)goodsId->objectAtIndex(selectGoodsIndex))->getValue();

	Global::getInstance()->getPayAwardByPayId(selectId);
	if (selectId == PAY_ID_SUNWUKONG || selectId == PAY_ID_SUNWUKONG)
	{
		((CCSprite *)goodsSprites->objectAtIndex(selectGoodsIndex))->setColor(myGrey);
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FINISH);

	TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_CHALLENGE_COUNT);
	_layer->doPromptByType(TEMP_PROMPT_BUY_SUCCESS);
	_layer->setPromptType2(1);
	Global::getInstance()->s->addLayerToRunningScene(_layer);
}


// 计费相关添加
void ChallengeCount::onMenuItemPayFailed(void)
{	
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FAILED);

	setBackGround(false);
}

// 菜单
void ChallengeCount::onMenuItemMenuClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
	CCLayer * p1 = Global::getInstance()->s->getMainLayer(p);

	p->addLoadingLayer(0,p1);
	p->setNextLayer(LAYER_ID_MAIN, p1);

	Global::getInstance()->s->replaceScene(p);
}

// 重玩
void ChallengeCount::onMenuItemReplayClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	// 开启挑战模式
	Global::getInstance()->setChallengeLevel(0);

	LoadingLayer * _tmp;
	CCLayer * _tmp1;
	_tmp = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
	_tmp1 = Global::getInstance()->s->getSelectChallengeMenu(_tmp);

	_tmp->setNextLayer(LAYER_ID_CHALLENGE, _tmp1);
	_tmp->addLoadingLayer(0,_tmp1);


	Global::getInstance()->s->replaceScene(_tmp);
}

void ChallengeCount::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"xingxing2") == 0)
	{	
		mAnimationManager->runAnimationsForSequenceNamed("xingxing2");
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"win") == 0)
	{	
		// 道具到达上限
		setBackGround(true);
		TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_CHALLENGE_COUNT);
		_layer->doPromptByType(TEMP_PROMPT_FOOD_FULL);
		_layer->setPromptType2(1);
		Global::getInstance()->s->addLayerToRunningScene(_layer);
	}
}

void ChallengeCount::setBackGround(bool _b)
{
	isBackGround = _b;
}

void ChallengeCount::reBackWithVisiable(void)
{
	setVisible(true);
	setBackGround(false);
}

void ChallengeCount::doAction(float _f)
{
	timeCount++;
	if (timeCount % 40 == 0)
	{
		removeChild(liZiTeXiaoYanHua, true);
		CC_SAFE_RELEASE_NULL(liZiTeXiaoYanHua);
		liZiTeXiaoYanHua = CCParticleSystemQuad::create("lizitexiao/yanhua/yanhua.plist");
		liZiTeXiaoYanHua->retain();
		addChild(liZiTeXiaoYanHua,LAYER_ORDER_CONTROL);
		int i = rand()%5;

		switch(i)
		{
		case 0:
			liZiTeXiaoYanHua->setPosition(ccp(100,120));
			break;
		case 1:
			liZiTeXiaoYanHua->setPosition(ccp(700,400));
			break;
		case 2:
			liZiTeXiaoYanHua->setPosition(ccp(585,378));
			break;
		case 3:
			liZiTeXiaoYanHua->setPosition(ccp(100,400));
			break;
		case 4:
			liZiTeXiaoYanHua->setPosition(ccp(440,387));
			break;
		}
		timeCount = 0;
	}
}

void ChallengeCount::addInformationAboutGoods(void)
{
	getChildByTag(3)->getChildByTag(3)->addChild((CCSprite *)goodsNames->objectAtIndex(selectGoodsIndex));
	getChildByTag(3)->getChildByTag(4)->addChild((CCSprite *)goodsIntroduces->objectAtIndex(selectGoodsIndex));
}

void ChallengeCount::removeInformationAboutGoods(void)
{
	getChildByTag(3)->getChildByTag(3)->removeChild((CCSprite *)goodsNames->objectAtIndex(selectGoodsIndex));
	getChildByTag(3)->getChildByTag(4)->removeChild((CCSprite *)goodsIntroduces->objectAtIndex(selectGoodsIndex));
}