#include "Explosive.h"
#include "Hanger.h"
#include "Target.h"
#include "DynamicTarget.h"

#define			GRENADE_TIME					20

Explosive::Explosive(Hanger * _hanger)
{
	CCSprite();
	initWithFile("youxi/zhadan.png");

	hanger = _hanger;
	hanger->retain();

	statusTimeCount = 0;

	autorelease();
}


Explosive::~Explosive(void)
{
	CC_SAFE_RELEASE(hanger);
}


bool Explosive::doAction(float _f)
{
#ifdef						GOLDEN_MINER_2_VERSION_TIME
	statusTimeCount += _f;
	double _positionX = 0;
	double _positionY = 0;
	float _ratio = (GRENADE_TIME/60.0 - statusTimeCount) / (GRENADE_TIME/60.0);
	if (_ratio < 0)
	{
		_ratio = 0;
	}
	if(hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
	{
		_positionX = ((Target *)hanger->carryTargetPoint)->getPositionX() + (Global::getInstance()->getcentreX() - ((Target *)hanger->carryTargetPoint)->getPositionX()) * _ratio;
		_positionY = ((Target *)hanger->carryTargetPoint)->getPositionY() + (Global::getInstance()->getcentreY() - ((Target *)hanger->carryTargetPoint)->getPositionY()) * _ratio;
		setPosition(ccp(_positionX, _positionY));
	}
	else if (hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
	{
		if (((DynamicTarget *)hanger->carryTargetPoint)->getId() == DYNAMIC_ID_SHELL)
		{
			_positionX = ((DynamicTargetShell *)hanger->carryTargetPoint)->shellSprite->getPositionX() + (Global::getInstance()->getcentreX() - ((DynamicTarget *)hanger->carryTargetPoint)->getArmature()->getPositionX()) * _ratio;
			_positionY = ((DynamicTargetShell *)hanger->carryTargetPoint)->shellSprite->getPositionY() + (Global::getInstance()->getcentreY() - ((DynamicTarget *)hanger->carryTargetPoint)->getArmature()->getPositionY()) * _ratio;
		}
		else
		{
			_positionX = ((DynamicTarget *)hanger->carryTargetPoint)->getArmature()->getPositionX() + (Global::getInstance()->getcentreX() - ((DynamicTarget *)hanger->carryTargetPoint)->getArmature()->getPositionX()) * _ratio;
			_positionY = ((DynamicTarget *)hanger->carryTargetPoint)->getArmature()->getPositionY() + (Global::getInstance()->getcentreY() - ((DynamicTarget *)hanger->carryTargetPoint)->getArmature()->getPositionY()) * _ratio;
		}
		setPosition(ccp(_positionX, _positionY));
	}
	else
	{
		return true;
	}
	if ((statusTimeCount >= GRENADE_TIME/60.0)&& ((statusTimeCount - _f) >= GRENADE_TIME/60.0))
	{
		return true;
		//releaseSkills(SKILL_ID_GRENADE);	
	}
#else
	statusTimeCount++;
	double _positionX = 0;
	double _positionY = 0;
	if(hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
	{
		_positionX = ((Target *)hanger->carryTargetPoint)->getPositionX() + (Global::getInstance()->getcentreX() - ((Target *)hanger->carryTargetPoint)->getPositionX()) * (GRENADE_TIME - statusTimeCount) / GRENADE_TIME;
		_positionY = ((Target *)hanger->carryTargetPoint)->getPositionY() + (Global::getInstance()->getcentreY() - ((Target *)hanger->carryTargetPoint)->getPositionY()) * (GRENADE_TIME - statusTimeCount) / GRENADE_TIME;
		setPosition(ccp(_positionX, _positionY));
	}
	else if (hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
	{
		if (((DynamicTarget *)hanger->carryTargetPoint)->getId() == DYNAMIC_ID_SHELL)
		{
			_positionX = ((DynamicTargetShell *)hanger->carryTargetPoint)->shellSprite->getPositionX() + (Global::getInstance()->getcentreX() - ((DynamicTarget *)hanger->carryTargetPoint)->getArmature()->getPositionX()) * (GRENADE_TIME - statusTimeCount) / GRENADE_TIME;
			_positionY = ((DynamicTargetShell *)hanger->carryTargetPoint)->shellSprite->getPositionY() + (Global::getInstance()->getcentreY() - ((DynamicTarget *)hanger->carryTargetPoint)->getArmature()->getPositionY()) * (GRENADE_TIME - statusTimeCount) / GRENADE_TIME;
		}
		else
		{
			_positionX = ((DynamicTarget *)hanger->carryTargetPoint)->getArmature()->getPositionX() + (Global::getInstance()->getcentreX() - ((DynamicTarget *)hanger->carryTargetPoint)->getArmature()->getPositionX()) * (GRENADE_TIME - statusTimeCount) / GRENADE_TIME;
			_positionY = ((DynamicTarget *)hanger->carryTargetPoint)->getArmature()->getPositionY() + (Global::getInstance()->getcentreY() - ((DynamicTarget *)hanger->carryTargetPoint)->getArmature()->getPositionY()) * (GRENADE_TIME - statusTimeCount) / GRENADE_TIME;
		}
		setPosition(ccp(_positionX, _positionY));
	}
	else
	{
		return true;
	}
	if (statusTimeCount == GRENADE_TIME)
	{
		return true;
		//releaseSkills(SKILL_ID_GRENADE);	
	}
#endif
	return false;
}
