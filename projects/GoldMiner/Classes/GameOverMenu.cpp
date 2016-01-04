#include "GameOverMenu.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "GameControl.h"
#include "LoadingLayer.h"
#include "PromptLayer.h"
#include "Prop.h"
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
	GAMEOVERMENU_XIAOSHI_TYPE_SHOP = 0,
	GAMEOVERMENU_XIAOSHI_TYPE_MENU,
	GAMEOVERMENU_XIAOSHI_TYPE_REPLAY,
	GAMEOVERMENU_XIAOSHI_TYPE_NEXT
};

GameOverMenu::GameOverMenu(void)
	: mAnimationManager(NULL)
	, ccLayer(NULL)
	//,liZiTeXiaos(NULL)
	,liZiTeXiaoResult(NULL)
	,isBackGround(false)
{
	liZiTeXiaoYanHua = NULL;
	isWin = -1;
	propControl = new Prop();
	coinsZhuan = NULL;
	ingotsZhuan = NULL;
	goodsSprites = NULL;
	goodsNames = NULL;
	goodsId = NULL;
	goodsIntroduces = NULL;
}

void GameOverMenu::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);
	CCLayer::onExit();
}

GameOverMenu::~GameOverMenu(void)
{
	CCObject * p;
	CCARRAY_FOREACH(coinsZhuan, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CCARRAY_FOREACH(ingotsZhuan, p)
	{
		CC_SAFE_RELEASE(p);
	}
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
	if (liZiTeXiaoYanHua != NULL)
	{
		CC_SAFE_RELEASE(liZiTeXiaoYanHua);
	}
	CC_SAFE_RELEASE_NULL(mAnimationManager);


	cs::ArmatureDataManager::sharedArmatureDataManager()->removeAll();
	cs::ArmatureDataManager::sharedArmatureDataManager()->purgeArmatureSystem();
	CCTextureCache::sharedTextureCache()->removeAllTextures();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
	CCLOG("GameOverMenu::~GameOverMenu");
}

SEL_MenuHandler GameOverMenu::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnShop", GameOverMenu::onMenuItemShopClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBuy", GameOverMenu::onMenuItemBuyClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnMenu", GameOverMenu::onMenuItemMenuClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnReplay", GameOverMenu::onMenuItemReplayClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnNext", GameOverMenu::onMenuItemNextClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnSelect1", GameOverMenu::onMenuItemSelect1Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnSelect2", GameOverMenu::onMenuItemSelect2Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnSelect3", GameOverMenu::onMenuItemSelect3Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnSelect4", GameOverMenu::onMenuItemSelect4Clicked);

	return NULL;
}

cocos2d::SEL_CallFuncN GameOverMenu::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calStar1", GameOverMenu::calStar1);
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calStar2", GameOverMenu::calStar2);
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calStar3", GameOverMenu::calStar3);
}

