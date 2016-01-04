#include "Hanger.h"
#include "Rope.h"
#include "Player.h"
#include "GameControl.h"

#define			HANGER_SPEED_CONTROL			10.0
#define			HANGER_SWAP_SPEED_CONTROL		2
#define			TARGET_CONTROL					2.0

#define			HANGER_SWAP_STOP_THROW_TIME		10

#define			HANGER_PULL_HACING_INTERTECT	5
#define			HANGER_PULL_START				5

Hanger::Hanger(double _distanceToCentre, double _distanceToRope, double _speedAngle, int _speedSelf, int _speedScene, int _type)//, const char _name[])//, cocos2d::CCRect _ccRect);
{
	CCSprite();

	functionType = HANGER_FUNCTION_TYPE_NORMAL;

	carryTargetPoint = NULL;
	carryTargetType = -1;
	speedTimes = 1.0;
	speedPet = 0;
	speedTargetType = 0;
	tmpStatusTimeCount = 0;
	distanceToCentre = _distanceToCentre;
	distanceToRope = _distanceToRope;
	speedAngle = _speedAngle;
	speedSelf = _speedSelf;
	speedScene = _speedScene;
	type = _type;
	speedTarget = 0;
	status = HANGER_STATUS_SWAYING;
	lastStatus = HANGER_STATUS_SWAYING;
	canThrow = true;
	//isHaveTarget = 0;
	if(speedAngle > 0)
	{
		angle = angleLeft;
	}
	else
	{
		angle = angleRight;
	}

	setScale(0.8);

	switch(Player::getInstance()->getSelectPet())
	{
	case PET_ELEMENT_JINGXIGUI:
		speedAngle += 1;
		break;
	case PET_ELEMENT_LINGGANDAWANG:
		speedScene += 5;
		break;
	case PET_ELEMENT_NIUMOWANG:
		speedScene += 10;
		//speedAngle -= 1;
		break;
	default:
		break;
	}

	//Global::getInstance()->setHangerAngle(angle);
	Global::getInstance()->setHangerStatus(status);
	//Global::getInstance()->setHangerDistanceToCentre(distanceToCentre);
	//Global::getInstance()->setHangerDistanceToRope(distanceToRope);
	//Global::getInstance()->setHangerCanThrow(canThrow);

	setAngle(angle);

	rope = new Rope(this);
	rope->retain();
	zhaDanSprite = NULL;

	autorelease();
}


Hanger::~Hanger(void)
{
}

void Hanger::onExit(void)
{
	CC_SAFE_RELEASE(rope);
}
	
Rope * Hanger::getRope(void)
{
	return rope;
}

void Hanger::setSpeedTimes(float _times)
{
	speedTimes = _times;
}

int Hanger::setSpeedTarget(int _speedTarget, int _speedTargetType)
{
	speedTarget = _speedTarget;
	speedTargetType = _speedTargetType;

	//CCLOG("speedTargetType = %d", speedTargetType);
	return speedTarget;
}

void Hanger::setPetSpeed(int _speed)
{
	speedPet = _speed;
}

int Hanger::getStatus(void)
{
	return status;
}

bool Hanger::getCanThrow(void)
{
	return canThrow;
}
	
double Hanger::getAngle(void)
{
	return angle;
}

void Hanger::setAngle(double _angle)
{
	angle = _angle;
	changeBitmap();
	setSwayPostion();
}
	
double Hanger::getCurrX(void)
{
	return currX;
}
	
double Hanger::getCurrY(void)
{
	return currY;
}

double Hanger::getDistanceToRope(void)
{
	return distanceToRope;
}

double Hanger::getDistanceToCentre(void)
{
	return distanceToCentre;
}

int Hanger::getFunctionType(void)
{
	return functionType;
}

void Hanger::setFunctionType(int _functionType)
{
	functionType = _functionType;
}

void Hanger::setType(int _type)
{
	type = _type;
}

