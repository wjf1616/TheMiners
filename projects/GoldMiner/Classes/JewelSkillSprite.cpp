#include "JewelSkillSprite.h"
#include "GameControl.h"
#include "IngotDrop.h"
#include "Alignment.h"
#include "Hanger.h"

/*************************************
JewelSkillSprite
**************************************/
JewelSkillSprite::JewelSkillSprite(void)
{
}

JewelSkillSprite::~JewelSkillSprite(void)
{
}

int JewelSkillSprite::getStatus(void)
{
	return status;
}

void JewelSkillSprite::doSkill(GameControl * _gameControl)
{

}

void JewelSkillSprite::updateSkill(float _f, GameControl * _gameControl)
{

}

void JewelSkillSprite::releaseSkill(GameControl * _gameControl)
{
}

/*************************************
JewelSkillBall
**************************************/
JewelSkillBall::JewelSkillBall(GameControl * _gameControl, Hanger * _hanger)
{
	status = JEWEL_SKILL_SPRITE_STATUS_NORMAL;
	initWithFile("youxi/guangqiu.png");
	_gameControl->setIsJewel(true);
	_gameControl->role->getHanger()->setVisible(false);
	_gameControl->role->doJewelSkill();
	hanger = _hanger;

	autorelease();
}

JewelSkillBall::~JewelSkillBall(void)
{
}

void JewelSkillBall::doSkill(GameControl * _gameControl)
{
	currX = hanger->getCurrX();
	currY = hanger->getCurrY();
	startY = currY;
	vectorX = cos(hanger->getAngle() / angleChange * pi);
	vectorY = sin(hanger->getAngle() / angleChange * pi);
	ballCollideCount = SKILL_ID_JEWEL_BALL_COUNT;
	//initWithFile("tmx/goods_025.png");
	setPosition(ccp(currX, currY));
	status = JEWEL_SKILL_SPRITE_STATUS_DOING;//变成释放技能的状态
	_gameControl->role->getHanger()->setStatus(HANGER_STATUS_PAUSE);
	_gameControl->role->getHanger()->setVisible(true);

	
	mySystem = CCParticleSystemQuad::create("lizitexiao/daojulizi/daojulizi.plist");//plist文件可以通过例子编辑器获得
	//mySystem = CCParticleSystemQuad::create("lizitexiao/guangqiu/guangqiu.plist");//plist文件可以通过例子编辑器获得
	mySystem->setPosition(ccp(getPositionX(), getPositionY()));
	_gameControl->addChild(mySystem, LAYER_ORDER_CONTROL);
}

void JewelSkillBall::updateSkill(float _f, GameControl * _gameControl)
{
	switch(status) {
	case JEWEL_SKILL_SPRITE_STATUS_NORMAL:
		// 只有装换角度和位置的问题
		setPosition(ccp(hanger->getCurrX(), hanger->getCurrY()));
		setRotation(angleCenter -hanger->getAngle());
		break;
	case JEWEL_SKILL_SPRITE_STATUS_DOING:
		if (ballCollideCount == 0)
		{
			status = JEWEL_SKILL_SPRITE_STATUS_FINISH;
		}
		else
		{
#ifdef							GOLDEN_MINER_2_VERSION_TIME
			currX += SKILL_ID_JEWEL_BALL_SPEED * vectorX * Global::getInstance()->getTimeRatio();
			currY += SKILL_ID_JEWEL_BALL_SPEED * vectorY * Global::getInstance()->getTimeRatio();
#else
			currX += SKILL_ID_JEWEL_BALL_SPEED * vectorX;
			currY += SKILL_ID_JEWEL_BALL_SPEED * vectorY;
#endif

			setPosition(ccp(currX, currY));
			mySystem->setPosition(ccp(currX, currY));

			if (currY < getContentSize().height/2)
			{
				ballCollideCount--;
				vectorY = -vectorY;

				currY = 2*getContentSize().height/2 - currY;

				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BALL);
			}
			else if(currX < getContentSize().width/2)
			{
				ballCollideCount--;
				vectorX = -vectorX;

				currX = 2*getContentSize().width/2 - currX;

				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BALL);
			}
			else if((currX + getContentSize().width/2) > CCDirector::sharedDirector()->getWinSize().width)
			{
				ballCollideCount--;
				vectorX = -vectorX;

				currX = 2*CCDirector::sharedDirector()->getWinSize().width - currX - getContentSize().width;

				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BALL);
			}
			else if (currY > startY)
			{
				//ballCollideCount = 0;
				ballCollideCount--;
				vectorY = -vectorY;

				currY = 2*startY - currY;

				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BALL);
			}

			CCRect rBall = cocos2d::CCRectMake(
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
					if (tmp->getStatus() == TARGET_STATUS_NORMAL || tmp->getStatus() == TARGET_STATUS_CARRIER_CARRIED)// 目标是可抓取的状态
					{
						// 抓取目标的碰撞矩阵
						CCRect rTmp = cocos2d::CCRectMake(
							tmp->getPosition().x - (tmp->getContentSize().width - INTERSECT_CONTROL)/2,
							tmp->getPosition().y - (tmp->getContentSize().height - INTERSECT_CONTROL)/2,
							tmp->getContentSize().width - INTERSECT_CONTROL,
							tmp->getContentSize().height - INTERSECT_CONTROL);
						if(rBall.intersectsRect(rTmp))
						{
							tmp->setStatus(TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
							_gameControl->addExplode(HANGER_EXPLODE, getPosition().x, getPosition().y);
						}
					}
				}
			}

			// 遍历移动对象
			if (_gameControl->gate->getDynamicTargets() != NULL)
			{		
				for(unsigned int i = 0; i < _gameControl->gate->getDynamicTargets()->count(); i++)
				{
					DynamicTarget * tmp = (DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i);
					//if (tmp->getStatus() != DYNAMIC_TARGET_STATUS_CARRIED)// 可抓取状态
					//{
						CCRect rTmp = cocos2d::CCRectMake(
							tmp->getArmature()->getPositionX() - (tmp->getWidth() - INTERSECT_CONTROL)/2,
							tmp->getArmature()->getPositionY() - (tmp->getHeight() - INTERSECT_CONTROL)/2,
							tmp->getWidth() - INTERSECT_CONTROL,
							tmp->getHeight() - INTERSECT_CONTROL);
						if(rBall.intersectsRect(rTmp))
						{
							if (tmp->getId() == DYNAMIC_ID_PEARL_SHELL)
							{
								((DynamicTargetPearlShell *)tmp)->setIsGetValueWithShell(true);
								_gameControl->addExplode(HANGER_EXPLODE, getPosition().x, getPosition().y);
							}
							
							tmp->setStatus(DYNAMIC_TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
						}
	/*				}*/
				}
			}
		}
		break;
	case JEWEL_SKILL_SPRITE_STATUS_FINISH:
		releaseSkill(_gameControl);
		break;
	default:
		break;
	}
}

