#include "Shop.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "RoleInformation.h"
#include "Player.h"
#include "CartoonLayer.h"
#include "GameControl.h"
#include "LoadingLayer.h"
#include "PromptLayer.h"
#include "Prop.h"
#include "PauseMenu.h"
#include "MainAppendLayer.h"
#include "BigGateMenu.h"
#include "GameOverMenu.h"
#include "PayService.h"
#include "SelectChallenge.h"
#include "SelectRoleAndPet.h"
#include "TemporaryPromptLayer.h"
#include "CostLayer.h"
#include "ChallengeCount.h"
#include "SpotLightLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

//#define							SHOP_CEIL_IS_MENU				

static const ccColor3B myGrey={60,60,60};
static const ccColor4B myGrey4 = {0,0,0,200};

Shop::Shop(void)
	: mAnimationManager(NULL)
	,greyLayer(NULL)
	,isBackGround(false)
	,loadingLayer(NULL)
{
	isDoAction = false;
	isBackGround2 = false;
	ingotNum = NULL;
	propName = NULL;
	propIntroduce = NULL;
	propPrice = NULL;
	propIngotNum = NULL;
	propBuyNum = NULL;
	selectId = -1;
	selectCeil = NULL;
	isBuy = false;
	startTimeCount = -1;
	isSpot = false;
	myItemIsCanTouched = true;
	//isCheck = false;
}


Shop::~Shop(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);

	CCObject * p ;
	CCARRAY_FOREACH(pages1, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(pages2, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}

	CCLOG("Shop::~Shop");
}

