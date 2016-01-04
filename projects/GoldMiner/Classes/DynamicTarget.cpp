#include "DynamicTarget.h"
#include "GameControl.h"
#include "Hanger.h"

#define    MOVE_CONTROL											10
#define    DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT				20
#define    DYANMIC_TARGET_SKILL_DISPLAY_TIME_COUNT				60*3

#define	   DYANMIC_TARGET_DIZZY_POSITIONY_CONTROL				8
#define	   DYANMIC_TARGET_DIZZY_POSITIONX_CONTROL				12

#define	   DYANMIC_MOVE2_STOP_CONTROl							3*60

USING_NS_CC;
using namespace cs;

const double moveDeviation = 15;// 确定是否到达移动点的检测范围

DynamicTarget::DynamicTarget(int _id, int _type, double _x, double _y)
{
	movePointCount = 0;
	id = _id;
	type = _type;
	currX = _x;
	currY = _y;
	canCarry = true;
	canMove = true;
	moveSpeed = 0;
	armature = NULL;
	timeDisplayCount = 0;
	vectorX = 0;
	vectorY = 0;
	minMoveX = 0;
	maxMoveX = CCDirector::sharedDirector()->getWinSize().width;

	autorelease();
}

DynamicTarget::~DynamicTarget(void)
{
	CC_SAFE_RELEASE(armature);
	//CC_SAFE_RELEASE(hanger);
}

void DynamicTarget::doAction(float _f, GameControl * _gameControl)
{
}

void DynamicTarget::recoverLastStatus(void)
{
	setStatus(lastStatus, NULL);
}

float DynamicTarget::getDistance(void)
{
	distance = sqrt(vectorX*vectorX + vectorY*vectorY);
	return distance;
}

void DynamicTarget::setStatus(int _status, Hanger * _hanger)
{
}

int DynamicTarget::getSpeed(void)
{
	return 0;
}

int DynamicTarget::getSpeedType(void)
{
	return TARGET_SPEED_TYPE_S;
}

int DynamicTarget::getStatus(void)
{
	return status;
}

int DynamicTarget::getType(void)
{
	return type;
}

bool DynamicTarget::isIntersectById(int _id)
{
	return false;
}

void DynamicTarget::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger)
{
	if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)
	{		
		if (_hanger->getFunctionType() == HANGER_FUNCTION_TYPE_CARRY_BOMB || _hanger->getFunctionType() == HANGER_FUNCTION_TYPE_EXCHANGE_TO_JEWEL)
		{
			hanger = _hanger;

			_hanger->carryTargetType = GAMECONTROL_TYPE_TARGET_DYNAMIC;
			_hanger->carryTargetPoint = this;
			setStatus(DYNAMIC_TARGET_STATUS_CARRIED, _hanger);
			_hanger->setStatus(HANGER_STATUS_PULL_HAVING);
			_gameControl->role->setStatus(ROLE_STATUS_PULL_HAVING);
		}
		else
		{
			// 添加爆炸
			_gameControl->addExplode(S_EXPLODE, armature->getPositionX(), armature->getPositionY());

			setStatus(DYNAMIC_TARGET_STATUS_REMOVE, NULL);
			if (_hanger->getFunctionType() != HANGER_FUNCTION_TYPE_THROW)
			{
				_hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
				_gameControl->role->setStatus(ROLE_STATUS_PULL_UNHAVING);
			}

			if (_gameControl->gate->getTargets() != NULL)
			{
				for (unsigned int i = 0; i < _gameControl->gate->getTargets()->count(); i++)
				{
					Target * tmp = (Target *)_gameControl->gate->getTargets()->objectAtIndex(i);
					if(Global::getInstance()->isInCircle(tmp->getPositionX(), tmp->getPositionY(), armature->getPositionX(), armature->getPositionY(), BOMB_CIRCLE)
						&& (tmp->getStatus() != TARGET_STATUS_REMOVE)
						&& (tmp->getStatus() != TARGET_STATUS_GOT_REMOVE))
					{
						tmp->intersectByBomb(_gameControl);
					}
				}
			}

			unsigned int j = _gameControl->gate->getDynamicTargets()->indexOfObject(this);
			for (unsigned int i = 0; i < _gameControl->gate->getDynamicTargets()->count(); i++)
			{
				if (i != j)
				{
					DynamicTarget * tmp = (DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i);
					if(Global::getInstance()->isInCircle(tmp->getArmature()->getPositionX(), tmp->getArmature()->getPositionY(), armature->getPositionX(), armature->getPositionY(), BOMB_CIRCLE)
						&& (tmp->getStatus() != DYNAMIC_TARGET_STATUS_CARRIED)
						&& (tmp->getStatus() != DYNAMIC_TARGET_STATUS_GOT_REMOVE)
						&& (tmp->getStatus() != DYNAMIC_TARGET_STATUS_REMOVE)
						&& (tmp->getStatus() != DYNAMIC_TARGET_STATUS_DESTORY))
					{
						tmp->intersectWithTarget(TARGET_ID_BOMB, NULL, _gameControl);
					}
				}
			}
		}
	}
	else
	{
		if (_hanger->getFunctionType() == HANGER_FUNCTION_TYPE_THROW)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, _hanger);
			_gameControl->addExplode(HANGER_EXPLODE, _hanger->getCurrX(), _hanger->getCurrY());
		}
		else if (_hanger->getFunctionType() == HANGER_FUNCTION_TYPE_BOMB)
		{			
			_gameControl->addExplode(B_EXPLODE, _hanger->getCurrX(), _hanger->getCurrY());

			_hanger->setStatus(HANGER_STATUS_PULL_HAVING);
			Global::getInstance()->setContinuesCount(-1);
			setStatus(DYNAMIC_TARGET_STATUS_REMOVE, NULL);
			_hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
			_gameControl->role->setStatus(ROLE_STATUS_PULL_UNHAVING);
		}
		else
		{
			hanger = _hanger;

			_hanger->carryTargetType = GAMECONTROL_TYPE_TARGET_DYNAMIC;
			_hanger->carryTargetPoint = this;
			setStatus(DYNAMIC_TARGET_STATUS_CARRIED, NULL);
			_hanger->setStatus(HANGER_STATUS_PULL_HAVING);
			_gameControl->role->setStatus(ROLE_STATUS_PULL_HAVING);
		}
	}
}

void DynamicTarget::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)
{
	if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)
	{
		// 添加爆炸
		_gameControl->addExplode(S_EXPLODE, armature->getPositionX(), armature->getPositionY());

		setStatus(DYNAMIC_TARGET_STATUS_REMOVE, NULL);
		if (_gameControl->gate->getTargets() != NULL)
		{
			for (unsigned int i = 0; i < _gameControl->gate->getTargets()->count(); i++)
			{
				Target * tmp = (Target *)_gameControl->gate->getTargets()->objectAtIndex(i);
				if(Global::getInstance()->isInCircle(tmp->getPositionX(), tmp->getPositionY(), armature->getPositionX(), armature->getPositionY(), BOMB_CIRCLE)
					&& (tmp->getStatus() != TARGET_STATUS_CARRIED)
					&& (tmp->getStatus() != TARGET_STATUS_REMOVE)
					&& (tmp->getStatus() != TARGET_STATUS_GOT_REMOVE))
				{
					tmp->intersectByBomb(_gameControl);
				}
			}
		}

		unsigned int j = _gameControl->gate->getDynamicTargets()->indexOfObject(this);
		for (unsigned int i = 0; i < _gameControl->gate->getDynamicTargets()->count(); i++)
		{
			if (i != j)
			{
				DynamicTarget * tmp = (DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i);
				if(Global::getInstance()->isInCircle(tmp->getArmature()->getPositionX(), tmp->getArmature()->getPositionY(),armature->getPositionX(), armature->getPositionY(), BOMB_CIRCLE)
					&& (tmp->getStatus() != DYNAMIC_TARGET_STATUS_CARRIED)
					&& (tmp->getStatus() != DYNAMIC_TARGET_STATUS_GOT_REMOVE)
					&& (tmp->getStatus() != DYNAMIC_TARGET_STATUS_REMOVE)
					&& (tmp->getStatus() != DYNAMIC_TARGET_STATUS_DESTORY))
				{
					tmp->intersectWithTarget(TARGET_ID_BOMB, NULL, _gameControl);
				}
			}
		}
	}
	else
	{
		if (_id == TARGET_ID_BOMB)
		{
			setStatus(DYNAMIC_TARGET_STATUS_REMOVE, NULL);
			if (_target != NULL)
			{// 为NULL  起始只是叫动态目标消失而已(且是碰撞或炸弹引起)
				_target->intersectByBomb(_gameControl);
			}
		}	
	}
}

void DynamicTarget::intersectWithDynamicTarget(int _id, DynamicTarget * _target, GameControl * _gameControl)
{
	if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)
	{
		// 添加爆炸
		_gameControl->addExplode(S_EXPLODE, armature->getPositionX(), armature->getPositionY());
		setStatus(DYNAMIC_TARGET_STATUS_REMOVE, NULL);

		if (_gameControl->gate->getTargets() != NULL)
		{
			for (unsigned int i = 0; i < _gameControl->gate->getTargets()->count(); i++)
			{
				Target * tmp = (Target *)_gameControl->gate->getTargets()->objectAtIndex(i);
				if(Global::getInstance()->isInCircle(tmp->getPositionX(), tmp->getPositionY(), armature->getPositionX(), armature->getPositionY(), BOMB_CIRCLE)
					&& (tmp->getStatus() != TARGET_STATUS_CARRIED)
					&& (tmp->getStatus() != TARGET_STATUS_REMOVE)
					&& (tmp->getStatus() != TARGET_STATUS_GOT_REMOVE))
				{
					tmp->intersectByBomb(_gameControl);
				}
			}
		}

		unsigned int j = _gameControl->gate->getDynamicTargets()->indexOfObject(this);
		for (unsigned int i = 0; i < _gameControl->gate->getDynamicTargets()->count(); i++)
		{
			if (i != j)
			{
				DynamicTarget * tmp = (DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i);
				if(Global::getInstance()->isInCircle(tmp->getArmature()->getPositionX(), tmp->getArmature()->getPositionY(), armature->getPositionX(), armature->getPositionY(), BOMB_CIRCLE)
					&& (tmp->getStatus() != DYNAMIC_TARGET_STATUS_CARRIED)
					&& (tmp->getStatus() != DYNAMIC_TARGET_STATUS_GOT_REMOVE)
					&& (tmp->getStatus() != DYNAMIC_TARGET_STATUS_REMOVE)
					&& (tmp->getStatus() != DYNAMIC_TARGET_STATUS_DESTORY))
				{
					tmp->intersectWithTarget(TARGET_ID_BOMB, NULL, _gameControl);
				}
			}
		}
	}
	else
	{
		if (_target->getType() == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)
		{
			setStatus(TARGET_STATUS_REMOVE, NULL);
			_target->intersectWithTarget(TARGET_ID_BOMB, NULL, _gameControl);
		}	
		else 
		{
			if (id == DYNAMIC_ID_LINGGANDAWANG)
			{
				_target->setStatus(DYNAMIC_TARGET_STATUS_REMOVE, NULL);
				setStatus(DYNAMIC_TARGET_STATUS_SKILL, NULL);
			}
			else if (id == DYNAMIC_ID_NIUMOWANG)
			{
				_target->setStatus(DYNAMIC_TARGET_STATUS_REMOVE, NULL);
				setStatus(DYNAMIC_TARGET_STATUS_SKILL, NULL);
			} 
			else
			{
				if (_id == DYNAMIC_ID_LINGGANDAWANG)
				{
					setStatus(DYNAMIC_TARGET_STATUS_REMOVE, NULL);
					_target->setStatus(DYNAMIC_TARGET_STATUS_SKILL, NULL);
				}
				else if (_id == DYNAMIC_ID_NIUMOWANG)
				{
					setStatus(DYNAMIC_TARGET_STATUS_REMOVE, NULL);
					_target->setStatus(DYNAMIC_TARGET_STATUS_SKILL, NULL);
				} 
			}
		}
	}
}

bool DynamicTarget::isCanCarried(void)
{
	return canCarry;
}
	
void DynamicTarget::setMove(int _movePointCount, double _movePointX[], double _movePointY[])
{
	// 可以移动的怪物的移动设置
	// 速度	有几个移动点	对应移动点的x坐标和y坐标
	//moveSpeed = _moveSpeed;

	movePointCount = _movePointCount;

	currMovePointIndex = 0;
	nextMovePointIndex = 1;

	minMoveX = _movePointX[0];
	maxMoveX = _movePointX[0];

	for (int i = 0; i < _movePointCount; i++)
	{
		//if ((_movePointX[i]-width/2) < 0)
		//{
		//	movePointX[i] = -(_movePointX[i]-width/2)+width/2;
		//}
		//else if((_movePointX[i]-width/2) > (CCDirector::sharedDirector()->getWinSize().width - width))
		//{
		//	movePointX[i] = (CCDirector::sharedDirector()->getWinSize().width - width) * 2 - (_movePointX[i]-width/2) + width/2;
		//}
		//else
		//{
			movePointX[i] = _movePointX[i];

			if (_movePointX[i] > maxMoveX)
			{
				maxMoveX = _movePointX[i];
			}
			if (_movePointX[i] < minMoveX)
			{
				minMoveX = _movePointX[i];
			}
		//}
		//if ((_movePointY[i]-height/2) < 0)
		//{
		//	movePointY[i] = -(_movePointY[i]-height/2)+height/2;
		//}
		//else if((_movePointY[i]-height/2) > (Global::getInstance()->getHangerStartY() - height))
		//{
		//	movePointY[i] = (Global::getInstance()->getHangerStartY() - height) * 2 - (_movePointY[i]-height/2) + height/2;
		//}
		//else
		//{
			if (i > 0)
			{
				movePointY[i] = 450 - _movePointY[i];
			}
			else
			{
				movePointY[i] = _movePointY[i];
			}
			//CCLOG("i = %d, movePointX = %f, movePointY = %f, CCDirector::sharedDirector()->getWinSize().height = %f", i , movePointX[i], movePointY[i], CCDirector::sharedDirector()->getVisibleSize().height );
		//}
	}

	setAngle();
}

double DynamicTarget::getCurrX(void)
{
	return currX;
}

double DynamicTarget::getCurrY(void)
{
	return currY;
}

double DynamicTarget::getWidth(void)// 获得宽度
{
	return width;
}
	
double DynamicTarget::getHeight(void)// 获得高度
{
	return height;
}

int DynamicTarget::getId(void)
{
	return id;
}

double DynamicTarget::getMoveSpeed(void)
{
	return moveSpeed;
}


cs::Armature* DynamicTarget::getArmature(void)
{
	return armature;
}

void DynamicTarget::getAwards(void)
{
}

bool DynamicTarget::actionMove(void)
{
	bool res = false;
	//currX += moveVectorX;
	//currY += moveVectorY;
	//armature->setPosition(currX ,currY);
#ifdef							GOLDEN_MINER_2_VERSION_TIME
	double _currX = currX + moveVectorX * Global::getInstance()->getTimeRatio();
#else
	double _currX = currX + moveVectorX;
#endif
	if (_currX < (minMoveX + width/2))//((_currX-width/2) < minMoveX)
	{
		if (moveVectorX < 0)
		{
			moveVectorX = -moveVectorX;// 变向
		}
		_currX =(minMoveX + width/2)*2 - _currX;//minMoveX* 2 -(_currX-width/2)+width/2;
		armature->setScaleX(-0.8);
		res = true;
	}
	else if(_currX > (maxMoveX + width/2))//((_currX-width/2) > (maxMoveX - width))
	{
		_currX = (maxMoveX + width/2)*2 - _currX;//maxMoveX* 2 - (_currX-width/2) + width/2;
		if (moveVectorX > 0)
		{
			moveVectorX = -moveVectorX;
		}
		armature->setScaleX(0.8);
		res = true;
	}

	currX = _currX;

	armature->setPosition(currX ,currY);

	return res;
}

