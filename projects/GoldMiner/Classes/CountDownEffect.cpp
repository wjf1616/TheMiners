#include "CountDownEffect.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "GameControl.h"


USING_NS_CC;
USING_NS_CC_EXT;

CountDownEffect::CountDownEffect(void)
	:mAnimationManager(NULL)
	,target(NULL)
	,isCount(false)
{
}


CountDownEffect::~CountDownEffect(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	CC_SAFE_RELEASE_NULL(target);
	CC_SAFE_RELEASE_NULL(num);
	CC_SAFE_RELEASE_NULL(jifen);

	CCLOG("CountDownEffect::~CountDownEffect");
}

void CountDownEffect::onEnter(void)
{
	CCLayer::onEnter();
}

void CountDownEffect::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

SEL_MenuHandler CountDownEffect::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnShop", CountDownEffect::onMenuItemShopClicked);

	return NULL;
}

cocos2d::SEL_CallFuncN CountDownEffect::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{	
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calThree", CountDownEffect::calThree);
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calTwo", CountDownEffect::calTwo);
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calOne", CountDownEffect::calOne);
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calStart", CountDownEffect::calStart);
}

SEL_CCControlHandler CountDownEffect::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool CountDownEffect::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void CountDownEffect::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(CountDownEffect::doAnimationCompleted));
	isCount = true;
	CC_SAFE_RETAIN(mAnimationManager);
}

void CountDownEffect::calThree(CCNode* sender)
{
	//Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_TIME_START);
}

void CountDownEffect::calTwo(CCNode* sender)
{
	//Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_TIME_START);
}

void CountDownEffect::calOne(CCNode* sender)
{
	//Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_TIME_START);
}

void CountDownEffect::calStart(CCNode* sender)
{
	//Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_TIME_START);
}

void CountDownEffect::setForwardLayer(cocos2d::CCLayer *_ccLayer)
{
	forwardLayer = _ccLayer;

	target = CCSprite::create("yindao/huode.png");


	getChildByTag(2)->addChild(target);

	char _s[32];
	int _getCoinTmp = ((GameControl *)forwardLayer)->getLeastCoin();
	sprintf(_s, "%d",_getCoinTmp);

	num = CCLabelAtlas::create(_s, "yindao/shuzi.png", 21, 30, '0');
	getChildByTag(2)->addChild(num);
	jifen = CCSprite::create("yindao/jifen.png");
	getChildByTag(2)->addChild(jifen);

	target->retain();
	num->retain();
	jifen->retain();
}

void CountDownEffect::onMenuItemShopClicked(cocos2d::CCObject * pSender)
{
}

void CountDownEffect::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"daojishi") == 0)
	{	
		this->setVisible(false);
		((GameControl *)forwardLayer)->setBackGroundWithOutGreyLayer(false);
		Global::getInstance()->s->removeLayerToRunningScene(this);
	}
}

void CountDownEffect::doCountDownEffect(int _roleId)
{
	// 播放转   还有粒子特效
	mAnimationManager->runAnimationsForSequenceNamed("daojishi");
	count = 0;

	schedule( schedule_selector(CountDownEffect::doAction), 0);
}

void CountDownEffect::doAction(float _f)
{
	if (target != NULL)
	{
		float scale = getChildByTag(2)->getScale();
		unsigned char opacity = ((CCSprite *)getChildByTag(2))->getOpacity();
		target->setPosition(ccp(100*scale, 120*scale));
		target->setOpacity(opacity);
		int i = 0;
		int _getCoinTmp = ((GameControl *)forwardLayer)->getLeastCoin();
		while(1)
		{
			_getCoinTmp = _getCoinTmp / 10;
			if (_getCoinTmp > 0)
			{
				i++;
			}
			else
			{
				break;
			}
		}
		num->setPosition(ccp(190 -(21+i*10)*scale, 105*scale));
		num->setOpacity(opacity);
		jifen->setPosition(ccp(260*scale, 120*scale));
		jifen->setOpacity(opacity);
	}
	//if (isCount)
	//{
	//	count++;
	//	if (count == 24)//114)
	//	{
	//		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_TIME_START);
	//	}
	//	else if (count == 66)//156)
	//	{
	//		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_TIME_START);
	//	}
	//	else if (count == 106)//196)
	//	{
	//		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_TIME_START);
	//	}
	//	else if (count == 144)//234)
	//	{
	//		isCount = false;
	//		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_TIME_START);
	//	}
	//}
	
}
