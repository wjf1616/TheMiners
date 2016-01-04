#include "Carrier.h"
#include "GameControl.h"

#define			TARGET_SCALE_SIZE_CONTROL				32

#define			CARRIER_SPEED_CONTROL					10.0

USING_NS_CC;

Carrier::Carrier(double _x, double _y, int _id, int _direction, int _speed)
{
	//status = CARRIER_STATUS_MOVING;
	carriedTarget = NULL;
	carriedTargetType = NULL;
	currX = _x;
	currY = _y;
	id = _id;
	isJustChangeDirction = false;
	initSelfById();

	vectorX = _speed / CARRIER_SPEED_CONTROL;
	if (_direction == 1)
	{
		vectorX = - vectorX;
	}
	else if (_direction != 2)
	{
		if (rand() % 2 == 0)
		{
			vectorX = - vectorX;
		}
	}

	autorelease();
}


Carrier::~Carrier(void)
{
	CCObject * p;
	CCARRAY_FOREACH(carriedTarget, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CCARRAY_FOREACH(carriedTargetType, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CC_SAFE_RELEASE(spriteUp);
	CC_SAFE_RELEASE(spriteDown);
	CC_SAFE_RELEASE(spriteMiddle);
}


void Carrier::doAction(float _f)
{
	//changeX = 0;

	//if (status == CARRIER_STATUS_MOVING)
	//{
		upDateSelfPosition();
	//}
	upDateCarriedTarget();
}


cocos2d::CCSprite * Carrier::getSpriteDown(void)
{
	return spriteDown;
}

cocos2d::CCSprite * Carrier::getSpriteMiddle(void)
{
	return spriteMiddle;
}

cocos2d::CCSprite * Carrier::getSpriteUp(void)
{
	return spriteUp;
}

cocos2d::CCArray * Carrier::getCarriedTarget(void)
{
	return carriedTarget;
}

//void Carrier::setStatus(int _status)
//{
//	status = _status;
//}

void Carrier::addSelfToLayer(GameControl * _gameControl)
{
	_gameControl->addChild(spriteDown);// 云朵的下层
	if (id == CARRIER_ID_CLOUD)
	{
		if (carriedTarget != NULL)
		{
			//for (int i = 0; i < carriedTarget->count(); i++)
			//{
			//	// pointIndex从小到大排序
			//	for(int j = i + 1; j < carriedTarget->count(); j++)
			//	{
			//		if(((Target *)carriedTarget->objectAtIndex(i))->getPointIndex() > ((Target *)carriedTarget->objectAtIndex(j))->getPointIndex())
			//		{
			//			carriedTarget->exchangeObjectAtIndex(i , j);
			//		}
			//	}
			//	_gameControl->addChild((Target *)carriedTarget->objectAtIndex(i));
			//}
			for (int i = 0; i < carriedTarget->count(); i++)
			{
				if(((CCInteger *)carriedTargetType->objectAtIndex(i))->getValue() == 0)
				{
					setTargetPositionByPointIndex(((Target *)carriedTarget->objectAtIndex(i))->getPointIndex() ,carriedTarget->objectAtIndex(i));
					_gameControl->addChild((Target *)carriedTarget->objectAtIndex(i));
				}
				else
				{
					setDynamicTargetPositionByPointIndex(((DynamicTargetHuoHuaLian *)carriedTarget->objectAtIndex(i))->getPointIndex() ,carriedTarget->objectAtIndex(i));
					_gameControl->addChild(((DynamicTarget *)carriedTarget->objectAtIndex(i))->getArmature());
					//_gameControl->addChild(((DynamicTarget *)carriedTarget->objectAtIndex(i))->roleSwaySpeed);
				}
			}
		}
	}
	else if(id == CARRIER_ID_BLACK_CLOUD)
	{
		if (carriedTarget != NULL)
		{
			//_gameControl->addChild(((DynamicTarget *)carriedTarget->objectAtIndex(0))->roleSwaySpeed);
			if (((DynamicTarget *)carriedTarget->objectAtIndex(0))->getId() == DYNAMIC_ID_PEARL_SHELL)
			{
				_gameControl->addChild(((DynamicTargetPearlShell *)carriedTarget->objectAtIndex(0))->getShell());
			}
			else if (((DynamicTarget *)carriedTarget->objectAtIndex(0))->getId()  == DYNAMIC_ID_YUMIANGONGZHU)
			{
				_gameControl->addChild(((DynamicTargetYuMianGongZhu *)carriedTarget->objectAtIndex(0))->getPen());
			}
			_gameControl->addChild(((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature());
		}

		//if (((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getScaleX() < 0)
		//{
		//	((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->setPositionX(((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getPositionX() + ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getWidth()/2);
		//}
		currX -= checkWidth/2;//+((DynamicTarget *)carriedTarget->objectAtIndex(0))->getWidth() /2;
		currY -= (((DynamicTarget *)carriedTarget->objectAtIndex(0))->getHeight() /2);
		spriteDown->setPosition(ccp(currX + checkWidth/2, currY + checkHeight/2));
		spriteMiddle->setPosition(ccp(currX+ spriteMiddle->getContentSize().width/2, currY + spriteMiddle->getContentSize().height/2));
		spriteUp->setPosition(ccp(currX + spriteUp->getContentSize().width/2, currY - spriteUp->getContentSize().height/2));

		//spriteDown->setPositionX(spriteMiddle->getPositionX()+checkWidth/2+((DynamicTarget *)carriedTarget->objectAtIndex(0))->getWidth() /2);
		//spriteMiddle->setPositionX(spriteMiddle->getPositionX()+checkWidth/2+((DynamicTarget *)carriedTarget->objectAtIndex(0))->getWidth() /2);
		//spriteUp->setPositionX(spriteUp->getPositionX()+checkWidth/2+((DynamicTarget *)carriedTarget->objectAtIndex(0))->getWidth() /2);
		//spriteDown->setPositionY(spriteMiddle->getPositionY()-(((DynamicTarget *)carriedTarget->objectAtIndex(0))->getHeight() /2 - checkHeight/2));
		//spriteMiddle->setPositionY(spriteMiddle->getPositionY()-(((DynamicTarget *)carriedTarget->objectAtIndex(0))->getHeight() /2 - checkHeight/2));
		//spriteUp->setPositionY(spriteUp->getPositionY()-(((DynamicTarget *)carriedTarget->objectAtIndex(0))->getHeight() /2 - checkHeight/2));
	}
	_gameControl->addChild(spriteMiddle);// 云朵的上层
	_gameControl->addChild(spriteUp);// 云朵的上层
}

void Carrier::addCarriedTarget(void * _target, bool _isTarget)
{
	if (carriedTarget == NULL)
	{
		carriedTarget = new CCArray;
		carriedTargetType = new CCArray;
	}
	if (id == CARRIER_ID_CLOUD)
	{
		if(_isTarget)
		{
			carriedTarget->addObject((Target *)_target);
			carriedTargetType->addObject(CCInteger::create(0));
		}
		else
		{
			carriedTarget->addObject((DynamicTarget *)_target);
			((DynamicTarget *)_target)->getArmature()->setScaleX(-0.8);
			carriedTargetType->addObject(CCInteger::create(1));
		}
	}
	else if(id == CARRIER_ID_BLACK_CLOUD)
	{
		carriedTarget->addObject((DynamicTarget *)_target);
		if(vectorX > 0)
		{
			((DynamicTarget *)_target)->getArmature()->setScaleX(-0.8);
			//spriteDown->setScaleX(-1);
			//spriteMiddle->setScaleX(-1);
			//spriteUp->setScaleX(-1);
		}
	}
}

bool Carrier::isCarried(double _positionX, double _positionY)
{
	bool res = false;

	if ((_positionX < (currX + checkWidth) ) && (_positionX > currX) && (_positionY > currY) && (_positionY < (currY + checkHeight)))
	{
		res = true;
	}

	return res;
}
	
bool Carrier::isCarried(void * _target)
{
	if(((Target *)_target)->getYunIndex() == yunIndex)
	{
		return true;
	}

	return false;
}

bool Carrier::isCarriedDynamicTarget(void * _target)
{
	if(((DynamicTargetHuoHuaLian *)_target)->getYunIndex() == yunIndex)
	{
		return true;
	}

	return false;
}
	
void Carrier::initSelfById(void)
{
	if (id == CARRIER_ID_CLOUD )
	{
		spriteDown = CCSprite::create("tmx/yun1.png");
		CC_SAFE_RETAIN(spriteDown);
		checkWidth = spriteDown->getContentSize().width;
		checkHeight = spriteDown->getContentSize().height;
		spriteDown->setPosition(ccp(currX + checkWidth/2, currY + checkHeight/2));
		spriteMiddle = CCSprite::create("tmx/yun2.png");
		CC_SAFE_RETAIN(spriteMiddle);
		spriteMiddle->setPosition(ccp(currX + spriteMiddle->getContentSize().width/2, currY + spriteMiddle->getContentSize().height/2));
		spriteUp = CCSprite::create("tmx/yun3.png");
		CC_SAFE_RETAIN(spriteUp);
		spriteUp->setPosition(ccp(currX + spriteUp->getContentSize().width/2, currY - spriteUp->getContentSize().height/2));
	}
	else if(id == CARRIER_ID_BLACK_CLOUD ) 
	{
		spriteDown = CCSprite::create("tmx/wuyun1.png");
		CC_SAFE_RETAIN(spriteDown);
		checkWidth = spriteDown->getContentSize().width;
		checkHeight = spriteDown->getContentSize().height;
		spriteMiddle = CCSprite::create("tmx/wuyun2.png");
		CC_SAFE_RETAIN(spriteMiddle);
		spriteUp = CCSprite::create("tmx/wuyun3.png");
		CC_SAFE_RETAIN(spriteUp);
	}
}

void Carrier::upDateSelfPosition(void)
{
#ifdef								GOLDEN_MINER_2_VERSION_TIME
	double _currX = currX + vectorX * Global::getInstance()->getTimeRatio();
#else
	double _currX = currX + vectorX;
#endif

	if (_currX < 0)
	{
		vectorX = -vectorX;// 变向
		_currX = -_currX;
	}
	else if(_currX > (CCDirector::sharedDirector()->getWinSize().width - checkWidth))
	{
		_currX = (CCDirector::sharedDirector()->getWinSize().width - checkWidth) * 2 - _currX;
		vectorX = -vectorX;
	}

	if(id == CARRIER_ID_BLACK_CLOUD)
	{
		if (carriedTarget->count() > 0)
		{
			if(vectorX > 0)
			{
				if (((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getScaleX() > 0)
				{
					isJustChangeDirction = true;
					CCLOG("x = %f, y = %f, scale = %f", ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getPositionX(), ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getPositionY(),((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getScaleX());
					((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->setScaleX(-0.8);
					CCLOG("x = %f, y = %f, scale = %f", ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getPositionX(), ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getPositionY(),((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getScaleX());
					//((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->setPositionX(((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getPositionX() - ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getWidth()/2);

					//spriteDown->setPositionX(spriteDown->getPositionX() - ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getWidth()*2/3);
					//spriteMiddle->setPositionX(spriteMiddle->getPositionX() - ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getWidth()*2/3);
					//spriteUp->setPositionX(spriteUp->getPositionX() - ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getWidth()*2/3);
				}
				//spriteDown->setScaleX(-1);
				//spriteMiddle->setScaleX(-1);
				//spriteUp->setScaleX(-1);
			}
			else
			{
				if (((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getScaleX() < 0)
				{
					isJustChangeDirction = true;
					CCLOG("x = %f, y = %f, scale = %f", ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getPositionX(), ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getPositionY(),((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getScaleX());
					((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->setScaleX(0.8);
					CCLOG("x = %f, y = %f, scale = %f", ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getPositionX(), ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getPositionY(),((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getScaleX());
					//((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->setPositionX(((DynamicTarget *)carriedTarget->objectAtIndex(0))->getArmature()->getPositionX() + ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getWidth()/2);

					//spriteDown->setPositionX(spriteDown->getPositionX() + ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getWidth()*2/3);
					//spriteMiddle->setPositionX(spriteMiddle->getPositionX() + ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getWidth()*2/3);
					//spriteUp->setPositionX(spriteUp->getPositionX() + ((DynamicTarget *)carriedTarget->objectAtIndex(0))->getWidth()*2/3);
				}
				//spriteDown->setScaleX(1);
				//spriteMiddle->setScaleX(1);
				//spriteUp->setScaleX(1);
			}
		}
	}

	changeX = _currX - currX;
	currX = _currX;

	// 更新云朵的位置
	spriteDown->setPositionX(spriteDown->getPositionX() + changeX);
	spriteMiddle->setPositionX(spriteMiddle->getPositionX() + changeX);
	spriteUp->setPositionX(spriteUp->getPositionX() + changeX);
}

void Carrier::setCarrierTypeAndIndex(int _yunIndex, int _point1Scale, int _point2Scale, int _point3Scale)
{
	yunIndex = _yunIndex;

	pointType = _point1Scale + _point2Scale*10 + _point3Scale*100 + (_point1Scale + _point2Scale + _point3Scale)*1000;
}

double Carrier::getCurrY(void)
{
	return currY;
}

void Carrier::upDateCarriedTarget(void)
{
	if (carriedTarget != NULL)
	{
		if (id == CARRIER_ID_CLOUD)
		{
			upDateCarriedStaticTarget();
		}
		else if (id == CARRIER_ID_BLACK_CLOUD)
		{
			upDateCarriedDynamicTarget();
		}
	}
}

void Carrier::upDateCarriedStaticTarget(void)
{
	CCArray * removeIndexTarget = CCArray::create();
	CCArray * removeIndexDynamicTarget = CCArray::create();

	for (unsigned int i = 0; i < carriedTarget->count(); i++)
	{
		if(((CCInteger *)carriedTargetType->objectAtIndex(i))->getValue() == 0)
		{
			Target * tmp = (Target *)carriedTarget->objectAtIndex(i);
			if (tmp->getStatus() == TARGET_STATUS_CARRIED)
			//if ((tmp->getStatus() == TARGET_STATUS_CARRIED) || (tmp->getStatus() == TARGET_STATUS_MAGNETED))
			{
				removeIndexTarget->addObject(CCInteger::create(i));
			}
			else
			{
				tmp->setPositionX(tmp->getPositionX() + changeX);
			}
		}
		else
		{
			DynamicTarget * tmp = (DynamicTarget *)carriedTarget->objectAtIndex(i);
			if (tmp->getStatus() == DYNAMIC_TARGET_STATUS_CARRIED)
			//if ((tmp->getStatus() == DYNAMIC_TARGET_STATUS_CARRIED) || (tmp->getStatus() == DYNAMIC_TARGET_STATUS_GOURD))
			{
				removeIndexDynamicTarget->addObject(CCInteger::create(i));
			}
			else
			{
				tmp->getArmature()->setPositionX(tmp->getArmature()->getPositionX() + changeX);
			}
		}
	}
	// 移除该移除的对象
	for (unsigned int i = removeIndexTarget->count(); i >0; i--)
	{
		carriedTarget->removeObjectAtIndex(((CCInteger *)removeIndexTarget->objectAtIndex(i-1))->getValue());
		carriedTargetType->removeObjectAtIndex(((CCInteger *)removeIndexTarget->objectAtIndex(i-1))->getValue());
		removeIndexTarget->removeObjectAtIndex(i-1,true);
	}
	for (unsigned int i = removeIndexDynamicTarget->count(); i > 0; i--)
	{
		carriedTarget->removeObjectAtIndex(((CCInteger *)removeIndexDynamicTarget->objectAtIndex(i-1))->getValue());
		carriedTargetType->removeObjectAtIndex(((CCInteger *)removeIndexDynamicTarget->objectAtIndex(i-1))->getValue());
		removeIndexDynamicTarget->removeObjectAtIndex(i-1,true);
	}
}

void Carrier::upDateCarriedDynamicTarget(void)
{
	CCArray * removeIndexDynamicTarget = CCArray::create();

	for (unsigned int i = 0; i < carriedTarget->count(); i++)
	{
		DynamicTarget * tmp = (DynamicTarget *)carriedTarget->objectAtIndex(i);
		if ((tmp->getStatus() == DYNAMIC_TARGET_STATUS_CARRIED) || (tmp->getStatus() == DYNAMIC_TARGET_STATUS_GOURD))
		{
			removeIndexDynamicTarget->addObject(CCInteger::create(i));
		}
		else
		{
			tmp->getArmature()->setPositionX(tmp->getArmature()->getPositionX() + changeX);
		}
	}

	for (unsigned int i = removeIndexDynamicTarget->count(); i > 0; i--)
	{
		carriedTarget->removeObjectAtIndex(((CCInteger *)removeIndexDynamicTarget->objectAtIndex(i-1))->getValue());
		removeIndexDynamicTarget->removeObjectAtIndex(i-1,true);
	}
}

void Carrier::setTargetPositionByPointIndex(int _pointIndex, void * _target)
{
	if(_pointIndex == 1)
	{
		((Target *)_target)->setPosition(ccp(currX + (pointType%10 * checkWidth / (pointType/1000) / 2), currY + ((Target *)_target)->getContentSize().height/2));
		if (pointType%10 == 1)
		{
			if (((Target *)_target)->getId() == TARGET_ID_JEWEL_PURPLE)
			{
				((Target *)_target)->setPositionY(((Target *)_target)->getPositionY() + ((Target *)_target)->getContentSize().height*3/4);
			}
			else if (((Target *)_target)->getId() == TARGET_ID_FOOD)
			{
				((Target *)_target)->setPositionY(((Target *)_target)->getPositionY() + ((Target *)_target)->getContentSize().height*1/3);
			}
			else
			{
				((Target *)_target)->setPositionY(((Target *)_target)->getPositionY() + ((Target *)_target)->getContentSize().height/2);
			}
		}
	}
	else if(_pointIndex == 2)
	{
		((Target *)_target)->setPosition(ccp(currX + (pointType%10 * checkWidth / (pointType/1000)) + (pointType%100/10 * checkWidth / (pointType/1000) / 2), currY + ((Target *)_target)->getContentSize().height/2));
		if (pointType%100/10 == 1)
		{
			if (((Target *)_target)->getId() == TARGET_ID_JEWEL_PURPLE)
			{
				((Target *)_target)->setPositionY(((Target *)_target)->getPositionY() + ((Target *)_target)->getContentSize().height*3/4);
			}
			else if (((Target *)_target)->getId() == TARGET_ID_FOOD)
			{
				((Target *)_target)->setPositionY(((Target *)_target)->getPositionY() + ((Target *)_target)->getContentSize().height*1/3);
			}
			else
			{
				((Target *)_target)->setPositionY(((Target *)_target)->getPositionY() + ((Target *)_target)->getContentSize().height/2);
			}
		}
	}
	else if(_pointIndex == 3)
	{
		((Target *)_target)->setPosition(ccp(currX + checkWidth - (pointType%1000/100 * checkWidth / (pointType/1000) / 2), currY + ((Target *)_target)->getContentSize().height/2));
		if (pointType%1000/100 == 1)
		{
			if (((Target *)_target)->getId() == TARGET_ID_JEWEL_PURPLE)
			{
				((Target *)_target)->setPositionY(((Target *)_target)->getPositionY() + ((Target *)_target)->getContentSize().height*3/4);
			}
			else if (((Target *)_target)->getId() == TARGET_ID_FOOD)
			{
				((Target *)_target)->setPositionY(((Target *)_target)->getPositionY() + ((Target *)_target)->getContentSize().height*1/3);
			}
			else
			{
				((Target *)_target)->setPositionY(((Target *)_target)->getPositionY() + ((Target *)_target)->getContentSize().height/2);
			}
		}
	}
}
	
void Carrier::setDynamicTargetPositionByPointIndex(int _pointIndex, void * _target)
{
	if(_pointIndex == 1)
	{
		((DynamicTarget *)_target)->getArmature()->setPosition(ccp(currX + (pointType%10 * checkWidth / (pointType/1000) / 2), currY + ((DynamicTarget *)_target)->getHeight()*5/6));
	}
	else if(_pointIndex == 2)
	{
		((DynamicTarget *)_target)->getArmature()->setPosition(ccp(currX + (pointType%10 * checkWidth / (pointType/1000)) + (pointType%100/10 * checkWidth / (pointType/1000) / 2), currY + ((DynamicTarget *)_target)->getHeight()*5/6));
	}
	else if(_pointIndex == 3)
	{
		((DynamicTarget *)_target)->getArmature()->setPosition(ccp(currX + checkWidth - (pointType%1000/100 * checkWidth / (pointType/1000) / 2), currY + ((DynamicTarget *)_target)->getHeight()*5/6));
	}
}