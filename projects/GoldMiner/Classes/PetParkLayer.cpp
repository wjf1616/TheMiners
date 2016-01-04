#include "PetParkLayer.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "PauseMenu.h"
#include "MainAppendLayer.h"
#include "Player.h"
#include "MainAppendLayer.h"
#include "DynamicTarget.h"
#include "LoadingLayer.h"
#include "Pet.h"
#include "PromptLayer.h"
#include "Player.h"
#include "CostLayer.h"
#include "TemporaryPromptLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define				PET_MOVING_SPEED_X					0.6
#define				PET_MOVING_SPEED_Y					0.8
#define				PET_MOVING_SPEED_CONTROL			10.0
#define				PET_STOP_TIMR_CONTROL				90

static const ccColor3B myGrey={60,60,60};
static const ccColor4B myGrey4 = {0,0,0,200};

PetParkLayer::PetParkLayer(void)
	: mAnimationManager(NULL)
{
	pets = NULL;
	cheerPet = NULL;
	currHeart = NULL;
	foodNum = NULL;
	meetNum = NULL;
	greyLayer = NULL;
	isBackGround = false;

	isCheckHideGateOpen = false;
	hideGateIndex = 0;
	hideGates[0] = 10;
	hideGates[1] = 11;
	hideGates[2] = 12;
	hideGates[3] = 28;
	hideGates[4] = 29;
	hideGates[5] = 30;
	hideGates[6] = 46;
	hideGates[7] = 47;
	hideGates[8] = 48;
	hideGates[9] = 64;
	hideGates[10] = 65;
	hideGates[11] = 66;
	hideGates[12] = 82;
	hideGates[13] = 83;
	hideGates[14] = 84;

	loadingLayer = NULL;
}

PetParkLayer::~PetParkLayer(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	CCObject * p = NULL;
	CCARRAY_FOREACH(pets, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	} 

	cs::ArmatureDataManager::sharedArmatureDataManager()->removeAll();
	cs::ArmatureDataManager::sharedArmatureDataManager()->purgeArmatureSystem();
	CCTextureCache::sharedTextureCache()->removeAllTextures();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();

	CCLOG("PetParkLayer : ~PetParkLayer");
}

void PetParkLayer::onEnter(void)
{

	CCLOG("PetParkLayer::onEnter");
	CCLayer::onEnter();
	setVisible(false);

	Player::getInstance()->getMusicControl()->playOtherBackGround();

	touchIndex = -1;
	currTouchIndex = -1;
	isTouch1 = false;
	isTouch2 = true;
	currTouchIndex = -1;
	Global::getInstance()->initCurrGameLayerLoadDynamicTarget();

	// 背景
	CCSprite * p = CCSprite::create("guaiwuwo/beijing.png");
	p->setAnchorPoint(ccp(0, 0));
	addChild(p, LAYER_ORDER_BACKGROUND);

	getChildByTag(999)->setZOrder(LAYER_ORDER_CONTROL);

	// 可活动空间
	quence = new cocos2d::CCRect(200,100, 400,200);
	DynamicTargetControl * control = NULL;

	// 道具显示
	setRiceNum(0);
	setMeetNum(0);

	// 显示宠物们
	//teach = CCSprite::create("guaiwuwo/meiri.png");
	//teach->setPosition(ccp(145,45));
	//teach->setVisible(false);
	//getChildByTag(999)->getChildByTag(4)->addChild(teach);
	//teached = CCSprite::create("guaiwuwo/yijiaoyu.png");
	//teached->setPosition(ccp(145,45));
	//teached->setVisible(false);
	//getChildByTag(999)->getChildByTag(4)->addChild(teached);
	PetManager * ppp = new PetManager();
	for (int i = PET_ELEMENT_XIAOZUANFENG; i < PET_ELEMENT_COUNT; i++)
	{
		if ((i == PET_ELEMENT_XIAOZUANFENG)
			|| (i == PET_ELEMENT_LINGLICHONG))
		{
			continue;
		}
		//if (Player::getInstance()->getPetHaving(i))
		//{
			if (pets == NULL)
			{
				// 初始化已经拥有的怪物
				pets = new cocos2d::CCArray();
			}
			pets->addObject(ppp->getPetByElementId(i));
			addChild((Pet *)pets->lastObject());
			((Pet *)pets->lastObject())->setPosition(ccp(quence->getMinX() -20 + 170*(pets->count()-1), (quence->getMidY())*5/4));

			if (Player::getInstance()->getSelectPet() == i)
			{
				cheerPet = (Pet *)pets->lastObject();
			}
		//}
	}

	// 界面设置
	initCurrSelectPet();

	getChildByTag(999)->setZOrder(LAYER_ORDER_CONTROL);
	getChildByTag(1)->setZOrder(LAYER_ORDER_CONTROL-1);
	getChildByTag(3)->setZOrder(LAYER_ORDER_CONTROL-1);

	setTouchEnabled(true);
	setKeypadEnabled(true);
	schedule( schedule_selector(PetParkLayer::doAction), 0);
}

