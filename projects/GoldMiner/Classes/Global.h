#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "cocos2d.h" 

class GoldenMinerScene;

/***************************************************************
	版本控制 宏开关
*****************************************************************/
// 宏开关

#define					GOLDEN_MINER2_FLASH_FRAME							// flash是否是序列帧

#define					GOLDEN_MINER_2_VERSION_TIME							// 按时间计时

#define					GOLDEN_MINER2_VIRSION_CHALLENGE						// 是否拥有排行榜

#define					GOLDEN_MINER_2_NEW_GUIDE							// 新引导(引导只有一次)

#ifdef					GOLDEN_MINER_2_NEW_GUIDE							// （只有引导的版本）(默认版本是  三个引导的  第一大关基本操作  第二大关孙悟空人物技能 第三大关的猪八戒的宝石技能)
#define					GOLDEN_MINER_2_NEW_GUIDE_CAR						// 带矿车的引导
#endif

//#define					GOLDEN_MINER_2_VERSION_REVIEW					// 是否是评审版本(屏蔽排行榜  关于  更多游戏  按钮)

//#define					GOLDEN_MINER_2_S								// 小版本(压缩资源包)

//#define				GOLDEN_MINER_2_VERSION_PAY							// 计费模式
#ifdef					GOLDEN_MINER_2_VERSION_PAY

#define				GOLDEN_MINER_2_VERSION_PAY_TENCENT						// 腾讯计费模式（计费自己弹框）
#define				GOLDEN_MINER_2_VERSION_PAY_UUCUN						// UU计费点（计费自己弹框）

#endif

#define					GOLDEN_MINER2_VERSION_PAY_SELF						// 计费是不是自己弹框

#define					GOLDEN_MINER2_VERSION_PAY_IS_HAVING_PACKAGE			// 计费中是否包含  礼包（直接购买元宝）

//#define					GOLDEN_MINER_2_BUY_INGOT						// 是否是元宝的显示框后面的+可见
	
#define					GAME_LAYER_JEWEL_IS_BUTTON							// 是否游戏界面的宝石是按钮

#ifdef					GAME_LAYER_JEWEL_IS_BUTTON

#define					GOLDEN_MINER2_JEWEL_IS_PAY							// 宝石技能是按钮  是不是  计费点（还有就是提示）

#endif

/***************************************************************
	版本控制 宏开关
*****************************************************************/





#define					BIG_GATE_SIMLE_GATE_NUM					12
#define					CHALLENGE_RECORD_NUM					10


#define INTERSECT_CONTROL					8



typedef struct ChallengeRecord_
{
	int					index;
	int					roleId;
	int					score;
	int					level;
	std::string			name;
}ChallengeRecord;
/**************************************************
	挑战模式
***************************************************/
#define CHALLENGE_TYPE_IRON					1//开场动画
#define CHALLENGE_TYPE_SILVER				2
#define CHALLENGE_TYPE_GOLD					3
/****************************************************
引导相关定义
*****************************************************/
#ifndef								GOLDEN_MINER_2_NEW_GUIDE
	#define GUIDE_ID_START						GUIDE_ID_GRAP
	#define GUIDE_ID_GRAP						1//开场动画
	#define GUIDE_ID_PILL						2
	#define GUIDE_ID_GRENADE					3
	#define GUIDE_ID_MOONLIGHT					4
	#define GUIDE_ID_ROLE_SKILL					5
	#define GUIDE_ID_JEWEIL_SKILL				6
#else
	#define GUIDE_ID_START						GUIDE_ID_FRIST
	#define GUIDE_ID_GRAP						1//开场动画
	#define GUIDE_ID_PILL						2
	#define GUIDE_ID_GRENADE					3
	#define GUIDE_ID_MOONLIGHT					4
	#define GUIDE_ID_FRIST						5//（引导第一大关）
	#define GUIDE_ID_ROLE_SKILL					6//（引导第二大关）
	#define GUIDE_ID_JEWEIL_SKILL				7//（引导第三大关）
#endif

/*************************************************
提示相关
*************************************************/
#define			TIP_GAMING_START			31
#define			TIP_GAMING_END				49

