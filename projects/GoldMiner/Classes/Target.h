#ifndef __TARGET_H__
#define __TARGET_H__

#include "cocos2d.h"
#include "Global.h"

using namespace cocos2d;

class GameControl;
class Hanger;

enum
{
	TARGET_STATUS_NORMAL,// 初始化状态
	TARGET_STATUS_CARRIED,// 被拉状态
	TARGET_STATUS_MAGNETED,// 被吸铁石吸取的状态
	TARGET_STATUS_GOT_REMOVE,// 获得后移除
	TARGET_STATUS_REMOVE,//直接移除
	TARGET_STATUS_CARRIER_CARRIED// 被云朵加载的状态
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
	int getSpeed(void);// 获得目标的速度一般为负  也就是目标的重量
	int getSpeedType(void);// 获得目标的速度一般为负  也就是目标的重量
	void getAwards(void);
	//void resetById(int _id);// 将对象重置
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

	int id;// 目标的详细编号
	int yunIndex;// 起绑定的云朵id号
	int pointIndex;// 自身的大小
	int status;
	int hideCount;// 是否是隐藏状态

	//bool isCarrierOwn;// 是否被携带者携带
	bool canCarry;// 能否被抓取
	double startX;
	double startY;
	double vectorX;
	double vectorY;
	//double magnetAngle;// 被吸取于结束点的连线角度
	//double magnetDistance;// 被吸取时候的距离

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