SEL_CCControlHandler GameOverMenu::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool GameOverMenu::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void GameOverMenu::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager, cocos2d::CCLayer *_ccLayer, bool _isWin)
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

	if (_isWin)
	{
		if (Global::getInstance()->getSelectGateNextGateId() == -1)
		{
			CCMenuItemImage * _tempMenuItem = (CCMenuItemImage *)getChildByTag(2)->getChildByTag(999)->getChildByTag(3);
			CCTexture2D *pTexture;
			CCRect rect;
			pTexture = CCTextureCache::sharedTextureCache()->addImage("slsb/huishouye1.png");
			if (pTexture)
			{
				rect = CCRectZero;
				rect.size = pTexture->getContentSize();
				((CCSprite *)_tempMenuItem->getNormalImage())->setTexture(pTexture);
				((CCSprite *)_tempMenuItem->getNormalImage())->setTextureRect(rect);
				((CCSprite *)_tempMenuItem->getDisabledImage())->setTexture(pTexture);
				((CCSprite *)_tempMenuItem->getDisabledImage())->setTextureRect(rect);
			}
			pTexture = CCTextureCache::sharedTextureCache()->addImage("slsb/huishouye2.png");
			if (pTexture)
			{
				rect = CCRectZero;
				rect.size = pTexture->getContentSize();
				((CCSprite *)_tempMenuItem->getSelectedImage())->setTexture(pTexture);
				((CCSprite *)_tempMenuItem->getSelectedImage())->setTextureRect(rect);
			}
		}

		isWin = 1;
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_WIN);

		mAnimationManager->runAnimationsForSequenceNamed("win");

		ccLayer = _ccLayer;
		isCount = true;
		isZhuan = true;
		//time = 0;

		ingotsZhuan = new cocos2d::CCArray();
		coinsZhuan = new cocos2d::CCArray();
		maxContinuesCountZhuan = new cocos2d::CCArray();
		getJewelCountZhuan = new cocos2d::CCArray();

		// 星星显示
		switch(((GameControl *) _ccLayer)->getStarNum)
		{
		case 3:
			break;
		case 2:
			getChildByTag(1)->getChildByTag(6)->setVisible(false);
			break;
		case 1:
			getChildByTag(1)->getChildByTag(6)->setVisible(false);
			getChildByTag(1)->getChildByTag(5)->setVisible(false);
			break;
		case 0:
			getChildByTag(1)->getChildByTag(6)->setVisible(false);
			getChildByTag(1)->getChildByTag(5)->setVisible(false);
			getChildByTag(1)->getChildByTag(4)->setVisible(false);
			break;
		default:
			break;
		}
		char _s[32];
		// 获得元宝数
		int tmp = ((GameControl *) _ccLayer)->getIngotNum;
		int _num = 1;
		while (tmp > 0)
		{
			tmp = tmp /10;
			if (tmp > 0)
			{
				ingotsZhuan->addObject(makeZhuan(80 -_num*24, -10, 1, getChildByTag(3)->getChildByTag(2)));
				_num++;
			}
		}
		ingotsZhuan->addObject(makeZhuan(80-_num*24, -10, 1, getChildByTag(3)->getChildByTag(2)));
		sprintf(_s, "%d",((GameControl *) _ccLayer)->getIngotNum);
		ingots = CCLabelAtlas::create(_s, "slsb/yuanbaoshuzi.png", 24, 37, '0');
		ingots->setVisible(false);
		getChildByTag(3)->getChildByTag(2)->addChild(ingots, 1);
		ingots->setPosition(ccp(80 -_num*24, -10));
		// 获得连击数
		tmp = Global::getInstance()->getMaxContinusesCount();
		_num = 1;
		while (tmp > 0)
		{
			tmp = tmp /10;
			if (tmp > 0)
			{
				maxContinuesCountZhuan->addObject(makeZhuan((2-_num)*18, -16, 2, getChildByTag(3)->getChildByTag(1)));
				_num++;
			}
		}
		maxContinuesCountZhuan->addObject(makeZhuan((2-_num)*18, -16, 2, getChildByTag(3)->getChildByTag(1)));
		sprintf(_s, "%d",Global::getInstance()->getMaxContinusesCount());
		maxContinuesCount = CCLabelAtlas::create(_s, "slsb/shuzi.png", 18, 26, '0');
		maxContinuesCount->setVisible(false);
		getChildByTag(3)->getChildByTag(1)->addChild(maxContinuesCount, 1);
		maxContinuesCount->setPosition(ccp((2-_num)*18 , -16));
		// 获得钻石数
		tmp = Global::getInstance()->getGetJewelCount();
		_num = 1;
		while (tmp > 0)
		{
			tmp = tmp /10;
			if (tmp > 0)
			{
				getJewelCountZhuan->addObject(makeZhuan((2-_num)*18, -50, 2, getChildByTag(3)->getChildByTag(1)));
				_num++;
			}
		}
		getJewelCountZhuan->addObject(makeZhuan( (2-_num)*18, -50, 2, getChildByTag(3)->getChildByTag(1)));
		sprintf(_s, "%d",Global::getInstance()->getGetJewelCount());
		getJewelCount = CCLabelAtlas::create(_s, "slsb/shuzi.png", 18, 26, '0');
		getJewelCount->setVisible(false);
		getChildByTag(3)->getChildByTag(1)->addChild(getJewelCount, 1);
		getJewelCount->setPosition(ccp( (2-_num)*18 , -50));
		// 获得金币数
		tmp = ((GameControl *) _ccLayer)->getCoinNum;
		_num = 1;
		while (tmp > 0)
		{
			tmp = tmp /10;
			if (tmp > 0)
			{
				coinsZhuan->addObject(makeZhuan(50 - _num*24, 20, 0, getChildByTag(3)->getChildByTag(1)));
				_num++;
			}
		}
		coinsZhuan->addObject(makeZhuan(50 - _num*24, 20, 0, getChildByTag(3)->getChildByTag(1)));
		sprintf(_s, "%d",((GameControl *) _ccLayer)->getCoinNum);
		coins = CCLabelAtlas::create(_s, "slsb/defenshuzi.png", 24, 37, '0');
		coins->setVisible(false);
		getChildByTag(3)->getChildByTag(1)->addChild(coins, 1);
		coins->setPosition(ccp(50 - _num*24 , 20));
		jiahao = CCSprite::create("slsb/+.png");
		jiahao->setPosition(ccp(-18, 5));
		jiahao->setVisible(true);
		getChildByTag(3)->getChildByTag(2)->addChild(jiahao, 1);

		schedule( schedule_selector(GameOverMenu::doAction), 0);

		timeCount = 0;
		f_timeCount = 0;

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
		//CCParticleBatchNode *batch = CCParticleBatchNode::createWithTexture(liZiTeXiaoYanHua->getTexture());

		//batch->addChild(liZiTeXiaoYanHua);
		//addChild(batch, 10);

		//schedule(schedule_selector(GameOverMenu::switchRender), 2.0f);

		//CCNode *node = CCNode::create();
		//addChild(node);

		//m_pParent1 = batch;
		//m_pParent2 = node;
		//m_pParent1->setZOrder(1000);
		//m_pParent2->setZOrder(1000);

		//liZiTeXiaos = new cocos2d::CCArray();

		//liZiTeXiaos->addObject(CCParticleSystemQuad::create("lizitexiao/yanhua/yanhua.plist"));
		////((CCParticleSystemQuad *)liZiTeXiaos->lastObject())->setBlendFunc();
		//((CCParticleSystemQuad *)liZiTeXiaos->lastObject())->setPosition(ccp(200 + liZiTeXiaos->count()%3*200,160 + liZiTeXiaos->count()/3*160));
		//addChild(((CCParticleSystemQuad *)liZiTeXiaos->lastObject()),LAYER_ORDER_CONTROL);
	}
	else
	{
		isWin = 0;
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_FAILED);

		mAnimationManager->runAnimationsForSequenceNamed("fail");

		liZiTeXiaoResult = CCParticleSystemQuad::create("lizitexiao/xuehua/xuehua.plist");
		liZiTeXiaoResult->retain();
		liZiTeXiaoResult->setPosition(ccp(400, 480));
		addChild(liZiTeXiaoResult,LAYER_ORDER_CONTROL);
	}

	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(GameOverMenu::doAnimationCompleted));

	// 原先版本
	//if (_isWin)
	//{
	//	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_WIN);

	//	mAnimationManager->runAnimationsForSequenceNamed("win");

	//	ccLayer = _ccLayer;
	//	isCount = true;
	//	isZhuan = true;
	//	//time = 0;

	//	ingotsZhuan = new cocos2d::CCArray();
	//	coinsZhuan = new cocos2d::CCArray();

	//	switch(((GameControl *) _ccLayer)->getStarNum)
	//	{
	//	case 3:
	//		break;
	//	case 2:
	//		getChildByTag(3)->setVisible(false);
	//		break;
	//	case 1:
	//		getChildByTag(2)->setVisible(false);
	//		getChildByTag(3)->setVisible(false);
	//		break;
	//	case 0:
	//		getChildByTag(1)->setVisible(false);
	//		getChildByTag(2)->setVisible(false);
	//		getChildByTag(3)->setVisible(false);
	//		break;
	//	default:
	//		break;
	//	}
	//	char _s[32];
	//	int tmp = ((GameControl *) _ccLayer)->getIngotNum;
	//	int _num = 0;
	//	while (tmp > 0)
	//	{
	//		tmp = tmp /10;
	//		_num++;
	//		ingotsZhuan->addObject(makeZhuan(388 + _num*24, 123, 1));
	//	}
	//	ingotsZhuan->addObject(makeZhuan(388 + _num*24, 123, 1));
	//	sprintf(_s, "%d",((GameControl *) _ccLayer)->getIngotNum);
	//	ingots = CCLabelAtlas::create(_s, "shengli/yuanbaoshuzi.png", 24, 37, '0');
	//	ingots->setVisible(false);
	//	addChild(ingots, 1);
	//	ingots->setPosition(ccp(400 , 123));
	//	tmp = ((GameControl *) _ccLayer)->getCoinNum;
	//	_num = 0;
	//	while (tmp > 0)
	//	{
	//		tmp = tmp /10;
	//		_num++;
	//		coinsZhuan->addObject(makeZhuan(368 + _num*24, 170, 0));
	//	}
	//	coinsZhuan->addObject(makeZhuan(368 + _num*24, 170, 0));
	//	sprintf(_s, "%d",((GameControl *) _ccLayer)->getCoinNum);
	//	coins = CCLabelAtlas::create(_s, "shengli/defenshuzi.png", 24, 37, '0');
	//	coins->setVisible(false);
	//	addChild(coins, 1);
	//	coins->setPosition(ccp(380 , 170));
	//	jiahao = CCSprite::create("shengli/+.png");
	//	jiahao->setPosition(ccp(385, 140));
	//	jiahao->setVisible(true);
	//	addChild(jiahao, 1);

	//	schedule( schedule_selector(GameOverMenu::doAction), 0);

	//	timeCount = 0;

	//	// 转光
	//	CCSprite* sp1 = CCSprite::create("shengli/guang.png");
	//	CCRotateBy* rot = CCRotateBy::create(2, 360);
	//	CCAction* forever = CCRepeatForever::create(rot);
	//	sp1->runAction(forever);           
	//	sp1->setPosition(ccp(400,375));   
	//	addChild(sp1, -1, GAME_OVER_WIN_SHINE_TAG);

	//	liZiTeXiaos = new cocos2d::CCArray();

	//	liZiTeXiaos->addObject(CCParticleSystemQuad::create("lizitexiao/yanhua/yanhua.plist"));
	//	((CCParticleSystemQuad *)liZiTeXiaos->lastObject())->setPosition(ccp(200 + liZiTeXiaos->count()%3*200,160 + liZiTeXiaos->count()/3*160));
	//	addChild(((CCParticleSystemQuad *)liZiTeXiaos->lastObject()),LAYER_ORDER_CONTROL);
	//}
	//else
	//{
	//	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_FAILED);

	//	mAnimationManager->runAnimationsForSequenceNamed("fail");

	//	liZiTeXiaoResult = CCParticleSystemQuad::create("lizitexiao/xuehua/xuehua.plist");
	//	liZiTeXiaoResult->retain();
	//	liZiTeXiaoResult->setPosition(ccp(400, 480));
	//	addChild(liZiTeXiaoResult,LAYER_ORDER_CONTROL);
	//}
	
	CC_SAFE_RETAIN(mAnimationManager);
}

