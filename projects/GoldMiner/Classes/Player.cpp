#include "Player.h"
#include "DateManger.h"
#include "GameControl.h"
// ��Ҷ�������ݴ洢���п���

#define									JEWEL_BUTTON_COUNT					1
#define									LIGHT_BUTTON_COUNT					1

Player * Player::player = NULL;

Player::Player(void)
{
}


Player::~Player(void)
{
}

Player * Player::getInstance(void)
{
	if (player == NULL)
	{
		player = new Player();
		player->init();
	}

	return player;
}

void Player::init(void)
{
	imei = 123456789;
	memset(imeiStr, 0, IMEI_LENGTH);
	imeiStr[0] = '1';
	imeiStr[1] = '2';
	imeiStr[2] = '3';
	imeiStr[3] = '4';
	imeiStr[4] = '5';
	imeiStr[5] = '6';
	imeiStr[6] = '7';
	imeiStr[7] = '8';
	imeiStr[8] = '9';

	// ���߸�����ʼ��
	memset(propNum, 0, sizeof(int) * PROP_TYPE_COUNT);
	for (int i = PROP_TYPE_COIN; i < PROP_TYPE_COUNT; i++)
	{
		propNum[i] = DateManger::getInstance()->getPlayerPropNum(i);
	}

	// �ؿ���ʼ��ʼ��
	lastMapId = DateManger::getInstance()->getLastMapId();
	for (int i = BIG_GATE_TYPE_BAOXIANGGUO; i < BIG_GATE_TYPE_COUNT; i++)
	{
		mapOpenStatus[i] = DateManger::getInstance()->getGateMapOn(i);
		mapOpenStatus[i] = true;
		mapRole[i] = DateManger::getInstance()->getMapLastRoleId(i);
	}
	starSum = 0;
	for (int i = 0; i < (GATE_ID_MAX-GATE_ID_MIN); i++)
	{
		gateOpenStatus[i] = DateManger::getInstance()->getGateOn(i+1);
		gateOpenStatus[i] = true;
		//if ((i+1)%18 == 10)
		//{
		//	gateOpenStatus[i] = true;
		//}

		if (gateOpenStatus[i])
		{
			maxOpenGateId = i;
		}
		gateLever[i] =DateManger::getInstance()->getGateLever(i+1);
		starSum += gateLever[i];
	}
	maxOpenGateId++;
	lastHideGateDay = DateManger::getInstance()->getHideGateDay();
	for (int i = 0; i < (BIG_GATE_TYPE_COUNT-1);i++)
	{
		for (int j = 0; j < 3; j++)
		{
			hideGateDraw[i*3 + j] = DateManger::getInstance()->getHideGateDraw(i*18 + 10 + j);
		}
	}

	// �����ʼ��
	for (int i = 0; i < ROLE_TYPE_COUNT; i++)
	{
		roleOpenStatus[i] = DateManger::getInstance()->getRoleOn(i);
		roleHavingStatus[i] = DateManger::getInstance()->getRoleHaving(i);
		roleHavingStatus[i] = true;
	}
	currSelectRoleId = DateManger::getInstance()->getPlayerRoleId();
	isOpenNewRole = DateManger::getInstance()->getOpenNewRole();

	// ��������
	musicBackGround = DateManger::getInstance()->getMusicBackGround();
	musicEffect = DateManger::getInstance()->getMusicEffect();
	musicControl = new MusicControl(musicBackGround, musicEffect);
	musicControl->setBackgroundMusicVolume(musicBackGround);
	musicControl->setEffectsVolume(musicEffect);

	// ��սģʽ
	challengeIsOpen = DateManger::getInstance()->getChallengeIsOpen();
	challengeIsOpen = true;
	challengeMaxLevel = DateManger::getInstance()->getChallengeMaxLever();
	challengeUpdate = DateManger::getInstance()->getChallengeUpdate();
	challengeName = DateManger::getInstance()->getChallengeAppendName();
	myRecord.level = DateManger::getInstance()->getChallengeRecordLever();
	myRecord.score = DateManger::getInstance()->getChallengeRecordScore();
	myRecord.name = DateManger::getInstance()->getChallengeRecordName();
	myRecord.roleId = DateManger::getInstance()->getChallengeRecordRoleId();

	// �����ʼ��
	selectPetId = DateManger::getInstance()->getSelectPet();
	for (int i = PET_ELEMENT_XIAOZUANFENG; i < PET_ELEMENT_COUNT; i++)
	{
		petNum[i] = DateManger::getInstance()->getPetElement(i);// ������ǵ�����
		petHeartNum[i] = DateManger::getInstance()->getPetHeart(i);// ������ǵ�����
		petHaving[i] = DateManger::getInstance()->getPetHaving(i);// �����Ƿ�ӵ��
		petHaving[i] = true;// �����Ƿ�ӵ��
		//petHeartNum[i] = Global::getInstance()->getPetHeartFull(i);
		petBorn[i] = DateManger::getInstance()->getPetBorn(i);// �����Ƿ�ӵ��
		petTeach[i] = DateManger::getInstance()->getPetTeach(i);// �����Ƿ�ӵ��
		lastPetDay = DateManger::getInstance()->getPetDay();
	}

	// �������
	isCartoonFrist = DateManger::getInstance()->getCarttonIsFrist();
	isCartoonPlay[0] = DateManger::getInstance()->getCarttonIsPlay(CARTOON_START);
	isCartoonPlay[CARTOON_COUNT - 1] = DateManger::getInstance()->getCarttonIsPlay(CARTOON_END);
	for(int i = CARTOON_BAOXIANGGUO; i <= CARTOON_LINGSHAN; i++)
	{
		isCartoonPlay[i] = DateManger::getInstance()->getCarttonIsPlay(i);
	}

	// �������
	for (int i = 0; i < GUIDE_ID_JEWEIL_SKILL; i++)
	{
		guideAward[i] = DateManger::getInstance()->getIsGetAwardByGuideId(i+1);
	}
	isGuideFrist = DateManger::getInstance()->getGuideIsFrist();
	isSlipBigGate = DateManger::getInstance()->getGuideSlipBigGate();
	isSlipRole = DateManger::getInstance()->getGuideSlipRole();
	isSlipChalleng =  DateManger::getInstance()->getGuideSlipChallenge();
	lastGuideIndex = DateManger::getInstance()->getGuideLastIndex();

	// ��ʾ���
	for (int i = TIP_GAMING_START; i <= TIP_GAMING_END; i++)
	{
		tips[i - TIP_GAMING_START] = DateManger::getInstance()->getTip(i);
	}
	jewelButtonTipCount = JEWEL_BUTTON_COUNT;
	lightTipCount = LIGHT_BUTTON_COUNT;

	// �Ʒ����
	for (int i = PAY_ID_GENUINE-1; i < PAY_ID_MEET; i++)
	{
		pays[i] = DateManger::getInstance()->getPay(i);
	}

	// ǩ�����
	registerDay = DateManger::getInstance()->getRegisterDay();
	registerCount = DateManger::getInstance()->getRegisterCount();

	// ��Ϸlayer
	gameLayer = NULL;
	gameLayerIsPause = false;
}