void JewelSkillBall::releaseSkill(GameControl * _gameControl)
{
	_gameControl->jewelSkillId = -1;
	_gameControl->role->getHanger()->setStatus(HANGER_STATUS_SWAYING);
	_gameControl->removeChild(mySystem, true);
	_gameControl->removeChild(this);
	//CC_SAFE_RELEASE((JewelSkillBall *)_gameControl->jewelSkillSprite);
	_gameControl->setIsJewel(false);
	_gameControl->role->getHanger()->setStatus(HANGER_STATUS_SWAYING);
	_gameControl->role->releaseJewelSkill();
}

/*************************************
JewelSkillMagnet
**************************************/
JewelSkillMagnet::JewelSkillMagnet(GameControl * _gameControl, Hanger * _hanger)
{
	hanger = _hanger;

	Global::getInstance()->setJewelSkillScale(1);
	setPosition(ccp(hanger->getCurrX(), hanger->getCurrY()));
	setRotation(angleCenter - hanger->getAngle());
	status = JEWEL_SKILL_SPRITE_STATUS_NORMAL;
	initWithFile("youxi/xitie.png");
	_gameControl->setIsJewel(true);

	quene = CCSprite::create("youxi/60du.png");
	quene->setPosition(ccp(hanger->getCurrX() + SKILL_ID_JEWEL_MAGNET_QUENE_DISTANCE * cos(hanger->getAngle() / angleChange * pi)
		, hanger->getCurrY() + SKILL_ID_JEWEL_MAGNET_QUENE_DISTANCE * sin(hanger->getAngle() / angleChange * pi)));
	quene->setRotation(angleCenter - hanger->getAngle());
	_gameControl->addChild(quene, LAYER_ORDER_BACKGROUND+2);
	quene->setVisible(false);

	setVisible(false);
	if (hanger->getStatus() == HANGER_STATUS_THROW)
	{
		hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
	}
	else if (hanger->getStatus() == HANGER_STATUS_PULL_HAVING)
	{
		if(hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
		{
			hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
			hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
			Global::getInstance()->setContinuesCount(-1);
		}
		else if (hanger->carryTargetType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
		{
			hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
			hanger->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
			Global::getInstance()->setContinuesCount(-1);
		}
	}
	else
	{
		setVisible(true);
		_gameControl->role->getHanger()->setVisible(false);
	}
	_gameControl->role->doJewelSkill();

	//_gameControl->role->getHanger()->setVisible(false);
	autorelease();
}

JewelSkillMagnet::~JewelSkillMagnet(void)
{
}

void JewelSkillMagnet::doSkill(GameControl * _gameControl)
{
	jewelSkillTimeCount = 0;
	jewelSkillTime = SKILL_ID_JEWEL_MAGNET_ABSORB_TIME;	

	_gameControl->role->getHanger()->setStatus(HANGER_STATUS_PAUSE);

	mySystem = CCParticleSystemQuad::create("lizitexiao/shouji3/shouji3.plist");//plist文件可以通过例子编辑器获得
	mySystem->setPosition(ccp(getPositionX(), getPositionY()));
	mySystem->setRotation(angleCenter - hanger->getAngle());
	_gameControl->addChild(mySystem, LAYER_ORDER_CONTROL);

	float lastDistance = 0;

	if (_gameControl->gate->getTargets() != NULL)
	{
		for (unsigned int i = 0; i < _gameControl->gate->getTargets()->count(); i++)
		{
			Target * tmp = ((Target *)_gameControl->gate->getTargets()->objectAtIndex(i));
			//if (tmp->getTypeById() == TARGET_TYPE_GOLDEN)
			//{
			if(Global::getInstance()->intersectCCRectWithSector(
				tmp->getPosition().x - (tmp->getContentSize().width - INTERSECT_CONTROL)/2,
				tmp->getPosition().y - (tmp->getContentSize().height - INTERSECT_CONTROL)/2,
				tmp->getPosition().x + (tmp->getContentSize().width - INTERSECT_CONTROL)/2,
				tmp->getPosition().y + (tmp->getContentSize().width - INTERSECT_CONTROL)/2,
				hanger->getCurrX(), hanger->getCurrY(), hanger->getAngle() - SKILL_ID_JEWEL_MAGNET_DEGREE/2, hanger->getAngle() + SKILL_ID_JEWEL_MAGNET_DEGREE/2))
			{
				tmp->setStatus(TARGET_STATUS_MAGNETED, hanger);
				if (lastDistance < tmp->getDistance())
				{
					lastDistance = tmp->getDistance();
				}
			}
			//}
		}
	}

	if (_gameControl->gate->getDynamicTargets() != NULL)
	{
		for (unsigned int i = 0; i < _gameControl->gate->getDynamicTargets()->count(); i++)
		{
			DynamicTarget * tmp = ((DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i));
			CCRect rTmp = cocos2d::CCRectMake(
				tmp->getArmature()->getPositionX() - (tmp->getWidth() - INTERSECT_CONTROL)/2,
				tmp->getArmature()->getPositionY() - (tmp->getHeight() - INTERSECT_CONTROL)/2,
				tmp->getWidth() - INTERSECT_CONTROL,
				tmp->getHeight() - INTERSECT_CONTROL);

			if(Global::getInstance()->intersectCCRectWithSector(&rTmp, Global::getInstance()->getcentreX(), Global::getInstance()->getcentreY(), hanger->getAngle() - SKILL_ID_JEWEL_MAGNET_DEGREE/2, hanger->getAngle() + SKILL_ID_JEWEL_MAGNET_DEGREE/2))
			{
				if (tmp->getId() == DYNAMIC_ID_PEARL_SHELL)
				{
					((DynamicTargetPearlShell *)tmp)->setIsGetValueWithShell(true);
					_gameControl->addExplode(HANGER_EXPLODE, getPosition().x, getPosition().y);
				}

				tmp->setStatus(DYNAMIC_TARGET_STATUS_GOURD, hanger);
				if (lastDistance < tmp->getDistance())
				{
					lastDistance = tmp->getDistance();
				}
			}
		}
	}

	Global::getInstance()->setJewelSkillDistance(lastDistance);

	status = JEWEL_SKILL_SPRITE_STATUS_DOING;

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_ABSORB);

	_gameControl->setLiZiTeXiaoVisible(false);
	_gameControl->role->getAlignment()->setJewelSkillUnVisiable(true);
}

void JewelSkillMagnet::updateSkill(float _f, GameControl * _gameControl)
{
	switch(status) {
	case JEWEL_SKILL_SPRITE_STATUS_NORMAL:
		// 只有装换角度和位置的问题
		setPosition(ccp(hanger->getCurrX(), hanger->getCurrY()));
		setRotation(angleCenter - hanger->getAngle());
		
		if ((hanger->getStatus() == HANGER_STATUS_SWAYING || hanger->getStatus() == HANGER_STATUS_PAUSE) && !quene->isVisible())
		{
			quene->setVisible(true);
			setVisible(true);
			_gameControl->role->getHanger()->setVisible(false);
		}
		//else
		//{
		//	quene->setVisible(false);
		//}

		quene->setPosition(ccp(hanger->getCurrX() + SKILL_ID_JEWEL_MAGNET_QUENE_DISTANCE * cos(hanger->getAngle() / angleChange * pi)
			, hanger->getCurrY() + SKILL_ID_JEWEL_MAGNET_QUENE_DISTANCE * sin(hanger->getAngle() / angleChange * pi)));
		quene->setRotation(angleCenter - hanger->getAngle());
		break;
	case JEWEL_SKILL_SPRITE_STATUS_DOING:
#ifdef										GOLDEN_MINER_2_VERSION_TIME
		if (jewelSkillTimeCount*SCHEDULE_TIMES < jewelSkillTime)
		{
			jewelSkillTimeCount += _f;
			Global::getInstance()->setJewelSkillScale((jewelSkillTime - jewelSkillTimeCount*SCHEDULE_TIMES) / (double)jewelSkillTime);
		}
		else
		{
			status = JEWEL_SKILL_SPRITE_STATUS_FINISH;
		}
#else
		if (jewelSkillTimeCount < jewelSkillTime)
		{
			jewelSkillTimeCount++;
			Global::getInstance()->setJewelSkillScale((jewelSkillTime - jewelSkillTimeCount) / (double)jewelSkillTime);
		}
		else
		{
			status = JEWEL_SKILL_SPRITE_STATUS_FINISH;
		}
#endif
		break;
	case JEWEL_SKILL_SPRITE_STATUS_FINISH:
		releaseSkill(_gameControl);
		break;
	default:
		break;
	}
}

void JewelSkillMagnet::releaseSkill(GameControl * _gameControl)
{
	_gameControl->jewelSkillId = -1;
	_gameControl->role->getHanger()->setStatus(HANGER_STATUS_SWAYING);
	_gameControl->role->releaseJewelSkill();
	_gameControl->removeChild(mySystem, true);
	_gameControl->removeChild(quene, true);
	_gameControl->removeChild(this);
	//CC_SAFE_RELEASE((JewelSkillMagnet *)_gameControl->jewelSkillSprite);
	//setVisible(false);
	_gameControl->setIsJewel(false);
	_gameControl->role->getHanger()->setVisible(true);
	_gameControl->setLiZiTeXiaoVisible(true);
	_gameControl->role->getAlignment()->setJewelSkillUnVisiable(false);
}

/*************************************
JewelSkillGourd
**************************************/
JewelSkillGourd::JewelSkillGourd(GameControl * _gameControl, Hanger * _hanger)
{
	hanger = _hanger;

	Global::getInstance()->setJewelSkillScale(1);
	setPosition(ccp(hanger->getCurrX(), hanger->getCurrY()));
	setRotation(angleCenter - hanger->getAngle());
	status = JEWEL_SKILL_SPRITE_STATUS_NORMAL;
	initWithFile("youxi/hulu2.png");

	//_gameControl->setIsJewel(true);// 7.16 改为葫芦娃技能才屏蔽

	quene = CCSprite::create("youxi/45du.png");
	quene->setPosition(ccp(hanger->getCurrX() + SKILL_ID_JEWEL_MAGNET_QUENE_DISTANCE * cos(hanger->getAngle() / angleChange * pi)
		, hanger->getCurrY() + SKILL_ID_JEWEL_MAGNET_QUENE_DISTANCE * sin(hanger->getAngle() / angleChange * pi)));
	quene->setRotation(angleCenter - hanger->getAngle());
	quene->setVisible(false);

	_gameControl->addChild(quene, LAYER_ORDER_BACKGROUND+2);

	_gameControl->role->getHanger()->setVisible(false);
	autorelease();
}

JewelSkillGourd::~JewelSkillGourd(void)
{

}

void JewelSkillGourd::doSkill(GameControl * _gameControl)
{
	jewelSkillTimeCount = 0;
	jewelSkillTime = SKILL_ID_JEWEL_GOURD_ABSORB_TIME;

	mySystem = CCParticleSystemQuad::create("lizitexiao/shouji4/shouji4.plist");//plist文件可以通过例子编辑器获得
	mySystem->setPosition(ccp(getPositionX(), getPositionY()));
	mySystem->setRotation(angleCenter - hanger->getAngle());
	_gameControl->addChild(mySystem, LAYER_ORDER_CONTROL);

	_gameControl->role->getHanger()->setStatus(HANGER_STATUS_PAUSE);

	float lastDistance = 0;

	if (_gameControl->gate->getTargets() != NULL)
	{
		for (unsigned int i = 0; i < _gameControl->gate->getTargets()->count(); i++)
		{
			Target * tmp = ((Target *)_gameControl->gate->getTargets()->objectAtIndex(i));
			//if (tmp->getTypeById() == TARGET_TYPE_GOLDEN)
			//{
			if(Global::getInstance()->intersectCCRectWithSector(
				tmp->getPosition().x - (tmp->getContentSize().width - INTERSECT_CONTROL)/2,
				tmp->getPosition().y - (tmp->getContentSize().height - INTERSECT_CONTROL)/2,
				tmp->getPosition().x + (tmp->getContentSize().width - INTERSECT_CONTROL)/2,
				tmp->getPosition().y + (tmp->getContentSize().width - INTERSECT_CONTROL)/2,
				hanger->getCurrX(), hanger->getCurrY(), hanger->getAngle() - SKILL_ID_JEWEL_GOURD_DEGREE/2, hanger->getAngle() + SKILL_ID_JEWEL_GOURD_DEGREE/2))
			{
				tmp->setStatus(TARGET_STATUS_MAGNETED, hanger);
				if (lastDistance < tmp->getDistance())
				{
					lastDistance = tmp->getDistance();
				}
			}
			//}
		}
	}

	if (_gameControl->gate->getDynamicTargets() != NULL)
	{
		for (unsigned int i = 0; i < _gameControl->gate->getDynamicTargets()->count(); i++)
		{
			DynamicTarget * tmp = ((DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i));
			CCRect rTmp = cocos2d::CCRectMake(
				tmp->getArmature()->getPositionX() - (tmp->getWidth() - INTERSECT_CONTROL)/2,
				tmp->getArmature()->getPositionY() - (tmp->getHeight() - INTERSECT_CONTROL)/2,
				tmp->getWidth() - INTERSECT_CONTROL,
				tmp->getHeight() - INTERSECT_CONTROL);

			if(Global::getInstance()->intersectCCRectWithSector(&rTmp, Global::getInstance()->getcentreX(), Global::getInstance()->getcentreY(), hanger->getAngle() - SKILL_ID_JEWEL_GOURD_DEGREE/2, hanger->getAngle() + SKILL_ID_JEWEL_GOURD_DEGREE/2))
			{
				if (tmp->getId() == DYNAMIC_ID_PEARL_SHELL)
				{
					((DynamicTargetPearlShell *)tmp)->setIsGetValueWithShell(true);
					_gameControl->addExplode(HANGER_EXPLODE, getPosition().x, getPosition().y);
				}

				tmp->setStatus(DYNAMIC_TARGET_STATUS_GOURD, hanger);
				if (lastDistance < tmp->getDistance())
				{
					lastDistance = tmp->getDistance();
				}
			}
		}
	}

	Global::getInstance()->setJewelSkillDistance(lastDistance);

	status = JEWEL_SKILL_SPRITE_STATUS_DOING;

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_ABSORB);
	
	_gameControl->setLiZiTeXiaoVisible(false);
	_gameControl->role->getAlignment()->setJewelSkillUnVisiable(true);
}

