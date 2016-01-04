#include "MainAppendLayer.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "GameControl.h"
#include "MainLayer.h"
#include "MyAboutLayer.h"
#include "HalpLayer.h"
#include "LoadingLayer.h"
#include "PetParkLayer.h"
#include "PromptLayer.h"
#include "SpotLightLayer.h"
#include "NetWork.h"
#include "GMJson.h"
#include "ChallengeOver.h"

USING_NS_CC;
USING_NS_CC_EXT;

static const ccColor4B myGrey4 = {0,0,0,200};

MainAppendLayer::MainAppendLayer(void)
	: mAnimationManager(NULL)
	,forward(NULL)
{
	isSpot = false;
	isBackGround = false;
	spotLighLayer = NULL;
	isDoAction = false;
	isDianJiContinues = false;
	grey = CCLayerColor::create(myGrey4);
	grey->retain();
	grey->setVisible(false);
	addChild(grey, LAYER_ORDER_CONTROL);
}

void MainAppendLayer::onEnter(void)
{
	CCLOG("MainAppendLayer::onEnter");
	CCLayer::onEnter();
	isSelectModel = false;
	isCanExit = true;
	setKeypadEnabled(true);
}

void MainAppendLayer::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);
	CCLayer::onExit();
}

MainAppendLayer::~MainAppendLayer(void)
{	
	if (spotLighLayer != NULL)
	{
		CC_SAFE_RELEASE_NULL(spotLighLayer);
	}
	CC_SAFE_RELEASE_NULL(forward);
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	CC_SAFE_RELEASE_NULL(grey);
	CCLOG("MainAppendLayer ~MainAppendLayer");
}

SEL_MenuHandler MainAppendLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnPlay", MainAppendLayer::onMenuItemPlayClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnSetup", MainAppendLayer::onMenuItemSetupClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnShop", MainAppendLayer::onMenuItemShopClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBattle", MainAppendLayer::onMenuItemBattleClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnStory", MainAppendLayer::onMenuItemStoryClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnHelp", MainAppendLayer::onMenuItemHelpClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnAbout", MainAppendLayer::onMenuItemAboutClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnMonster", MainAppendLayer::onMenuItemMonsterClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnMore", MainAppendLayer::onMenuItemMoreClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBack", MainAppendLayer::onMenuItemBackClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnOff", MainAppendLayer::onMenuItemOffClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnRank", MainAppendLayer::onMenuItemRankClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnMoreGame", MainAppendLayer::onMenuItemMoreGameClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnExit", MainAppendLayer::onMenuItemExitClicked);

	return NULL;
}

cocos2d::SEL_CallFuncN MainAppendLayer::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calJiXuFinish", MainAppendLayer::calJiXuFinish);
}

SEL_CCControlHandler MainAppendLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool MainAppendLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void MainAppendLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager, cocos2d::CCLayer * _ccLayer)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	forward = _ccLayer;
	forward->retain();
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(MainAppendLayer::doAnimationCompleted));
	mAnimationManager->runAnimationsForSequenceNamed("dianjijixu");
#ifndef								GOLDEN_MINER2_VIRSION_CHALLENGE
	getChildByTag(999)->getChildByTag(1)->setVisible(false);
#endif
#ifdef								GOLDEN_MINER_2_VERSION_REVIEW
	getChildByTag(999)->getChildByTag(2)->setVisible(false);
#endif
	setTouchEnabled(true);
	CC_SAFE_RETAIN(mAnimationManager);
}

void MainAppendLayer::onMenuItemPlayClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	if (isDoAction)
	{
		return;
	}

	isSelectModel = true;
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	((MainLayer *)forward)->setIsBackGround(true);
	mAnimationManager->runAnimationsForSequenceNamed("kaishitanchu");
}

void MainAppendLayer::onMenuItemSetupClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	if (isDoAction)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	setBackGround(true);
	Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getSettingMenu(this, LAYER_ID_MAIN));
}

void MainAppendLayer::onMenuItemShopClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	if (isDoAction)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	setBackGround(true);
	setVisible(true);
	((MainLayer *)forward)->setVisible(true);
	Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getShopLayer(NULL, this, LAYER_ID_MAIN));
}

