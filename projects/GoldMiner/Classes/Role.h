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
	 ROLE_STATUS_NORMARL,// 站立
	 ROLE_STATUS_THROW,// 放绳子
	 ROLE_STATUS_PULL_HAVING,// 拉绳子(有拉到东西)
	 ROLE_STATUS_PULL_UNHAVING,// 拉绳子(没有拉到东西)
	 ROLE_STATUS_GETTHING,// 拉到东西
	 ROLE_STATUS_GETNOTHING,// 没有拉到东西
	 ROLE_STATUS_FAIL,// 通关失败
	 ROLE_STATUS_WIN,// 通关成功
	 ROlE_STATUS_CARTOON// 动画状态
};

enum
{
	ROLE_SKILL_STATUS_CANSKILL,// 能释放技能的状态
	ROLE_SKILL_STATUS_SKILLING,// 释放技能中
	ROLE_SKILL_STATUS_COOLING,// 技能冷却状态
};


class Role :
	public cocos2d::CCNode
{
public:
	~Role(void);
	static Role * getInstance(int _type, GameControl * _gameControl, double _x, double _y, double _centreX, double _centreY, double _scale);

	virtual void doAction(float _f, GameControl * _gameControl);
	virtual void doActionSkill(float _f, GameControl * _gameControl);
	Hanger * getHanger(void);// 获得的当前判定依据的钩子指针
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

	Hanger * hanger;//钩子指针
	Alignment * alignment;// 瞄准线
	bool isHaveAlignment;
	ExchangeHangerEffect * exchangeHangerEffect;

	//int skillCountTmp;

	int skillTime;// 技能持续的时间
	//cocos2d::CCSprite * hangerSkill;//钩子指针
#ifdef							GOLDEN_MINER_2_VERSION_TIME
	float skillTimeCount;// 技能剩下的时间
	float skillTimeLeftCount;// 技能冷却剩下的时间
#else
	int skillTimeCount;// 技能剩下的时间
	int skillTimeLeftCount;// 技能冷却剩下的时间
#endif
	int skillTimeLeft;// 技能冷却时间
#ifdef							GOLDEN_MINER_2_VERSION_TIME
	float happyTimeCount;
#else
	int happyTimeCount;
#endif
	int skillStatus;// 技能状态
	// 预留cocosbuilder的动画处理
	Sensitization * liuGuang;// 技能的流光

	int type;//对应的Role的id号
	int status;// 任务整体状态
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
	// 激光的图
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
	// 激光的图
	bool isSkillThrow;
	bool doJewel;
	bool releaseJewel;
};

#endif