#include "Explode.h"
#include "Global.h"
#include "Player.h"

#define  EXPLODE_EXCHANGE_BITMAP_TIME			0.5

Explode::Explode(int _type)
{
	type = _type;
	startTime = 0.0;
	index = 0;
	bitmaps = new CCArray();
	if (_type == B_EXPLODE)
	{
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BOMB);
		bitmaps->addObject(CCSprite::create("texiao/baozha2/bzu1.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(true);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/baozha2/bzu2.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/baozha2/bzu3.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/baozha2/bzu4.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/baozha2/bzu5.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/baozha2/bzu6.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
	}
	else if (_type == S_EXPLODE)
	{
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BOMB);
		bitmaps->addObject(CCSprite::create("texiao/baozha1/bz1.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(true);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/baozha1/bz2.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/baozha1/bz3.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/baozha1/bz4.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/baozha1/bz5.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/baozha1/bz6.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
	}	
	else if (_type == HANGER_EXPLODE)
	{
		bitmaps->addObject(CCSprite::create("texiao/zhuagou/zhuagou1.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(true);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/zhuagou/zhuagou2.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/zhuagou/zhuagou3.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/zhuagou/zhuagou4.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
		bitmaps->addObject(CCSprite::create("texiao/zhuagou/zhuagou5.png"));
		((CCSprite *)bitmaps->lastObject())->setVisible(false);
		addChild((CCSprite *)bitmaps->lastObject());
	}

	autorelease();
}

bool Explode::doAction(float _f)
{
	startTime += _f;
	if (startTime >= EXPLODE_EXCHANGE_BITMAP_TIME/bitmaps->count())
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

Explode::~Explode(void)
{
	CCObject * p;
	CCARRAY_FOREACH(bitmaps, p)
	{
		CC_SAFE_RELEASE(p);
	}
}