void GameOverMenu::switchRender(float dt)
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
void GameOverMenu::onMenuItemSelect1Clicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	if (isWin == -1)
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
void GameOverMenu::onMenuItemSelect2Clicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	if (isWin == -1)
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
void GameOverMenu::onMenuItemSelect3Clicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	if (isWin == -1)
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
void GameOverMenu::onMenuItemSelect4Clicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	if (isWin == -1)
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
void GameOverMenu::onMenuItemShopClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	if (isWin == -1)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	setVisible(false);
	setBackGround(true);
	Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getShopLayer(NULL, this, LAYER_ID_GAMEOVER));
}

// 购买（计费点相关）
void GameOverMenu::onMenuItemBuyClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	if (isWin == -1)
	{
		return;
	}	

	//if (((CCSprite *)goodsSprites->objectAtIndex(selectGoodsIndex))->getColor().b == myGrey.b
	//	&& ((CCSprite *)goodsSprites->objectAtIndex(selectGoodsIndex))->getColor().g == myGrey.g
	//	&& ((CCSprite *)goodsSprites->objectAtIndex(selectGoodsIndex))->getColor().r == myGrey.r)
	//{
	//	return;
	//}	

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
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMEOVER);
		//promptLayer->setForwardLayer(this);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->miaoZhunXianInformation();
	}
	else if (_id == PAY_ID_MEET && (Player::getInstance()->getPropNum(PROP_TYPE_MEET) > 99998))
	{
		// 道具到达上限
		TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_GAMEOVER);
		_layer->doPromptByType(TEMP_PROMPT_FOOD_FULL);
		_layer->setPromptType2(1);
		Global::getInstance()->s->addLayerToRunningScene(_layer);
	}
	else if (_id == PAY_ID_SUNWUKONG && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_SUNWUKONG)))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMEOVER);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->payRoleIsHaving();
	}
	else if (_id == PAY_ID_HULUWA && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_HULUWA)))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMEOVER);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->payRoleIsHaving();
	}
	else
	{
		CostLayer * _layer = (CostLayer *)Global::getInstance()->s->getCostLayer(this, LAYER_ID_GAMEOVER);
		_layer->costById(_id, CCCallFunc::create(this,callfunc_selector(GameOverMenu::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(GameOverMenu::onMenuItemPayFailed)));
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
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMEOVER);
		//promptLayer->setForwardLayer(this);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->miaoZhunXianInformation();
	}
	else if (_id == PAY_ID_MEET && (Player::getInstance()->getPropNum(PROP_TYPE_MEET) > 99998))
	{
		// 道具到达上限
		TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_GAMEOVER);
		_layer->doPromptByType(TEMP_PROMPT_FOOD_FULL);
		_layer->setPromptType2(1);
		Global::getInstance()->s->addLayerToRunningScene(_layer);
	}
	else if (_id == PAY_ID_SUNWUKONG && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_SUNWUKONG)))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMEOVER);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->payRoleIsHaving();
	}
	else if (_id == PAY_ID_HULUWA && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_HULUWA)))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMEOVER);
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
			PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMEOVER);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->miaoBuddahaInformation();
		}
		else if (_id == PAY_ID_MEET && (Player::getInstance()->getPropNum(PROP_TYPE_MEET) > 99998))
		{
			// 道具到达上限
			TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_GAMEOVER);
			_layer->doPromptByType(TEMP_PROMPT_FOOD_FULL);
			_layer->setPromptType2(1);
			Global::getInstance()->s->addLayerToRunningScene(_layer);
		}
		else if (_id == PAY_ID_SUNWUKONG && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_SUNWUKONG)))
		{
			// 提示已经购买了瞄准线了 (瞄准线最多1个)
			PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMEOVER);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->payRoleIsHaving();
		}
		else if (_id == PAY_ID_HULUWA && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_HULUWA)))
		{
			// 提示已经购买了瞄准线了 (瞄准线最多1个)
			PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMEOVER);
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
	//	PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMEOVER);
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
void GameOverMenu::onMenuItemPaySuccess(void)
{
	int selectId = ((CCInteger *)goodsId->objectAtIndex(selectGoodsIndex))->getValue();

	Global::getInstance()->getPayAwardByPayId(selectId);
	if (selectId == PAY_ID_HULUWA || selectId == PAY_ID_SUNWUKONG)
	{
		((CCSprite *)goodsSprites->objectAtIndex(selectGoodsIndex))->setColor(myGrey);
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FINISH);

	TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_GAMEOVER);
	_layer->doPromptByType(TEMP_PROMPT_BUY_SUCCESS);
	_layer->setPromptType2(1);
	Global::getInstance()->s->addLayerToRunningScene(_layer);
}


