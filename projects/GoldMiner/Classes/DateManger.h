#ifndef __DATEMANGER_H__
#define __DATEMANGER_H__

#include "cocos2d.h"
#include "Global.h"

class DateManger
{
public:
	~DateManger(void);
	static DateManger * getInstance(void);

	// Gate 相关
	void saveGateMapOn(int _gateMapId, bool _on);// 更新对应关卡map是否开启
	bool getGateMapOn(int _gateMapId); // 获得玩家对应关卡的map是否开启
	void saveGateOn(int _gateId, bool _on);// 更新玩家对应关卡是否开启
	bool getGateOn(int _gateId);// 获得玩家对应关卡是否能够开启
	void saveGateLever(int _gateId, int _lever);// 更新玩家对应关卡的通关等级
	int getGateLever(int _gateId);// 获得玩家对应关卡的通关等级
	void saveLastMapId(int _gateId);// 更新引导是否初始化
	int getLastMapId(void);// 获取引导是不是初始化过
	void saveMapLastRoleId(int _gateId, int _roleId);// 设置当前关卡的上一次选择的人的id号
	int getMapLastRoleId(int _gateId);// 当前关卡的上一次选择的人的id号
	void saveHideGateDraw(int _hideGateId, bool _isdraw);
	bool getHideGateDraw(int _hideGateId);
	void saveHideGateDay(int _day);
	int getHideGateDay(void);

	// 挑战模式相关
	bool getChallengeIsOpen(void);
	void saveChallengeIsOpen(bool _isOpeng);

	bool getChallengeAppendName(void);
	void saveChallengeAppendName(bool _name);
	bool getChallengeUpdate(void);
	void saveChallengeUpdate(bool _isDate);
	int getChallengeRecordRoleId();
	void saveChallengeRecordRoleId(int _roleId);
	int getChallengeRecordLever();
	void saveChallengeRecordLever(int _level);
	int getChallengeRecordScore();
	void saveChallengeRecordScore(int _score);
	std::string getChallengeRecordName();
	void saveChallengeRecordName(std::string _str);
	int getChallengeMaxLever(void);
	void saveChallengeMaxLever(int _level);
	//int getChallengeNum(void);
	//void saveChallengeNum(int _num);
	//int getChallengeRecordLever(int _id);
	//void saveChallengeRecordLever(int _id, int _level);
	//int getChallengeRecordScore(int _id);
	//void saveChallengeRecordScore(int _id, int _score);
	//std::string getChallengeRecordName(int _id);
	//void saveChallengeRecordName(int _id, std::string _str);

	// rloe 相关
	void saveRoleOn(int _roleId, bool _on);// 更新玩家对应角色是否开启
	bool getRoleOn(int _roleId);// 获得玩家对应角色是否能够开启
	bool getRoleHaving(int _roleId);
	void saveRoleHaving(int _roleId, bool _isOpen);

	// PLayer 相关
	void savePlayerRoleId(int _roleId);// 更新玩家选择角色的id
	int getPlayerRoleId(void);// 获得玩家选择角色的id
	void savePlayerPropNum(int _propId, int _num);// 更新玩家拥有对应道具id的数量
	int getPlayerPropNum(int _propId);// 获得玩家拥有对应道具id的数量
	bool getOpenNewRole(void);
	void saveOpenNewRole(bool _b);


	// Music相关
	void saveMusicBackGround(bool _isOpen);
	bool getMusicBackGround(void);
	void saveMusicEffect(bool _isOpen);
	bool getMusicEffect(void);

	// 宠物相关
	int getSelectPet(void);// 获得当前一助阵的宠物编号
	void saveSelectPet(int _id);
	void savePetTeach(int _petElementId, bool _isHaving);
	bool getPetTeach(int _petElementId);
	void savePetDay(int _day);
	int getPetDay(void);
	void savePetHaving(int _petElementId, bool _isHaving);
	bool getPetHaving(int _petElementId);
	void savePetBorn(int _petElementId, bool _isHaving);
	bool getPetBorn(int _petElementId);
	void savePetElement(int _petElementId, int _num);
	int getPetElement(int _petElementId);
	void savePetHeart(int _petElementId, int _num);
	int getPetHeart(int _petElementId);

	// 漫画相关
	void saveCarttonIsFrist(bool _isFrist);// 更新游戏是否初始化
	bool getCarttonIsFrist(void);// 获取是不是初始化过
	void saveCarttonIsPlay(int _cartoonId, bool _isPlay);// 更新漫画是否已经播放过
	bool getCarttonIsPlay(int _cartoonId);// 获取是不是已经播放过漫画

	// 引导相关
	void saveGuideSlipBigGate(bool _isFrist);// 更新选大操作引导
	bool getGuideSlipBigGate(void);// 获取选大操作引导
	void saveGuideSlipRole(bool _isFrist);// 更新选人操作引导
	bool getGuideSlipRole(void);// 获取选ren操作引导
	void saveGuideSlipChallenge(bool _isFrist);// 更新挑战操作引导
	bool getGuideSlipChallenge(void);// 获取挑战操作引导
	void saveGuideIsFrist(bool _isFrist);// 更新引导是否初始化
	bool getGuideIsFrist(void);// 获取引导是不是初始化过
	void saveGuideLastIndex(int _index);// 设置引导的上一次地方
	int getGuideLastIndex(void);// 获取引导的上一次地方
	bool getIsGetAwardByGuideId(int _guideId);
	void saveIsGetAwardByGuideId(int _guideId, bool _isGet);

	// 提示相关
	void saveTip(int _tipId, bool _num);
	bool getTip(int _tipId);

	// 计费
	void savePay(int _payId, bool _isPay);
	bool getPay(int _payId);

	// 登陆相关
	void saveRegisterDay(int _day);
	int getRegisterDay(void);
	void saveRegisterCount(int _count);
	int getRegisterCount(void);
private:
	DateManger(void);

	void saveGoldenMiner2IsInit(bool _isFrist);// 更新游戏是否初始化
	bool getGoldenMiner2IsInit(void);// 获取是不是初始化过

	void initDate(void);// 初始化存档内容

	char _s[128];
	static DateManger * dateManger;
};

#endif