void Hanger::resetHangerBitmap(const char _name[], double _distanceToCentre, double _distanceToRope, int _functionType)
{
	//CCLOG("width = %f, height = %f", getContentSize().width, getContentSize().height);
	distanceToCentre = _distanceToCentre;
	distanceToRope = _distanceToRope;
	functionType = _functionType;
	initWithFile(_name);
	//CCLOG("width = %f, height = %f", getContentSize().width, getContentSize().height);
	//Global::getInstance()->setHangerDistanceToCentre(_distanceToCentre);
	//Global::getInstance()->setHangerDistanceToRope(_distanceToRope);
}


int Hanger::setStatus(int _status)
{
	// 连击相关处理
	if (_status == HANGER_STATUS_PULL_HAVING)
	{	
		Player::getInstance()->getMusicControl()->stopEffect(MUSICCONTROL_EFFECT_ID_PULL);
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_PULL);
		
		tmpStatusTimeCount = HANGER_PULL_HACING_INTERTECT + HANGER_PULL_START;

		// 换图
		rope->changeImageByStatus(ROPE_STATUS_INTERSECT, this);

		if (type == 0)
		{
			//只要抓住过就计数1次
			Global::getInstance()->setContinuesCount(1);
		}
	}
	else if (_status == HANGER_STATUS_PULL_UNHAVING)
	{
		Player::getInstance()->getMusicControl()->stopEffect(MUSICCONTROL_EFFECT_ID_PULL);
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_PULL);
		
		tmpStatusTimeCount =  HANGER_PULL_START;

		// 换图
		rope->changeImageByStatus(ROPE_STATUS_PULL, this);

		if (type == 0)
		{
			if (status == HANGER_STATUS_THROW)
			{ // 放空就重新计数
				Global::getInstance()->initContinuesCount(); 
			}
			else
			{ //只要抓住过就计数1次
				Global::getInstance()->setContinuesCount(1);
			}
		}
	}
	else if (_status == HANGER_STATUS_THROW)
	{
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_THROW);

		// 换图
		rope->changeImageByStatus(ROPE_STATUS_THROW, this);
	}
	else if (_status == HANGER_STATUS_SWAYING)
	{
		Player::getInstance()->getMusicControl()->stopEffect(MUSICCONTROL_EFFECT_ID_PULL);
		if (status == HANGER_STATUS_PULL_HAVING)
		{
			Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_GET_TARGET);
		}
		rope->changeImageByStatus(ROPE_STATUS_NORMAL, this);
		canThrow = false;
	}

	lastStatus = status;
	status = _status;
	Global::getInstance()->setHangerStatus(status);
	return status;
}

//unsigned char Hanger::setIsHaveTarget(unsigned char _isHaveTarget)
//{
//	isHaveTarget = _isHaveTarget;
//	return isHaveTarget;
//}	