// 计费相关添加
void GameOverMenu::onMenuItemPayFailed(void)
{	
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FAILED);

	setBackGround(false);
}

// 菜单
void GameOverMenu::onMenuItemMenuClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	if (isWin == -1)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	//mAnimationManager->runAnimationsForSequenceNamed("xiaoshi");
	//xiaoshiType = GAMEOVERMENU_XIAOSHI_TYPE_MENU;
	LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
	CCLayer * p1 = Global::getInstance()->s->getSimleGateMenu(p);

	p->addLoadingLayer(0,p1);
	p->setNextLayer(LAYER_ID_SMILE_GATE_SCENCE, p1);

	Global::getInstance()->s->replaceScene(p);

	//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getSimleGateMenu());
}

// 重玩
void GameOverMenu::onMenuItemReplayClicked(cocos2d::CCObject * pSender)
{
	// loading 开始
	if (isBackGround)
	{
		return;
	}

	if (isWin == -1)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
	CCLayer * p1 = Global::getInstance()->s->getShopLayer(p, NULL, 0);

	p->addLoadingLayer(0,p1);
	p->setNextLayer(LAYER_ID_SHOP, p1);

	Global::getInstance()->s->replaceScene(p);

	//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getSelectRoleAndPropMenu());


	// 直接重新开始
	//if (isBackGround)
	//{
	//	return;
	//}
	//Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	////mAnimationManager->runAnimationsForSequenceNamed("xiaoshi");
	////xiaoshiType = GAMEOVERMENU_XIAOSHI_TYPE_REPLAY;
	////重新运行当前游戏
	////// 有loading的
	////LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
	////CCLayer * p1 = Global::getInstance()->s->getGameLayer(Global::getInstance()->getSelectGateId(), Global::getInstance()->getSelectRoleId(), p);
	////((GameControl *)p1)->setLoadingLayer(p);
	//////p->appendLoadingLayerNum(1);
	////p->addLoadingLayer(0,p1);
	////p->setNextLayer(LAYER_ID_GAMING, p1);

	////Global::getInstance()->s->replaceScene(p);
	//////Global::getInstance()->s->addLayerToRunningScene(p1);

	//// 没有loading的
	//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getGameLayer(Global::getInstance()->getSelectGateId(), Global::getInstance()->getSelectRoleId(), NULL));

	////Global::getInstance()->s->replaceScene(Global::getInstance()->s->getGameLayer(Global::getInstance()->getSelectGateId(), Global::getInstance()->getSelectRoleId()));
}

