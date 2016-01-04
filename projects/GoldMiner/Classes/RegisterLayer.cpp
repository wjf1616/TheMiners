#include "RegisterLayer.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "PauseMenu.h"
#include "MainAppendLayer.h"
#include "Player.h"
#include "MyScrollView.h"
#include "MainLayer.h"
#include "TemporaryPromptLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define		HalpLayer_POINT_Y										90
#define		HalpLayer_POINT_X										18

#define		HALP_NUM												8

RegisterLayer::RegisterLayer(void)
	: mAnimationManager(NULL)
{
	isBackGround = false;
}

RegisterLayer::~RegisterLayer(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);// 动画管理器
	CCLOG("RegisterLayer : ~RegisterLayer");
}

void RegisterLayer::onEnter(void)
{
	CCLOG("RegisterLayer::onEnter");
	CCLayer::onEnter();
}

void RegisterLayer::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

SEL_MenuHandler RegisterLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnReceive", RegisterLayer::onMenuItemReceiveClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnKnow", RegisterLayer::onMenuItemKnowClicked);

	return NULL;
}

SEL_CCControlHandler RegisterLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool RegisterLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void RegisterLayer::setForwardLayer(cocos2d::CCLayer * _ccLayer)
{
	forwardLayer = _ccLayer;

	setKeypadEnabled(true);
}

void RegisterLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;

	time_t  time1 = time(NULL);
	struct tm *tm;
	tm = localtime(&time1);
	day = tm->tm_yday;
	day += tm->tm_year * 1000;
	int _day = Player::getInstance()->getRegisterDay();

	if ((day - _day) > 0)
	{
		registerCount = 1;

		// 不是初始化
		if (_day != 0)
		{
			if (_day/1000 == tm->tm_year)
			{// 同年 比较第几天
				if ((day - _day) == 1)
				{
					registerCount = Player::getInstance()->getRegisterCount() + 1;
					registerCount = registerCount % 8;
				}
			}
			else if(_day/1000 == (tm->tm_year-1))
			{// 过一年
				if (tm->tm_yday == 0)
				{// 新年第一天
					if (Global::getInstance()->isLeapYear(_day/1000))
					{// 去年闰年
						if (_day%1000 == 365)
						{
							registerCount = Player::getInstance()->getRegisterCount() + 1;
							registerCount = registerCount % 8;
						}
					}
					else
					{
						if (_day%1000 == 364)
						{
							registerCount = Player::getInstance()->getRegisterCount() + 1;
							registerCount = registerCount % 8;
						}
					}
				}
			}
		}

		initByCount(registerCount);
	}
	else
	{
		Global::getInstance()->s->removeLayerToRunningScene(this);
		((MainLayer *)forwardLayer)->registerReBack(false);
	}

	mAnimationManager->runAnimationsForSequenceNamed("cx");
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(RegisterLayer::doAnimationCompleted));
	CC_SAFE_RETAIN(mAnimationManager);
}

void RegisterLayer::initByCount(int _count)
{
	CCTexture2D *pTexture;
	CCRect rect;
	char _s[24];
	CCSprite * _tmp;
	for (int i = 1; i < _count; i++)
	{
		sprintf(_s, "denglujiangli/%d.png", i*3 + 6);
		pTexture = CCTextureCache::sharedTextureCache()->addImage(_s);
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			((CCSprite *)getChildByTag(1)->getChildByTag(i))->setTexture(pTexture);
			((CCSprite *)getChildByTag(1)->getChildByTag(i))->setTextureRect(rect);
		}
	}
	sprintf(_s, "denglujiangli/%d.png", _count*3+ 5);
	pTexture = CCTextureCache::sharedTextureCache()->addImage(_s);
	if (pTexture)
	{
		rect = CCRectZero;
		rect.size = pTexture->getContentSize();
		((CCSprite *)getChildByTag(1)->getChildByTag(_count))->setTexture(pTexture);
		((CCSprite *)getChildByTag(1)->getChildByTag(_count))->setTextureRect(rect);
	}
	sprintf(_s, "denglujiangli/%d.png", _count);
	_tmp = CCSprite::create(_s);
	getChildByTag(1)->getChildByTag(8)->addChild(_tmp,1);
	_tmp->setAnchorPoint(ccp(-0.1,-0.15));
	_tmp = CCSprite::create(_s);
	getChildByTag(2)->getChildByTag(1)->addChild(_tmp,1);
	_tmp->setAnchorPoint(ccp(-0.1,-0.15));
}

