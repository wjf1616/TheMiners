#include "Global.h"
#include "Player.h"
#include "GoldenMinerScene.h"

USING_NS_CC;


Global * Global::global = NULL;

Global::Global(void)
{
	//hangerStartX = 0;
	//hangerStartY = 0;
	//hangerCurrX = 0;
	//hangerCurrY = 0;
	//hangerAngle = 0;
	cartoonId = 0;
	jewelSkillScale = 1;
	hangerStatus = HANGER_STATUS_SWAYING;
}

int Global::getTimeByChallengeLevel(void)
{
	if (challengeTimeLevel > 5)
	{
		return 20;
	}
	else if (challengeTimeLevel > 1)
	{
		return (60 - 10*(challengeTimeLevel-1));
	}
	else if (challengeTimeLevel == 1)
	{
		return 60;
	}
	else
	{
		return -1;
	}
}

int Global::getRoleSpeedByRoleId(int _roleId) // 速度
{
	int res = -1;
	switch(_roleId)
	{
	case ROLE_TYPE_TANGSENG:
		res = 2;//3;
		break;
	case ROLE_TYPE_ZHUBAJIE:
		res = 2;//3;
		break;
	case ROLE_TYPE_SHAHESHANG:
		res = 3;//4;
		break;
	case ROLE_TYPE_SUNWUKONG:
		res = 4;//5;
		break;
	case ROLE_TYPE_XIAOLONGNV:
		res = 4;//2;
		break;
	case ROLE_TYPE_HULUWA:
		res = 5;//4;
		break;
	default:
		break;
	}
	return res;
}

int Global::getRoleSwapSpeedByRoleId(int _roleId)// 角速度  技巧
{
	int res = -1;
	switch(_roleId)
	{
	case ROLE_TYPE_TANGSENG:
		res = 2;
		break;
	case ROLE_TYPE_ZHUBAJIE:
		res = 3;
		break;
	case ROLE_TYPE_SHAHESHANG:
		res = 4;//5;
		break;
	case ROLE_TYPE_SUNWUKONG:
		res = 5;//4;
		break;
	case ROLE_TYPE_XIAOLONGNV:
		res = 3;//4;
		break;
	case ROLE_TYPE_HULUWA:
		res = 5;
		break;
	default:
		break;
	}
	return res;
}

void Global::getPayAwardByPayId(int _payId)
{
	switch(_payId)
	{
	case PAY_ID_BUDDAHA: // 元宝2000   佛光普照
		Player::getInstance()->appendPropNum(PROP_TYPE_INGOT ,2000);
		Player::getInstance()->savePropNum(PROP_TYPE_INGOT ,2000);
		Player::getInstance()->appendPropNum(PROP_TYPE_BUDDAHA ,1);
		Player::getInstance()->savePropNum(PROP_TYPE_BUDDAHA ,1);
		Player::getInstance()->setPay(_payId, true);
		break;
	case PAY_ID_SUNWUKONG: // 元宝2000 孙悟空
		Player::getInstance()->appendPropNum(PROP_TYPE_INGOT ,2000);
		Player::getInstance()->savePropNum(PROP_TYPE_INGOT ,2000);
		Player::getInstance()->setRoleHavingStatusByRoleId(ROLE_TYPE_SUNWUKONG, true);
		Player::getInstance()->setRoleOpenStatusByRoleId(ROLE_TYPE_SUNWUKONG, true);
		Player::getInstance()->setOpenNewRole(true);
		Player::getInstance()->setPay(_payId, true);
		break;
	case PAY_ID_HULUWA:	// 葫芦娃
		Player::getInstance()->setRoleHavingStatusByRoleId(ROLE_TYPE_HULUWA, true);
		Player::getInstance()->setRoleOpenStatusByRoleId(ROLE_TYPE_HULUWA, true);
		Player::getInstance()->setOpenNewRole(true);
		Player::getInstance()->setPay(_payId, true);
		break;
	case PAY_ID_MEET:	// 元宝2000  黄金口粮10
		Player::getInstance()->appendPropNum(PROP_TYPE_INGOT ,2000);
		Player::getInstance()->savePropNum(PROP_TYPE_INGOT ,2000);
		Player::getInstance()->appendPropNum(PROP_TYPE_MEET ,10);
		Player::getInstance()->savePropNum(PROP_TYPE_MEET ,10);
		Player::getInstance()->setPay(_payId, true);
		break;
	case PAY_ID_VALUE_PACKAGE: // 特价包		元宝5000  月光宝盒5
		Player::getInstance()->appendPropNum(PROP_TYPE_INGOT ,5000);
		Player::getInstance()->savePropNum(PROP_TYPE_INGOT ,5000);
		Player::getInstance()->appendPropNum(PROP_TYPE_MOONLIGHT ,5);
		Player::getInstance()->savePropNum(PROP_TYPE_MOONLIGHT ,5);
		Player::getInstance()->setPay(_payId, true);
		break;
	case PAY_ID_GOLDEN_PACKAGE:// 黄金包    元宝20000 力量药水5
		Player::getInstance()->appendPropNum(PROP_TYPE_INGOT ,20000);
		Player::getInstance()->savePropNum(PROP_TYPE_INGOT ,20000);
		Player::getInstance()->appendPropNum(PROP_TYPE_VIGOROUSLY_PILL ,5);
		Player::getInstance()->savePropNum(PROP_TYPE_VIGOROUSLY_PILL ,5);
		Player::getInstance()->setPay(_payId, true);
		break;
	default:
		break;
	}
}

