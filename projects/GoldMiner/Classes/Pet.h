#ifndef __PET_H__
#define __PET_H__

#include "cocos2d.h"
#include "CSArmature/CSArmature.h"
#include "CSArmature/utils/CSArmatureDataManager.h"

using namespace cocos2d;

enum
{
	PET_LIFE_STATUS_EGG,// 蛋
	PET_LIFE_STATUS_BABY,// 宝宝
	PET_LIFE_STATUS_GROW,// 长大
};

#define					PET_APPEND_TYPE_SPECIAL				2
#define					PET_APPEND_TYPE_NORMAL				1
#define					PET_APPEND_TYPE_TEACH				0

class BornEffect :
	public cocos2d::CCNode
{
public:
	BornEffect(void);
	~BornEffect(void);
	bool doAction(float _f);

private:
	int index;
	CCArray * bitmaps;

	float startTime;
};

class GrowEffect :
	public cocos2d::CCNode
{
public:
	GrowEffect(void);
	~GrowEffect(void);
	bool doAction(float _f);

private:
	int index;
	CCArray * bitmaps;

	float startTime;
};

class Pet :
	public cocos2d::CCNode
{
public:
	Pet(void);
	virtual ~Pet(void);

	virtual int doAction(float _f);

	virtual void initSelf(void);
	virtual void exchangeAction(void);// 更换动作

	bool addHeart(int _num, int _type);
	cs::Armature * getArmature(void);
	int getElementId(void);
	int getLifeStatus(void);
	bool isBeSelected(void);
	void setBeSelected(bool _b);
	void setIsCheer(bool _b);
	bool getIsCheer(void);

	float getWidth(void);
	float getHeight(void);

protected:

	void doBorn(void);// 出生
	void finishBorn(void);
	void doGrow(void);// 长大
	void finishGrow(void);

	virtual void setLifeStatus(int _status);

	virtual void setTip(void);// 设置话语
//private:

	cocos2d::CCParticleSystemQuad * system;

	float width;
	float height;

	float timeCount;

	int elementId;

	int lifeStatus;// 生命周期
	bool beSelected;// 是否被选中

	CCSprite * frame;// 话语框
	CCSprite * tip;// 话语
	CCSprite * room;// 窝
	CCSprite * isCheer;// 已上阵
	CCSprite * egg;
	cs::Armature* armature;// flash
	GrowEffect * growEffect;// 长大特效
	BornEffect * bronEffect;// 出生特效
};

class PetJingXiGui :
	public::Pet
{
public:
	PetJingXiGui(void);
	~PetJingXiGui(void);

	virtual int doAction(float _f);
	virtual void initSelf(void);
	virtual void exchangeAction(void);// 更换动作
protected:

	virtual void setLifeStatus(int _status);
	virtual void setTip(void);// 设置话语
};

class PetNiuMoWang :
	public::Pet
{
public:
	PetNiuMoWang(void);
	~PetNiuMoWang(void);

	virtual int doAction(float _f);

	virtual void initSelf(void);
	virtual void exchangeAction(void);// 更换动作
protected:
	virtual void setLifeStatus(int _status);
	virtual void setTip(void);// 设置话语
};

class PetYuMianGongZhu :
	public::Pet
{
public:
	PetYuMianGongZhu(void);
	~PetYuMianGongZhu(void);

	virtual int doAction(float _f);

	virtual void initSelf(void);
	virtual void exchangeAction(void);// 更换动作
protected:
	virtual void setLifeStatus(int _status);
	virtual void setTip(void);// 设置话语
};

class PetLingGanDaWang :
	public::Pet
{
public:
	PetLingGanDaWang(void);
	~PetLingGanDaWang(void);

	virtual int doAction(float _f);

	virtual void initSelf(void);
	virtual void exchangeAction(void);// 更换动作
protected:
	virtual void setLifeStatus(int _status);
	virtual void setTip(void);// 设置话语
};

class PetManager
{
public:
	PetManager(void);
	~PetManager(void);

	Pet * getPetByElementId(int _elementId);
};

#endif