void Shop::onEnter(void)
{
	CCLayer::onEnter();

	setVisible(false);
	isBackGround = true;

	Global::getInstance()->setSelectRoleId(Player::getInstance()->getLastRoleSelect());

	Player::getInstance()->getMusicControl()->playOtherBackGround();

	greyLayer = CCLayerColor::create(myGrey4);
	greyLayer->setVisible(false);
	getChildByTag(4)->addChild(greyLayer, -999);
	getChildByTag(4)->setZOrder(400);
	getChildByTag(3)->setZOrder(300);
	getChildByTag(2)->setZOrder(200);
	getChildByTag(1)->setZOrder(100);

	setIngotNum();


#ifdef											SHOP_CEIL_IS_MENU
	// 上面的页面
	pages1 = new cocos2d::CCArray();
	pages1->addObject(new ShopCeilSpecail(SHOP_CEIL_WITHOUT_INGOT, PAY_ID_SUNWUKONG, this, true));
	((ShopCeilSpecail *)pages1->lastObject())->setPositionX(-132);
	((ShopCeilSpecail *)pages1->lastObject())->setTouchEnabled(false);
	getChildByTag(2)->getChildByTag(1)->addChild((ShopCeilSpecail *)pages1->lastObject());
	pages1->addObject(new ShopCeilSpecail(SHOP_CEIL_WITHOUT_INGOT, PAY_ID_BUDDAHA, this, true));
	((ShopCeilSpecail *)pages1->lastObject())->setTouchEnabled(false);
	((ShopCeilSpecail *)pages1->lastObject())->setPositionX(-38);
	getChildByTag(2)->getChildByTag(1)->addChild((ShopCeilSpecail *)pages1->lastObject());
	pages1->addObject(new ShopCeilSpecail(SHOP_CEIL_WITHOUT_INGOT, PAY_ID_MEET, this, true));
	((ShopCeilSpecail *)pages1->lastObject())->setTouchEnabled(false);
	((ShopCeilSpecail *)pages1->lastObject())->setPositionX(58);
	getChildByTag(2)->getChildByTag(1)->addChild((ShopCeilSpecail *)pages1->lastObject());
	pages1->addObject(new ShopCeilSpecail(SHOP_CEIL_WITHOUT_INGOT, PAY_ID_HULUWA, this, true));
	((ShopCeilSpecail *)pages1->lastObject())->setTouchEnabled(false);
	((ShopCeilSpecail *)pages1->lastObject())->setPositionX(152);
	getChildByTag(2)->getChildByTag(1)->addChild((ShopCeilSpecail *)pages1->lastObject());

	//// 下面的页面
	//pages1 = new cocos2d::CCArray();
	//pages1->addObject(new ShopCeilSpecail(SHOP_CEIL_WITHOUT_INGOT, PROP_TYPE_MOONLIGHT, this, false));
	//((ShopCeilSpecail *)pages1->lastObject())->setPositionX(-132);
	//getChildByTag(2)->getChildByTag(1)->addChild((ShopCeilSpecail *)pages1->lastObject());
	//pages1->addObject(new ShopCeilSpecail(SHOP_CEIL_WITHOUT_INGOT, PROP_TYPE_GRENADE, this, false));
	//((ShopCeilSpecail *)pages1->lastObject())->setPositionX(-38);
	//getChildByTag(2)->getChildByTag(1)->addChild((ShopCeilSpecail *)pages1->lastObject());
	//pages1->addObject(new ShopCeilSpecail(SHOP_CEIL_WITHOUT_INGOT, PROP_TYPE_VIGOROUSLY_PILL, this, false));
	//((ShopCeilSpecail *)pages1->lastObject())->setPositionX(58);
	//getChildByTag(2)->getChildByTag(1)->addChild((ShopCeilSpecail *)pages1->lastObject());
	//pages1->addObject(new ShopCeilSpecail(SHOP_CEIL_WITHOUT_INGOT, PROP_TYPE_ALIGNMENT, this, false));
	//((ShopCeilSpecail *)pages1->lastObject())->setPositionX(152);
	//getChildByTag(2)->getChildByTag(1)->addChild((ShopCeilSpecail *)pages1->lastObject());

	// 下面的页面
	pages2 = new cocos2d::CCArray();
	pages2->addObject(new ShopCeilSpecail(SHOP_CEIL_WITHOUT_INGOT, PROP_TYPE_MOONLIGHT, this, false));
	((ShopCeilSpecail *)pages2->lastObject())->setPositionX(-132);
	getChildByTag(2)->getChildByTag(2)->addChild((ShopCeilSpecail *)pages2->lastObject());
	pages2->addObject(new ShopCeilSpecail(SHOP_CEIL_WITHOUT_INGOT, PROP_TYPE_GRENADE, this, false));
	((ShopCeilSpecail *)pages2->lastObject())->setPositionX(-38);
	getChildByTag(2)->getChildByTag(2)->addChild((ShopCeilSpecail *)pages2->lastObject());
	pages2->addObject(new ShopCeilSpecail(SHOP_CEIL_WITHOUT_INGOT, PROP_TYPE_VIGOROUSLY_PILL, this, false));
	((ShopCeilSpecail *)pages2->lastObject())->setPositionX(58);
	getChildByTag(2)->getChildByTag(2)->addChild((ShopCeilSpecail *)pages2->lastObject());
	pages2->addObject(new ShopCeilSpecail(SHOP_CEIL_WITHOUT_INGOT, PROP_TYPE_ALIGNMENT, this, false));
	((ShopCeilSpecail *)pages2->lastObject())->setPositionX(152);
	getChildByTag(2)->getChildByTag(2)->addChild((ShopCeilSpecail *)pages2->lastObject());
#else
	pageMenu = NULL;
	pageMenu = CCMenu::create(NULL);
	int _appendX = -412;
	int _appendY = -235;
	getChildByTag(2)->getChildByTag(1)->addChild(pageMenu, -1);

	// 上面的页面
#ifdef								GOLDEN_MINER2_VERSION_PAY_IS_HAVING_PACKAGE
	pages1 = new cocos2d::CCArray();
	if (Player::getInstance()->getPay(PAY_ID_SUNWUKONG))
	{
		if (Player::getInstance()->getPay(PAY_ID_HULUWA))
		{
			pages1->addObject(new ShopCeil(SHOP_CEIL_WITHOUT_INGOT, PAY_ID_MEET, this, true));
			((ShopCeil *)pages1->lastObject())->setTouchEnabled(false);
			((ShopCeil *)pages1->lastObject())->setPosition(-132 , 0);
			((ShopCeil *)pages1->lastObject())->getMenuItem()->setPosition(-120 + _appendX, -5 + _appendY);
			getChildByTag(2)->getChildByTag(1)->addChild((ShopCeil *)pages1->lastObject());
		}
		else
		{
			pages1->addObject(new ShopCeil(SHOP_CEIL_WITHOUT_INGOT, PAY_ID_HULUWA, this, true));
			((ShopCeil *)pages1->lastObject())->setTouchEnabled(false);
			((ShopCeil *)pages1->lastObject())->setPosition(-132, 0);
			((ShopCeil *)pages1->lastObject())->getMenuItem()->setPosition(-120 + _appendX, -5 + _appendY);
			getChildByTag(2)->getChildByTag(1)->addChild((ShopCeil *)pages1->lastObject());
		}
	}
	else
	{
		pages1->addObject(new ShopCeil(SHOP_CEIL_WITHOUT_INGOT, PAY_ID_SUNWUKONG, this, true));
		((ShopCeil *)pages1->lastObject())->setTouchEnabled(false);
		((ShopCeil *)pages1->lastObject())->setPosition(-132, 0);
		((ShopCeil *)pages1->lastObject())->getMenuItem()->setPosition(-120 + _appendX, -5 + _appendY);
		getChildByTag(2)->getChildByTag(1)->addChild((ShopCeil *)pages1->lastObject());
	}
	
	pages1->addObject(new ShopCeil(SHOP_CEIL_WITHOUT_INGOT, PAY_ID_BUDDAHA, this, true));
	((ShopCeil *)pages1->lastObject())->setTouchEnabled(false);
	((ShopCeil *)pages1->lastObject())->setPosition(-38, 0);
	((ShopCeil *)pages1->lastObject())->getMenuItem()->setPosition(-26 + _appendX, -5 + _appendY);
	getChildByTag(2)->getChildByTag(1)->addChild((ShopCeil *)pages1->lastObject());
	pages1->addObject(new ShopCeil(SHOP_CEIL_WITHOUT_INGOT, PAY_ID_VALUE_PACKAGE, this, true));
	((ShopCeil *)pages1->lastObject())->setTouchEnabled(false);
	((ShopCeil *)pages1->lastObject())->setPosition(58 , 0);
	((ShopCeil *)pages1->lastObject())->getMenuItem()->setPosition(70 + _appendX, -5 + _appendY);
	getChildByTag(2)->getChildByTag(1)->addChild((ShopCeil *)pages1->lastObject());
	pages1->addObject(new ShopCeil(SHOP_CEIL_WITHOUT_INGOT, PAY_ID_GOLDEN_PACKAGE, this, true));
	((ShopCeil *)pages1->lastObject())->setTouchEnabled(false);
	((ShopCeil *)pages1->lastObject())->setPosition(152 , 0);
	((ShopCeil *)pages1->lastObject())->getMenuItem()->setPosition(164 + _appendX, -5 + _appendY);
	getChildByTag(2)->getChildByTag(1)->addChild((ShopCeil *)pages1->lastObject());
#else
	pages1 = new cocos2d::CCArray();
	pages1->addObject(new ShopCeil(SHOP_CEIL_WITHOUT_INGOT, PAY_ID_SUNWUKONG, this, true));
	((ShopCeil *)pages1->lastObject())->setTouchEnabled(false);
	((ShopCeil *)pages1->lastObject())->setPosition(-132, 0);
	((ShopCeil *)pages1->lastObject())->getMenuItem()->setPosition(-120 + _appendX, -5 + _appendY);
	getChildByTag(2)->getChildByTag(1)->addChild((ShopCeil *)pages1->lastObject());
	pages1->addObject(new ShopCeil(SHOP_CEIL_WITHOUT_INGOT, PAY_ID_BUDDAHA, this, true));
	((ShopCeil *)pages1->lastObject())->setTouchEnabled(false);
	((ShopCeil *)pages1->lastObject())->setPosition(-38, 0);
	((ShopCeil *)pages1->lastObject())->getMenuItem()->setPosition(-26 + _appendX, -5 + _appendY);
	getChildByTag(2)->getChildByTag(1)->addChild((ShopCeil *)pages1->lastObject());
	pages1->addObject(new ShopCeil(SHOP_CEIL_WITHOUT_INGOT, PAY_ID_MEET, this, true));
	((ShopCeil *)pages1->lastObject())->setTouchEnabled(false);
	((ShopCeil *)pages1->lastObject())->setPosition(58 , 0);
	((ShopCeil *)pages1->lastObject())->getMenuItem()->setPosition(70 + _appendX, -5 + _appendY);
	getChildByTag(2)->getChildByTag(1)->addChild((ShopCeil *)pages1->lastObject());
	pages1->addObject(new ShopCeil(SHOP_CEIL_WITHOUT_INGOT, PAY_ID_HULUWA, this, true));
	((ShopCeil *)pages1->lastObject())->setTouchEnabled(false);
	((ShopCeil *)pages1->lastObject())->setPosition(152, 0);
	((ShopCeil *)pages1->lastObject())->getMenuItem()->setPosition(164 + _appendX, -5 + _appendY);
	getChildByTag(2)->getChildByTag(1)->addChild((ShopCeil *)pages1->lastObject());
#endif


	// 下面的页面
	pages2 = new cocos2d::CCArray();
	pages2->addObject(new ShopCeil(SHOP_CEIL_WITHOUT_INGOT, PROP_TYPE_MOONLIGHT, this, false));
	((ShopCeil *)pages2->lastObject())->setPosition(-132, -133);
	((ShopCeil *)pages2->lastObject())->getMenuItem()->setPosition(-120 + _appendX, -138 + _appendY);
	getChildByTag(2)->getChildByTag(1)->addChild((ShopCeil *)pages2->lastObject());
	pages2->addObject(new ShopCeil(SHOP_CEIL_WITHOUT_INGOT, PROP_TYPE_GRENADE, this, false));
	((ShopCeil *)pages2->lastObject())->setPosition(-38, -133);
	((ShopCeil *)pages2->lastObject())->getMenuItem()->setPosition(-26 + _appendX, -138 + _appendY);
	getChildByTag(2)->getChildByTag(1)->addChild((ShopCeil *)pages2->lastObject());
	pages2->addObject(new ShopCeil(SHOP_CEIL_WITHOUT_INGOT, PROP_TYPE_VIGOROUSLY_PILL, this, false));
	((ShopCeil *)pages2->lastObject())->setPosition(58, -133);
	((ShopCeil *)pages2->lastObject())->getMenuItem()->setPosition(70 + _appendX, -138 + _appendY);
	getChildByTag(2)->getChildByTag(1)->addChild((ShopCeil *)pages2->lastObject());
	pages2->addObject(new ShopCeil(SHOP_CEIL_WITHOUT_INGOT, PROP_TYPE_ALIGNMENT, this, false));
	((ShopCeil *)pages2->lastObject())->setPosition(152, -133);
	((ShopCeil *)pages2->lastObject())->getMenuItem()->setPosition(164 + _appendX, -138 + _appendY);
	getChildByTag(2)->getChildByTag(1)->addChild((ShopCeil *)pages2->lastObject());
#endif

	setTouchEnabled(true);
	setKeypadEnabled(true);

	schedule( schedule_selector(Shop::doAction), 0);
}

