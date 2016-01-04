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

	// 获得imei号
	long getImei(void);
	char * getImeiStr(void);
	void setImeiStr(char * _str, int _length);

	// 道具相关
	void appendPropNum(int _propType, int _num);
	int getPropNum(int _propType);
	void initPropNumFromDateStoreByType(int _propType);
	void initPropNumFromDateStore(void);
	void savePropNum(int _propType, int _num);
	
	// 关卡相关
	bool getMapOpenStatusByMapId(int _mapId);
	void setMapOpenStatusByMapId(int _mapId, bool _isOpen);
	bool getGateOpenStatusByGateId(int _gateId);
	void setGateOpenStatusByGateId(int _gateId, bool _isOpen);
	int getGateLeverStatusByGateId(int _gateId);
	void setGateLeverStatusByGateId(int _gateId, int _lever);
	void setLastMapId(int _mapId);// 更新引导是否初始化
	int getLastMapId(void);// 获取引导是不是初始化过
	void setMapLastRoleId(int _mapId, int _roleId);// 设置当前关卡的上一次选择的人的id号
	int getMapLastRoleId(int _mapId);// 当前关卡的上一次选择的人的id号
	int getStarSum(void);
	int getMaxOpenGateId(void);
	void setHideGateDraw(int _hideGateId, bool _isdraw);
	bool getHideGateDraw(int _hideGateId);
	void initHideGateDraw(void);
	void setHideGateDay(int _day);
	int getHideGateDay(void);
	
	// 挑战
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

	// 人物相关
	bool getRoleOpenStatusByRoleId(int _roleId);
	void setRoleOpenStatusByRoleId(int _roleId, bool _isOpen);
	bool getRoleHavingStatusByRoleId(int _roleId);
	void setRoleHavingStatusByRoleId(int _roleId, bool _isOpen);
	int getLastRoleSelect(void);
	void setLastRoleSelect(int _roleId);
	bool getOpenNewRole(void);
	void setOpenNewRole(bool _b);

	// 音乐相关
	MusicControl * getMusicControl(void);
	void setMusicBackGround(bool _isOpen);
	void saveMusic(void);
	bool getMusicBackGround(void);
	void setMusicEffect(bool _isOpen);
	bool getMusicEffect(void);

	// 宠物相关
	int getSelectPet(void);// 获得当前一助阵的宠物编号
	void setSelectPet(int _id);
	void setPetHaving(int _petElementId, bool _isHaving);// 宠物是否已经养成
	bool getPetHaving(int _petElementId);
	void setPetBorn(int _petElementId, bool _isHaving);// 宠物是否等待出生动作
	bool getPetBorn(int _petElementId);
	void setPetTeach(int _petElementId, bool _isHaving);// 宠物是否教育
	bool getPetTeach(int _petElementId);
	void setPetDay(int _day);// 当前教育的时间对应日期
	int getPetDay(void);
	void appendPetHeart(int _petElementId, int _num);// 爱心的控制
	int getPetHeart(int _petElementId);
	void appendPetElement(int _petElementId, int _num);// 灵魂的控制
	int getPetElement(int _petElementId);
	// 漫画相关
	void setCarttonIsFrist(bool _isFrist);// 更新游戏是否初始化
	bool getCarttonIsFrist(void);// 获取是不是初始化过
	void setCarttonIsPlay(int _cartoonId, bool _isPlay);// 更新漫画是否已经播放过
	bool getCarttonIsPlay(int _cartoonId);// 获取是不是已经播放过漫画
	// 引导相关
	void setGuideSlipBigGate(bool _isFrist);// 更新选大操作引导
	bool getGuideSlipBigGate(void);// 获取选大操作引导
	void setGuideSlipRole(bool _isFrist);// 更新选人操作引导
	bool getGuideSlipRole(void);// 获取选ren操作引导
	void setGuideSlipChallenge(bool _isFrist);// 更新挑战操作引导
	bool getGuideSlipChallenge(void);// 获取挑战操作引导
	void setGuideIsFrist(bool _isFrist);// 更新引导是否初始化
	bool getGuideIsFrist(void);// 获取引导是不是初始化过
	void setGuideLastIndex(int _index);// 设置引导的上一次地方
	int getGuideLastIndex(void);// 获取引导的上一次地方
	bool getIsGetAwardByGuideId(int _guideId);
	void setIsGetAwardByGuideId(int _guideId, bool _isGet);
	// 提示相关
	bool getTip(int _tipId);
	void setTip(int _tipId, bool _isGet);
	int getJewelButtonTipCount(void);
	void setJewelButtonTipCount(int _count);
	int getMoonLightTipCount(void);
	void setMoonLightTipCount(int _count);
	// 计费相关
	bool getPay(int _payId);
	void setPay(int _payId, bool _isPay);
	// 登陆相关
	void setRegisterDay(int _day);
	int getRegisterDay(void);
	void setRegisterCount(int _count);
	int getRegisterCount(void);

	// 设置当前是否在游戏状态  是游戏状态的游戏layer的指针
	void setGameLayer(GameControl * _gameLayer);
	void gameLayerBackGround(void);
	void setGameLayerIsPause(bool _isPause);
private:
	GameControl * gameLayer;// 游戏layer的指针
	bool gameLayerIsPause;// 游戏是否处于暂停状态

	Player(void); 
	static Player * player;

	long imei;
	char imeiStr[IMEI_LENGTH];

	MusicControl * musicControl;

	int petNum[PET_ELEMENT_COUNT];// 宠物魂魄的数量
	int petHeartNum[PET_ELEMENT_COUNT];// 宠物魂魄的数量
	bool petHaving[PET_ELEMENT_COUNT];// 宠物是否拥有
	bool petBorn[PET_ELEMENT_COUNT];// 宠物待开启状态
	bool petTeach[PET_ELEMENT_COUNT];// 宠物是否拥有
	int lastPetDay;
	int selectPetId;

	int propNum[PROP_TYPE_COUNT];// 道具的个数
	bool mapOpenStatus[BIG_GATE_TYPE_COUNT];// 地图开启的状态
	bool gateOpenStatus[GATE_ID_MAX - GATE_ID_MIN];//关卡开启的状态
	int gateLever[GATE_ID_MAX - GATE_ID_MIN];// 关卡的星星等级
	int starSum;// 所有关卡的星星数量和
	int maxOpenGateId;
	int mapRole[BIG_GATE_TYPE_COUNT];// 关卡的星星等级
	int lastMapId;// 是否是第一次引导
	int lastHideGateDay;
	bool hideGateDraw[3*(BIG_GATE_TYPE_COUNT-1)];

	bool roleOpenStatus[ROLE_TYPE_COUNT];
	bool roleHavingStatus[ROLE_TYPE_COUNT];
	int currSelectRoleId;
	bool isOpenNewRole;

	bool musicBackGround;// 背景音乐
	bool musicEffect;//音效

	bool isCartoonFrist;// 是否是第一次进入游戏要播放卡通
	bool isCartoonPlay[CARTOON_COUNT];// 是否是第一次进入游戏要播放卡通

	bool isGuideFrist;// 是否是第一次引导
	bool isSlipBigGate;
	bool isSlipRole;
	bool isSlipChalleng;
	int lastGuideIndex;// 上一次的引导
	bool guideAward[GUIDE_ID_JEWEIL_SKILL];// 引导奖励

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

	int registerDay;// 上次签到的时间
	int registerCount;// 连续签到的天数

	void init(void);
};

#endif