/****************************************************
cartton相关定义
*****************************************************/
#define CARTOON_START						-999//开场动画
#define CARTOON_BAOXIANGGUO					1//宝象国
#define CARTOON_TONGYIANHE					2//通天河
#define CARTOON_NVERGUO						3//女儿国
#define CARTOON_HUOYANSHAN					4//火焰山
#define CARTOON_LINGSHAN					5//灵山
#define CARTOON_END							999//结束动画
#define CARTOON_COUNT						7

/****************************************************
explode相关定义
*****************************************************/
#define B_EXPLODE							1//logo界面
#define S_EXPLODE							2//load界面
#define HANGER_EXPLODE						3//load界面
#define HANGER_GOT_AWARD					HANGER_EXPLODE
#define BOMB_CIRCLE							100

/****************************************************
layer相关定义
*****************************************************/
#define LAYER_ID_LOGO						1//logo界面
#define LAYER_ID_LOADING					2//load界面
#define LAYER_ID_MAIN						3// 主界面
#define LAYER_ID_SETTING					4// 设置界面
#define LAYER_ID_HELP						5// 帮助界面
#define LAYER_ID_BIG_GATE_MAP				6// 大关选择界面
#define LAYER_ID_SMILE_GATE_SCENCE			7//小关卡界面
#define LAYER_ID_GATE_PAUSE					8// 暂停界面
#define LAYER_ID_GAMING						9// 游戏界面
#define LAYER_ID_CARTOON					10// 动画
#define LAYER_ID_PETPARK					11// 怪物窝
#define LAYER_ID_PROP_ROLE					12// 选人选道具
#define LAYER_ID_MAIN_APPEND				13// 主界面添加页
#define LAYER_ID_SHOP						14// 商城
#define LAYER_ID_GAMEOVER					15// 游戏结束
#define LAYER_ID_CHALLENGE					16// 挑战
#define LAYER_ID_CHALLENGE_COUNT			17// 挑战结算
#define LAYER_ID_PAUSE						18// 暂停
#define LAYER_ID_ROLE						19 // 选人页面
#define LAYER_ID_REGISTER					20// 签到页面
#define LAYER_ID_ROLE_INFORMATION			21// 选人提示信息页
#define LAYER_ID_DRAW						22// 抽奖

/****************************************************
宏定义：   读取对应关卡的tmx文件的对象类型的相关对应值
*****************************************************/
#define GAMECONTROL_TYPE_ROLE				1//对象类型 人物
#define GAMECONTROL_TYPE_NPC				2//对象类型 npc
#define GAMECONTROL_TYPE_SKILL				3//对象类型 技能
#define GAMECONTROL_TYPE_TARGET_STATIC		4//对象类型 静态目标
#define GAMECONTROL_TYPE_TARGET_DYNAMIC		5//对象类型 动态目标
#define GAMECONTROL_TYPE_PROP				6//对象类型 道具
#define GAMECONTROL_TYPE_CHIP				7//对象类型 怪物碎片
#define GAMECONTROL_TYPE_PET				8//对象类型 宠物
#define GAMECONTROL_TYPE_CARRIER			9//对象类型 携带者（云朵）
#define GAMECONTROL_TYPE_INFORMATION		999//对象类型 关卡信息
/***************************************************
关卡相关定义
***************************************************/
#define GATE_ID_MIN							1
#define GATE_ID_MAX							90
#define GATE_ID_START						1

enum
{
	BIG_GATE_TYPE_BAOXIANGGUO = 0,
	BIG_GATE_TYPE_TONGYIANHE,
	BIG_GATE_TYPE_NVERGUO,
	BIG_GATE_TYPE_HUOYANSHAN,
	BIG_GATE_TYPE_LINGSHAN,
	BIG_GATE_TYPE_GUIDE,
	BIG_GATE_TYPE_COUNT
};

/***************************************************
角度相关定义
***************************************************/
const double angleChange = 180;
const double angleLeft = 190;
const double angleRight = 350;
const double angleCenter = 270;
const double pi = 3.1415926;

/***************************************************
层次关系
****************************************************/
enum
{
	LAYER_ORDER_BACKGROUND =-999,//背景
	LAYER_ORDER_CONTROL = 999// 技能等相关东西
};