void Shop::onEnterTransitionDidFinish(void)
{
	CCLayer::onEnterTransitionDidFinish();

	if (loadingLayer != NULL)
	{
		((LoadingLayer *)loadingLayer)->appendFinishLayerNum(1);
	}
	else
	{
		startSelf();
	}
}

void Shop::startSelf(void)
{
	setVisible(true);
	isBackGround = false;
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
	//isCheck = true;
	setIsDoaction(true);//isDoAction = true;
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_SHOP);
}

void Shop::setLoadingLayer(cocos2d::CCLayer * _layer)
{
	loadingLayer = _layer;

	if (loadingLayer == NULL)
	{
		setVisible(true);
		//getChildByTag(2)->getChildByTag(998)->getChildByTag(3)->setVisible(false); // 屏蔽选人按钮
		getChildByTag(1)->getChildByTag(999)->getChildByTag(1)->setVisible(false);
	}
}

void Shop::keyBackClicked(void)	
{
	onMenuItemBackClicked(NULL);
}

void Shop::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

SEL_MenuHandler Shop::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBack", Shop::onMenuItemBackClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnStart", Shop::onMenuItemPlayClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnPlus", Shop::onMenuItemPlusClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnPerson", Shop::onMenuItemPersonClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnOff", Shop::onMenuItemOffClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBuy", Shop::onMenuItemBuyClicked);

	return NULL;
}

SEL_CCControlHandler Shop::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool Shop::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void Shop::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;

#ifndef										GOLDEN_MINER_2_BUY_INGOT	
	getChildByTag(2)->getChildByTag(998)->getChildByTag(89)->setVisible(false);
#endif
	//mAnimationManager->runAnimationsForSequenceNamed("daojuchuxian");
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(Shop::doAnimationCompleted));
	CC_SAFE_RETAIN(mAnimationManager);
}

void Shop::setBackGround2(bool _b)
{
	isBackGround2 = _b;


#ifdef						GOLDEN_MINER_2_VERSION_PAY
	// 计费相关添加
	if (!_b && selectCeil->getIsPay())
	{
		setBackGround(false);

#ifdef						SHOP_CEIL_IS_MENU

		for (int i = 0; i < pages1->count(); i++)
		{
			((ShopCeilSpecail *)pages1->objectAtIndex(i))->setTouchEnabled(true);
		}
		for (int i = 0; i < pages2->count(); i++)
		{
			((ShopCeilSpecail *)pages2->objectAtIndex(i))->setTouchEnabled(true);
		}
		myItemIsCanTouched = true;
#else
		for (int i = 0; i < pages1->count(); i++)
		{
			((ShopCeil *)pages1->objectAtIndex(i))->setTouchEnabled(true);
		}
		for (int i = 0; i < pages2->count(); i++)
		{
			((ShopCeil *)pages2->objectAtIndex(i))->setTouchEnabled(true);
		}
		myItemIsCanTouched = true;
#endif

		selectId = -1;
		selectCeil = NULL;
	}
	
#endif
}

void Shop::setBackGround(bool _b)
{

	greyLayer->setVisible(_b);

	isBackGround = _b;
}

void Shop::onMenuItemPersonClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		if (!isSpot)
		{
			return;
		}
		else
		{
			spotLighLayerCallBack();
		}
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	//Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getSelectRoleAndPetMenu(NULL));
	SelectRoleAndPet * _tmp = (SelectRoleAndPet *)Global::getInstance()->s->getSelectRoleAndPetMenu(NULL);
	//Global::getInstance()->s->replaceScene(_tmp);
	setPropInformation(-1, NULL, true);
	setBackGround(true);
	((CCMenu *)getChildByTag(1)->getChildByTag(999))->setVisible(false);
	((CCMenu *)getChildByTag(2)->getChildByTag(998))->setVisible(false);
	_tmp->setForwardLayer(this, LAYER_ID_SHOP);
	Global::getInstance()->s->addLayerToRunningScene(_tmp);
	if (getChildByTag(1)->getChildByTag(999)->getChildByTag(1)->isVisible())
	{
		_tmp->setBackInformation(0, 0);
	}
	else
	{
		_tmp->setBackInformation(forwardLayer, forwardType);
	}
}

void Shop::onMenuItemOffClicked(cocos2d::CCObject * pSender)
{
	if (isDoAction)
	{
		return;
	}

	if (!isBackGround)
	{
		return;
	}

	if (isBackGround2)
	{
		return;
	}

#ifdef										SHOP_CEIL_IS_MENU
	for (int i = 0; i < pages1->count(); i++)
	{
		((ShopCeilSpecail *)pages1->objectAtIndex(i))->setTouchEnabled(true);
	}
	for (int i = 0; i < pages2->count(); i++)
	{
		((ShopCeilSpecail *)pages2->objectAtIndex(i))->setTouchEnabled(true);
	}
	myItemIsCanTouched = true;
#else
	for (int i = 0; i < pages1->count(); i++)
	{
		((ShopCeil *)pages1->objectAtIndex(i))->setTouchEnabled(true);
	}
	for (int i = 0; i < pages2->count(); i++)
	{
		((ShopCeil *)pages2->objectAtIndex(i))->setTouchEnabled(true);
	}
	myItemIsCanTouched = true;
#endif

	selectId = -1;
	selectCeil = NULL;

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	mAnimationManager->runAnimationsForSequenceNamed("shouhui");
	setIsDoaction(true);//isDoAction = true;
	if (propName != NULL)
	{
		propName->setVisible(false);
		propIntroduce->setVisible(false);
		propPrice->setVisible(false);
		propIngotNum->setVisible(false);
		propBuyNum->setVisible(false);
	}
}