int Global::getPetElementIdByHideGateId(int _hideGateId, cocos2d::CCArray * _elementIds)
{
	int res = 0;

	if (Player::getInstance()->getGateOpenStatusByGateId(_hideGateId))
	{
		return res;
	}

	switch(_hideGateId)
	{
	case 10:
		res = 1;
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_JINGXIGUI));
		break;
	case 11:
		res = 2;
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_JINGXIGUI));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_YUMIANGONGZHU));
		break;
	case 12:
		res = 3;
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_JINGXIGUI));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_LINGGANDAWANG));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_YUMIANGONGZHU));
		break;
	case 28:
		res = 1;
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_LINGGANDAWANG));
		break;
	case 29:
		res = 2;
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_JINGXIGUI));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_LINGGANDAWANG));
		break;
	case 30:
		res = 3;
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_JINGXIGUI));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_LINGGANDAWANG));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_NIUMOWANG));
		break;
	case 46:
		res = 1;
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_YUMIANGONGZHU));
		break;
	case 47:
		res = 2;
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_LINGGANDAWANG));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_YUMIANGONGZHU));
		break;
	case 48:
		res = 3;
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_LINGGANDAWANG));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_YUMIANGONGZHU));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_NIUMOWANG));
		break;
	case 64:
		res = 1;
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_NIUMOWANG));
		break;
	case 65:
		res = 2;
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_LINGGANDAWANG));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_NIUMOWANG));
		break;
	case 66:
		res = 3;
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_JINGXIGUI));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_YUMIANGONGZHU));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_NIUMOWANG));
		break;
	case 82:
		res = 2;
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_JINGXIGUI));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_NIUMOWANG));
		break;
	case 83:
		res = 2;
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_YUMIANGONGZHU));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_NIUMOWANG));
		break;
	case 84:
		res = 4;
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_JINGXIGUI));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_LINGGANDAWANG));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_YUMIANGONGZHU));
		_elementIds->addObject(CCInteger::create(PET_ELEMENT_NIUMOWANG));
		break;
	}
	return res;
}

int Global::getChallengCostByChallengeType(int _challengeType)
{
	switch(_challengeType)
	{
	case CHALLENGE_TYPE_IRON:
		return 100;
	case CHALLENGE_TYPE_SILVER:
		return 500;
	case CHALLENGE_TYPE_GOLD:
		return 1000;
	default:
		return -1;
	}
}

int Global::getGenuineGateId(void)
{
	return 3;
}
	
int Global::getWordsIdByMapIdAndRoleId(int _mapId, int _roleId)
{
	return (_mapId*10 + _roleId);
}

int Global::getChallengeLevel(void)
{
	return challengeLevel;
}

void Global::setChallengeLevel(int _b)
{
	challengeLevel = _b;
	if (challengeLevel == 0)
	{
		lastChallengeGateId = 0;
	}
}

