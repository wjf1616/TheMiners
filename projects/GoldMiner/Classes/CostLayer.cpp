#include "CostLayer.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "GameControl.h"
#include "MainAppendLayer.h"
#include "PetParkLayer.h"
#include "Shop.h"
#include "GameOverMenu.h"
#include "ChallengeCount.h"
#include "SelectChallenge.h"
#include "RoleInformation.h"
#include "SelectRoleAndPet.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define				HIDE_PETS_SCALE				0.6

CostLayer::CostLayer(void)
	:mAnimationManager(NULL)
	,forwardType(-1)
{
	isCostGenuine = false;
	isCost = false;
}


CostLayer::~CostLayer(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	CCLOG("CostLayer::~CostLayer");
}

void CostLayer::onEnter(void)
{
	CCLayer::onEnter();
}

void CostLayer::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);
	CCLayer::onExit();
}

SEL_MenuHandler CostLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnOpen", CostLayer::onMenuItemOpenClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBuy", CostLayer::onMenuItemBuyClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnOff", CostLayer::onMenuItemOffClicked);
	return NULL;
}

SEL_CCControlHandler CostLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool CostLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void CostLayer::onMenuItemOpenClicked(cocos2d::CCObject * pSender)
{
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	// 计费点（正版验证）
	isCost = true;
	mAnimationManager->runAnimationsForSequenceNamed("xiaoshi1");
}

void CostLayer::onMenuItemBuyClicked(cocos2d::CCObject * pSender)
{
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	// 计费点
	isCost = true;
	mAnimationManager->runAnimationsForSequenceNamed("xiaoshi2");
}

void CostLayer::onMenuItemOffClicked(cocos2d::CCObject * pSender)
{
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	isCost = false;
	if (isCostGenuine)
	{
		mAnimationManager->runAnimationsForSequenceNamed("xiaoshi1");
	}
	else
	{
		mAnimationManager->runAnimationsForSequenceNamed("xiaoshi2");
	}
}

void CostLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(CostLayer::doAnimationCompleted));

	CC_SAFE_RETAIN(mAnimationManager);
}

void CostLayer::costGenuine(int _index, CCCallFunc * _success, CCCallFunc * _false)
{
	assert(_success);
	assert(_false);

	paySuccess = _success;
	paySuccess->retain();
	payFailed = _false;
	payFailed->retain();

	isCostGenuine = true;
	getChildByTag(999)->getChildByTag(2)->setVisible(false);
	
	getChildByTag(1)->addChild(CCSprite::create("jifei/1.png"));

	mAnimationManager->runAnimationsForSequenceNamed("cx1");
}

void CostLayer::costById(int _costId, cocos2d::CCCallFunc * _success, cocos2d::CCCallFunc * _false)
{
	assert(_success);
	assert(_false);

	paySuccess = _success;
	paySuccess->retain();
	payFailed = _false;
	payFailed->retain();

	isCostGenuine = false;
	getChildByTag(999)->getChildByTag(1)->setVisible(false);

	switch(_costId)
	{
	case PAY_ID_TIMEMACHINE:
		getChildByTag(1)->addChild(CCSprite::create("jifei/2.png"));
		break;
	case PAY_ID_SUNWUKONG:
		getChildByTag(1)->addChild(CCSprite::create("jifei/3.png"));
		break;
	case PAY_ID_BUDDAHA:
		getChildByTag(1)->addChild(CCSprite::create("jifei/5.png"));
		break;
	case PAY_ID_HULUWA:
		getChildByTag(1)->addChild(CCSprite::create("jifei/6.png"));
		break;
	case PAY_ID_MEET:
		getChildByTag(1)->addChild(CCSprite::create("jifei/7.png"));
		break;
	case PAY_ID_JEWEL:
		getChildByTag(1)->addChild(CCSprite::create("jifei/7.png"));
		break;
	case PAY_ID_VALUE_PACKAGE:
		getChildByTag(1)->addChild(CCSprite::create("jifei/7.png"));
		break;
	case PAY_ID_GOLDEN_PACKAGE:
		getChildByTag(1)->addChild(CCSprite::create("jifei/7.png"));
		break;
	default:
		break;
	}

	mAnimationManager->runAnimationsForSequenceNamed("cx2");
}

void CostLayer::setForwardLayer(cocos2d::CCLayer *_ccLayer, int _type)
{
	forwardLayer = _ccLayer;
	forwardType = _type;
}

void CostLayer::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"xiaoshi1") == 0
		|| strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"xiaoshi2") == 0)
	{
		if (isCost)
		{
			paySuccess->execute();
		}
		else
		{
			payFailed->execute();
		}
		paySuccess->release();
		payFailed->release();
		paySuccess = NULL;
		payFailed = NULL;
		//switch(forwardType)
		//{
		//case LAYER_ID_GAMING:
		//	if (isCost)
		//	{
		//		((GameControl *)forwardLayer)->genuineSuccess();
		//	}
		//	else
		//	{
		//		((GameControl *)forwardLayer)->genuineFailed();
		//	}
		//	break;
		//case LAYER_ID_SHOP:
		//	if (isCost)
		//	{
		//		((Shop *)forwardLayer)->onMenuItemPaySuccess();
		//	}
		//	else
		//	{
		//		((Shop *)forwardLayer)->onMenuItemPayFailed();
		//	}
		//	break;
		//case LAYER_ID_PETPARK:
		//	if (isCost)
		//	{
		//		((PetParkLayer *)forwardLayer)->onMenuItemPaySuccess();
		//	}
		//	else
		//	{
		//		((PetParkLayer *)forwardLayer)->onMenuItemPayFailed();
		//	}
		//	break;
		//case LAYER_ID_GAMEOVER:
		//	((GameOverMenu *)forwardLayer)->setBackGround(false);
		//	break;
		//case LAYER_ID_CHALLENGE_COUNT:
		//	((ChallengeCount *)forwardLayer)->setBackGround(false);
		//	break;
		//case LAYER_ID_ROLE:
		//	if (isCost)
		//	{
		//		((SelectRoleAndPet *)forwardLayer)->onMenuItemPaySuccess();
		//	}
		//	else
		//	{
		//		((SelectRoleAndPet *)forwardLayer)->onMenuItemPayFailed();
		//	}
		//	break;
		//default:
		//	break;
		//}

		Global::getInstance()->s->removeLayerToRunningScene(this);
	}
}