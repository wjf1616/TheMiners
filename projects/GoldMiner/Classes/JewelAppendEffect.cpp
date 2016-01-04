#include "JewelAppendEffect.h"
#include "Global.h"
#include "GameControl.h"

#define			ADD_NEW_JEWEL_FLY_TIME_LONG		0.5

#define			RED_JEWEL_BLUE_X				766.4
#define			RED_JEWEL_RED_X					754.1
#define			RED_JEWEL_GREEN_X				717.8
#define			RED_JEWEL_YELLOW_X				707.3
#define			RED_JEWEL_PURPLE_X				736.1
#define			RED_JEWEL_BLUE_Y				240.8
#define			RED_JEWEL_RED_Y					207.3
#define			RED_JEWEL_GREEN_Y				207.9
#define			RED_JEWEL_YELLOW_Y				240.1
#define			RED_JEWEL_PURPLE_Y				264.4

USING_NS_CC;

JewelAppendEffect::JewelAppendEffect(GameControl * _gameControl, int _addNewJewelType)
{
	flyTime = 0.0;
	destinationX = _gameControl->getGetCoinLabelPosition().x;
	destinationY = _gameControl->getGetCoinLabelPosition().y;
	startX = Global::getInstance()->getcentreX();
	startY = Global::getInstance()->getcentreY();


	addNewJewelType = _addNewJewelType;
	newJewelSystem = CCParticleSystemQuad::create("lizitexiao/daojulizi/daojulizi.plist");//plist文件可以通过例子编辑器获得
	newJewelSystem->setPosition(ccp(startX, startY));
	newJewelSystem->retain();
	addChild(newJewelSystem);


	this->autorelease();
}


JewelAppendEffect::~JewelAppendEffect(void)
{
}

void JewelAppendEffect::onExit()
{
	CC_SAFE_RELEASE_NULL(newJewelSystem);

	CCLayer::onExit();
}

int JewelAppendEffect::getAddNewJewelType(void)
{
	return addNewJewelType;
}


bool JewelAppendEffect::doAction(float _f)
{
	flyTime += _f;
	if (flyTime < ADD_NEW_JEWEL_FLY_TIME_LONG)
	{
		switch(addNewJewelType)
		{
		case PROP_TYPE_JEWEL_BLUE:
			newJewelSystem->setPosition(ccp(Global::getInstance()->getcentreX() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_BLUE_X - Global::getInstance()->getcentreX()), Global::getInstance()->getcentreY() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_BLUE_Y - Global::getInstance()->getcentreY())));
			break;
		case PROP_TYPE_JEWEL_PURPLE:
			newJewelSystem->setPosition(ccp(Global::getInstance()->getcentreX() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_PURPLE_X - Global::getInstance()->getcentreX()), Global::getInstance()->getcentreY() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_PURPLE_Y - Global::getInstance()->getcentreY())));
			break;
		case PROP_TYPE_JEWEL_YELLOW:
			newJewelSystem->setPosition(ccp(Global::getInstance()->getcentreX() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_YELLOW_X - Global::getInstance()->getcentreX()), Global::getInstance()->getcentreY() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_YELLOW_Y - Global::getInstance()->getcentreY())));
			break;
		case PROP_TYPE_JEWEL_GREEN:
			newJewelSystem->setPosition(ccp(Global::getInstance()->getcentreX() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_GREEN_X - Global::getInstance()->getcentreX()), Global::getInstance()->getcentreY() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_GREEN_Y - Global::getInstance()->getcentreY())));
			break;
		case PROP_TYPE_JEWEL_RED:
			newJewelSystem->setPosition(ccp(Global::getInstance()->getcentreX() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_RED_X - Global::getInstance()->getcentreX()), Global::getInstance()->getcentreY() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_RED_Y - Global::getInstance()->getcentreY())));
			break;
		default:
			break;
		}
		return false;
	}
	else
	{
		return true;
	}
}