void JewelSkillGourd::updateSkill(float _f, GameControl * _gameControl)
{
	switch(status) {
	case JEWEL_SKILL_SPRITE_STATUS_NORMAL:
		// 只有装换角度和位置的问题
		setPosition(ccp(hanger->getCurrX(), hanger->getCurrY()));
		setRotation(angleCenter - hanger->getAngle());
		
		if (isVisible() && (hanger->getStatus() == HANGER_STATUS_SWAYING || hanger->getStatus() == HANGER_STATUS_PAUSE))
		{
			quene->setVisible(true);
		}
		else
		{
			quene->setVisible(false);
		}

		quene->setPosition(ccp(hanger->getCurrX() + SKILL_ID_JEWEL_MAGNET_QUENE_DISTANCE * cos(hanger->getAngle() / angleChange * pi)
			, hanger->getCurrY() + SKILL_ID_JEWEL_MAGNET_QUENE_DISTANCE * sin(hanger->getAngle() / angleChange * pi)));
		quene->setRotation(angleCenter - hanger->getAngle());
		break;
	case JEWEL_SKILL_SPRITE_STATUS_DOING:
#ifdef						GOLDEN_MINER_2_VERSION_TIME
		if (jewelSkillTimeCount*SCHEDULE_TIMES < jewelSkillTime)
		{
			jewelSkillTimeCount += _f;
			Global::getInstance()->setJewelSkillScale((jewelSkillTime - jewelSkillTimeCount*SCHEDULE_TIMES) / (double)jewelSkillTime);
		}
		else
		{
			status = JEWEL_SKILL_SPRITE_STATUS_FINISH;
		}
#else
		if (jewelSkillTimeCount < jewelSkillTime)
		{
			jewelSkillTimeCount++;
			Global::getInstance()->setJewelSkillScale((jewelSkillTime - jewelSkillTimeCount) / (double)jewelSkillTime);
		}
		else
		{
			status = JEWEL_SKILL_SPRITE_STATUS_FINISH;
		}
#endif
		break;
	case JEWEL_SKILL_SPRITE_STATUS_FINISH:
		releaseSkill(_gameControl);
		break;
	default:
		break;
	}
}

