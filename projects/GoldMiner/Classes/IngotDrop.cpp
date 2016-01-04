#include "IngotDrop.h"
#include "Global.h"

#define  INGOTDROP_EXCHANGE_BITMAP_TIME			3

IngotDrop::IngotDrop(int _speed, float _staticPositionY, float _staticLiveTime)
{
	startPositionY = 470;
	speed = _speed;
	staticPositionY = _staticPositionY;
	staticLiveTime = _staticLiveTime;
	liveCount = 0.0;
	startTime = 0.0;
	index = 0;
	bitmaps = new CCArray();

	bitmaps->addObject(CCSprite::create("texiao/tongqian/tongqian1.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(true);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/tongqian/tongqian2.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/tongqian/tongqian3.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/tongqian/tongqian4.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/tongqian/tongqian5.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/tongqian/tongqian6.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());


	autorelease();
}

bool IngotDrop::doAction(float _f)
{
	startTime += _f;
	
	if(liveCount > 0)
	{
		liveCount += _f;
		if(liveCount >= staticLiveTime)
		{
			return true;
		}
	}
	else
	{
		if(getPositionY() <= 10)
		{
			liveCount = 1;
		}
		else
		{
			startPositionY -= speed;
			setPositionY(startPositionY);
			CCLog("startPositionY = %f, speed = %d",startPositionY, speed);
		}
	}

	if (startTime >= INGOTDROP_EXCHANGE_BITMAP_TIME/bitmaps->count())
	{
		((CCSprite *)bitmaps->objectAtIndex(index++))->setVisible(false);


		if (index == bitmaps->count())
		{
			index = 0;
		}

		((CCSprite *)bitmaps->objectAtIndex(index))->setVisible(true);
		startTime = 0;
	}
	return false;
}

IngotDrop::~IngotDrop(void)
{
	CCObject * p;
	CCARRAY_FOREACH(bitmaps, p)
	{
		CC_SAFE_RELEASE(p);
	}
}
