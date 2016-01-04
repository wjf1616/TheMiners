#include "SlipGuide.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "GameControl.h"
#include "Player.h"
#include "BigGateMenu.h"
#include "SelectChallenge.h"
#include "SelectRoleAndPet.h"

USING_NS_CC;
USING_NS_CC_EXT;

SlipGuide::SlipGuide(void)
	: mAnimationManager(NULL)
{
	isLeft = 1;
}

SlipGuide::~SlipGuide(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);

	CCLOG("SlipGuide::~SlipGuide");
}

void SlipGuide::onEnter(void)
{
	CCLayer::onEnter();
}

void SlipGuide::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

SEL_MenuHandler SlipGuide::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
	return NULL;
}

SEL_CCControlHandler SlipGuide::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool SlipGuide::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void SlipGuide::setForwardLayer(cocos2d::CCLayer * _ccLayer, int _type)
{
	forwardLayer = _ccLayer;
	forwardType = _type;
}

void SlipGuide::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(SlipGuide::doAnimationCompleted));
	mAnimationManager->runAnimationsForSequenceNamed("xiangyou");
	CC_SAFE_RETAIN(mAnimationManager);
	setTouchEnabled(true);
}

void SlipGuide::doAnimationCompleted(void)
{
	if (isLeft == 2)
	{
		mAnimationManager->runAnimationsForSequenceNamed("xiangzuo");
	}
	else if (isLeft == 1)
	{
		mAnimationManager->runAnimationsForSequenceNamed("xiangyou");
	}
}

void SlipGuide::setIsLeft(int _i)
{
	if (isLeft == 1)
	{
		// 向右滑动
		if (forwardType == LAYER_ID_BIG_GATE_MAP)
		{
			((BigGateMenu *)forwardLayer)->setCurrPageIndex(false);
		}
		else if (forwardType == LAYER_ID_ROLE)
		{
			((SelectRoleAndPet *)forwardLayer)->setCurrRole(false);
		}
		else if (forwardType == LAYER_ID_CHALLENGE)
		{
			((SelectChallenge *)forwardLayer)->setCurrProp(false);
		}
	}
	else if (isLeft == 2)
	{
		// 向左滑动
		if (forwardType == LAYER_ID_BIG_GATE_MAP)
		{
			((BigGateMenu *)forwardLayer)->setCurrPageIndex(true);
		}
		else if (forwardType == LAYER_ID_ROLE)
		{
			((SelectRoleAndPet *)forwardLayer)->setCurrRole(true);
		}
		else if (forwardType == LAYER_ID_CHALLENGE)
		{
			((SelectChallenge *)forwardLayer)->setCurrProp(true);
		}
	}
	
	isLeft = _i;
	if (isLeft >= 3)
	{// 结束引导
		if (forwardType == LAYER_ID_BIG_GATE_MAP)
		{
			((BigGateMenu *)forwardLayer)->setBackGround(false);
			Player::getInstance()->setGuideSlipBigGate(false);
		}
		else if (forwardType == LAYER_ID_ROLE)
		{
			((SelectRoleAndPet *)forwardLayer)->reBack(0, false);
			Player::getInstance()->setGuideSlipRole(false);
		}
		else if (forwardType == LAYER_ID_CHALLENGE)
		{
			((SelectChallenge *)forwardLayer)->reBack(0, false);
			Player::getInstance()->setGuideSlipChallenge(false);
		}
		Global::getInstance()->s->removeLayerToRunningScene(this);
	}
}

void SlipGuide::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	m_touchEndPos = touch->getLocation ();
	m_touchEndPos = CCDirector::sharedDirector()->convertToGL( m_touchEndPos );
	if(m_touchMove)
	{
		//如果move了，那么看手指是否上下滑动超过50像素，这个纠正值得有，否则太灵敏了
		if ((m_touchBeginPos.x - m_touchEndPos.x) > 50)
		{
			if (isLeft == 2)
			{
				setIsLeft(isLeft+1);
			}
		}
		else if ((m_touchEndPos.x - m_touchBeginPos.x) > 50)
		{
			if (isLeft == 1)
			{
				setIsLeft(isLeft+1);
			}
		}
	}

	m_touchMove = false;
}

void SlipGuide::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	m_touchMove = true;
}

void SlipGuide::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{

	//此方法是cocos2d-x的标准操作，取touch集合第一个touch，将其位置转成opengl坐标，没办法，这些坐标太乱了，touch默认坐标是屏幕坐标，左上角为远点，cocos默认坐标是opengl坐标，左下角是原点。
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	m_touchBeginPos = touch->getLocation ();
	m_touchBeginPos = CCDirector::sharedDirector()->convertToGL( m_touchBeginPos );

	m_touchMove = false;
}