void PetParkLayer::setBackGround(bool _b, int _type, bool _typeB)
{
	if (_b)
	{
		if (greyLayer == NULL)
		{
			greyLayer = CCLayerColor::create(myGrey4);
		}

		Global::getInstance()->s->addLayerToRunningScene(greyLayer);
	}
	else
	{
		if (greyLayer != NULL)
		{
			Global::getInstance()->s->removeLayerToRunningScene(greyLayer);
			greyLayer = NULL;
		}
	}
	isBackGround = _b;

	if (_typeB)
	{
		if (_type == 1)
		{
			if (cheerPet != NULL)
			{
				cheerPet->setIsCheer(false);
			}

			cheerPet = (Pet *)pets->objectAtIndex(currTouchIndex);
			cheerPet->setIsCheer(true);	
			getChildByTag(999)->getChildByTag(13)->setVisible(true);
			getChildByTag(999)->getChildByTag(8)->setVisible(false);
		}
		else if (_type == 2)
		{
			onMenuItemPlus2Clicked(NULL);
		}
	}
}

void PetParkLayer::onEnterTransitionDidFinish(void)
{
	CCLayer::onEnterTransitionDidFinish();

	if (loadingLayer != NULL)
	{
		((LoadingLayer *)loadingLayer)->appendFinishLayerNum(1);
	}
}

void PetParkLayer::startSelf(void)
{
	setVisible(true);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PetParkLayer::setLoadingLayer(cocos2d::CCLayer * _layer)
{
	loadingLayer = _layer;
}

void PetParkLayer::keyBackClicked(void)	
{
	onMenuItemBackClicked(NULL);
}

SEL_MenuHandler PetParkLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBack", PetParkLayer::onMenuItemBackClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnPlus1", PetParkLayer::onMenuItemPlus1Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnPlus2", PetParkLayer::onMenuItemPlus2Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnCheer", PetParkLayer::onMenuItemCheerClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnTeach", PetParkLayer::onMenuItemTeachClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnDevelop", PetParkLayer::onMenuItemDevelopClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnSpecial", PetParkLayer::onMenuItemMeatClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnCommon", PetParkLayer::onMenuItemRiceClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnQuit", PetParkLayer::onMenuItemQuitClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnHelp", PetParkLayer::onMenuItemHelpClicked);

	return NULL;
}

cocos2d::SEL_CallFuncN PetParkLayer::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calXiaoShiFinish", PetParkLayer::calXiaoShiFinish);
}

SEL_CCControlHandler PetParkLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool PetParkLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void PetParkLayer::reBackBackClicked(bool _b)
{
	setBackGround(false, 0, false);
	if(_b)
	{
		LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
		CCLayer * p1 = Global::getInstance()->s->getMainLayer(p);

		p->addLoadingLayer(0,p1);
		p->setNextLayer(LAYER_ID_MAIN, p1);

		Global::getInstance()->s->replaceScene(p);
	}
}

void PetParkLayer::onMenuItemBackClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_PETPARK);
	setBackGround(true, 0, false);
	//promptLayer->setForwardLayer(this);
	Global::getInstance()->s->addLayerToRunningScene(promptLayer);
	promptLayer->isBack();

	//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getMainLayer());
}

void PetParkLayer::onMenuItemPlus1Clicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	// 计费
}

void PetParkLayer::onMenuItemPlus2Clicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	// 计费
	setBackGround(true, 0, false);

	if(Player::getInstance()->getPropNum(PROP_TYPE_MEET) > 99998)
	{
		TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_PETPARK);
		_layer->doPromptByType(TEMP_PROMPT_FOOD_FULL);
		_layer->setPromptType2(0);
		Global::getInstance()->s->addLayerToRunningScene(_layer);
	}

#ifdef						GOLDEN_MINER_2_VERSION_PAY

