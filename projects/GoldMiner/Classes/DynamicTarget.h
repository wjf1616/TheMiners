#ifndef __DYNAMIC_TARGET_H__
#define __DYNAMIC_TARGET_H__

#include "cocos2d.h"
#include "Global.h"
#include "Target.h"
#include "CSArmature/CSArmature.h"
#include "CSArmature/utils/CSArmatureDataManager.h"
#include "DizzySpecialEffect.h"

#define DYNAMIC_TARGET_MOVE_POINT_COUNT_MAX						4	// 规定的移动的点的最大个数

class GameControl;
class Hanger;
class DynamicTargetShell;

/*********************************************
	类型
*********************************************/
enum
{
	DYNAMIC_TARGET_TYPE_NORMALE = 0,// 原始状态
	DYNAMIC_TARGET_TYPE_CARRIED_BOMB,// 带着炸弹移动
	DYNAMIC_TARGET_TYPE_CARRIED_DIAMOND,// 带着钻石移动
	DYNAMIC_TARGET_TYPE_CARRIED_FOOD,// 带着食物移动
	DYNAMIC_TARGET_TYPE_PET// 宠物
};

//	状态
enum
{
	DYNAMIC_TARGET_STATUS_STATIC = 0,// 静止
	DYNAMIC_TARGET_STATUS_MOVING,// 移动
	DYNAMIC_TARGET_STATUS_CARRIED,// 被抓住
	DYNAMIC_TARGET_STATUS_GOT_REMOVE,// 获得后移除
	DYNAMIC_TARGET_STATUS_REMOVE,//直接移除
	DYNAMIC_TARGET_STATUS_DESTORY,// 冲屏幕中移除
	DYNAMIC_TARGET_STATUS_GOURD,// 被葫芦吸取的状态
	DYNAMIC_TARGET_STATUS_DIZZY,// 晕眩
	DYNAMIC_TARGET_STATUS_SKILL,// 技能
	DYNAMIC_TARGET_STATUS_CARRIER_CARRIED,// 被云朵加载的状态
	DYNAMIC_TARGET_STATUS_COUNT
};

