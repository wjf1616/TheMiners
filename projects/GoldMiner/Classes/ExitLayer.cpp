#include "ExitLayer.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "PauseMenu.h"
#include "MainLayer.h"
#include "Player.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

ExitLayer::ExitLayer(void)
	: mAnimationManager(NULL)
{
	isExit = false;
	isAction = false;
}

ExitLayer::~ExitLayer(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);

	CCLOG("ExitLayer::~ExitLayer");
}

void ExitLayer::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

void ExitLayer::onEnter(void)
{
	CCLayer::onEnter();
}

void ExitLayer::keyBackClicked(void)	
{
	onMenuItemContinueClicked(NULL);
}

SEL_MenuHandler ExitLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnExit", ExitLayer::onMenuItemExitClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnContinue", ExitLayer::onMenuItemContinueClicked);

	return NULL;
}

SEL_CCControlHandler ExitLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool ExitLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void ExitLayer::setForwardLayer(cocos2d::CCLayer * _ccLayer)
{
	forwardLayer = _ccLayer;
	setKeypadEnabled(true);
}

void ExitLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
	isAction = true;
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(ExitLayer::doAnimationCompleted));
	CC_SAFE_RETAIN(mAnimationManager);
}

void ExitLayer::onMenuItemExitClicked(cocos2d::CCObject * pSender)
{
	if (isAction)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	mAnimationManager->runAnimationsForSequenceNamed("xiaoshi");
	isAction = true;
	isExit = true;
}

void ExitLayer::onMenuItemContinueClicked(cocos2d::CCObject * pSender)
{
	if (isAction)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	mAnimationManager->runAnimationsForSequenceNamed("xiaoshi");
	isAction = true;
	isExit = false;
}

void ExitLayer::doAnimationCompleted(void)
{
	isAction = false;
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"xiaoshi") == 0)
	{	
		if (isExit)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
			CCDirector::sharedDirector()->end();
			//exit(0);
		}
		else
		{
			Global::getInstance()->s->removeLayerToRunningScene(this);
			((MainLayer *)forwardLayer)->exitReBack(false);
		}
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"chuxian") == 0)
	{	
		setKeypadEnabled(true);
	}
}
