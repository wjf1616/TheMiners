#ifndef __HANGER_H__
#define __HANGER_H__

#include "cocos2d.h"
#include "Global.h"

class Rope;
class GameControl;

using namespace cocos2d;

#define				HANGER_FUNCTION_TYPE_NORMAL					1 // 普通
#define				HANGER_FUNCTION_TYPE_THROW					2 // 贯串
#define				HANGER_FUNCTION_TYPE_CARRY_BOMB				3 // 抓炸弹
#define				HANGER_FUNCTION_TYPE_BOMB					4 // 炸掉遇到物品
#define				HANGER_FUNCTION_TYPE_EXCHANGE_TO_JEWEL		5 // 变换成随意的宝石
#define				HANGER_FUNCTION_TYPE_STONE_TO_GOLDEN		6 // 石头变金子

#define				HANGER_SPEED_PULL_NORMAL			45

enum
{
	HANGER_GET_TARFET = 10,
	HANGER_GET_NOTHING,
};



class Hanger :
	public cocos2d::CCSprite
{
public:
	Hanger(double _distanceToCentre, double _distanceToRope, double _speedAngle, int _speedSelf, int _speedScene, int _type);//, const char _name[]);//, const cocos2d::CCRect &_ccRect);
	~Hanger(void);

	virtual void onExit(void);
	Rope * getRope(void);
	void setSpeedTimes(float _times);
	int setSpeedTarget(int _speedTarget, int _speedTargetType);//设置目标对钩子速度的影响
	int getStatus(void);//返回钩子状态
	int setStatus(int _status);//设置钩子状态
	//int setPullSpeed(int _pullSpeed);
	double getAngle(void);// 获得钩子当前的角度
	void setAngle(double _angle);// 获得钩子当前的角度
	double getCurrX(void);// 获得钩子的当前x
	double getCurrY(void);// 获得钩子的当前y
	double getDistanceToRope(void);
	double getDistanceToCentre(void);
	void resetHangerBitmap(const char _name[], double _distanceToCentre, double _distanceToRope, int _functionType);
	//unsigned char setIsHaveTarget(unsigned char _isHaveTarget);//设置是否挂有目标
	//cocos2d::CCSprite * getHanger(void);//获得钩子对象
	void doAction(float _f, GameControl * _gameControl);//钩子动作执行
	void intersectCheck(GameControl * _gameControl);
	bool getCanThrow(void);
	void appendSpeedSelf(int _append);
	int getFunctionType(void);
	void setFunctionType(int _functionType);
	void setType(int _type);

	void setPetSpeed(int _speed);
	void setSpeedAngle(double _s);
	double getSpeedAngle(void);


	// test用
	int getSpeedSelf(void);
	int getSpeedScene(void);
	void setSpeedSelf(int _s);
	void setSpeedScene(int _s);

	//void getCanThrow(void);
	int carryTargetType;// 当前被抓取对象的类型（没有抓取为0）
	void * carryTargetPoint;// 当前被抓取对象的地址引用
private:
	Rope * rope;//绳子的指针
	cocos2d::CCSprite * zhaDanSprite;
#ifdef				GOLDEN_MINER_2_VERSION_TIME
	float tmpStatusTimeCount;
#else
	int tmpStatusTimeCount;
#endif

	bool canThrow;

	float speedTimes;
	double speedAngle;//角速度
	//int pullSpeed; // 提上的速度
	int speedSelf;//钩子自己的速度
	int speedScene;//场景的速度
	int speedTarget;//目标物体的速度
	int speedTargetType;//目标物体的速度
	int speedPet;
	int status;//状态
	int lastStatus;// 上一次的状态
	int type;
	int functionType;
	double angle;//角度
	double x;//初始x坐标
	double y;//初始y坐标
	double currX;//当前x坐标
	double currY;//当前y坐标
	double distanceToCentre;//中心点距离绳子其实点的距离
	double distanceToRope;//中心点距离绳子接口点的距离

	void changeAngle(void);
	void changeBitmap(void);
	void setMovePostion(GameControl * _gameControl);
	void setSwayPostion(void);
	float getSpeed(void);
};

#endif