MusicControl * Player::getMusicControl(void)
{
	return musicControl;
}

char * Player::getImeiStr(void)
{
	return imeiStr;
}

void Player::setImeiStr(char * _str, int _length)
{
	memset(imeiStr, '0', IMEI_LENGTH);
	for (int i = 0; i < _length; i++)
	{
		imeiStr[i] = _str[i];
	}
}

long Player::getImei(void)
{
	return imei;
}

/*************************************************************
	������صĻ���
********************************************************************/
// ���������͵�type��id���һ����
void Player::appendPropNum(int _propType, int _num)
{
	propNum[_propType] += _num; 
	//DateManger::getInstance()->savePlayerPropNum(_propType, propNum[_propType]);
}

int Player::getPropNum(int _propType)
{
	return propNum[_propType];
}

void Player::savePropNum(int _propType, int _num)
{
	// ����û���ò�������num
	DateManger::getInstance()->savePlayerPropNum(_propType, propNum[_propType]);
}

void Player::initPropNumFromDateStoreByType(int _propType)
{
	propNum[_propType] = DateManger::getInstance()->getPlayerPropNum(_propType);
}

void Player::initPropNumFromDateStore(void)
{
	memset(propNum, 0, sizeof(int) * PROP_TYPE_COUNT);
	for (int i = PROP_TYPE_COIN; i < PROP_TYPE_COUNT; i++)
	{
		propNum[i] = DateManger::getInstance()->getPlayerPropNum(i);
	}
}