void JewelSkillGourd::releaseSkill(GameControl * _gameControl)
{
	//_gameControl->jewelSkillId = -1;// 7.16 改为葫芦娃技能才屏蔽

	_gameControl->role->getHanger()->setStatus(HANGER_STATUS_SWAYING);
	_gameControl->removeChild(mySystem, true);
	_gameControl->removeChild(quene, true);
	_gameControl->removeChild(this);

	//_gameControl->setIsJewel(false);// 7.16 改为葫芦娃技能才屏蔽

	_gameControl->role->getHanger()->setVisible(true);
	_gameControl->setLiZiTeXiaoVisible(true);
	_gameControl->role->getAlignment()->setJewelSkillUnVisiable(false);
}

/*************************************
JewelSkillDizzy
**************************************/

JewelSkillDizzy::JewelSkillDizzy(GameControl * _gameControl)
{
	status = JEWEL_SKILL_SPRITE_STATUS_NORMAL;
	jewelSkillTimeCount = 0;
	jewelSkillTime = 1;
	_gameControl->setIsJewel(true);
}

JewelSkillDizzy::~JewelSkillDizzy(void)
{

}

void JewelSkillDizzy::doSkill(GameControl * _gameControl)
{
	jewelSkillTimeCount = 0;
	jewelSkillTime = 600;

	mySystem = CCParticleSystemQuad::create("lizitexiao/yunxuan/yunxuan.plist");//plist文件可以通过例子编辑器获得
	mySystem->setPosition(ccp(400, 200));
	_gameControl->addChild(mySystem, LAYER_ORDER_CONTROL);
	if(_gameControl->gate->getDynamicTargets() != NULL)
	{
		for (unsigned int i = 0; i < _gameControl->gate->getDynamicTargets()->count(); i++)
		{
			if ((((DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i))->getId() >= DYNAMIC_ID_XIAOZUANFENG) && (((DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i))->getId() <= DYNAMIC_ID_NIUMOWANG))
			{
				((DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i))->setStatus(DYNAMIC_TARGET_STATUS_DIZZY, NULL);
			}
		}
	}
	status = JEWEL_SKILL_SPRITE_STATUS_DOING;
}

