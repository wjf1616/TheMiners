#include "Target.h"
#include "GameControl.h"

#define			TAEGET_EXCHANGE_BITMAP_TIME		0.5

Target::Target(double _x, double _y, int _id, int _pointIndex, int _yunIndex)
{
	CCSprite();
	
	effect = NULL;
	status = TARGET_STATUS_NORMAL;
	canCarry = true;
	hideCount = 0;
	pointIndex = _pointIndex;
	yunIndex = _yunIndex;
	id = _id;
	initById();
	startX = _x + getContentSize().width/2;
	startY = _y + getContentSize().height/2;
	setPosition(ccp(startX, startY));

	//CCLabelTTF * roleSwaySpeed = CCLabelTTF ::create("","Arial",10);
	////roleSwaySpeed->setPosition(ccp(startX, startY));
	//char _s[64];
	//sprintf(_s, "weight: %d",getSpeed());
	//roleSwaySpeed->setString(_s);
	//addChild(roleSwaySpeed); 

	// 自动释放资源
	autorelease();
}

Target::~Target(void)
{
	//CC_SAFE_RELEASE(hanger);
}

int Target::getSpeed(void)
{
	int speed = 0;
	switch(id)
	{
	case TARGET_ID_BOMB:
		speed = 0;
		break;
	case TARGET_ID_BOX:
		speed = 9;
		break;
	case TARGET_ID_GOLDEN_S:
		speed = 4;
		break;
	case TARGET_ID_GOLDEN_M:
		speed = 7;
		break;
	case TARGET_ID_GOLDEN_B:
		speed = 10;
		break;
	case TARGET_ID_STONE_S:
		speed = 6;
		break;
	case TARGET_ID_STONE_M:
		speed = 9;
		break;
	case TARGET_ID_STONE_B:
		speed = 15;
		break;
	case TARGET_ID_DIAMOND:
		speed = 4;
		break;
	case TARGET_ID_COAL:
		speed = 4;
		break;
	case TARGET_ID_TRUNK: 
		speed = 7;
		break;
	case TARGET_ID_JEWEL_BLUE:
		speed = 4;
		break;
	case TARGET_ID_JEWEL_RED:
		speed = 4;
		break;
	case TARGET_ID_JEWEL_GREEN:
		speed = 4;
		break;
	case TARGET_ID_JEWEL_YELLOW:
		speed = 4;
		break;
	case TARGET_ID_JEWEL_PURPLE:
		speed = 4;
		break;
	case TARGET_ID_FOOD:
		speed = 4;
		break;
	default:
		break;
	}
	return speed;
}

int Target::getSpeedType(void)
{
	int speed = 0;
	switch(id)
	{
	case TARGET_ID_BOMB:
		speed = TARGET_SPEED_TYPE_S;
		break;
	case TARGET_ID_BOX:
		speed = TARGET_SPEED_TYPE_M;
		break;
	case TARGET_ID_GOLDEN_S:
		speed = TARGET_SPEED_TYPE_S;
		break;
	case TARGET_ID_GOLDEN_M:
		speed = TARGET_SPEED_TYPE_M;
		break;
	case TARGET_ID_GOLDEN_B:
		speed = TARGET_SPEED_TYPE_B;
		break;
	case TARGET_ID_STONE_S:
		speed = TARGET_SPEED_TYPE_S;
		break;
	case TARGET_ID_STONE_M:
		speed = TARGET_SPEED_TYPE_M;
		break;
	case TARGET_ID_STONE_B:
		speed = TARGET_SPEED_TYPE_B;
		break;
	case TARGET_ID_DIAMOND:
		speed = TARGET_SPEED_TYPE_S;
		break;
	case TARGET_ID_COAL:
		speed = TARGET_SPEED_TYPE_S;
		break;
	case TARGET_ID_TRUNK: 
		speed = TARGET_SPEED_TYPE_M;
		break;
	case TARGET_ID_JEWEL_BLUE:
		speed = TARGET_SPEED_TYPE_S;
		break;
	case TARGET_ID_JEWEL_RED:
		speed = TARGET_SPEED_TYPE_S;
		break;
	case TARGET_ID_JEWEL_GREEN:
		speed = TARGET_SPEED_TYPE_S;
		break;
	case TARGET_ID_JEWEL_YELLOW:
		speed = TARGET_SPEED_TYPE_S;
		break;
	case TARGET_ID_JEWEL_PURPLE:
		speed = TARGET_SPEED_TYPE_S;
		break;
	case TARGET_ID_FOOD:
		speed = TARGET_SPEED_TYPE_S;
		break;
	default:
		break;
	}
	return speed;
}

