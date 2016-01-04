#include "DateManger.h"

USING_NS_CC;

DateManger * DateManger::dateManger = NULL;

/************************************************
	gate相关信息
	int			gateId		关卡的编号				
	string		tsmNum		关卡的地编文件名	gateId+tsmNum
	bool		on			关卡是否开启		gateId+on
	int			lever		通关关卡的等级		gateId+lever
************************************************/

/************************************************
	role相关信息
	int			roleId		角色的编号				
	bool		on			角色是否开启		roleId+on
************************************************/

/***********************************************
	player相关信息
	int			roleId		当前玩家选择的人	player+roleId
	int			propId		道具id号			
	int			propNum		道具数量			player+propId+propNum
***********************************************/

/***********************************************
	music相关信息
	bool			musicBackGround	背景音乐
	bool			musicEffect		音效
***********************************************/

DateManger::DateManger(void)
{
	if(!getGoldenMiner2IsInit())
	{// 如果游戏没有初始化 则初始话
		initDate();
	}
}


DateManger::~DateManger(void)
{
}


DateManger * DateManger::getInstance(void)
{
	if (dateManger == NULL)
	{
		dateManger = new DateManger();
	}

	return dateManger;
}

/*********************************************
	gate相关
***********************************************/
// map存储
void DateManger::saveGateMapOn(int _gateMapId, bool _on)
{
	sprintf(_s, "map_on_%d", _gateMapId);
	CCUserDefault::sharedUserDefault()->setBoolForKey(_s, _on); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getGateMapOn(int _gateMapId)
{
	sprintf(_s, "map_on_%d", _gateMapId);
	return CCUserDefault::sharedUserDefault()->getBoolForKey(_s, false); 
}

void DateManger::saveLastMapId(int _lastMapId)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("lastmapid", _lastMapId); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

int DateManger::getLastMapId(void)
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("lastmapid", BIG_GATE_TYPE_GUIDE); 
}

void DateManger::saveMapLastRoleId(int _gateId, int _roleId)
{
	sprintf(_s, "gate_role_%d", _gateId);
	CCUserDefault::sharedUserDefault()->setIntegerForKey(_s, _roleId); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

int DateManger::getMapLastRoleId(int _gateId)
{
	sprintf(_s, "gate_role_%d", _gateId);
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(_s, 0); 
}

void DateManger::saveHideGateDraw(int _hideGateId, bool _isdraw)
{
	sprintf(_s, "hide_gateid_%d", _hideGateId);
	CCUserDefault::sharedUserDefault()->setBoolForKey(_s, _isdraw); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getHideGateDraw(int _hideGateId)
{
	sprintf(_s, "hide_gateid_%d", _hideGateId);
	return CCUserDefault::sharedUserDefault()->getBoolForKey(_s, false); 
}

void DateManger::saveHideGateDay(int _day)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("day_hidegate", _day); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

int DateManger::getHideGateDay(void)
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("day_hidegate", 0); 
}

// 特殊关卡
void DateManger::saveGateOn(int _gateId, bool _on)
{
	sprintf(_s, "gate_on_%d", _gateId);
	CCUserDefault::sharedUserDefault()->setBoolForKey(_s, _on); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getGateOn(int _gateId)
{
	sprintf(_s, "gate_on_%d", _gateId);
	return CCUserDefault::sharedUserDefault()->getBoolForKey(_s, false); 
}

void DateManger::saveGateLever(int _gateId, int _lever)
{
	sprintf(_s, "gate_lever_%d", _gateId);
	CCUserDefault::sharedUserDefault()->setIntegerForKey(_s, _lever); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

int DateManger::getGateLever(int _gateId)
{
	sprintf(_s, "gate_lever_%d", _gateId);
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(_s, 0); 
}
/*************************************************************
	挑战模式相关
**************************************************************/
bool DateManger::getChallengeIsOpen(void)
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("challengeopen");
}

void DateManger::saveChallengeIsOpen(bool _isOpeng)
{
	CCUserDefault::sharedUserDefault()->setBoolForKey("challengeopen", _isOpeng); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getChallengeAppendName(void)
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("challengename");
}
void DateManger::saveChallengeAppendName(bool _name)
{
	CCUserDefault::sharedUserDefault()->setBoolForKey("challengename", _name); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getChallengeUpdate(void)
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("challengeupdate");
}

void DateManger::saveChallengeUpdate(bool _isUpdate)
{
	CCUserDefault::sharedUserDefault()->setBoolForKey("challengeupdate", _isUpdate); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

int DateManger::getChallengeRecordRoleId()
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("challenge_record_role");
}

void DateManger::saveChallengeRecordRoleId(int _roleId)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("challenge_record_role", _roleId); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

int DateManger::getChallengeRecordLever()
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("challenge_record_lever");
}

void DateManger::saveChallengeRecordLever(int _level)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("challenge_record_lever", _level); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

int DateManger::getChallengeRecordScore()
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("challenge_record_score");
}