int Global::getChallengeTimeLevel(void)// 获得战模式控制时间的层次数
{
	return challengeTimeLevel;
}

void Global::setChallengeTimeLevel(int _level)
{
	challengeTimeLevel = _level;
}

int Global::getChallengeLevelType(void)
{
	return challengeType;
}

void Global::setChallengeLevelType(int _type)
{
	challengeType = _type;
}

int Global::getNextChallengeGateId(void)
{
	// 隐藏关卡不能被随机到  只是已开启的关卡
	int res;
	int _tmp = getMapIdByGateId(Player::getInstance()->getMaxOpenGateId());
	res = rand()%(_tmp + 1);
	if (res == _tmp)
	{
		if ((Player::getInstance()->getMaxOpenGateId() - res * 18) == 1)
		{
			res = Player::getInstance()->getMaxOpenGateId();
		}
		else if ((Player::getInstance()->getMaxOpenGateId() - res * 18) > 9)
		{
			res = res * 18 + 1 +rand()%9;
		}
		else
		{
			res = res * 18 + 1 + rand()%(Player::getInstance()->getMaxOpenGateId() - res * 18);
		}
 	}
	else
	{
		res = res * 18 + 1 +rand()%9;
	}

	if (res == lastChallengeGateId)
	{
		if (res % 18 == 9)
		{
			res--;
		}
		else
		{
			res++;
		}
	}

	return res;
}

int Global::getChallengeCountSum(void)
{
	return challengeCountSum;
}

void Global::setChallengeCountSum(int _sum)
{
	challengeCountSum = _sum;
}

int Global::getPetHeartFull(int _petElementId)
{
	switch(_petElementId)
	{
	case PET_ELEMENT_XIAOZUANFENG:
		return -1;
	case PET_ELEMENT_JINGXIGUI:
		return 20;
	case PET_ELEMENT_LINGLICHONG:
		return -1;
	case PET_ELEMENT_LINGGANDAWANG:
		return 50;
	case PET_ELEMENT_YUMIANGONGZHU:
		return 75;
	case PET_ELEMENT_NIUMOWANG:
		return 99;
	default:
		return -1;
	}
}

void Global::setSelectGateId(int _gateId)// 设置选中的关卡id号 
{
	selectGateId = _gateId;
}
	
int Global::getSelectGateId(void)// 获得选中的关卡id号 
{
	return selectGateId;
}

int Global::getCartoonId(void)
{
	return cartoonId;
}

bool Global::getIsBuyThing(void)
{
	return isBuyThing;
}

void Global::setIsBuyThing(bool _b)
{
	isBuyThing = _b;
}

void Global::setCartoonId(int _gateId)
{
	switch (_gateId)
	{
	case 1:
		cartoonId = CARTOON_BAOXIANGGUO;
		break;
	case 19:
		cartoonId = CARTOON_TONGYIANHE;
		break;
	case 37:
		cartoonId = CARTOON_NVERGUO;
		break;
	case 55:
		cartoonId = CARTOON_HUOYANSHAN;
		break;
	case 73:
		cartoonId = CARTOON_LINGSHAN;
		break;
	case -1:
		cartoonId = CARTOON_END;
		break;
	default:
		cartoonId = 0;
		break;
	}
}

bool Global::getCurrGameLayerLoadDynamicTarget(int _dynamicTargetId)
{
	return currGameLayerLoadDynamicTarget[_dynamicTargetId - DYNAMIC_ID_XIAOZUANFENG];
}

void Global::setCurrGameLayerLoadDynamicTarget(int _dynamicTargetId, bool _isLoaded)
{
	currGameLayerLoadDynamicTarget[_dynamicTargetId - DYNAMIC_ID_XIAOZUANFENG] = _isLoaded;
}

void Global::initCurrGameLayerLoadDynamicTarget(void)
{
	for (int i = DYNAMIC_ID_XIAOZUANFENG; i < DYNAMIC_ID_COUNT; i++)
	{
		currGameLayerLoadDynamicTarget[i - DYNAMIC_ID_XIAOZUANFENG] = false;
	}
}