/*************************************************************
	�ؿ���صĻ���
********************************************************************/
void Player::setLastMapId(int _mapId)
{
#ifndef										GOLDEN_MINER_2_NEW_GUIDE
	if (_mapId > BIG_GATE_TYPE_COUNT || _mapId < 0)
#else
	if (_mapId > BIG_GATE_TYPE_GUIDE || _mapId < 0)
#endif
	{
		CCLOG("GoldenMiner2 Player setLastMapId  _mapId = %d  bigger than %d", _mapId, BIG_GATE_TYPE_COUNT);
		_mapId = BIG_GATE_TYPE_BAOXIANGGUO;
	}
	lastMapId = _mapId;
	DateManger::getInstance()->saveLastMapId(_mapId);
}

int Player::getLastMapId(void)
{
	return lastMapId;
}

bool Player::getMapOpenStatusByMapId(int _mapId)
{
	if (_mapId >= BIG_GATE_TYPE_COUNT || _mapId < 0)
	{
		CCLOG("GoldenMiner2 Player getMapOpenStatusByMapId  _mapId = %d  bigger than %d", _mapId, BIG_GATE_TYPE_COUNT);
		return false;
	}
	return mapOpenStatus[_mapId];
}

void Player::setMapOpenStatusByMapId(int _mapId, bool _isOpen)
{
	if (_mapId >= BIG_GATE_TYPE_COUNT || _mapId < 0)
	{
		CCLOG("GoldenMiner2 Player setMapOpenStatusByMapId  _mapId = %d  bigger than %d", _mapId, BIG_GATE_TYPE_COUNT);
		return;
	}
	mapOpenStatus[_mapId] = _isOpen;
	DateManger::getInstance()->saveGateMapOn(_mapId, _isOpen);
}

bool Player::getGateOpenStatusByGateId(int _gateId)
{
	if (_gateId > 88 || _gateId < 0)
	{
		CCLOG("GoldenMiner2 Player getGateOpenStatusByGateId  _gateId = %d  bigger than 88", _gateId);
		return false;
	}
	return gateOpenStatus[_gateId-1];
}

void Player::setGateOpenStatusByGateId(int _gateId, bool _isOpen)
{
	if (_gateId > 88 || _gateId < 0)
	{
		CCLOG("GoldenMiner2 Player setGateOpenStatusByGateId  _gateId = %d  bigger than 88", _gateId);
		return ;
	}
	gateOpenStatus[_gateId-1] = _isOpen;

	if (_isOpen && (_gateId > maxOpenGateId))
	{
		maxOpenGateId = _gateId;
	}

	DateManger::getInstance()->saveGateOn(_gateId, _isOpen);
}

int Player::getGateLeverStatusByGateId(int _gateId)
{
	return gateLever[_gateId-1];
}

void Player::setGateLeverStatusByGateId(int _gateId, int _lever)
{
	if (gateLever[_gateId-1] >= _lever)
	{
		return;
	}
	starSum += _lever - gateLever[_gateId-1];
	gateLever[_gateId-1] = _lever;
	DateManger::getInstance()->saveGateLever(_gateId, _lever);
}

void Player::setMapLastRoleId(int _mapId, int _roleId)
{
	mapRole[_mapId] = _roleId;
	DateManger::getInstance()->saveMapLastRoleId(_mapId, _roleId);
}

int Player::getMapLastRoleId(int _mapId)
{
	return mapRole[_mapId];
}

int Player::getStarSum(void)
{
	return starSum;
}

int Player::getMaxOpenGateId(void)
{
	return maxOpenGateId;
}

void Player::setHideGateDraw(int _hideGateId, bool _isdraw)
{
	hideGateDraw[_hideGateId/18*3 + _hideGateId%18 - 10] = _isdraw;
	DateManger::getInstance()->saveHideGateDraw(_hideGateId, _isdraw);
}

bool Player::getHideGateDraw(int _hideGateId)
{
	return hideGateDraw[_hideGateId/18*3 + _hideGateId%18 - 10]; 
}

void Player::initHideGateDraw(void)
{
	for (int i = 0; i < (BIG_GATE_TYPE_COUNT-1);i++)
	{
		for (int j = 0; j < 3; j++)
		{
			hideGateDraw[i*3 + j] = true;
			DateManger::getInstance()->saveHideGateDraw(i*3 + 10 + j, true);
		}
	}
}

void Player::setHideGateDay(int _day)
{
	lastHideGateDay = _day;
	DateManger::getInstance()->saveHideGateDay(lastHideGateDay);
}

int Player::getHideGateDay(void)
{
	return lastHideGateDay; 
}
/*************************************************************
	��ս
********************************************************************/
bool Player::getChallengeIsOpen(void)
{
	return challengeIsOpen;
}