void Shop::onMenuItemBuyClicked(cocos2d::CCObject * pSender)
{
	if (isDoAction)
	{
		return;
	}

	if (!isBackGround)
	{
		return;
	}

	if (isBackGround2)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	if (selectId == PROP_TYPE_ALIGNMENT && (Player::getInstance()->getPropNum(PROP_TYPE_ALIGNMENT) > 0))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_SHOP);
		setBackGround2(true);
		//promptLayer->setForwardLayer(this);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->miaoZhunXianInformation();
	}
	else if (selectId != PROP_TYPE_ALIGNMENT && (Player::getInstance()->getPropNum(selectId) > 98))
	{
		// 道具到达上限
		TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_SHOP);
		setBackGround2(true);
		_layer->doPromptByType(TEMP_PROMPT_PROP_FULL);
		_layer->setPromptType2(2);
		Global::getInstance()->s->addLayerToRunningScene(_layer);
	}
	else
	{
		if (Player::getInstance()->getPropNum(PROP_TYPE_INGOT) >= propControl->getPrice(selectId))
		{
			isBuy = true;
			Player::getInstance()->appendPropNum(PROP_TYPE_INGOT ,-propControl->getPrice(selectId));
			Player::getInstance()->savePropNum(PROP_TYPE_INGOT ,-propControl->getPrice(selectId));
			Player::getInstance()->appendPropNum(selectId ,1);
			Player::getInstance()->savePropNum(selectId ,1);

			setIngotNum();

			selectCeil->updateNum();

			if(propIngotNum != NULL)
			{
				getChildByTag(4)->getChildByTag(4)->removeChild(propBuyNum);
				getChildByTag(4)->getChildByTag(5)->removeChild(propIngotNum);
				propIngotNum = NULL;
				propBuyNum = NULL;
			}
			propIngotNum = CCLabelAtlas::create(ingotNum->getString(), "shangcheng/shuzi.png", 15, 20, '0');
			propBuyNum = CCLabelAtlas::create(selectCeil->getNum()->getString(), "shangcheng/shuzi.png", 15, 20, '0');
			getChildByTag(4)->getChildByTag(4)->addChild(propBuyNum);
			getChildByTag(4)->getChildByTag(5)->addChild(propIngotNum);
			propBuyNum->setPosition(ccp(5,-8));
			propIngotNum->setPosition(ccp(-12,-8));

			Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FINISH);

			TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_SHOP);
			setBackGround2(true);
			_layer->doPromptByType(TEMP_PROMPT_BUY_SUCCESS);
			_layer->setPromptType2(2);
			Global::getInstance()->s->addLayerToRunningScene(_layer);
		}
		else
		{
			// 钱不够购买
			Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FAILED);

			TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_SHOP);
			setBackGround2(true);
			_layer->doPromptByType(TEMP_PROMPT_INGOT_NOT_RICH);
			_layer->setPromptType2(2);
			Global::getInstance()->s->addLayerToRunningScene(_layer);
		}
	}
}

void Shop::onMenuItemButtonClicked(void)
{
	if (isDoAction)
	{
		return;
	}

	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	setBackGround(true);
	mAnimationManager->runAnimationsForSequenceNamed("tanchu");
	setIsDoaction(true);//isDoAction = true;
}

void Shop::onMenuItemPayButtonClicked(void)
{
	// 计费相关添加
	if (isBackGround)
	{
		return;
	}
	bool _flag = true;
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	setBackGround(true);
#ifdef						GOLDEN_MINER_2_VERSION_PAY
#ifdef						GOLDEN_MINER2_VERSION_PAY_SELF
	_flag = false;

	if (selectId == PAY_ID_BUDDAHA && (Player::getInstance()->getPropNum(PROP_TYPE_BUDDAHA) == 1))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_SHOP);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->miaoBuddahaInformation();
	}
	else if (selectId == PAY_ID_MEET && (Player::getInstance()->getPropNum(PROP_TYPE_MEET) > 99998))
	{
		// 道具到达上限
		TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_SHOP);
		_layer->doPromptByType(TEMP_PROMPT_FOOD_FULL);
		_layer->setPromptType2(1);
		Global::getInstance()->s->addLayerToRunningScene(_layer);
	}
	else if (selectId == PAY_ID_SUNWUKONG && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_SUNWUKONG)))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_SHOP);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->payRoleIsHaving();
	}
	else if (selectId == PAY_ID_HULUWA && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_HULUWA)))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_SHOP);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->payRoleIsHaving();
	}
	else
	{
		CostLayer * _layer = (CostLayer *)Global::getInstance()->s->getCostLayer(this, LAYER_ID_SHOP);
		_layer->costById(selectId, CCCallFunc::create(this,callfunc_selector(Shop::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(Shop::onMenuItemPayFailed)));
		Global::getInstance()->s->addLayerToRunningScene(_layer);
	}
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
	_flag = false;

	if (selectId == PAY_ID_BUDDAHA && (Player::getInstance()->getPropNum(PROP_TYPE_BUDDAHA) == 1))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_SHOP);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->miaoBuddahaInformation();
	}
	else if (selectId == PAY_ID_MEET && (Player::getInstance()->getPropNum(PROP_TYPE_MEET) > 99998))
	{
		// 道具到达上限
		TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_SHOP);
		_layer->doPromptByType(TEMP_PROMPT_FOOD_FULL);
		_layer->setPromptType2(1);
		Global::getInstance()->s->addLayerToRunningScene(_layer);
	}
	else if (selectId == PAY_ID_SUNWUKONG && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_SUNWUKONG)))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_SHOP);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->payRoleIsHaving();
	}
	else if (selectId == PAY_ID_HULUWA && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_HULUWA)))
	{
		// 提示已经购买了瞄准线了 (瞄准线最多1个)
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_SHOP);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->payRoleIsHaving();
	}
	else
	{
		if (selectId == PAY_ID_BUDDAHA && selectId == PAY_ID_MEET)
		{
			PayService::getInstance()->pay(selectId, true,  CCCallFunc::create(this,callfunc_selector(Shop::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(Shop::onMenuItemPayFailed)));
		}
		else
		{
			PayService::getInstance()->pay(selectId, true,  CCCallFunc::create(this,callfunc_selector(Shop::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(Shop::onMenuItemPayFailed)));
			//PayService::getInstance()->pay(selectId, false, CCCallFunc::create(this, callfunc_selector(Shop::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(Shop::onMenuItemPayFailed)));
		}
	}

#endif
#endif
#endif
	if (_flag)
	{
		if (selectId == PAY_ID_BUDDAHA && (Player::getInstance()->getPropNum(PROP_TYPE_BUDDAHA) == 1))
		{
			// 提示已经购买了瞄准线了 (瞄准线最多1个)
			PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_SHOP);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->miaoBuddahaInformation();
		}
		else if (selectId == PAY_ID_MEET && (Player::getInstance()->getPropNum(PROP_TYPE_MEET) > 99998))
		{
			// 道具到达上限
			TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_SHOP);
			_layer->doPromptByType(TEMP_PROMPT_FOOD_FULL);
			_layer->setPromptType2(1);
			Global::getInstance()->s->addLayerToRunningScene(_layer);
		}
		else if (selectId == PAY_ID_SUNWUKONG && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_SUNWUKONG)))
		{
			// 提示已经购买了瞄准线了 (瞄准线最多1个)
			PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_SHOP);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->payRoleIsHaving();
		}
		else if (selectId == PAY_ID_HULUWA && (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_HULUWA)))
		{
			// 提示已经购买了瞄准线了 (瞄准线最多1个)
			PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_SHOP);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->payRoleIsHaving();
		}
		else
		{
			onMenuItemPaySuccess();
		}
	}
}


