#include "Buddaha.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "GameControl.h"
#include "Player.h"

USING_NS_CC;
USING_NS_CC_EXT;

Buddaha::Buddaha(void)
	: mAnimationManager(NULL)
{
	isDoAction = false;
	timeCount = 0;
}

Buddaha::~Buddaha(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);

	CCObject * p;
	CCARRAY_FOREACH(zhuan, p)
	{
		CC_SAFE_RELEASE(p);
	}

	CCLOG("Buddaha::~Buddaha");
}

void Buddaha::onEnter(void)
{
	CCLayer::onEnter();
}

void Buddaha::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

SEL_MenuHandler Buddaha::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
	return NULL;
}

cocos2d::SEL_CallFuncN Buddaha::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "OnStart1", Buddaha::OnStart1);
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "OnStart2", Buddaha::OnStart2);
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "OnStart3", Buddaha::OnStart3);
}

SEL_CCControlHandler Buddaha::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool Buddaha::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void Buddaha::setForwardLayer(cocos2d::CCLayer * _ccLayer)
{
	forwardLayer = _ccLayer;
}

void Buddaha::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	zhuan = new cocos2d::CCArray();
	char _s[54];
	int tmp = ((GameControl *) forwardLayer)->getLeastCoin();
	int _num = 1;
	while (tmp > 0)
	{
		tmp = tmp /10;
		if (tmp > 0)
		{
			zhuan->addObject(makeZhuan(550 -_num*24, 415, 1, this));
			_num++;
		}
	}
	zhuan->addObject(makeZhuan(550-_num*24, 415, 1, this));
	isZhuan = false;

	sprintf(_s, "%d",((GameControl *) forwardLayer)->getLeastCoin());
	beforeTarget = CCLabelAtlas::create(_s, "texiao/foguang/shuzi.png", 24, 37, '0');
	beforeTarget->setPosition(550-_num*24, 415);
	addChild(beforeTarget, 1);
	sprintf(_s, "%d",((GameControl *) forwardLayer)->getLeastCoin()/2);
	afterTarget = CCLabelAtlas::create(_s, "texiao/foguang/shuzi.png", 24, 37, '0');
	afterTarget->setPosition(550-_num*24, 415);
	afterTarget->setVisible(false);
	addChild(afterTarget, 1);


	mAnimationManager->runAnimationsForSequenceNamed("cx");
	isDoAction = true;
	
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(Buddaha::doAnimationCompleted));
	CC_SAFE_RETAIN(mAnimationManager);
	schedule( schedule_selector(Buddaha::doAction), 0);
}

void Buddaha::OnStart1(CCNode* sender)
{
	beforeTarget->setVisible(false);
	setZhuanIsDoing(true);
}

void Buddaha::OnStart2(CCNode* sender)
{
	setZhuanIsDoing(false);
	afterTarget->setVisible(true);
	((GameControl *)forwardLayer)->setLeastCoin(((GameControl *)forwardLayer)->getLeastCoin()/2);
}

void Buddaha::OnStart3(CCNode* sender)
{
	((GameControl *)forwardLayer)->setBackGround(false);

	Global::getInstance()->s->removeLayerToRunningScene(this);
}


void Buddaha::doAnimationCompleted(void)
{
	isDoAction = false;
}

void Buddaha::doAction(float _f)
{
	if (isZhuan)
	{
		timeCount++;
		for (int i = 0; i < zhuan->count(); i++)
		{
			CCArray * tmp = (CCArray *)zhuan->objectAtIndex(i);
			((CCLabelAtlas *)tmp->objectAtIndex(timeCount%tmp->count()))->setVisible(true);
			((CCLabelAtlas *)tmp->objectAtIndex((timeCount-1)%tmp->count()))->setVisible(false);
		}
	}
}
void Buddaha::setZhuanIsDoing(bool _b)
{
	isZhuan = _b;
	if (isZhuan)
	{
		timeCount = 10;
		for (int i = 0; i < zhuan->count(); i++)
		{
			CCArray * tmp = (CCArray *)zhuan->objectAtIndex(i);
			((CCLabelAtlas *)tmp->objectAtIndex(0))->setVisible(true);
		}
	}
	else
	{
		for (int i = 0; i < zhuan->count(); i++)
		{
			CCArray * tmp = (CCArray *)zhuan->objectAtIndex(i);
			((CCLabelAtlas *)tmp->objectAtIndex(timeCount%tmp->count()))->setVisible(false);
		}
	}
}

CCArray * Buddaha::makeZhuan(double _x, double _y, int _type, CCNode * _node)
{
	CCArray * res = CCArray::create();
	char _s[32];
	for (int i = 0; i < 10; i++)
	{
		sprintf(_s, "%d",i);
		CCLabelAtlas * tmp = NULL;
		tmp= CCLabelAtlas::create(_s, "texiao/foguang/shuzi.png", 24, 37, '0');
		tmp->setVisible(false);
		tmp->setPosition(ccp(_x, _y));
		res->addObject(tmp);
		_node->addChild(tmp);
	}

	//((CCLabelAtlas *)res->objectAtIndex(0))->setVisible(true);

	return res;
}