int Global::getSimleGateNumAndGateIdBySelectBigGateType(cocos2d::CCArray * _gateIds)
{
	int res = -1;


	// 7月10号   安城小熊更改关卡数量  每大关只有12个小关
	switch(selectGateType)
	{
	case BIG_GATE_TYPE_BAOXIANGGUO:
		res = 12;
		for(int i = 0; i < 12; i++)
		{
			_gateIds->addObject(CCInteger::create(i + 1));
		}
		break;
	case BIG_GATE_TYPE_TONGYIANHE:
		res = 12;
		for(int i = 0; i < 12; i++)
		{
			_gateIds->addObject(CCInteger::create(i + 19));
		}
		break;
	case BIG_GATE_TYPE_NVERGUO:
		res = 12;
		for(int i = 0; i < 12; i++)
		{
			_gateIds->addObject(CCInteger::create(i + 37));
		}
		break;
	case BIG_GATE_TYPE_HUOYANSHAN:
		res = 12;
		for(int i = 0; i < 12; i++)
		{
			_gateIds->addObject(CCInteger::create(i + 55));
		}
		break;
	case BIG_GATE_TYPE_LINGSHAN:
		res = 12;
		for(int i = 0; i < 12; i++)
		{
			_gateIds->addObject(CCInteger::create(i + 73));
		}
		break;
	default:
		break;
	}

	return res;
}

int Global::getMapIdByGateId(int _gateId)
{
	int res = -1;
	if ((_gateId > 0) && (_gateId < 19))
	{
		res = BIG_GATE_TYPE_BAOXIANGGUO;
	} 
	else if ((_gateId > 18) && (_gateId < 37))
	{
		res = BIG_GATE_TYPE_TONGYIANHE;
	}
	else if ((_gateId > 36) && (_gateId < 55))
	{
		res = BIG_GATE_TYPE_NVERGUO;
	}
	else if ((_gateId > 54) && (_gateId < 73))
	{
		res = BIG_GATE_TYPE_HUOYANSHAN;
	}
	else if ((_gateId > 72) && (_gateId < 91))
	{
		res = BIG_GATE_TYPE_LINGSHAN;
	}

	return res;
}

int Global::getSmallGateIdByGateId(int _gateId)
{
	int res = -1;
	if ((_gateId > 0) && (_gateId < 19))
	{
		res = _gateId;
	} 
	else if ((_gateId > 18) && (_gateId < 37))
	{
		res = _gateId - 18;
	}
	else if ((_gateId > 36) && (_gateId < 55))
	{
		res = _gateId - 36;
	}
	else if ((_gateId > 54) && (_gateId < 73))
	{
		res = _gateId - 54;
	}
	else if ((_gateId > 72) && (_gateId < 91))
	{
		res = _gateId - 72;
	}
#ifdef													GOLDEN_MINER_2_NEW_GUIDE
	else if ((_gateId > 996) && (_gateId < 1000))
	{
		// 引导
		res = _gateId - 996;
	}
#else
	else if ((_gateId > 993) && (_gateId < 1000))
	{
		// 引导
		res = _gateId - 993;
	}
#endif

	return res;
}

int Global::getSelectGateType(void)
{
	return selectGateType;
}

void Global::setSelectGateType(int _gateType)
{
	selectGateType = _gateType;
}


void Global::setSelectGateNextGateId(int _nextGateId)// 设置选中的关卡下一关id号 
{
	nextGateId = _nextGateId;
}

int Global::getSelectGateNextGateId(void)// 获得选中的关卡下一关id号 
{
	return nextGateId;
}

int Global::getSelectRoleId(void)// 获得选择人物的角色
{
	return selectRoleId;
}

void Global::setSelectRoleId(int _roleId)// 设置选择人物的角色
{
	selectRoleId = _roleId;
}

int Global::getCurrGuideId(void)
{
	return currGuideId;
}

void Global::setCurrGuideId(int _guideId)
{
	currGuideId = _guideId;
}

int Global::getSceneSpeedByMapId(int _mapId)// 通过map的id来获的场景速度
{
	switch(_mapId%10 - 1)
	{
	case BIG_GATE_TYPE_BAOXIANGGUO:
		return 10;
	case BIG_GATE_TYPE_TONGYIANHE:
		return 10;
	case BIG_GATE_TYPE_NVERGUO:
		return 10;
	case BIG_GATE_TYPE_HUOYANSHAN:
		return 10;
	case BIG_GATE_TYPE_LINGSHAN:
		return 10;
	default:
		return -1;
	}
}