// 计费相关添加
void Shop::onMenuItemPaySuccess(void)
{
	isBuy = true;

	Global::getInstance()->getPayAwardByPayId(selectId);

	setIngotNum();

#ifdef						SHOP_CEIL_IS_MENU
	for(int i = 0; i < pages2->count(); i++)
	{
		((ShopCeilSpecail *)pages2->objectAtIndex(i))->updateNum();
	}
#else
	for(int i = 0; i < pages2->count(); i++)
	{
		((ShopCeil *)pages2->objectAtIndex(i))->updateNum();
	}
#endif

	selectCeil->updateNum();

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FINISH);

	TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_SHOP);
	_layer->doPromptByType(TEMP_PROMPT_BUY_SUCCESS);
	_layer->setPromptType2(1);
	Global::getInstance()->s->addLayerToRunningScene(_layer);
}


// 计费相关添加
void Shop::onMenuItemPayFailed(void)
{	
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FAILED);

	clearPropInformation();
}

void Shop::reBackBackClicked(bool _b)
{
	setBackGround(false);
	if(_b)
	{
		if (Global::getInstance()->getChallengeLevel() != 0)
		{
			LoadingLayer * _tmp;
			CCLayer * _tmp1;
			_tmp = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
			_tmp1 = Global::getInstance()->s->getMainLayer(_tmp);

			_tmp->setNextLayer(LAYER_ID_MAIN, _tmp1);
			_tmp->addLoadingLayer(0,_tmp1);


			Global::getInstance()->s->replaceScene(_tmp);
		}
		else
		{
			LoadingLayer * _tmp;
			CCLayer * _tmp1;
			_tmp = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
			_tmp1 = Global::getInstance()->s->getSimleGateMenu(_tmp);

			_tmp->setNextLayer(LAYER_ID_SMILE_GATE_SCENCE, _tmp1);
			_tmp->addLoadingLayer(0,_tmp1);


			Global::getInstance()->s->replaceScene(_tmp);
		}
	}
}

void Shop::onMenuItemBackClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	
	// 有loading
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);


		if (loadingLayer != NULL || forwardType == 0)
		{
			if (Global::getInstance()->getChallengeLevel() != 0)
			{
				PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_SHOP);
				setBackGround(true);
				//promptLayer->setForwardLayer(this);
				Global::getInstance()->s->addLayerToRunningScene(promptLayer);
				promptLayer->isChallengeShopBack();
			}
			else
			{
				PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_SHOP);
				setBackGround(true);
				//promptLayer->setForwardLayer(this);
				Global::getInstance()->s->addLayerToRunningScene(promptLayer);
				promptLayer->isBack();
			}
		}
		else
		{
			if (forwardType == LAYER_ID_GATE_PAUSE)
			{
				((PauseMenu *)forwardLayer)->reBackWithVisiable();
				//((PauseMenu *)forwardLayer)->reBack();
			} 
			else if (forwardType == LAYER_ID_MAIN)
			{
				((MainAppendLayer *)forwardLayer)->reBackWithVisiable();
				//((MainAppendLayer *)forwardLayer)->reBack();
			}
			else if (forwardType == LAYER_ID_BIG_GATE_MAP)
			{
				((BigGateMenu *)forwardLayer)->reBackWithVisiable();
				//((BigGateMenu *)forwardLayer)->setBackGround(false);
			}
			else if (forwardType == LAYER_ID_GAMEOVER)
			{
				((GameOverMenu *)forwardLayer)->reBackWithVisiable();
				//((GameOverMenu *)forwardLayer)->setBackGround(false);
			}
			else if (forwardType == LAYER_ID_CHALLENGE_COUNT)
			{
				((ChallengeCount *)forwardLayer)->reBackWithVisiable();
				//((ChallengeCount *)forwardLayer)->setBackGround(false);
			}
			else if (forwardType == LAYER_ID_CHALLENGE)
			{
				((SelectChallenge *)forwardLayer)->reBackWithVisiable();
				//((SelectChallenge *)forwardLayer)->reBack(0, false);
			}

			Global::getInstance()->s->removeLayerToRunningScene(this);
		}
}

void Shop::clearPropInformation(void)
{
	setBackGround(false);

#ifdef							SHOP_CEIL_IS_MENU
	for (int i = 0; i < pages1->count(); i++)
	{
		((ShopCeilSpecail *)pages1->objectAtIndex(i))->setTouchEnabled(true);
	}
	for (int i = 0; i < pages2->count(); i++)
	{
		((ShopCeilSpecail *)pages2->objectAtIndex(i))->setTouchEnabled(true);
	}
	myItemIsCanTouched = true;
#else
	for (int i = 0; i < pages1->count(); i++)
	{
		((ShopCeil *)pages1->objectAtIndex(i))->setTouchEnabled(true);
	}
	for (int i = 0; i < pages2->count(); i++)
	{
		((ShopCeil *)pages2->objectAtIndex(i))->setTouchEnabled(true);
	}
	myItemIsCanTouched = true;
#endif

	selectId = -1;
	selectCeil = NULL;
}