class DynamicTarget :
	public cocos2d::CCNode
{
public:
	DynamicTarget(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTarget(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 
	virtual void intersectWithDynamicTarget(int _id, DynamicTarget * _target, GameControl * _gameControl);


	void setMove(int _movePointCount, double _movePointX[], double _movePointY[]);// 设置movePoint的属性
	void recoverLastStatus(void);// 恢复成上一个状态
	float getDistance(void);
	int getStatus(void);// 获得状态
	int getType(void);// 获得类型
	bool isCanCarried(void);// 是否可以抓取
	double getCurrX(void);// 获得当前x坐标
	double getCurrY(void);// 获得当前y坐标
	double getWidth(void);// 获得宽度
	double getHeight(void);// 获得高度
	int getId(void);// 获得id号

	double getMoveSpeed(void);

	cs::Armature* getArmature(void);

	//CCLabelTTF * roleSwaySpeed;
protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型

	Hanger * hanger;

	cs::Armature* armature;// flash
	int timeDisplayCount;
	int id;// 对象类型
	int type;// 对象的初始动作类型
	int status;// 状态
	int lastStatus;// 上一个状态
	bool canCarry;// 能否抓取
	bool canMove;// 是否能够移动

	double moveSpeed;// 移动速度
	int movePointCount;// 移动点的个数
	int currMovePointIndex;// 当前移动的开始点index
	int nextMovePointIndex;// 当前移动的结束点index
	double movePointX[DYNAMIC_TARGET_MOVE_POINT_COUNT_MAX];// 移动点的设置（起点规定为movePointX【0】）
	double movePointY[DYNAMIC_TARGET_MOVE_POINT_COUNT_MAX];// 移动点的设置（起点规定为movePointY【0】）
	//double moveAngle;// 当前移动的角度
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

	double currX;// 当前所在的x坐标
	double currY;// 当前所在的y坐标
	double vectorX;
	double vectorY;
	float distance;
	double width;// 宽
	double height;// 高

	float minMoveX;
	float maxMoveX;
	bool actionMove(void);// 移动处理函数
	void actionMove2(float _f);
	virtual void setAngle(void);// 设置角度
	void setAngle1(void);// 设置角度
	void setAngle2(void);// 设置角度
};

/******************************************************************
 小钻风
*******************************************************************/
//	自己状态
enum
{
	DYNAMIC_TARGET_XIAOXUANFEN_STATUS_STEAL = DYNAMIC_TARGET_STATUS_COUNT,// 移动
};

class DynamicTargetXiaoZuanFeng :
	public DynamicTarget
{
public:
	DynamicTargetXiaoZuanFeng(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTargetXiaoZuanFeng(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型
	virtual void setAngle(void);// 设置角度

	DizzySpecialEffect * dizzySpecialEffect;
	cocos2d::CCSprite * words;
	bool isWords;
};

/******************************************************************
精细鬼
*******************************************************************/
//	状态
class DynamicTargetJingXiGui :
	public DynamicTarget
{
public:
	DynamicTargetJingXiGui(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTargetJingXiGui(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型
	virtual void setAngle(void);// 设置角度

	DizzySpecialEffect * dizzySpecialEffect;
	cocos2d::CCSprite * words;
	bool isWords;
};


/******************************************************************
伶俐虫
*******************************************************************/
class DynamicTargetLingLiChong :
	public DynamicTarget
{
public:
	DynamicTargetLingLiChong(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTargetLingLiChong(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型
	virtual void setAngle(void);// 设置角度

	DizzySpecialEffect * dizzySpecialEffect;
	cocos2d::CCSprite * words;
	bool isWords;
};


/******************************************************************
灵感大王
*******************************************************************/
class DynamicTargetLingGanDaWang :
	public DynamicTarget
{
public:
	DynamicTargetLingGanDaWang(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTargetLingGanDaWang(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型
	virtual void setAngle(void);// 设置角度

	DizzySpecialEffect * dizzySpecialEffect;
	cocos2d::CCSprite * words;
	bool isWords;
};

/******************************************************************
玉面公主
*******************************************************************/
#define					DYNAMIC_TARGET_YUMIANGONGZHU_SKILL_SCOPE					120

class DynamicTargetYuMianGongZhu :
	public DynamicTarget
{
public:
	DynamicTargetYuMianGongZhu(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTargetYuMianGongZhu(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 

	cocos2d::CCSprite * getPen(void);

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型
	virtual void setAngle(void);// 设置角度

	DizzySpecialEffect * dizzySpecialEffect;
	cocos2d::CCSprite * words;
	bool isWords;

private:
	void hideTarget(GameControl * _gameControl);
	cocos2d::CCSprite * pen;
	bool isRemovePen;
};

/******************************************************************
牛魔王
*******************************************************************/
#define					NIUMOWANG_STATUS_DIZZY					DYNAMIC_TARGET_STATUS_COUNT
#define					NIUMOWANG_STATUS_DIZZY_TIME				180

class DynamicTargetNiuMoWang :
	public DynamicTarget
{
public:
	DynamicTargetNiuMoWang(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTargetNiuMoWang(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型
	virtual void setAngle(void);// 设置角度

	DizzySpecialEffect * dizzySpecialEffect;
	cocos2d::CCSprite * words;
	bool isWords;

private:
	bool isCarrierCarried;
	int beCarriedCount;// 被钩子抓住的次数
	int carriedTimeCount;
};

/******************************************************************
小丑鱼
*******************************************************************/
class DynamicTargetXiaoChouYu :
	public DynamicTarget
{
public:
	DynamicTargetXiaoChouYu(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTargetXiaoChouYu(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型
	virtual void setAngle(void);// 设置角度
};

/******************************************************************
鸟
*******************************************************************/
class DynamicTargetBrid :
	public DynamicTarget
{
public:
	DynamicTargetBrid(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTargetBrid(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型
	virtual void setAngle(void);// 设置角度
};

/******************************************************************
珍珠贝
*******************************************************************/
#define				DYNAMIC_TARGET_PEARL_SHELL_TIME_OPEN			160
#define				DYNAMIC_TARGET_PEARL_SHELL_TIME_OPEN_FRIST		20
#define				DYNAMIC_TARGET_PEARL_SHELL_TIME_CLOSE			180
class DynamicTargetPearlShell :
	public DynamicTarget
{
public:
	DynamicTargetPearlShell(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTargetPearlShell(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 

	void setIsGetValueWithShell(bool _b);

	CCSprite * getShell(void);

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型
	virtual void setAngle(void);// 设置角度

private:
	DynamicTargetShell * shell;
	bool isNeedCheck;// 是否需要检测开合状态
	bool isOpen;// 是否打开状态
	bool isHavingShell;// 是否拥有珍珠状态
	int timeCount;
	bool isGetValueWithShell;
};

/******************************************************************
珍珠
*******************************************************************/
class DynamicTargetShell :
	public DynamicTarget
{
public:
	DynamicTargetShell(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTargetShell(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 

	cocos2d::CCSprite * shellSprite;
protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型
	virtual void setAngle(void);// 设置角度
};

/******************************************************************
黄金
*******************************************************************/
class DynamicTargetGolden :
	public DynamicTarget
{
public:
	DynamicTargetGolden(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTargetGolden(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型
	virtual void setAngle(void);// 设置角度
};

/******************************************************************
石头
*******************************************************************/
class DynamicTargetStone :
	public DynamicTarget
{
public:
	DynamicTargetStone(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTargetStone(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型
	virtual void setAngle(void);// 设置角度
};

/******************************************************************
蝙蝠
*******************************************************************/
class DynamicTargetBat :
	public DynamicTarget
{
public:
	DynamicTargetBat(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTargetBat(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型
	virtual void setAngle(void);// 设置角度
};

/******************************************************************
蜘蛛
*******************************************************************/
class DynamicTargetSpider :
	public DynamicTarget
{
public:
	DynamicTargetSpider(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTargetSpider(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型
	virtual void setAngle(void);// 设置角度
};

/******************************************************************
火花莲
*******************************************************************/
#define					DYNAMIC_TARGET_HUOHUALIAN_BOMB_TIME							160 * 3
#define					DYNAMIC_TARGET_HUOHUALIAN_NORMAL_TIME						180 * 3
class DynamicTargetHuoHuaLian :
	public DynamicTarget
{
public:
	DynamicTargetHuoHuaLian(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTargetHuoHuaLian(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 

	void setYunInformation(int _pointIndex, int _yunIndex);
	int getYunIndex(void);
	int getPointIndex(void);
protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型
	virtual void setAngle(void);// 设置角度

private:
	bool canBomb;// 是否是可以爆炸的状态
	int timeCount;

	int pointIndex;
	int yunIndex;
};

/******************************************************************
星星
*******************************************************************/
class DynamicTargetStar :
	public DynamicTarget
{
public:
	DynamicTargetStar(int _id, int _type, double _x, double _y);// 类型   起始坐标
	~DynamicTargetStar(void);

	virtual void doAction(float _f, GameControl * _gameControl);// 动作调用函数
	virtual void getAwards(void);// 获得奖励
	virtual void setStatus(int _status, Hanger * _hanger);// 修改状态
	virtual int getSpeed(void);// 获得移动目标被抓取的数度(负的)
	virtual int getSpeedType(void);// 获得移动目标被抓取的数度(负的)
	virtual bool isIntersectById(int _id);// 返回是否与对应id的对象进行碰撞检测
	virtual void doIntersectWithHanger(GameControl * _gameControl, Hanger * _hanger); // 与钩子碰撞的处理
	virtual void intersectWithTarget(int _id, Target * _target, GameControl * _gameControl);//碰撞到静态对象时候 的处理函数 

protected:
	virtual void setArmatureByTypeAndStatus(int _type);// 设置flash的类型
	virtual void setAngle(void);// 设置角度
};


// 动态目标生成控制器
class DynamicTargetControl
{
public:
	DynamicTargetControl(void);// 类型   起始坐标
	~DynamicTargetControl(void);
	DynamicTarget * getDynamicTargetById(int _id, int _type, double _x, double _y);
};

#endif

