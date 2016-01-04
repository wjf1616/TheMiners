#ifndef __DYNAMIC_TARGET_H__
#define __DYNAMIC_TARGET_H__

#include "cocos2d.h"
#include "Global.h"
#include "Target.h"
#include "CSArmature/CSArmature.h"
#include "CSArmature/utils/CSArmatureDataManager.h"
#include "DizzySpecialEffect.h"

#define DYNAMIC_TARGET_MOVE_POINT_COUNT_MAX						4	// �涨���ƶ��ĵ��������

class GameControl;
class Hanger;
class DynamicTargetShell;

/*********************************************
	����
*********************************************/
enum
{
	DYNAMIC_TARGET_TYPE_NORMALE = 0,// ԭʼ״̬
	DYNAMIC_TARGET_TYPE_CARRIED_BOMB,// ����ը���ƶ�
	DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND,// ������ʯ�ƶ�
	DYNAMIC_TARGET_TYPE_CARRIED_FOOD,// ����ʳ���ƶ�
	DYNAMIC_TARGET_TYPE_PET// ����
};

//	״̬
enum
{
	DYNAMIC_TARGET_STATUS_STATIC = 0,// ��ֹ
	DYNAMIC_TARGET_STATUS_MOVING,// �ƶ�
	DYNAMIC_TARGET_STATUS_CARRIED,// ��ץס
	DYNAMIC_TARGET_STATUS_GOT_REMOVE,// ��ú��Ƴ�
	DYNAMIC_TARGET_STATUS_REMOVE,//ֱ���Ƴ�
	DYNAMIC_TARGET_STATUS_DESTORY,// ����Ļ���Ƴ�
	DYNAMIC_TARGET_STATUS_GOURD,// ����«��ȡ��״̬
	DYNAMIC_TARGET_STATUS_DIZZY,// ��ѣ
	DYNAMIC_TARGET_STATUS_SKILL,// ����
	DYNAMIC_TARGET_STATUS_CARRIER_CARRIED,// ���ƶ���ص�״̬
	DYNAMIC_TARGET_STATUS_COUNT
};