void JewelSkillDizzy::updateSkill(float _f, GameControl * _gameControl)
{
#ifdef						GOLDEN_MINER_2_VERSION_TIME
	switch(status) {
	case JEWEL_SKILL_SPRITE_STATUS_NORMAL:
		if (jewelSkillTimeCount*SCHEDULE_TIMES < jewelSkillTime)
		{
			jewelSkillTimeCount += _f;
		}
		else
		{
			doSkill(_gameControl);// 晕  直接释放技能
		}
		break;
	case JEWEL_SKILL_SPRITE_STATUS_DOING:
		if (jewelSkillTimeCount*SCHEDULE_TIMES < jewelSkillTime)
		{
			jewelSkillTimeCount += _f;
		}
		else
		{
			status = JEWEL_SKILL_SPRITE_STATUS_FINISH;
		}
		break;
	case JEWEL_SKILL_SPRITE_STATUS_FINISH:
		releaseSkill(_gameControl);
		break;
	default:
		break;
	}
#else
	switch(status) {
	case JEWEL_SKILL_SPRITE_STATUS_NORMAL:
		if (jewelSkillTimeCount < jewelSkillTime)
		{
			jewelSkillTimeCount++;
		}
		else
		{
			doSkill(_gameControl);// 晕  直接释放技能
		}
		break;
	case JEWEL_SKILL_SPRITE_STATUS_DOING:
		if (jewelSkillTimeCount < jewelSkillTime)
		{
			jewelSkillTimeCount++;
		}
		else
		{
			status = JEWEL_SKILL_SPRITE_STATUS_FINISH;
		}
		break;
	case JEWEL_SKILL_SPRITE_STATUS_FINISH:
		releaseSkill(_gameControl);
		break;
	default:
		break;
	}
#endif
}

