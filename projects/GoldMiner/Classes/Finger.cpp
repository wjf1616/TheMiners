#include "Finger.h"
#include "Global.h"

#define  Finger_EXCHANGE_BITMAP_TIME			0.5

Finger::Finger(void)
{
	startTime = 0.0;
	index = 0;
	bitmaps = new CCArray();

	bitmaps->addObject(CCSprite::create("texiao/shouzhi/shou1.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(true);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/shouzhi/shou2.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/shouzhi/shou3.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/shouzhi/shou4.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/shouzhi/shou5.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/shouzhi/shou6.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());

	autorelease();
}

bool Finger::doAction(float _f)
{
	startTime += _f;
	if (startTime >= Finger_EXCHANGE_BITMAP_TIME/bitmaps->count())
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

Finger::~Finger(void)
{
	CCObject * p;
	CCARRAY_FOREACH(bitmaps, p)
	{
		CC_SAFE_RELEASE(p);
	}
}