class DynamicTarget :
	public cocos2d::CCNode
{
public:
	DynamicTarget(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTarget(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 
	virtual void intersectWithDynamicTarget(int _id, DynamicTarget * _target, GameControl * _gameControl);


	void setMove(int _movePointCount, double _movePointX[], double _movePointY[]);// ����movePoint������
	void recoverLastStatus(void);// �ָ�����һ��״̬
	float getDistance(void);
	int getStatus(void);// ���״̬
	int getType(void);// �������
	bool isCanCarried(void);// �Ƿ����ץȡ
	double getCurrX(void);// ��õ�ǰx����
	double getCurrY(void);// ��õ�ǰy����
	double getWidth(void);// ��ÿ��
	double getHeight(void);// ��ø߶�
	int getId(void);// ���id��

	double getMoveSpeed(void);

	cs::Armature* getArmature(void);

	//CCLabelTTF * roleSwaySpeed;
protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������

	Hanger * hanger;

	cs::Armature* armature;// flash
	int timeDisplayCount;
	int id;// ��������
	int type;// ����ĳ�ʼ��������
	int status;// ״̬
	int lastStatus;// ��һ��״̬
	bool canCarry;// �ܷ�ץȡ
	bool canMove;// �Ƿ��ܹ��ƶ�

	double moveSpeed;// �ƶ��ٶ�
	int movePointCount;// �ƶ���ĸ���
	int currMovePointIndex;// ��ǰ�ƶ��Ŀ�ʼ��index
	int nextMovePointIndex;// ��ǰ�ƶ��Ľ�����index
	double movePointX[DYNAMIC_TARGET_MOVE_POINT_COUNT_MAX];// �ƶ�������ã����涨ΪmovePointX��0����
	double movePointY[DYNAMIC_TARGET_MOVE_POINT_COUNT_MAX];// �ƶ�������ã����涨ΪmovePointY��0����
	//double moveAngle;// ��ǰ�ƶ��ĽǶ�
#ifdef							GOLDEN_MINER_2_VERSION_TIME
	float moveTimeSum;
	float moveTimeCount;
#else
	int moveTimeSum;
	int moveTimeCount;
#endif
	double moveVectorX;
	double moveVectorY;

	float carriedDistance;

	double currX;// ��ǰ���ڵ�x����
	double currY;// ��ǰ���ڵ�y����
	double vectorX;
	double vectorY;
	float distance;
	double width;// ��
	double height;// ��

	float minMoveX;
	float maxMoveX;
	bool actionMove(void);// �ƶ�������
	void actionMove2(float _f);
	virtual void setAngle(void);// ���ýǶ�
	void setAngle1(void);// ���ýǶ�
	void setAngle2(void);// ���ýǶ�
};

/******************************************************************
 С���
*******************************************************************/
//	�Լ�״̬
enum
{
	DYNAMIC_TARGET_XIAOXUANFEN_STATUS_STEAL = DYNAMIC_TARGET_STATUS_COUNT,// �ƶ�
};

class DynamicTargetXiaoZuanFeng :
	public DynamicTarget
{
public:
	DynamicTargetXiaoZuanFeng(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTargetXiaoZuanFeng(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������
	virtual void setAngle(void);// ���ýǶ�

	DizzySpecialEffect * dizzySpecialEffect;
	cocos2d::CCSprite * words;
	bool isWords;
};

/******************************************************************
��ϸ��
*******************************************************************/
//	״̬
class DynamicTargetJingXiGui :
	public DynamicTarget
{
public:
	DynamicTargetJingXiGui(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTargetJingXiGui(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������
	virtual void setAngle(void);// ���ýǶ�

	DizzySpecialEffect * dizzySpecialEffect;
	cocos2d::CCSprite * words;
	bool isWords;
};


/******************************************************************
������
*******************************************************************/
class DynamicTargetLingLiChong :
	public DynamicTarget
{
public:
	DynamicTargetLingLiChong(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTargetLingLiChong(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������
	virtual void setAngle(void);// ���ýǶ�

	DizzySpecialEffect * dizzySpecialEffect;
	cocos2d::CCSprite * words;
	bool isWords;
};


/******************************************************************
��д���
*******************************************************************/
class DynamicTargetLingGanDaWang :
	public DynamicTarget
{
public:
	DynamicTargetLingGanDaWang(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTargetLingGanDaWang(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������
	virtual void setAngle(void);// ���ýǶ�

	DizzySpecialEffect * dizzySpecialEffect;
	cocos2d::CCSprite * words;
	bool isWords;
};

/******************************************************************
���湫��
*******************************************************************/
#define					DYNAMIC_TARGET_YUMIANGONGZHU_SKILL_SCOPE					120

class DynamicTargetYuMianGongZhu :
	public DynamicTarget
{
public:
	DynamicTargetYuMianGongZhu(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTargetYuMianGongZhu(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 

	cocos2d::CCSprite * getPen(void);

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������
	virtual void setAngle(void);// ���ýǶ�

	DizzySpecialEffect * dizzySpecialEffect;
	cocos2d::CCSprite * words;
	bool isWords;

private:
	void hideTarget(GameControl * _gameControl);
	cocos2d::CCSprite * pen;
	bool isRemovePen;
};

/******************************************************************
ţħ��
*******************************************************************/
#define					NIUMOWANG_STATUS_DIZZY					DYNAMIC_TARGET_STATUS_COUNT
#define					NIUMOWANG_STATUS_DIZZY_TIME				180

class DynamicTargetNiuMoWang :
	public DynamicTarget
{
public:
	DynamicTargetNiuMoWang(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTargetNiuMoWang(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������
	virtual void setAngle(void);// ���ýǶ�

	DizzySpecialEffect * dizzySpecialEffect;
	cocos2d::CCSprite * words;
	bool isWords;

private:
	bool isCarrierCarried;
	int beCarriedCount;// ������ץס�Ĵ���
	int carriedTimeCount;
};

/******************************************************************
С����
*******************************************************************/
class DynamicTargetXiaoChouYu :
	public DynamicTarget
{
public:
	DynamicTargetXiaoChouYu(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTargetXiaoChouYu(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������
	virtual void setAngle(void);// ���ýǶ�
};

/******************************************************************
��
*******************************************************************/
class DynamicTargetBrid :
	public DynamicTarget
{
public:
	DynamicTargetBrid(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTargetBrid(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������
	virtual void setAngle(void);// ���ýǶ�
};

/******************************************************************
���鱴
*******************************************************************/
#define				DYNAMIC_TARGET_PEARL_SHELL_TIME_OPEN			160
#define				DYNAMIC_TARGET_PEARL_SHELL_TIME_OPEN_FRIST		20
#define				DYNAMIC_TARGET_PEARL_SHELL_TIME_CLOSE			180
class DynamicTargetPearlShell :
	public DynamicTarget
{
public:
	DynamicTargetPearlShell(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTargetPearlShell(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 

	void setIsGetValueWithShell(bool _b);

	CCSprite * getShell(void);

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������
	virtual void setAngle(void);// ���ýǶ�

private:
	DynamicTargetShell * shell;
	bool isNeedCheck;// �Ƿ���Ҫ��⿪��״̬
	bool isOpen;// �Ƿ��״̬
	bool isHavingShell;// �Ƿ�ӵ������״̬
	int timeCount;
	bool isGetValueWithShell;
};

/******************************************************************
����
*******************************************************************/
class DynamicTargetShell :
	public DynamicTarget
{
public:
	DynamicTargetShell(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTargetShell(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 

	cocos2d::CCSprite * shellSprite;
protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������
	virtual void setAngle(void);// ���ýǶ�
};

/******************************************************************
�ƽ�
*******************************************************************/
class DynamicTargetGolden :
	public DynamicTarget
{
public:
	DynamicTargetGolden(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTargetGolden(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������
	virtual void setAngle(void);// ���ýǶ�
};

/******************************************************************
ʯͷ
*******************************************************************/
class DynamicTargetStone :
	public DynamicTarget
{
public:
	DynamicTargetStone(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTargetStone(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������
	virtual void setAngle(void);// ���ýǶ�
};

/******************************************************************
����
*******************************************************************/
class DynamicTargetBat :
	public DynamicTarget
{
public:
	DynamicTargetBat(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTargetBat(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������
	virtual void setAngle(void);// ���ýǶ�
};

/******************************************************************
֩��
*******************************************************************/
class DynamicTargetSpider :
	public DynamicTarget
{
public:
	DynamicTargetSpider(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTargetSpider(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������
	virtual void setAngle(void);// ���ýǶ�
};

/******************************************************************
����
*******************************************************************/
#define					DYNAMIC_TARGET_HUOHUALIAN_BOMB_TIME							160 * 3
#define					DYNAMIC_TARGET_HUOHUALIAN_NORMAL_TIME						180 * 3
class DynamicTargetHuoHuaLian :
	public DynamicTarget
{
public:
	DynamicTargetHuoHuaLian(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTargetHuoHuaLian(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 

	void setYunInformation(int _pointIndex, int _yunIndex);
	int getYunIndex(void);
	int getPointIndex(void);
protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������
	virtual void setAngle(void);// ���ýǶ�

private:
	bool canBomb;// �Ƿ��ǿ��Ա�ը��״̬
	int timeCount;

	int pointIndex;
	int yunIndex;
};

/******************************************************************
����
*******************************************************************/
class DynamicTargetStar :
	public DynamicTarget
{
public:
	DynamicTargetStar(int _id, int _type, double _x, double _y);// ����   ��ʼ����
	~DynamicTargetStar(void);

	virtual void doAction(float _f, GameControl * _gameControl);// �������ú���
	virtual void getAwards(void);// ��ý���
	virtual void setStatus(int _status, Hanger * _hanger);// �޸�״̬
	virtual int getSpeed(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual int getSpeedType(void);// ����ƶ�Ŀ�걻ץȡ������(����)
	virtual bool isIntersectById(int _id);// �����Ƿ����Ӧid�Ķ��������ײ���
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // �빳����ײ�Ĵ���
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//��ײ����̬����ʱ�� �Ĵ����� 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// ����flash������
	virtual void setAngle(void);// ���ýǶ�
};


// ��̬Ŀ�����ɿ�����
class DynamicTargetControl
{
public:
	DynamicTargetControl(void);// ����   ��ʼ����
	~DynamicTargetControl(void);
	DynamicTarget * getDynamicTargetById(int _id, int _type, double _x, double _y);
};

#endif