/**************************************************
	角色类型			
	添加角色有规则：选人买道具页面的排序最后一个是enum为0的 剩下按照顺序
***************************************************/
enum
{
	ROLE_TYPE_HULUWA = 0,
	//ROLE_TYPE_XIAOLONGNV = 0,// 小龙女
	ROLE_TYPE_TANGSENG,	//唐僧
	ROLE_TYPE_ZHUBAJIE,// 猪八戒
	ROLE_TYPE_SHAHESHANG,// 沙和尚
	ROLE_TYPE_SUNWUKONG, //孙悟空
	ROLE_TYPE_XIAOLONGNV,// 小龙女
	ROLE_TYPE_COUNT// 角色总数
};
#define  ROLE_TYPE_START				ROLE_TYPE_TANGSENG				//游戏初始角色


/**************************************************
	静态目标的类型
***************************************************/
enum
{
	TARGET_TYPE_GOLDEN = 0,//黄金
	TARGET_TYPE_STONE,//石头
	TARGET_TYPE_DIAMOND,//钻石
	TARGET_TYPE_COAL,//煤矿
	TARGET_TYPE_TRUNK,//树干 
	TARGET_TYPE_JEWEL,//宝石
	TARGET_TYPE_FOOD,//粮食
	TARGET_TYPE_BOMB,//炸弹
	TARGET_TYPE_BOX,//宝箱盒子
	TARGET_TYPE_COUNT,//所有目标类型的总数
};

/**************************************************
	静态目标所有对象的id
***************************************************/
enum
{
	TARGET_ID_BOMB = 4001,//炸弹
	TARGET_ID_BOX,//宝箱盒子
	TARGET_ID_GOLDEN_S,//黄金s
	TARGET_ID_GOLDEN_M,//黄金m
	TARGET_ID_GOLDEN_B,//黄金b
	TARGET_ID_STONE_S,//石头s
	TARGET_ID_STONE_M,//石头m
	TARGET_ID_STONE_B,//石头b
	TARGET_ID_DIAMOND,//钻石
	TARGET_ID_COAL,//煤矿
	TARGET_ID_TRUNK,//树干 
	TARGET_ID_JEWEL_BLUE,//蓝宝石
	TARGET_ID_JEWEL_RED,//红宝石
	TARGET_ID_JEWEL_GREEN,//绿宝石
	TARGET_ID_JEWEL_YELLOW,//黄宝石
	TARGET_ID_JEWEL_PURPLE,//紫宝石
	TARGET_ID_FOOD,//粮食
	TARGET_ID_COUNT,//所有目标类型的总数
};

/*****************************************************
	动态目标所有对象的id
*******************************************************/
enum
{
	DYNAMIC_ID_TYPE_START = 5000,
	DYNAMIC_ID_XIAOZUANFENG = 5001,// 小钻风
	DYNAMIC_ID_JINGXIGUI,// 精细鬼
	DYNAMIC_ID_LINGLICHONG,// 伶俐虫
	DYNAMIC_ID_LINGGANDAWANG,// 灵感大王
	DYNAMIC_ID_YUMIANGONGZHU,// 玉面公主
	DYNAMIC_ID_NIUMOWANG,// 牛魔王
	DYNAMIC_ID_XIAOCHOUYU,// 小丑鱼
	DYNAMIC_ID_BIRD,// 鸟
	DYNAMIC_ID_PEARL_SHELL,// 珍珠贝
	DYNAMIC_ID_SHELL,// 珍珠
	DYNAMIC_ID_GOLDEN,// 黄金
	DYNAMIC_ID_STONE,// 石头
	DYNAMIC_ID_BAT,// 蝙蝠
	DYNAMIC_ID_SPIDER,// 蜘蛛
	DYNAMIC_ID_HUOHUALIAN,// 或莲花
	DYNAMIC_ID_HUOHUALIAN_OTHER,// 或莲花(蓝)
	DYNAMIC_ID_STAR,// 星星
	DYNAMIC_ID_COUNT
};


/***************************************************
云朵类型
****************************************************/
enum
{
	CARRIER_ID_CLOUD = 9001,// 云朵携带静态目标
	CARRIER_ID_BLACK_CLOUD// 云朵携带动态精灵
};