/**************************************************
吸取东西同时到达的处理
**************************************************/	
void Global::setJewelSkillScale(double _scale)
{
	jewelSkillScale = _scale;
}

double Global::getJewelSkillScale(void)
{
	return jewelSkillScale;
}

/**************************************************
	吸取东西到达时长确定（移动速度不定）的异步到达
******************************************************/	
float Global::getJewelSkillDistance(void)
{
	return jewelSkillDistance;
}

void Global::setJewelSkillDistance(float _distance)
{
	jewelSkillDistance = _distance;
}

int Global::getRolePriceByRoleId(int _roleId)
{
	int res = -1;
	switch(_roleId)
	{
	case ROLE_TYPE_XIAOLONGNV:
		res = 9999;
		break;
	case ROLE_TYPE_ZHUBAJIE:
		res = 1000;
		break;
	case ROLE_TYPE_SHAHESHANG:
		res = 2000;
		break;
	case ROLE_TYPE_SUNWUKONG:
		res = 5000;
		break;
	default:
		break;
	}
	return res;
}

void Global::initValueTimes(void)
{
	//memset(propAwardTimes, 1, PROP_TYPE_COUNT * sizeof(int));
	for (int i = 0; i < TARGET_TYPE_COUNT; i++)
	{
		propAwardTimes[i] = 1;
	}
}

void Global::setValueTimes(int _targetType, int _times)
{
	propAwardTimes[_targetType] = _times;
}

int Global::getPropAwardNumById(int _propId)
{
	return propAwardGet[_propId];
}

void Global::appendPropAwardGet(int _targetType, int _propId, int _num)
{
	if (_propId == PROP_TYPE_COIN && Player::getInstance()->getSelectPet() == PET_ELEMENT_YUMIANGONGZHU)
	{
		propAwardGet[_propId] += _num * propAwardTimes[_targetType] * 1.2;
	}
	else
	{
		propAwardGet[_propId] += _num * propAwardTimes[_targetType];
	}

	if (_propId >= PROP_TYPE_JEWEL_BLUE && _propId <= PROP_TYPE_JEWEL_PURPLE)
	{
		if (_num > 0)
		{
			getJewelCount += _num;
		}
	}
}

void Global::appendPropAwardGet(int _propId, int _num)
{
	if (_propId == PROP_TYPE_COIN && Player::getInstance()->getSelectPet() == PET_ELEMENT_YUMIANGONGZHU)
	{
		propAwardGet[_propId] += _num * 1.2;
	}
	else
	{
		propAwardGet[_propId] += _num;
	}

	if (_propId >= PROP_TYPE_JEWEL_BLUE && _propId <= PROP_TYPE_JEWEL_PURPLE)
	{
		if (_num > 0)
		{
			getJewelCount += _num;
		}
	}
}

void Global::initPropAwardGet(void)
{
	memset(propAwardGet, 0, PROP_TYPE_COUNT * sizeof(int));

	maxContinuesCount = 0;// 最大连击数
	getJewelCount = 0;// 获得的宝石的统计数
}

void Global::initPetElementGet(void)
{
	memset(petElementGet, 0 , sizeof(int) * PET_ELEMENT_COUNT);
}

void Global::appendPetElementGet(int _petElementId, int _num)
{
	petElementGet[_petElementId] += _num;
}

int Global::getPetElementGetById(int _petElementId)
{
	return petElementGet[_petElementId];
}

bool Global::getPetIsOpenByIdAndNum(int _petElementId, int num)
{
	bool res = false;
	switch(_petElementId)
	{
	case PET_ELEMENT_XIAOZUANFENG:
		if (num > 0)
		{
			res = true;
		}
		break;
	case PET_ELEMENT_JINGXIGUI:
		if (num > 0)
		{
			res = true;
		}
		break;
	case PET_ELEMENT_LINGLICHONG:
		if (num > 0)
		{
			res = true;
		}
		break;
	case PET_ELEMENT_LINGGANDAWANG:
		if (num > 0)
		{
			res = true;
		}
		break;
	case PET_ELEMENT_YUMIANGONGZHU:
		if (num > 0)
		{
			res = true;
		}
		break;
	case PET_ELEMENT_NIUMOWANG:
		if (num > 0)
		{
			res = true;
		}
		break;
	default:
		break;
	}

	return res;
}

