#include "MainLayer.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "GameControl.h"
#include "Player.h"
#include "MainAppendLayer.h"
#include "LoadingLayer.h"
#include "RegisterLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

static const ccColor4B myGrey4 = {0,0,0,200};

MainLayer::MainLayer(void)
	: mAnimationManager(NULL)
	,greyLayer(NULL)
{
	isFrist = false;
	appendLayer = NULL;
	registerLayer = NULL;
	isExit = false;
}

void MainLayer::onEnter(void)
{
	CCLayer::onEnter();

	CCLOG("MainLayer::onEnter");
	setVisible(false);
	Player::getInstance()->getMusicControl()->playOtherBackGround();

	Global::getInstance()->setChallengeLevel(0);
	isInChuXian = false;
	setKeypadEnabled(true);
}

void MainLayer::onEnterTransitionDidFinish(void)
{
	((LoadingLayer *)loadingLayer)->appendFinishLayerNum(1);
}

void MainLayer::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

MainLayer::~MainLayer(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	CC_SAFE_RELEASE_NULL(greyLayer);
	CCLOG("MainLayer ~MainLayer");
}

SEL_MenuHandler MainLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;
}

//cocos2d::SEL_CallFuncN MainLayer::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
//{
//	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calChuXianFinish", MainLayer::calChuXianFinish);
//}

SEL_CCControlHandler MainLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;
}

bool MainLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void MainLayer::setIsFrist(bool _b)
{
	isFrist = _b;
	isCheckRegister = !isFrist;
	isCanTouch = false;
}

bool MainLayer::getIsCheckRegister(void)
{
	return isCheckRegister;
}

void MainLayer::startSelf(void)
{
	setVisible(true);
	if (isFrist)
	{
		mAnimationManager->runAnimationsForSequenceNamed("cx");
		CCLOG("cx");
		setTouchEnabled(true);
	}
	else
	{
		mAnimationManager->runAnimationsForSequenceNamed("cx3");
		CCLOG("cx3");
	}
}

cocos2d::CCLayer * MainLayer::getLoadingLayer(void)
{
	return loadingLayer;
}

void MainLayer::setLoadingLayer(cocos2d::CCLayer * _layer)
{
	loadingLayer = _layer;
}

//void MainLayer::calChuXianFinish(CCNode* sender)
//{
//	Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getMainAppendLayer(this));
//	isInChuXian = false;
//	mAnimationManager->runAnimationsForSequenceNamed("cx2");
//}

void MainLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	greyLayer = CCLayerColor::create(myGrey4);
	greyLayer->retain();
	greyLayer->setVisible(false);
	addChild(greyLayer);
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(MainLayer::doAnimationCompleted));
	//mAnimationManager->runAnimationsForSequenceNamed("cx");
	isInChuXian = true;
	//setTouchEnabled(true);
	CC_SAFE_RETAIN(mAnimationManager);

	//Player::getInstance()->getMusicControl()->playOtherBackGround();
}

void MainLayer::setIsBackGround(bool _isGrey)
{
	if (_isGrey)
	{
		greyLayer->setVisible(true);
	}
	else
	{
		greyLayer->setVisible(false);
	}	
}

void MainLayer::keyBackClicked(void)
{
	if (isExit)
	{
		return;
	}
	if (isInChuXian)
	{
		exitInit();
		//exit(0);
	}
}

void MainLayer::exitInit(void)
{
	if (registerLayer != NULL)
	{
		((RegisterLayer *)registerLayer)->setBackGround(true);
	}
	if (appendLayer != NULL)
	{
		((MainAppendLayer *)appendLayer)->setBackGround(true);
	}
	this->setTouchEnabled(false);
	isExit = true;

	Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getExitLayer(this));
}

void MainLayer::registerReBack(bool _b)
{
	if (_b)
	{
		registerLayer = NULL;
		((MainAppendLayer *)appendLayer)->startSelf();
		((MainAppendLayer *)appendLayer)->setVisible(true);
	}
	isCheckRegister = true;
	isExit = false;
}

void MainLayer::exitReBack(bool _b)
{
	if (registerLayer != NULL)
	{
		((RegisterLayer *)registerLayer)->setBackGround(false);
	}
	if (appendLayer != NULL)
	{
		((MainAppendLayer *)appendLayer)->setBackGround(false);
	}
	this->setTouchEnabled(true);
	isExit = false;
}

void MainLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if (isCanTouch && !isCheckRegister)
	{
		((MainAppendLayer *)appendLayer)->setVisible(false);
		((RegisterLayer *)registerLayer)->startSelf();
		isCanTouch = false;
	}
}

void MainLayer::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"cx2") == 0)
	{
#ifdef								GOLDEN_MINER_2_S
#else
		mAnimationManager->runAnimationsForSequenceNamed("cx2");
#endif
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"cx") == 0)
	{
		//CCLOG("finish cx");
		if (!isCheckRegister)
		{
			appendLayer = (MainAppendLayer *)Global::getInstance()->s->getMainAppendLayer(this);
			Global::getInstance()->s->addLayerToRunningScene(appendLayer);
			registerLayer = Global::getInstance()->s->getRegisterLayer(this);
			Global::getInstance()->s->addLayerToRunningScene(registerLayer);
#ifdef								GOLDEN_MINER_2_S
#else
			mAnimationManager->runAnimationsForSequenceNamed("cx2");
#endif
			isCanTouch = true;
		}
		else
		{
			appendLayer = (MainAppendLayer *)Global::getInstance()->s->getMainAppendLayer(this);
			Global::getInstance()->s->addLayerToRunningScene(appendLayer);
			//MainAppendLayer * _layer = (MainAppendLayer *)Global::getInstance()->s->getMainAppendLayer(this);
			//Global::getInstance()->s->addLayerToRunningScene(_layer);
#ifdef								GOLDEN_MINER_2_S
#else
			mAnimationManager->runAnimationsForSequenceNamed("cx2");
#endif
		}
		isInChuXian = false;
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"cx3") == 0)
	{
		//CCLOG("finish cx3");
		appendLayer = (MainAppendLayer *)Global::getInstance()->s->getMainAppendLayer(this);
		Global::getInstance()->s->addLayerToRunningScene(appendLayer);
		//MainAppendLayer * _layer = (MainAppendLayer *)Global::getInstance()->s->getMainAppendLayer(this);
		//Global::getInstance()->s->addLayerToRunningScene(_layer);
		((MainAppendLayer *)appendLayer)->startSelf();
		isInChuXian = false;
#ifdef								GOLDEN_MINER_2_S
#else
		mAnimationManager->runAnimationsForSequenceNamed("cx2");
#endif
	}
}