void JewelSkillDizzy::releaseSkill(GameControl * _gameControl)
{
	// 恢复晕前的状态
	_gameControl->removeChild(mySystem, true);
	if(_gameControl->gate->getDynamicTargets() != NULL)
	{
		for (unsigned int i = 0; i < _gameControl->gate->getDynamicTargets()->count(); i++)
		{
			if ((((DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i))->getId() >= DYNAMIC_ID_XIAOZUANFENG)
				&& (((DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i))->getId() <= DYNAMIC_ID_NIUMOWANG)
				&& (((DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i))->getStatus() == DYNAMIC_TARGET_STATUS_DIZZY))
			{
				((DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i))->recoverLastStatus();
			}
		}
	}
	
	_gameControl->jewelSkillId = -1;
	_gameControl->setIsJewel(false);
}

/*************************************
JewelSkillDrop
**************************************/
#define							JEWEL_SKILL_DROP_APPEND_TIME	180
JewelSkillDrop::JewelSkillDrop(GameControl * _gameControl)
	:JewelSkillSprite()
{
	mSystem = NULL;
	status = JEWEL_SKILL_SPRITE_STATUS_NORMAL;
	drops = new CCArray();
	award = 0;
	doSkill(_gameControl);// 下铜钱 马上触发
}

JewelSkillDrop::~JewelSkillDrop(void)
{
	CCObject * p;
}

void JewelSkillDrop::doSkill(GameControl * _gameControl)
{
	awardNum = NULL;
	award = rand()%501 + 500;
	jewelSkillTimeCount = 0;
	jewelSkillVoiceTime = 0;
	jewelSkillTime = 240;
	status = JEWEL_SKILL_SPRITE_STATUS_DOING;
	_gameControl->setIsJewel(true);
	_gameControl->role->getAlignment()->setJewelSkillUnVisiable(true);
}