// 下一关
void GameOverMenu::onMenuItemNextClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	if (isWin != 1)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	if (Global::getInstance()->getSelectGateNextGateId() == -1)
	{
		//onMenuItemMenuClicked(this);

		LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
		CCLayer * p1 = Global::getInstance()->s->getMainLayer(p);

		p->addLoadingLayer(0,p1);
		p->setNextLayer(LAYER_ID_MAIN, p1);

		Global::getInstance()->s->replaceScene(p);

		return;
	}

	//mAnimationManager->runAnimationsForSequenceNamed("xiaoshi");
	//xiaoshiType = GAMEOVERMENU_XIAOSHI_TYPE_NEXT;
	//mAnimationManager->runAnimations("fail");
	Global::getInstance()->setSelectGateType(Global::getInstance()->getMapIdByGateId(Global::getInstance()->getSelectGateNextGateId()));
	Global::getInstance()->setSelectGateId(Global::getInstance()->getSelectGateNextGateId());
	Player::getInstance()->setLastMapId(Global::getInstance()->getSelectGateType());
	
	LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
	CCLayer * p1 = Global::getInstance()->s->getShopLayer(p, NULL, 0);

	p->addLoadingLayer(0,p1);
	p->setNextLayer(LAYER_ID_SHOP, p1);

	Global::getInstance()->s->replaceScene(p);
	
	//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getSelectRoleAndPropMenu());
}

