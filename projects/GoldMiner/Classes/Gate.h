#ifndef __GATE_H__
#define __GATE_H__

#include "cocos2d.h"
#include "Global.h"
#include "Target.h"
#include "DynamicTarget.h"
#include "Role.h"
#include "Carrier.h"

class GameControl;

class Gate
{
public:
	~Gate(void);
	/*
		gameId为0的时候确定的是测试关卡的固定属性值
		通过gameId来确定读取txm的文件
	*/
	static Gate * getInstance(int _gateId, GameControl * _gameControl);

	cocos2d::CCArray * getTargets(void);//目标指针集合
	cocos2d::CCArray * getDynamicTargets(void);//目标指针集合
	cocos2d::CCArray * getCarriers(void);
	//cocos2d::CCTMXTiledMap * getMap(void);
	//void setIsTiming(bool _isTiming);
	void setIsDynamicTargetMoving(bool _isDynamicTargetMoving);
	void setIsCarrierMoving(bool _isCarrierMoving);
	int getGoldenNum(void);
	int getTargetTotalNum(void);
	int getCanGoundDynamicTargetNum(void);
	//int * getCarriersLines(void);
	bool addHideTarget(Target * _target);
	bool addHideDynamicTarget(DynamicTarget * _dynamicTarget);

	void doAction(float _f, GameControl * _gameControl);

private:

	Gate(void);

	//Global * global;
	int gateId;// 关卡对应的id号
	//cocos2d::CCTMXTiledMap * map;//加载的对应的tmx文件
	cocos2d::CCArray * carriers;// 云朵的集合
	cocos2d::CCArray * targets;//目标指针集合
	cocos2d::CCArray * dynamicTargets;//目标指针集合

	cocos2d::CCArray * hideTarget;// 隐藏的静态目标的索引
	cocos2d::CCArray * hideDynamicTarget;// 隐藏的静态目标的索引

	bool isCarrierMoving;// 云朵是否移动
	bool isDynamicTargetMoving;// 移动的怪物能否移动
	int goldenNum;// 剩余金子的数量
	int targetTotalNum;// 静态和动态总共的目标的数量
	int dynamicTargetNum;// 可以被葫芦吸取的人物个数
	int needValue;
	//int carriersLines[50];
	DynamicTargetControl * dynamicTargetControl;

	void initSelf(GameControl * _gameControl, cocos2d::CCTMXTiledMap * map);

};

#endif