void Shop::setPropInformation(int _id, ShopCeilBase * _ceil, bool _isPay)
{
	if (isBackGround)
	{
		return;
	}

	selectId = _id;
	selectCeil = _ceil;

#ifdef								SHOP_CEIL_IS_MENU
	for (int i = 0; i < pages1->count(); i++)
	{
		((ShopCeilSpecail *)pages1->objectAtIndex(i))->setTouchEnabled(false);
	}
	for (int i = 0; i < pages2->count(); i++)
	{
		((ShopCeilSpecail *)pages2->objectAtIndex(i))->setTouchEnabled(false);
	}
	myItemIsCanTouched = false;
#else
	for (int i = 0; i < pages1->count(); i++)
	{
		((ShopCeil *)pages1->objectAtIndex(i))->setTouchEnabled(false);
	}
	for (int i = 0; i < pages2->count(); i++)
	{
		((ShopCeil *)pages2->objectAtIndex(i))->setTouchEnabled(false);
	}
	myItemIsCanTouched = false;
#endif

	if (!_isPay)
	{
		if(propName != NULL)
		{
			getChildByTag(4)->getChildByTag(1)->removeChild(propName);
			getChildByTag(4)->getChildByTag(2)->removeChild(propIntroduce);
			getChildByTag(4)->getChildByTag(3)->removeChild(propPrice);
			getChildByTag(4)->getChildByTag(4)->removeChild(propBuyNum);
			getChildByTag(4)->getChildByTag(5)->removeChild(propIngotNum);
			propName = NULL;
			propIntroduce = NULL;
			propPrice = NULL;
			propIngotNum = NULL;
			propBuyNum = NULL;
		}


		char _s[32];
		propControl = new Prop();
		switch(_id)
		{
		case PROP_TYPE_MOONLIGHT:
			propName = CCSprite::create("xuanren/sl1.png");
			propIntroduce = CCSprite::create("xuanren/sl2.png");
			sprintf(_s, "%d",propControl->getPrice(_id));
			propPrice = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
			break;
		case PROP_TYPE_GRENADE:
			propName = CCSprite::create("xuanren/zhadan.png");
			propIntroduce = CCSprite::create("xuanren/zd1.png");
			sprintf(_s, "%d",propControl->getPrice(_id));
			propPrice = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
			break;
		case PROP_TYPE_VIGOROUSLY_PILL:
			propName = CCSprite::create("xuanren/llys1.png");
			propIntroduce = CCSprite::create("xuanren/dlys2.png");
			sprintf(_s, "%d",propControl->getPrice(_id));
			propPrice = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
			break;
		case PROP_TYPE_ALIGNMENT:
			propName = CCSprite::create("xuanren/miaozhunjing2.png");
			propIntroduce = CCSprite::create("xuanren/miaozhunjing1.png");
			sprintf(_s, "%d",propControl->getPrice(_id));
			propPrice = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
			break;
		default:
			break;
		}
		propIngotNum = CCLabelAtlas::create(ingotNum->getString(), "shangcheng/shuzi.png", 15, 20, '0');
		propBuyNum = CCLabelAtlas::create(_ceil->getNum()->getString(), "shangcheng/shuzi.png", 15, 20, '0');
		getChildByTag(4)->getChildByTag(1)->addChild(propName);
		getChildByTag(4)->getChildByTag(2)->addChild(propIntroduce);
		getChildByTag(4)->getChildByTag(3)->addChild(propPrice);
		getChildByTag(4)->getChildByTag(4)->addChild(propBuyNum);
		getChildByTag(4)->getChildByTag(5)->addChild(propIngotNum);
		propBuyNum->setPosition(ccp(5,-8));
		propIngotNum->setPosition(ccp(-12,-8));
		propPrice->setPosition(ccp(-10,-10));
	}
}

void Shop::onMenuItemPlayClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	Player::getInstance()->setLastRoleSelect(Global::getInstance()->getSelectRoleId());

	if (isBuy)
	{
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_THING);
	}
	else
	{
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_NOTHING);
	}

	startTimeCount = 0;
	isBackGround = true;

	// 为了让小龙女说完声音 进行doAction判断
}

void Shop::onMenuItemPlusClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
}

void Shop::setIsDoaction(bool _b)
{
	isDoAction = _b;
#ifdef								SHOP_CEIL_IS_MENU
	if (myItemIsCanTouched)
	{
		for (int i = 0; i < pages1->count(); i++)
		{
			((ShopCeilSpecail *)pages1->objectAtIndex(i))->setTouchEnabled(!isDoAction);
		}
		for (int i = 0; i < pages2->count(); i++)
		{
			((ShopCeilSpecail *)pages2->objectAtIndex(i))->setTouchEnabled(!isDoAction);
		}
	}
#else
	if (myItemIsCanTouched)
	{
		for (int i = 0; i < pages1->count(); i++)
		{
			((ShopCeil *)pages1->objectAtIndex(i))->setTouchEnabled(!isDoAction);
		}
		for (int i = 0; i < pages2->count(); i++)
		{
			((ShopCeil *)pages2->objectAtIndex(i))->setTouchEnabled(!isDoAction);
		}
	}
#endif
}

void Shop::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"chuxian") == 0)
	{	
		mAnimationManager->runAnimationsForSequenceNamed("dong");
		setIsDoaction(false);
		//isCheck = false;

		if (Player::getInstance()->getOpenNewRole() && getChildByTag(2)->getChildByTag(998)->getChildByTag(3)->isVisible())
		{
			CCSprite * senticl = CCSprite::create("yindao/yuan.png");//youxi/baoshitantan.png");
			senticl->setScale(1.5);
			senticl->setPosition(ccp(686, 414));
			CCSprite * message = CCSprite::create("yindao/kaiqi3.png");
			message->setPosition(ccp(320, 410));
			CCSprite * diretion = CCSprite::create("xiaoguan/xiangyou1.png");
			diretion->setPosition(ccp(565, 410));
			spotLighLayer = new SpotLightLayer(senticl, message, diretion);
			setPropInformation(-1, NULL, true);
			isBackGround = true;
			isSpot = true;
			((SpotLightLayer *)spotLighLayer)->setStencilAction(CCScaleTo::create(0.5f, 0.3));
			((SpotLightLayer *)spotLighLayer)->setMessageAction(CCFadeIn::create(1.5f));
			((SpotLightLayer *)spotLighLayer)->setDirectionSpriteAction(CCFadeIn::create(1.5f));
			((SpotLightLayer *)spotLighLayer)->setActionFinishCallBackFunc(CCCallFunc::create(this, callfunc_selector(Shop::spotLighLayerCallBack)));
			Global::getInstance()->s->addLayerToRunningScene((SpotLightLayer *)spotLighLayer);
			((SpotLightLayer *)spotLighLayer)->startAction();
		}
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"dong") == 0)
	{
		mAnimationManager->runAnimationsForSequenceNamed("dong");
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"shouhui") == 0)
	{
		setBackGround(false);
		mAnimationManager->runAnimationsForSequenceNamed("dong");
		setIsDoaction(false);//isDoAction = false;
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"tanchu") == 0)
	{
		setIsDoaction(false);//isDoAction = false;
	}
}

void Shop::spotLighLayerCallBack(void)
{
	Global::getInstance()->s->removeLayerToRunningScene((SpotLightLayer *)spotLighLayer);
	isBackGround = false;
	isSpot = false;
	clearPropInformation();
}

void Shop::reBack(int _type, bool _b)
{
	setBackGround(false);
	if (_type == LAYER_ID_ROLE)
	{
		for (int i = 0; i < pages1->count(); i++)
		{
#ifdef							SHOP_CEIL_IS_MENU
			((ShopCeilSpecail *)pages1->objectAtIndex(i))->updateNum();
#else
			((ShopCeil *)pages1->objectAtIndex(i))->updateNum();
#endif
		}
		clearPropInformation();
		((CCMenu *)getChildByTag(1)->getChildByTag(999))->setVisible(true);
		((CCMenu *)getChildByTag(2)->getChildByTag(998))->setVisible(true);
	}
}

void Shop::setIngotNum(void)
{
	if (ingotNum != NULL)
	{
		getChildByTag(1)->getChildByTag(10)->removeChild(ingotNum);
	}
	char _s[32];
	sprintf(_s, "%d",Player::getInstance()->getPropNum(PROP_TYPE_INGOT));
	ingotNum = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
	getChildByTag(1)->getChildByTag(10)->addChild(ingotNum, 998);
	ingotNum->setPosition(ccp(50, 7));
}