void JewelSkillDrop::updateSkill(float _f, GameControl * _gameControl)
{
	switch(status) {
	case JEWEL_SKILL_SPRITE_STATUS_NORMAL:
		doSkill(_gameControl);// 下铜钱 马上触发
		break;
	case JEWEL_SKILL_SPRITE_STATUS_DOING:
#ifdef										GOLDEN_MINER_2_VERSION_TIME
		if (jewelSkillTimeCount < jewelSkillTime/((float)SCHEDULE_TIMES))
		{
			if ((mSystem == NULL))// && (jewelSkillTimeCount > 10))
			{
				mSystem = CCParticleSystemQuad::create("lizitexiao/tongqian/tongqian.plist");//plist文件可以通过例子编辑器获得
				mSystem->setPosition(ccp(400,0));//设置位置  
				_gameControl->addChild(mSystem, LAYER_ORDER_CONTROL+1);  
			}
			jewelSkillTimeCount += _f;
			jewelSkillVoiceTime += _f;
			if(jewelSkillVoiceTime > 0.3)
			{
				jewelSkillVoiceTime = 0;
				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_DROP);
			}

			if((jewelSkillTimeCount > JEWEL_SKILL_DROP_APPEND_TIME/((float)SCHEDULE_TIMES)) && ((jewelSkillTimeCount - _f) < JEWEL_SKILL_DROP_APPEND_TIME/((float)SCHEDULE_TIMES)))
			{
				char _s[24];

				sprintf(_s, "%d",award);
				awardNum = CCLabelAtlas::create(_s, "texiao/foguang/shuzi.png", 24, 37, '0');
				awardNum->setPosition(350, 280);
				awardNum->runAction(CCSpawn::create(CCFadeIn::create((jewelSkillTime/((float)SCHEDULE_TIMES) - jewelSkillTimeCount)/2),CCScaleTo::create((jewelSkillTime/((float)SCHEDULE_TIMES) - jewelSkillTimeCount)/2,1.8),NULL));
				_gameControl->addChild(awardNum, LAYER_ORDER_CONTROL+2);  
			}
		}
		else
		{
			status = JEWEL_SKILL_SPRITE_STATUS_FINISH;
		}
#else
		if (jewelSkillTimeCount < jewelSkillTime)
		{
			if ((mSystem == NULL))// && (jewelSkillTimeCount > 10))
			{
				mSystem = CCParticleSystemQuad::create("lizitexiao/tongqian/tongqian.plist");//plist文件可以通过例子编辑器获得
				mSystem->setPosition(ccp(400,0));//设置位置  
				_gameControl->addChild(mSystem, LAYER_ORDER_CONTROL+1);  
			}
			jewelSkillTimeCount++;
			if(jewelSkillTimeCount % 20 == 0)
			{
				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_DROP);
			}

			if(jewelSkillTimeCount == JEWEL_SKILL_DROP_APPEND_TIME)
			{
				char _s[24];

				sprintf(_s, "%d",award);
				awardNum = CCLabelAtlas::create(_s, "texiao/foguang/shuzi.png", 24, 37, '0');
				awardNum->setPosition(400, 240);
				awardNum->runAction(CCSpawn::create(CCFadeIn::create((jewelSkillTime - JEWEL_SKILL_DROP_APPEND_TIME)/((float)SCHEDULE_TIMES)),CCScaleTo::create((jewelSkillTime - JEWEL_SKILL_DROP_APPEND_TIME)/((float)SCHEDULE_TIMES),2),NULL));
				_gameControl->addChild(awardNum, LAYER_ORDER_CONTROL+2);  
			}
			//if(jewelSkillTimeCount % 5 == 0)
			//{
			//drops->addObject(new IngotDrop(2,20,30));
			//((IngotDrop *)drops->lastObject())->setPosition(ccp(rand()%20*40, 470));
			//_gameControl->addChild(((IngotDrop *)drops->lastObject()), LAYER_ORDER_CONTROL+1); 
			//}

			//for(int i = 0; i < drops->count(); i++)
			//{
			//	
			//	CCArray * removeIndexExplode = CCArray::create();

			//	for(unsigned int i = 0; i < drops->count(); i++)
			//	{
			//		IngotDrop * tmp = ((IngotDrop  *)drops->objectAtIndex(i));
			//		if(tmp->doAction(_f))
			//		{
			//			removeIndexExplode->addObject(CCInteger::create(i));
			//		}
			//	}

			//	 移除该移除的对象
			//	for (unsigned int i = removeIndexExplode->count(); i >0; i--)
			//	{
			//		_gameControl->removeChild((IngotDrop *)(drops->objectAtIndex(((CCInteger *)removeIndexExplode->objectAtIndex(i-1))->getValue())),true);
			//		drops->removeObject((IngotDrop *)(drops->objectAtIndex(((CCInteger *)removeIndexExplode->objectAtIndex(i-1))->getValue())),true);
			//		removeIndexExplode->removeObjectAtIndex(i-1,true);
			//	}
			//}
		}
		else
		{
			status = JEWEL_SKILL_SPRITE_STATUS_FINISH;
		}
#endif
		break;
	case JEWEL_SKILL_SPRITE_STATUS_FINISH:
		releaseSkill(_gameControl);
		break;
	default:
		break;
	}
}