void MainAppendLayer::onMenuItemBattleClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	if (isDoAction)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (Player::getInstance()->getChallengeIsOpen())
	{
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
	else
	{
		// 未开启挑战模式
		setBackGround(true);
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_MAIN_APPEND);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->challengeGateNotOpen();
	}
}

void MainAppendLayer::onMenuItemStoryClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	if (isDoAction)
	{
		return;
	}

#ifdef										GOLDEN_MINER_2_NEW_GUIDE
	if (Player::getInstance()->getGuideIsFrist())
	{
		LoadingLayer * p = NULL;
		CCLayer * p1 = NULL;
		p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
		p1 = Global::getInstance()->s->getGuideLayer(Player::getInstance()->getGuideLastIndex(), p);
		p->setNextLayer(LAYER_ID_GAMING, p1);
		((GameControl *)p1)->setLoadingLayer(p);

		//p->appendLoadingLayerNum(1);
		p->addLoadingLayer(0,p1);
		Global::getInstance()->s->replaceScene(p);
		return;
	}
#endif
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
	CCLayer * p1 = Global::getInstance()->s->getBigGateMenu(p);

	p->addLoadingLayer(0,p1);
	p->setNextLayer(LAYER_ID_BIG_GATE_MAP, p1);

	Global::getInstance()->s->replaceScene(p);
	
	//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getBigGateMenu());
}

void MainAppendLayer::onMenuItemHelpClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	if (isDoAction)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	setBackGround(true);
	Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getHalpLayer(this, LAYER_ID_MAIN));
}

void MainAppendLayer::onMenuItemAboutClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	if (isDoAction)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	setBackGround(true);
	Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getAboutLayer(this, LAYER_ID_MAIN));
}

void MainAppendLayer::onMenuItemMonsterClicked(cocos2d::CCObject * pSender)
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
	if (isDoAction)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
	CCLayer * p1 =	Global::getInstance()->s->getPetParkLayer(p);
	//((PetParkLayer *)p1)->setLoadingLayer(p);
	//p->appendLoadingLayerNum(1);
	p->addLoadingLayer(0,p1);
	p->setNextLayer(LAYER_ID_PETPARK, p1);

	Global::getInstance()->s->replaceScene(p);
	//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getPetParkLayer());
}

void MainAppendLayer::onMenuItemMoreClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	if (isDoAction)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	mAnimationManager->runAnimationsForSequenceNamed("dianjigengduo");
	isDoAction = true;
}

void MainAppendLayer::onMenuItemBackClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	if (isDoAction)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	mAnimationManager->runAnimationsForSequenceNamed("dianjishouhui");
	isDoAction = true;
}

void MainAppendLayer::onMenuItemOffClicked(cocos2d::CCObject * pSender)
{
	if (isDoAction)
	{
		return;
	}

	isSelectModel = false;
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	((MainLayer *)forward)->setIsBackGround(false);
	// 有问题 要解决  
	mAnimationManager->runAnimationsForSequenceNamed("tanchushouhui");
	isDoAction = true;
}

void MainAppendLayer::onMenuItemRankClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	if (isDoAction)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	setBackGround(true);

	NetWork::getInstance()->getChallengeDate(this, callfuncND_selector(MainAppendLayer::onGetChallengeDateCompleted));
}

void MainAppendLayer::onGetChallengeDateCompleted(cocos2d::CCNode *sender, void *data)
{
	CCHttpResponse *response = (CCHttpResponse*)data;

	if (!response || !response->isSucceed())
	{
		if (response == NULL)
		{
			CCLOG("response is NULL");
		}
		else
		{
			CCLog("response failed   filedcode = %d", response->getResponseCode());
			CCLog("error buffer: %s", response->getErrorBuffer());
		}

		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_MAIN_APPEND);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->notOpen();
		return;
	}

	// dump data
	std::vector<char> *buffer = response->getResponseData();
	//把vector转换成std::string
	std::string buf(buffer->begin(),buffer->end()); 
	//buf.c_str()把std::string转换成string;
	GMJson * _json = new GMJson();
	_json->getChallengeDate(buf);
	delete(_json);

	ChallengeOver * _layer = (ChallengeOver *)Global::getInstance()->s->getChallengeOverMenu(LAYER_ID_MAIN_APPEND, this);
	Global::getInstance()->s->addLayerToRunningScene(_layer);
}

