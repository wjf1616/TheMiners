#include "Sensitization.h"
#include "Global.h"

#define  SENSITIZATION_EXCHANGE_BITMAP_TIME			0.1

Sensitization::Sensitization(int _type)
{
	startTime = 0.0;
	index = 0;
	bitmaps = new CCArray();

	if (_type == SENSITIZATION_TYPE_CIRCULAR)
	{
		bitmaps->addObject(CCSprite::create("texiao/liuguang1/lg1.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(true);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/liuguang1/lg2.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/liuguang1/lg3.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/liuguang1/lg4.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/liuguang1/lg5.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/liuguang1/lg6.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/liuguang1/lg7.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/liuguang1/lg8.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
	}
	else if (_type == SENSITIZATION_TYPE_RECT)
	{
		bitmaps->addObject(CCSprite::create("texiao/liuguang2/g1.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(true);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/liuguang2/g2.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/liuguang2/g3.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/liuguang2/g4.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/liuguang2/g5.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/liuguang2/g6.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/liuguang2/g7.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/liuguang2/g8.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/liuguang2/g9.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/liuguang2/g10.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
	}

	autorelease();
}

bool Sensitization::doAction(float _f)
{
	startTime += _f;
	if (startTime >= SENSITIZATION_EXCHANGE_BITMAP_TIME)
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

Sensitization::~Sensitization(void)
{
	CCObject * p;
	CCARRAY_FOREACH(bitmaps, p)
	{
		CC_SAFE_RELEASE(p);
	}
}
