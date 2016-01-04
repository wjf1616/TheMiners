#ifndef __ROLE_H__
#define __ROLE_H__

#include "cocos2d.h"
#include "Hanger.h"
#include "Rope.h"
#include "CSArmature.h"
#include "CSArmatureDataManager.h"
#include "Global.h"
#include "Sensitization.h"
#include "ExchangeHangerEffect.h"

class GameControl;
class Alignment;
class JewelSkillGourd;

enum
{
	 ROLE_STATUS_NORMARL,// վ��
	 ROLE_STATUS_THROW,// ������
	 ROLE_STATUS_PULL_HAVING,// ������(����������)
	 ROLE_STATUS_PULL_UNHAVING,// ������(û����������)
	 ROLE_STATUS_GETTHING,// ��������
	 ROLE_STATUS_GETNOTHING,// û����������
	 ROLE_STATUS_FAIL,// ͨ��ʧ��
	 ROLE_STATUS_WIN,// ͨ�سɹ�
	 ROlE_STATUS_CARTOON// ����״̬
};

enum
{
	ROLE_SKILL_STATUS_CANSKILL,// ���ͷż��ܵ�״̬
	ROLE_SKILL_STATUS_SKILLING,// �ͷż�����
	ROLE_SKILL_STATUS_COOLING,// ������ȴ״̬
};


class Role :
	public cocos2d::CCNode
{
public:
	~Role(void);
	static Role * getInstance(int _type, GameControl * _gameControl, double _x, double _y, double _centreX, double _centreY, double _scale);

	virtual void doAction(float _f, GameControl * _gameControl);
	virtual void doActionSkill(float _f, GameControl * _gameControl);
	Hanger * getHanger(void);// ��õĵ�ǰ�ж����ݵĹ���ָ��
	cs::Armature* getArmature(void);
	void setStatus(int _status);
	void setSkillStatus(int _status);
	int getSkillStatus(void);
	int getType(void);
	void setSkillVisible(bool _b);
	void setIsHaveAlignment(bool _b);
	bool getIsHaveAlignment(void);
	Alignment * getAlignment(void);
	virtual void throwHanger(GameControl * _gameControl);
	virtual bool canDoExplosive(void);
	virtual void doExplosive(GameControl * _gameControl);
	virtual void releaseExplosive(GameControl * _gameControl);
	virtual void appendHangerSpeed(int _speed);

	virtual void doJewelSkill(void);
	virtual void releaseJewelSkill(void);
	virtual void doSkill(GameControl *gameControl);
	virtual void releaseSkill(GameControl *gameControl);

#ifdef						GOLDEN_MINER2_FLASH_FRAME
	cocos2d::CCSprite * gunLun;
#endif
	cocos2d::CCSprite * roleHide;

protected:
	Role(void);

	void initSelf(double _x, double _y, double _centreX, double _centreY, double _scale);
	virtual void initSkill(int _skillTime, int _skillTimeLeft, int _skillStatus);

	void setArmature(cs::Armature* _armature);

	Hanger * hanger;//����ָ��
	Alignment * alignment;// ��׼��
	bool isHaveAlignment;
	ExchangeHangerEffect * exchangeHangerEffect;

	//int skillCountTmp;

	int skillTime;// ���ܳ�����ʱ��
	//cocos2d::CCSprite * hangerSkill;//����ָ��
#ifdef							GOLDEN_MINER_2_VERSION_TIME
	float skillTimeCount;// ����ʣ�µ�ʱ��
	float skillTimeLeftCount;// ������ȴʣ�µ�ʱ��
#else
	int skillTimeCount;// ����ʣ�µ�ʱ��
	int skillTimeLeftCount;// ������ȴʣ�µ�ʱ��
#endif
	int skillTimeLeft;// ������ȴʱ��
#ifdef							GOLDEN_MINER_2_VERSION_TIME
	float happyTimeCount;
#else
	int happyTimeCount;
#endif
	int skillStatus;// ����״̬
	// Ԥ��cocosbuilder�Ķ�������
	Sensitization * liuGuang;// ���ܵ�����

	int type;//��Ӧ��Role��id��
	int status;// ��������״̬
	cs::Armature * armature;
	cocos2d::CCSprite * skillSprite;
	cocos2d::CCSprite * skillSprite2;

};

class Tangseng:
	public Role
{
public:
	virtual void doAction(float _f, GameControl * _gameControl);
	virtual void doActionSkill(float _f, GameControl * _gameControl);
	virtual void doSkill(GameControl *gameControl);
	virtual void releaseSkill(GameControl *gameControl);
	virtual void initSkill(int _skillTime, int _skillTimeLeft, int _skillStatus);
	virtual void throwHanger(GameControl * _gameControl);
	virtual bool canDoExplosive(void);
	virtual void doExplosive(GameControl * _gameControl);
	virtual void releaseExplosive(GameControl * _gameControl);
	virtual void appendHangerSpeed(int _speed);
	virtual void doJewelSkill(void);
	virtual void releaseJewelSkill(void);

protected:
};

