#ifndef __DATEMANGER_H__
#define __DATEMANGER_H__

#include "cocos2d.h"
#include "Global.h"

class DateManger
{
public:
	~DateManger(void);
	static DateManger * getInstance(void);

	// Gate ���
	void saveGateMapOn(int _gateMapId, bool _on);// ���¶�Ӧ�ؿ�map�Ƿ���
	bool getGateMapOn(int _gateMapId); // �����Ҷ�Ӧ�ؿ���map�Ƿ���
	void saveGateOn(int _gateId, bool _on);// ������Ҷ�Ӧ�ؿ��Ƿ���
	bool getGateOn(int _gateId);// �����Ҷ�Ӧ�ؿ��Ƿ��ܹ�����
	void saveGateLever(int _gateId, int _lever);// ������Ҷ�Ӧ�ؿ���ͨ�صȼ�
	int getGateLever(int _gateId);// �����Ҷ�Ӧ�ؿ���ͨ�صȼ�
	void saveLastMapId(int _gateId);// ���������Ƿ��ʼ��
	int getLastMapId(void);// ��ȡ�����ǲ��ǳ�ʼ����
	void saveMapLastRoleId(int _gateId, int _roleId);// ���õ�ǰ�ؿ�����һ��ѡ����˵�id��
	int getMapLastRoleId(int _gateId);// ��ǰ�ؿ�����һ��ѡ����˵�id��
	void saveHideGateDraw(int _hideGateId, bool _isdraw);
	bool getHideGateDraw(int _hideGateId);
	void saveHideGateDay(int _day);
	int getHideGateDay(void);

	// ��սģʽ���
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

	// rloe ���
	void saveRoleOn(int _roleId, bool _on);// ������Ҷ�Ӧ��ɫ�Ƿ���
	bool getRoleOn(int _roleId);// �����Ҷ�Ӧ��ɫ�Ƿ��ܹ�����
	bool getRoleHaving(int _roleId);
	void saveRoleHaving(int _roleId, bool _isOpen);

	// PLayer ���
	void savePlayerRoleId(int _roleId);// �������ѡ���ɫ��id
	int getPlayerRoleId(void);// ������ѡ���ɫ��id
	void savePlayerPropNum(int _propId, int _num);// �������ӵ�ж�Ӧ����id������
	int getPlayerPropNum(int _propId);// ������ӵ�ж�Ӧ����id������
	bool getOpenNewRole(void);
	void saveOpenNewRole(bool _b);


	// Music���
	void saveMusicBackGround(bool _isOpen);
	bool getMusicBackGround(void);
	void saveMusicEffect(bool _isOpen);
	bool getMusicEffect(void);

	// �������
	int getSelectPet(void);// ��õ�ǰһ����ĳ�����
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

	// �������
	void saveCarttonIsFrist(bool _isFrist);// ������Ϸ�Ƿ��ʼ��
	bool getCarttonIsFrist(void);// ��ȡ�ǲ��ǳ�ʼ����
	void saveCarttonIsPlay(int _cartoonId, bool _isPlay);// ���������Ƿ��Ѿ����Ź�
	bool getCarttonIsPlay(int _cartoonId);// ��ȡ�ǲ����Ѿ����Ź�����

	// �������
	void saveGuideSlipBigGate(bool _isFrist);// ����ѡ���������
	bool getGuideSlipBigGate(void);// ��ȡѡ���������
	void saveGuideSlipRole(bool _isFrist);// ����ѡ�˲�������
	bool getGuideSlipRole(void);// ��ȡѡren��������
	void saveGuideSlipChallenge(bool _isFrist);// ������ս��������
	bool getGuideSlipChallenge(void);// ��ȡ��ս��������
	void saveGuideIsFrist(bool _isFrist);// ���������Ƿ��ʼ��
	bool getGuideIsFrist(void);// ��ȡ�����ǲ��ǳ�ʼ����
	void saveGuideLastIndex(int _index);// ������������һ�εط�
	int getGuideLastIndex(void);// ��ȡ��������һ�εط�
	bool getIsGetAwardByGuideId(int _guideId);
	void saveIsGetAwardByGuideId(int _guideId, bool _isGet);

	// ��ʾ���
	void saveTip(int _tipId, bool _num);
	bool getTip(int _tipId);

	// �Ʒ�
	void savePay(int _payId, bool _isPay);
	bool getPay(int _payId);

	// ��½���
	void saveRegisterDay(int _day);
	int getRegisterDay(void);
	void saveRegisterCount(int _count);
	int getRegisterCount(void);
private:
	DateManger(void);

	void saveGoldenMiner2IsInit(bool _isFrist);// ������Ϸ�Ƿ��ʼ��
	bool getGoldenMiner2IsInit(void);// ��ȡ�ǲ��ǳ�ʼ����

	void initDate(void);// ��ʼ���浵����

	char _s[128];
	static DateManger * dateManger;
};

#endif