void Hanger::doAction(float _f, GameControl * _gameControl)
{
	switch(status)
	{
	case HANGER_STATUS_SWAYING:
#ifdef							GOLDEN_MINER_2_VERSION_TIME
		if(tmpStatusTimeCount <= 0)
		{
			canThrow = true;
			//Global::getInstance()->setHangerCanThrow(canThrow);
		}
		else
		{
			tmpStatusTimeCount -= _f*SCHEDULE_TIMES;
		}
#else
		if(tmpStatusTimeCount == 0)
		{
			canThrow = true;
			//Global::getInstance()->setHangerCanThrow(canThrow);
		}
		else
		{
			tmpStatusTimeCount--;
		}
#endif
		// 钩子摇摆状态要改变角度 以及图片显示
		changeAngle();
		//setSwayPostion();
		break;
	case HANGER_STATUS_THROW:
		setMovePostion(_gameControl);
		intersectCheck(_gameControl);
		break;
	case HANGER_STATUS_PULL_HAVING:
#ifdef							GOLDEN_MINER_2_VERSION_TIME
		if(tmpStatusTimeCount <= 0)
		{
			setMovePostion(_gameControl);
		}
		else
		{
			tmpStatusTimeCount -= _f*SCHEDULE_TIMES;
			if((tmpStatusTimeCount <= HANGER_PULL_START) && ((tmpStatusTimeCount+_f*SCHEDULE_TIMES) >= HANGER_PULL_START))
			{
				// 换图
				rope->changeImageByStatus(ROPE_STATUS_PULL, this);
			}
			else if((tmpStatusTimeCount <= 0) && ((tmpStatusTimeCount+_f*SCHEDULE_TIMES) >= 0))
			{
				// 换图
				rope->changeImageByStatus(ROPE_STATUS_NORMAL, this);
			}
		}
#else
		if(tmpStatusTimeCount == 0)
		{
			setMovePostion(_gameControl);
		}
		else
		{
			tmpStatusTimeCount--;
			if(tmpStatusTimeCount == HANGER_PULL_START)
			{
				// 换图
				rope->changeImageByStatus(ROPE_STATUS_PULL, this);
			}
			else if(tmpStatusTimeCount == 0)
			{
				// 换图
				rope->changeImageByStatus(ROPE_STATUS_NORMAL, this);
			}
		}
#endif
		break;
	case HANGER_STATUS_PULL_UNHAVING:
		// 出钩子/收钩子 只有位置变化
		//CCLOG("Hanger doAction: status = %d", status);
#ifdef									GOLDEN_MINER_2_VERSION_TIME
		if(tmpStatusTimeCount < 0)
		{
			setMovePostion(_gameControl);
		}
		else
		{
			tmpStatusTimeCount -= _f*SCHEDULE_TIMES;
			if((tmpStatusTimeCount <= 0) && ((tmpStatusTimeCount+_f*SCHEDULE_TIMES) >= 0))
			{
				// 换图
				rope->changeImageByStatus(ROPE_STATUS_NORMAL, this);
			}
		}
#else
		if(tmpStatusTimeCount == 0)
		{
			setMovePostion(_gameControl);
		}
		else
		{
			tmpStatusTimeCount--;
			if(tmpStatusTimeCount == 0)
			{
				// 换图
				rope->changeImageByStatus(ROPE_STATUS_NORMAL, this);
			}
		}
#endif
		setMovePostion(_gameControl);
		break;
	case HANGER_STATUS_PAUSE:
		break;
	default:
		// 不能出现其他状态 有错误
		break;
	}

	rope->doAction(_f, this);
}

//bool Hanger::getCanThrow(void)
//{
//	return canThrow;
//}

double Hanger::getSpeedAngle(void)
{
	return speedAngle;
}

void Hanger::setSpeedAngle(double _s)
{
	speedAngle = _s;
}

void Hanger::appendSpeedSelf(int _append)
{
	speedSelf += _append;
}

void Hanger::changeAngle(void)
{
#ifdef						GOLDEN_MINER_2_VERSION_TIME
	double nextAngle = angle + speedAngle/HANGER_SWAP_SPEED_CONTROL*Global::getInstance()->getTimeRatio();
#else
	double nextAngle = angle + speedAngle/HANGER_SWAP_SPEED_CONTROL;
#endif

	if(nextAngle > angleRight)
	{
		angle = angleRight * 2 - nextAngle;
		speedAngle = -speedAngle;
	}
	else if(nextAngle < angleLeft)
	{
		angle = angleLeft * 2 - nextAngle;
		speedAngle = -speedAngle;
	}
	else 
	{
		angle = nextAngle;
	}

	changeBitmap();
	setSwayPostion();
	//CCLOG("Hanger: angle= %f", angle);
	//Global::getInstance()->setHangerAngle(angle);
}

void Hanger::changeBitmap(void)
{
	this->setRotation(angleCenter - angle);// + 45);
}