/**************************************************
	道具的类型
***************************************************/
enum
{
	PROP_TYPE_COIN = 0,				// 铜钱
	PROP_TYPE_INGOT,				// 元宝
	PROP_TYPE_GRENADE,				// 炸弹
	PROP_TYPE_VIGOROUSLY_PILL,		// 大力丸
	PROP_TYPE_MOONLIGHT,			// 月光宝盒
	PROP_TYPE_ALIGNMENT,			// 瞄准线
	PROP_TYPE_BUDDAHA,				// 佛光
	PROP_TYPE_FOOD,					// 粮食
	PROP_TYPE_MEET,					// 肉
	PROP_TYPE_JEWEL_BLUE,			// 蓝宝石
	PROP_TYPE_JEWEL_RED,			// 红宝石
	PROP_TYPE_JEWEL_GREEN,			// 绿宝石
	PROP_TYPE_JEWEL_YELLOW,			// 黄宝石
	PROP_TYPE_JEWEL_PURPLE,			// 紫宝石
	PROP_TYPE_COUNT,
};

/***************************************************
	宠物精华
****************************************************/
enum
{
	PET_ELEMENT_XIAOZUANFENG = 0,// 小钻风魂魄
	PET_ELEMENT_JINGXIGUI,// 精细鬼
	PET_ELEMENT_LINGLICHONG,// 伶俐虫
	PET_ELEMENT_LINGGANDAWANG,// 灵感大王
	PET_ELEMENT_YUMIANGONGZHU,// 玉面公主
	PET_ELEMENT_NIUMOWANG,// 牛魔王
	PET_ELEMENT_COUNT
};

/**************************************************
	钩子状态
***************************************************/
enum
{
	HANGER_STATUS_SWAYING = 0,// 摇摆
	//HANGER_STATUS_SWAYING_STOP_THROW,// 静止放绳子的摇摆状态
	//HANGER_STATUS_INTERSECT_TARGET,// 钩子碰到可抓取物
	//HANGER_STATUS_INTERSECT_WALL,// 钩子碰到墙
	HANGER_STATUS_PULL_HAVING,// 拉回 抓到
	HANGER_STATUS_PULL_UNHAVING,// 拉回 没抓到
	HANGER_STATUS_THROW,// 放
	HANGER_STATUS_PAUSE// 暂停
};

enum
{
	TARGET_SPEED_TYPE_S = 2,
	TARGET_SPEED_TYPE_M,
	TARGET_SPEED_TYPE_B
};


/**************************************************
	物品技能ID
***************************************************/
enum
{
	SKILL_ID_NO = 0,
	SKILL_ID_GRENADE,// 炸弹
	SKILL_ID_VIGOROUSLY_PILL,// 大力丸
	SKILL_ID_MOONLIGHT// 月光宝盒
};

/**************************************************
	宝石技能ID
***************************************************/
enum
{
	SKILL_ID_JEWEL_DROP = 0,// 宝石技能 掉铜钱
	SKILL_ID_JEWEL_BALL,// 宝石技能 弹弹球
	SKILL_ID_JEWEL_FIVE_HANGER,// 宝石技能五个钩子技能
	SKILL_ID_JEWEL_MAGNET,// 宝石技能 吸铁石(矿)
	//SKILL_ID_JEWEL_DIZZY,// 宝石技能 晕
	//SKILL_ID_JEWEL_GOURD,// 宝石技能 紫金葫芦(怪物)
	SKILL_ID_JEWEL_COUNT// 宝石技能的总数
};

/**************************************************
	计费点ID
***************************************************/
enum
{
	PAY_ID_GENUINE = 1,//正版验证
	PAY_ID_TIMEMACHINE,// 时光机
	PAY_ID_SUNWUKONG,// 孙悟空
	PAY_ID_BUDDAHA,// 佛光
	PAY_ID_HULUWA,// 葫芦娃
	PAY_ID_MEET,// 肉
	PAY_ID_JEWEL,// 宝石技能
	PAY_ID_VALUE_PACKAGE,// 超值礼包
	PAY_ID_GOLDEN_PACKAGE,// 黄金礼包
};

class Global
{
public:
	static Global * getInstance(void);
	~Global(void);

	void getPayAwardByPayId(int _payId);

	int getPetElementIdByHideGateId(int _hideGateId, cocos2d::CCArray * _elementIds);

	int getChallengCostByChallengeType(int _challengeType);

	int getGenuineGateId(void);// 获得正版验证的关卡