void JewelSkillDrop::releaseSkill(GameControl * _gameControl)
{
	// 获得价钱在500 - 1000之间
	_gameControl->removeChild(mSystem); 
	_gameControl->removeChild(awardNum); 
	//for(int i = 0; i < drops->count(); i++)
	//{
	//	_gameControl->removeChild((IngotDrop *)drops->objectAtIndex(i)); 
	//}
	Global::getInstance()->appendPropAwardGet(PROP_TYPE_COIN,award);
	_gameControl->jewelSkillId = -1;
	_gameControl->setIsJewel(false);
	_gameControl->role->getAlignment()->setJewelSkillUnVisiable(false);
}

/*************************************
JewelSkillFiveHanger
**************************************/
#define				NORMAL_DISTANCE_TO_CENTER			32
#define				NORMAL_DISTANCE_TO_ROPE				10
#define				NORMAL_THROW_SPEED					30
JewelSkillFiveHanger::JewelSkillFiveHanger(GameControl * _gameControl)
	:JewelSkillSprite()
{
	CCLayer();

	mSystem = NULL;
	status = JEWEL_SKILL_SPRITE_STATUS_NORMAL;
	hangers = new CCArray();
	doSkill(_gameControl);// 下铜钱 马上触发
}

JewelSkillFiveHanger::~JewelSkillFiveHanger(void)
{
	CCObject * p;
}

void JewelSkillFiveHanger::doSkill(GameControl * _gameControl)
{
	_gameControl->role->doJewelSkill();
	_gameControl->role->getHanger()->setStatus(HANGER_STATUS_PAUSE);
	_gameControl->role->getHanger()->setVisible(false);
	_gameControl->role->getHanger()->getRope()->setVisible(false);
	jewelSkillTimeCount = 0;
	jewelSkillTime = 1;
	status = JEWEL_SKILL_SPRITE_STATUS_DOING;
	_gameControl->setIsJewel(true);
	_gameControl->role->getAlignment()->setJewelSkillUnVisiable(true);


	for (int i = 0; i < 5; i++)
	{
		hangers->addObject(new Hanger(NORMAL_DISTANCE_TO_CENTER, NORMAL_DISTANCE_TO_ROPE, 0, NORMAL_THROW_SPEED, 0, 1));
		((Hanger *)hangers->lastObject())->initWithFile("youxi/gouzi.png");
		((Hanger *)hangers->lastObject())->setAngle((330 - 210)*i/(5-1) + 210);
		_gameControl->addChild(((Hanger *)hangers->lastObject())->getRope(), LAYER_ORDER_CONTROL - 1);
		_gameControl->addChild(((Hanger *)hangers->lastObject()), LAYER_ORDER_CONTROL - 1);
	}
}

void JewelSkillFiveHanger::updateSkill(float _f, GameControl * _gameControl)
{	
	Hanger * tmp;
	int count = 0;

	switch(status) {
	case JEWEL_SKILL_SPRITE_STATUS_NORMAL:
		doSkill(_gameControl);// 下铜钱 马上触发
		break;
	case JEWEL_SKILL_SPRITE_STATUS_DOING:
		jewelSkillTimeCount++;
		for (int i = 0; i < hangers->count(); i++)
		{
			((Hanger *)hangers->objectAtIndex(i))->doAction(_f, _gameControl);
		}

		if (jewelSkillTimeCount == jewelSkillTime)
		{
			for (int i = 0; i < hangers->count(); i++)
			{
				((Hanger *)hangers->objectAtIndex(i))->setStatus(HANGER_STATUS_THROW);
			}
		}
		else if (jewelSkillTimeCount > jewelSkillTime)
		{
			for (int i = 0; i < hangers->count(); i++)
			{
				tmp = (Hanger *)hangers->objectAtIndex(i);
				if (tmp->getStatus() == HANGER_STATUS_SWAYING)
				{
					count++;
					tmp->setVisible(false);
					tmp->getRope()->setVisible(false);
				}
			}
		}

		if (hangers->count() == count)
		{
			status = JEWEL_SKILL_SPRITE_STATUS_FINISH;
		}
		break;
	case JEWEL_SKILL_SPRITE_STATUS_FINISH:
		releaseSkill(_gameControl);
		break;
	default:
		break;
	}
}

void JewelSkillFiveHanger::releaseSkill(GameControl * _gameControl)
{
	_gameControl->role->getHanger()->setStatus(HANGER_STATUS_SWAYING);
	_gameControl->role->getHanger()->setVisible(true);
	_gameControl->role->getHanger()->getRope()->setVisible(true);

	_gameControl->jewelSkillId = -1;
	_gameControl->setIsJewel(false);
	_gameControl->role->getAlignment()->setJewelSkillUnVisiable(false);
	_gameControl->role->releaseJewelSkill();

	for (int i = 0; i < 5; i++)
	{
		_gameControl->removeChild(((Hanger *)hangers->objectAtIndex(i))->getRope(), LAYER_ORDER_CONTROL - 1);
		_gameControl->removeChild(((Hanger *)hangers->objectAtIndex(i)), LAYER_ORDER_CONTROL - 1);
	}

	CCObject * p = NULL;
	CCARRAY_FOREACH(hangers, p)
	{
		CC_SAFE_RELEASE(p);
	}
}