int Target::getYunIndex(void)
{
	return yunIndex;
}

int Target::getPointIndex(void)
{
	return pointIndex;
}

void Target::getAwards(void)
{
	int propId = 0;
	int propNum = 0;
	int coin = 0;

	switch(id)
	{
	case TARGET_ID_BOMB:// 不给炸弹的奖励 给1块钱
		coin = 1;
		//propId = PROP_TYPE_GRENADE;    
		//propNum = 1;
		break;
	case TARGET_ID_BOX:
		coin = rand()%201 + 300;// (300-500随机价值)
		break;
	case TARGET_ID_GOLDEN_S:
		coin = 50;
		break;
	case TARGET_ID_GOLDEN_M:
		coin = 100;
		break;
	case TARGET_ID_GOLDEN_B:
		coin = 250;
		break;
	case TARGET_ID_STONE_S:
		coin = 10;
		break;
	case TARGET_ID_STONE_M:
		coin = 20;
		break;
	case TARGET_ID_STONE_B:
		coin = 50;
		break;
	case TARGET_ID_DIAMOND:
		coin = 700;
		break;
	case TARGET_ID_COAL:
		coin = 5;
		break;
	case TARGET_ID_TRUNK: 
		coin = 30;
		break;
	case TARGET_ID_JEWEL_BLUE:
		coin = 50;
		propId = PROP_TYPE_JEWEL_BLUE;
		propNum = 1;
		break;
	case TARGET_ID_JEWEL_RED:
		coin = 50;
		propId = PROP_TYPE_JEWEL_RED;
		propNum = 1;
		break;
	case TARGET_ID_JEWEL_GREEN:
		coin = 50;
		propId = PROP_TYPE_JEWEL_GREEN;
		propNum = 1;
		break;
	case TARGET_ID_JEWEL_YELLOW:
		coin = 50;
		propId = PROP_TYPE_JEWEL_YELLOW;
		propNum = 1;
		break;
	case TARGET_ID_JEWEL_PURPLE:
		coin = 50;
		propId = PROP_TYPE_JEWEL_PURPLE;
		propNum = 1;
		break;
	case TARGET_ID_FOOD:
		coin = 0;
		propId = PROP_TYPE_FOOD;
		propNum = 1;
		break;
	default:
		break;
	}
	
	Global::getInstance()->appendPropAwardGet(getTypeById(), PROP_TYPE_COIN, coin);
	Global::getInstance()->appendPropAwardGet(propId, propNum);
}

int Target::getId(void)
{
	return id;
}