	int getWordsIdByMapIdAndRoleId(int _mapId, int _roleId);// 获得选择关卡和人物对应的对话id号

	int getTimeByChallengeLevel(void);// 获得挑战等级的时间
	int getChallengeLevel(void);// 获得挑战的层次
	void setChallengeLevel(int _b);// 设置挑战模式的层次
	int getChallengeTimeLevel(void);// 获得战模式控制时间的层次数
	void setChallengeTimeLevel(int _level); // 设置挑战模式控制时间的层次数
	int getChallengeLevelType(void);// 获得挑战的类型
	void setChallengeLevelType(int _type);// 设置挑战的类型
	int getNextChallengeGateId(void);// 获得下次挑战模式的id号
	int getChallengeCountSum(void);
	void setChallengeCountSum(int _sum);

	int getRoleSpeedByRoleId(int _roleId);// 通过任务id获得速度
	int getRoleSwapSpeedByRoleId(int _roleId);// 通过人物id获得摇摆速度

	int getPetHeartFull(int _petElementId);	// 获得宠物养成的所需爱心数	

	int getCartoonId(void);// 获得要播放的漫画号
	void setCartoonId(int _gateId);// 设置要播放的漫画的号

	bool getIsBuyThing(void);// 是否游戏开始前购买东西
	void setIsBuyThing(bool _b);// 是否游戏开始前购买东西

	bool getCurrGameLayerLoadDynamicTarget(int _dynamicTargetId);
	void setCurrGameLayerLoadDynamicTarget(int _dynamicTargetId, bool _isLoaded);
	void initCurrGameLayerLoadDynamicTarget(void);
	int getSimleGateNumAndGateIdBySelectBigGateType(cocos2d::CCArray * _gateIds);
	int getMapIdByGateId(int _gateId);// 通过gateid号获得其所属于的map的id号
	int getSmallGateIdByGateId(int _gateId);// 通过gateid号获得小关的号
	void setSelectGateType(int _gateType);
	int getSelectGateType(void);
	void setSelectGateId(int _gateId);// 设置选中的关卡id号 
	int getSelectGateId(void);// 获得选中的关卡id号 
	void setSelectGateNextGateId(int _nextGateId);// 设置选中的关卡下一关id号 
	int getSelectGateNextGateId(void);// 获得选中的关卡下一关id号 
	int getSelectRoleId(void);// 获得选择人物的角色
	void setSelectRoleId(int _roleId);// 设置选择人物的角色
	int getCurrGuideId(void);// 当前的引导关卡的号  如果是-1表示不是引导关卡
	void setCurrGuideId(int _guideId);

	int getSceneSpeedByMapId(int _mapId);// 通过map的id来获的场景速度

	int getRolePriceByRoleId(int _roleId);// 获得解锁对应人物所需的价格

/**************************************************
吸取东西同时到达的处理
**************************************************/
	double getJewelSkillScale(void);
	void setJewelSkillScale(double _scale);
/**************************************************
	吸取东西到达时长确定（移动速度不定）的异步到达
******************************************************/	
	float getJewelSkillDistance(void);
	void setJewelSkillDistance(float _distance);

	void initValueTimes(void);// 初始化获得奖励的倍数
	void setValueTimes(int _targetType, int _times);// 设这奖励的倍数
	int getPropAwardNumById(int _propId);// 获得对应道具id的关卡获得值
	void appendPropAwardGet(int _propId, int _num);// 直接添加
	void appendPropAwardGet(int _targetType, int _propId, int _num);// 根据目标类型添加
	void initPropAwardGet(void);// 初始化关卡获得的奖励
	void initPetElementGet(void);// 初始化获得的宠物精华
	void appendPetElementGet(int _petElementId, int num);// 添加获得的宠物的值
	int getPetElementGetById(int _petElementId);// 获得宠物精华的获得的值
	bool getPetIsOpenByIdAndNum(int _petElementId, int num);

	int getGetJewelCount(void);// 获得的宝石的统计数
	int getMaxContinusesCount(void);// 获得最高连击数
	int getContinuesCount(void);// 获得连击次数
	void setContinuesCount(int _appendNum);// 设置连击次数
	void initContinuesCount(void);// 设置连击次数

