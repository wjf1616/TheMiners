#ifndef __TARGET_H__
#define __TARGET_H__

#include "cocos2d.h"
#include "Global.h"

using namespace cocos2d;

class GameControl;
class Hanger;

enum
{
	TARGET_STATUS_NORMAL,// ��ʼ��״̬
	TARGET_STATUS_CARRIED,// ����״̬
	TARGET_STATUS_MAGNETED,// ������ʯ��ȡ��״̬
	TARGET_STATUS_GOT_REMOVE,// ��ú��Ƴ�
	TARGET_STATUS_REMOVE,//ֱ���Ƴ�
	TARGET_STATUS_CARRIER_CARRIED// ���ƶ���ص�״̬
};

class TargetExchangeBing;
class TargetExchangeEffect;

class Target :
	public cocos2d::CCSprite
{
public:
	Target(double _x, double _y, int _id, int _pointIndex, int _yunIndex);
	Target(double _x, double _y, const char _name[]);
	~Target(void);

	void doAction(float _f, GameControl * _gameControl);


	void exchangeBitmapAndId(int _id);
	void exchangeBitmap(int _id);
	int getStatus(void);
	void setStatus(int _status, Hanger * _hanger);
	float getDistance(void);
	int getSpeed(void);// ���Ŀ����ٶ�һ��Ϊ��  Ҳ����Ŀ�������
	int getSpeedType(void);// ���Ŀ����ٶ�һ��Ϊ��  Ҳ����Ŀ�������
	void getAwards(void);
	//void resetById(int _id);// ����������
	int getTypeById(void);
	int getId(void);
	bool isCanCarry(void);
	void intersectByHanger(GameControl * _gameControl, Hanger * _hanger);
	void intersectByBomb(GameControl * _gameControl);
	int getYunIndex(void);
	int getPointIndex(void);
	void addEffect(void);
	//void setIsCarrierOwn(bool _b);
	//bool getIsCarrierOwn(void);
	//bool flag;

private:
	Hanger * hanger;

	int id;// Ŀ�����ϸ���
	int yunIndex;// ��󶨵��ƶ�id��
	int pointIndex;// ����Ĵ�С
	int status;
	int hideCount;// �Ƿ�������״̬

	//bool isCarrierOwn;// �Ƿ�Я����Я��
	bool canCarry;// �ܷ�ץȡ
	double startX;
	double startY;
	double vectorX;
	double vectorY;
	//double magnetAngle;// ����ȡ�ڽ���������߽Ƕ�
	//double magnetDistance;// ����ȡʱ��ľ���

	float distance;
	float carriedDistance;
	
	bool isExchange;
	int exchangeId;
	int exchangeIndex;
	int exchangeCount;
	float startTime;

	TargetExchangeBing * bing;

	TargetExchangeEffect * effect;

	void initById();

	void shine(float _f);
};


class TargetExchangeBing :
	public cocos2d::CCNode
{
public:
	TargetExchangeBing(void);
	~TargetExchangeBing(void);
	bool doAction(float _f);

	void setDoAction(bool _b);

private:
	bool isDoAction;
	int index;
	CCArray * bitmaps;

	float startTime;
};

class TargetExchangeEffect :
	public cocos2d::CCNode
{
public:
	TargetExchangeEffect(void);
	~TargetExchangeEffect(void);
	bool doAction(float _f);
private:
	int index;
	CCArray * bitmaps;

	float startTime;
};

#endif
