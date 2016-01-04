#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Global.h"
#include "MusicControl.h"

#define							IMEI_LENGTH								50

class GameControl;

class Player
{
public:
	~Player(void);

	static Player * getInstance(void);

	// ���imei��
	long getImei(void);
	char * getImeiStr(void);
	void setImeiStr(char * _str, int _length);

	// �������
	void appendPropNum(int _propType, int _num);
	int getPropNum(int _propType);
	void initPropNumFromDateStoreByType(int _propType);
	void initPropNumFromDateStore(void);
	void savePropNum(int _propType, int _num);
	
	// �ؿ����
	bool getMapOpenStatusByMapId(int _mapId);
	void setMapOpenStatusByMapId(int _mapId, bool _isOpen);
	bool getGateOpenStatusByGateId(int _gateId);
	void setGateOpenStatusByGateId(int _gateId, bool _isOpen);
	int getGateLeverStatusByGateId(int _gateId);
	void setGateLeverStatusByGateId(int _gateId, int _lever);
	void setLastMapId(int _mapId);// ���������Ƿ��ʼ��
	int getLastMapId(void);// ��ȡ�����ǲ��ǳ�ʼ����
	void setMapLastRoleId(int _mapId, int _roleId);// ���õ�ǰ�ؿ�����һ��ѡ����˵�id��
	int getMapLastRoleId(int _mapId);// ��ǰ�ؿ�����һ��ѡ����˵�id��
	int getStarSum(void);
	int getMaxOpenGateId(void);
	void setHideGateDraw(int _hideGateId, bool _isdraw);
	bool getHideGateDraw(int _hideGateId);
	void initHideGateDraw(void);
	void setHideGateDay(int _day);
	int getHideGateDay(void);
	
	// ��ս
	bool getChallengeIsOpen(void);
	void setChallengeIsOpen(bool _isOpeng);
	int getChallengeMaxLevel(void);
	void setChallengeMaxLevel(int _level);
	//int getChallengeNum(void);
	//void setChallengeNum(int _num);
	//void addChallenge(ChallengeRecord _record);
	bool getChallengeAppendName(void);
	void setChallengeAppendName(bool _name);
	bool getChallengeUpdate(void);
	void setChallengeUpdate(bool _upDate);
	void updateChallenge(ChallengeRecord _record);
	ChallengeRecord getChallengeById(void);

	// �������
	bool getRoleOpenStatusByRoleId(int _roleId);
	void setRoleOpenStatusByRoleId(int _roleId, bool _isOpen);
	bool getRoleHavingStatusByRoleId(int _roleId);
	void setRoleHavingStatusByRoleId(int _roleId, bool _isOpen);
	int getLastRoleSelect(void);
	void setLastRoleSelect(int _roleId);
	bool getOpenNewRole(void);
	void setOpenNewRole(bool _b);

	// �������
	MusicControl * getMusicControl(void);
	void setMusicBackGround(bool _isOpen);
	void saveMusic(void);
	bool getMusicBackGround(void);
	void setMusicEffect(bool _isOpen);
	bool getMusicEffect(void);

	// �������
	int getSelectPet(void);// ��õ�ǰһ����ĳ�����
	void setSelectPet(int _id);
	void setPetHaving(int _petElementId, bool _isHaving);// �����Ƿ��Ѿ�����
	bool getPetHaving(int _petElementId);
	void setPetBorn(int _petElementId, bool _isHaving);// �����Ƿ�ȴ���������
	bool getPetBorn(int _petElementId);
	void setPetTeach(int _petElementId, bool _isHaving);// �����Ƿ����
	bool getPetTeach(int _petElementId);
	void setPetDay(int _day);// ��ǰ������ʱ���Ӧ����
	int getPetDay(void);
	void appendPetHeart(int _petElementId, int _num);// ���ĵĿ���
	int getPetHeart(int _petElementId);
	void appendPetElement(int _petElementId, int _num);// ���Ŀ���
	int getPetElement(int _petElementId);
	// �������
	void setCarttonIsFrist(bool _isFrist);// ������Ϸ�Ƿ��ʼ��
	bool getCarttonIsFrist(void);// ��ȡ�ǲ��ǳ�ʼ����
	void setCarttonIsPlay(int _cartoonId, bool _isPlay);// ���������Ƿ��Ѿ����Ź�
	bool getCarttonIsPlay(int _cartoonId);// ��ȡ�ǲ����Ѿ����Ź�����
	// �������
	void setGuideSlipBigGate(bool _isFrist);// ����ѡ���������
	bool getGuideSlipBigGate(void);// ��ȡѡ���������
	void setGuideSlipRole(bool _isFrist);// ����ѡ�˲�������
	bool getGuideSlipRole(void);// ��ȡѡren��������
	void setGuideSlipChallenge(bool _isFrist);// ������ս��������
	bool getGuideSlipChallenge(void);// ��ȡ��ս��������
	void setGuideIsFrist(bool _isFrist);// ���������Ƿ��ʼ��
	bool getGuideIsFrist(void);// ��ȡ�����ǲ��ǳ�ʼ����
	void setGuideLastIndex(int _index);// ������������һ�εط�
	int getGuideLastIndex(void);// ��ȡ��������һ�εط�
	bool getIsGetAwardByGuideId(int _guideId);
	void setIsGetAwardByGuideId(int _guideId, bool _isGet);
	// ��ʾ���
	bool getTip(int _tipId);
	void setTip(int _tipId, bool _isGet);
	int getJewelButtonTipCount(void);
	void setJewelButtonTipCount(int _count);
	int getMoonLightTipCount(void);
	void setMoonLightTipCount(int _count);
	// �Ʒ����
	bool getPay(int _payId);
	void setPay(int _payId, bool _isPay);
	// ��½���
	void setRegisterDay(int _day);
	int getRegisterDay(void);
	void setRegisterCount(int _count);
	int getRegisterCount(void);