	//double getHangerStartX(void);
	//void setHangerStartX(double _x);
	//double getHangerStartY(void);
	//void setHangerStartY(double _y);
	//double getHangerCurrX(void);
	//void setHangerCurrX(double _x);
	//double getHangerCurrY(void);
	//void setHangerCurrY(double _y);
	//double getHangerAngle(void);
	//void setHangerAngle(double _angle);
	int getHangerStatus(void);
	void setHangerStatus(int _status);
	//double getHangerDistanceToRope(void);
	//void setHangerDistanceToRope(double _hangerDistanceToRope);
	//double getHangerDistanceToCentre(void);
	//void setHangerDistanceToCentre(double _hangerDistanceToRope);
	//bool getHangerCanThrow(void);
	//void setHangerCanThrow(bool _b);

	double getcentreX(void);
	void setcentreX(double _centreX);
	double getcentreY(void);
	void setcentreY(double _centreY);

	int getGameControlTypeById(int _id);// 地编文件读取对象类型

#ifdef							GOLDEN_MINER_2_VERSION_TIME
	float getTimeRatio(void);
	void setTimeRatio(float _f);
#endif

	//工具
	bool isInRect(cocos2d::CCRect * _rect, double _pointX, double _pointY);
	bool isInCircle(double _x, double _y, double _pointX, double _pointY, double _r);
	bool intersectCCRectWithSector(cocos2d::CCRect * _rect, double _pointX, double _pointY, double _angleL, double _angleR);
	bool intersectCCRectWithSector(double _rectX, double _rectY, double _rectW, double _rectH, double _pointX, double _pointY, double _angleL, double _angleR);
	double getMin(double _tmp[], unsigned int _num);
	double getMax(double _tmp[], unsigned int _num);
	void changeAngleAtan2To360(double * angle);
	bool isLeapYear(int _year);

	GoldenMinerScene *s;

	ChallengeRecord records[20];
	int recordsNum;
	int myRecordIndex;

private:
	Global(void);

	static Global * global;

#ifdef							GOLDEN_MINER_2_VERSION_TIME
	float timeRatio;
#endif
	int challengeCountSum;
	int challengeLevel;
	int challengeTimeLevel;
	int challengeType;
	int lastChallengeGateId;

	bool isBuyThing;

	int cartoonId;// 卡通id   如果是0就是不播放卡通
	int currGuideId;// 当前的引导关卡的号  如果是-1表示不是引导关卡

	int selectGateType;	// 选择的大关的类型
	int selectRoleId;// 选择的人的角色
	int selectGateId;// 选中关卡的id号
	int nextGateId;// 下一关的关卡的id号

	bool currGameLayerLoadDynamicTarget[DYNAMIC_ID_COUNT-DYNAMIC_ID_XIAOZUANFENG];// 当前游戏加载的我动画对象是否已经加载
	int petElementGet[PET_ELEMENT_COUNT];// 获得的灵魂的数量
	int propAwardGet[PROP_TYPE_COUNT];//抓到对应的矿的数量
	int propAwardTimes[TARGET_TYPE_COUNT];//当前对应prop的获得倍数(目前是针对获得所有prop而言 )

/**************************************************
吸取东西同时到达的处理
******************************************************/
	double jewelSkillScale;// 宝石技能触发对应对象的放缩比例
/**************************************************
	吸取东西到达时长确定（移动速度不定）的异步到达
******************************************************/
	float jewelSkillDistance;// 宝石技能触发对应对象的放缩比例

	double centreX;// 抓钩摇摆根据的点x坐标
	double centreY;// 抓钩摇摆根据的点y坐标

	int continuousCount;// 连击次数
	int maxContinuesCount;// 最大连击数
	int getJewelCount;// 获得的宝石的统计数

	//double hangerStartX;// 钩子初始化起始的x坐标
	//double hangerStartY;// 钩子初始化起始的y坐标
	//double hangerCurrX;// 钩子当前的x坐标
	//double hangerCurrY;// 钩子当前的y坐标
	//double hangerAngle;// 钩子当前的角度
	int hangerStatus;// 钩子当前的状态
	//double hangerDistanceToRope;// 钩子置绳子节点的距离
	//double hangerDistanceToCentre;// 钩子置中心的距离
	//bool hangerCanThrow;
};

#endif
