#include "Alignment.h"
#include "Hanger.h"
#include "MusicControl.h"
#include "Player.h"

#define	ALIGNMENT_TIME_CONTROL 90

Alignment::Alignment(void)
{
	CCSprite();
	type = ALIGNMENT_TYPE_NORMAL;
	initWithFile("youxi/xian2.png");
	setScaleX(0.65);
	isJewelSkillUnVisiable = false;

	autorelease();
}


Alignment::~Alignment(void)
{
}

bool Alignment::doAction(float _f, Hanger * _hanger)
{
	if (isJewelSkillUnVisiable)
	{
		return false;
	}

	if (_hanger->getStatus() == HANGER_STATUS_SWAYING && _hanger->isVisible())
	{
		setRotation(angleCenter - _hanger->getAngle());
		changeMiaoZhunXianPosition(_hanger);
		setVisible(true);
	}
	else
	{
		setVisible(false);
	}

	if (type == ALIGNMENT_TYPE_SHAHESHANG)
	{
		jiGuangTimeCount++;
		if (jiGuangTimeCount <= ALIGNMENT_TIME_CONTROL)
		{
			setTextureRect(*new CCRect(0,getContentSize().height*(ALIGNMENT_TIME_CONTROL-jiGuangTimeCount)/ALIGNMENT_TIME_CONTROL,getContentSize().width,getContentSize().height));
		}
	}
	return true;
}

void Alignment::setJewelSkillUnVisiable(bool _b)
{
	isJewelSkillUnVisiable = _b;

	if (_b)
	{
		setVisible(!_b);
	}
}

void Alignment::setType(int _type)
{	
	CCTexture2D *pTexture;
	CCRect rect;

	type = _type;

	if (_type == ALIGNMENT_TYPE_NORMAL)
	{
		pTexture = CCTextureCache::sharedTextureCache()->addImage("youxi/xian2.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
		}
	}
	else if (_type == ALIGNMENT_TYPE_SHAHESHANG)
	{
		pTexture = CCTextureCache::sharedTextureCache()->addImage("youxi/miaozhunxian.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
		}
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_SHAHESHANG_LINE);
		jiGuangTimeCount = 0;		
	}
}

void Alignment::changeMiaoZhunXianPosition(Hanger * _hanger)
{
	double positionX = _hanger->getCurrX() + 
		getContentSize().height * 0.8 / 2 * cos(_hanger->getAngle() / angleChange * pi);
	double positionY = _hanger->getCurrY() + 
		getContentSize().height * 0.8 / 2 * sin(_hanger->getAngle() / angleChange * pi);

	setPosition(ccp(positionX, positionY));
}