	// ���õ�ǰ�Ƿ�����Ϸ״̬  ����Ϸ״̬����Ϸlayer��ָ��
	void setGameLayer(GameControl * _gameLayer);
	void gameLayerBackGround(void);
	void setGameLayerIsPause(bool _isPause);
private:
	GameControl * gameLayer;// ��Ϸlayer��ָ��
	bool gameLayerIsPause;// ��Ϸ�Ƿ�����ͣ״̬

	Player(void); 
	static Player * player;

	long imei;
	char imeiStr[IMEI_LENGTH];

	MusicControl * musicControl;

	int petNum[PET_ELEMENT_COUNT];// ������ǵ�����
	int petHeartNum[PET_ELEMENT_COUNT];// ������ǵ�����
	bool petHaving[PET_ELEMENT_COUNT];// �����Ƿ�ӵ��
	bool petBorn[PET_ELEMENT_COUNT];// ���������״̬
	bool petTeach[PET_ELEMENT_COUNT];// �����Ƿ�ӵ��
	int lastPetDay;
	int selectPetId;

	int propNum[PROP_TYPE_COUNT];// ���ߵĸ���
	bool mapOpenStatus[BIG_GATE_TYPE_COUNT];// ��ͼ������״̬
	bool gateOpenStatus[GATE_ID_MAX - GATE_ID_MIN];//�ؿ�������״̬
	int gateLever[GATE_ID_MAX - GATE_ID_MIN];// �ؿ������ǵȼ�
	int starSum;// ���йؿ�������������
	int maxOpenGateId;
	int mapRole[BIG_GATE_TYPE_COUNT];// �ؿ������ǵȼ�
	int lastMapId;// �Ƿ��ǵ�һ������
	int lastHideGateDay;
	bool hideGateDraw[3*(BIG_GATE_TYPE_COUNT-1)];

	bool roleOpenStatus[ROLE_TYPE_COUNT];
	bool roleHavingStatus[ROLE_TYPE_COUNT];
	int currSelectRoleId;
	bool isOpenNewRole;

	bool musicBackGround;// ��������
	bool musicEffect;//��Ч

	bool isCartoonFrist;// �Ƿ��ǵ�һ�ν�����ϷҪ���ſ�ͨ
	bool isCartoonPlay[CARTOON_COUNT];// �Ƿ��ǵ�һ�ν�����ϷҪ���ſ�ͨ

	bool isGuideFrist;// �Ƿ��ǵ�һ������
	bool isSlipBigGate;
	bool isSlipRole;
	bool isSlipChalleng;
	int lastGuideIndex;// ��һ�ε�����
	bool guideAward[GUIDE_ID_JEWEIL_SKILL];// ��������

	bool tips[TIP_GAMING_END - TIP_GAMING_START + 1];
	int jewelButtonTipCount;
	int lightTipCount;
	bool pays[6];

	//ChallengeRecord records[CHALLENGE_RECORD_NUM];
	//int challengeNum;
	bool challengeIsOpen;
	bool challengeName;
	bool challengeUpdate;
	ChallengeRecord myRecord;
	int challengeMaxLevel;

	int registerDay;// �ϴ�ǩ����ʱ��
	int registerCount;// ����ǩ��������

	void init(void);
};

#endif