bool Target::isCanCarry(void)
{
	return canCarry;
}
//void Target::setIsCarrierOwn(bool _b)
//{
//	isCarrierOwn = _b;
//}
//
//bool Target::getIsCarrierOwn(void)
//{
//	return isCarrierOwn;
//}
void Target::intersectByHanger(GameControl * _gameControl, Hanger * _hanger)
{
	if (id == TARGET_ID_BOMB)
	{
		if (_hanger->getFunctionType() == HANGER_FUNCTION_TYPE_CARRY_BOMB)
		{
			hanger = _hanger;

			_hanger->carryTargetType = GAMECONTROL_TYPE_TARGET_STATIC;
			_hanger->carryTargetPoint = this;
			setStatus(TARGET_STATUS_CARRIED, _hanger);
			_hanger->setStatus(HANGER_STATUS_PULL_HAVING);
			_gameControl->role->setStatus(ROLE_STATUS_PULL_HAVING);
		}
		else if (_hanger->getFunctionType() == HANGER_FUNCTION_TYPE_EXCHANGE_TO_JEWEL)
		{
			hanger = _hanger;

			_hanger->carryTargetType = GAMECONTROL_TYPE_TARGET_STATIC;
			_hanger->carryTargetPoint = this;
			setStatus(TARGET_STATUS_CARRIED, _hanger);
			_hanger->setStatus(HANGER_STATUS_PULL_HAVING);
			_gameControl->role->setStatus(ROLE_STATUS_PULL_HAVING);

			//int exchaneId = rand()%(TARGET_ID_JEWEL_PURPLE - TARGET_ID_JEWEL_BLUE + 1) + TARGET_ID_JEWEL_BLUE;
			exchangeBitmapAndId(_gameControl->getMinUnhavingJewelId());
			addEffect();
		}
		else
		{
			// 添加爆炸
			_gameControl->addExplode(S_EXPLODE, getPositionX(), getPositionY());

			if (_hanger->getFunctionType() != HANGER_FUNCTION_TYPE_THROW)
			{
				_hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
				_gameControl->role->setStatus(ROLE_STATUS_PULL_UNHAVING);
			}
			setStatus(TARGET_STATUS_REMOVE, _hanger);

			unsigned int j = _gameControl->gate->getTargets()->indexOfObject(this);
			for (unsigned int i = 0; i < _gameControl->gate->getTargets()->count(); i++)
			{
				if (i != j)
				{
					Target * tmp = (Target *)_gameControl->gate->getTargets()->objectAtIndex(i);
					if(Global::getInstance()->isInCircle(tmp->getPositionX(), tmp->getPositionY(), getPositionX(), getPositionY(), BOMB_CIRCLE)
						&& (tmp->getStatus() != TARGET_STATUS_CARRIED)
						&& (tmp->getStatus() != TARGET_STATUS_REMOVE)
						&& (tmp->getStatus() != TARGET_STATUS_GOT_REMOVE))
					{
						tmp->intersectByBomb(_gameControl);
					}
				}
			}

			if (_gameControl->gate->getDynamicTargets() != NULL)
			{
				for (unsigned int i = 0; i < _gameControl->gate->getDynamicTargets()->count(); i++)
				{
					DynamicTarget * tmp = (DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i);
					if(Global::getInstance()->isInCircle(tmp->getArmature()->getPositionX(),tmp->getArmature()->getPositionY(), getPositionX(), getPositionY(), BOMB_CIRCLE)
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
			_hanger->setStatus(HANGER_STATUS_PULL_UNHAVING);
			_gameControl->role->setStatus(ROLE_STATUS_PULL_UNHAVING);
			setStatus(TARGET_STATUS_REMOVE, _hanger);
		}
		else
		{
			hanger = _hanger;

			_hanger->carryTargetType = GAMECONTROL_TYPE_TARGET_STATIC;
			_hanger->carryTargetPoint = this;
			setStatus(TARGET_STATUS_CARRIED, _hanger);
			_hanger->setStatus(HANGER_STATUS_PULL_HAVING);
			_gameControl->role->setStatus(ROLE_STATUS_PULL_HAVING);
			//hanger->retain();

			// 点石成金   因为只改变倍率  就通过倍率来验证  是否石头变成金子
			if (getTypeById() == TARGET_TYPE_STONE && _hanger->getFunctionType() == HANGER_FUNCTION_TYPE_STONE_TO_GOLDEN)
			{
				exchangeBitmapAndId(id - 3);
				addEffect();
			}
			else if (_hanger->getFunctionType() == HANGER_FUNCTION_TYPE_EXCHANGE_TO_JEWEL)
			{
				//int exchaneId = rand()%(TARGET_ID_JEWEL_PURPLE - TARGET_ID_JEWEL_BLUE + 1) + TARGET_ID_JEWEL_BLUE;
				exchangeBitmapAndId(_gameControl->getMinUnhavingJewelId());
				addEffect();
			}
		}
	}
}

void Target::intersectByBomb(GameControl * _gameControl)
{
	setStatus(TARGET_STATUS_REMOVE, NULL);
	if (id == TARGET_ID_BOMB)
	{
		// 添加爆炸
		_gameControl->addExplode(S_EXPLODE, getPositionX(), getPositionY());

		unsigned int j = _gameControl->gate->getTargets()->indexOfObject(this);
		for (unsigned int i = 0; i < _gameControl->gate->getTargets()->count(); i++)
		{
			if (i != j)
			{
				Target * tmp = (Target *)_gameControl->gate->getTargets()->objectAtIndex(i);
				if(Global::getInstance()->isInCircle(tmp->getPositionX(), tmp->getPositionY(), getPositionX(), getPositionY(), BOMB_CIRCLE)
					&& (tmp->getStatus() != TARGET_STATUS_CARRIED)
					&& (tmp->getStatus() != TARGET_STATUS_REMOVE)
					&& (tmp->getStatus() != TARGET_STATUS_GOT_REMOVE))
				{
					tmp->intersectByBomb(_gameControl);
				}
			}
		}

		if (_gameControl->gate->getDynamicTargets() != NULL)
		{
			for (unsigned int i = 0; i < _gameControl->gate->getDynamicTargets()->count(); i++)
			{
				DynamicTarget * tmp = (DynamicTarget *)_gameControl->gate->getDynamicTargets()->objectAtIndex(i);
				if(Global::getInstance()->isInCircle(tmp->getArmature()->getPositionX(), tmp->getArmature()->getPositionY(), getPositionX(), getPositionY(), BOMB_CIRCLE)
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

void Target::doAction(float _f, GameControl * _gameControl)
{
	if(status == TARGET_STATUS_CARRIED)
	{
		if (hanger->getStatus() == HANGER_STATUS_SWAYING)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);// 获得移除
			hanger->carryTargetPoint = NULL;
			hanger->carryTargetType = -1;
		}
		else
		{
		setPosition(ccp(hanger->getCurrX() - (hanger->getDistanceToRope() + carriedDistance)*cos((hanger->getAngle() - angleChange)/angleChange*pi)
			, hanger->getCurrY() - (hanger->getDistanceToRope() + carriedDistance)*sin((hanger->getAngle() - angleChange)/angleChange*pi)));
		}
	}
	else if (status == TARGET_STATUS_MAGNETED)
	{// 被吸取  放缩   位置更改
		double _tmp = distance/Global::getInstance()->getJewelSkillDistance()*Global::getInstance()->getJewelSkillScale();
		if (_tmp < 0.1)
		{
			setStatus(TARGET_STATUS_GOT_REMOVE, NULL);
		}
		//setScale(Global::getInstance()->getJewelSkillScale()); // 放缩
		setPosition(ccp(startX + vectorX * (1 - _tmp), startY + vectorY * (1 - _tmp)));
	}
	else if (status == TARGET_STATUS_NORMAL || status == TARGET_STATUS_CARRIER_CARRIED)
	{
		shine(_f);
	}

	if (effect != NULL)
	{
		if (effect->doAction(_f))
		{
			removeChild(effect, true);
			effect = NULL;
		}
	}
}

void Target::initById()
{
	isExchange = true;
	exchangeIndex = 0;
	exchangeCount = 0;
	startTime = 0;
	exchangeId = -1;
	bing = NULL;

	switch(id)
	{
	case TARGET_ID_BOMB:
		initWithFile("tmx/goods_001.png");
		carriedDistance = 15;
		break;
	case TARGET_ID_BOX:
		initWithFile("tmx/goods_002.png");
		carriedDistance = 22;
		break;
	case TARGET_ID_GOLDEN_S:
		initWithFile("texiao/xiaohj/xiaohj1.png");
		carriedDistance = 8;
		exchangeCount = 4;
		exchangeId = TARGET_ID_GOLDEN_S;
		bing = new TargetExchangeBing();
		addChild(bing);
		break;
	case TARGET_ID_GOLDEN_M:
		initWithFile("texiao/zhonghj/zhonghj1.png");
		carriedDistance = 24;
		exchangeCount = 4;
		exchangeId = TARGET_ID_GOLDEN_M;
		bing = new TargetExchangeBing();
		addChild(bing);
		break;
	case TARGET_ID_GOLDEN_B:
		initWithFile("texiao/dahj/dahj1.png");
		carriedDistance = 36;
		exchangeCount = 4;
		exchangeId = TARGET_ID_GOLDEN_B;
		bing = new TargetExchangeBing();
		addChild(bing);
		break;
	case TARGET_ID_STONE_S:
		initWithFile("tmx/goods_006.png");
		carriedDistance = 8;
		break;
	case TARGET_ID_STONE_M:
		initWithFile("tmx/goods_007.png");
		carriedDistance = 24;
		break;
	case TARGET_ID_STONE_B:
		initWithFile("tmx/goods_008.png");
		carriedDistance = 36;
		break;
	case TARGET_ID_DIAMOND:
		initWithFile("texiao/zuanshi/zuanshi1.png");
		carriedDistance = 6;
		exchangeCount = 4;
		exchangeId = TARGET_ID_DIAMOND;
		bing = new TargetExchangeBing();
		addChild(bing);
		break;
	case TARGET_ID_COAL:
		initWithFile("tmx/goods_025.png");
		carriedDistance = 6;
		break;
	case TARGET_ID_TRUNK: 
		initWithFile("tmx/goods_026.png");
		carriedDistance = 20;
		break;
	case TARGET_ID_JEWEL_BLUE:
		initWithFile("tmx/goods_020.png");
		carriedDistance = 9;
		break;
	case TARGET_ID_JEWEL_RED:
		initWithFile("tmx/goods_021.png");
		carriedDistance = 9;
		break;
	case TARGET_ID_JEWEL_GREEN:
		initWithFile("tmx/goods_022.png");
		carriedDistance = 6;
		break;
	case TARGET_ID_JEWEL_YELLOW:
		initWithFile("tmx/goods_023.png");
		carriedDistance = 6;
		break;
	case TARGET_ID_JEWEL_PURPLE:
		initWithFile("tmx/goods_024.png");
		carriedDistance = 0;
		break;
	case TARGET_ID_FOOD:
		initWithFile("tmx/goods_010.png");
		carriedDistance = 4;
		break;
	default:
		break;
	}
}

void Target::exchangeBitmapAndId(int _id)
{
	id = _id;
	switch(id)
	{
	case TARGET_ID_BOMB:
		carriedDistance = 15;
		break;
	case TARGET_ID_BOX:
		carriedDistance = 22;
		break;
	case TARGET_ID_GOLDEN_S:
		carriedDistance = 8;
		break;
	case TARGET_ID_GOLDEN_M:
		carriedDistance = 24;
		break;
	case TARGET_ID_GOLDEN_B:
		carriedDistance = 36;
		break;
	case TARGET_ID_STONE_S:
		carriedDistance = 8;
		break;
	case TARGET_ID_STONE_M:
		carriedDistance = 24;
		break;
	case TARGET_ID_STONE_B:
		carriedDistance = 36;
		break;
	case TARGET_ID_DIAMOND:
		carriedDistance = 6;
		break;
	case TARGET_ID_COAL:
		carriedDistance = 6;
		break;
	case TARGET_ID_TRUNK: 
		carriedDistance = 20;
		break;
	case TARGET_ID_JEWEL_BLUE:
		carriedDistance = 9;
		break;
	case TARGET_ID_JEWEL_RED:
		carriedDistance = 9;
		break;
	case TARGET_ID_JEWEL_GREEN:
		carriedDistance = 6;
		break;
	case TARGET_ID_JEWEL_YELLOW:
		carriedDistance = 6;
		break;
	case TARGET_ID_JEWEL_PURPLE:
		carriedDistance = 0;
		break;
	case TARGET_ID_FOOD:
		carriedDistance = 4;
		break;
	default:
		break;
	}
	exchangeBitmap(_id);
}

void Target::exchangeBitmap(int _id)
{	
	CCTexture2D *pTexture;
	CCRect rect;

	switch(_id)
	{
	case TARGET_ID_BOMB:	
		pTexture = CCTextureCache::sharedTextureCache()->addImage("tmx/goods_001.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("");
		break;
	case TARGET_ID_BOX:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("tmx/goods_002.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("tmx/goods_002.png");
		break;
	case TARGET_ID_GOLDEN_S:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("texiao/xiaohj/xiaohj1.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("tmx/goods_003.png");
		break;
	case TARGET_ID_GOLDEN_M:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("texiao/zhonghj/zhonghj1.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("tmx/goods_004.png");
		break;
	case TARGET_ID_GOLDEN_B:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("texiao/dahj/dahj1.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("tmx/goods_005.png");
		break;
	case TARGET_ID_STONE_S:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("tmx/goods_006.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("tmx/goods_006.png");
		break;
	case TARGET_ID_STONE_M:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("tmx/goods_007.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("tmx/goods_007.png");
		break;
	case TARGET_ID_STONE_B:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("tmx/goods_008.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("tmx/goods_008.png");
		break;
	case TARGET_ID_DIAMOND:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("texiao/zuanshi/zuanshi1.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("tmx/goods_009.png");
		break;
	case TARGET_ID_COAL:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("tmx/goods_025.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("tmx/goods_025.png");
		break;
	case TARGET_ID_TRUNK: 
		pTexture = CCTextureCache::sharedTextureCache()->addImage("tmx/goods_026.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("tmx/goods_026.png");
		break;
	case TARGET_ID_JEWEL_BLUE:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("tmx/goods_020.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("tmx/goods_020.png");
		break;
	case TARGET_ID_JEWEL_RED:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("tmx/goods_021.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("tmx/goods_021.png");
		break;
	case TARGET_ID_JEWEL_GREEN:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("tmx/goods_022.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("tmx/goods_022.png");
		break;
	case TARGET_ID_JEWEL_YELLOW:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("tmx/goods_023.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("tmx/goods_023.png");
		break;
	case TARGET_ID_JEWEL_PURPLE:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("tmx/goods_024.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("tmx/goods_024.png");
		break;
	case TARGET_ID_FOOD:
		pTexture = CCTextureCache::sharedTextureCache()->addImage("tmx/goods_010.png");
		if (pTexture)
		{
			rect = CCRectZero;
			rect.size = pTexture->getContentSize();
			setTexture(pTexture);
			setTextureRect(rect);
			exchangeId = _id;
		}
		//initWithFile("tmx/goods_010.png");
		break;
	default:
		break;
	}
}

int Target::getStatus(void)
{
	return status;
}

float Target::getDistance(void)
{
	distance = sqrt(vectorX*vectorX + vectorY*vectorY);
	return distance;
}

void Target::setStatus(int _status, Hanger * _hanger)
{
	status = _status;
	if (status == TARGET_STATUS_MAGNETED)
	{// 如果更改为被吸取状态对应更新参数
		startX = getPositionX();// 更新位置
		startY = getPositionY();
		vectorX = _hanger->getCurrX() - (_hanger->getDistanceToRope() + carriedDistance)*cos((_hanger->getAngle() - angleChange)/angleChange*pi) - getPositionX();
		vectorY = _hanger->getCurrY() - (_hanger->getDistanceToRope() + carriedDistance)*sin((_hanger->getAngle() - angleChange)/angleChange*pi) - getPositionY();
		//magnetAngle = atan2(
		//	global->getHangerCurrY() - global->getHangerDistanceToRope()*sin((global->getHangerAngle() - angleChange)/angleChange*pi) - getPositionY()
		//	, global->getHangerCurrX() - global->getHangerDistanceToRope()*cos((global->getHangerAngle() - angleChange)/angleChange*pi) - getPositionX());
		//magnetDistance = sqrt(
		//	(getPositionX() - global->getHangerCurrX() - global->getHangerDistanceToRope()*cos((global->getHangerAngle() - angleChange)/angleChange*pi))
		//	* (getPositionX() - global->getHangerCurrX() - global->getHangerDistanceToRope()*cos((global->getHangerAngle() - angleChange)/angleChange*pi))
		//	+ (getPositionY() - global->getHangerCurrY() - global->getHangerDistanceToRope()*sin((global->getHangerAngle() - angleChange)/angleChange*pi))
		//	* (getPositionY() - global->getHangerCurrY() - global->getHangerDistanceToRope()*sin((global->getHangerAngle() - angleChange)/angleChange*pi))
		//	);
	}
	if ((status == TARGET_STATUS_NORMAL) || (status == TARGET_STATUS_CARRIER_CARRIED))
	{
		canCarry = true;
	}
	else
	{
		canCarry = false;
		if (status == TARGET_STATUS_CARRIED)
		{
			exchangeBitmapAndId(id);
			if (bing != NULL)
			{
				bing->setVisible(false);
			}
			this->setZOrder(LAYER_ORDER_CONTROL-2);
			this->setRotation(angleCenter - hanger->getAngle());
		}
	}
}

int Target::getTypeById(void)
{
	int type = -1;

	switch(id)
	{
	case TARGET_ID_BOMB:
		type = TARGET_TYPE_BOMB;
		break;
	case TARGET_ID_BOX:
		type = TARGET_TYPE_BOX;
		break;
	case TARGET_ID_GOLDEN_S:
	case TARGET_ID_GOLDEN_M:
	case TARGET_ID_GOLDEN_B:
		type = TARGET_TYPE_GOLDEN;
		break;
	case TARGET_ID_STONE_S:
	case TARGET_ID_STONE_M:
	case TARGET_ID_STONE_B:
		type = TARGET_TYPE_STONE;
		break;
	case TARGET_ID_DIAMOND:
		type = TARGET_TYPE_DIAMOND;
		break;
	case TARGET_ID_COAL:
		type = TARGET_TYPE_COAL;
		break;
	case TARGET_ID_TRUNK: 
		type = TARGET_TYPE_TRUNK;
		break;
	case TARGET_ID_JEWEL_BLUE:
	case TARGET_ID_JEWEL_RED:
	case TARGET_ID_JEWEL_GREEN:
	case TARGET_ID_JEWEL_YELLOW:
	case TARGET_ID_JEWEL_PURPLE:
		type = TARGET_TYPE_JEWEL;
		break;
	case TARGET_ID_FOOD:
		type = TARGET_TYPE_FOOD;
		break;
	default:
		break;
	}

	return type;
}

void Target::shine(float _f)
{
	char s[128];
	CCTexture2D *pTexture;
	CCRect rect;
	switch(exchangeId)
	{
	case TARGET_ID_GOLDEN_S:
		sprintf(s, "texiao/xiaohj/xiaohj%d.png", exchangeIndex + 1);
		break;
	case TARGET_ID_GOLDEN_M:
		sprintf(s, "texiao/zhonghj/zhonghj%d.png", exchangeIndex + 1);
		break;
	case TARGET_ID_GOLDEN_B:
		sprintf(s, "texiao/dahj/dahj%d.png", exchangeIndex + 1);
		break;
	case TARGET_ID_DIAMOND:
		sprintf(s, "texiao/zuanshi/zuanshi%d.png", exchangeIndex + 1);
		break;
	case TARGET_ID_JEWEL_BLUE:
	case TARGET_ID_JEWEL_RED:
	case TARGET_ID_JEWEL_GREEN:
	case TARGET_ID_JEWEL_YELLOW:
	case TARGET_ID_JEWEL_PURPLE:
	case TARGET_ID_BOMB:
	case TARGET_ID_BOX:
	case TARGET_ID_STONE_S:
	case TARGET_ID_STONE_M:
	case TARGET_ID_STONE_B:
	case TARGET_ID_COAL:
	case TARGET_ID_TRUNK: 
	case TARGET_ID_FOOD:
	default:
		break;
	}

	if (bing != NULL)
	{
		if (isExchange)
		{
			if (_f)
			{
				startTime += _f;
				if (startTime >= TAEGET_EXCHANGE_BITMAP_TIME/exchangeCount)
				{
					pTexture = CCTextureCache::sharedTextureCache()->addImage(s);
					if (pTexture)
					{
						rect = CCRectZero;
						rect.size = pTexture->getContentSize();
						setTexture(pTexture);
						setTextureRect(rect);
						exchangeIndex++;
					}
					startTime = 0;
					if (exchangeIndex == exchangeCount)
					{
						exchangeIndex = 0;
						isExchange = false;
						bing->setDoAction(true);
						bing->setPosition(ccp(getContentSize().width*3/4, getContentSize().height*5/6));
					}
				}
			}
		}
		else
		{
			if (bing->doAction(_f))
			{
				isExchange = true;
				bing->setDoAction(false);
			}
		}
	}
}

void Target::addEffect(void)
{
	effect = new TargetExchangeEffect();
	addChild(effect);
	effect->setPosition(getContentSize().width/2, getContentSize().height/2);
}

/************************************************************
闪光最后的效果
*************************************************************/
#define				TAEGET_EXCHANGE_BING_EXCHANGE_BITMAP_TIME    0.3

TargetExchangeBing::TargetExchangeBing(void)
{
	setDoAction(false);
	startTime = 0.0;
	index = 0;
	bitmaps = new CCArray();
	bitmaps->addObject(CCSprite::create("texiao/xuanz/xuanz1.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(true);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/xuanz/xuanz2.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/xuanz/xuanz3.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());

	autorelease();
}

bool TargetExchangeBing::doAction(float _f)
{
	if (isDoAction)
	{
		if (_f)
		{
			startTime += _f;
			if (startTime >= TAEGET_EXCHANGE_BING_EXCHANGE_BITMAP_TIME/bitmaps->count())
			{
				((CCSprite *)bitmaps->objectAtIndex(index++))->setVisible(false);
				startTime = 0;
				if (index == bitmaps->count())
				{
					index = 0;
					return true;
				}
				((CCSprite *)bitmaps->objectAtIndex(index))->setVisible(true);
			}
		}
	}
	return false;
}

void TargetExchangeBing::setDoAction(bool _b)
{
	isDoAction = _b;
	setVisible(_b);
}

TargetExchangeBing::~TargetExchangeBing(void)
{
	CCObject * p;
	CCARRAY_FOREACH(bitmaps, p)
	{
		CC_SAFE_RELEASE(p);
	}
}


/************************************************************
金子变成石头的特效
*************************************************************/
#define				TAEGET_EXCHANGE_EFFECT_EXCHANGE_BITMAP_TIME    0.5

TargetExchangeEffect::TargetExchangeEffect(void)
{
	startTime = 0.0;
	index = 0;
	bitmaps = new CCArray();
	bitmaps->addObject(CCSprite::create("texiao/bian/bian1.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(true);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/bian/bian2.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/bian/bian3.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/bian/bian4.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(true);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/bian/bian5.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/bian/bian6.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(false);
	addChild((CCSprite *)bitmaps->lastObject());
	bitmaps->addObject(CCSprite::create("texiao/bian/bian7.png"));
	((CCSprite *)bitmaps->lastObject())->setVisible(true);
	addChild((CCSprite *)bitmaps->lastObject());

	autorelease();
}

bool TargetExchangeEffect::doAction(float _f)
{
	if (_f)
	{
		startTime += _f;
		if (startTime >= TAEGET_EXCHANGE_EFFECT_EXCHANGE_BITMAP_TIME/bitmaps->count())
		{
			((CCSprite *)bitmaps->objectAtIndex(index++))->setVisible(false);
			startTime = 0;
			if (index == bitmaps->count())
			{
				index = 0;
				return true;
			}
			((CCSprite *)bitmaps->objectAtIndex(index))->setVisible(true);
		}
	}
	return false;
}

TargetExchangeEffect::~TargetExchangeEffect(void)
{
	CCObject * p;
	CCARRAY_FOREACH(bitmaps, p)
	{
		CC_SAFE_RELEASE(p);
	}
}
