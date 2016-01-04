#include "TimeAppendEffect.h"
#include "Global.h"
#include "GameControl.h"

USING_NS_CC;

#define				TIME_APPEND_EFFECT_EXCHANGE_BITMAP_TIME   0.5

TimeAppendEffect::TimeAppendEffect(GameControl * _gameControl)
{
	float startX = _gameControl->getChildByTag(1)->getPositionX();
	float startY = _gameControl->getChildByTag(1)->getPositionY();
	startTime = 0.0;
	index = 0;
	bitmaps = new CCArray();
	bitmaps->addObject(CCSprite::create("texiao/jiashijian/jiashijian1.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(true);
	((CCSprite *)bitmaps->lastObject())->setPosition(ccp(startX - 3.5, startY - 20));
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/jiashijian/jiashijian2.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	((CCSprite *)bitmaps->lastObject())->setPosition(ccp(startX - 3.5, startY - 20));
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/jiashijian/jiashijian3.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	((CCSprite *)bitmaps->lastObject())->setPosition(ccp(startX - 3.5, startY - 20));
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/jiashijian/jiashijian4.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(true);
	((CCSprite *)bitmaps->lastObject())->setPosition(ccp(startX - 3.5, startY - 20));
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/jiashijian/jiashijian5.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	((CCSprite *)bitmaps->lastObject())->setPosition(ccp(startX - 3.5, startY - 20));
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/jiashijian/jiashijian6.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	((CCSprite *)bitmaps->lastObject())->setPosition(ccp(startX - 3.5, startY - 20));
	addChild((CCSprite *)bitmaps->lastObject());

	CCSequence * sequence;
	CCSpawn * spawn;
	startX = Global::getInstance()->getcentreX();
	startY = Global::getInstance()->getcentreY();

	addTimeSprite = CCSprite::create("texiao/+15.png");
	addTimeSprite->setPosition(ccp(startX + 40, startY  + 15));
	spawn = CCSpawn::create(CCFadeIn::create(.3f),CCMoveTo::create(.3f,ccp(startX + 40,startY  + 15 +40)),NULL);
	sequence = CCSequence::create(spawn,CCFadeTo::create(1,255*1),CCFadeOut::create(.2f),NULL);
	//sequence = CCSequence::create(CCScaleTo::create(.1f,1.5f),CCScaleTo::create(.1f,1),
	//	CCMoveTo::create(.3f,ccp(startX + 90,startY  + 65 +80))
	//	,CCFadeOut::create(.2f),NULL);
	addTimeSprite->runAction(sequence);
	addTimeSprite->retain();
	addChild(addTimeSprite);

	this->autorelease();
}


TimeAppendEffect::~TimeAppendEffect(void)
{
}

void TimeAppendEffect::onExit()
{
	CC_SAFE_RELEASE_NULL(addTimeSprite);

	CCObject * p;

	CCARRAY_FOREACH(bitmaps, p)
	{
		CC_SAFE_RELEASE(p);
	}

	CCLayer::onExit();
}

bool TimeAppendEffect::doAction(float _f)
{
	startTime += _f;
	if (startTime >= TIME_APPEND_EFFECT_EXCHANGE_BITMAP_TIME/bitmaps->count())
	{
		((CCSprite *)bitmaps->objectAtIndex(index++))->setVisible(false);
		if (index == bitmaps->count())
		{
			index = 0;
			return true;
		}
		((CCSprite *)bitmaps->objectAtIndex(index))->setVisible(true);
		startTime = 0;
	}
	return false;
}