#ifdef						GOLDEN_MINER2_VERSION_PAY_SELF
	CostLayer * _layer = (CostLayer *)Global::getInstance()->s->getCostLayer(this, LAYER_ID_PETPARK);
	_layer->costById(PAY_ID_MEET, CCCallFunc::create(this,callfunc_selector(PetParkLayer::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(PetParkLayer::onMenuItemPayFailed)));
	Global::getInstance()->s->addLayerToRunningScene(_layer);
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
	PayService::getInstance()->pay(PAY_ID_MEET, true,  CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
#endif
#endif
#else
	onMenuItemPaySuccess();
#endif

}

// 计费相关添加
void PetParkLayer::onMenuItemPaySuccess(void)
{

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FINISH);

	Global::getInstance()->getPayAwardByPayId(PAY_ID_MEET);
	setMeetNum(0);
	
	TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_PETPARK);
	_layer->doPromptByType(TEMP_PROMPT_BUY_SUCCESS);
	_layer->setPromptType2(0);
	Global::getInstance()->s->addLayerToRunningScene(_layer);
	//setBackGround(false, 0, false);
}


// 计费相关添加
void PetParkLayer::onMenuItemPayFailed(void)
{	
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FAILED);
	
	setBackGround(false, 0, false);
}

void PetParkLayer::onMenuItemCheerClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_PETPARK);
	setBackGround(true, 0, false);
	//promptLayer->setForwardLayer(this);
	Global::getInstance()->s->addLayerToRunningScene(promptLayer);
	promptLayer->isCheer();
}

void PetParkLayer::onMenuItemQuitClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	if (cheerPet != NULL)
	{
		cheerPet->setIsCheer(false);
		getChildByTag(999)->getChildByTag(13)->setVisible(false);
		getChildByTag(999)->getChildByTag(8)->setVisible(true);
	}
}

void PetParkLayer::onMenuItemHelpClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_PETPARK);
	setBackGround(true, 0, false);
	//promptLayer->setForwardLayer(this);
	Global::getInstance()->s->addLayerToRunningScene(promptLayer);
	promptLayer->petParkInformation();
}

void PetParkLayer::onMenuItemDevelopClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"dianji2") == 0)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	CCMenuItemImage * tmp = (CCMenuItemImage *)getChildByTag(999)->getChildByTag(7);
	CCTexture2D *pTexture;
	CCRect rect;

	if (Player::getInstance()->getPetTeach(((Pet *)pets->objectAtIndex(currTouchIndex))->getElementId()))
	{
		pTexture = CCTextureCache::sharedTextureCache()->addImage("guaiwuwo/jiao1.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			((CCSprite *)tmp->getNormalImage())->setTexture(pTexture);
			((CCSprite *)tmp->getNormalImage())->setTextureRect(rect);
		}
		pTexture = CCTextureCache::sharedTextureCache()->addImage("guaiwuwo/jiao2.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			((CCSprite *)tmp->getSelectedImage())->setTexture(pTexture);
			((CCSprite *)tmp->getSelectedImage())->setTextureRect(rect);
			((CCSprite *)tmp->getDisabledImage())->setTexture(pTexture);
			((CCSprite *)tmp->getDisabledImage())->setTextureRect(rect);
		}
	}
	else
	{
		pTexture = CCTextureCache::sharedTextureCache()->addImage("guaiwuwo/jiao3.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			((CCSprite *)tmp->getNormalImage())->setTexture(pTexture);
			((CCSprite *)tmp->getNormalImage())->setTextureRect(rect);
			((CCSprite *)tmp->getSelectedImage())->setTexture(pTexture);
			((CCSprite *)tmp->getSelectedImage())->setTextureRect(rect);
			((CCSprite *)tmp->getDisabledImage())->setTexture(pTexture);
			((CCSprite *)tmp->getDisabledImage())->setTextureRect(rect);
		}
	}
	getChildByTag(999)->getChildByTag(10)->setVisible(true);
	getChildByTag(999)->getChildByTag(11)->setVisible(true);

	mAnimationManager->runAnimationsForSequenceNamed("dianji2");
}