void Hanger::setMovePostion(GameControl * _gameControl)
{
	//unsigned char res = 0;
#ifdef									GOLDEN_MINER_2_VERSION_TIME 
	double speed = getSpeed() / HANGER_SPEED_CONTROL * Global::getInstance()->getTimeRatio();
#else
	double speed = getSpeed() / HANGER_SPEED_CONTROL;
#endif

	double speedX = 0;
	double speedY = 0;
	if((status == HANGER_STATUS_PULL_UNHAVING) || (status == HANGER_STATUS_PULL_HAVING))
	{
		speedX = speed * cos((angle - angleChange) / angleChange * pi);
		speedY = speed * sin((angle - angleChange) / angleChange * pi);
		currX += speedX;
		currY += speedY;

		if(currY >= y) 
		{
			// 收回
			//setStatus(HANGER_STATUS_SWAYING_STOP_THROW);
			//Global::getInstance()->setHangerCanThrow(canThrow);
			currX = x;
			currY = y;

			if (status == HANGER_STATUS_PULL_HAVING)
			{
				_gameControl->addExplode(HANGER_GOT_AWARD, currX, currY);
			}
			tmpStatusTimeCount = HANGER_SWAP_STOP_THROW_TIME;
			setStatus(HANGER_STATUS_SWAYING);
		}
	}
	else
	{
		speedX = speed * cos(angle / angleChange * pi);
		speedY = speed * sin(angle / angleChange * pi);
		currX += speedX;
		currY += speedY;

		if((currY < 0) || (currX < 0) || (currX > CCDirector::sharedDirector()->getWinSize().width))
		{
			// 放空
			Player::getInstance()->getMusicControl()->stopEffect(MUSICCONTROL_EFFECT_ID_THROW);
			setStatus(HANGER_STATUS_PULL_UNHAVING);
		}
	}

	setPosition(CCPoint(currX, currY));
	//Global::getInstance()->setHangerCurrX(currX);
	//Global::getInstance()->setHangerCurrY(currY);
	//return res;
}

void Hanger::setSwayPostion(void)
{
	x = Global::getInstance()->getcentreX() + distanceToCentre * cos(angle / angleChange * pi);
	y = Global::getInstance()->getcentreY() + distanceToCentre * sin(angle / angleChange * pi);
	currX = x;
	currY = y;

	setPosition(CCPoint(currX, currY));
	//Global::getInstance()->setHangerCurrX(currX);
	//Global::getInstance()->setHangerCurrY(currY);
	//Global::getInstance()->setHangerStartX(x);
	//Global::getInstance()->setHangerStartY(y);
}

float Hanger::getSpeed(void)
{
	float res = 0;
	//基本速度
	if (status == HANGER_STATUS_THROW)
	{
		res = HANGER_SPEED_PULL_NORMAL;
	}
	else
	{
		if (speedScene == 0)
		{
			res = speedSelf;
		}
		else
		{
			if (status == HANGER_STATUS_PULL_HAVING)
			{
				res = (speedSelf + speedScene - speedTarget)*TARGET_CONTROL/speedTargetType + speedPet;
			}
			else if (status == HANGER_STATUS_PULL_UNHAVING)
			{
				res = (speedSelf + speedScene)*TARGET_CONTROL + speedPet;
			}
		}
	}

	if(res < 0) 
	{
		//如果速度小于0有错误
		return 0;
	}
	return res*speedTimes;
}