void Shop::setForwardLayer(cocos2d::CCLayer * _ccLayer, int _layerType)
{
	forwardLayer = _ccLayer;
	forwardType = _layerType;

	if (loadingLayer == NULL)
	{
		if (forwardType == 0)
		{
			setVisible(true);
			getChildByTag(2)->getChildByTag(998)->getChildByTag(3)->setVisible(true);
			getChildByTag(1)->getChildByTag(999)->getChildByTag(1)->setVisible(true);
		}
		else if (forwardType == LAYER_ID_GATE_PAUSE)
		{
			getChildByTag(2)->getChildByTag(998)->getChildByTag(3)->setVisible(false);
		} 
	}
	else
	{
		if (forwardType == LAYER_ID_CHALLENGE)
		{
			getChildByTag(2)->getChildByTag(998)->getChildByTag(88)->setVisible(false);
		}
	}
}

void Shop::doAction(float _f)
{
	if (startTimeCount < 0)
	{
	}
	else
	{
		startTimeCount += _f;
		if (startTimeCount > 1)
		{
			if (Global::getInstance()->getChallengeLevel() != 0)
			{
				//开始游戏没有loading的页面
				Global::getInstance()->s->replaceScene(Global::getInstance()->s->getChallengeLayer(Global::getInstance()->getNextChallengeGateId(), Global::getInstance()->getSelectRoleId(), NULL));
			}
			else
			{
				Player::getInstance()->setLastMapId(Global::getInstance()->getMapIdByGateId(Global::getInstance()->getSelectGateId()));
				// 播放漫画
				Global::getInstance()->setCartoonId(0);
				Global::getInstance()->setCartoonId(Global::getInstance()->getSelectGateId());

				// 开始游戏loading的页面
				if (Global::getInstance()->getCartoonId() != 0 && !Player::getInstance()->getCarttonIsPlay(Global::getInstance()->getCartoonId()))
				{
					if (Global::getInstance()->getCartoonId() == CARTOON_BAOXIANGGUO)
					{
						Global::getInstance()->s->replaceScene(Global::getInstance()->s->getCartoonLayer(CARTOON_START, NULL));
					}
					else
					{
						Global::getInstance()->s->replaceScene(Global::getInstance()->s->getCartoonLayer(Global::getInstance()->getCartoonId(), NULL));
					}
				}
				else
				{
					Global::getInstance()->s->replaceScene(Global::getInstance()->s->getGameLayer(Global::getInstance()->getSelectGateId(), Global::getInstance()->getSelectRoleId(), NULL));
				}
			}
		}
	}
}

cocos2d::CCMenu * Shop::getPageMenu(void)
{
	return pageMenu;
}

/****************************************************************************
按钮单元
*****************************************************************************/
ShopCeil::ShopCeil(int _type, int _id, Shop * _shop, bool _isPay)
{
	isPay = _isPay;
	shop = _shop;
	id = _id;
	nodeImage = CCNode::create();

	type = _type;

	setContentSize(* new CCSize(96, 107));

	recommend = CCSprite::create("shangcheng/tuijian.png");
	disCount = CCSprite::create("shangcheng/tejia.png");
	pMenuItem = CCMenuItemImage::create(
		"shangcheng/anniu1.png",
		"shangcheng/anniu2.png",
		"shangcheng/anniu1.png",
		this,
		menu_selector(ShopCeil::menuButtonCallback));

	isButtonTouchEnabled = true;
	if (isPay)
	{
		switch(_id)
		{
		case PAY_ID_BUDDAHA:
			image = CCSprite::create("shangcheng/jifei2.png");
			setIsDisCount(false);
			break;
		case PAY_ID_SUNWUKONG:
			image = CCSprite::create("shangcheng/jifei1.png");
			setIsRecommend(false);
			break;
		case PAY_ID_HULUWA:
			image = CCSprite::create("shangcheng/jifei5.png");
			setIsRecommend(false);
			break;
		case PAY_ID_MEET:
			image = CCSprite::create("shangcheng/jifei3.png");
			setIsDisCount(false);
			break;
		case PAY_ID_VALUE_PACKAGE:
			image = CCSprite::create("shangcheng/jifei3.png");
			setIsDisCount(false);
			break;
		case PAY_ID_GOLDEN_PACKAGE:
			image = CCSprite::create("shangcheng/jifei3.png");
			setIsDisCount(false);
			break;
		default:
			break;
		}
	}
	else
	{
		switch(_id)
		{
		case PROP_TYPE_MOONLIGHT:
			image = CCSprite::create("xuanren/sl.png");
			break;
		case PROP_TYPE_GRENADE:
			image = CCSprite::create("xuanren/zd.png");
			break;
		case PROP_TYPE_VIGOROUSLY_PILL:
			image = CCSprite::create("xuanren/llys.png");
			break;
		case PROP_TYPE_ALIGNMENT:
			image = CCSprite::create("xuanren/miaozhunjing.png");
			break;
		default:
			break;
		}
		setIsRecommend(false);
		setIsDisCount(false);
	}
	nodeImage->setContentSize(* new CCSize(96,107));
	addChild(nodeImage);
	shop->getPageMenu()->addChild(pMenuItem);
	nodeImage->addChild(image);
	nodeImage->addChild(disCount);
	nodeImage->addChild(recommend);
	disCount->setPosition(ccp(-20,20));
	recommend->setPosition(ccp(-20,20));

	ingotNum = NULL;
	updateNum();

	autorelease();
}

ShopCeil::~ShopCeil(void)
{

}

void ShopCeil::setTouchEnabled(bool _b)
{
	if (_b)
	{
		if (isButtonTouchEnabled)
		{
			CCLayer::setTouchEnabled(_b);
			pMenuItem->setEnabled(_b);
		}
	}
	else
	{
		CCLayer::setTouchEnabled(_b);
		pMenuItem->setEnabled(_b);
	}
}

cocos2d::CCMenuItem * ShopCeil::getMenuItem(void)
{
	return pMenuItem;
}

void ShopCeil::menuButtonCallback(CCObject* pSender)
{
	shop->setPropInformation(id, this, isPay);
	if (isPay)
	{
		shop->onMenuItemPayButtonClicked();
	}
	else
	{
		shop->onMenuItemButtonClicked();
	}
}

void ShopCeil::setIsRecommend(bool _b)
{
	recommend->setVisible(_b);
}

void ShopCeil::setIsDisCount(bool _b)
{
	disCount->setVisible(_b);
}

cocos2d::CCLabelAtlas * ShopCeil::getNum(void)
{
	return ingotNum;
}