void PetParkLayer::onMenuItemTeachClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	// 教育
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (Player::getInstance()->getPetTeach(((Pet *)pets->objectAtIndex(currTouchIndex))->getElementId()))
	{
		if(Player::getInstance()->getPetHeart(((Pet *)pets->objectAtIndex(currTouchIndex))->getElementId()) != Global::getInstance()->getPetHeartFull(((Pet *)pets->objectAtIndex(currTouchIndex))->getElementId()))
		{
			Player::getInstance()->setPetTeach(((Pet *)pets->objectAtIndex(currTouchIndex))->getElementId(), false);
		
			CCMenuItemImage * tmp = (CCMenuItemImage *)getChildByTag(999)->getChildByTag(7);
			CCTexture2D *pTexture;
			CCRect rect;
			pTexture = CCTextureCache::sharedTextureCache()->addImage("guaiwuwo/jiao3.png");
			if (pTexture)
			{
				rect = CCRectZero;
				rect.size = pTexture->getContentSize();
				((CCSprite *)tmp->getNormalImage())->setTexture(pTexture);
				((CCSprite *)tmp->getNormalImage())->setTextureRect(rect);
				((CCSprite *)tmp->getSelectedImage())->setTexture(pTexture);
				((CCSprite *)tmp->getSelectedImage())->setTextureRect(rect);
				((CCSprite *)tmp->getDisabledImage())->setTexture(pTexture);
				((CCSprite *)tmp->getDisabledImage())->setTextureRect(rect);
			}
		
			if (((Pet *)pets->objectAtIndex(currTouchIndex))->addHeart(3, PET_APPEND_TYPE_TEACH))
			{
				mAnimationManager->runAnimationsForSequenceNamed("dianji3");
				//getChildByTag(999)->getChildByTag(9)->setVisible(false);
				//getChildByTag(999)->getChildByTag(7)->setVisible(false);
				//getChildByTag(999)->getChildByTag(10)->setVisible(false);
				//getChildByTag(999)->getChildByTag(11)->setVisible(false);
				getChildByTag(999)->getChildByTag(8)->setVisible(true);
			}
			setCurrHeart(((Pet *)pets->objectAtIndex(currTouchIndex))->getElementId());
		}
	}
}

void PetParkLayer::onMenuItemMeatClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (Player::getInstance()->getPropNum(PROP_TYPE_MEET) > 0)
	{
		if(Player::getInstance()->getPetHeart(((Pet *)pets->objectAtIndex(currTouchIndex))->getElementId()) != Global::getInstance()->getPetHeartFull(((Pet *)pets->objectAtIndex(currTouchIndex))->getElementId()))
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_MEET, -1);
			Player::getInstance()->savePropNum(PROP_TYPE_MEET,0);
			setMeetNum(0);
			//char _s[32];
			//sprintf(_s, "%d",Player::getInstance()->getPropNum(PROP_TYPE_FOOD));
			//removeChild(meetNum);
			//meetNum = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
			//getChildByTag(3)->addChild(meetNum);
			if (((Pet *)pets->objectAtIndex(currTouchIndex))->addHeart(3, PET_APPEND_TYPE_SPECIAL))
			{
				mAnimationManager->runAnimationsForSequenceNamed("dianji3");
				//getChildByTag(999)->getChildByTag(9)->setVisible(false);
				//getChildByTag(999)->getChildByTag(7)->setVisible(false);
				//getChildByTag(999)->getChildByTag(10)->setVisible(false);
				//getChildByTag(999)->getChildByTag(11)->setVisible(false);
				getChildByTag(999)->getChildByTag(8)->setVisible(true);
			}
			setCurrHeart(((Pet *)pets->objectAtIndex(currTouchIndex))->getElementId());
		}
	}		
	else
	{
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_PETPARK);
		setBackGround(true, 0, false);
		//promptLayer->setForwardLayer(this);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->specailFood();
	}
}

void PetParkLayer::onMenuItemRiceClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (Player::getInstance()->getPropNum(PROP_TYPE_FOOD) > 0)
	{
		if(Player::getInstance()->getPetHeart(((Pet *)pets->objectAtIndex(currTouchIndex))->getElementId()) != Global::getInstance()->getPetHeartFull(((Pet *)pets->objectAtIndex(currTouchIndex))->getElementId()))
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_FOOD, -1);
			Player::getInstance()->savePropNum(PROP_TYPE_FOOD,0);
			setRiceNum(0);
			//char _s[32];
			//sprintf(_s, "%d",Player::getInstance()->getPropNum(PROP_TYPE_FOOD));
			//removeChild(foodNum);
			//foodNum = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
			//getChildByTag(1)->addChild(foodNum);
			//foodNum->setPosition(ccp(100 - (13+_i*10), 10));
			if (((Pet *)pets->objectAtIndex(currTouchIndex))->addHeart(1, PET_APPEND_TYPE_NORMAL))
			{
				mAnimationManager->runAnimationsForSequenceNamed("dianji3");
				//getChildByTag(999)->getChildByTag(9)->setVisible(false);
				//getChildByTag(999)->getChildByTag(7)->setVisible(false);
				//getChildByTag(999)->getChildByTag(10)->setVisible(false);
				//getChildByTag(999)->getChildByTag(11)->setVisible(false);
				getChildByTag(999)->getChildByTag(8)->setVisible(true);
			}
			setCurrHeart(((Pet *)pets->objectAtIndex(currTouchIndex))->getElementId());
		}
	}	
	else
	{
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_PETPARK);
		setBackGround(true, 0, false);
		//promptLayer->setForwardLayer(this);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->specailFood();
	}
}

