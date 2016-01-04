#include "PowerBuff.h"
#include "Global.h"
#include "GameControl.h"

#define  POWERBUFF_EXCHANGE_BITMAP_TIME			0.7

PowerBuff::PowerBuff(GameControl * _gameControl)
{
	startTime = 0.0;
	index = 0;
	isBuff = false;

	bitmap = CCNode::create();
	bitmap->setPosition(ccp(Global::getInstance()->getcentreX()+25, Global::getInstance()->getcentreY()+40));
	//bitmap->setPosition(ccp(Global::getInstance()->getcentreX()+25, Global::getInstance()->getcentreY()+60));
	_gameControl->addChild(bitmap, LAYER_ORDER_CONTROL + 3);
	buffBitmap = CCNode::create();
	buffBitmap->setPosition(ccp(Global::getInstance()->getcentreX()+25, Global::getInstance()->getcentreY()+40));
	_gameControl->addChild(buffBitmap, LAYER_ORDER_CONTROL + 3);
	// buff1
	//buffBitmap->setPosition(ccp(Global::getInstance()->getcentreX()+25, Global::getInstance()->getcentreY()-10));
	//_gameControl->addChild(buffBitmap);

	bitmaps = new CCArray();

	bitmaps->addObject(CCSprite::create("texiao/liliang2/liliang1.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(true);
	bitmap->addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/liliang2/liliang2.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	bitmap->addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/liliang2/liliang3.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	bitmap->addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/liliang2/liliang4.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	bitmap->addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/liliang2/liliang5.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	bitmap->addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/liliang2/liliang6.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	bitmap->addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/liliang2/liliang7.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	bitmap->addChild((CCSprite *)bitmaps->lastObject());
	//bitmaps->addObject(CCSprite::create("texiao/liliang/liliang1.png"));
	//((CCSprite *)bitmaps->lastObject())->setVisible(true);
	//addChild((CCSprite *)bitmaps->lastObject());
	//bitmaps->addObject(CCSprite::create("texiao/liliang/liliang2.png"));
	//((CCSprite *)bitmaps->lastObject())->setVisible(false);
	//addChild((CCSprite *)bitmaps->lastObject());
	//bitmaps->addObject(CCSprite::create("texiao/liliang/liliang3.png"));
	//((CCSprite *)bitmaps->lastObject())->setVisible(false);
	//addChild((CCSprite *)bitmaps->lastObject());
	//bitmaps->addObject(CCSprite::create("texiao/liliang/liliang4.png"));
	//((CCSprite *)bitmaps->lastObject())->setVisible(false);
	//addChild((CCSprite *)bitmaps->lastObject());
	//bitmaps->addObject(CCSprite::create("texiao/liliang/liliang5.png"));
	//((CCSprite *)bitmaps->lastObject())->setVisible(false);
	//addChild((CCSprite *)bitmaps->lastObject());
	//bitmaps->addObject(CCSprite::create("texiao/liliang/liliang6.png"));
	//((CCSprite *)bitmaps->lastObject())->setVisible(false);
	//addChild((CCSprite *)bitmaps->lastObject());
	//bitmaps->addObject(CCSprite::create("texiao/liliang/liliang7.png"));
	//((CCSprite *)bitmaps->lastObject())->setVisible(false);
	//addChild((CCSprite *)bitmaps->lastObject());
	//bitmaps->addObject(CCSprite::create("texiao/liliang/liliang8.png"));
	//((CCSprite *)bitmaps->lastObject())->setVisible(false);
	//addChild((CCSprite *)bitmaps->lastObject());

	buffBitmaps = new CCArray();
	buffBitmaps->addObject(CCSprite::create("texiao/jiabuff2/jia1.png"));
	((CCSprite *)buffBitmaps->lastObject())->setVisible(false);
	buffBitmap->addChild((CCSprite *)buffBitmaps->lastObject());
	buffBitmaps->addObject(CCSprite::create("texiao/jiabuff2/jia2.png"));
	((CCSprite *)buffBitmaps->lastObject())->setVisible(false);
	buffBitmap->addChild((CCSprite *)buffBitmaps->lastObject());
	buffBitmaps->addObject(CCSprite::create("texiao/jiabuff2/jia3.png"));
	((CCSprite *)buffBitmaps->lastObject())->setVisible(false);
	buffBitmap->addChild((CCSprite *)buffBitmaps->lastObject());
	buffBitmaps->addObject(CCSprite::create("texiao/jiabuff2/jia4.png"));
	((CCSprite *)buffBitmaps->lastObject())->setVisible(false);
	buffBitmap->addChild((CCSprite *)buffBitmaps->lastObject());
	// buff1
	//buffBitmaps->addObject(CCSprite::create("texiao/jiabuff/buff1.png"));
	//((CCSprite *)buffBitmaps->lastObject())->setVisible(false);
	//buffBitmap->addChild((CCSprite *)buffBitmaps->lastObject());
	//buffBitmaps->addObject(CCSprite::create("texiao/jiabuff/buff2.png"));
	//((CCSprite *)buffBitmaps->lastObject())->setVisible(false);
	//buffBitmap->addChild((CCSprite *)buffBitmaps->lastObject());
	//buffBitmaps->addObject(CCSprite::create("texiao/jiabuff/buff3.png"));
	//((CCSprite *)buffBitmaps->lastObject())->setVisible(false);
	//buffBitmap->addChild((CCSprite *)buffBitmaps->lastObject());
	//buffBitmaps->addObject(CCSprite::create("texiao/jiabuff/buff4.png"));
	//((CCSprite *)buffBitmaps->lastObject())->setVisible(false);
	//buffBitmap->addChild((CCSprite *)buffBitmaps->lastObject());

	autorelease();
}

bool PowerBuff::doAction(float _f)
{
	startTime += _f;
	if (isBuff)
	{
		if (startTime >= POWERBUFF_EXCHANGE_BITMAP_TIME/buffBitmaps->count())
		{
			((CCSprite *)buffBitmaps->objectAtIndex(index++))->setVisible(false);
			if (index == buffBitmaps->count())
			{
				index = 0;
				return true;
			}
			((CCSprite *)buffBitmaps->objectAtIndex(index))->setVisible(true);
			startTime = 0;
		}
	}
	else
	{
		if (startTime >= POWERBUFF_EXCHANGE_BITMAP_TIME/bitmaps->count())
		{
			((CCSprite *)bitmaps->objectAtIndex(index++))->setVisible(false);
			if (index == bitmaps->count())
			{
				index = 0;
				isBuff = true;
				bitmap->setVisible(false);
				startTime = 0.0;
				((CCSprite *)buffBitmaps->objectAtIndex(0))->setVisible(true);
			}
			else
			{
				((CCSprite *)bitmaps->objectAtIndex(index))->setVisible(true);
				startTime = 0;
			}
		}
	}
	return false;
}

PowerBuff::~PowerBuff(void)
{
	CCObject * p;
	CCARRAY_FOREACH(bitmaps, p)
	{
		CC_SAFE_RELEASE(p);
	}
}

void PowerBuff::removeSelf(GameControl * _gameControl)
{
	_gameControl->removeChild(bitmap);
	_gameControl->removeChild(buffBitmap);
}