void DynamicTarget::actionMove2(float _f)
{
#ifdef							GOLDEN_MINER_2_VERSION_TIME
	moveTimeCount += _f;

	if(moveTimeCount*SCHEDULE_TIMES <= moveTimeSum)
	{
		currX = movePointX[currMovePointIndex] + (movePointX[nextMovePointIndex] - movePointX[currMovePointIndex])*moveTimeCount*SCHEDULE_TIMES/moveTimeSum;
		currY = movePointY[currMovePointIndex] + (movePointY[nextMovePointIndex] - movePointY[currMovePointIndex])*moveTimeCount*SCHEDULE_TIMES/moveTimeSum;

		armature->setPosition(currX ,currY);
	}
	else if(moveTimeCount*SCHEDULE_TIMES >= moveTimeSum + DYANMIC_MOVE2_STOP_CONTROl)
	{
		// 获得下一次的移动位置
		int ram = rand()%movePointCount;
		if(ram == nextMovePointIndex)
		{
			ram = (ram + 1) % movePointCount;
		}

		currMovePointIndex = nextMovePointIndex;
		nextMovePointIndex = ram;
		setAngle2();
	}
#else
	moveTimeCount++;

	if(moveTimeCount <= moveTimeSum)
	{
		currX = movePointX[currMovePointIndex] + (movePointX[nextMovePointIndex] - movePointX[currMovePointIndex])*moveTimeCount/moveTimeSum;
		currY = movePointY[currMovePointIndex] + (movePointY[nextMovePointIndex] - movePointY[currMovePointIndex])*moveTimeCount/moveTimeSum;

		armature->setPosition(currX ,currY);
	}
	else if(moveTimeCount >= moveTimeSum + DYANMIC_MOVE2_STOP_CONTROl)
	{
		// 获得下一次的移动位置
		int ram = rand()%movePointCount;
		if(ram == nextMovePointIndex)
		{
			ram = (ram + 1) % movePointCount;
		}

		currMovePointIndex = nextMovePointIndex;
		nextMovePointIndex = ram;
		setAngle2();
	}
#endif

	//bool flag = false; 
	//double _currX = currX + moveVectorX;
	//if ((_currX-width/2) < 0)
	//{
	//	moveVectorX = -moveVectorX;// 变向
	//	_currX = -(_currX-width/2)+width/2;
	//	flag = true;
	//	armature->setScaleX(-0.8);
	//}
	//else if((_currX-width/2) > (CCDirector::sharedDirector()->getWinSize().width - width))
	//{
	//	_currX = (CCDirector::sharedDirector()->getWinSize().width - width) * 2 - (_currX-width/2) + width/2;
	//	moveVectorX = -moveVectorX;
	//	flag = true;
	//	armature->setScaleX(0.8);
	//}
	//double _currY = currY + moveVectorY;
	//if ((_currY-height/2) < 0)
	//{
	//	moveVectorY = -moveVectorY;// 变向
	//	_currY = -(_currY-height/2)+height/2;
	//	flag = true;
	//}
	//else if((_currY-height/2) > (Global::getInstance()->getHangerStartY() - height))
	//{
	//	_currY = (Global::getInstance()->getHangerStartY() - height) * 2 - (_currY-height/2) + height/2;
	//	moveVectorY = -moveVectorY;
	//	flag = true;
	//}

	//currX = _currX;
	//currY = _currY;
	//armature->setPosition(currX ,currY);

	//if (flag)
	//{
	//	return;
	//}

	//currX += moveVectorX;
	//currY += moveVectorY;
	//armature->setPosition(currX ,currY);

	//if((currX > (movePointX[nextMovePointIndex] - moveDeviation)) && (currX < (movePointX[nextMovePointIndex] + moveDeviation)) && (currY > (movePointY[nextMovePointIndex] - moveDeviation)) && (currY < (movePointY[nextMovePointIndex] + moveDeviation)))
	//{
	//	// 获得下一次的移动位置
	//	int ram = rand()%movePointCount;
	//	if(ram == nextMovePointIndex)
	//	{
	//		ram = (ram + 1) % movePointCount;
	//	}

	//	currMovePointIndex = nextMovePointIndex;
	//	nextMovePointIndex = ram;
	//	setAngle2();
	//}
}

void DynamicTarget::setArmatureByTypeAndStatus(int _type)
{
}

void DynamicTarget::setAngle(void)
{

}

void DynamicTarget::setAngle1(void)
{
	// 注意要不要关注第二参数为0的情况
	double x = movePointX[nextMovePointIndex] - movePointX[currMovePointIndex];
	double y = movePointY[nextMovePointIndex] - movePointY[currMovePointIndex];

	if (x > 0)
	{
		armature->setScaleX(-0.8f);
		moveVectorX = moveSpeed / MOVE_CONTROL;
		moveVectorY = 0;
		//moveAngle = 0;
	}
	else if (x < 0)
	{
		moveVectorX = -moveSpeed / MOVE_CONTROL;
		moveVectorY = 0;
		armature->setScaleX(0.8f);
		//moveAngle = 180;
	}

	CCLOG("moveVectorX = %f", moveVectorX);

	//moveAngle = atan2(y, x);
}

void DynamicTarget::setAngle2(void)
{
	// 注意要不要关注第二参数为0的情况
	double x = movePointX[nextMovePointIndex] - movePointX[currMovePointIndex];
	double y = movePointY[nextMovePointIndex] - movePointY[currMovePointIndex];

	double moveAngle = atan2(y, x);

	moveTimeSum = x/(moveSpeed / MOVE_CONTROL * cos(moveAngle));
	moveTimeCount = 0;
	if (x > 0)
	{
		//CCLOG("x1= %f, y1 = %f", armature->getAnchorPoint().x, armature->getAnchorPoint().y);
		armature->setScaleX(-0.8f);
	}
	else if (x < 0)
	{
		armature->setScaleX(0.8f);
	}

	//moveVectorX = moveSpeed / MOVE_CONTROL * cos(moveAngle);
	//moveVectorY = moveSpeed / MOVE_CONTROL * sin(moveAngle);
}

/******************************************************************
 小钻风
*******************************************************************/
DynamicTargetXiaoZuanFeng::DynamicTargetXiaoZuanFeng(int _id, int _type, double _x, double _y)// 类型   起始坐标
:DynamicTarget(_id, _type, _x, _y)
{
	currX = currX + width/2;
	currY = currY + height/2;
	dizzySpecialEffect = NULL;
}

DynamicTargetXiaoZuanFeng::~DynamicTargetXiaoZuanFeng(void)
{

}

void DynamicTargetXiaoZuanFeng::doAction(float _f, GameControl * _gameControl)// 动作调用函数
{
	float _tmp;
	switch(status)
	{
	case DYNAMIC_TARGET_STATUS_MOVING:// 移动
		if (movePointCount != 0)
		{
			actionMove();
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:// 被抓住
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
			armature->setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
				, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
		// 被吸取  放缩   位置更改
		_tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//armature->setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		armature->setPosition(currX + vectorX * (1 - _tmp), currY + vectorY * (1 - _tmp));
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		getAwards();
		if (words != NULL)
		{
			_gameControl->removeChild(words, true);
			words = NULL;
		}
		setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		if (words != NULL)
		{
			_gameControl->removeChild(words, true);
			words = NULL;
		}
		setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		if (dizzySpecialEffect == NULL)
		{
			dizzySpecialEffect = new DizzySpecialEffect();
			_gameControl->addChild(dizzySpecialEffect);
		}
		if (armature->getScaleX() > 0)
		{
			dizzySpecialEffect->setPosition(ccp(armature->getPositionX() - DYANMIC_TARGET_DIZZY_POSITIONX_CONTROL, armature->getPositionY() + height/2 + DYANMIC_TARGET_DIZZY_POSITIONY_CONTROL));
			dizzySpecialEffect->setScaleX(1);
		}
		else
		{
			dizzySpecialEffect->setPosition(ccp(armature->getPositionX() + DYANMIC_TARGET_DIZZY_POSITIONX_CONTROL, armature->getPositionY() + height/2 + DYANMIC_TARGET_DIZZY_POSITIONY_CONTROL));
			dizzySpecialEffect->setScaleX(-1);
		}
		dizzySpecialEffect->doAction(_f);
		break;
	default:
		break;
	}
	//roleSwaySpeed->setPosition(armature->getPosition());
}

void DynamicTargetXiaoZuanFeng::getAwards(void)// 获得奖励
{
	Global::getInstance()->appendPetElementGet(PET_ELEMENT_XIAOZUANFENG, 1);
	Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 10);

	if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
	{
		Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 700);
	}
	else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
	{
		Global::getInstance()->appendPropAwardGet(PROP_TYPE_FOOD, 1);
	}
}

void DynamicTargetXiaoZuanFeng::setStatus(int _status, Hanger * _hanger)// 修改状态
{
	lastStatus = status;
	status = _status;
	if (status == DYNAMIC_TARGET_STATUS_GOURD)
	{// 如果更改为被吸取状态对应更新参数
		vectorX = hanger->getCurrX() - hanger->getDistanceToRope()*cos((hanger->getAngle() - angleChange)/angleChange*pi) - getPositionX();
		vectorY = hanger->getCurrY() - hanger->getDistanceToRope()*sin((hanger->getAngle() - angleChange)/angleChange*pi) - getPositionY();
	}
	// 设置状态的同时要改变其动画
	armature->getAnimation()->playByIndex(status , 0, 50, 1, TWEEN_EASING_MAX);
}

int DynamicTargetXiaoZuanFeng::getSpeed(void)// 获得移动目标被抓取的数度(负的)
{
	return 5;
}

int DynamicTargetXiaoZuanFeng::getSpeedType(void)// 获得移动目标被抓取的数度(负的)
{
	return TARGET_SPEED_TYPE_M;
}

void DynamicTargetXiaoZuanFeng::setArmatureByTypeAndStatus(int _type)
{
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("jingxigui", "", "flash/jingxigui.png", "flash/jingxigui.plist", "flash/jingxigui.xml");
	armature = Armature::create("jingxigui");
	armature->setScale(0.8);
	armature->setAnchorPoint(ccp(0.5, 0.5));
	armature->setPosition(currX ,currY);
	carriedDistance = 30;
	//armature->getDisplayRenderNode()->setZOrder(LAYER_ORDER_CONTROL);
	//armature->getZOrder();
}

void DynamicTargetXiaoZuanFeng::setAngle(void)
{
	DynamicTarget::setAngle1();
}

bool DynamicTargetXiaoZuanFeng::isIntersectById(int _id)// 返回是否与对应id的对象进行碰撞检测
{// 将钻石偷走 
	if ((_id == TARGET_ID_BOMB) || (_id == TARGET_ID_DIAMOND) || (_id > DYNAMIC_ID_TYPE_START))
	{
		return true;
	}
	return false;
}

void DynamicTargetXiaoZuanFeng::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger) // 与钩子碰撞的处理
{
	DynamicTarget::doIntersectWithHanger(_gameControl, _hanger);
}

void DynamicTargetXiaoZuanFeng::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)//碰撞到静态对象时候 的处理函数 
{
	DynamicTarget::intersectWithTarget(_id, _target, _gameControl);// 炸弹处理
	if (_id == TARGET_ID_DIAMOND)
	{// 将砖石偷走
		setStatus(DYNAMIC_TARGET_STATUS_SKILL, NULL);// 自己变成技能状态
		_target->setStatus(TARGET_STATUS_REMOVE, NULL);
	}
}
/******************************************************************
精细鬼
*******************************************************************/
DynamicTargetJingXiGui::DynamicTargetJingXiGui(int _id, int _type, double _x, double _y)// 类型   起始坐标
:DynamicTarget(_id, _type, _x, _y)
{
	dizzySpecialEffect = NULL;
	width = 47;
	height = 74;
	currX = currX + width/2;
	currY = currY + height/2;
	type = _type;
	setArmatureByTypeAndStatus(_type);
	setStatus(status, NULL);
	isWords = false;
	words = NULL;
}

DynamicTargetJingXiGui::~DynamicTargetJingXiGui(void)
{

}

void DynamicTargetJingXiGui::doAction(float _f, GameControl * _gameControl)// 动作调用函数
{
	double _tmp;
	switch(status)
	{
	case DYNAMIC_TARGET_STATUS_MOVING:// 移动
		if (movePointCount != 0)
		{
			if (actionMove())
			{
				isWords = true;
			}
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:// 被抓住
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
			armature->setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
				, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
		// 被吸取  放缩   位置更改
		_tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//armature->setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		armature->setPosition(currX + vectorX * (1 - _tmp), currY + vectorY * (1 - _tmp));
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			getAwards();
			if (words != NULL)
			{
				_gameControl->removeChild(words, true);
				words = NULL;
			}
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			if (words != NULL)
			{
				_gameControl->removeChild(words, true);
				words = NULL;
			}
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		if (dizzySpecialEffect == NULL)
		{
			dizzySpecialEffect = new DizzySpecialEffect();
			_gameControl->addChild(dizzySpecialEffect);
		}
		if (armature->getScaleX() > 0)
		{
			dizzySpecialEffect->setPosition(ccp(armature->getPositionX() - DYANMIC_TARGET_DIZZY_POSITIONX_CONTROL, armature->getPositionY() + height/2 + DYANMIC_TARGET_DIZZY_POSITIONY_CONTROL));
			dizzySpecialEffect->setScaleX(1);
		}
		else
		{
			dizzySpecialEffect->setPosition(ccp(armature->getPositionX() + DYANMIC_TARGET_DIZZY_POSITIONX_CONTROL, armature->getPositionY() + height/2 + DYANMIC_TARGET_DIZZY_POSITIONY_CONTROL));
			dizzySpecialEffect->setScaleX(-1);
		}
		dizzySpecialEffect->doAction(_f);
		break;
	default:
		break;
	}

	if (!isWords)
	{
		if (words == NULL)
		{
			isWords = true;
		}
	}
	else
	{
		if (words == NULL)
		{
			words = CCSprite::create("duihuakuang/19.png");

			CCSequence * sequence;
			sequence = CCSequence::create(CCFadeIn::create(.2f),CCFadeTo::create(1.5f,255*1),CCFadeOut::create(.1f),NULL);
			_gameControl->addChild(words, LAYER_ORDER_CONTROL - 1);
			words->runAction(sequence);
			isWords = false;
		}
		else
		{
			CCSequence * sequence;
			sequence = CCSequence::create(CCFadeIn::create(.2f),CCFadeTo::create(1.5f,255*1),CCFadeOut::create(.1f),NULL);
			words->runAction(sequence);
			isWords = false;
		}
	}
	if (words != NULL)
	{
		words->setPosition(ccp(armature->getPositionX() + armature->getContentSize().width/2,armature->getPositionY() + armature->getContentSize().height/2));
	}
	//roleSwaySpeed->setPosition(armature->getPosition());
}

void DynamicTargetJingXiGui::getAwards(void)// 获得奖励
{
	Global::getInstance()->appendPetElementGet(PET_ELEMENT_JINGXIGUI, 1);
	Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 10);

	if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
	{
		Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 700);
	}
	else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
	{
		Global::getInstance()->appendPropAwardGet(PROP_TYPE_FOOD, 1);
	}
	else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)
	{
		// 炸弹装给 1块钱
		Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 1);
		//Global::getInstance()->appendPropAwardGet(PROP_TYPE_GRENADE, 1);
	}
}