Global::~Global(void)
{
	if(global != NULL)
	{
		delete(global);
	}
}

Global * Global::getInstance(void)
{
	if(global == NULL)
	{
		global = new Global();
	}

	return global;
}

int Global::getGetJewelCount(void)
{
	return getJewelCount;
}

int Global::getMaxContinusesCount(void)
{
	return maxContinuesCount;
}
	
int Global::getContinuesCount(void)
{
	return continuousCount;
}

void Global::setContinuesCount(int _appendNum)
{
	continuousCount += _appendNum;

	if (continuousCount > maxContinuesCount)
	{
		maxContinuesCount = continuousCount;
	}
}

void Global::initContinuesCount(void)
{
	continuousCount = 0;
}

//double Global::getHangerStartX(void)
//{
//	return hangerStartX;
//}
//
//void Global::setHangerStartX(double _x)
//{
//	hangerStartX = _x;
//}
//
//double Global::getHangerStartY(void)
//{
//	return hangerStartY;
//}
//
//void Global::setHangerStartY(double _y)
//{
//	hangerStartY = _y;
//}

//double Global::getHangerCurrX(void)
//{
//	return hangerCurrX;
//}
//
//void Global::setHangerCurrX(double _x)
//{
//	hangerCurrX = _x;
//}
//
//double Global::getHangerCurrY(void)
//{
//	return hangerCurrY;
//}
//
//void Global::setHangerCurrY(double _y)
//{
//	hangerCurrY = _y;
//}
//
//double Global::getHangerAngle(void)
//{
//	return hangerAngle;
//}
//
//void Global::setHangerAngle(double _angle)
//{
//	hangerAngle = _angle;
//}

int Global::getHangerStatus(void)
{
	return hangerStatus;
}

void Global::setHangerStatus(int _status)
{
	hangerStatus = _status;
}

//double Global::getHangerDistanceToRope(void)
//{
//	return hangerDistanceToRope;
//}

//void Global::setHangerDistanceToRope(double _hangerDistanceToRope)
//{
//	hangerDistanceToRope = _hangerDistanceToRope;
//}
//
//double Global::getHangerDistanceToCentre(void)
//{
//	return hangerDistanceToCentre;
//}
//
//void Global::setHangerDistanceToCentre(double _hangerDistanceToCentre)
//{
//	hangerDistanceToCentre = _hangerDistanceToCentre;
//}
	
//bool Global::getHangerCanThrow(void)
//{
//	return hangerCanThrow;
//}
//	
//void Global::setHangerCanThrow(bool _b)
//{
//	hangerCanThrow = _b;;
//}

double Global::getcentreX(void)
{
	return centreX;
}

void Global::setcentreX(double _centreX)
{
	centreX = _centreX;
}

double Global::getcentreY(void)
{
	return centreY;
}

void Global::setcentreY(double _centreY)
{
	centreY = _centreY;
}

int Global::getGameControlTypeById(int _id)
{
	if (_id > 1000)
	{
		_id = _id / 1000;
	}

	return _id;
}

#ifdef							GOLDEN_MINER_2_VERSION_TIME
float Global::getTimeRatio(void)
{
	return timeRatio;
}

void Global::setTimeRatio(float _f)
{
	timeRatio = _f;
}
#endif

// 工具

bool Global::isInRect(cocos2d::CCRect * _rect, double _pointX, double _pointY)
{
	//CCLOG("minx = %f, maxx = %f, miny = %f, maxy = %f, x = %f, y = %f;", _rect->getMinX(), _rect->getMaxX(), _rect->getMinY(), _rect->getMaxY(), _pointX, _pointY);
	if ((_pointX < _rect->getMaxX()) && (_pointY < _rect->getMaxY()) && (_pointX > _rect->getMinX()) && (_pointY > _rect->getMinY()))
	{
		return true;
	}
	return false;
}

