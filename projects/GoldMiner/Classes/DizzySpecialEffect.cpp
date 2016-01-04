#include "DizzySpecialEffect.h"

#define			DIZZY_SPECIAL_EFFECT_EXCHANGE_BITMAP_TIME					0.5

DizzySpecialEffect::DizzySpecialEffect(void)
{
	startTime = 0.0;
	index = 0;
	bitmaps = new CCArray();
	bitmaps->addObject(CCSprite::create("texiao/yun/yun1.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(true);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/yun/yun2.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/yun/yun3.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());

	autorelease();
}

bool DizzySpecialEffect::doAction(float _f)
{
	startTime += _f;
	if (startTime >= DIZZY_SPECIAL_EFFECT_EXCHANGE_BITMAP_TIME/bitmaps->count())
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

DizzySpecialEffect::~DizzySpecialEffect(void)
{
	CCObject * p;
	CCARRAY_FOREACH(bitmaps, p)
	{
		CC_SAFE_RELEASE(p);
	}
}