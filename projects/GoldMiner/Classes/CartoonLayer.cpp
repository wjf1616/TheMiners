#include "CartoonLayer.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "LoadingLayer.h"
#include "Player.h"

USING_NS_CC;
USING_NS_CC_EXT;

CartoonLayer::CartoonLayer(void)
	: mAnimationManager(NULL)
	,nextLayerType(-1)
	,nextlayer(NULL)
	,loadingLayer(NULL)
{
	setVisible(false);
	jixu = NULL;
	bye = false;
}

void CartoonLayer::onEnterTransitionDidFinish(void)
{
	if (loadingLayer != NULL)
	{
		((LoadingLayer *)loadingLayer)->appendFinishLayerNum(1);
	}
	else
	{
		startSelf();
	}
}

void CartoonLayer::onExit()
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);
	CCLayer::onExit();
}


CartoonLayer::~CartoonLayer(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	CCLOG("CartoonLayer::~CartoonLayer");
}

SEL_MenuHandler CartoonLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler CartoonLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName)
{
	return NULL;
}

bool CartoonLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void CartoonLayer::setId(int _cartoonId)
{
	cartoonId = _cartoonId;
	setTouchEnabled(true);
}

void CartoonLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(CartoonLayer::doAnimationCompleted));

	//CCSprite * tmp = CCSprite::create("yindao/djjx1.png");
	//tmp->setVisible(false);
	//tmp->setPosition(ccp(700, 60));
	//addChild(tmp,1,10086);
	//tmp = CCSprite::create("yindao/djjx2.png");
	//tmp->setVisible(false);
	//tmp->setPosition(ccp(700, 60));
	//addChild(tmp,1,10087);
	CC_SAFE_RETAIN(mAnimationManager);
	timeCount = 0;
}

void CartoonLayer::setLoadingLayer(cocos2d::CCLayer * _layer)
{
	loadingLayer = _layer;
}

void CartoonLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if (jixu != NULL)
	//if (getChildByTag(10087)->isVisible() || getChildByTag(10086)->isVisible())
	{
		//// ÓÐloadingµÄÂß¼­
		//Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
		//if (cartoonId == CARTOON_END)
		//{
		//	LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
		//	CCLayer * p1 = Global::getInstance()->s->getMainLayer(p);

		//	p->addLoadingLayer(0,p1);
		//	p->setNextLayer(LAYER_ID_MAIN, p1);

		//	Global::getInstance()->s->replaceScene(p);

		//	//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getMainLayer());
		//}
		//else
		//{
		//	Global::getInstance()->s->removeLayerToRunningSceneAndSetNextLayer(this, nextLayerType, nextlayer);
		//}

		// Ã»ÓÐloadingµÄÂß¼­
		if (cartoonId == CARTOON_START)
		{
			Global::getInstance()->s->replaceScene(Global::getInstance()->s->getCartoonLayer(CARTOON_BAOXIANGGUO, NULL));
		}
		else if (cartoonId == CARTOON_END)
		{
			if (bye == NULL)
			{
				bye = CCSprite::create("youxi/weiwan.png");
				bye->setAnchorPoint(ccp(0, 0));
				addChild(bye, 1);
			}
			else
			{
				Player::getInstance()->setCarttonIsPlay(cartoonId, true);
				//LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
				//CCLayer * p1 = Global::getInstance()->s->getMainLayer(p);

				//p->addLoadingLayer(0,p1);
				//p->setNextLayer(LAYER_ID_MAIN, p1);

				//Global::getInstance()->s->replaceScene(p);
				Global::getInstance()->s->removeLayerToRunningScene(this);
				nextlayer->setVisible(true);
				Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getGameOverMenu(nextlayer, true));

				//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getMainLayer());

				//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getMainLayer());
			}
		}
		else
		{
			if (cartoonId == CARTOON_BAOXIANGGUO)
			{
				Player::getInstance()->setCarttonIsPlay(CARTOON_START, true);
			}
			Player::getInstance()->setCarttonIsPlay(cartoonId, true);
			Global::getInstance()->s->replaceScene(Global::getInstance()->s->getGameLayer(Global::getInstance()->getSelectGateId(), Global::getInstance()->getSelectRoleId(), NULL));
		}
	}
}

void CartoonLayer::doAnimationCompleted(void)
{
	if ((strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"cartoon1") == 0)
		|| (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"cartoon2") == 0)
		|| (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"cartoon3") == 0)
		|| (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"cartoon4") == 0)
		|| (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"cartoon5") == 0)
		|| (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"cartoon6") == 0)
		|| (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"cartoon7") == 0))
	{	
		jixu = CCSprite::create("manhua/dianjijixu.png");

		CCRepeatForever * forever;
		CCSequence * sequence;
		sequence = CCSequence::create(CCScaleTo::create(1.0f, 1.3),CCScaleTo::create(1.0f, 0.8),NULL);
		forever = CCRepeatForever::create(sequence);
		jixu->runAction(forever);
		jixu->setPosition(ccp(680, 80));
		addChild(jixu,2);
		//getChildByTag(10087)->setVisible(true);
		//getChildByTag(10086)->setVisible(false);
		//schedule(schedule_selector(CartoonLayer::doAction), 0);
	}
}

void CartoonLayer::doAction(float _f)
{
	timeCount += _f;
	if (timeCount > 0.3)
	{
		timeCount = 0;
		if (getChildByTag(10087)->isVisible())
		{
			getChildByTag(10087)->setVisible(false);
			getChildByTag(10086)->setVisible(true);
		}
		else
		{
			getChildByTag(10087)->setVisible(true);
			getChildByTag(10086)->setVisible(false);
		}
	}
}

void CartoonLayer::setNextLayer(int _type, cocos2d::CCLayer * _layer)
{
	nextLayerType = _type;
	nextlayer = _layer;
}

void CartoonLayer::startSelf(void)
{
	setVisible(true);
	// ²¥±³¾°ÒôÀÖ
	Player::getInstance()->getMusicControl()->playGameBackGround(Global::getInstance()->getMapIdByGateId(Global::getInstance()->getSelectGateId()));
	switch(cartoonId)
	{
	case CARTOON_START:
		mAnimationManager->runAnimationsForSequenceNamed("cartoon1");
		break;
	case CARTOON_BAOXIANGGUO:
		mAnimationManager->runAnimationsForSequenceNamed("cartoon2");
		break;
	case CARTOON_TONGYIANHE:
		mAnimationManager->runAnimationsForSequenceNamed("cartoon3");
		break;
	case CARTOON_NVERGUO:
		mAnimationManager->runAnimationsForSequenceNamed("cartoon4");
		break;
	case CARTOON_HUOYANSHAN:
		mAnimationManager->runAnimationsForSequenceNamed("cartoon5");
		break;
	case CARTOON_LINGSHAN:
		mAnimationManager->runAnimationsForSequenceNamed("cartoon6");
		break;
	case CARTOON_END:
		mAnimationManager->runAnimationsForSequenceNamed("cartoon7");
		break;
	default:
		break;
	}
}