#include "MyAboutLayer.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "PauseMenu.h"
#include "MainAppendLayer.h"
#include "Player.h"
#include "MainAppendLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

MyAboutLayer::MyAboutLayer(void)
	: mAnimationManager(NULL)
{
	isDoAction = false;
}

MyAboutLayer::~MyAboutLayer(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);

	CCLOG("MyAboutLayer::~MyAboutLayer");
}

void MyAboutLayer::onEnter(void)
{
	CCLayer::onEnter();
}

void MyAboutLayer::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

void MyAboutLayer::keyBackClicked(void)	
{
	onMenuItemOffClicked(NULL);
}

SEL_MenuHandler MyAboutLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnOff", MyAboutLayer::onMenuItemOffClicked);

	return NULL;
}

cocos2d::SEL_CallFuncN MyAboutLayer::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calXiaoShiFinish", MyAboutLayer::calXiaoShiFinish);
}

SEL_CCControlHandler MyAboutLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool MyAboutLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void MyAboutLayer::setForwardLayer(cocos2d::CCLayer * _ccLayer, int _layerType)
{
	forwardLayer = _ccLayer;
	forwardType = _layerType;
	setKeypadEnabled(true);
}

void MyAboutLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
	isDoAction = true;

#ifndef									GOLDEN_MINER_2_VERSION_REVIEW
	CCSprite * p = CCSprite::create("bangzhuguanyu/guanyu2.png");
	p->setPosition(ccp(0, -20));
	getChildByTag(1)->addChild(p);
#endif
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(MyAboutLayer::doAnimationCompleted));
	CC_SAFE_RETAIN(mAnimationManager);
}

void MyAboutLayer::onMenuItemOffClicked(cocos2d::CCObject * pSender)
{
	if (isDoAction)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	mAnimationManager->runAnimationsForSequenceNamed("xiaoshi");
	isDoAction = true;
}

void MyAboutLayer::calXiaoShiFinish(CCNode* sender)
{
	if (forwardType == LAYER_ID_MAIN)
	{
		((MainAppendLayer *)forwardLayer)->reBack();
	}

	Global::getInstance()->s->removeLayerToRunningScene(this);
}

void MyAboutLayer::doAnimationCompleted(void)
{
	isDoAction = false;
	//if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"xiaoshi") == 0)
	//{	
	//	Global::getInstance()->s->removeLayerToRunningScene(this);
	//	// 只有在退出的时候才存储到文件中去
	//	Player::getInstance()->saveMusic();
	//	if (forwardType == LAYER_ID_GATE_PAUSE)
	//	{
	//		((PauseMenu *)forwardLayer)->reBack();
	//	} 
	//	else if (forwardType == LAYER_ID_GATE_PAUSE)
	//	{
	//		((MainAppendLayer *)forwardLayer)->reBack();
	//	}
	//}
}