void ShopCeil::updateNum(void)
{
	int _id = -1;

	if (isPay)
	{
		switch(id)
		{
		case PAY_ID_HULUWA:
			if (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_HULUWA))
			{
				setIsDisCount(false);
				isButtonTouchEnabled = false;
			}
			break;
		case PAY_ID_SUNWUKONG:
			if (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_SUNWUKONG))
			{
				setIsDisCount(false);
				isButtonTouchEnabled = false;
			}
			break;
		case PAY_ID_BUDDAHA:
			_id = Player::getInstance()->getPropNum(PROP_TYPE_BUDDAHA);
			break;
		case PAY_ID_MEET:
			_id = Player::getInstance()->getPropNum(PROP_TYPE_MEET);
			break;
		case PAY_ID_VALUE_PACKAGE:
			break;
		case PAY_ID_GOLDEN_PACKAGE:
			break;
		default:
			break;
		}

		if (!isButtonTouchEnabled)
		{
			recommend->setColor(myGrey);
			disCount->setColor(myGrey);
			image->setColor(myGrey);
			//pMenu->setColor(myGrey);
			isButtonTouchEnabled = true;
			//setTouchEnabled(false);
		}
	}
	else
	{
		if (ingotNum != NULL)
		{
			nodeImage->removeChild(ingotNum);
		}

		_id = Player::getInstance()->getPropNum(id);
		if (_id > 99)
		{
			_id = 99;
		}

		char _s[32];
		sprintf(_s, "%d",_id);
		ingotNum = CCLabelAtlas::create(_s, "shangcheng/shuzi.png", 15, 20, '0');
		nodeImage->addChild(ingotNum);
		if (Player::getInstance()->getPropNum(id) > 9)
		{
			ingotNum->setPosition(ccp(11, -38));
		}
		else
		{
			ingotNum->setPosition(ccp(20, -38));
		}
	}
}

int ShopCeil::getId(void)
{
	return id;
}

bool ShopCeil::getIsPay(void)
{
	return isPay;
}

void ShopCeil::setImageAndPriceById(int _id)
{

}

/****************************************************************************
单元
*****************************************************************************/
ShopCeilSpecail::ShopCeilSpecail(int _type, int _id, Shop * _shop, bool _isPay)
{
	isPay = _isPay;
	shop = _shop;
	id = _id;
	nodeImage = CCNode::create();
	nodeImage->setContentSize(* new CCSize(96,107));
	addChild(nodeImage);

	type = _type;

	//setContentSize(* new CCSize(96, 107));

	recommend = CCSprite::create("shangcheng/tuijian.png");
	disCount = CCSprite::create("shangcheng/tejia.png");
	CCMenuItemImage *pButtonItem = CCMenuItemImage::create(
		"shangcheng/anniu1.png",
		"shangcheng/anniu2.png",
		this,
		menu_selector(ShopCeilSpecail::menuButtonCallback));
	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pButtonItem, NULL);
	
	isButtonTouchEnabled = true;
	if (isPay)
	{
		switch(_id)
		{
		case PAY_ID_BUDDAHA:
			image = CCSprite::create("shangcheng/jifei2.png");
			setIsDisCount(false);
			break;
		case PAY_ID_SUNWUKONG:
			image = CCSprite::create("shangcheng/jifei1.png");
			setIsRecommend(false);
			break;
		case PAY_ID_HULUWA:
			image = CCSprite::create("shangcheng/jifei5.png");
			setIsRecommend(false);
			break;
		case PAY_ID_MEET:
			image = CCSprite::create("shangcheng/jifei3.png");
			setIsDisCount(false);
			break;
		case PAY_ID_VALUE_PACKAGE:
			image = CCSprite::create("shangcheng/jifei3.png");
			setIsDisCount(false);
			break;
		case PAY_ID_GOLDEN_PACKAGE:
			image = CCSprite::create("shangcheng/jifei3.png");
			setIsDisCount(false);
			break;
		default:
			break;
		}
	}
	else
	{
		switch(_id)
		{
		case PROP_TYPE_MOONLIGHT:
			image = CCSprite::create("xuanren/sl.png");
			break;
		case PROP_TYPE_GRENADE:
			image = CCSprite::create("xuanren/zd.png");
			break;
		case PROP_TYPE_VIGOROUSLY_PILL:
			image = CCSprite::create("xuanren/llys.png");
			break;
		case PROP_TYPE_ALIGNMENT:
			image = CCSprite::create("xuanren/miaozhunjing.png");
			break;
		default:
			break;
		}
		setIsRecommend(false);
		setIsDisCount(false);
	}
	//nodeImage->addChild(frame);pMenu
	pMenu->setPosition(nodeImage->getPosition());
	addChild(pMenu, -1);
	nodeImage->addChild(image);
	nodeImage->addChild(disCount);
	nodeImage->addChild(recommend);
	disCount->setPosition(ccp(-20,20));
	recommend->setPosition(ccp(-20,20));

	ingotNum = NULL;
	updateNum();

	autorelease();
}
	
ShopCeilSpecail::~ShopCeilSpecail(void)
{

}

void ShopCeilSpecail::setTouchEnabled(bool _b)
{
	if (_b)
	{
		if (isButtonTouchEnabled)
		{
			CCLayer::setTouchEnabled(_b);
			pMenu->setTouchEnabled(_b);
		}
	}
	else
	{
		CCLayer::setTouchEnabled(_b);
		pMenu->setTouchEnabled(_b);
	}
}

void ShopCeilSpecail::menuButtonCallback(CCObject* pSender)
{
	shop->setPropInformation(id, this, isPay);
	if (isPay)
	{
		shop->onMenuItemPayButtonClicked();
	}
	else
	{
		shop->onMenuItemButtonClicked();
	}
}

void ShopCeilSpecail::setIsRecommend(bool _b)
{
	recommend->setVisible(_b);
}
	
void ShopCeilSpecail::setIsDisCount(bool _b)
{
	disCount->setVisible(_b);
}

cocos2d::CCLabelAtlas * ShopCeilSpecail::getNum(void)
{
	return ingotNum;
}

void ShopCeilSpecail::updateNum(void)
{
	int _id = -1;

	if (isPay)
	{
		if (id == PAY_ID_HULUWA)
		{
			if (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_HULUWA))
			{
				setIsDisCount(false);
				isButtonTouchEnabled = false;
			}
		}
		else if (id == PAY_ID_SUNWUKONG)
		{
			if (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_SUNWUKONG))
			{
				setIsDisCount(false);
				isButtonTouchEnabled = false;
			}
		}

		if (!isButtonTouchEnabled)
		{
			recommend->setColor(myGrey);
			disCount->setColor(myGrey);
			image->setColor(myGrey);
			pMenu->setColor(myGrey);
			isButtonTouchEnabled = true;
			//setTouchEnabled(false);
		}
	}
	else
	{
		if (ingotNum != NULL)
		{
			nodeImage->removeChild(ingotNum);
		}

		_id = Player::getInstance()->getPropNum(id);
		if (_id > 99)
		{
			_id = 99;
		}

		char _s[32];
		sprintf(_s, "%d",_id);
		ingotNum = CCLabelAtlas::create(_s, "shangcheng/shuzi.png", 15, 20, '0');
		nodeImage->addChild(ingotNum);
		if (Player::getInstance()->getPropNum(id) > 9)
		{
			ingotNum->setPosition(ccp(11, -38));
		}
		else
		{
			ingotNum->setPosition(ccp(20, -38));
		}
	}
}

int ShopCeilSpecail::getId(void)
{
	return id;
}

bool ShopCeilSpecail::getIsPay(void)
{
	return isPay;
}

void ShopCeilSpecail::setImageAndPriceById(int _id)
{

}