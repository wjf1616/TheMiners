#include "LastTimeCountEffect.h"
#include "Global.h"

#define  LASTTIMECOUNTEFFECT_EXCHANGE_BITMAP_TIME				0.1
#define  LASTTIMECOUNTEFFECT_PER_EXCHANGE_BITMAP_TIME			1.0

LastTimeCountEffect::LastTimeCountEffect(int _type)
{
	startTime = 0.0;
	perTime = 0.0;
	index = 0;
	isExchange = true;
	bitmaps = new CCArray();

	bitmaps->addObject(CCSprite::create("texiao/daoshu/daoshu1.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(true);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/daoshu/daoshu2.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/daoshu/daoshu3.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/daoshu/daoshu4.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/daoshu/daoshu5.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/daoshu/daoshu6.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());

	autorelease();
}

bool LastTimeCountEffect::doAction(float _f)
{
	bool res = false;
	startTime += _f;
	perTime += _f;
	if (isExchange)
	{
		if (startTime >= LASTTIMECOUNTEFFECT_EXCHANGE_BITMAP_TIME)
		{
			((CCSprite *)bitmaps->objectAtIndex(index++))->setVisible(false);
			if (index == bitmaps->count())
			{
				index = 0;
				isExchange = false;
				res = true;
			}
			else
			{
				((CCSprite *)bitmaps->objectAtIndex(index))->setVisible(true);
				startTime = 0;
			}
		}
	}

	if (perTime >= LASTTIMECOUNTEFFECT_PER_EXCHANGE_BITMAP_TIME)
	{
		isExchange = true;
		((CCSprite *)bitmaps->objectAtIndex(index))->setVisible(true);
		startTime = 0;
		perTime = 0;
	}

	return res;
}

LastTimeCountEffect::~LastTimeCountEffect(void)
{
	CCObject * p;
	CCARRAY_FOREACH(bitmaps, p)
	{
		CC_SAFE_RELEASE(p);
	}
}