void Player::setChallengeIsOpen(bool _isOpeng)
{
	challengeIsOpen = _isOpeng;
	DateManger::getInstance()->saveChallengeIsOpen(challengeIsOpen);
}

bool Player::getChallengeAppendName(void)
{
	return challengeName;
}

void Player::setChallengeAppendName(bool _name)
{
	challengeName = _name;
	DateManger::getInstance()->saveChallengeAppendName(challengeName);
}

bool Player::getChallengeUpdate(void)
{
	return challengeUpdate;
}

void Player::setChallengeUpdate(bool _upDate)
{
	challengeUpdate = _upDate;
	DateManger::getInstance()->saveChallengeUpdate(challengeUpdate);
}

void Player::updateChallenge(ChallengeRecord _record)
{
	if ((myRecord.level == -1) || ((myRecord.score < _record.score) || ((_record.score == myRecord.score) && (myRecord.level < _record.level))))
	{
		myRecord.index = _record.index;
		myRecord.level = _record.level;
		myRecord.roleId = _record.roleId;
		myRecord.name = _record.name;
		myRecord.score = _record.score;
		DateManger::getInstance()->saveChallengeRecordName(myRecord.name);
		DateManger::getInstance()->saveChallengeRecordRoleId(myRecord.roleId);
		DateManger::getInstance()->saveChallengeRecordLever(myRecord.level);
		DateManger::getInstance()->saveChallengeRecordScore(myRecord.score);
		setChallengeUpdate(true);
	}
}

ChallengeRecord Player::getChallengeById(void)
{
	return myRecord;
}


int Player::getChallengeMaxLevel(void)
{
	return challengeMaxLevel;
}

void Player::setChallengeMaxLevel(int _level)
{
	if (_level > challengeMaxLevel)
	{
		challengeMaxLevel = _level;
		DateManger::getInstance()->saveChallengeMaxLever(challengeMaxLevel);
	}
}
//
//int Player::getChallengeNum(void)
//{
//	return challengeNum;
//}
//
//void Player::setChallengeNum(int _num)
//{
//	challengeNum = _num;
//	DateManger::getInstance()->saveChallengeNum(challengeNum);
//}
//
//void Player::addChallenge(ChallengeRecord _record)
//{
//	int exchangeId = -1;
//	bool isfull = true;
//
//	if (challengeNum < CHALLENGE_RECORD_NUM)
//	{
//		isfull = false;
//		setChallengeNum(challengeNum + 1);
//	}
//
//	for (int i = 0 ; i < challengeNum; i++)
//	{
//		if (records[i].score < _record.score)
//		{
//			exchangeId = i;
//			break;
//		}
//		else if (records[i].score == _record.score && records[i].level < _record.level)
//		{
//			exchangeId = i;
//			break;
//		}
//	}
//
//	if (exchangeId != -1)
//	{
//		int i = challengeNum-1;
//		if (!isfull)
//		{
//			i = challengeNum;
//		}
//
//		for (; i > exchangeId; i--)
//		{
//			records[i].level = records[i-1].level;
//			records[i].score = records[i-1].score;
//			records[i].name = records[i-1].name;
//		}
//		records[exchangeId].level = _record.level;
//		records[exchangeId].score = _record.score;
//		records[exchangeId].name = _record.name;
//	}
//}
//
//ChallengeRecord Player::getChallengeById(int _id)
//{
//	return records[_id - 1];
//}

/*************************************************************
	������صĻ���
********************************************************************/
bool Player::getRoleOpenStatusByRoleId(int _roleId)
{
	return roleOpenStatus[_roleId];
}

void Player::setRoleOpenStatusByRoleId(int _roleId, bool _isOpen)
{
	roleOpenStatus[_roleId] = _isOpen;
	DateManger::getInstance()->saveRoleOn(_roleId, _isOpen);
}

bool Player::getRoleHavingStatusByRoleId(int _roleId)
{
	return roleHavingStatus[_roleId];
}

void Player::setRoleHavingStatusByRoleId(int _roleId, bool _isOpen)
{
	roleHavingStatus[_roleId] = _isOpen;
	DateManger::getInstance()->saveRoleHaving(_roleId, _isOpen);
}

int Player::getLastRoleSelect(void)
{
	return currSelectRoleId;
}

void Player::setLastRoleSelect(int _roleId)
{
	currSelectRoleId = _roleId;
	DateManger::getInstance()->savePlayerRoleId(currSelectRoleId);
}

bool Player::getOpenNewRole(void)
{
	return isOpenNewRole;
}