void GameOverMenu::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"xingxing2") == 0)
	{	
		mAnimationManager->runAnimationsForSequenceNamed("xingxing2");
	}
}

void GameOverMenu::setBackGround(bool _b)
{
	isBackGround = _b;
}

void GameOverMenu::reBackWithVisiable(void)
{
	setVisible(true);
	setBackGround(false);
}

void GameOverMenu::calStar1(CCNode* sender)
{
	if (((GameControl *)ccLayer)->getStarNum > 0)
	{
		liZiTeXiao = CCParticleSystemQuad::create("lizitexiao/baoxingxing/baoxingxing.plist");//plist文件可以通过例子编辑器获得
		liZiTeXiao->setPosition(ccp(173,330));
		addChild(liZiTeXiao);
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_START_ONE);
	}
}

void GameOverMenu::calStar2(CCNode* sender)
{
	if (((GameControl *)ccLayer)->getStarNum > 1)
	{
		removeChild(liZiTeXiao);
		liZiTeXiao = CCParticleSystemQuad::create("lizitexiao/baoxingxing/baoxingxing.plist");//plist文件可以通过例子编辑器获得
		liZiTeXiao->setPosition(ccp(253,330));
		addChild(liZiTeXiao);
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_START_TWO);
	}
}

void GameOverMenu::calStar3(CCNode* sender)
{
	if (((GameControl *)ccLayer)->getStarNum > 2)
	{
		removeChild(liZiTeXiao);
		liZiTeXiao = CCParticleSystemQuad::create("lizitexiao/baoxingxing/baoxingxing.plist");//plist文件可以通过例子编辑器获得
		liZiTeXiao->setPosition(ccp(333,330));
		addChild(liZiTeXiao);
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_START_THREE);
	}
	mAnimationManager->runAnimationsForSequenceNamed("xingxing2");
}