void DateManger::saveChallengeRecordScore(int _score)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("challenge_record_score", _score); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

std::string DateManger::getChallengeRecordName()
{
	return CCUserDefault::sharedUserDefault()->getStringForKey("challenge_record_name");
}

void DateManger::saveChallengeRecordName(std::string _str)
{
	CCUserDefault::sharedUserDefault()->setStringForKey("challenge_record_name", _str); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

int DateManger::getChallengeMaxLever(void)
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("challenge_maxlever");
}

void DateManger::saveChallengeMaxLever(int _level)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("challenge_maxlever", _level); 
	CCUserDefault::sharedUserDefault()->flush(); 
}
//
//int DateManger::getChallengeNum(void)
//{
//	return CCUserDefault::sharedUserDefault()->getIntegerForKey("challenge_num");
//}
//
//void DateManger::saveChallengeNum(int _num)
//{
//	CCUserDefault::sharedUserDefault()->setIntegerForKey("challenge_num", _num); 
//	CCUserDefault::sharedUserDefault()->flush(); 
//}
//
//int DateManger::getChallengeRecordLever(int _id)
//{
//	sprintf(_s, "challenge_record_lever_%d", _id);
//	return CCUserDefault::sharedUserDefault()->getIntegerForKey(_s);
//}
//
//void DateManger::saveChallengeRecordLever(int _id, int _level)
//{
//	sprintf(_s, "challenge_record_lever_%d", _id);
//	CCUserDefault::sharedUserDefault()->setIntegerForKey(_s, _level); 
//	CCUserDefault::sharedUserDefault()->flush(); 
//}
//
//int DateManger::getChallengeRecordScore(int _id)
//{
//	sprintf(_s, "challenge_record_score_%d", _id);
//	return CCUserDefault::sharedUserDefault()->getIntegerForKey(_s);
//}
//
//void DateManger::saveChallengeRecordScore(int _id, int _score)
//{
//	sprintf(_s, "challenge_record_score_%d", _id);
//	CCUserDefault::sharedUserDefault()->setIntegerForKey(_s, _score); 
//	CCUserDefault::sharedUserDefault()->flush(); 
//}
//
//std::string DateManger::getChallengeRecordName(int _id)
//{
//	sprintf(_s, "challenge_record_name_%d", _id);
//	return CCUserDefault::sharedUserDefault()->getStringForKey(_s);
//}
//
//void DateManger::saveChallengeRecordName(int _id, std::string _str)
//{
//	sprintf(_s, "challenge_record_name_%d", _id);
//	CCUserDefault::sharedUserDefault()->setStringForKey(_s, _str); 
//	CCUserDefault::sharedUserDefault()->flush(); 
//}
/*********************************************
	role相关
***********************************************/
void DateManger::saveRoleOn(int _roleId, bool _on)
{
	sprintf(_s, "role_on_%d", _roleId);
	CCUserDefault::sharedUserDefault()->setBoolForKey(_s, _on); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getRoleOn(int _roleId)
{
	sprintf(_s, "role_on_%d", _roleId);
	return CCUserDefault::sharedUserDefault()->getBoolForKey(_s, false); 
}

bool DateManger::getRoleHaving(int _roleId)
{
	sprintf(_s, "role_having_%d", _roleId);
	return CCUserDefault::sharedUserDefault()->getBoolForKey(_s, false); 
}

void DateManger::saveRoleHaving(int _roleId, bool _isOpen)
{
	sprintf(_s, "role_having_%d", _roleId);
	CCUserDefault::sharedUserDefault()->setBoolForKey(_s, _isOpen); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

/*********************************************
	player相关
***********************************************/
void DateManger::savePlayerRoleId(int _roleId)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("player_roleid", _roleId); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

int DateManger::getPlayerRoleId(void)
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("player_roleid", ROLE_TYPE_START); 
}

void DateManger::savePlayerPropNum(int _propId, int _num)
{
	sprintf(_s, "player_propid_%d", _propId);

	if (_num > 99 && (_propId == PROP_TYPE_GRENADE || _propId == PROP_TYPE_MOONLIGHT || _propId == PROP_TYPE_VIGOROUSLY_PILL))
	{
		_num = 99;
	}

	if (_num > 99999 && (_propId == PROP_TYPE_FOOD || _propId == PROP_TYPE_MEET))
	{
		_num = 99999;
	}

	CCUserDefault::sharedUserDefault()->setIntegerForKey(_s, _num); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

int DateManger::getPlayerPropNum(int _propId)
{
	sprintf(_s, "player_propid_%d", _propId);
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(_s, 0); 
}

bool DateManger::getOpenNewRole(void)
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("player_new_open_role", false); 
}

void DateManger::saveOpenNewRole(bool _b)
{
	CCUserDefault::sharedUserDefault()->setBoolForKey("player_new_open_role", _b); 
	CCUserDefault::sharedUserDefault()->flush(); 
}
/*********************************************
	初始化
***********************************************/
void DateManger::saveGoldenMiner2IsInit(bool _isFrist)
{
	CCUserDefault::sharedUserDefault()->setBoolForKey("GoldenMiner2", _isFrist); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getGoldenMiner2IsInit(void)
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("GoldenMiner2", false); 
}


/*********************************************
	音效相关
***********************************************/
void DateManger::saveMusicBackGround(bool _isOpen)
{
	CCUserDefault::sharedUserDefault()->setBoolForKey("MusicBackGround", _isOpen); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getMusicBackGround(void)
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("MusicBackGround", false); 
}

void DateManger::saveMusicEffect(bool _isOpen)
{
	CCUserDefault::sharedUserDefault()->setBoolForKey("MusicEffect", _isOpen); 
	CCUserDefault::sharedUserDefault()->flush();  
}

bool DateManger::getMusicEffect(void)
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("MusicEffect", false); 
}

