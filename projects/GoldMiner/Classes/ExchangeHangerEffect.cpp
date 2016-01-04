#include "ExchangeHangerEffect.h"
#include "Global.h"
#include "Player.h"
#include "Hanger.h"

#define  EXCHANGEHANGEREFFECT_EXCHANGE_BITMAP_TIME			0.5

ExchangeHangerEffect::ExchangeHangerEffect(Hanger * _hanger)
{
	hanger = _hanger;

	isSpecial = true;
	isAllVisiable = false;
	startTime = 0.0;
	index = 0;

	special = CCNode::create();
	addChild(special);
	normal = CCNode::create();
	addChild(normal);

	mSystem = CCParticleSystemQuad::create("lizitexiao/gouzi1/gouzi1.plist");
	addChild(mSystem);

	toSpecialBitmaps = new CCArray();
	toNormalBitmaps = new CCArray();

	toSpecialBitmaps->addObject(CCSprite::create("texiao/huangouzi/huan1.png"));
	((CCSprite *)toSpecialBitmaps->lastObject())->setVisible(true);
	special->addChild((CCSprite *)toSpecialBitmaps->lastObject());
	toSpecialBitmaps->addObject(CCSprite::create("texiao/huangouzi/huan2.png"));
	((CCSprite *)toSpecialBitmaps->lastObject())->setVisible(false);
	special->addChild((CCSprite *)toSpecialBitmaps->lastObject());
	toSpecialBitmaps->addObject(CCSprite::create("texiao/huangouzi/huan3.png"));
	((CCSprite *)toSpecialBitmaps->lastObject())->setVisible(false);
	special->addChild((CCSprite *)toSpecialBitmaps->lastObject());
	toSpecialBitmaps->addObject(CCSprite::create("texiao/huangouzi/huan4.png"));
	((CCSprite *)toSpecialBitmaps->lastObject())->setVisible(false);
	special->addChild((CCSprite *)toSpecialBitmaps->lastObject());

	toNormalBitmaps->addObject(CCSprite::create("texiao/huangouzi2/huan1.png"));
	((CCSprite *)toNormalBitmaps->lastObject())->setVisible(true);
	normal->addChild((CCSprite *)toNormalBitmaps->lastObject());
	toNormalBitmaps->addObject(CCSprite::create("texiao/huangouzi2/huan2.png"));
	((CCSprite *)toNormalBitmaps->lastObject())->setVisible(false);
	normal->addChild((CCSprite *)toNormalBitmaps->lastObject());
	toNormalBitmaps->addObject(CCSprite::create("texiao/huangouzi2/huan3.png"));
	((CCSprite *)toNormalBitmaps->lastObject())->setVisible(false);
	normal->addChild((CCSprite *)toNormalBitmaps->lastObject());
	toNormalBitmaps->addObject(CCSprite::create("texiao/huangouzi2/huan4.png"));
	((CCSprite *)toNormalBitmaps->lastObject())->setVisible(false);
	normal->addChild((CCSprite *)toNormalBitmaps->lastObject());

	toSpecial();

	autorelease();
}

bool ExchangeHangerEffect::doAction(float _f)
{
	if (isAllVisiable)
	{
		startTime += _f;

		if (isSpecial)
		{
			if (startTime >= EXCHANGEHANGEREFFECT_EXCHANGE_BITMAP_TIME/toSpecialBitmaps->count())
			{
				((CCSprite *)toSpecialBitmaps->objectAtIndex(index++))->setVisible(false);
				if (index == toSpecialBitmaps->count())
				{
					index = 0;
					setUnVisiable();
				}
				else
				{
					((CCSprite *)toSpecialBitmaps->objectAtIndex(index))->setVisible(true);
					startTime = 0;
				}
			}
		}
		else
		{
			if (startTime >= EXCHANGEHANGEREFFECT_EXCHANGE_BITMAP_TIME/toNormalBitmaps->count())
			{
				((CCSprite *)toNormalBitmaps->objectAtIndex(index++))->setVisible(false);
				if (index == toNormalBitmaps->count())
				{
					index = 0;
					setUnVisiable();
					return true;
				}
				else
				{
					((CCSprite *)toNormalBitmaps->objectAtIndex(index))->setVisible(true);
					startTime = 0;
				}
			}
		}
	}

	if (isSpecial)
	{
		mSystem->setPosition(ccp(hanger->getCurrX(), hanger->getCurrY()));
	}
	
	return false;
}

void ExchangeHangerEffect::toSpecial(void)
{
	isAllVisiable = true;
	isSpecial = true;
	startTime = 0.0;
	index = 0;

	normal->setVisible(false);
	special->setPosition(ccp(hanger->getCurrX(), hanger->getCurrY()));
	special->setVisible(true);
}

void ExchangeHangerEffect::toNormal(void)
{
	isAllVisiable = true;
	isSpecial = false;
	startTime = 0.0;
	index = 0;

	mSystem->setVisible(false);
	normal->setPosition(ccp(hanger->getCurrX() + 20* cos((hanger->getAngle() - angleChange) / angleChange * pi), hanger->getCurrY() + 20* sin((hanger->getAngle() - angleChange) / angleChange * pi)));
	normal->setVisible(true);
	special->setVisible(false);
}

void ExchangeHangerEffect::setUnVisiable(void)
{
	isAllVisiable = false;
	normal->setVisible(false);
	special->setVisible(false);
}


ExchangeHangerEffect::~ExchangeHangerEffect(void)
{
	CCObject * p;
	CCARRAY_FOREACH(toSpecialBitmaps, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CCARRAY_FOREACH(toNormalBitmaps, p)
	{
		CC_SAFE_RELEASE(p);
	}
}