void PetParkLayer::setForwardLayer(cocos2d::CCLayer * _ccLayer, int _layerType)
{
	forwardLayer = _ccLayer;
	forwardType = _layerType;
}

void PetParkLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
#ifndef										GOLDEN_MINER_2_BUY_INGOT	
	getChildByTag(999)->getChildByTag(88)->setVisible(false);
#endif
	//mAnimationManager->runAnimationsForSequenceNamed("chuxian");
	//mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(PetParkLayer::doAnimationCompleted));
	CC_SAFE_RETAIN(mAnimationManager);
}

void PetParkLayer::calXiaoShiFinish(CCNode* sender)
{
	if (forwardType == LAYER_ID_MAIN)
	{
		((MainAppendLayer *)forwardLayer)->reBack();
	}

	Global::getInstance()->s->removeLayerToRunningScene(this);
}

void PetParkLayer::doAction(float _f)
{
	if (isBackGround)
	{
		return;
	}
	
	if (isCheckHideGateOpen)
	{
		if (hideGateIndex < 15)
		{
			checkHideGateOpen(hideGates[hideGateIndex++]);
		}
		else
		{
			hideGateIndex = 0;
			isCheckHideGateOpen = false;
		}
	}
	else
	{
		// 宠物移动
		if (pets != NULL)
		{
			//collideCheck(0);
			for(int i = 0; i < pets->count(); i++)
			{
				int res = ((Pet *)pets->objectAtIndex(i))->doAction(_f);
				if (res == 2)
				{
					isCheckHideGateOpen = true;
					hideGateIndex = 0;
				}
				else if (res == 1)
				{
					getChildByTag(999)->getChildByTag(13)->setVisible(false);
					getChildByTag(999)->getChildByTag(8)->setVisible(false);
					getChildByTag(999)->getChildByTag(9)->setVisible(true);
				}
			}
			//changeZOrder();
		}	
	}
}

void PetParkLayer::updateTeach(void)
{
	time_t  time1 = time(NULL);
	struct tm *tm;
	tm = localtime(&time1);
	int day = tm->tm_mday;
	day += tm->tm_mon * 100;
	day += tm->tm_year * 10000;

	if (day > Player::getInstance()->getPetDay())
	{
		// 更新时间  更新教育次数
		Player::getInstance()->setPetDay(day);
		for (int i = PET_ELEMENT_XIAOZUANFENG; i < PET_ELEMENT_COUNT; i++)
		{
			Player::getInstance()->setPetTeach(i, true);
		}
	}
}

void PetParkLayer::petMove(float _f, CCObject * p)
{
}

void PetParkLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	//此方法是cocos2d-x的标准操作，取touch集合第一个touch，将其位置转成opengl坐标，没办法，这些坐标太乱了，touch默认坐标是屏幕坐标，左上角为远点，cocos默认坐标是opengl坐标，左下角是原点。
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	m_touchBeginPos = touch->getLocation ();
	m_touchBeginPos = CCDirector::sharedDirector()->convertToGL( m_touchBeginPos );

	touchIndex = -1;
	isTouchTarget = false;
	for (int i = 0; i < pets->count(); i++)
	{
		if (((Pet *)pets->objectAtIndex(i))->isBeSelected())
		{
			continue;
		}

		Pet * tmp = ((Pet *)pets->objectAtIndex(i));
		CCRect * myButton = new CCRect(tmp->getPositionX() - tmp->getWidth()/2
			,tmp->getPositionY() - tmp->getHeight()/2
			,tmp->getWidth()
			,tmp->getHeight());

		if(Global::getInstance()->isInRect(myButton, m_touchBeginPos.x, 480 - m_touchBeginPos.y))
		{
			touchIndex = i;
			isTouchTarget = true;
			break;
		}
	}

	CCLOG("begin touchIndex=%d", touchIndex);

	m_touchMove = false;
}

void PetParkLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	m_touchMove = true;
}

void PetParkLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	m_touchEndPos = touch->getLocation ();
	m_touchEndPos = CCDirector::sharedDirector()->convertToGL( m_touchEndPos );
	if (isTouchTarget)
	{
		if(m_touchMove && (m_touchBeginPos.x - m_touchEndPos.x) > 50 && (m_touchEndPos.x - m_touchBeginPos.x) > 50)
		{
			CCLOG("end meijizhong");
		}
		else
		{
			if(touchIndex != -1)
			{
				Pet * tmp = ((Pet *)pets->objectAtIndex(touchIndex));
				CCRect * myButton = new CCRect(tmp->getPositionX() - tmp->getWidth()/2
					,tmp->getPositionY() - tmp->getHeight()/2
					,tmp->getWidth()
					,tmp->getHeight());
				if(Global::getInstance()->isInRect(myButton, m_touchEndPos.x, 480 - m_touchEndPos.y))
				{
					Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
					if (currTouchIndex != -1)
					{
						((Pet *)pets->objectAtIndex(currTouchIndex))->setBeSelected(false);
					}
					// 更新时间刷新可否能教育
					updateTeach();

					currTouchIndex = touchIndex;
					((Pet *)pets->objectAtIndex(currTouchIndex))->setBeSelected(true);
					if (((Pet *)pets->objectAtIndex(currTouchIndex))->getLifeStatus() == PET_LIFE_STATUS_EGG)
					{
						getChildByTag(999)->getChildByTag(13)->setVisible(false);
						getChildByTag(999)->getChildByTag(8)->setVisible(false);
						getChildByTag(999)->getChildByTag(9)->setVisible(false);
					}
					else if (((Pet *)pets->objectAtIndex(currTouchIndex))->getLifeStatus() == PET_LIFE_STATUS_BABY)
					{
						getChildByTag(999)->getChildByTag(13)->setVisible(false);
						getChildByTag(999)->getChildByTag(8)->setVisible(false);
						getChildByTag(999)->getChildByTag(9)->setVisible(true);
					}
					else
					{
						if (((Pet *)pets->objectAtIndex(currTouchIndex))->getIsCheer())
						{
							getChildByTag(999)->getChildByTag(13)->setVisible(true);
							getChildByTag(999)->getChildByTag(8)->setVisible(false);
							getChildByTag(999)->getChildByTag(9)->setVisible(false);
						}
						else
						{
							getChildByTag(999)->getChildByTag(13)->setVisible(false);
							getChildByTag(999)->getChildByTag(8)->setVisible(true);
							getChildByTag(999)->getChildByTag(9)->setVisible(false);
						}
					}


					mAnimationManager->runAnimationsForSequenceNamed("dianji");
					isTouch1 = true;
					isTouch2 = false;
					setCurrSelectPet(currTouchIndex);
					CCLOG("end chenggong");
				}
				else
				{
					CCLOG("end meizhong2");
				}
			}
		}
	}
	else
	{
		CCLOG("end waimian");
		if (!isTouch2)
		{
			for (int i = 0; i < pets->count(); i++)
			{
				Pet * tmp = ((Pet *)pets->objectAtIndex(i));
				CCRect * myButton = new CCRect(tmp->getPositionX() - tmp->getWidth()/2
					,tmp->getPositionY() - tmp->getHeight()/2
					,tmp->getWidth()
					,tmp->getHeight());
				if(Global::getInstance()->isInRect(myButton, m_touchBeginPos.x, 480 - m_touchBeginPos.y))
				{
					touchIndex = i;
					isTouchTarget = true;
					break;
				}
			}
			if (!isTouchTarget)
			{
				//((Pet *)pets->objectAtIndex(currTouchIndex))->setBeSelected(false);
				//mAnimationManager->runAnimationsForSequenceNamed("dianji2");
				isTouch2 = true;
				isTouch1 = false;
			}
		}
	}
	m_touchMove = false;
}