class Sunwukong:
	public Role
{
public:
	virtual void doAction(float _f, GameControl * _gameControl);
	virtual void doActionSkill(float _f, GameControl * _gameControl);
	virtual void doSkill(GameControl *gameControl);
	virtual void releaseSkill(GameControl *gameControl);
	virtual void initSkill(int _skillTime, int _skillTimeLeft, int _skillStatus);
	virtual void throwHanger(GameControl * _gameControl);
	virtual bool canDoExplosive(void);
	virtual void doExplosive(GameControl * _gameControl);
	virtual void releaseExplosive(GameControl * _gameControl);
	virtual void appendHangerSpeed(int _speed);
	virtual void doJewelSkill(void);
	virtual void releaseJewelSkill(void);

private:
	CCLayer * bingLayer;
};

class Zhubajie:
	public Role
{
public:
	virtual void doAction(float _f, GameControl * _gameControl);
	virtual void doActionSkill(float _f, GameControl * _gameControl);
	virtual void doSkill(GameControl *gameControl);
	virtual void releaseSkill(GameControl *gameControl);
	virtual void initSkill(int _skillTime, int _skillTimeLeft, int _skillStatus);
	virtual void throwHanger(GameControl * _gameControl);
	virtual bool canDoExplosive(void);
	virtual void doExplosive(GameControl * _gameControl);
	virtual void releaseExplosive(GameControl * _gameControl);
	virtual void appendHangerSpeed(int _speed);
	virtual void doJewelSkill(void);
	virtual void releaseJewelSkill(void);

protected:

private:
	// �����ͼ
	bool isSkillThrow;
	bool isWite;
};

class Shaheshang:
	public Role
{
public:
	virtual void doAction(float _f, GameControl * _gameControl);
	virtual void doActionSkill(float _f, GameControl * _gameControl);
	virtual void doSkill(GameControl *gameControl);
	virtual void releaseSkill(GameControl *gameControl);
	virtual void initSkill(int _skillTime, int _skillTimeLeft, int _skillStatus);
	virtual void throwHanger(GameControl * _gameControl);
	virtual bool canDoExplosive(void);
	virtual void doExplosive(GameControl * _gameControl);
	virtual void releaseExplosive(GameControl * _gameControl);
	virtual void appendHangerSpeed(int _speed);
	virtual void doJewelSkill(void);
	virtual void releaseJewelSkill(void);

protected:
	//cocos2d::CCSprite *	biaozhunxian;
	//cocos2d::CCSprite *	buybiaozhunxian;

	//void changeMiaoZhunXianPosition(void);
};

class Xiaolongnv:
	public Role
{
public:
	virtual void doAction(float _f, GameControl * _gameControl);
	virtual void doActionSkill(float _f, GameControl * _gameControl);
	virtual void doSkill(GameControl *gameControl);
	virtual void releaseSkill(GameControl *gameControl);
	virtual void initSkill(int _skillTime, int _skillTimeLeft, int _skillStatus);
	virtual void throwHanger(GameControl * _gameControl);
	virtual bool canDoExplosive(void);
	virtual void doExplosive(GameControl * _gameControl);
	virtual void releaseExplosive(GameControl * _gameControl);
	virtual void appendHangerSpeed(int _speed);
	virtual void doJewelSkill(void);
	virtual void releaseJewelSkill(void);

protected:
};

class HuLuWa:
	public Role
{
public:
	HuLuWa(void);
	~HuLuWa(void);

	virtual void doAction(float _f, GameControl * _gameControl);
	virtual void doActionSkill(float _f, GameControl * _gameControl);
	virtual void doSkill(GameControl *gameControl);
	virtual void releaseSkill(GameControl *gameControl);
	virtual void initSkill(int _skillTime, int _skillTimeLeft, int _skillStatus);
	virtual void throwHanger(GameControl * _gameControl);
	virtual bool canDoExplosive(void);
	virtual void doExplosive(GameControl * _gameControl);
	virtual void releaseExplosive(GameControl * _gameControl);
	virtual void appendHangerSpeed(int _speed);
	virtual void doJewelSkill(void);
	virtual void releaseJewelSkill(void);

	Hanger * initHangers(GameControl * _gameControl);
private:
	Hanger * hangerIce;
	Hanger * hangerFire;
	bool isIce;
	bool isExchange;
	JewelSkillGourd * jewelSkillSprite;
	// �����ͼ
	bool isSkillThrow;
	bool doJewel;
	bool releaseJewel;
};

#endif