void GameOverMenu::doAction(float _f)
{
	if (isCount)
	{
		timeCount++;
		f_timeCount += _f;
#ifdef										GOLDEN_MINER_2_VERSION_TIME
		if ((f_timeCount >= GAME_OVER_WIN_NUM_TIME/SCHEDULE_TIMES) && ((f_timeCount - _f) <= GAME_OVER_WIN_NUM_TIME/SCHEDULE_TIMES))
#else
		if (timeCount == GAME_OVER_WIN_NUM_TIME)
#endif
		{
			for (int i = 0; i < ingotsZhuan->count(); i++)
			{
				CCArray * tmp = (CCArray *)ingotsZhuan->objectAtIndex(i);
				((CCLabelAtlas *)tmp->objectAtIndex((timeCount-1)%tmp->count()))->setVisible(false);
			}
			for (int i = 0; i < coinsZhuan->count(); i++)
			{
				CCArray * tmp = (CCArray *)coinsZhuan->objectAtIndex(i);
				((CCLabelAtlas *)tmp->objectAtIndex((timeCount-1)%tmp->count()))->setVisible(false);
			}
			for (int i = 0; i < maxContinuesCountZhuan->count(); i++)
			{
				CCArray * tmp = (CCArray *)maxContinuesCountZhuan->objectAtIndex(i);
				((CCLabelAtlas *)tmp->objectAtIndex((timeCount-1)%tmp->count()))->setVisible(false);
				//for(int j = 0; j < tmp->count(); j++)
				//{
				//	((CCLabelAtlas *)tmp->objectAtIndex(j))->setVisible(false);
				//}
			}
			for (int i = 0; i < getJewelCountZhuan->count(); i++)
			{
				CCArray * tmp = (CCArray *)getJewelCountZhuan->objectAtIndex(i);
				((CCLabelAtlas *)tmp->objectAtIndex((timeCount-1)%tmp->count()))->setVisible(false);
				//for(int j = 0; j < tmp->count(); j++)
				//{
				//	((CCLabelAtlas *)tmp->objectAtIndex(j))->setVisible(false);
				//}
			}
			coins->setVisible(true);
			ingots->setVisible(true);
			maxContinuesCount->setVisible(true);
			getJewelCount->setVisible(true);
			isZhuan = false;
		}
		else
		{
			if (isZhuan)
			{
				for (int i = 0; i < ingotsZhuan->count(); i++)
				{
					CCArray * tmp = (CCArray *)ingotsZhuan->objectAtIndex(i);
					((CCLabelAtlas *)tmp->objectAtIndex(timeCount%tmp->count()))->setVisible(true);
					((CCLabelAtlas *)tmp->objectAtIndex((timeCount-1)%tmp->count()))->setVisible(false);
				}
				for (int i = 0; i < coinsZhuan->count(); i++)
				{
					CCArray * tmp = (CCArray *)coinsZhuan->objectAtIndex(i);
					((CCLabelAtlas *)tmp->objectAtIndex(timeCount%tmp->count()))->setVisible(true);
					((CCLabelAtlas *)tmp->objectAtIndex((timeCount-1)%tmp->count()))->setVisible(false);
				}
				for (int i = 0; i < maxContinuesCountZhuan->count(); i++)
				{
					CCArray * tmp = (CCArray *)maxContinuesCountZhuan->objectAtIndex(i);
					((CCLabelAtlas *)tmp->objectAtIndex(timeCount%tmp->count()))->setVisible(true);
					((CCLabelAtlas *)tmp->objectAtIndex((timeCount-1)%tmp->count()))->setVisible(false);
				}
				for (int i = 0; i < getJewelCountZhuan->count(); i++)
				{
					CCArray * tmp = (CCArray *)getJewelCountZhuan->objectAtIndex(i);
					((CCLabelAtlas *)tmp->objectAtIndex(timeCount%tmp->count()))->setVisible(true);
					((CCLabelAtlas *)tmp->objectAtIndex((timeCount-1)%tmp->count()))->setVisible(false);
				}
			}
		}
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
		/*	liZiTeXiaos->addObject(CCParticleSystemQuad::create("lizitexiao/yanhua/yanhua.plist"));
			getChildByTag(5)->getChildByTag(timeCount%GAME_OVER_WIN_SYSTEM_POSITION_NUM + 1)->addChild((CCParticleSystemQuad *)liZiTeXiaos->lastObject());
		*/}
	}
	else
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
			/*	liZiTeXiaos->addObject(CCParticleSystemQuad::create("lizitexiao/yanhua/yanhua.plist"));
			getChildByTag(5)->getChildByTag(timeCount%GAME_OVER_WIN_SYSTEM_POSITION_NUM + 1)->addChild((CCParticleSystemQuad *)liZiTeXiaos->lastObject());
			*/timeCount = 0;
		}
	}
}