void Player::setOpenNewRole(bool _b)
{
	isOpenNewRole = _b;
	DateManger::getInstance()->saveOpenNewRole(isOpenNewRole);
}
/*************************************************************
	������صĻ���
********************************************************************/
void Player::setMusicBackGround(bool _isOpen)
{
	musicBackGround = _isOpen;// ��������
	musicControl->setBackgroundMusicVolume(_isOpen);
}

bool Player::getMusicBackGround(void)
{
	return musicBackGround;// ��������
}

void Player::setMusicEffect(bool _isOpen)
{
	musicEffect = _isOpen;//��Ч
	musicControl->setEffectsVolume(_isOpen);
}

bool Player::getMusicEffect(void)
{
	return musicEffect;//��Ч
}

void Player::saveMusic(void)
{
	musicControl->setBackGround(musicBackGround);
	musicControl->setEffect(musicEffect);

	DateManger::getInstance()->saveMusicEffect(musicEffect);
	DateManger::getInstance()->saveMusicBackGround(musicBackGround);
}
/*************************************************************
	������صĻ���
********************************************************************/
void Player::setPetTeach(int _petElementId, bool _isHaving)
{
	petTeach[_petElementId] = _isHaving;
	DateManger::getInstance()->savePetTeach(_petElementId, petTeach[_petElementId]);
}

bool Player::getPetTeach(int _petElementId)
{
	return petTeach[_petElementId];// �����Ƿ�ӵ��
}

void Player::setPetDay(int _day)
{
	lastPetDay = _day;
	DateManger::getInstance()->savePetDay(lastPetDay);
}

int Player::getPetDay(void)
{
	return lastPetDay;
}

int Player::getSelectPet(void)
{
	return selectPetId;
}

void Player::setSelectPet(int _id)
{
	selectPetId = _id;
	DateManger::getInstance()->saveSelectPet(selectPetId);
}

void Player::setPetHaving(int _petElementId, bool _isHaving)
{
	petHaving[_petElementId] = _isHaving;
	DateManger::getInstance()->savePetHaving(_petElementId, petHaving[_petElementId]);
}

bool Player::getPetHaving(int _petElementId)
{
	return petHaving[_petElementId];// �����Ƿ�ӵ��
}

void Player::setPetBorn(int _petElementId, bool _isHaving)
{
	petBorn[_petElementId] = _isHaving;
	DateManger::getInstance()->savePetBorn(_petElementId, petBorn[_petElementId]);
}

bool Player::getPetBorn(int _petElementId)
{
	return petBorn[_petElementId];// �����Ƿ�ӵ��
}

void Player::appendPetHeart(int _petElementId, int _num)
{
	petHeartNum[_petElementId] += _num;
	if (petHeartNum[_petElementId] > Global::getInstance()->getPetHeartFull(_petElementId))
	{
		petHeartNum[_petElementId] = Global::getInstance()->getPetHeartFull(_petElementId);
	}
	DateManger::getInstance()->savePetHeart(_petElementId, petHeartNum[_petElementId]);
}

int Player::getPetHeart(int _petElementId)
{
	return petHeartNum[_petElementId];// ������ǵ�����
}

void Player::appendPetElement(int _petElementId, int _num)
{
	petNum[_petElementId] += _num;
	DateManger::getInstance()->savePetElement(_petElementId, petNum[_petElementId]);
}

int Player::getPetElement(int _petElementId)
{
	return petNum[_petElementId];// ������ǵ�����
}
/*************************************************************
	������صĻ���
********************************************************************/
void Player::setCarttonIsFrist(bool _isFrist)
{
	isCartoonFrist = _isFrist;
	DateManger::getInstance()->saveCarttonIsFrist(isCartoonFrist);
}

bool Player::getCarttonIsFrist(void)
{
	return isCartoonFrist;
}

void Player::setCarttonIsPlay(int _cartoonId, bool _isPlay)
{
	if (_cartoonId == CARTOON_START)
	{
		isCartoonPlay[0] = _isPlay;
	}
	else if (_cartoonId == CARTOON_END)
	{
		isCartoonPlay[CARTOON_COUNT - 1] = _isPlay;
	}
	else
	{
		isCartoonPlay[_cartoonId] = _isPlay;
	}
	DateManger::getInstance()->saveCarttonIsPlay(_cartoonId, _isPlay);
}