void PetParkLayer::initCurrSelectPet(void)
{
	aiXin = CCSprite::create("guaiwuwo/aixin.png");
	aiXin->setPosition(ccp(getChildByTag(2)->getPositionX() - 0,getChildByTag(2)->getPositionY() + 0));
	getChildByTag(2)->addChild(aiXin);
	xieXian = CCSprite::create("guaiwuwo/xiexian.png");
	xieXian->setPosition(ccp(getChildByTag(2)->getPositionX() - 0,getChildByTag(2)->getPositionY() + 0));
	getChildByTag(2)->addChild(xieXian);
	shuXing = CCSprite::create("guaiwuwo/shuxing.png");
	shuXing->setPosition(ccp(getChildByTag(2)->getPositionX() + 0,getChildByTag(2)->getPositionY() + 0));
	getChildByTag(2)->addChild(shuXing);
	int num;
	int i = 0;
	currhand = CCSprite::create("guaiwuwo/jingxi.png");
	getChildByTag(2)->addChild(currhand);
	currName = CCSprite::create("guaiwuwo/jingxi1.png");
	getChildByTag(2)->addChild(currName);
	currAdd = CCSprite::create("guaiwuwo/zhuagou.png");
	getChildByTag(2)->addChild(currAdd);
	num = Player::getInstance()->getPetHeart(PET_ELEMENT_JINGXIGUI);		
	setCurrHeart(PET_ELEMENT_JINGXIGUI);

	selectLight = CCSprite::create("guaiwuwo/guang.png");
	addChild(selectLight, LAYER_ORDER_CONTROL-2);
	selectLight->setVisible(false);
	
	char _s[32];
	//sprintf(_s, "%d",num);
	//currHeart = CCLabelAtlas::create(_s, "guaiwuwo/aixinshuzi.png", 15, 19, '0');
	//i = 0;
	//while(1)
	//{
	//	num = num / 10;
	//	if (num > 0)
	//	{
	//		i++;
	//	}
	//	else
	//	{
	//		break;
	//	}
	//}
	//currHeart->setPosition(ccp(getChildByTag(2)->getPositionX() - 50 -(13+i*10), getChildByTag(2)->getPositionY() + 110));
	//getChildByTag(2)->addChild(currHeart);
	num = Global::getInstance()->getPetHeartFull(PET_ELEMENT_JINGXIGUI);		
	sprintf(_s, "%d",num);
	currHeartFull = CCLabelAtlas::create(_s, "guaiwuwo/aixinshuzi.png", 15, 19, '0');
	i = 0;
	while(1)
	{
		num = num / 10;
		if (num > 0)
		{
			i++;
		}
		else
		{
			break;
		}
	}
	currHeartFull->setPosition(ccp(getChildByTag(2)->getPositionX() -(13+i*10), getChildByTag(2)->getPositionY() + 110));
	getChildByTag(2)->addChild(currHeartFull);
}

void PetParkLayer::setCurrSelectPet(int _touchIndex)
{
	selectLight->setVisible(true);
	selectLight->setPosition(ccp(((Pet *)pets->objectAtIndex(_touchIndex))->getPositionX(), 480 - selectLight->getContentSize().height/2));

	getChildByTag(2)->removeChild(currhand);
	getChildByTag(2)->removeChild(currName);
	getChildByTag(2)->removeChild(currHeartFull);
	getChildByTag(2)->removeChild(currAdd);

	int type = ((Pet *)pets->objectAtIndex(_touchIndex))->getElementId();
	
	int num;
	int i = 0;
	switch(type)
	{
	case PET_ELEMENT_XIAOZUANFENG:
		currhand = CCSprite::create("guaiwuwo/");
		getChildByTag(2)->addChild(currhand);
		currName = CCSprite::create("");
		getChildByTag(2)->addChild(currName);
		currAdd = CCSprite::create("guaiwuwo/");
		getChildByTag(2)->addChild(currAdd);
		break;
	case PET_ELEMENT_JINGXIGUI:
		currhand = CCSprite::create("guaiwuwo/jingxi.png");
		getChildByTag(2)->addChild(currhand);
		currName = CCSprite::create("guaiwuwo/jingxi1.png");
		getChildByTag(2)->addChild(currName);
		currAdd = CCSprite::create("guaiwuwo/zhuagou.png");
		getChildByTag(2)->addChild(currAdd);
		break;
	case PET_ELEMENT_LINGLICHONG:
		currhand = CCSprite::create("guaiwuwo/");
		getChildByTag(2)->addChild(currhand);
		currName = CCSprite::create("");
		getChildByTag(2)->addChild(currName);
		currAdd = CCSprite::create("guaiwuwo/");
		getChildByTag(2)->addChild(currAdd);
		break;
	case PET_ELEMENT_LINGGANDAWANG:
		currhand = CCSprite::create("guaiwuwo/linggan.png");
		getChildByTag(2)->addChild(currhand);
		currName = CCSprite::create("guaiwuwo/linggan1.png");
		getChildByTag(2)->addChild(currName);
		currAdd = CCSprite::create("guaiwuwo/shangxia.png");
		getChildByTag(2)->addChild(currAdd);
		break;
	case PET_ELEMENT_YUMIANGONGZHU:
		currhand = CCSprite::create("guaiwuwo/yumian.png");
		getChildByTag(2)->addChild(currhand);
		currName = CCSprite::create("guaiwuwo/yumian1.png");
		getChildByTag(2)->addChild(currName);
		currAdd = CCSprite::create("guaiwuwo/huangjin.png");
		getChildByTag(2)->addChild(currAdd);
		break;
	case PET_ELEMENT_NIUMOWANG:
		currhand = CCSprite::create("guaiwuwo/niu.png");
		getChildByTag(2)->addChild(currhand);
		currName = CCSprite::create("guaiwuwo/niu1.png");
		getChildByTag(2)->addChild(currName);
		currAdd = CCSprite::create("guaiwuwo/baisu.png");
		getChildByTag(2)->addChild(currAdd);
		break;
	default:
		break;
	}
	aiXin->setPosition(ccp(getChildByTag(2)->getPositionX()- 160,getChildByTag(2)->getPositionY() + 100));
	xieXian->setPosition(ccp(getChildByTag(2)->getPositionX()- 95,getChildByTag(2)->getPositionY() + 100));
	shuXing->setPosition(ccp(getChildByTag(2)->getPositionX(),getChildByTag(2)->getPositionY() + 100));
	currhand->setPosition(ccp(getChildByTag(2)->getPositionX() - 361,getChildByTag(2)->getPositionY() + 120));
	currName->setPosition(ccp(getChildByTag(2)->getPositionX() - 252,getChildByTag(2)->getPositionY() + 100));
	currAdd->setPosition(ccp(getChildByTag(2)->getPositionX() + 150,getChildByTag(2)->getPositionY() + 100));

	setCurrHeart(type);

	num = Global::getInstance()->getPetHeartFull(type);	
	char _s[32];	
	sprintf(_s, "%d",num);
	currHeartFull = CCLabelAtlas::create(_s, "guaiwuwo/aixinshuzi.png", 15, 19, '0');
	i = 0;
	while(1)
	{
		num = num / 10;
		if (num > 0)
		{
			i++;
		}
		else
		{
			break;
		}
	}
	currHeartFull->setPosition(ccp(getChildByTag(2)->getPositionX() - 65 - (13+i*10), getChildByTag(2)->getPositionY() + 90));
	getChildByTag(2)->addChild(currHeartFull);
}