CCArray * GameOverMenu::makeZhuan(double _x, double _y, int _type, CCNode * _node)
{
	CCArray * res = CCArray::create();
	char _s[32];
	for (int i = 0; i < 10; i++)
	{
		sprintf(_s, "%d",i);
		CCLabelAtlas * tmp = NULL;
		if (_type == 0)
		{ 
			tmp= CCLabelAtlas::create(_s, "slsb/defenshuzi.png", 24, 37, '0');
		}
		else if (_type == 1)
		{
			tmp = CCLabelAtlas::create(_s, "slsb/yuanbaoshuzi.png", 24, 37, '0');
		}
		else if (_type == 2)
		{
			tmp = CCLabelAtlas::create(_s, "slsb/shuzi.png", 18, 26, '0');
		}
		tmp->setVisible(false);
		tmp->setPosition(ccp(_x, _y));
		res->addObject(tmp);
		_node->addChild(tmp);
	}

	((CCLabelAtlas *)res->objectAtIndex(0))->setVisible(true);

	return res;
}

void GameOverMenu::addInformationAboutGoods(void)
{
	getChildByTag(3)->getChildByTag(3)->addChild((CCSprite *)goodsNames->objectAtIndex(selectGoodsIndex));
	getChildByTag(3)->getChildByTag(4)->addChild((CCSprite *)goodsIntroduces->objectAtIndex(selectGoodsIndex));
}

void GameOverMenu::removeInformationAboutGoods(void)
{
	getChildByTag(3)->getChildByTag(3)->removeChild((CCSprite *)goodsNames->objectAtIndex(selectGoodsIndex));
	getChildByTag(3)->getChildByTag(4)->removeChild((CCSprite *)goodsIntroduces->objectAtIndex(selectGoodsIndex));
}