bool Player::getCarttonIsPlay(int _cartoonId)
{
	if (_cartoonId == CARTOON_START)
	{
		return isCartoonPlay[0];
	}
	else if (_cartoonId == CARTOON_END)
	{
		return isCartoonPlay[CARTOON_COUNT - 1];
	}
	else
	{
		return isCartoonPlay[_cartoonId];
	}
}
/*************************************************************
	������صĻ���
********************************************************************/
void Player::setGuideSlipBigGate(bool _isFrist)
{
	isSlipBigGate = _isFrist;
	DateManger::getInstance()->saveGuideSlipBigGate(isSlipBigGate);
}

bool Player::getGuideSlipBigGate(void)
{
	return isSlipBigGate;
}

void Player::setGuideSlipRole(bool _isFrist)
{
	isSlipRole = _isFrist;
	DateManger::getInstance()->saveGuideSlipRole(isSlipRole);
}

bool Player::getGuideSlipRole(void)
{
	return isSlipRole;
}

void Player::setGuideSlipChallenge(bool _isFrist)
{
	isSlipChalleng = _isFrist;
	DateManger::getInstance()->saveGuideSlipChallenge(isSlipChalleng);
}

bool Player::getGuideSlipChallenge(void)
{
	return isSlipChalleng;
}

void Player::setGuideIsFrist(bool _isFrist)
{
	isGuideFrist = _isFrist;
	DateManger::getInstance()->saveGuideIsFrist(isGuideFrist);
}

bool Player::getGuideIsFrist(void)
{
	return isGuideFrist;
}

void Player::setGuideLastIndex(int _index)
{
	lastGuideIndex = _index;
	DateManger::getInstance()->saveGuideLastIndex(lastGuideIndex);
}

int Player::getGuideLastIndex(void)
{
	return lastGuideIndex;
}

bool Player::getIsGetAwardByGuideId(int _guideId)
{
	return guideAward[_guideId-1];
}

void Player::setIsGetAwardByGuideId(int _guideId, bool _isGet)
{
	guideAward[_guideId - 1] = _isGet;
	DateManger::getInstance()->saveIsGetAwardByGuideId(_guideId, guideAward[_guideId - 1]);
}
/**********************************************************
��ʾ���
***********************************************************/
bool Player::getTip(int _tipId)
{
	return tips[_tipId-TIP_GAMING_START];
}

void Player::setTip(int _tipId, bool _isGet)
{
	tips[_tipId-TIP_GAMING_START] = _isGet;
	DateManger::getInstance()->saveTip(_tipId, tips[_tipId-TIP_GAMING_START]);
}

int Player::getJewelButtonTipCount(void)
{
	return jewelButtonTipCount;
}
void Player::setJewelButtonTipCount(int _count)
{
	jewelButtonTipCount = _count;
}

int Player::getMoonLightTipCount(void)
{
	return lightTipCount;
}

void Player::setMoonLightTipCount(int _count)
{
	lightTipCount = _count;
}
/**********************************************************
�Ʒ����
***********************************************************/
bool Player::getPay(int _payId)
{
	return pays[_payId-1];
}

void Player::setPay(int _payId, bool _isPay)
{
	pays[_payId-1] = _isPay;
	DateManger::getInstance()->saveTip(_payId, pays[_payId-1]);
}
/**********************************************************
��ʾ���
***********************************************************/
void Player::setRegisterDay(int _day)
{
	registerDay = _day;
	DateManger::getInstance()->saveRegisterDay(registerDay);
}

int Player::getRegisterDay(void)
{
	return registerDay;
}

void Player::setRegisterCount(int _count)
{
	registerCount = _count;
	DateManger::getInstance()->saveRegisterCount(registerCount);
}

int Player::getRegisterCount(void)
{
	return registerCount;
}
/**********************************************************
gameLayer ���
***********************************************************/

void Player::setGameLayer(GameControl * _gameLayer)
{
	gameLayer = _gameLayer;
}

void Player::setGameLayerIsPause(bool _isPause)
{
	gameLayerIsPause = _isPause;
}

void Player::gameLayerBackGround(void)
{
	if (gameLayer != NULL && !gameLayerIsPause)
	{
		if (gameLayer->getType() == GAMEING_GUIDE)
		{
			((GuideLayer *)gameLayer)->onMenuItemPauseClicked(NULL);
		}
		else if (gameLayer->getType() == GAMEING_NORMAL)
		{
			((GameControl *)gameLayer)->onMenuItemPauseClicked(NULL);
		}
		else if (gameLayer->getType() == GAMEING_CHALLENGE)
		{
			((ChallengeLayer *)gameLayer)->onMenuItemPauseClicked(NULL);
		}
	}
}