/*********************************************
	宠物相关
***********************************************/
void DateManger::savePetTeach(int _petElementId, bool _isHaving)
{
	sprintf(_s, "teach_petelementid_%d", _petElementId);
	CCUserDefault::sharedUserDefault()->setBoolForKey(_s, _isHaving); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getPetTeach(int _petElementId)
{
	sprintf(_s, "teach_petelementid_%d", _petElementId);
	return CCUserDefault::sharedUserDefault()->getBoolForKey(_s, false); 
}

void DateManger::savePetHaving(int _petElementId, bool _isHaving)
{
	sprintf(_s, "having_petelementid_%d", _petElementId);
	CCUserDefault::sharedUserDefault()->setBoolForKey(_s, _isHaving); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getPetHaving(int _petElementId)
{
	sprintf(_s, "having_petelementid_%d", _petElementId);
	return CCUserDefault::sharedUserDefault()->getBoolForKey(_s, false); 
}

void DateManger::savePetBorn(int _petElementId, bool _isHaving)
{
	sprintf(_s, "born_petelementid_%d", _petElementId);
	CCUserDefault::sharedUserDefault()->setBoolForKey(_s, _isHaving); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getPetBorn(int _petElementId)
{
	sprintf(_s, "born_petelementid_%d", _petElementId);
	return CCUserDefault::sharedUserDefault()->getBoolForKey(_s, false); 
}

void DateManger::savePetHeart(int _petElementId, int _num)
{
	sprintf(_s, "num_petheartid_%d", _petElementId);
	CCUserDefault::sharedUserDefault()->setIntegerForKey(_s, _num); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

int DateManger::getPetHeart(int _petElementId)
{
	sprintf(_s, "num_petheartid_%d", _petElementId);
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(_s, 0); 
}

void DateManger::savePetElement(int _petElementId, int _num)
{
	sprintf(_s, "num_petelementid_%d", _petElementId);
	CCUserDefault::sharedUserDefault()->setIntegerForKey(_s, _num); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

int DateManger::getPetElement(int _petElementId)
{
	sprintf(_s, "num_petelementid_%d", _petElementId);
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(_s, 0); 
}

int DateManger::getSelectPet(void)
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("selected_pet", -1); 
}

void DateManger::saveSelectPet(int _id)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("selected_pet", _id); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

void DateManger::savePetDay(int _day)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("day_pet", _day); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

int DateManger::getPetDay(void)
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("day_pet", 0); 
}

/*********************************************
漫画相关
***********************************************/
void DateManger::saveCarttonIsFrist(bool _isFrist)
{
	CCUserDefault::sharedUserDefault()->setBoolForKey("CartoonFirst", _isFrist); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getCarttonIsFrist(void)
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("CartoonFirst", false); 
}

void DateManger::saveCarttonIsPlay(int _cartoonId, bool _isPlay)
{
	sprintf(_s, "cartoon_play_%d", _cartoonId);
	CCUserDefault::sharedUserDefault()->setBoolForKey(_s, _isPlay); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getCarttonIsPlay(int _cartoonId)
{
	sprintf(_s, "cartoon_play_%d", _cartoonId);
	return CCUserDefault::sharedUserDefault()->getBoolForKey(_s, false); 
}
/*********************************************
引导相关
***********************************************/
void DateManger::saveGuideSlipBigGate(bool _isFrist)
{
	CCUserDefault::sharedUserDefault()->setBoolForKey("slipbiggate", _isFrist); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getGuideSlipBigGate(void)
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("slipbiggate", false); 
}

void DateManger::saveGuideSlipRole(bool _isFrist)
{
	CCUserDefault::sharedUserDefault()->setBoolForKey("sliprole", _isFrist); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getGuideSlipRole(void)
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("sliprole", false); 
}

void DateManger::saveGuideSlipChallenge(bool _isFrist)
{
	CCUserDefault::sharedUserDefault()->setBoolForKey("slipchallenge", _isFrist); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getGuideSlipChallenge(void)
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("slipchallenge", false);
}

void DateManger::saveGuideIsFrist(bool _isFrist)
{
	CCUserDefault::sharedUserDefault()->setBoolForKey("GuideFirst", _isFrist); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

bool DateManger::getGuideIsFrist(void)
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("GuideFirst", false); 
}

void DateManger::saveGuideLastIndex(int _index)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("guide_last_index", _index); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

int DateManger::getGuideLastIndex(void)
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("guide_last_index", GUIDE_ID_START); 
}

bool DateManger::getIsGetAwardByGuideId(int _guideId)
{
	sprintf(_s, "guide_award_%d", _guideId);
	return CCUserDefault::sharedUserDefault()->getBoolForKey(_s, false); 
}

void DateManger::saveIsGetAwardByGuideId(int _guideId, bool _isGet)
{
	sprintf(_s, "guide_award_%d", _guideId);
	CCUserDefault::sharedUserDefault()->setBoolForKey(_s, _isGet); 
	CCUserDefault::sharedUserDefault()->flush(); 
}
/**********************************************************
提示相关
***********************************************************/
bool DateManger::getTip(int _tipId)
{
	sprintf(_s, "tip_%d", _tipId);
	return CCUserDefault::sharedUserDefault()->getBoolForKey(_s, false); 
}

void DateManger::saveTip(int _tipId, bool _isGet)
{
	sprintf(_s, "tip_%d", _tipId);
	CCUserDefault::sharedUserDefault()->setBoolForKey(_s, _isGet); 
	CCUserDefault::sharedUserDefault()->flush(); 
}
/**********************************************************
提示相关
***********************************************************/
void DateManger::saveRegisterDay(int _day)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("day_register", _day); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

int DateManger::getRegisterDay(void)
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("day_register", 0); 
}

void DateManger::saveRegisterCount(int _count)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("count_register", _count); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

int DateManger::getRegisterCount(void)
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("count_register", 0); 
}
/**********************************************************
计费相关
***********************************************************/
bool DateManger::getPay(int _tipId)
{
	sprintf(_s, "pay_%d", _tipId);
	return CCUserDefault::sharedUserDefault()->getBoolForKey(_s, false); 
}

void DateManger::savePay(int _tipId, bool _isGet)
{
	sprintf(_s, "pay_%d", _tipId);
	CCUserDefault::sharedUserDefault()->setBoolForKey(_s, _isGet); 
	CCUserDefault::sharedUserDefault()->flush(); 
}

void DateManger::initDate(void)
{
	time_t  time1 = time(NULL);
	struct tm *tm;
	tm = localtime(&time1);
	int day = tm->tm_mday;
	day += tm->tm_mon * 100;
	day += tm->tm_year * 10000;
	saveGoldenMiner2IsInit(true);
	// 关卡信息初始化
#ifndef										GOLDEN_MINER_2_NEW_GUIDE
	saveLastMapId(BIG_GATE_TYPE_GUIDE);
#else
	saveLastMapId(BIG_GATE_TYPE_BAOXIANGGUO);
#endif
	for(int i = GATE_ID_MIN; i <= GATE_ID_MAX; i++)
	{
		if (i == GATE_ID_START)
		{
			saveGateOn(i, true);
		}
		else
		{
			//saveGateOn(i, true);
			saveGateOn(i, false);
		}
		saveGateLever(i, 0);
	}
	for(int i = BIG_GATE_TYPE_BAOXIANGGUO; i < BIG_GATE_TYPE_COUNT; i++)
	{
		if (i == BIG_GATE_TYPE_BAOXIANGGUO)
		{
			saveGateMapOn(i, true);
		}
		else
		{
			//saveGateMapOn(i, true);
			saveGateMapOn(i, false);
		}
		saveMapLastRoleId(i, 0);
	}
	saveHideGateDay(day);
	for (int i = 0; i < (BIG_GATE_TYPE_COUNT-1);i++)
	{
		for (int j = 0; j < 3; j++)
		{
			saveHideGateDraw(i*18 + 10 + j, true);
		}
	}

	// 角色信息初始化
	for (int i = 0; i <= ROLE_TYPE_COUNT; i++)
	{
		if (i == ROLE_TYPE_START)
		{
			saveRoleOn(i, true);
			saveRoleHaving(i, true);
			continue;
		}
		saveRoleOn(i, false);
		saveRoleHaving(i, false);
	}
	// 玩家信息初始化
	for (int i = 1; i <= PROP_TYPE_COUNT; i++)
	{
		savePlayerPropNum(i, 0);
		if (i == PROP_TYPE_INGOT)
		{
			savePlayerPropNum(i, 99999);
		}
		if (i == PROP_TYPE_FOOD)
		{
			savePlayerPropNum(i, 999);
		}
	}
	saveOpenNewRole(false);
	savePlayerRoleId(ROLE_TYPE_START);
	
	// music相关
	saveMusicBackGround(true);
	saveMusicEffect(true);

	// 宠物相关
	saveSelectPet(-1);
	savePetDay(day);
	for (int i = PET_ELEMENT_XIAOZUANFENG; i < PET_ELEMENT_COUNT; i++)
	{
		savePetTeach(i, true);
		savePetHaving(i, false);
		savePetElement(i, 0);
		savePetHeart(i, 0);
		savePetBorn(i, false);
	}

	// cartoon相关
	saveCarttonIsFrist(false);
	saveCarttonIsPlay(CARTOON_START, false);
	saveCarttonIsPlay(CARTOON_END, false);
	for(int i = CARTOON_BAOXIANGGUO; i <= CARTOON_LINGSHAN; i++)
	{
		saveCarttonIsPlay(i, false);
	}

	// 引导相关
	saveGuideIsFrist(true);
	saveGuideSlipBigGate(true);
	saveGuideSlipRole(true);
	saveGuideSlipChallenge(true);
	saveGuideLastIndex(GUIDE_ID_START);
	for (int i = GUIDE_ID_GRAP; i <= GUIDE_ID_JEWEIL_SKILL; i++)
	{
		saveIsGetAwardByGuideId(i, false);
	}
	
	// 提示相关
	for (int i = TIP_GAMING_START; i <= TIP_GAMING_END; i++)
	{
		saveTip(i, true);
	}
	// 计费相关
	for (int i = PAY_ID_GENUINE; i <= PAY_ID_MEET; i++)
	{
		savePay(i, false);
	}

	// 挑战模式
	saveChallengeIsOpen(false);
	saveChallengeUpdate(false);
	saveChallengeAppendName(true);
	saveChallengeRecordLever(-1);
	//saveChallengeNum(0);
	//saveChallengeMaxLever(0);

	// 签到相关
	saveRegisterCount(0);
	saveRegisterDay(0);
}