#ifndef __PET_H__
#define __PET_H__

#include "cocos2d.h"
#include "CSArmature/CSArmature.h"
#include "CSArmature/utils/CSArmatureDataManager.h"

using namespace cocos2d;

enum
{
	PET_LIFE_STATUS_EGG,// ��
	PET_LIFE_STATUS_BABY,// ����
	PET_LIFE_STATUS_GROW,// ����
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
	virtual void exchangeAction(void);// ��������

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

	void doBorn(void);// ����
	void finishBorn(void);
	void doGrow(void);// ����
	void finishGrow(void);

	virtual void setLifeStatus(int _status);

	virtual void setTip(void);// ���û���
//private:

	cocos2d::CCParticleSystemQuad * system;

	float width;
	float height;

	float timeCount;

	int elementId;

	int lifeStatus;// ��������
	bool beSelected;// �Ƿ�ѡ��

	CCSprite * frame;// �����
	CCSprite * tip;// ����
	CCSprite * room;// ��
	CCSprite * isCheer;// ������
	CCSprite * egg;
	cs::Armature* armature;// flash
	GrowEffect * growEffect;// ������Ч
	BornEffect * bronEffect;// ������Ч
};

class PetJingXiGui :
	public::Pet
{
public:
	PetJingXiGui(void);
	~PetJingXiGui(void);

	virtual int doAction(float _f);
	virtual void initSelf(void);
	virtual void exchangeAction(void);// ��������
protected:

	virtual void setLifeStatus(int _status);
	virtual void setTip(void);// ���û���
};

class PetNiuMoWang :
	public::Pet
{
public:
	PetNiuMoWang(void);
	~PetNiuMoWang(void);

	virtual int doAction(float _f);

	virtual void initSelf(void);
	virtual void exchangeAction(void);// ��������
protected:
	virtual void setLifeStatus(int _status);
	virtual void setTip(void);// ���û���
};

class PetYuMianGongZhu :
	public::Pet
{
public:
	PetYuMianGongZhu(void);
	~PetYuMianGongZhu(void);

	virtual int doAction(float _f);

	virtual void initSelf(void);
	virtual void exchangeAction(void);// ��������
protected:
	virtual void setLifeStatus(int _status);
	virtual void setTip(void);// ���û���
};

class PetLingGanDaWang :
	public::Pet
{
public:
	PetLingGanDaWang(void);
	~PetLingGanDaWang(void);

	virtual int doAction(float _f);

	virtual void initSelf(void);
	virtual void exchangeAction(void);// ��������
protected:
	virtual void setLifeStatus(int _status);
	virtual void setTip(void);// ���û���
};

class PetManager
{
public:
	PetManager(void);
	~PetManager(void);

	Pet * getPetByElementId(int _elementId);
};

#endif
