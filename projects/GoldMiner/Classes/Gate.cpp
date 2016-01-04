#include "Gate.h"
#include "GameControl.h"
#include "DateManger.h"
#include "CSArmature.h"
#include "CSArmatureDataManager.h"

USING_NS_CC;
using namespace cs;

Gate::Gate(void)
{
	targets = NULL;
	dynamicTargets = NULL;
	carriers = NULL;
	hideTarget = NULL;
	hideDynamicTarget = NULL;
	isDynamicTargetMoving = true;
	isCarrierMoving = true;
}

Gate::~Gate(void)
{
	CCObject * p;
	CCARRAY_FOREACH(targets, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(dynamicTargets, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(carriers, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(hideTarget, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(hideDynamicTarget, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
}

Gate * Gate::getInstance(int _gateId, GameControl * _gameControl)
{
	Gate * gate = NULL;
	if (_gateId == 0)
	{
		gate = new Gate();
		gate->initSelf(_gameControl, CCTMXTiledMap::create("tmx/1_01.tmx"));
	}
	else if ((_gateId > 0) && (_gateId < 91))
	{
		gate = new Gate();
		char _s[64];
		sprintf(_s, "tmx/%d.tmx", _gateId);
		gate->initSelf(_gameControl, CCTMXTiledMap::create(_s));
	}
	else if ((_gateId > 993) && (_gateId < 1000))
	{
		gate = new Gate();
		char _s[64];
		sprintf(_s, "tmx/%d.tmx", _gateId);
		gate->initSelf(_gameControl, CCTMXTiledMap::create(_s));
	}

	if(gate != NULL)
	{
		gate->gateId = _gateId;
	}

	return gate;
}

void Gate::doAction(float _f, GameControl * _gameControl)
{

	if (carriers != NULL && isCarrierMoving)
	{
		for(unsigned int i = 0; i < carriers->count(); i++)
		{
			((Carrier *)carriers->objectAtIndex(i))->doAction(_f);
		}
	}

	if (targets != NULL)
	{
		CCArray * removeIndexTarget = CCArray::create();
		//removeIndexTarget->retain();

		for(unsigned int i = 0; i < targets->count(); i++)
		{
			Target * tmp = ((Target  *)targets->objectAtIndex(i));
			tmp->doAction(_f, _gameControl);
			tmp->setVisible(true);
			if (tmp->getStatus() == TARGET_STATUS_GOT_REMOVE)
			{// ��ץȥ ��������ת����ҡ��״̬   ���ö���  ��ҪҪ�������� 
				if (tmp->getTypeById() == TARGET_TYPE_GOLDEN)
				{
					goldenNum--;
				}
				removeIndexTarget->addObject(CCInteger::create(i));
				tmp->getAwards();// ���ץȡ��Ľ���(����������������������ʱ���ֱ�Ӷ�����е����Ը�ֵ)
				targetTotalNum--;
			}
			else if (tmp->getStatus() == TARGET_STATUS_REMOVE)
			{// ֱ���Ƴ�  �����ȡ����
				removeIndexTarget->addObject(CCInteger::create(i));
				targetTotalNum--;
			}
		}

		// �Ƴ����Ƴ��Ķ���
		for (unsigned int i = removeIndexTarget->count(); i >0; i--)
		{
			_gameControl->removeChild((Target *)(targets->objectAtIndex(((CCInteger *)removeIndexTarget->objectAtIndex(i-1))->getValue())),true);
			hideTarget->removeObject((Target *)(targets->objectAtIndex(((CCInteger *)removeIndexTarget->objectAtIndex(i-1))->getValue())));
			targets->removeObjectAtIndex(((CCInteger *)removeIndexTarget->objectAtIndex(i-1))->getValue());
			removeIndexTarget->removeObjectAtIndex(i-1,true);
		}
	}

	if (dynamicTargets != NULL)
	{
		CCArray * removeIndexDynamicTarget = CCArray::create();
		//removeIndexDynamicTarget->retain();

		for(unsigned int i = 0; i < dynamicTargets->count(); i++)
		{
			DynamicTarget * tmp = (DynamicTarget *)dynamicTargets->objectAtIndex(i);
			// �ƶ����ﲻ������  ���� �����Ƶ��ǲ����ƶ�״̬
			if (isDynamicTargetMoving || (tmp->getStatus() != DYNAMIC_TARGET_STATUS_MOVING))
			{
				tmp->doAction(_f, _gameControl);
				tmp->setVisible(false);
			}
			if (tmp->getStatus() == DYNAMIC_TARGET_STATUS_DESTORY)
			{
				removeIndexDynamicTarget->addObject(CCInteger::create(i));
				targetTotalNum--;
				if((tmp->getId() >= DYNAMIC_ID_XIAOZUANFENG) && (tmp->getId() <= DYNAMIC_ID_NIUMOWANG))
				{// �ɱ���«��ȡ��Ŀ��¼
					dynamicTargetNum--;
				}
			}
			else
			{
				tmp->getArmature()->setVisible(true);
			}
		}

		// �Ƴ����Ƴ��Ķ���
		for (unsigned int i = removeIndexDynamicTarget->count(); i > 0; i--)
		{
			_gameControl->removeChild(((DynamicTarget *)(dynamicTargets->objectAtIndex(((CCInteger *)removeIndexDynamicTarget->objectAtIndex(i-1))->getValue())))->getArmature(),true);
			//_gameControl->removeChild(((DynamicTarget *)(dynamicTargets->objectAtIndex(((CCInteger *)removeIndexDynamicTarget->objectAtIndex(i-1))->getValue())))->roleSwaySpeed,true);
			hideDynamicTarget->removeObject(((DynamicTarget *)(dynamicTargets->objectAtIndex(((CCInteger *)removeIndexDynamicTarget->objectAtIndex(i-1))->getValue())))->getArmature());
			dynamicTargets->removeObjectAtIndex(((CCInteger *)removeIndexDynamicTarget->objectAtIndex(i-1))->getValue());
			removeIndexDynamicTarget->removeObjectAtIndex(i-1,true);
		}
	}

	// ���ض���
	if (hideTarget != NULL)
	{
		for(unsigned int i = 0; i < hideTarget->count(); i++)
		{
			Target * tmp = (Target *)hideTarget->objectAtIndex(i);
			if ((tmp->getStatus() != TARGET_STATUS_CARRIED) && (tmp->getStatus() != TARGET_STATUS_REMOVE) && (tmp->getStatus() != TARGET_STATUS_GOT_REMOVE))
			{
				tmp->setVisible(false);
			}
		}

		hideTarget->removeAllObjects();
	}

	if (hideDynamicTarget != NULL)
	{
		for(unsigned int i = 0; i < hideDynamicTarget->count(); i++)
		{
			DynamicTarget * tmp = (DynamicTarget *)hideDynamicTarget->objectAtIndex(i);
			if ((tmp->getStatus() != DYNAMIC_TARGET_STATUS_CARRIED) && (tmp->getStatus() != DYNAMIC_TARGET_STATUS_GOT_REMOVE) && (tmp->getStatus() != DYNAMIC_TARGET_STATUS_REMOVE) && (tmp->getStatus() != DYNAMIC_TARGET_STATUS_DESTORY))
			{
				tmp->setVisible(false);
			}
		}
		hideDynamicTarget->removeAllObjects();
	}
}

//cocos2d::CCTMXTiledMap * Gate::getMap(void)
//{
//	return map;
//}

bool Gate::addHideTarget(Target * _target)
{
	if (hideTarget->indexOfObject(_target) != CC_INVALID_INDEX)
	{
		return false;
	}
	else
	{
		hideTarget->addObject(_target);
		return true;
	}
}

bool Gate::addHideDynamicTarget(DynamicTarget * _dynamicTarget)
{
	if (hideDynamicTarget->indexOfObject(_dynamicTarget) != CC_INVALID_INDEX)
	{
		return false;
	}
	else
	{
		hideDynamicTarget->addObject(_dynamicTarget);
		return true;
	}
}

cocos2d::CCArray * Gate::getTargets(void)
{
	return targets;
}

cocos2d::CCArray * Gate::getDynamicTargets(void)
{
	return dynamicTargets;
}

cocos2d::CCArray * Gate::getCarriers(void)
{
	return carriers;
}

int Gate::getGoldenNum(void)
{
	return goldenNum;
}

int Gate::getTargetTotalNum(void)
{
	return targetTotalNum;
}

int Gate::getCanGoundDynamicTargetNum(void)
{
	return dynamicTargetNum;
}

void Gate::setIsDynamicTargetMoving(bool _isDynamicTargetMoving)
{
	isDynamicTargetMoving = _isDynamicTargetMoving;
}

void Gate::setIsCarrierMoving(bool _isCarrierMoving)
{
	isCarrierMoving = _isCarrierMoving;
}

//int * Gate::getCarriersLines(void)
//{
//	return carriersLines;
//}

void Gate::initSelf(GameControl * _gameControl, cocos2d::CCTMXTiledMap * map)
{
	_gameControl->addChild(map);
	map->setPosition(ccp(0,0));

	dynamicTargetNum = 0;
	goldenNum = 0;
	targetTotalNum = 0;
	int carriersNum = 0;
	int tmpCount = 0;
	int isGateId = -1;// �Ƿ����ƶ��
	map->layerNamed("bg")->getParent()->setZOrder(LAYER_ORDER_BACKGROUND);// ���������������²�
	CCTMXObjectGroup *objectsTarget = map->objectGroupNamed("logic");//��ȡ�����
	cocos2d::CCArray *arrayTarget = objectsTarget->getObjects();

	CCArray * tmpTargets = CCArray::create();
	CCArray * tmpTargetsType = CCArray::create();
	CCArray * tmpYunTargets = CCArray::create();
	CCArray * tmpYunTargetsType = CCArray::create();
	int targetYunTotalNum = 0;

//#ifdef										GOLDEN_MINER_2_NEW_GUIDE
//	if (_gameControl->getType() == GAMEING_GUIDE)
//	{
		CCArray * stepNum = CCArray::create();
		int tmpStepCount = 0;
		int stepCount = 0;
		CCArray * stepTargets = CCArray::create();
//	}
//#endif		

	// ��ʼ������
	for(unsigned int i = 0; i < arrayTarget->count(); i++)
	{
		CCDictionary  *tmp = (CCDictionary  *)arrayTarget->objectAtIndex(i);
		int objectType = Global::getInstance()->getGameControlTypeById(tmp->valueForKey("typeid")->intValue());
		if (objectType == GAMECONTROL_TYPE_TARGET_STATIC)
		{
			if (targets == NULL)
			{
				targets = new CCArray;
				hideTarget = new cocos2d::CCArray;// ���صľ�̬Ŀ�������
			}

			targets->addObject(new Target(tmp->valueForKey("x")->doubleValue(), tmp->valueForKey("y")->doubleValue(), tmp->valueForKey("typeid")->intValue(), tmp->valueForKey("point")->intValue(), tmp->valueForKey("cloudin")->intValue()));

#ifdef										GOLDEN_MINER_2_NEW_GUIDE
			if (_gameControl->getType() == GAMEING_GUIDE)
			{
				// ����step���꽫�����ɴ�С
				if (tmp->valueForKey("guidestep")->intValue() > 0)
				{
					stepNum->addObject(CCInteger::create(tmp->valueForKey("guidestep")->intValue()));
					stepTargets->addObject(targets->lastObject());
					((GuideLayer *)_gameControl)->setStepNum(tmp->valueForKey("guidestep")->intValue());
					tmpStepCount = stepCount;
					for (; tmpStepCount > 0; tmpStepCount--)
					{
						if (((CCInteger *)stepNum->objectAtIndex(tmpStepCount-1))->getValue() > tmp->valueForKey("guidestep")->intValue())
						{
							break;
						}
					}
					if (stepCount != tmpStepCount)
					{
						stepNum->insertObject(CCInteger::create(tmp->valueForKey("guidestep")->intValue()), tmpStepCount);
						stepNum->removeLastObject(true);
						stepTargets->insertObject(targets->lastObject(), tmpStepCount);
						stepTargets->removeLastObject(true);
					}
					stepCount++;
				}
			}
#endif			
			
			if(((Target *)targets->lastObject())->getTypeById() == TARGET_TYPE_GOLDEN)
			{// ��¼�ƽ�ĸ���
				goldenNum++;
			}

			// ����y���꽫�����ɴ�С
			tmpTargets->addObject(targets->lastObject());
			tmpTargetsType->addObject(CCInteger::create(0));
			tmpCount = targetTotalNum;
			for (; tmpCount > 0; tmpCount--)
			{
				if (((CCInteger *)tmpTargetsType->objectAtIndex(tmpCount - 1))->getValue() == 0)
				{
					if (((Target *)tmpTargets->objectAtIndex(tmpCount-1))->getPositionY() > tmp->valueForKey("y")->doubleValue())
					{
						break;
					}
				}
				else
				{
					if (((DynamicTarget *)tmpTargets->objectAtIndex(tmpCount-1))->getCurrY() > tmp->valueForKey("y")->doubleValue())
					{
						break;
					}
				}
			}

			if (tmpCount != targetTotalNum)
			{
				tmpTargets->exchangeObjectAtIndex(targetTotalNum, tmpCount);
				tmpTargetsType->exchangeObjectAtIndex(targetTotalNum, tmpCount);
			}
			targetTotalNum++;
		}
		else if (objectType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
		{
			// ��̬Ŀ��̶���һ����0��
			if (dynamicTargets == NULL)
			{
				dynamicTargets = new CCArray;
				dynamicTargetControl = new DynamicTargetControl();
				hideDynamicTarget = new CCArray;// ���صľ�̬Ŀ�������
			}
			dynamicTargets->addObject(dynamicTargetControl->getDynamicTargetById(tmp->valueForKey("typeid")->intValue(), tmp->valueForKey("starttype")->intValue(), tmp->valueForKey("x")->doubleValue(), tmp->valueForKey("y")->doubleValue()));
			double _x[] = {
				tmp->valueForKey("x")->doubleValue(),
				tmp->valueForKey("pointx1")->doubleValue(),
				tmp->valueForKey("pointx2")->doubleValue(),
				tmp->valueForKey("pointx3")->doubleValue()
			};
			double _y[] = {
				tmp->valueForKey("y")->doubleValue(),
				tmp->valueForKey("pointy1")->doubleValue(),
				tmp->valueForKey("pointy2")->doubleValue(),
				tmp->valueForKey("pointy3")->doubleValue()
			};
			((DynamicTarget *)dynamicTargets->lastObject())->setMove(tmp->valueForKey("pointcount")->intValue(), _x, _y);
			if((((DynamicTarget *)dynamicTargets->lastObject())->getId() >= DYNAMIC_ID_XIAOZUANFENG) && (((DynamicTarget *)dynamicTargets->lastObject())->getId() <= DYNAMIC_ID_NIUMOWANG))
			{// �ɱ���«��ȡ��Ŀ��¼
				dynamicTargetNum++;
			}
			else if(((DynamicTarget *)dynamicTargets->lastObject())->getId() == DYNAMIC_ID_HUOHUALIAN)
			{
				((DynamicTargetHuoHuaLian *)dynamicTargets->lastObject())->setYunInformation(tmp->valueForKey("point")->intValue(), tmp->valueForKey("cloudin")->intValue());
			}
			else
			{
				// ����y���꽫�����ɴ�С
				tmpYunTargets->addObject(dynamicTargets->lastObject());
				tmpYunTargetsType->addObject(CCInteger::create(0));
				tmpCount = targetYunTotalNum;
				for (; tmpCount > 0; tmpCount--)
				{
					if (((CCInteger *)tmpYunTargetsType->objectAtIndex(tmpCount - 1))->getValue() == 0)
					{
						if (((DynamicTarget *)tmpYunTargetsType->objectAtIndex(tmpCount-1))->getCurrY() > tmp->valueForKey("y")->doubleValue())
						{
							break;
						}
					}
					else
					{
						if (((Carrier *)tmpYunTargetsType->objectAtIndex(tmpCount-1))->getCurrY() > tmp->valueForKey("y")->doubleValue())
						{
							break;
						}
					}
				}

				if (tmpCount != targetYunTotalNum)
				{
					tmpYunTargets->exchangeObjectAtIndex(targetYunTotalNum, tmpCount);
					tmpYunTargetsType->exchangeObjectAtIndex(targetYunTotalNum, tmpCount);
				}
				targetYunTotalNum++;
			}

			// ����y���꽫�����ɴ�С
			tmpTargets->addObject(dynamicTargets->lastObject());
			tmpTargetsType->addObject(CCInteger::create(1));
			tmpCount = targetTotalNum;
			for (; tmpCount > 0; tmpCount--)
			{
				if (((CCInteger *)tmpTargetsType->objectAtIndex(tmpCount - 1))->getValue() == 0)
				{
					if (((Target *)tmpTargets->objectAtIndex(tmpCount-1))->getPositionY() > tmp->valueForKey("y")->doubleValue())
					{
						break;
					}
				}
				else
				{
					if (((DynamicTarget *)tmpTargets->objectAtIndex(tmpCount-1))->getCurrY() > tmp->valueForKey("y")->doubleValue())
					{
						break;
					}
				}
			}

			if (tmpCount != targetTotalNum)
			{
				tmpTargets->exchangeObjectAtIndex(targetTotalNum, tmpCount);
				tmpTargetsType->exchangeObjectAtIndex(targetTotalNum, tmpCount);
			}
			targetTotalNum++;
		}
		else if (objectType == GAMECONTROL_TYPE_CARRIER)
		{
			if (carriers == NULL)
			{
				carriers = new CCArray;
			}
			carriers->addObject(new Carrier(tmp->valueForKey("x")->doubleValue(), tmp->valueForKey("y")->doubleValue(), tmp->valueForKey("typeid")->intValue(), tmp->valueForKey("direction")->intValue(), tmp->valueForKey("speed")->intValue()));
			((Carrier *)carriers->lastObject())->setCarrierTypeAndIndex(tmp->valueForKey("cloudid")->intValue(), tmp->valueForKey("cloudpoint1")->intValue(), tmp->valueForKey("cloudpoint2")->intValue(), tmp->valueForKey("cloudpoint3")->intValue());

			
			// ����y���꽫�����ɴ�С
			tmpYunTargets->addObject(carriers->lastObject());
			tmpYunTargetsType->addObject(CCInteger::create(1));
			tmpCount = targetYunTotalNum;
			for (; tmpCount > 0; tmpCount--)
			{
				if (((CCInteger *)tmpYunTargetsType->objectAtIndex(tmpCount - 1))->getValue() == 0)
				{
					if (((DynamicTarget *)tmpYunTargetsType->objectAtIndex(tmpCount-1))->getCurrY() > tmp->valueForKey("y")->doubleValue())
					{
						break;
					}
				}
				else
				{
					if (((Carrier *)tmpYunTargetsType->objectAtIndex(tmpCount-1))->getCurrY() > tmp->valueForKey("y")->doubleValue())
					{
						break;
					}
				}
			}

			if (tmpCount != targetYunTotalNum)
			{
				tmpYunTargets->exchangeObjectAtIndex(targetYunTotalNum, tmpCount);
				tmpYunTargetsType->exchangeObjectAtIndex(targetYunTotalNum, tmpCount);
			}
			targetYunTotalNum++;
			//// ����y���꽫�����ɴ�С
			//tmpCount = carriersNum;
			//for (; tmpCount > 0; tmpCount--)
			//{
			//	if (((Carrier *)carriers->objectAtIndex(tmpCount-1))->getCurrY() > tmp->valueForKey("y")->doubleValue())
			//	{
			//		break;
			//	}
			//}

			//if (tmpCount != carriersNum)
			//{
			//	carriers->exchangeObjectAtIndex(carriersNum, tmpCount);
			//}

			//carriersLines[carriersNum] = carriersNum;

			//for (unsigned int j = 0; j < carriersNum; j++)
			//{
			//	if (((Carrier *)carriers->objectAtIndex(carriersLines[j]))->getCurrY() < tmp->valueForKey("y")->doubleValue())
			//	{
			//		for (unsigned int k = carriersNum; k > j; k--)
			//		{
			//			carriersLines[k] = carriersLines[k - 1];
			//		}
			//		carriersLines[j] = carriersNum;
			//		break;
			//	}
			//}

			carriersNum++;
			//_gameControl->addChild((DynamicTarget *)tmpTargets->lastObject());
			//_gameControl->addChild(((Carrier *)carriers->lastObject())->getSpriteDown(), LAYER_ORDER_CARRIER_DOWN);// �ƶ���²�
			//_gameControl->addChild(((Carrier *)carriers->lastObject())->getSpriteUp(), LAYER_ORDER_CARRIER_UP);// �ƶ���ϲ�
		}
		else if (objectType == GAMECONTROL_TYPE_INFORMATION)
		{
			// ���õ�ǰ���ڹؿ���Ϸ������Ϣ
			_gameControl->setLeastCoin(tmp->valueForKey("coins")->intValue());
			_gameControl->setLeaveTime(tmp->valueForKey("time")->intValue());
			// ������һ�صĹؿ�id
			int tmpValue = tmp->valueForKey("nextscene2")->intValue();
			if ((tmpValue != -1) && DateManger::getInstance()->getGateOn(tmpValue))
			{
				Global::getInstance()->setSelectGateNextGateId(tmpValue);
			}
			else
			{
				Global::getInstance()->setSelectGateNextGateId(tmp->valueForKey("nextscene")->intValue());
			}
			// ���õ�ǰ���ڴ�ص�id��
			_gameControl->setCurrMapId(tmp->valueForKey("map")->intValue());
			isGateId = tmp->valueForKey("map")->intValue()%10-1;
			// ���õ�ǰ������
			_gameControl->setCurrSceneId(Global::getInstance()->getSmallGateIdByGateId(tmp->valueForKey("scene")->intValue()));
			// tip���
			_gameControl->setTipId(tmp->valueForKey("tips")->intValue());
		}
	}


#ifdef										GOLDEN_MINER_2_NEW_GUIDE
	if (_gameControl->getType() == GAMEING_GUIDE)
	{
		for (int i = 0; i < stepNum->count(); i++)
		{
			CCLOG("%d", ((CCInteger *)stepNum->objectAtIndex(i))->getValue());
			((GuideLayer *)_gameControl)->addStepTarget(stepTargets->objectAtIndex(i));
		}
	}
#endif	

	// ����������
	Player::getInstance()->getMusicControl()->playGameBackGround(isGateId);
	// ��������ص�layer��
	if (isGateId == BIG_GATE_TYPE_LINGSHAN)
	{// �ƶ��
		if (targets != NULL)
		{
			for (unsigned int i = 0; i < targets->count(); i++)
			{
				Target * tmpTarget = (Target *)targets->objectAtIndex(i);
				for(unsigned int j = 0; j < carriers->count(); j++)
				{
					Carrier * tmpCarrier = (Carrier *)carriers->objectAtIndex(j);
					if (tmpCarrier->isCarried(tmpTarget))
					{
						tmpCarrier->addCarriedTarget(tmpTarget, true);
						tmpTarget->setStatus(TARGET_STATUS_CARRIER_CARRIED, NULL);
						break;
					}
					//if (tmpCarrier->isCarried(tmpTarget->getPositionX() - tmpTarget->getContentSize().width/2, tmpTarget->getPositionY() - tmpTarget->getContentSize().height/2))
					//{
					//	tmpCarrier->addCarriedTarget(tmpTarget);
					//	tmpTarget->setStatus(TARGET_STATUS_CARRIER_CARRIED);
					//	break;
					//}
				}
			}
		}


		if (dynamicTargets != NULL)
		{
			for (unsigned int i = 0; i < dynamicTargets->count(); i++)
			{
				DynamicTarget * tmpTarget = (DynamicTarget *)dynamicTargets->objectAtIndex(i);

				if(tmpTarget->getId() > DYNAMIC_ID_NIUMOWANG)
				{
					if(tmpTarget->getId() == DYNAMIC_ID_HUOHUALIAN)
					{
						for(unsigned int j = 0; j < carriers->count(); j++)
						{
							Carrier * tmpCarrier = (Carrier *)carriers->objectAtIndex(j);
							if (tmpCarrier->isCarriedDynamicTarget(tmpTarget))
							{
								tmpCarrier->addCarriedTarget(tmpTarget, false);
								tmpTarget->setStatus(DYNAMIC_TARGET_STATUS_CARRIER_CARRIED, NULL);
								break;
							}
						}
					}

					continue;
				}
				
				// ��������
				if (carriers == NULL)
				{
					carriers = new CCArray;
				}
				carriers->addObject(new Carrier(tmpTarget->getCurrX(), tmpTarget->getArmature()->getPositionY(), CARRIER_ID_BLACK_CLOUD, 0 , 8));
				((Carrier *)carriers->lastObject())->addCarriedTarget(tmpTarget, false);
				tmpTarget->setStatus(DYNAMIC_TARGET_STATUS_CARRIER_CARRIED, NULL);

				// ����y���꽫�����ɴ�С
				tmpYunTargets->addObject(carriers->lastObject());
				tmpYunTargetsType->addObject(CCInteger::create(1));
				tmpCount = targetYunTotalNum;
				for (; tmpCount > 0; tmpCount--)
				{
					if (((CCInteger *)tmpYunTargetsType->objectAtIndex(tmpCount - 1))->getValue() == 0)
					{
						if (((DynamicTarget *)tmpYunTargetsType->objectAtIndex(tmpCount-1))->getCurrY() > ((Carrier *)carriers->lastObject())->getCurrY())
						{
							break;
						}
					}
					else
					{
						if (((Carrier *)tmpYunTargetsType->objectAtIndex(tmpCount-1))->getCurrY() > ((Carrier *)carriers->lastObject())->getCurrY())
						{
							break;
						}
					}
				}

				if (tmpCount != targetYunTotalNum)
				{
					tmpYunTargets->exchangeObjectAtIndex(targetYunTotalNum, tmpCount);
					tmpYunTargetsType->exchangeObjectAtIndex(targetYunTotalNum, tmpCount);
				}
				targetYunTotalNum++;
				//// ����y���꽫�����ɴ�С
				//tmpCount = carriersNum;
				//for (; tmpCount > 0; tmpCount--)
				//{
				//	if (((Carrier *)carriers->objectAtIndex(tmpCount-1))->getCurrY() > ((Carrier *)carriers->lastObject())->getCurrY())
				//	{
				//		break;
				//	}
				//}

				//if (tmpCount != carriersNum)
				//{
				//	carriers->exchangeObjectAtIndex(carriersNum, tmpCount);
				//}
				carriersNum++;				
			}
		}

		
		for (int i = 0 ; i < targetYunTotalNum; i++)
		{
			if (((CCInteger *)tmpYunTargetsType->objectAtIndex(i))->getValue() == 0)
			{
				_gameControl->addChild(((DynamicTarget *)tmpYunTargets->objectAtIndex(i))->getArmature());
				//_gameControl->addChild(((DynamicTarget *)tmpYunTargets->objectAtIndex(i))->roleSwaySpeed);
				if (((DynamicTarget *)tmpYunTargets->objectAtIndex(i))->getId() == DYNAMIC_ID_PEARL_SHELL)
				{
					_gameControl->addChild(((DynamicTargetPearlShell *)tmpYunTargets->objectAtIndex(i))->getShell());
				}
				else if (((DynamicTarget *)tmpYunTargets->objectAtIndex(i))->getId() == DYNAMIC_ID_YUMIANGONGZHU)
				{
					_gameControl->addChild(((DynamicTargetYuMianGongZhu *)tmpYunTargets->objectAtIndex(i))->getPen());
				}
			}
			else
			{
				((Carrier *)tmpYunTargets->objectAtIndex(i))->addSelfToLayer(_gameControl);
			}
		}

		//for (unsigned int i = 0; i < carriers->count(); i++)
		//{
		//	((Carrier *)carriers->objectAtIndex(i))->addSelfToLayer(_gameControl);
		//	//_gameControl->addChild(((Carrier *)carriers->objectAtIndex(i))->getSpriteDown(), (i - carriers->count())-1);// �ƶ���²�
		//	//for (unsigned int j = 0; j < ((Carrier *)carriers->objectAtIndex(i))->getCarriedTarget()->count(); j++)
		//	//{
		//	//	_gameControl->addChild(((Target *)((Carrier *)carriers->objectAtIndex(i))->getCarriedTarget()->objectAtIndex(j)), (i - carriers->count())-1);
		//	//}
		//	//_gameControl->addChild(((Carrier *)carriers->objectAtIndex(i))->getSpriteMiddle(), (i - carriers->count())-1);// �ƶ���ϲ�
		//	//_gameControl->addChild(((Carrier *)carriers->objectAtIndex(i))->getSpriteUp(), (i - carriers->count())-1);// �ƶ���ϲ�
		//	//carriersLines[i] = ((Carrier *)carriers->objectAtIndex(carriersLines[i]))->getCurrY();
		//}

		//for (unsigned int i = 0; i < carriers->count(); i++)
		//{
		//	_gameControl->addChild(((Carrier *)carriers->objectAtIndex(carriersLines[i]))->getSpriteDown(), (i - carriers->count())-1);// �ƶ���²�
		//	for (unsigned int j = 0; j < ((Carrier *)carriers->objectAtIndex(carriersLines[i]))->getCarriedTarget()->count(); j++)
		//	{
		//		_gameControl->addChild(((Target *)((Carrier *)carriers->objectAtIndex(carriersLines[i]))->getCarriedTarget()->objectAtIndex(j)), (i - carriers->count())-1);
		//	}
		//	_gameControl->addChild(((Carrier *)carriers->objectAtIndex(carriersLines[i]))->getSpriteMiddle(), (i - carriers->count())-1);// �ƶ���ϲ�
		//	_gameControl->addChild(((Carrier *)carriers->objectAtIndex(carriersLines[i]))->getSpriteUp(), (i - carriers->count()));// �ƶ���ϲ�
		//	//carriersLines[i] = ((Carrier *)carriers->objectAtIndex(carriersLines[i]))->getCurrY();
		//}

		//for (unsigned int i = 0; i < carriers->count(); i++)
		//{
		//	_gameControl->addChild(((Carrier *)carriers->objectAtIndex(i))->getSpriteDown(), LAYER_ORDER_CARRIER_DOWN);// �ƶ���²�
		//	for (unsigned int j = 0; j < ((Carrier *)carriers->objectAtIndex(i))->getCarriedTarget()->count(); j++)
		//	{
		//		_gameControl->addChild(((Target *)((Carrier *)carriers->objectAtIndex(i))->getCarriedTarget()->objectAtIndex(j)), LAYER_ORDER_TARGET);
		//	}
		//	_gameControl->addChild(((Carrier *)carriers->objectAtIndex(i))->getSpriteMiddle(), LAYER_ORDER_CARRIER_DOWN);// �ƶ���ϲ�
		//	_gameControl->addChild(((Carrier *)carriers->objectAtIndex(i))->getSpriteUp(), LAYER_ORDER_CARRIER_UP);// �ƶ���ϲ�
		//	carriersLines[i] = ((Carrier *)carriers->objectAtIndex(i))->getCurrY();
		//}
	}
	else
	{
		CCParticleSystemQuad * mSystem = NULL;
		cs::Armature * haigui = NULL;
		switch(isGateId)
		{
		case BIG_GATE_TYPE_BAOXIANGGUO:
			mSystem = CCParticleSystemQuad::create("lizitexiao/yezi/yezi2.plist");//plist�ļ�����ͨ�����ӱ༭�����
			mSystem->setPosition(ccp(400,480));//����λ��  
			_gameControl->addChild(mSystem, LAYER_ORDER_CONTROL+1);
			break;
		case BIG_GATE_TYPE_TONGYIANHE:
			// ���ڹ�
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("haigui", "", "flash/haigui/haigui.png", "flash/haigui/haigui.plist", "flash/haigui/skeleton.xml");
			haigui = cs::Armature::create("haigui");
			haigui->setPosition(350,310);
			haigui->setScale(0.8);
			haigui->getAnimation()->playByIndex(0 , 0, 50, 1, TWEEN_EASING_MAX);
			_gameControl->addChild(haigui, LAYER_ORDER_BACKGROUND+1);
			mSystem = CCParticleSystemQuad::create("lizitexiao/paopao/paopao.plist");//plist�ļ�����ͨ�����ӱ༭�����
			mSystem->setPosition(ccp(400,0));//����λ��  
			_gameControl->addChild(mSystem, LAYER_ORDER_CONTROL-1);
			break;
		case BIG_GATE_TYPE_NVERGUO:
			mSystem = CCParticleSystemQuad::create("lizitexiao/yinghua/yinghua.plist");//plist�ļ�����ͨ�����ӱ༭�����
			mSystem->setPosition(ccp(400,480));//����λ��  
			_gameControl->addChild(mSystem, LAYER_ORDER_CONTROL+1); 
			mSystem = CCParticleSystemQuad::create("lizitexiao/yinghuo/yinhuo.plist");//plist�ļ�����ͨ�����ӱ༭�����
			mSystem->setPosition(ccp(400,200));//����λ��  
			_gameControl->addChild(mSystem, LAYER_ORDER_CONTROL+1);  
			break;
		case BIG_GATE_TYPE_HUOYANSHAN:
			break;
		default:
			break;
		}
		for (int i = 0 ; i < targetTotalNum; i++)
		{
			if (((CCInteger *)tmpTargetsType->objectAtIndex(i))->getValue() == 0)
			{
				_gameControl->addChild((Target *)tmpTargets->objectAtIndex(i));
			}
			else
			{
				//_gameControl->addChild(((DynamicTarget *)tmpTargets->objectAtIndex(i))->roleSwaySpeed);
				if (((DynamicTarget *)tmpTargets->objectAtIndex(i))->getId() == DYNAMIC_ID_PEARL_SHELL)
				{
					_gameControl->addChild(((DynamicTargetPearlShell *)tmpTargets->objectAtIndex(i))->getShell());
				}
				else if (((DynamicTarget *)tmpTargets->objectAtIndex(i))->getId() == DYNAMIC_ID_YUMIANGONGZHU)
				{
					_gameControl->addChild(((DynamicTargetYuMianGongZhu *)tmpTargets->objectAtIndex(i))->getPen());
				}
				_gameControl->addChild(((DynamicTarget *)tmpTargets->objectAtIndex(i))->getArmature());
			}
		}
	}

	//DynamicTarget * a = DynamicTarget::getInstance(DYNAMIC_ID_JINGXIGUI, 0, 100, 100);
	//_gameControl->addChild(a->getArmature());

	tmpTargets->removeAllObjects();
	tmpTargetsType->removeAllObjects();
	
	tmpYunTargets->removeAllObjects();
	tmpYunTargetsType->removeAllObjects();
	////CCTMXObjectGroup *objectsTarget = map->objectGroupNamed("target");//��ȡ�����
	//CCTMXObjectGroup *objectsTarget = map->objectGroupNamed("logic");//��ȡ�����
	//cocos2d::CCArray *arrayTarget = objectsTarget->getObjects();
	//for(unsigned int i = 0; i < arrayTarget->count(); i++)
	//{
	//	CCDictionary  *tmp = (CCDictionary  *)arrayTarget->objectAtIndex(i);
	//	if(tmp->valueForKey("type")->intValue() == GAMECONTROL_TYPE_TARGET_STATIC)
	//	{
	//		std::string str = "tmx/";
	//		std::string str1 = tmp->valueForKey("picname")->getCString() + (std::string)".png";
	//		str.append(str1.c_str());
	//		targets->addObject(new Target(tmp->valueForKey("x")->doubleValue(), tmp->valueForKey("y")->doubleValue(),  str.c_str()));
	//		_gameControl->addChild((Target *)targets->lastObject());
	//	}
	//}
}