void MainAppendLayer::onMenuItemMoreGameClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	if (isDoAction)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

#ifdef								GOLDEN_MINER_2_VERSION_PAY
#ifdef								GOLDEN_MINER2_VERSION_PAY_SELF
#else	
	PayService::getInstance()->getMoreGames();
#endif
#else
	setBackGround(true);
	PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_MAIN_APPEND);
	Global::getInstance()->s->addLayerToRunningScene(promptLayer);
	promptLayer->notOpen();
#endif
}

void MainAppendLayer::onMenuItemExitClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	keyBackClicked();
}

void MainAppendLayer::calJiXuFinish(CCNode* sender)
{
	mAnimationManager->runAnimationsForSequenceNamed("dianjijixu");
}

void MainAppendLayer::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"tanchushouhui") == 0)
	{
		mAnimationManager->runAnimationsForSequenceNamed("anniuchuxian");
		isDoAction = true;
		return;
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"anniuchuxian") == 0)
	{
		for(int i = PET_ELEMENT_XIAOZUANFENG; i < PET_ELEMENT_COUNT; i++)
		{
			if (Player::getInstance()->getPetBorn(i))
			{
				CCSprite * senticl = CCSprite::create("yindao/yuan.png");//youxi/baoshitantan.png");
				senticl->setScale(1.5);
				senticl->setPosition(ccp(706, 414));
				CCSprite * message = CCSprite::create("yindao/kaiqi4.png");
				message->setPosition(ccp(340, 410));
				CCSprite * diretion = CCSprite::create("xiaoguan/xiangyou1.png");
				diretion->setPosition(ccp(585, 410));
				spotLighLayer = new SpotLightLayer(senticl, message, diretion);
				spotLighLayer->retain();
				isBackGround = true;
				isSpot = true;
				((SpotLightLayer *)spotLighLayer)->setStencilAction(CCScaleTo::create(0.5f, 0.3));
				((SpotLightLayer *)spotLighLayer)->setMessageAction(CCFadeIn::create(1.5f));
				((SpotLightLayer *)spotLighLayer)->setDirectionSpriteAction(CCFadeIn::create(1.5f));
				((SpotLightLayer *)spotLighLayer)->setActionFinishCallBackFunc(CCCallFunc::create(this, callfunc_selector(MainAppendLayer::spotLighLayerCallBack)));
				Global::getInstance()->s->addLayerToRunningScene((SpotLightLayer *)spotLighLayer);
				((SpotLightLayer *)spotLighLayer)->startAction();
				break;
			}
		}
	}
	isDoAction = false;
}

void MainAppendLayer::spotLighLayerCallBack(void)
{
	Global::getInstance()->s->removeLayerToRunningScene((SpotLightLayer *)spotLighLayer);
	CC_SAFE_RELEASE_NULL(spotLighLayer);
	isBackGround = false;
	isSpot = false;
}

void MainAppendLayer::reBack(void)
{
	setBackGround(false);
}

void MainAppendLayer::reBackWithVisiable(void)
{
	setVisible(true);
	((MainLayer *)forward)->setVisible(true);
	setBackGround(false);
}

void MainAppendLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if (((MainLayer *)forward)->getIsCheckRegister() && !isDianJiContinues)
	{
		startSelf();
	}
}

void MainAppendLayer::startSelf(void)
{
	isDianJiContinues = true;
	mAnimationManager->runAnimationsForSequenceNamed("anniuchuxian");
	isDoAction = true;
}

void MainAppendLayer::doAction(float _f)
{
}

void MainAppendLayer::setBackGround(bool _b)
{
	isCanExit = !_b;
	isBackGround = _b;
	grey->setVisible(_b);
}

void MainAppendLayer::keyBackClicked(void)
{
	if (((MainLayer *)forward)->isExit)
	{
		return;
	}

	if (isSelectModel)
	{
		onMenuItemOffClicked(NULL);
	}
	else
	{
		if (isCanExit)
		{
			((MainLayer *)forward)->exitInit();
			//exit(0);
		}
	}
}