void PetParkLayer::setRiceNum(int _num)
{
	if (foodNum != NULL)
	{
		getChildByTag(1)->removeChild(foodNum);
	}

	char _s[32];
	int _i = 0;
	int num = Player::getInstance()->getPropNum(PROP_TYPE_FOOD);		
	sprintf(_s, "%d",num);
	_i = 0;
	while(1)
	{
		num = num / 10;
		if (num > 0)
		{
			_i++;
		}
		else
		{
			break;
		}
	}
	foodNum = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
	foodNum->setPosition(ccp(100 - (13+_i*10), 12));
	getChildByTag(1)->addChild(foodNum);
}

void PetParkLayer::setMeetNum(int _num)
{
	if (meetNum != NULL)
	{
		getChildByTag(3)->removeChild(meetNum);
	}

	char _s[32];
	int num = Player::getInstance()->getPropNum(PROP_TYPE_MEET);		
	sprintf(_s, "%d",num);
	int _i = 0;
	while(1)
	{
		num = num / 10;
		if (num > 0)
		{
			_i++;
		}
		else
		{
			break;
		}
	}
	meetNum = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
	meetNum->setPosition(ccp(100 - (13+_i*10), 10));
	getChildByTag(3)->addChild(meetNum);
}

void PetParkLayer::setCurrHeart(int _type)
{
	if (currHeart != NULL)
	{
		getChildByTag(2)->removeChild(currHeart);
	}
	
	int num;
	int i = 0;
	num = Player::getInstance()->getPetHeart(_type);		
	char _s[32];
	sprintf(_s, "%d",num);
	currHeart = CCLabelAtlas::create(_s, "guaiwuwo/aixinshuzi.png", 15, 19, '0');
	i = 0;
	while(1)
	{
		num = num / 10;
		if (num > 0)
		{
			i++;
		}
		else
		{
			break;
		}
	}
	getChildByTag(2)->addChild(currHeart);
	currHeart->setPosition(ccp(getChildByTag(2)->getPositionX() - 105 -(13+i*10), 30));
}

void PetParkLayer::checkHideGateOpen(int _gateId)
{
	// 还要关卡判断
	if(!Player::getInstance()->getGateOpenStatusByGateId(_gateId-1) || (Player::getInstance()->getGateLeverStatusByGateId(_gateId - 1)==0))
	{
		return;
	}

	CCArray * _petElements = CCArray::create();
	if (Global::getInstance()->getPetElementIdByHideGateId(_gateId, _petElements) != 0)
	{
		bool _flag = false;
		for (int i = 0; i < _petElements->count(); i++)
		{
			if (Player::getInstance()->getPetHeart(((CCInteger *)_petElements->objectAtIndex(i))->getValue()) < Global::getInstance()->getPetHeartFull(((CCInteger *)_petElements->objectAtIndex(i))->getValue()))
			{
				_flag = true;
			}
		}

		if (!_flag)
		{
			PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_PETPARK);
			setBackGround(true, 0, false);
			//promptLayer->setForwardLayer(this);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->addNewHideGate(_gateId);

			Player::getInstance()->setGateOpenStatusByGateId(_gateId, true);
		}
	}
}