void RegisterLayer::getRegisterWard(int _count)
{
	isFull = false;
	switch(_count)
	{
	case 1:
		Player::getInstance()->appendPropNum(PROP_TYPE_INGOT, 100);
		Player::getInstance()->savePropNum(PROP_TYPE_INGOT, 100);
		break;
	case 2:
		Player::getInstance()->appendPropNum(PROP_TYPE_GRENADE, 3);
		if (Player::getInstance()->getPropNum(PROP_TYPE_GRENADE) > 98)
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_GRENADE, 99-Player::getInstance()->getPropNum(PROP_TYPE_GRENADE));
			isFull = true;
		}
		Player::getInstance()->savePropNum(PROP_TYPE_GRENADE, 3);
		break;
	case 3:
		Player::getInstance()->appendPropNum(PROP_TYPE_INGOT, 300);
		Player::getInstance()->savePropNum(PROP_TYPE_INGOT, 300);
		break;
	case 4:
		Player::getInstance()->appendPropNum(PROP_TYPE_VIGOROUSLY_PILL, 3);
		if (Player::getInstance()->getPropNum(PROP_TYPE_VIGOROUSLY_PILL) > 98)
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_VIGOROUSLY_PILL, 99-Player::getInstance()->getPropNum(PROP_TYPE_VIGOROUSLY_PILL));
			isFull = true;
		}
		Player::getInstance()->savePropNum(PROP_TYPE_VIGOROUSLY_PILL, 3);
		break;
	case 5:
		Player::getInstance()->appendPropNum(PROP_TYPE_INGOT, 500);
		Player::getInstance()->savePropNum(PROP_TYPE_INGOT, 500);
		break;
	case 6:
		Player::getInstance()->appendPropNum(PROP_TYPE_MOONLIGHT, 3);
		if (Player::getInstance()->getPropNum(PROP_TYPE_MOONLIGHT) > 98)
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_MOONLIGHT, 99-Player::getInstance()->getPropNum(PROP_TYPE_MOONLIGHT));
			isFull = true;
		}
		Player::getInstance()->savePropNum(PROP_TYPE_MOONLIGHT, 3);
		break;
	case 7:
		Player::getInstance()->appendPropNum(PROP_TYPE_INGOT, 1000);
		Player::getInstance()->savePropNum(PROP_TYPE_INGOT, 1000);
		break;
	default:
		break;
	}
}

void RegisterLayer::setBackGround(bool _b)
{
	isBackGround = _b;
}

void RegisterLayer::startSelf(void)
{
	mAnimationManager->runAnimationsForSequenceNamed("tanchu");
}

void RegisterLayer::onMenuItemKnowClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	if (isFull)
	{
		// 道具到达上限
		TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_REGISTER);
		_layer->doPromptByType(TEMP_PROMPT_PROP_FULL);
		Global::getInstance()->s->addLayerToRunningScene(_layer);
	}
	else
	{
		mAnimationManager->runAnimationsForSequenceNamed("xiaoshi1");
	}
}

void RegisterLayer::onMenuItemReceiveClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	

	Player::getInstance()->setRegisterDay(day);
	Player::getInstance()->setRegisterCount(registerCount);
	getRegisterWard(registerCount);
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	mAnimationManager->runAnimationsForSequenceNamed("xiaoshi");
}

void RegisterLayer::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"xiaoshi") == 0)
	{
		mAnimationManager->runAnimationsForSequenceNamed("tanchu1");
		// 转光
		CCSprite* sp1 = CCSprite::create("yindao/guang2.png");
		CCRotateBy* rot = CCRotateBy::create(2, 360);
		CCAction* forever = CCRepeatForever::create(rot);
		sp1->runAction(forever);           
		sp1->setPosition(ccp(400,240));   
		addChild(sp1, -1);
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"xiaoshi1") == 0)
	{
		Global::getInstance()->s->removeLayerToRunningScene(this);
		((MainLayer *)forwardLayer)->registerReBack(true);
	}
}

void RegisterLayer::tempPromptReBack(void)
{
	mAnimationManager->runAnimationsForSequenceNamed("xiaoshi1");
}

