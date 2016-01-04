#include "HalpLayer.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "PauseMenu.h"
#include "MainAppendLayer.h"
#include "Player.h"
#include "MyScrollView.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define		HalpLayer_POINT_Y										90
#define		HalpLayer_POINT_X										18

#define		HALP_NUM												8

HalpLayer::HalpLayer(void)
	: mAnimationManager(NULL)
{
	isDoAction = false;
}

HalpLayer::~HalpLayer(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);// 动画管理器

	cocos2d::CCObject * p = NULL;
	CCARRAY_FOREACH(helpsSprite, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(pointSprites, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CC_SAFE_RELEASE_NULL(pointIndexSprite);

	CCLOG("HalpLayer::~HalpLayer");
}

void HalpLayer::onEnter(void)
{
	helpsSprite = new cocos2d::CCArray();
	pointSprites = new cocos2d::CCArray();

	currIndex = 0;

	for (int i = 0; i < HALP_NUM; i++)
	{
		helpsSprite->addObject(getSpriteByIndex(i));
		((CCSprite *)helpsSprite->lastObject())->setVisible(false);
		getChildByTag(1)->addChild((CCSprite *)helpsSprite->lastObject(), LAYER_ORDER_CONTROL);
		((CCSprite *)helpsSprite->lastObject())->setPosition(ccp(-10,-20));
	}

	// 添加任务点点
	for (int i = 0; i < helpsSprite->count(); i++)
	{
		pointSprites->addObject(CCSprite::create("bangzhuguanyu/dian1.png"));
		((CCSprite *)pointSprites->lastObject())->setPosition(ccp(400 - helpsSprite->count()*HalpLayer_POINT_X/2 + i*HalpLayer_POINT_X + HalpLayer_POINT_X/2, HalpLayer_POINT_Y));
		addChild((CCSprite *)pointSprites->lastObject());
	}

	// 亮点点
	pointIndexSprite = CCSprite::create("bangzhuguanyu/dian2.png");
	pointIndexSprite->retain();
	addChild(pointIndexSprite,998);

	setInformation(currIndex);
	if (currIndex == 0)
	{
		getChildByTag(999)->getChildByTag(1)->setVisible(false);
	}
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
	isDoAction = true;
	CCLayer::onEnter();
}

void HalpLayer::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

void HalpLayer::keyBackClicked(void)	
{
	onMenuItemOffClicked(NULL);
}

SEL_MenuHandler HalpLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnOff", HalpLayer::onMenuItemOffClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnLeft", HalpLayer::onMenuItemLeftClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnRight", HalpLayer::onMenuItemRightClicked);

	return NULL;
}

cocos2d::SEL_CallFuncN HalpLayer::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calXiaoShiFinish", HalpLayer::calXiaoShiFinish);
}

SEL_CCControlHandler HalpLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool HalpLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void HalpLayer::PlayAnimation(int _id)
{
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
	isDoAction = true;
}

void HalpLayer::setForwardLayer(cocos2d::CCLayer * _ccLayer, int _layerType)
{
	forwardLayer = _ccLayer;
	forwardType = _layerType;

	setKeypadEnabled(true);
}

void HalpLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(HalpLayer::doAnimationCompleted));
	CC_SAFE_RETAIN(mAnimationManager);
}

void HalpLayer::onMenuItemOffClicked(cocos2d::CCObject * pSender)
{
	if (isDoAction)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	mAnimationManager->runAnimationsForSequenceNamed("xiaoshi");
	isDoAction = true;
}

void HalpLayer::onMenuItemLeftClicked(cocos2d::CCObject * pSender)
{
	if (isDoAction)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	((CCSprite *)helpsSprite->objectAtIndex(currIndex))->setVisible(false);
	currIndex--;
	if (currIndex == 0)
	{
		getChildByTag(999)->getChildByTag(1)->setVisible(false);
	}

	getChildByTag(999)->getChildByTag(2)->setVisible(true);

	setInformation(currIndex);
}

void HalpLayer::onMenuItemRightClicked(cocos2d::CCObject * pSender)
{
	if (isDoAction)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	((CCSprite *)helpsSprite->objectAtIndex(currIndex))->setVisible(false);
	currIndex++;
	if (currIndex == (HALP_NUM-1))
	{
		getChildByTag(999)->getChildByTag(2)->setVisible(false);
	}

	getChildByTag(999)->getChildByTag(1)->setVisible(true);
	
	setInformation(currIndex);
}

void HalpLayer::calXiaoShiFinish(CCNode* sender)
{
	if (forwardType == LAYER_ID_GATE_PAUSE)
	{
		((PauseMenu *)forwardLayer)->reBack();
	} 
	else if (forwardType == LAYER_ID_MAIN)
	{
		((MainAppendLayer *)forwardLayer)->reBack();
	}

	Global::getInstance()->s->removeLayerToRunningScene(this);
}

void HalpLayer::doAnimationCompleted(void)
{
	isDoAction = false;
}

cocos2d::CCSprite * HalpLayer::getSpriteByIndex(int _index)
{
	CCSprite * sprite = NULL;

	switch(_index)
	{
	case 0:
		sprite = CCSprite::create("bangzhuguanyu/8.png");
		break;
	case 1:
		sprite = CCSprite::create("bangzhuguanyu/1.png");
		break;
	case 2:
		sprite = CCSprite::create("bangzhuguanyu/2.png");
		break;
	case 3:
		sprite = CCSprite::create("bangzhuguanyu/3.png");
		break;
	case 4:
		sprite = CCSprite::create("bangzhuguanyu/4.png");
		break;
	case 5:
		sprite = CCSprite::create("bangzhuguanyu/5.png");
		break;
	case 6:
		sprite = CCSprite::create("bangzhuguanyu/6.png");
		break;
	case 7:
		sprite = CCSprite::create("bangzhuguanyu/7.png");
		break;
	default:
		break;
	}

	return sprite;
}

void HalpLayer::setInformation(int _index)
{
	((CCSprite *)helpsSprite->objectAtIndex(_index))->setVisible(true);
	pointIndexSprite->setPosition(((CCSprite *)pointSprites->objectAtIndex(_index))->getPosition());
}