bool Global::isInCircle(double _x, double _y, double _pointX, double _pointY, double _r)
{
	if (((_x - _pointX)*(_x - _pointX) + (_y - _pointY)*(_y - _pointY)) < _r*_r)
	{
		return true;
	}
	return false;
}

bool Global::intersectCCRectWithSector(cocos2d::CCRect * _rect, double _pointX, double _pointY, double _angleL, double _angleR)
{
	bool res = false;
	double angle[4];
	angle[0] = atan2(_rect->getMaxY() - _pointY, _rect->getMaxX() - _pointX) * angleChange / pi;
	angle[1] = atan2(_rect->getMaxY() - _pointY, _rect->getMinX() - _pointX) * angleChange / pi;
	angle[2] = atan2(_rect->getMinY() - _pointY, _rect->getMaxX() - _pointX) * angleChange / pi;
	angle[3] = atan2(_rect->getMinY() - _pointY, _rect->getMinX() - _pointX) * angleChange / pi;

	for (unsigned int i = 0; i < 4; i++)
	{
		changeAngleAtan2To360(&angle[i]);
	}

	double angleMin = getMin(angle, 4);
	double angleMax = getMax(angle, 4);

	//CCLOG("GameControl : angleMin = %f, angleMax = %f, angleL = %f, angleR = %f", angleMin, angleMax, _angleL, _angleR);

	if ((_angleL > angleMin) && (_angleL < angleMax))
	{
		res = true;
	}
	else if ((_angleR > angleMin) && (_angleR < angleMax))
	{
		res = true;
	}
	else if ((_angleL < angleMin) && (_angleR > angleMin))
	{
		res = true;
	}
	else if ((_angleL < angleMax) && (_angleR > angleMax))
	{
		res = true;
	}

	return res;
}


bool Global::intersectCCRectWithSector(double _rectX, double _rectY, double _rectW, double _rectH, double _pointX, double _pointY, double _angleL, double _angleR)
{
	bool res = false;
	double angle[4];

	angle[0] = atan2(_rectH - _pointY, _rectW - _pointX) * angleChange / pi;
	angle[1] = atan2(_rectY - _pointY, _rectW - _pointX) * angleChange / pi;
	angle[2] = atan2(_rectH - _pointY, _rectX - _pointX) * angleChange / pi;
	angle[3] = atan2(_rectY - _pointY, _rectX - _pointX) * angleChange / pi;

	for (unsigned int i = 0; i < 4; i++)
	{
		changeAngleAtan2To360(&angle[i]);
	}

	double angleMin = getMin(angle, 4);
	double angleMax = getMax(angle, 4);

	//CCLOG("GameControl : angleMin = %f, angleMax = %f, angleL = %f, angleR = %f", angleMin, angleMax, _angleL, _angleR);

	if ((_angleL > angleMin) && (_angleL < angleMax))
	{
		res = true;
	}
	else if ((_angleR > angleMin) && (_angleR < angleMax))
	{
		res = true;
	}
	else if ((_angleL < angleMin) && (_angleR > angleMin))
	{
		res = true;
	}
	else if ((_angleL < angleMax) && (_angleR > angleMax))
	{
		res = true;
	}

	return res;
}

double Global::getMin(double _tmp[], unsigned int _num)
{
	double res = _tmp[0];
	for(unsigned int i = 1; i < _num ; i++)
	{
		if (_tmp[i] < res)
		{
			res = _tmp[i];
		}
	}
	return res;
}

double Global::getMax(double _tmp[], unsigned int _num)
{
	double res = _tmp[0];
	for(unsigned int i = 1; i < _num ; i++)
	{
		if (_tmp[i] > res)
		{
			res = _tmp[i];
		}
	}
	return res;	
}

void Global::changeAngleAtan2To360(double * angle)
{
	while (*angle <0)
	{
		*angle += 360;
	}
}

bool Global::isLeapYear(int _year)
{
	bool res = false;
	if (_year % 4 == 0)
	{
		if (_year % 100 == 0)
		{
			if (_year % 400 == 0)
			{
				res = true;
			}
		}
		else
		{
			res = true;
		}
	}

	return res;
}