void Hanger::intersectCheck(GameControl * _gameControl)
{
	// 只有钩子是丢出状态才能去抓取物品
	bool flag = true;

	CCRect rHanger = cocos2d::CCRectMake(
		getPosition().x - (getContentSize().width - INTERSECT_CONTROL)/2,
		getPosition().y - (getContentSize().height - INTERSECT_CONTROL)/2,
		getContentSize().width - INTERSECT_CONTROL,
		getContentSize().height - INTERSECT_CONTROL);
		
	// 钩子碰撞矩阵
	if (_gameControl->gate->getTargets() != NULL)	
	{
		// 遍历固定对象
		for(unsigned int i = 0; i < _gameControl->gate->getTargets()->count(); i++)
		{
			Target * tmp = (Target *)_gameControl->gate->getTargets()->objectAtIndex(i);
			if (tmp->isCanCarry())// 目标是可抓取的状态
			{
				// 抓取目标的碰撞矩阵
				CCRect rTmp = cocos2d::CCRectMake(
					tmp->getPosition().x - (tmp->getContentSize().width - INTERSECT_CONTROL)/2,
					tmp->getPosition().y - (tmp->getContentSize().height - INTERSECT_CONTROL)/2,
					tmp->getContentSize().width - INTERSECT_CONTROL,
					tmp->getContentSize().height - INTERSECT_CONTROL);
				if(rHanger.intersectsRect(rTmp))
				{
					flag = false;
					//Player::getInstance()->getMusicControl()->stopEffect(MUSICCONTROL_EFFECT_ID_THROW);
					//Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_CARRY_TARGET);
					tmp->intersectByHanger(_gameControl, this);
				}
			}
			if (!flag)
			{
				if (functionType != HANGER_FUNCTION_TYPE_THROW)
				{
					Player::getInstance()->getMusicControl()->stopEffect(MUSICCONTROL_EFFECT_ID_THROW);
					Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_CARRY_TARGET);
					break;
				}
				else
				{
					if (status == HANGER_STATUS_PULL_HAVING)
					{
						Player::getInstance()->getMusicControl()->stopEffect(MUSICCONTROL_EFFECT_ID_THROW);
					}
					else
					{
						flag = true;
						Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_CARRY_TARGET);
					}
				}
			}
		}
	}
		// 遍历移动对象
	if (_gameControl->gate->getDynamicTargets() != NULL)
	{		
		if (flag)
		{
			for(unsigned int i = 0; i < _gameControl->gate->getDynamicTargets()->count(); i++)
			{
				DynamicTarget * tmp = (DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i);
				if (tmp->isCanCarried())// 可抓取状态
				{
					CCRect rTmp = cocos2d::CCRectMake(
						tmp->getArmature()->getPositionX() - (tmp->getWidth() - INTERSECT_CONTROL)/2,
						tmp->getArmature()->getPositionY() - (tmp->getHeight() - INTERSECT_CONTROL)/2,
						tmp->getWidth() - INTERSECT_CONTROL,
						tmp->getHeight() - INTERSECT_CONTROL);
					if(rHanger.intersectsRect(rTmp))
					{
						flag = false;
						//Player::getInstance()->getMusicControl()->stopEffect(MUSICCONTROL_EFFECT_ID_THROW);
						//Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_CARRY_TARGET);
						tmp->doIntersectWithHanger(_gameControl, this);
					}
				}
				if (!flag)
				{
					if (functionType != HANGER_FUNCTION_TYPE_THROW)
					{
						Player::getInstance()->getMusicControl()->stopEffect(MUSICCONTROL_EFFECT_ID_THROW);
						Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_CARRY_TARGET);
						break;
					}
					else
					{
						if (status == HANGER_STATUS_PULL_HAVING)
						{
							Player::getInstance()->getMusicControl()->stopEffect(MUSICCONTROL_EFFECT_ID_THROW);
						}
						else
						{
							flag = true;
							Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_CARRY_TARGET);
						}
					}
				}
			}
		}
	}

	if (!flag)
	{
		if (status == HANGER_STATUS_PULL_HAVING)
		{
			if (carryTargetPoint != NULL)
			{
				if(carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
				{
					if (((Target *)carryTargetPoint)->getId() == TARGET_ID_STONE_B)
					{
						_gameControl->setLiuGuangVisiable(SKILL_ID_GRENADE-1, true);
					}
					else if (((Target *)carryTargetPoint)->getId() == TARGET_ID_GOLDEN_B)
					{
						_gameControl->setLiuGuangVisiable(SKILL_ID_VIGOROUSLY_PILL-1, true);
					}
					
					setSpeedTarget(((Target *)carryTargetPoint)->getSpeed(), ((Target *)carryTargetPoint)->getSpeedType());
					_gameControl->addExplode(HANGER_EXPLODE, currX, currY);
				}
				else if (carryTargetType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
				{
					setSpeedTarget(((DynamicTarget *)carryTargetPoint)->getSpeed(), ((DynamicTarget *)carryTargetPoint)->getSpeedType());
					_gameControl->addExplode(HANGER_EXPLODE, currX, currY);
				}
			}
			else
			{
				CCLOG("严重错误，钩子撞到物品，但是携带的指针存储为空");
			}
		}
	}
}


int Hanger::getSpeedSelf(void)
{
	return speedSelf;
}

int Hanger::getSpeedScene(void)
{
	return speedScene;
}

void Hanger::setSpeedSelf(int _s)
{
	speedSelf = _s;
}

void Hanger::setSpeedScene(int _s)
{
	speedScene = _s;
}