void DynamicTargetJingXiGui::setStatus(int _status, Hanger * _hanger)// 修改状态
{// 0 走路 1 凶狠 2 砖石 3 钻石晕 4 钻石消失 5 卖萌 6 口量 7 口粮晕 8 口粮消失 9 炸弹 10 晕 11 消失

	if (dizzySpecialEffect != NULL)
	{
		dizzySpecialEffect->setVisible(false);
	}
	
#ifdef										GOLDEN_MINER2_FLASH_FRAME
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
			canCarry = true;
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)// 炸弹状态
		{
			armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 食物状态
		{
			armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_MOVING:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)// 炸弹状态
		{
			armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 食物状态
		{
			armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(9 , 0, 50, 1, TWEEN_EASING_MAX);
			armature->setRotation(angleCenter - hanger->getAngle());
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 食物状态
		{
			armature->getAnimation()->playByIndex(11 , 0, 50, 1, TWEEN_EASING_MAX);
			armature->setRotation(angleCenter - hanger->getAngle());
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)// 炸弹状态
		{
			armature->getAnimation()->playByIndex(7 , 0, 50, 1, TWEEN_EASING_MAX);
			armature->setRotation(angleCenter - hanger->getAngle());
		}
		else
		{
			armature->getAnimation()->playByIndex(5 , 0, 50, 1, TWEEN_EASING_MAX);
			armature->setRotation(angleCenter - hanger->getAngle());
		}
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_JINGXIGUI_CARRIED);

		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(10 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 食物状态
		{
			armature->getAnimation()->playByIndex(12 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)// 炸弹状态
		{
			armature->getAnimation()->playByIndex(8 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else
		{
			armature->getAnimation()->playByIndex(6 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(10 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 食物状态
		{
			armature->getAnimation()->playByIndex(12 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)// 炸弹状态
		{
			armature->getAnimation()->playByIndex(8 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else
		{
			armature->getAnimation()->playByIndex(6 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		// 设置状态的同时要改变其动画
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(9 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 食物状态
		{
			armature->getAnimation()->playByIndex(11 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)// 炸弹状态
		{
			armature->getAnimation()->playByIndex(7 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else
		{
			armature->getAnimation()->playByIndex(5 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(9 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 食物状态
		{
			armature->getAnimation()->playByIndex(11 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)// 炸弹状态
		{
			armature->getAnimation()->playByIndex(7 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else
		{
			armature->getAnimation()->playByIndex(5 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		if (dizzySpecialEffect != NULL)
		{
			dizzySpecialEffect->setVisible(true);
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_SKILL:
		// 没有技能
		return;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		armature->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
#else
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
			canCarry = true;
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)// 炸弹状态
		{
			armature->getAnimation()->playByIndex(9 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 食物状态
		{
			armature->getAnimation()->playByIndex(6 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_MOVING:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)// 炸弹状态
		{
			armature->getAnimation()->playByIndex(9 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 食物状态
		{
			armature->getAnimation()->playByIndex(6 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);
			armature->setRotation(angleCenter - hanger->getAngle());
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)// 炸弹状态
		{
			armature->getAnimation()->playByIndex(15 , 0, 50, 1, TWEEN_EASING_MAX);
			armature->setRotation(angleCenter - hanger->getAngle());
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 食物状态
		{
			armature->getAnimation()->playByIndex(7 , 0, 50, 1, TWEEN_EASING_MAX);
			armature->setRotation(angleCenter - hanger->getAngle());
		}
		else
		{
			armature->getAnimation()->playByIndex(10 , 0, 50, 1, TWEEN_EASING_MAX);
			armature->setRotation(angleCenter - hanger->getAngle());
		}
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_JINGXIGUI_CARRIED);

		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)// 炸弹状态
		{
			armature->getAnimation()->playByIndex(16 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 食物状态
		{
			armature->getAnimation()->playByIndex(8 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else
		{
			armature->getAnimation()->playByIndex(11 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 食物状态
		{
			armature->getAnimation()->playByIndex(8 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)// 炸弹状态
		{
			armature->getAnimation()->playByIndex(16 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else
		{
			armature->getAnimation()->playByIndex(11 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		// 设置状态的同时要改变其动画
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)// 炸弹状态
		{
			armature->getAnimation()->playByIndex(15 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 食物状态
		{
			armature->getAnimation()->playByIndex(7 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else
		{
			armature->getAnimation()->playByIndex(10 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)// 炸弹状态
		{
			armature->getAnimation()->playByIndex(15 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 食物状态
		{
			armature->getAnimation()->playByIndex(7 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else
		{
			armature->getAnimation()->playByIndex(10 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		if (dizzySpecialEffect != NULL)
		{
			dizzySpecialEffect->setVisible(true);
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_SKILL:
		// 没有技能
		return;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		armature->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
#endif

	lastStatus = status;
	status = _status;
}

int DynamicTargetJingXiGui::getSpeed(void)// 获得移动目标被抓取的数度(负的)
{
	return 6;
}

int DynamicTargetJingXiGui::getSpeedType(void)// 获得移动目标被抓取的数度(负的)
{
	return TARGET_SPEED_TYPE_M;
}

void DynamicTargetJingXiGui::setArmatureByTypeAndStatus(int _type)
{
	armature = Armature::create("jingxigui");
	armature->setScale(0.8);
	armature->setAnchorPoint(ccp(0.5, 0.5));
	armature->retain();
	armature->setPosition(currX ,currY);
#ifdef					GOLDEN_MINER2_FLASH_FRAME
	carriedDistance = 25;
#else
	carriedDistance = 30;
#endif

	switch(_type)
	{
	case DYNAMIC_TARGET_TYPE_NORMALE:// 原始状态
		status = DYNAMIC_TARGET_STATUS_MOVING;
		lastStatus = status;
		moveSpeed = 2;
		break;
	case DYNAMIC_TARGET_TYPE_CARRIED_FOOD:
		status = DYNAMIC_TARGET_STATUS_MOVING;
		lastStatus = status;
		moveSpeed = 5;
		break;
	case DYNAMIC_TARGET_TYPE_CARRIED_BOMB:
		status = DYNAMIC_TARGET_STATUS_MOVING;
		lastStatus = status;
		moveSpeed = 7;
		break;
	case DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND:
		status = DYNAMIC_TARGET_STATUS_MOVING;
		lastStatus = status;
		moveSpeed = 5;
		break;
	default:
		break;
	}
}

void DynamicTargetJingXiGui::setAngle(void)
{
	DynamicTarget::setAngle1();
}

bool DynamicTargetJingXiGui::isIntersectById(int _id)// 返回是否与对应id的对象进行碰撞检测
{
	if (_id == TARGET_ID_BOMB || (_id > DYNAMIC_ID_TYPE_START))
	{
		return true;
	}
	return false;
}

void DynamicTargetJingXiGui::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger) // 与钩子碰撞的处理
{		
	DynamicTarget::doIntersectWithHanger(_gameControl, _hanger);
}

void DynamicTargetJingXiGui::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)//碰撞到静态对象时候 的处理函数 
{
	DynamicTarget::intersectWithTarget(_id, _target, _gameControl);
}
/******************************************************************
伶俐虫
*******************************************************************/
DynamicTargetLingLiChong::DynamicTargetLingLiChong(int _id, int _type, double _x, double _y)// 类型   起始坐标
:DynamicTarget(_id, _type, _x, _y)
{
	dizzySpecialEffect = NULL;
	currX = currX + width/2;
	currY = currY + height/2;
}

DynamicTargetLingLiChong::~DynamicTargetLingLiChong(void)
{

}

void DynamicTargetLingLiChong::doAction(float _f, GameControl * _gameControl)// 动作调用函数
{
	double _tmp;
	switch(status)
	{
	case DYNAMIC_TARGET_STATUS_MOVING:// 移动
		if (movePointCount != 0)
		{
			actionMove();
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:// 被抓住
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
			armature->setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
				, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
		// 被吸取  放缩   位置更改
		_tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//armature->setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		armature->setPosition(currX + vectorX * (1 - _tmp), currY + vectorY * (1 - _tmp));
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			getAwards();
			if (words != NULL)
			{
				_gameControl->removeChild(words, true);
				words = NULL;
			}
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			if (words != NULL)
			{
				_gameControl->removeChild(words, true);
				words = NULL;
			}
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		if (dizzySpecialEffect == NULL)
		{
			dizzySpecialEffect = new DizzySpecialEffect();
			_gameControl->addChild(dizzySpecialEffect);
		}
		if (armature->getScaleX() > 0)
		{
			dizzySpecialEffect->setPosition(ccp(armature->getPositionX() - DYANMIC_TARGET_DIZZY_POSITIONX_CONTROL, armature->getPositionY() + height/2 + DYANMIC_TARGET_DIZZY_POSITIONY_CONTROL));
			dizzySpecialEffect->setScaleX(1);
		}
		else
		{
			dizzySpecialEffect->setPosition(ccp(armature->getPositionX() + DYANMIC_TARGET_DIZZY_POSITIONX_CONTROL, armature->getPositionY() + height/2 + DYANMIC_TARGET_DIZZY_POSITIONY_CONTROL));
			dizzySpecialEffect->setScaleX(-1);
		}
		dizzySpecialEffect->doAction(_f);
		break;
	default:
		break;
	}
	//roleSwaySpeed->setPosition(armature->getPosition());

	if (!isWords)
	{
		if (words == NULL)
		{
			isWords = true;
		}
	}
	else
	{
		if (words == NULL)
		{
			words = CCSprite::create("duihuakuang/19.png");

			CCSequence * sequence;
			sequence = CCSequence::create(CCFadeIn::create(.2f),CCFadeTo::create(1.5f,255*1),CCFadeOut::create(.1f),NULL);
			_gameControl->addChild(words,  LAYER_ORDER_CONTROL - 1);
			words->runAction(sequence);
			isWords = false;
		}
		else
		{
			CCSequence * sequence;
			sequence = CCSequence::create(CCFadeIn::create(.2f),CCFadeTo::create(1.5f,255*1),CCFadeOut::create(.1f),NULL);
			words->runAction(sequence);
			isWords = false;
		}
	}
	if (words != NULL)
	{
		words->setPosition(ccp(armature->getPositionX() + armature->getContentSize().width/2,armature->getPositionY() + armature->getContentSize().height/2));
	}
}

void DynamicTargetLingLiChong::getAwards(void)// 获得奖励
{
	Global::getInstance()->appendPetElementGet(PET_ELEMENT_LINGLICHONG, 1);
	Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 10);

	if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
	{
		Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 700);
	}
	else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
	{
		Global::getInstance()->appendPropAwardGet(PROP_TYPE_FOOD, 1);
	}
	else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)
	{
		Global::getInstance()->appendPropAwardGet(PROP_TYPE_GRENADE, 1);
	}
}

void DynamicTargetLingLiChong::setStatus(int _status, Hanger * _hanger)// 修改状态
{
	if (dizzySpecialEffect != NULL)
	{
		dizzySpecialEffect->setVisible(false);
	}
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
			canCarry = true;
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_NORMALE)// 原始状态
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 原始状态
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
			canCarry = true;
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_MOVING:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_NORMALE)// 原始状态
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 原始状态
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
			canCarry = true;
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);
		armature->setRotation(angleCenter - hanger->getAngle());
		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		// 设置状态的同时要改变其动画
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)// 携带宝石的
		{
			armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)// 食物状态
		{
			armature->getAnimation()->playByIndex(7 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		else
		{
			armature->getAnimation()->playByIndex(10 , 0, 50, 1, TWEEN_EASING_MAX);
		}
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);
		if (dizzySpecialEffect != NULL)
		{
			dizzySpecialEffect->setVisible(true);
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_SKILL:
		// 没有技能
		return;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		armature->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
	lastStatus = status;
	status = _status;
}

int DynamicTargetLingLiChong::getSpeed(void)// 获得移动目标被抓取的数度(负的)
{
	return 6;
}

int DynamicTargetLingLiChong::getSpeedType(void)// 获得移动目标被抓取的数度(负的)
{
	return TARGET_SPEED_TYPE_M;
}

void DynamicTargetLingLiChong::setArmatureByTypeAndStatus(int _type)
{
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("bajie", "", "flash/bajie.png", "flash/bajie.plist", "flash/bajie.xml");
	armature = Armature::create("bajie");
	armature->setScale(0.8);
	armature->setAnchorPoint(ccp(0.5, 0.5));
	armature->setPosition(currX ,currY);

	status = DYNAMIC_TARGET_STATUS_MOVING;
	lastStatus = status;
	moveSpeed = 5;
	carriedDistance = 30;
}

void DynamicTargetLingLiChong::setAngle(void)
{
	DynamicTarget::setAngle1();
}

bool DynamicTargetLingLiChong::isIntersectById(int _id)// 返回是否与对应id的对象进行碰撞检测
{// 将金矿变成石头
	switch(_id)
	{
	case TARGET_ID_BOMB:
	case TARGET_ID_GOLDEN_B:
	case TARGET_ID_GOLDEN_M:
	case TARGET_ID_GOLDEN_S:
		return true;
	default:
		break;
	} 
	if (_id > DYNAMIC_ID_TYPE_START)
	{
		return true;
	}
	
	return false;
}

void DynamicTargetLingLiChong::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger) // 与钩子碰撞的处理
{
	DynamicTarget::doIntersectWithHanger(_gameControl, _hanger);
}

void DynamicTargetLingLiChong::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)//碰撞到静态对象时候 的处理函数 
{
	// 将金矿变成石头
	DynamicTarget::intersectWithTarget(_id, _target, _gameControl);// 炸弹
	if (_id == TARGET_ID_GOLDEN_B)
	{
		setStatus(DYNAMIC_TARGET_STATUS_SKILL, NULL);
		_target->exchangeBitmapAndId(TARGET_ID_STONE_B);
	}
	else if (_id == TARGET_ID_GOLDEN_M)
	{
		setStatus(DYNAMIC_TARGET_STATUS_SKILL, NULL);
		_target->exchangeBitmapAndId(TARGET_ID_STONE_M);
	}
	else if (_id == TARGET_ID_GOLDEN_S)
	{
		setStatus(DYNAMIC_TARGET_STATUS_SKILL, NULL);
		_target->exchangeBitmapAndId(TARGET_ID_STONE_S);
	}
}
/******************************************************************
灵感大王
*******************************************************************/
DynamicTargetLingGanDaWang::DynamicTargetLingGanDaWang(int _id, int _type, double _x, double _y)// 类型   起始坐标
:DynamicTarget(_id, _type, _x, _y)
{	
	dizzySpecialEffect = NULL;
	width = 85;
	height = 40;
	currX = currX + width/2;
	currY = currY + height/2;
	type = _type;
	setArmatureByTypeAndStatus(_type);
	setStatus(status, NULL);
	isWords = false;
	words = NULL;
}

DynamicTargetLingGanDaWang::~DynamicTargetLingGanDaWang(void)
{

}

void DynamicTargetLingGanDaWang::doAction(float _f, GameControl * _gameControl)// 动作调用函数
{
	double _tmp;
	switch(status)
	{
	case DYNAMIC_TARGET_STATUS_MOVING:// 移动
		if (movePointCount != 0)
		{
			if (actionMove())
			{
				isWords = true;
			}
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:// 被抓住
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
			armature->setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
				, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
		// 被吸取  放缩   位置更改
		_tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//armature->setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		armature->setPosition(currX + vectorX * (1 - _tmp), currY + vectorY * (1 - _tmp));
		break;
	case DYNAMIC_TARGET_STATUS_SKILL:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			//recoverLastStatus();
			setStatus(DYNAMIC_TARGET_STATUS_MOVING, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			getAwards();
			if (words != NULL)
			{
				_gameControl->removeChild(words, true);
				words = NULL;
			}
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			if (words != NULL)
			{
				_gameControl->removeChild(words, true);
				words = NULL;
			}
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		if (dizzySpecialEffect == NULL)
		{
			dizzySpecialEffect = new DizzySpecialEffect();
			_gameControl->addChild(dizzySpecialEffect);
		}
		if (armature->getScaleX() > 0)
		{
			dizzySpecialEffect->setPosition(ccp(armature->getPositionX() + DYANMIC_TARGET_DIZZY_POSITIONX_CONTROL, armature->getPositionY() + height/2 + DYANMIC_TARGET_DIZZY_POSITIONY_CONTROL));
			dizzySpecialEffect->setScaleX(1);
		}
		else
		{
			dizzySpecialEffect->setPosition(ccp(armature->getPositionX() - DYANMIC_TARGET_DIZZY_POSITIONX_CONTROL, armature->getPositionY() + height/2 + DYANMIC_TARGET_DIZZY_POSITIONY_CONTROL));
			dizzySpecialEffect->setScaleX(-1);
		}
		dizzySpecialEffect->doAction(_f);
		break;
	default:
		break;
	}

	if (!isWords)
	{
		if (words == NULL)
		{
			isWords = true;
		}
	}
	else
	{
		if (words == NULL)
		{
			words = CCSprite::create("duihuakuang/20.png");

			CCSequence * sequence;
			sequence = CCSequence::create(CCFadeIn::create(.2f),CCFadeTo::create(1.5f,255*1),CCFadeOut::create(.1f),NULL);
			_gameControl->addChild(words,  LAYER_ORDER_CONTROL - 1);
			words->runAction(sequence);
			isWords = false;
		}
		else
		{
			CCSequence * sequence;
			sequence = CCSequence::create(CCFadeIn::create(.2f),CCFadeTo::create(1.5f,255*1),CCFadeOut::create(.1f),NULL);
			words->runAction(sequence);
			isWords = false;
		}
	}
	if (words != NULL)
	{
		words->setPosition(ccp(armature->getPositionX() + armature->getContentSize().width/2,armature->getPositionY() + armature->getContentSize().height/2));
	}
	//roleSwaySpeed->setPosition(armature->getPosition());
}

void DynamicTargetLingGanDaWang::getAwards(void)// 获得奖励
{
	Global::getInstance()->appendPetElementGet(PET_ELEMENT_LINGGANDAWANG, 1);
	Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 20);
}

void DynamicTargetLingGanDaWang::setStatus(int _status, Hanger * _hanger)// 修改状态
{// 0 凶狠  1 卖萌 2 游动 3 攻击 4 晕 5 消失 
	if (dizzySpecialEffect != NULL)
	{
		dizzySpecialEffect->setVisible(false);
	}
#ifdef							GOLDEN_MINER2_FLASH_FRAME
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
			canCarry = true;
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
			canCarry = true;
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_MOVING:
		if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
			canCarry = true;
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);
		armature->setRotation(angleCenter - hanger->getAngle());
		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_LINGGANDAWANG_CARRIED);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		// 设置状态的同时要改变其动画
		armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);
		if (dizzySpecialEffect != NULL)
		{
			dizzySpecialEffect->setVisible(true);
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_SKILL:
		armature->getAnimation()->playByIndex(2 , 0, 180, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_SKILL_DISPLAY_TIME_COUNT;
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		armature->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
#else
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
			canCarry = true;
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
			canCarry = true;
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_MOVING:
		if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
			canCarry = true;
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		armature->setRotation(angleCenter - hanger->getAngle());
		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_LINGGANDAWANG_CARRIED);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		armature->getAnimation()->playByIndex(5 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		armature->getAnimation()->playByIndex(5 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		// 设置状态的同时要改变其动画
		armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		if (dizzySpecialEffect != NULL)
		{
			dizzySpecialEffect->setVisible(true);
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_SKILL:
		armature->getAnimation()->playByIndex(3 , 0, 180, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_SKILL_DISPLAY_TIME_COUNT;
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		armature->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
#endif
	lastStatus = status;
	status = _status;
}

int DynamicTargetLingGanDaWang::getSpeed(void)// 获得移动目标被抓取的数度(负的)
{
	return 12;
}

int DynamicTargetLingGanDaWang::getSpeedType(void)// 获得移动目标被抓取的数度(负的)
{
	return TARGET_SPEED_TYPE_B;
}

void DynamicTargetLingGanDaWang::setArmatureByTypeAndStatus(int _type)
{
	armature = Armature::create("linggandawang");
	armature->setScale(0.8);
	armature->setAnchorPoint(ccp(0.5, 0.5));
	armature->retain();
	armature->setPosition(currX ,currY);
	status = DYNAMIC_TARGET_STATUS_MOVING;
	lastStatus = DYNAMIC_TARGET_STATUS_MOVING;
	moveSpeed = 3;
	carriedDistance = 5;
}

void DynamicTargetLingGanDaWang::setAngle(void)
{
	DynamicTarget::setAngle1();
}

bool DynamicTargetLingGanDaWang::isIntersectById(int _id)// 返回是否与对应id的对象进行碰撞检测
{
	return true;
}

void DynamicTargetLingGanDaWang::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger) // 与钩子碰撞的处理
{
	DynamicTarget::doIntersectWithHanger(_gameControl, _hanger);
}

void DynamicTargetLingGanDaWang::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)//碰撞到静态对象时候 的处理函数 
{
	DynamicTarget::intersectWithTarget(_id, _target, _gameControl);//炸弹
	// 吃掉
	if (_id != TARGET_ID_BOMB)
	{
		setStatus(DYNAMIC_TARGET_STATUS_SKILL, NULL);
		_target->setStatus(TARGET_STATUS_REMOVE, NULL);
	}
}
/******************************************************************
玉面公主
*******************************************************************/
DynamicTargetYuMianGongZhu::DynamicTargetYuMianGongZhu(int _id, int _type, double _x, double _y)// 类型   起始坐标
:DynamicTarget(_id, _type, _x, _y)
{
	dizzySpecialEffect = NULL;
	width = 47;
	height = 74;
	currX = currX + width/2;
	currY = currY + height/2;
	type = _type;

	isRemovePen = false;
	pen = CCSprite::create("youxi/kuang.png");
	pen->retain();

	setArmatureByTypeAndStatus(_type);
	setStatus(status, NULL);
	isWords = false;
	words = NULL;

	pen->setScale(2*DYNAMIC_TARGET_YUMIANGONGZHU_SKILL_SCOPE/pen->getContentSize().width);
	//pen->setZOrder(1);
	//armature->setZOrder(2);
}

DynamicTargetYuMianGongZhu::~DynamicTargetYuMianGongZhu(void)
{

}

void DynamicTargetYuMianGongZhu::doAction(float _f, GameControl * _gameControl)// 动作调用函数
{
	double _tmp;
	switch(status)
	{
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		hideTarget(_gameControl);
		break;
	case DYNAMIC_TARGET_STATUS_MOVING:// 移动
		if (movePointCount != 0)
		{
			if (actionMove())
			{
				isWords = true;
			}
		}
		hideTarget(_gameControl);
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:// 被抓住
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
			armature->setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
				, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
		// 被吸取  放缩   位置更改
		_tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//armature->setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		armature->setPosition(currX + vectorX * (1 - _tmp), currY + vectorY * (1 - _tmp));
		break;
	//case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
	//	// 被吸取  放缩   位置更改
	//	if (Global::getInstance()->getJewelSkillScale() < 0.1)
	//	{
	//		setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
	//	}
	//	armature->setScale(Global::getInstance()->getJewelSkillScale());
	//	armature->setPosition(currX + vectorX * (1 - Global::getInstance()->getJewelSkillScale()), currY + vectorY * (1 - Global::getInstance()->getJewelSkillScale()));
	//	break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			getAwards();
			if (words != NULL)
			{
				_gameControl->removeChild(words, true);
				words = NULL;
			}
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			if (words != NULL)
			{
				_gameControl->removeChild(words, true);
				words = NULL;
			}
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		hideTarget(_gameControl);
		if (dizzySpecialEffect == NULL)
		{
			dizzySpecialEffect = new DizzySpecialEffect();
			_gameControl->addChild(dizzySpecialEffect);
		}
		if (armature->getScaleX() > 0)
		{
			dizzySpecialEffect->setPosition(ccp(armature->getPositionX() + 2 * DYANMIC_TARGET_DIZZY_POSITIONX_CONTROL, armature->getPositionY() + height/2 + DYANMIC_TARGET_DIZZY_POSITIONY_CONTROL));
			dizzySpecialEffect->setScaleX(1);
		}
		else
		{
			dizzySpecialEffect->setPosition(ccp(armature->getPositionX() - 2 * DYANMIC_TARGET_DIZZY_POSITIONX_CONTROL, armature->getPositionY() + height/2 + DYANMIC_TARGET_DIZZY_POSITIONY_CONTROL));
			dizzySpecialEffect->setScaleX(-1);
		}
		dizzySpecialEffect->doAction(_f);
		break;
	default:
		break;
	}
	if (isRemovePen)
	{
		if (pen != NULL)
		{
			_gameControl->removeChild(pen, true);
			pen = NULL;
			isRemovePen = false;
		}
	}
	else
	{
		if (pen != NULL)
		{
			pen->setPosition(armature->getPosition());
		}
	}

	if (!isWords)
	{
		if (words == NULL)
		{
			isWords = true;
		}
	}
	else
	{
		if (words == NULL)
		{
			words = CCSprite::create("duihuakuang/21.png");

			CCSequence * sequence;
			sequence = CCSequence::create(CCFadeIn::create(.2f),CCFadeTo::create(1.5f,255*1),CCFadeOut::create(.1f),NULL);
			_gameControl->addChild(words,  LAYER_ORDER_CONTROL - 1);
			words->runAction(sequence);
			isWords = false;
		}
		else
		{
			CCSequence * sequence;
			sequence =CCSequence::create(CCFadeIn::create(.2f),CCFadeTo::create(1.5f,255*1),CCFadeOut::create(.1f),NULL);
			words->runAction(sequence);
			isWords = false;
		}
	}
	if (words != NULL)
	{
		words->setPosition(ccp(armature->getPositionX() + armature->getContentSize().width/2,armature->getPositionY() + armature->getContentSize().height/2));
	}
	//roleSwaySpeed->setPosition(armature->getPosition());
}

void DynamicTargetYuMianGongZhu::getAwards(void)// 获得奖励
{
	Global::getInstance()->appendPetElementGet(PET_ELEMENT_YUMIANGONGZHU, 1);
	Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 20);

	if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
	{
		Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 700);
	}
	else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
	{
		Global::getInstance()->appendPropAwardGet(PROP_TYPE_FOOD, 1);
	}
	else if (type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)
	{
		Global::getInstance()->appendPropAwardGet(PROP_TYPE_GRENADE, 1);
	}
}

void DynamicTargetYuMianGongZhu::setStatus(int _status, Hanger * _hanger)// 修改状态
{// 0 卖萌 1 凶狠 2 走路 3 钻石 4 钻石晕 5 砖石消失 6 口粮 7 口粮晕 8 口粮消失  9 晕  10 消失
	if (dizzySpecialEffect != NULL)
	{
		dizzySpecialEffect->setVisible(false);
	}

#ifdef												GOLDEN_MINER2_FLASH_FRAME
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
		{
			armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);// 钻石状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
		{
			armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else
		{
			armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		if (pen != NULL)
		{
			pen->setVisible(true);
			isRemovePen = false;
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
		{
			armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);// 钻石状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
		{
			armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else
		{
			armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		if (pen != NULL)
		{
			pen->setVisible(true);
			isRemovePen = false;
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_MOVING:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
		{
			armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);// 钻石状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
		{
			armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else
		{
			armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		if (pen != NULL)
		{
			pen->setVisible(true);
			isRemovePen = false;
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
		{
			armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);// 钻石状态
			armature->setRotation(angleCenter - hanger->getAngle());
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
		{
			armature->getAnimation()->playByIndex(6 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
			armature->setRotation(angleCenter - hanger->getAngle());
		}
		else
		{
			armature->getAnimation()->playByIndex(8 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
			armature->setRotation(angleCenter - hanger->getAngle());
		}
		if (pen != NULL)
		{
			pen->setVisible(false);
			isRemovePen = true;
		}
		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_YUMIANGONGZHU_CARRIED);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
		{
			armature->getAnimation()->playByIndex(5 , 0, 50, 1, TWEEN_EASING_MAX);// 钻石状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
		{
			armature->getAnimation()->playByIndex(7 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else
		{
			armature->getAnimation()->playByIndex(9 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		if (pen != NULL)
		{
			pen->setVisible(false);
			isRemovePen = true;
		}
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
		{
			armature->getAnimation()->playByIndex(5 , 0, 50, 1, TWEEN_EASING_MAX);// 钻石状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
		{
			armature->getAnimation()->playByIndex(7 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else
		{
			armature->getAnimation()->playByIndex(9 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		if (pen != NULL)
		{
			pen->setVisible(false);
			isRemovePen = true;
		}
		//armature->getAnimation()->playByIndex(5 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		// 设置状态的同时要改变其动画
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
		{
			armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);// 钻石状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
		{
			armature->getAnimation()->playByIndex(6 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else
		{
			armature->getAnimation()->playByIndex(8 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		if (pen != NULL)
		{
			pen->setVisible(false);
			isRemovePen = true;
		}
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
		{
			armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);// 钻石状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
		{
			armature->getAnimation()->playByIndex(6 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else
		{
			armature->getAnimation()->playByIndex(8 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		if (dizzySpecialEffect != NULL)
		{
			dizzySpecialEffect->setVisible(true);
		}
		if (pen != NULL)
		{
			pen->setVisible(true);
			isRemovePen = false;
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_SKILL:
		CCLOG("玉面公主技能是移动或者静止时候的状态释放的，没有单独的技能状态");
		return;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		if (pen != NULL)
		{
			pen->setVisible(false);
			isRemovePen = true;
		}
		armature->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
#else
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
		{
			armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);// 钻石状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
		{
			armature->getAnimation()->playByIndex(6 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else
		{
			armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		if (pen != NULL)
		{
			pen->setVisible(true);
			isRemovePen = false;
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
		{
			armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);// 钻石状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
		{
			armature->getAnimation()->playByIndex(6 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else
		{
			armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		if (pen != NULL)
		{
			pen->setVisible(true);
			isRemovePen = false;
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_MOVING:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
		{
			armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);// 钻石状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
		{
			armature->getAnimation()->playByIndex(6 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else
		{
			armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		if (pen != NULL)
		{
			pen->setVisible(true);
			isRemovePen = false;
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
		{
			armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);// 钻石状态
			armature->setRotation(angleCenter - hanger->getAngle());
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
		{
			armature->getAnimation()->playByIndex(7 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
			armature->setRotation(angleCenter - hanger->getAngle());
		}
		else
		{
			armature->getAnimation()->playByIndex(9 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
			armature->setRotation(angleCenter - hanger->getAngle());
		}
		if (pen != NULL)
		{
			pen->setVisible(false);
			isRemovePen = true;
		}
		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_YUMIANGONGZHU_CARRIED);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
		{
			armature->getAnimation()->playByIndex(5 , 0, 50, 1, TWEEN_EASING_MAX);// 钻石状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
		{
			armature->getAnimation()->playByIndex(8 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else
		{
			armature->getAnimation()->playByIndex(10 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		if (pen != NULL)
		{
			pen->setVisible(false);
			isRemovePen = true;
		}
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
		{
			armature->getAnimation()->playByIndex(5 , 0, 50, 1, TWEEN_EASING_MAX);// 钻石状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
		{
			armature->getAnimation()->playByIndex(8 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else
		{
			armature->getAnimation()->playByIndex(10 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		if (pen != NULL)
		{
			pen->setVisible(false);
			isRemovePen = true;
		}
		armature->getAnimation()->playByIndex(5 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		// 设置状态的同时要改变其动画
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
		{
			armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);// 钻石状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
		{
			armature->getAnimation()->playByIndex(7 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else
		{
			armature->getAnimation()->playByIndex(9 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		if (pen != NULL)
		{
			pen->setVisible(false);
			isRemovePen = true;
		}
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		if (type == DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND)
		{
			armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);// 钻石状态
		}
		else if (type == DYNAMIC_TARGET_TYPE_CARRIED_FOOD)
		{
			armature->getAnimation()->playByIndex(7 , 0, 50, 1, TWEEN_EASING_MAX);// 口粮状态
		}
		else
		{
			armature->getAnimation()->playByIndex(9 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		if (dizzySpecialEffect != NULL)
		{
			dizzySpecialEffect->setVisible(true);
		}
		if (pen != NULL)
		{
			pen->setVisible(true);
			isRemovePen = false;
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_SKILL:
		CCLOG("玉面公主技能是移动或者静止时候的状态释放的，没有单独的技能状态");
		return;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		if (pen != NULL)
		{
			pen->setVisible(false);
			isRemovePen = true;
		}
		armature->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
#endif
	lastStatus = status;
	status = _status;
}

int DynamicTargetYuMianGongZhu::getSpeed(void)// 获得移动目标被抓取的数度(负的)
{
	return 7;
}

int DynamicTargetYuMianGongZhu::getSpeedType(void)// 获得移动目标被抓取的数度(负的)
{
	return TARGET_SPEED_TYPE_M;
}

void DynamicTargetYuMianGongZhu::setArmatureByTypeAndStatus(int _type)
{
#ifdef						GOLDEN_MINER2_FLASH_FRAME
	armature = Armature::create("yumiangongzhu"); 
#else
	armature = Armature::create("yumian");
#endif
	armature->setScale(0.8);
	armature->setAnchorPoint(ccp(0.5, 0.5));
	armature->retain();
	armature->setPosition(currX ,currY);
	pen->setPosition(armature->getPosition());
	status = DYNAMIC_TARGET_STATUS_MOVING;
	lastStatus = DYNAMIC_TARGET_STATUS_MOVING;
	moveSpeed = 7;
#ifdef					GOLDEN_MINER2_FLASH_FRAME
	carriedDistance = 27;
#else
	carriedDistance = 30;
#endif
}

void DynamicTargetYuMianGongZhu::setAngle(void)
{
	DynamicTarget::setAngle1();
}

bool DynamicTargetYuMianGongZhu::isIntersectById(int _id)// 返回是否与对应id的对象进行碰撞检测
{
	if (_id == TARGET_ID_BOMB || (_id > DYNAMIC_ID_TYPE_START))
	{
		return true;
	}
	return false;
}

void DynamicTargetYuMianGongZhu::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger) // 与钩子碰撞的处理
{
	DynamicTarget::doIntersectWithHanger(_gameControl, _hanger);
}

void DynamicTargetYuMianGongZhu::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)//碰撞到静态对象时候 的处理函数 
{
	DynamicTarget::intersectWithTarget(_id, _target, _gameControl);
}

cocos2d::CCSprite * DynamicTargetYuMianGongZhu::getPen(void)
{
	return pen;
}

void DynamicTargetYuMianGongZhu::hideTarget(GameControl * _gameControl)
{
	// 隐藏怪物
	// 静态目标
	if (_gameControl->gate->getTargets() != NULL)
	{
		for (unsigned int i = 0; i < _gameControl->gate->getTargets()->count(); i++)
		{
			Target * tmp = (Target *)_gameControl->gate->getTargets()->objectAtIndex(i);
			if(Global::getInstance()->isInCircle(tmp->getPositionX(), tmp->getPositionY(), armature->getPositionX(), armature->getPositionY(), DYNAMIC_TARGET_YUMIANGONGZHU_SKILL_SCOPE))
			{
				_gameControl->gate->addHideTarget(tmp);
			}
		}
	}

	// 动态目标
	unsigned int j = _gameControl->gate->getDynamicTargets()->indexOfObject(this);
	for (unsigned int i = 0; i < _gameControl->gate->getDynamicTargets()->count(); i++)
	{
		if (i != j)
		{
			DynamicTarget * tmp = (DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i);
			if (tmp->getId() == DYNAMIC_ID_YUMIANGONGZHU)
			{
				continue;
			}
			if(Global::getInstance()->isInCircle(tmp->getArmature()->getPositionX(), tmp->getArmature()->getPositionY(), armature->getPositionX(), armature->getPositionY(), DYNAMIC_TARGET_YUMIANGONGZHU_SKILL_SCOPE))
			{
				_gameControl->gate->addHideDynamicTarget(tmp);
			}
		}
	}
}
/******************************************************************
牛魔王
*******************************************************************/
DynamicTargetNiuMoWang::DynamicTargetNiuMoWang(int _id, int _type, double _x, double _y)// 类型   起始坐标
:DynamicTarget(_id, _type, _x, _y)
{
	dizzySpecialEffect = NULL;
	beCarriedCount = 0;
	width = 60;
	height = 100;
	currX = currX + width/2;
	currY = currY + height/2;
	type = _type;
	setArmatureByTypeAndStatus(_type);
	setStatus(status, NULL);
	isWords = false;
	words = NULL;
	isCarrierCarried = false;
}

DynamicTargetNiuMoWang::~DynamicTargetNiuMoWang(void)
{

}

void DynamicTargetNiuMoWang::doAction(float _f, GameControl * _gameControl)// 动作调用函数
{
	double _tmp;
	switch(status)
	{
	case DYNAMIC_TARGET_STATUS_MOVING:// 移动
		if (movePointCount != 0)
		{
			if (actionMove())
			{
				isWords = true;
			}
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:// 被抓住
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
			armature->setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
				, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
		// 被吸取  放缩   位置更改
		_tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//armature->setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		armature->setPosition(currX + vectorX * (1 - _tmp), currY + vectorY * (1 - _tmp));
		break;
	case DYNAMIC_TARGET_STATUS_SKILL:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			//recoverLastStatus();
			setStatus(DYNAMIC_TARGET_STATUS_MOVING, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			getAwards();
			if (words != NULL)
			{
				_gameControl->removeChild(words, true);
				words = NULL;
			}
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			if (words != NULL)
			{
				_gameControl->removeChild(words, true);
				words = NULL;
			}
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		if (dizzySpecialEffect == NULL)
		{
			dizzySpecialEffect = new DizzySpecialEffect();
			_gameControl->addChild(dizzySpecialEffect);
		}
		if (armature->getScaleX() > 0)
		{
			dizzySpecialEffect->setPosition(ccp(armature->getPositionX() - 1.5*DYANMIC_TARGET_DIZZY_POSITIONX_CONTROL, armature->getPositionY() + height/2 + DYANMIC_TARGET_DIZZY_POSITIONY_CONTROL));
			dizzySpecialEffect->setScaleX(1);
		}
		else
		{
			dizzySpecialEffect->setPosition(ccp(armature->getPositionX() + 1.5*DYANMIC_TARGET_DIZZY_POSITIONX_CONTROL, armature->getPositionY() + height/2 + DYANMIC_TARGET_DIZZY_POSITIONY_CONTROL));
			dizzySpecialEffect->setScaleX(-1);
		}
		dizzySpecialEffect->doAction(_f);
		break;
	case NIUMOWANG_STATUS_DIZZY:
		carriedTimeCount++;
		if (carriedTimeCount == NIUMOWANG_STATUS_DIZZY_TIME)
		{
			//recoverLastStatus();
			if (isCarrierCarried)
			{
				setStatus(DYNAMIC_TARGET_STATUS_CARRIER_CARRIED, NULL);
			}
			else
			{
				setStatus(DYNAMIC_TARGET_STATUS_MOVING, NULL);
			}
		}
		else
		{
			if (dizzySpecialEffect == NULL)
			{
				dizzySpecialEffect = new DizzySpecialEffect();
				_gameControl->addChild(dizzySpecialEffect);
			}
			if (armature->getScaleX() > 0)
			{
				dizzySpecialEffect->setPosition(ccp(armature->getPositionX() - 1.5*DYANMIC_TARGET_DIZZY_POSITIONX_CONTROL, armature->getPositionY() + height/2 + DYANMIC_TARGET_DIZZY_POSITIONY_CONTROL));
				dizzySpecialEffect->setScaleX(1);
			}
			else
			{
				dizzySpecialEffect->setPosition(ccp(armature->getPositionX() + 1.5*DYANMIC_TARGET_DIZZY_POSITIONX_CONTROL, armature->getPositionY() + height/2 + DYANMIC_TARGET_DIZZY_POSITIONY_CONTROL));
				dizzySpecialEffect->setScaleX(-1);
			}
			dizzySpecialEffect->doAction(_f);
		}
		break;
	default:
		break;
	}
	//roleSwaySpeed->setPosition(armature->getPosition());

	if (!isWords)
	{
		if (words == NULL)
		{
			isWords = true;
		}
	}
	else
	{
		if (words == NULL)
		{
			words = CCSprite::create("duihuakuang/22.png");

			CCSequence * sequence;
			sequence =CCSequence::create(CCFadeIn::create(.2f),CCFadeTo::create(1.5f,255*1),CCFadeOut::create(.1f),NULL);
			_gameControl->addChild(words,  LAYER_ORDER_CONTROL - 1);
			words->runAction(sequence);
			isWords = false;
		}
		else
		{
			CCSequence * sequence;
			sequence =CCSequence::create(CCFadeIn::create(.2f),CCFadeTo::create(1.5f,255*1),CCFadeOut::create(.1f),NULL);
			words->runAction(sequence);
			isWords = false;
		}
	}
	if (words != NULL)
	{
		words->setPosition(ccp(armature->getPositionX() + armature->getContentSize().width/2,armature->getPositionY() + armature->getContentSize().height/2));
	}
}

void DynamicTargetNiuMoWang::getAwards(void)// 获得奖励
{
	Global::getInstance()->appendPetElementGet(PET_ELEMENT_NIUMOWANG, 1);
	Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 50);
}

void DynamicTargetNiuMoWang::setStatus(int _status, Hanger * _hanger)// 修改状态
{// 0 卖萌 1 凶狠 2 移动 3 攻击 4 晕 5 消失 
	if (dizzySpecialEffect != NULL)
	{
		dizzySpecialEffect->setVisible(false);
	}
#ifdef									GOLDEN_MINER2_FLASH_FRAME
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
			canCarry = true;
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
			canCarry = true;
		}
		isCarrierCarried = true;
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_MOVING:
		if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
			canCarry = true;
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);
		armature->setRotation(angleCenter - hanger->getAngle());
		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_NIUMOWANG_CARRIED);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		// 设置状态的同时要改变其动画
		armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);
		if (dizzySpecialEffect != NULL)
		{
			dizzySpecialEffect->setVisible(true);
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_SKILL:
		armature->getAnimation()->playByIndex(2 , 0, 160, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_SKILL_DISPLAY_TIME_COUNT;
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		armature->setVisible(false);
		canCarry = false;
		break;
	case NIUMOWANG_STATUS_DIZZY:
		armature->getAnimation()->playByIndex(3 , 0, 50, 1, TWEEN_EASING_MAX);
		if (dizzySpecialEffect != NULL)
		{
			dizzySpecialEffect->setVisible(true);
		}
		canCarry = true;
		carriedTimeCount = 0;
		break;
	default:
		break;
	}
#else
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
			canCarry = true;
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
			canCarry = true;
		}
		isCarrierCarried = true;
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_MOVING:
		if (type == DYNAMIC_TARGET_TYPE_PET)
		{
			armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
		}
		else
		{
			armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
			canCarry = true;
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		armature->setRotation(angleCenter - hanger->getAngle());
		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_NIUMOWANG_CARRIED);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		armature->getAnimation()->playByIndex(5 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		armature->getAnimation()->playByIndex(5 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		// 设置状态的同时要改变其动画
		armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		if (dizzySpecialEffect != NULL)
		{
			dizzySpecialEffect->setVisible(true);
		}
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_SKILL:
		armature->getAnimation()->playByIndex(3 , 0, 160, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_SKILL_DISPLAY_TIME_COUNT;
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		armature->setVisible(false);
		canCarry = false;
		break;
	case NIUMOWANG_STATUS_DIZZY:
		armature->getAnimation()->playByIndex(4 , 0, 50, 1, TWEEN_EASING_MAX);
		if (dizzySpecialEffect != NULL)
		{
			dizzySpecialEffect->setVisible(true);
		}
		canCarry = true;
		carriedTimeCount = 0;
		break;
	default:
		break;
	}
#endif
	lastStatus = status;
	status = _status;
}

int DynamicTargetNiuMoWang::getSpeed(void)// 获得移动目标被抓取的数度(负的)
{
	return 15;
}

int DynamicTargetNiuMoWang::getSpeedType(void)// 获得移动目标被抓取的数度(负的)
{
	return TARGET_SPEED_TYPE_B;
}

void DynamicTargetNiuMoWang::setArmatureByTypeAndStatus(int _type)
{
	armature = Armature::create("niumowang");
	armature->setScale(0.8);
	armature->setAnchorPoint(ccp(0.5, 0.5));
	armature->retain();
	armature->setPosition(currX ,currY);
	armature->setAnchorPoint(ccp(0.5,0.5));
	status = DYNAMIC_TARGET_STATUS_MOVING;
	lastStatus = DYNAMIC_TARGET_STATUS_MOVING;
	moveSpeed = 3;
	carriedDistance = 40;
}

void DynamicTargetNiuMoWang::setAngle(void)
{
	DynamicTarget::setAngle1();
}

bool DynamicTargetNiuMoWang::isIntersectById(int _id)// 返回是否与对应id的对象进行碰撞检测
{
	return true;
}

void DynamicTargetNiuMoWang::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger) // 与钩子碰撞的处理
{
	if (_hanger->getFunctionType() == HANGER_FUNCTION_TYPE_THROW)
	{
		setStatus(TARGET_STATUS_GOT_REMOVE, _hanger);
	}
	else
	{
		beCarriedCount++;
		if (beCarriedCount == 2)
		{
			DynamicTarget::doIntersectWithHanger(_gameControl, _hanger);
		}
		else if (beCarriedCount == 1)
		{// 牛魔王要抓两次才行
			if (_hanger->getFunctionType() == HANGER_FUNCTION_TYPE_BOMB)
			{
				_gameControl->addExplode(B_EXPLODE, _hanger->getCurrX(), _hanger->getCurrY());

				_hanger->setStatus(HANGER_STATUS_PULL_HAVING);
				Global::getInstance()->setContinuesCount(-1);
				setStatus(DYNAMIC_TARGET_STATUS_REMOVE, NULL);
				_hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
				_gameControl->role->setStatus(ROLE_STATUS_PULL_UNHAVING);
			}
			else if (_hanger->getFunctionType() == HANGER_FUNCTION_TYPE_THROW)
			{
				setStatus(TARGET_STATUS_GOT_REMOVE, _hanger);
				_gameControl->addExplode(HANGER_EXPLODE, _hanger->getCurrX(), _hanger->getCurrY());
			}
			else
			{
				_hanger->carryTargetType = -1;
				_hanger->carryTargetPoint = NULL;
				_hanger->setStatus(HANGER_STATUS_PULL_HAVING);
				_hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
				_hanger->setSpeedTarget(0, 0);
				_gameControl->role->setStatus(ROLE_STATUS_PULL_UNHAVING);
				setStatus(NIUMOWANG_STATUS_DIZZY, NULL);
			}
		}
	}
}

void DynamicTargetNiuMoWang::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)//碰撞到静态对象时候 的处理函数 
{
	DynamicTarget::intersectWithTarget(_id, _target, _gameControl);
	if (_id != TARGET_ID_BOMB)
	{
		setStatus(DYNAMIC_TARGET_STATUS_SKILL, NULL);
		_target->setStatus(TARGET_STATUS_REMOVE, NULL);// 破坏掉
	}
}
/******************************************************************
小丑鱼
*******************************************************************/
DynamicTargetXiaoChouYu::DynamicTargetXiaoChouYu(int _id, int _type, double _x, double _y)// 类型   起始坐标
:DynamicTarget(_id, _type, _x, _y)
{
	width = 50;
	height = 50;
	currX = currX + width/2;
	currY = currY + height/2;
	setArmatureByTypeAndStatus(_type);
	setStatus(status, NULL);
}

DynamicTargetXiaoChouYu::~DynamicTargetXiaoChouYu(void)
{

}

void DynamicTargetXiaoChouYu::doAction(float _f, GameControl * _gameControl)// 动作调用函数
{
	double _tmp;
	switch(status)
	{
	case DYNAMIC_TARGET_STATUS_MOVING:// 移动
		if (movePointCount != 0)
		{
			actionMove2(_f);
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:// 被抓住
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
			armature->setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
				, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
		// 被吸取  放缩   位置更改
		_tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//armature->setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		armature->setPosition(currX + vectorX * (1 - _tmp), currY + vectorY * (1 - _tmp));
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			getAwards();
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	default:
		break;
	}
	//roleSwaySpeed->setPosition(armature->getPosition());
}

void DynamicTargetXiaoChouYu::getAwards(void)// 获得奖励
{
	Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 120);
}

void DynamicTargetXiaoChouYu::setStatus(int _status, Hanger * _hanger)// 修改状态
{
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		CCLOG("小丑鱼没有静止状态");
		return;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		CCLOG("小丑鱼没有被云装载的状态");
		return;
	case DYNAMIC_TARGET_STATUS_MOVING:
		armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		armature->setRotation(angleCenter - hanger->getAngle());
		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_XIAOCHOUYU_CARRIED);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		// 设置状态的同时要改变其动画
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_SKILL:
		CCLOG("小丑鱼没有技能的状态");
		return;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		armature->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
	lastStatus = status;
	status = _status;
}

int DynamicTargetXiaoChouYu::getSpeed(void)// 获得移动目标被抓取的数度(负的)
{
	return 4;
}

int DynamicTargetXiaoChouYu::getSpeedType(void)// 获得移动目标被抓取的数度(负的)
{
	return TARGET_SPEED_TYPE_S;
}

void DynamicTargetXiaoChouYu::setArmatureByTypeAndStatus(int _type)
{
	armature = Armature::create("xiaochouyu");
	armature->setScale(0.8);
	armature->setAnchorPoint(ccp(0.5, 0.5));
	armature->retain();
	armature->setPosition(currX ,currY);

	type = _type;
	status = DYNAMIC_TARGET_STATUS_MOVING;
	lastStatus = status;
	moveSpeed = 5;
	carriedDistance = 0;
}

void DynamicTargetXiaoChouYu::setAngle(void)
{
	DynamicTarget::setAngle2();
}

bool DynamicTargetXiaoChouYu::isIntersectById(int _id)// 返回是否与对应id的对象进行碰撞检测
{
	if (_id == TARGET_ID_BOMB || (_id > DYNAMIC_ID_TYPE_START))
	{
		return true;
	}
	return false;
}

void DynamicTargetXiaoChouYu::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger) // 与钩子碰撞的处理
{
	DynamicTarget::doIntersectWithHanger(_gameControl, _hanger);
}

void DynamicTargetXiaoChouYu::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)//碰撞到静态对象时候 的处理函数 
{
	DynamicTarget::intersectWithTarget(_id, _target, _gameControl);
}
/******************************************************************
鸟
*******************************************************************/
DynamicTargetBrid::DynamicTargetBrid(int _id, int _type, double _x, double _y)// 类型   起始坐标
:DynamicTarget(_id, _type, _x, _y)
{
	width = 50;
	height = 50;
	currX = currX + width/2;
	currY = currY + height/2;
	moveSpeed = 5;
	setArmatureByTypeAndStatus(_type);
	setStatus(status, NULL);
}

DynamicTargetBrid::~DynamicTargetBrid(void)
{

}

void DynamicTargetBrid::doAction(float _f, GameControl * _gameControl)// 动作调用函数
{
	double _tmp;
	switch(status)
	{
	case DYNAMIC_TARGET_STATUS_MOVING:// 移动
		if (movePointCount != 0)
		{
			actionMove2(_f);
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:// 被抓住
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
			armature->setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
				, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
		// 被吸取  放缩   位置更改
		_tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//armature->setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		armature->setPosition(currX + vectorX * (1 - _tmp), currY + vectorY * (1 - _tmp));
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			getAwards();
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	default:
		break;
	}
	//roleSwaySpeed->setPosition(armature->getPosition());
}

void DynamicTargetBrid::getAwards(void)// 获得奖励
{
	Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 160);
}

void DynamicTargetBrid::setStatus(int _status, Hanger * _hanger)// 修改状态
{
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		CCLOG("鸟没有静止状态");
		return;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		CCLOG("鸟没有被云装载的状态");
		return;
	case DYNAMIC_TARGET_STATUS_MOVING:
		armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		armature->setRotation(angleCenter - hanger->getAngle());
		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BRID_CARRIED);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		// 设置状态的同时要改变其动画
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_SKILL:
		CCLOG("鸟没有技能的状态");
		return;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		armature->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
	lastStatus = status;
	status = _status;
}

int DynamicTargetBrid::getSpeed(void)// 获得移动目标被抓取的数度(负的)
{
	return 4;
}

int DynamicTargetBrid::getSpeedType(void)// 获得移动目标被抓取的数度(负的)
{
	return TARGET_SPEED_TYPE_S;
}

void DynamicTargetBrid::setArmatureByTypeAndStatus(int _type)
{
	armature = Armature::create("niao");
	armature->setScale(0.8);
	armature->setAnchorPoint(ccp(0.5, 0.5));
	armature->retain();
	armature->setPosition(currX ,currY);

	type = _type;
	status = DYNAMIC_TARGET_STATUS_MOVING;
	lastStatus = status;
	carriedDistance = 0;
}

void DynamicTargetBrid::setAngle(void)
{
	DynamicTarget::setAngle2();
}

bool DynamicTargetBrid::isIntersectById(int _id)// 返回是否与对应id的对象进行碰撞检测
{
	if (_id == TARGET_ID_BOMB || (_id > DYNAMIC_ID_TYPE_START))
	{
		return true;
	}
	return false;
}

void DynamicTargetBrid::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger) // 与钩子碰撞的处理
{
	DynamicTarget::doIntersectWithHanger(_gameControl, _hanger);
}

void DynamicTargetBrid::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)//碰撞到静态对象时候 的处理函数 
{
	DynamicTarget::intersectWithTarget(_id, _target, _gameControl);
}
/******************************************************************
珍珠贝
0 合上
1 打开
*******************************************************************/
DynamicTargetPearlShell::DynamicTargetPearlShell(int _id, int _type, double _x, double _y)// 类型   起始坐标
:DynamicTarget(_id, _type, _x, _y)
{
	// 珍珠贝只有原始状态
	width = 50;
	height = 50;
	currX = currX + width/2;
	currY = currY + height/2;
	shell = new DynamicTargetShell(DYNAMIC_ID_SHELL, DYNAMIC_TARGET_TYPE_NORMALE, _x, _y);// 创建自己的珍珠
	isNeedCheck = true;

	addChild(shell);
	type = DYNAMIC_TARGET_TYPE_NORMALE;
	setArmatureByTypeAndStatus(_type);
	setStatus(status, NULL);
	isGetValueWithShell = false;
}

DynamicTargetPearlShell::~DynamicTargetPearlShell(void)
{
}

void DynamicTargetPearlShell::doAction(float _f, GameControl * _gameControl)// 动作调用函数
{
	double _tmp;
	switch(status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:// 静止
		if (shell != NULL)// 有珍珠的时候  才会有状态变化
		{
			if (isNeedCheck)
			{
				if (isOpen)
				{
					timeCount++;
					if (timeCount == DYNAMIC_TARGET_PEARL_SHELL_TIME_OPEN_FRIST)
					{
						armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);// 打开状态
					}

					if (timeCount > DYNAMIC_TARGET_PEARL_SHELL_TIME_OPEN*3)
					{
						timeCount = 0;
						isOpen = false;
						armature->getAnimation()->playByIndex(0);// 合上状态
						shell->shellSprite->setVisible(false);// 贝壳里的珍珠不可见
					}
				}// 自己也要换图
				else
				{
					timeCount++;
					if (timeCount > DYNAMIC_TARGET_PEARL_SHELL_TIME_CLOSE)
					{
						timeCount = 0;
						isOpen = true;
						Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_PEAL_OPEN);
						armature->getAnimation()->playByIndex(1);// 打开状态
						shell->shellSprite->setVisible(false);// 贝壳里的珍珠可见
					}
				}
			}
			if (isNeedCheck)
			{
				if ((shell->getStatus() == DYNAMIC_TARGET_STATUS_DESTORY) 
					|| (shell->getStatus() == DYNAMIC_TARGET_STATUS_CARRIED)
					|| (shell->getStatus() == DYNAMIC_TARGET_STATUS_GOT_REMOVE)
					|| (shell->getStatus() == DYNAMIC_TARGET_STATUS_REMOVE))
				{
					isNeedCheck = false;
					timeCount = 0;
					isOpen = false;
					armature->getAnimation()->playByIndex(3);// 合上状态
				}
			}
			// 对珍珠的控制
			shell->doAction(_f, _gameControl);
			if (shell->getStatus() == DYNAMIC_TARGET_STATUS_DESTORY)
			{
				_gameControl->removeChild(shell->shellSprite);
				removeChild(shell,true);
				shell = NULL;
				isNeedCheck = false;
			}
		}
		else
		{
			armature->getAnimation()->playByIndex(0);// 打开状态
		}
		if (movePointCount != 0)
		{
			actionMove();
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:// 被抓住
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
			armature->setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
				, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
		// 被吸取  放缩   位置更改
		_tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//armature->setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		armature->setPosition(currX + vectorX * (1 - _tmp), currY + vectorY * (1 - _tmp));
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		getAwards();
		setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		break;
	default:
		break;
	}
	//roleSwaySpeed->setPosition(armature->getPosition());
}

void DynamicTargetPearlShell::getAwards(void)// 获得奖励
{
	Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 50);

	if (shell != NULL && isGetValueWithShell)
	{
		Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 600);
	}
}

void DynamicTargetPearlShell::setStatus(int _status, Hanger * _hanger)// 修改状态
{
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		isOpen = false;
		timeCount = 0;
		armature->getAnimation()->playByIndex(0);// 合上状态
		shell->shellSprite->setVisible(false);// 贝壳里的珍珠不可见
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		CCLOG("珍珠贝没有被云装载的状态");
		return;
	case DYNAMIC_TARGET_STATUS_MOVING:
		CCLOG("珍珠贝没有移动状态");
		return;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		armature->setRotation(angleCenter - hanger->getAngle());
		armature->getAnimation()->playByIndex(0);// 打开状态
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount = 1;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount = 1;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		canCarry = false;
		if (shell != NULL && isOpen)
		{
			shell->setStatus(DYNAMIC_TARGET_STATUS_GOURD, _hanger);
		}
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		CCLOG("珍珠贝没有晕眩的状态");
		return;
	case DYNAMIC_TARGET_STATUS_SKILL:
		CCLOG("珍珠贝没有技能的状态");
		return;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		armature->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
	lastStatus = status;
	status = _status;
}

int DynamicTargetPearlShell::getSpeed(void)// 获得移动目标被抓取的数度(负的)
{
	return 7;
}

int DynamicTargetPearlShell::getSpeedType(void)// 获得移动目标被抓取的数度(负的)
{
	return TARGET_SPEED_TYPE_M;
}

void DynamicTargetPearlShell::setArmatureByTypeAndStatus(int _type)
{
	armature = Armature::create("dabeike");
	armature->setScale(0.8);
	armature->setAnchorPoint(ccp(0.5, 0.5));
	armature->retain();
	armature->setPosition(currX ,currY);
	status = DYNAMIC_TARGET_STATUS_STATIC;// 初始状态就是静止状态
	lastStatus = status;
	carriedDistance = 22;
}

void DynamicTargetPearlShell::setAngle(void)
{
	DynamicTarget::setAngle1();
}

bool DynamicTargetPearlShell::isIntersectById(int _id)// 返回是否与对应id的对象进行碰撞检测
{
	if (_id == TARGET_ID_BOMB || (_id > DYNAMIC_ID_TYPE_START))
	{
		return true;
	}
	return false;
}

void DynamicTargetPearlShell::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger) // 与钩子碰撞的处理
{
	if (!isOpen)// 只有关闭的时候才能被抓
	{
		DynamicTarget::doIntersectWithHanger(_gameControl, _hanger);
	}
	else
	{// 打开的时候只能抓取珍珠
		CCRect rHanger = cocos2d::CCRectMake(
			_hanger->getPosition().x - (_hanger->getContentSize().width - INTERSECT_CONTROL)/2,
			_hanger->getPosition().y - (_hanger->getContentSize().height - INTERSECT_CONTROL)/2,
			_hanger->getContentSize().width - INTERSECT_CONTROL,
			_hanger->getContentSize().height - INTERSECT_CONTROL);
		CCRect rTmp = cocos2d::CCRectMake(
			shell->getCurrX(),
			shell->getCurrY(),
			shell->getWidth() - INTERSECT_CONTROL,
			shell->getHeight() - INTERSECT_CONTROL);
		if(rHanger.intersectsRect(rTmp))
		{
			shell->doIntersectWithHanger(_gameControl, _hanger);
		}
	}
}

void DynamicTargetPearlShell::setIsGetValueWithShell(bool _b)
{
	isGetValueWithShell = _b;
	if (_b && !isOpen)
	{
		isGetValueWithShell = false;
	}
}

CCSprite * DynamicTargetPearlShell::getShell(void)
{
	return shell->shellSprite;
}

void DynamicTargetPearlShell::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)//碰撞到静态对象时候 的处理函数 
{
	DynamicTarget::intersectWithTarget(_id, _target, _gameControl);
}
/******************************************************************
珍珠
*******************************************************************/
DynamicTargetShell::DynamicTargetShell(int _id, int _type, double _x, double _y)// 类型   起始坐标
:DynamicTarget(_id, _type, _x, _y)
{
	type = _type;
	setArmatureByTypeAndStatus(_type);
	setStatus(status, NULL);
}

DynamicTargetShell::~DynamicTargetShell(void)
{

}

void DynamicTargetShell::doAction(float _f, GameControl * _gameControl)// 动作调用函数
{
	double _tmp;
	switch(status)
	{
	case DYNAMIC_TARGET_STATUS_CARRIED:// 被抓住
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
			shellSprite->setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
				, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
		// 被吸取  放缩   位置更改
		_tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//armature->setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		shellSprite->setPosition(ccp(currX + vectorX * (1 - _tmp), currY + vectorY * (1 - _tmp)));
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		getAwards();
		setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		break;
	default: 
		break;
	}
}

void DynamicTargetShell::getAwards(void)// 获得奖励
{
	Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 600);
}

void DynamicTargetShell::setStatus(int _status, Hanger * _hanger)// 修改状态
{
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		CCLOG("珍珠没有被云装载的状态");
		return;
	case DYNAMIC_TARGET_STATUS_MOVING:
		CCLOG("珍珠没有移动状态");
		return;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		shellSprite->setZOrder(LAYER_ORDER_CONTROL-2);
		shellSprite->setRotation(angleCenter - hanger->getAngle());
		shellSprite->setVisible(true);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount = 1;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount = 1;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = shellSprite->getPositionX();
		currY = shellSprite->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		CCLOG("珍珠没有晕眩的状态");
		return;
	case DYNAMIC_TARGET_STATUS_SKILL:
		CCLOG("珍珠没有技能的状态");
		return;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		shellSprite->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
	lastStatus = status;
	status = _status;
}

int DynamicTargetShell::getSpeed(void)// 获得移动目标被抓取的数度(负的)
{
	return 4;
}

int DynamicTargetShell::getSpeedType(void)// 获得移动目标被抓取的数度(负的)
{
	return TARGET_SPEED_TYPE_S;
}

void DynamicTargetShell::setArmatureByTypeAndStatus(int _type)
{	
	shellSprite = CCSprite::create("flash/beike/zhenzhu.png");
	shellSprite->setScale(0.8);
	shellSprite->retain();
	width = shellSprite->getContentSize().width;
	height = shellSprite->getContentSize().height;
	currX = currX + 25;
	currY = currY + 33;
	shellSprite->setPosition(ccp(currX ,currY));
	status = DYNAMIC_TARGET_STATUS_STATIC;
	lastStatus = status;
	carriedDistance = 5;
}

void DynamicTargetShell::setAngle(void)
{
	DynamicTarget::setAngle1();
}

bool DynamicTargetShell::isIntersectById(int _id)// 返回是否与对应id的对象进行碰撞检测
{
	return false;
}

void DynamicTargetShell::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger) // 与钩子碰撞的处理
{
	DynamicTarget::doIntersectWithHanger(_gameControl, _hanger);
}

void DynamicTargetShell::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)//碰撞到静态对象时候 的处理函数 
{
	DynamicTarget::intersectWithTarget(_id, _target, _gameControl);
}
/******************************************************************
黄金
*******************************************************************/
DynamicTargetGolden::DynamicTargetGolden(int _id, int _type, double _x, double _y)// 类型   起始坐标
:DynamicTarget(_id, _type, _x, _y)
{
	//DynamicTarget::DynamicTarget(_id, _type, _x, _y);
}

DynamicTargetGolden::~DynamicTargetGolden(void)
{

}

void DynamicTargetGolden::doAction(float _f, GameControl * _gameControl)// 动作调用函数
{
	double _tmp;
	switch(status)
	{
	case DYNAMIC_TARGET_STATUS_MOVING:// 移动
		if (movePointCount != 0)
		{
			actionMove();
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:// 被抓住
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
			armature->setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
				, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
		// 被吸取  放缩   位置更改
		_tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//armature->setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		armature->setPosition(currX + vectorX * (1 - _tmp), currY + vectorY * (1 - _tmp));
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			getAwards();
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	default:
		break;
	}
	//roleSwaySpeed->setPosition(armature->getPosition());
}

void DynamicTargetGolden::getAwards(void)// 获得奖励
{
	Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 150);
}

void DynamicTargetGolden::setStatus(int _status, Hanger * _hanger)// 修改状态
{
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		CCLOG("珍珠贝没有被云装载的状态");
		return;
	case DYNAMIC_TARGET_STATUS_MOVING:
		CCLOG("鸟没有移动状态");
		return;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		armature->setRotation(angleCenter - hanger->getAngle());
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount = 1;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount = 1;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		CCLOG("鸟没有晕眩的状态");
		return;
	case DYNAMIC_TARGET_STATUS_SKILL:
		CCLOG("鸟没有技能的状态");
		return;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		armature->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
	lastStatus = status;
	status = _status;
}


int DynamicTargetGolden::getSpeed(void)// 获得移动目标被抓取的数度(负的)
{
	return 7;
}

int DynamicTargetGolden::getSpeedType(void)// 获得移动目标被抓取的数度(负的)
{
	return TARGET_SPEED_TYPE_S;
}

void DynamicTargetGolden::setArmatureByTypeAndStatus(int _type)
{
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("bajie", "", "flash/bajie.png", "flash/bajie.plist", "flash/bajie.xml");
	armature = Armature::create("bajie");
	armature->setScale(0.8);
	armature->setAnchorPoint(ccp(0.5, 0.5));
	armature->setPosition(currX ,currY);
	carriedDistance = 30;
	//armature->getDisplayRenderNode()->setZOrder(LAYER_ORDER_CONTROL);
	//armature->getZOrder();
}

void DynamicTargetGolden::setAngle(void)
{
	DynamicTarget::setAngle1();
}

bool DynamicTargetGolden::isIntersectById(int _id)// 返回是否与对应id的对象进行碰撞检测
{
	if (_id == TARGET_ID_BOMB || (_id > DYNAMIC_ID_TYPE_START))
	{
		return true;
	}
	return false;
}

void DynamicTargetGolden::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger) // 与钩子碰撞的处理
{
	DynamicTarget::doIntersectWithHanger(_gameControl, _hanger);
}

void DynamicTargetGolden::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)//碰撞到静态对象时候 的处理函数 
{
	DynamicTarget::intersectWithTarget(_id, _target, _gameControl);
}
/******************************************************************
石头
*******************************************************************/
DynamicTargetStone::DynamicTargetStone(int _id, int _type, double _x, double _y)// 类型   起始坐标
:DynamicTarget(_id, _type, _x, _y)
{
	//DynamicTarget::DynamicTarget(_id, _type, _x, _y);
}

DynamicTargetStone::~DynamicTargetStone(void)
{

}

void DynamicTargetStone::doAction(float _f, GameControl * _gameControl)// 动作调用函数
{
	double _tmp;
	switch(status)
	{
	case DYNAMIC_TARGET_STATUS_MOVING:// 移动
		if (movePointCount != 0)
		{
			actionMove();
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:// 被抓住
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
			armature->setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
				, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
		// 被吸取  放缩   位置更改
		_tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//armature->setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		armature->setPosition(currX + vectorX * (1 - _tmp), currY + vectorY * (1 - _tmp));
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			getAwards();
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	default:
		break;
	}
	//roleSwaySpeed->setPosition(armature->getPosition());
}

void DynamicTargetStone::getAwards(void)// 获得奖励
{
	Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 50);
}

void DynamicTargetStone::setStatus(int _status, Hanger * _hanger)// 修改状态
{
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		CCLOG("珍珠贝没有被云装载的状态");
		return;
	case DYNAMIC_TARGET_STATUS_MOVING:
		CCLOG("鸟没有移动状态");
		return;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		armature->setRotation(angleCenter - hanger->getAngle());
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount = 1;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount = 1;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		CCLOG("鸟没有晕眩的状态");
		return;
	case DYNAMIC_TARGET_STATUS_SKILL:
		CCLOG("鸟没有技能的状态");
		return;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		armature->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
	lastStatus = status;
	status = _status;
}

int DynamicTargetStone::getSpeed(void)// 获得移动目标被抓取的数度(负的)
{
	return 7;
}

int DynamicTargetStone::getSpeedType(void)// 获得移动目标被抓取的数度(负的)
{
	return TARGET_SPEED_TYPE_S;
}

void DynamicTargetStone::setArmatureByTypeAndStatus(int _type)
{
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("bajie", "", "flash/bajie.png", "flash/bajie.plist", "flash/bajie.xml");
	armature = Armature::create("bajie");
	armature->setScale(0.8);
	armature->setAnchorPoint(ccp(0.5, 0.5));
	armature->setPosition(currX ,currY);
	carriedDistance = 30;
	//armature->getDisplayRenderNode()->setZOrder(LAYER_ORDER_CONTROL);
	//armature->getZOrder();
}

void DynamicTargetStone::setAngle(void)
{
	DynamicTarget::setAngle1();
}

bool DynamicTargetStone::isIntersectById(int _id)// 返回是否与对应id的对象进行碰撞检测
{
	if (_id == TARGET_ID_BOMB || (_id > DYNAMIC_ID_TYPE_START))
	{
		return true;
	}
	return false;
}

void DynamicTargetStone::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger) // 与钩子碰撞的处理
{
	DynamicTarget::doIntersectWithHanger(_gameControl, _hanger);
}

void DynamicTargetStone::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)//碰撞到静态对象时候 的处理函数 
{
	DynamicTarget::intersectWithTarget(_id, _target, _gameControl);
}
/******************************************************************
蝙蝠
0 飞
1 晕
2 消失
*******************************************************************/
DynamicTargetBat::DynamicTargetBat(int _id, int _type, double _x, double _y)// 类型   起始坐标
:DynamicTarget(_id, _type, _x, _y)
{
	width = 50;
	height = 50;
	currX = currX + width/2;
	currY = currY + height/2;
	setArmatureByTypeAndStatus(_type);
	setStatus(status, NULL);
}

DynamicTargetBat::~DynamicTargetBat(void)
{

}

void DynamicTargetBat::doAction(float _f, GameControl * _gameControl)// 动作调用函数
{
	double _tmp;
	switch(status)
	{
	case DYNAMIC_TARGET_STATUS_MOVING:// 移动
		if (movePointCount != 0)
		{
			actionMove();
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:// 被抓住
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
			armature->setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
				, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
		// 被吸取  放缩   位置更改
		_tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//armature->setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		armature->setPosition(currX + vectorX * (1 - _tmp), currY + vectorY * (1 - _tmp));
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			getAwards();
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	default:
		break;
	}
	//roleSwaySpeed->setPosition(armature->getPosition());
}

void DynamicTargetBat::getAwards(void)// 获得奖励
{
	Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 160);
}

void DynamicTargetBat::setStatus(int _status, Hanger * _hanger)// 修改状态
{
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		CCLOG("蝙蝠没有静止状态");
		return;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		CCLOG("蝙蝠没有被云装载的状态");
		return;
	case DYNAMIC_TARGET_STATUS_MOVING:
		armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		armature->setRotation(angleCenter - hanger->getAngle());
		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BAT_CARRIED);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_SKILL:
		CCLOG("蝙蝠没有技能的状态");
		return;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		armature->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
	lastStatus = status;
	status = _status;
}

int DynamicTargetBat::getSpeed(void)// 获得移动目标被抓取的数度(负的)
{
	return 4;
}

int DynamicTargetBat::getSpeedType(void)// 获得移动目标被抓取的数度(负的)
{
	return TARGET_SPEED_TYPE_S;
}

void DynamicTargetBat::setArmatureByTypeAndStatus(int _type)
{
	armature = Armature::create("bianfu");
	armature->setScale(0.8);
	armature->setAnchorPoint(ccp(0.5, 0.5));
	armature->retain();
	armature->setPosition(currX ,currY);

	moveSpeed = 4;
	type = _type;
	status = DYNAMIC_TARGET_STATUS_MOVING;
	lastStatus = status;
	carriedDistance = 5;
}

void DynamicTargetBat::setAngle(void)
{
	DynamicTarget::setAngle1();
}

bool DynamicTargetBat::isIntersectById(int _id)// 返回是否与对应id的对象进行碰撞检测
{
	if (_id == TARGET_ID_BOMB || (_id > DYNAMIC_ID_TYPE_START))
	{
		return true;
	}
	return false;
}

void DynamicTargetBat::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger) // 与钩子碰撞的处理
{
	DynamicTarget::doIntersectWithHanger(_gameControl, _hanger);
}

void DynamicTargetBat::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)//碰撞到静态对象时候 的处理函数 
{
	DynamicTarget::intersectWithTarget(_id, _target, _gameControl);
}
/******************************************************************
蜘蛛

闪		0
抓		1
消失	2
*******************************************************************/
DynamicTargetSpider::DynamicTargetSpider(int _id, int _type, double _x, double _y)// 类型   起始坐标
:DynamicTarget(_id, _type, _x, _y)
{
	width = 50;
	height = 50;
	currX = currX + width/2;
	currY = currY + height/2;
	setArmatureByTypeAndStatus(_type);
	setStatus(status, NULL);
}

DynamicTargetSpider::~DynamicTargetSpider(void)
{

}

void DynamicTargetSpider::doAction(float _f, GameControl * _gameControl)// 动作调用函数
{
	double _tmp;
	switch(status)
	{
	case DYNAMIC_TARGET_STATUS_MOVING:// 移动
		if (movePointCount != 0)
		{
			actionMove();
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:// 被抓住
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
			armature->setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
				, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
		// 被吸取  放缩   位置更改
		_tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//armature->setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		armature->setPosition(currX + vectorX * (1 - _tmp), currY + vectorY * (1 - _tmp));
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			getAwards();
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount--;
		if (timeDisplayCount == 0)
		{
			setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		}
		break;
	default:
		break;
	}
	//roleSwaySpeed->setPosition(armature->getPosition());
}

void DynamicTargetSpider::getAwards(void)// 获得奖励
{
	Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 160);
}

void DynamicTargetSpider::setStatus(int _status, Hanger * _hanger)// 修改状态
{
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		CCLOG("蜘蛛没有静止状态");
		return;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		CCLOG("蜘蛛没有被云装载的状态");
		return;
	case DYNAMIC_TARGET_STATUS_MOVING:
		armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		armature->setRotation(angleCenter - hanger->getAngle());
		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		timeDisplayCount = DYANMIC_TARGET_REMOVE_DISPLAY_TIME_COUNT;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_SKILL:
		CCLOG("蜘蛛没有技能的状态");
		return;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		armature->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
}

int DynamicTargetSpider::getSpeed(void)// 获得移动目标被抓取的数度(负的)
{
	return 4;
}

int DynamicTargetSpider::getSpeedType(void)// 获得移动目标被抓取的数度(负的)
{
	return TARGET_SPEED_TYPE_S;
}

void DynamicTargetSpider::setArmatureByTypeAndStatus(int _type)
{
	armature = Armature::create("zhizhu");
	armature->setScale(0.8);
	armature->setAnchorPoint(ccp(0.5, 0.5));
	armature->retain();
	armature->setPosition(currX ,currY);

	moveSpeed = 4;
	type = _type;
	status = DYNAMIC_TARGET_STATUS_MOVING;
	lastStatus = status;
	carriedDistance = 30;
}

void DynamicTargetSpider::setAngle(void)
{
	DynamicTarget::setAngle2();
}

bool DynamicTargetSpider::isIntersectById(int _id)// 返回是否与对应id的对象进行碰撞检测
{
	if (_id == TARGET_ID_BOMB || (_id > DYNAMIC_ID_TYPE_START))
	{
		return true;
	}
	return false;
}

void DynamicTargetSpider::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger) // 与钩子碰撞的处理
{
	DynamicTarget::doIntersectWithHanger(_gameControl, _hanger);
}

void DynamicTargetSpider::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)//碰撞到静态对象时候 的处理函数 
{
	DynamicTarget::intersectWithTarget(_id, _target, _gameControl);
}
/******************************************************************
火花莲
0 红
1 蓝
*******************************************************************/
DynamicTargetHuoHuaLian::DynamicTargetHuoHuaLian(int _id, int _type, double _x, double _y)// 类型   起始坐标
:DynamicTarget(_id, _type, _x, _y)
{
	width = 50;
	height = 50;
	currX = currX + width/2;
	currY = currY + height/2;
	setArmatureByTypeAndStatus(_type);
	setStatus(status, NULL);
}

DynamicTargetHuoHuaLian::~DynamicTargetHuoHuaLian(void)
{

}

//void DynamicTargetHuoHuaLian::setCarrierInformation(void)
//{
//
//}

void DynamicTargetHuoHuaLian::doAction(float _f, GameControl * _gameControl)// 动作调用函数
{
	double _tmp;
	switch(status)
	{
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
	case DYNAMIC_TARGET_STATUS_STATIC:
		timeCount++;
		if (canBomb)
		{
			if (timeCount == DYNAMIC_TARGET_HUOHUALIAN_BOMB_TIME)
			{
				armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
				canBomb = false;
				type = DYNAMIC_TARGET_TYPE_NORMALE;
				timeCount = 0;
			}
		}
		else
		{
			if (timeCount == DYNAMIC_TARGET_HUOHUALIAN_NORMAL_TIME)
			{
				type = DYNAMIC_TARGET_TYPE_CARRIED_BOMB;
				armature->getAnimation()->playByIndex(0 , 0, 180, 1, TWEEN_EASING_MAX);
				canBomb = true;
				timeCount = 0;
			}
			else if (timeCount == (DYNAMIC_TARGET_HUOHUALIAN_NORMAL_TIME - 120))
			{
				//armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
			}
		}
		break;
	case DYNAMIC_TARGET_STATUS_CARRIED:// 被抓住
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
			armature->setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
				, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
		// 被吸取  放缩   位置更改
		_tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//armature->setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		armature->setPosition(currX + vectorX * (1 - _tmp), currY + vectorY * (1 - _tmp));
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		getAwards();
		setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		break;
	default:
		break;
	}
	//roleSwaySpeed->setPosition(armature->getPosition());
}

void DynamicTargetHuoHuaLian::getAwards(void)// 获得奖励
{
	if (!canBomb)
	{
		Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 50);
	}
	else
	{
		// 炸弹状态 给1块钱  
		Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 1);
		//Global::getInstance()->appendPropAwardGet(PROP_TYPE_GRENADE, 1);
	}
}

void DynamicTargetHuoHuaLian::setStatus(int _status, Hanger * _hanger)// 修改状态
{
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_MOVING:
		CCLOG("或莲花没有移动状态");
		return;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		armature->setRotation(angleCenter - hanger->getAngle());
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount = 1;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount = 1;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		CCLOG("或莲花没有晕眩的状态");
		return;
	case DYNAMIC_TARGET_STATUS_SKILL:
		CCLOG("或莲花没有技能的状态");
		return;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		armature->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
	lastStatus = status;
	status = _status;
}

int DynamicTargetHuoHuaLian::getSpeed(void)// 获得移动目标被抓取的数度(负的)
{
	return 7;
}

int DynamicTargetHuoHuaLian::getSpeedType(void)// 获得移动目标被抓取的数度(负的)
{
	return TARGET_SPEED_TYPE_M;
}

void DynamicTargetHuoHuaLian::setArmatureByTypeAndStatus(int _type)
{
	armature = Armature::create("huolianhua");
	armature->setScale(0.8);
	armature->setAnchorPoint(ccp(0.5, 0.5));
	armature->retain();
	armature->setPosition(currX ,currY);

	if (_type == DYNAMIC_TARGET_TYPE_CARRIED_BOMB)
	{
		armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		canBomb = true;
	}
	else
	{
		armature->getAnimation()->playByIndex(2 , 0, 50, 1, TWEEN_EASING_MAX);
		canBomb = false;
	}
	timeCount = 0;
	status = DYNAMIC_TARGET_STATUS_STATIC;
	lastStatus = status;
	carriedDistance = 2;
}

void DynamicTargetHuoHuaLian::setAngle(void)
{
	DynamicTarget::setAngle1();
}

bool DynamicTargetHuoHuaLian::isIntersectById(int _id)// 返回是否与对应id的对象进行碰撞检测
{
	if (_id == TARGET_ID_BOMB || (_id > DYNAMIC_ID_TYPE_START))
	{
		return true;
	}
	return false;
}

void DynamicTargetHuoHuaLian::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger) // 与钩子碰撞的处理
{
	DynamicTarget::doIntersectWithHanger(_gameControl, _hanger);
}

void DynamicTargetHuoHuaLian::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)//碰撞到静态对象时候 的处理函数 
{
	DynamicTarget::intersectWithTarget(_id, _target, _gameControl);
}

void DynamicTargetHuoHuaLian::setYunInformation(int _pointIndex, int _yunIndex)
{
	pointIndex = _pointIndex;
	yunIndex = _yunIndex;
}

int DynamicTargetHuoHuaLian::getYunIndex(void)
{
	return yunIndex;
}

int DynamicTargetHuoHuaLian::getPointIndex(void)
{
	return pointIndex;
}
/******************************************************************
星星

闪		0
抓		1
*******************************************************************/
DynamicTargetStar::DynamicTargetStar(int _id, int _type, double _x, double _y)// 类型   起始坐标
:DynamicTarget(_id, _type, _x, _y)
{
	width = 24;
	height = 24;
	currX = currX + width/2;
	currY = currY + height/2;
	type = _type;
	setArmatureByTypeAndStatus(_type);
	setStatus(status, NULL);
}

DynamicTargetStar::~DynamicTargetStar(void)
{

}

void DynamicTargetStar::doAction(float _f, GameControl * _gameControl)// 动作调用函数
{
	double _tmp;
	switch(status)
	{
	case DYNAMIC_TARGET_STATUS_CARRIED:// 被抓住
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
			armature->setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
				, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:// 被葫芦吸取的状态
		// 被吸取  放缩   位置更改
		_tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//armature->setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		armature->setPosition(currX + vectorX * (1 - _tmp), currY + vectorY * (1 - _tmp));
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		getAwards();
		setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		setStatus(DYNAMIC_TARGET_STATUS_DESTORY, NULL);
		break;
	default:
		break;
	}
	//roleSwaySpeed->setPosition(armature->getPosition());
}

void DynamicTargetStar::getAwards(void)// 获得奖励
{
	Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN, 100);
}

void DynamicTargetStar::setStatus(int _status, Hanger * _hanger)// 修改状态
{
	switch(_status)
	{
	case DYNAMIC_TARGET_STATUS_STATIC:
		armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_CARRIER_CARRIED:
		armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = true;
		break;
	case DYNAMIC_TARGET_STATUS_MOVING:
		CCLOG("星星没有移动状态");
		return;
	case DYNAMIC_TARGET_STATUS_CARRIED:
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		armature->setRotation(angleCenter - hanger->getAngle());
		armature->setZOrder(LAYER_ORDER_CONTROL-2);
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_STAR_CARRIED);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOT_REMOVE:
		timeDisplayCount = 1;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_REMOVE:
		timeDisplayCount = 1;
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_GOURD:
		// 如果更改为被吸取状态对应更新参数
		currX = armature->getPositionX();
		currY = armature->getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - currX;
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - currY;
		// 设置状态的同时要改变其动画
		armature->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
		canCarry = false;
		break;
	case DYNAMIC_TARGET_STATUS_DIZZY:
		armature->getAnimation()->playByIndex(1 , 0, 50, 1, TWEEN_EASING_MAX);
		break;
	case DYNAMIC_TARGET_STATUS_SKILL:
		CCLOG("星星没有技能的状态");
		return;
	case DYNAMIC_TARGET_STATUS_DESTORY:
		armature->setVisible(false);
		canCarry = false;
		break;
	default:
		break;
	}
	width = armature->getContentSize().width;
	height = armature->getContentSize().height;
	lastStatus = status;
	status = _status;
}

int DynamicTargetStar::getSpeed(void)// 获得移动目标被抓取的数度(负的)
{
	return 4;
}

int DynamicTargetStar::getSpeedType(void)// 获得移动目标被抓取的数度(负的)
{
	return TARGET_SPEED_TYPE_S;
}

void DynamicTargetStar::setArmatureByTypeAndStatus(int _type)
{
	armature = Armature::create("xingxing");
	armature->setScale(0.8);
	armature->setAnchorPoint(ccp(0.5, 0.5));
	armature->retain();
	armature->setPosition(currX ,currY);
	type = _type;
	status = DYNAMIC_TARGET_STATUS_STATIC;
	lastStatus = status;
	carriedDistance = 5;
}

void DynamicTargetStar::setAngle(void)
{
	DynamicTarget::setAngle1();
}

bool DynamicTargetStar::isIntersectById(int _id)// 返回是否与对应id的对象进行碰撞检测
{
	if (_id == TARGET_ID_BOMB || (_id > DYNAMIC_ID_TYPE_START))
	{
		return true;
	}
	return false;
}

void DynamicTargetStar::doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger) // 与钩子碰撞的处理
{
	DynamicTarget::doIntersectWithHanger(_gameControl, _hanger);
}

void DynamicTargetStar::intersectWithTarget(int _id, Target * _target, GameControl * _gameControl)//碰撞到静态对象时候 的处理函数 
{
	DynamicTarget::intersectWithTarget(_id, _target, _gameControl);
}

// 动态目标生成控制器
DynamicTargetControl::DynamicTargetControl(void)
{

}

DynamicTargetControl::~DynamicTargetControl(void)
{

}

DynamicTarget * DynamicTargetControl::getDynamicTargetById(int _id, int _type, double _x, double _y)
{

	DynamicTarget * res = NULL;
	switch (_id)
	{
	case DYNAMIC_ID_XIAOZUANFENG:// 小钻风
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_XIAOZUANFENG))
		{
			// 加载
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("xiaozuanfeng", "", "flash/xiaozuanfeng/xiaozhuanfeng.png", "flash/xiaozuanfeng/xiaozhuanfeng.plist", "flash/xiaozuanfeng/skeleton.xml");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_XIAOZUANFENG, true);
		}
		res = new DynamicTargetXiaoZuanFeng(_id, _type, _x, _y);
		break;
	case DYNAMIC_ID_JINGXIGUI:// 精细鬼
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_JINGXIGUI))
		{
			// 加载
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("jingxigui", "", "flash/jingxigui/jingxigui.png", "flash/jingxigui/jingxigui.plist", "flash/jingxigui/skeleton.xml");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_JINGXIGUI, true);
		}
		res = new DynamicTargetJingXiGui(_id, _type, _x, _y);
		break;
	case DYNAMIC_ID_LINGLICHONG:// 伶俐虫
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_LINGLICHONG))
		{
			// 加载
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("linglichong", "", "flash/linglichong/linglichong.png", "flash/linglichong/linglichong.plist", "flash/linglichong/skeleton.xml");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_LINGLICHONG, true);
		}
		res = new DynamicTargetLingLiChong(_id, _type, _x, _y);
		break;
	case DYNAMIC_ID_LINGGANDAWANG:// 灵感大王
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_LINGGANDAWANG))
		{
			// 加载
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("linggandawang", "", "flash/linggandawang/linggandawang.png", "flash/linggandawang/linggandawang.plist", "flash/linggandawang/skeleton.xml");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_LINGGANDAWANG, true);
		}
		res = new DynamicTargetLingGanDaWang(_id, _type, _x, _y);
		break;
	case DYNAMIC_ID_YUMIANGONGZHU:// 玉面公主
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_YUMIANGONGZHU))
		{
			// 加载
#ifdef									GOLDEN_MINER2_FLASH_FRAME
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("yumiangongzhu", "", "flash/yumiangongzhu/yumiangongzhu.png", "flash/yumiangongzhu/yumiangongzhu.plist", "flash/yumiangongzhu/skeleton.xml");
#else
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("yumian", "", "flash/yumiangongzhu/yumiangongzhu.png", "flash/yumiangongzhu/yumiangongzhu.plist", "flash/yumiangongzhu/skeleton.xml");
#endif
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_YUMIANGONGZHU, true);
		}
		res = new DynamicTargetYuMianGongZhu(_id, _type, _x, _y);
		break;
	case DYNAMIC_ID_NIUMOWANG:// 牛魔王
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_NIUMOWANG))
		{
			// 加载
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("niumowang", "", "flash/niumowang/niumowang.png", "flash/niumowang/niumowang.plist", "flash/niumowang/skeleton.xml");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_NIUMOWANG, true);
		}
		res = new DynamicTargetNiuMoWang(_id, _type, _x, _y);
		break;
	case DYNAMIC_ID_XIAOCHOUYU:// 小丑鱼
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_XIAOCHOUYU))
		{
			// 加载
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("xiaochouyu", "", "flash/xiaochouyu/xiaochouyu.png", "flash/xiaochouyu/xiaochouyu.plist", "flash/xiaochouyu/skeleton.xml");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_XIAOCHOUYU, true);
		}
		res = new DynamicTargetXiaoChouYu(_id, _type, _x, _y);
		break;
	case DYNAMIC_ID_BIRD:// 鸟
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_BIRD))
		{
			// 加载
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("niao", "", "flash/niao/niao.png", "flash/niao/niao.plist", "flash/niao/skeleton.xml");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_BIRD, true);
		}
		res = new DynamicTargetBrid(_id, _type, _x, _y);
		break;
	case DYNAMIC_ID_PEARL_SHELL: // 珍珠贝
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_PEARL_SHELL))
		{
			// 加载
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("dabeike", "", "flash/beike/beike.png", "flash/beike/beike.plist", "flash/beike/skeleton.xml");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_PEARL_SHELL, true);
		}
		res = new DynamicTargetPearlShell(_id, _type, _x, _y);
		break;
	case DYNAMIC_ID_GOLDEN:// 黄金
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_GOLDEN))
		{
			// 加载
			//cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("TestBone", "", "Armature/TestBone0.png", "Armature/TestBone0.plist", "Armature/TestBone.json");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_GOLDEN, true);
		}
		res = new DynamicTargetGolden(_id, _type, _x, _y);
		break;
	case DYNAMIC_ID_STONE:// 石头
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_STONE))
		{
			// 加载
			//cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("TestBone", "", "Armature/TestBone0.png", "Armature/TestBone0.plist", "Armature/TestBone.json");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_STONE, true);
		}
		res = new DynamicTargetStone(_id, _type, _x, _y);
		break;
	case DYNAMIC_ID_BAT:// 蝙蝠
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_BAT))
		{
			// 加载
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("bianfu", "", "flash/bianfu/bianfu.png", "flash/bianfu/bianfu.plist", "flash/bianfu/skeleton.xml");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_BAT, true);
		}
		res = new DynamicTargetBat(_id, _type, _x, _y);
		break;
	case DYNAMIC_ID_SPIDER:// 蜘蛛
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_SPIDER))
		{
			// 加载
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("zhizhu", "", "flash/zhizhu/zhizhu.png", "flash/zhizhu/zhizhu.plist", "flash/zhizhu/skeleton.xml");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_SPIDER, true);
		}
		res = new DynamicTargetSpider(_id, _type, _x, _y);
		break;
	case DYNAMIC_ID_HUOHUALIAN:// 或莲花
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_HUOHUALIAN))
		{
			// 加载
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("huolianhua", "", "flash/huolianhua/huolianhua.png", "flash/huolianhua/huolianhua.plist", "flash/huolianhua/skeleton.xml");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_HUOHUALIAN, true);
		}
		res = new DynamicTargetHuoHuaLian(_id, _type, _x, _y);
		break;
	case DYNAMIC_ID_STAR:// 星星
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_STAR))
		{
			// 加载
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("xingxing", "", "flash/xingxing/xingxing.png", "flash/xingxing/xingxing.plist", "flash/xingxing/skeleton.xml");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_STAR, true);
		}
		res = new DynamicTargetStar(_id, _type, _x, _y);
		break;
	default:
		break;
	}

	//res->roleSwaySpeed = CCLabelTTF::create("","Arial",10);
	//res->roleSwaySpeed->retain();
	//res->roleSwaySpeed->setPosition(res->getArmature()->getPosition());
	//char _s[64];
	//sprintf(_s, "weight: %d, moveSpeed: %lf",res->getSpeed(), res->getMoveSpeed());
	//res->roleSwaySpeed->setString(_s);

	return res;
}
