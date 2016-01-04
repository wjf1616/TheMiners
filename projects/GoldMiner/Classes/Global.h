#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "cocos2d.h" 

class GoldenMinerScene;

/***************************************************************
	�汾���� �꿪��
*****************************************************************/
// �꿪��

#define					GOLDEN_MINER2_FLASH_FRAME							// flash�Ƿ�������֡

#define					GOLDEN_MINER_2_VERSION_TIME							// ��ʱ���ʱ

#define					GOLDEN_MINER2_VIRSION_CHALLENGE						// �Ƿ�ӵ�����а�

#define					GOLDEN_MINER_2_NEW_GUIDE							// ������(����ֻ��һ��)

#ifdef					GOLDEN_MINER_2_NEW_GUIDE							// ��ֻ�������İ汾��(Ĭ�ϰ汾��  ����������  ��һ��ػ�������  �ڶ������������＼�� ������ص���˽�ı�ʯ����)
#define					GOLDEN_MINER_2_NEW_GUIDE_CAR						// ���󳵵�����
#endif

//#define					GOLDEN_MINER_2_VERSION_REVIEW					// �Ƿ�������汾(�������а�  ����  ������Ϸ  ��ť)

//#define					GOLDEN_MINER_2_S								// С�汾(ѹ����Դ��)

//#define				GOLDEN_MINER_2_VERSION_PAY							// �Ʒ�ģʽ
#ifdef					GOLDEN_MINER_2_VERSION_PAY

#define				GOLDEN_MINER_2_VERSION_PAY_TENCENT						// ��Ѷ�Ʒ�ģʽ���Ʒ��Լ�����
#define				GOLDEN_MINER_2_VERSION_PAY_UUCUN						// UU�Ʒѵ㣨�Ʒ��Լ�����

#endif

#define					GOLDEN_MINER2_VERSION_PAY_SELF						// �Ʒ��ǲ����Լ�����

#define					GOLDEN_MINER2_VERSION_PAY_IS_HAVING_PACKAGE			// �Ʒ����Ƿ����  �����ֱ�ӹ���Ԫ����

//#define					GOLDEN_MINER_2_BUY_INGOT						// �Ƿ���Ԫ������ʾ������+�ɼ�
	
#define					GAME_LAYER_JEWEL_IS_BUTTON							// �Ƿ���Ϸ����ı�ʯ�ǰ�ť

#ifdef					GAME_LAYER_JEWEL_IS_BUTTON

#define					GOLDEN_MINER2_JEWEL_IS_PAY							// ��ʯ�����ǰ�ť  �ǲ���  �Ʒѵ㣨���о�����ʾ��

#endif

/***************************************************************
	�汾���� �꿪��
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
	��սģʽ
***************************************************/
#define CHALLENGE_TYPE_IRON					1//��������
#define CHALLENGE_TYPE_SILVER				2
#define CHALLENGE_TYPE_GOLD					3
/****************************************************
������ض���
*****************************************************/
#ifndef								GOLDEN_MINER_2_NEW_GUIDE
	#define GUIDE_ID_START						GUIDE_ID_GRAP
	#define GUIDE_ID_GRAP						1//��������
	#define GUIDE_ID_PILL						2
	#define GUIDE_ID_GRENADE					3
	#define GUIDE_ID_MOONLIGHT					4
	#define GUIDE_ID_ROLE_SKILL					5
	#define GUIDE_ID_JEWEIL_SKILL				6
#else
	#define GUIDE_ID_START						GUIDE_ID_FRIST
	#define GUIDE_ID_GRAP						1//��������
	#define GUIDE_ID_PILL						2
	#define GUIDE_ID_GRENADE					3
	#define GUIDE_ID_MOONLIGHT					4
	#define GUIDE_ID_FRIST						5//��������һ��أ�
	#define GUIDE_ID_ROLE_SKILL					6//�������ڶ���أ�
	#define GUIDE_ID_JEWEIL_SKILL				7//������������أ�
#endif

/*************************************************
��ʾ���
*************************************************/
#define			TIP_GAMING_START			31
#define			TIP_GAMING_END				49

/****************************************************
cartton��ض���
*****************************************************/
#define CARTOON_START						-999//��������
#define CARTOON_BAOXIANGGUO					1//�����
#define CARTOON_TONGYIANHE					2//ͨ���
#define CARTOON_NVERGUO						3//Ů����
#define CARTOON_HUOYANSHAN					4//����ɽ
#define CARTOON_LINGSHAN					5//��ɽ
#define CARTOON_END							999//��������
#define CARTOON_COUNT						7

/****************************************************
explode��ض���
*****************************************************/
#define B_EXPLODE							1//logo����
#define S_EXPLODE							2//load����
#define HANGER_EXPLODE						3//load����
#define HANGER_GOT_AWARD					HANGER_EXPLODE
#define BOMB_CIRCLE							100

/****************************************************
layer��ض���
*****************************************************/
#define LAYER_ID_LOGO						1//logo����
#define LAYER_ID_LOADING					2//load����
#define LAYER_ID_MAIN						3// ������
#define LAYER_ID_SETTING					4// ���ý���
#define LAYER_ID_HELP						5// ��������
#define LAYER_ID_BIG_GATE_MAP				6// ���ѡ�����
#define LAYER_ID_SMILE_GATE_SCENCE			7//С�ؿ�����
#define LAYER_ID_GATE_PAUSE					8// ��ͣ����
#define LAYER_ID_GAMING						9// ��Ϸ����
#define LAYER_ID_CARTOON					10// ����
#define LAYER_ID_PETPARK					11// ������
#define LAYER_ID_PROP_ROLE					12// ѡ��ѡ����
#define LAYER_ID_MAIN_APPEND				13// ���������ҳ
#define LAYER_ID_SHOP						14// �̳�
#define LAYER_ID_GAMEOVER					15// ��Ϸ����
#define LAYER_ID_CHALLENGE					16// ��ս
#define LAYER_ID_CHALLENGE_COUNT			17// ��ս����
#define LAYER_ID_PAUSE						18// ��ͣ
#define LAYER_ID_ROLE						19 // ѡ��ҳ��
#define LAYER_ID_REGISTER					20// ǩ��ҳ��
#define LAYER_ID_ROLE_INFORMATION			21// ѡ����ʾ��Ϣҳ
#define LAYER_ID_DRAW						22// �齱

/****************************************************
�궨�壺   ��ȡ��Ӧ�ؿ���tmx�ļ��Ķ������͵���ض�Ӧֵ
*****************************************************/
#define GAMECONTROL_TYPE_ROLE				1//�������� ����
#define GAMECONTROL_TYPE_NPC				2//�������� npc
#define GAMECONTROL_TYPE_SKILL				3//�������� ����
#define GAMECONTROL_TYPE_TARGET_STATIC		4//�������� ��̬Ŀ��
#define GAMECONTROL_TYPE_TARGET_DYNAMIC		5//�������� ��̬Ŀ��
#define GAMECONTROL_TYPE_PROP				6//�������� ����
#define GAMECONTROL_TYPE_CHIP				7//�������� ������Ƭ
#define GAMECONTROL_TYPE_PET				8//�������� ����
#define GAMECONTROL_TYPE_CARRIER			9//�������� Я���ߣ��ƶ䣩
#define GAMECONTROL_TYPE_INFORMATION		999//�������� �ؿ���Ϣ
/***************************************************
�ؿ���ض���
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
�Ƕ���ض���
***************************************************/
const double angleChange = 180;
const double angleLeft = 190;
const double angleRight = 350;
const double angleCenter = 270;
const double pi = 3.1415926;

/***************************************************
��ι�ϵ
****************************************************/
enum
{
	LAYER_ORDER_BACKGROUND =-999,//����
	LAYER_ORDER_CONTROL = 999// ���ܵ���ض���
};

/**************************************************
	��ɫ����			
	��ӽ�ɫ�й���ѡ�������ҳ����������һ����enumΪ0�� ʣ�°���˳��
***************************************************/
enum
{
	ROLE_TYPE_HULUWA = 0,
	//ROLE_TYPE_XIAOLONGNV = 0,// С��Ů
	ROLE_TYPE_TANGSENG,	//��ɮ
	ROLE_TYPE_ZHUBAJIE,// ��˽�
	ROLE_TYPE_SHAHESHANG,// ɳ����
	ROLE_TYPE_SUNWUKONG, //�����
	ROLE_TYPE_XIAOLONGNV,// С��Ů
	ROLE_TYPE_COUNT// ��ɫ����
};
#define  ROLE_TYPE_START				ROLE_TYPE_TANGSENG				//��Ϸ��ʼ��ɫ


/**************************************************
	��̬Ŀ�������
***************************************************/
enum
{
	TARGET_TYPE_GOLDEN = 0,//�ƽ�
	TARGET_TYPE_STONE,//ʯͷ
	TARGET_TYPE_DIAMOND,//��ʯ
	TARGET_TYPE_COAL,//ú��
	TARGET_TYPE_TRUNK,//���� 
	TARGET_TYPE_JEWEL,//��ʯ
	TARGET_TYPE_FOOD,//��ʳ
	TARGET_TYPE_BOMB,//ը��
	TARGET_TYPE_BOX,//�������
	TARGET_TYPE_COUNT,//����Ŀ�����͵�����
};

/**************************************************
	��̬Ŀ�����ж����id
***************************************************/
enum
{
	TARGET_ID_BOMB = 4001,//ը��
	TARGET_ID_BOX,//�������
	TARGET_ID_GOLDEN_S,//�ƽ�s
	TARGET_ID_GOLDEN_M,//�ƽ�m
	TARGET_ID_GOLDEN_B,//�ƽ�b
	TARGET_ID_STONE_S,//ʯͷs
	TARGET_ID_STONE_M,//ʯͷm
	TARGET_ID_STONE_B,//ʯͷb
	TARGET_ID_DIAMOND,//��ʯ
	TARGET_ID_COAL,//ú��
	TARGET_ID_TRUNK,//���� 
	TARGET_ID_JEWEL_BLUE,//����ʯ
	TARGET_ID_JEWEL_RED,//�챦ʯ
	TARGET_ID_JEWEL_GREEN,//�̱�ʯ
	TARGET_ID_JEWEL_YELLOW,//�Ʊ�ʯ
	TARGET_ID_JEWEL_PURPLE,//�ϱ�ʯ
	TARGET_ID_FOOD,//��ʳ
	TARGET_ID_COUNT,//����Ŀ�����͵�����
};

/*****************************************************
	��̬Ŀ�����ж����id
*******************************************************/
enum
{
	DYNAMIC_ID_TYPE_START = 5000,
	DYNAMIC_ID_XIAOZUANFENG = 5001,// С���
	DYNAMIC_ID_JINGXIGUI,// ��ϸ��
	DYNAMIC_ID_LINGLICHONG,// ������
	DYNAMIC_ID_LINGGANDAWANG,// ��д���
	DYNAMIC_ID_YUMIANGONGZHU,// ���湫��
	DYNAMIC_ID_NIUMOWANG,// ţħ��
	DYNAMIC_ID_XIAOCHOUYU,// С����
	DYNAMIC_ID_BIRD,// ��
	DYNAMIC_ID_PEARL_SHELL,// ���鱴
	DYNAMIC_ID_SHELL,// ����
	DYNAMIC_ID_GOLDEN,// �ƽ�
	DYNAMIC_ID_STONE,// ʯͷ
	DYNAMIC_ID_BAT,// ����
	DYNAMIC_ID_SPIDER,// ֩��
	DYNAMIC_ID_HUOHUALIAN,// ������
	DYNAMIC_ID_HUOHUALIAN_OTHER,// ������(��)
	DYNAMIC_ID_STAR,// ����
	DYNAMIC_ID_COUNT
};


/***************************************************
�ƶ�����
****************************************************/
enum
{
	CARRIER_ID_CLOUD = 9001,// �ƶ�Я����̬Ŀ��
	CARRIER_ID_BLACK_CLOUD// �ƶ�Я����̬����
};


/**************************************************
	���ߵ�����
***************************************************/
enum
{
	PROP_TYPE_COIN = 0,				// ͭǮ
	PROP_TYPE_INGOT,				// Ԫ��
	PROP_TYPE_GRENADE,				// ը��
	PROP_TYPE_VIGOROUSLY_PILL,		// ������
	PROP_TYPE_MOONLIGHT,			// �¹ⱦ��
	PROP_TYPE_ALIGNMENT,			// ��׼��
	PROP_TYPE_BUDDAHA,				// ���
	PROP_TYPE_FOOD,					// ��ʳ
	PROP_TYPE_MEET,					// ��
	PROP_TYPE_JEWEL_BLUE,			// ����ʯ
	PROP_TYPE_JEWEL_RED,			// �챦ʯ
	PROP_TYPE_JEWEL_GREEN,			// �̱�ʯ
	PROP_TYPE_JEWEL_YELLOW,			// �Ʊ�ʯ
	PROP_TYPE_JEWEL_PURPLE,			// �ϱ�ʯ
	PROP_TYPE_COUNT,
};

/***************************************************
	���ﾫ��
****************************************************/
enum
{
	PET_ELEMENT_XIAOZUANFENG = 0,// С������
	PET_ELEMENT_JINGXIGUI,// ��ϸ��
	PET_ELEMENT_LINGLICHONG,// ������
	PET_ELEMENT_LINGGANDAWANG,// ��д���
	PET_ELEMENT_YUMIANGONGZHU,// ���湫��
	PET_ELEMENT_NIUMOWANG,// ţħ��
	PET_ELEMENT_COUNT
};

/**************************************************
	����״̬
***************************************************/
enum
{
	HANGER_STATUS_SWAYING = 0,// ҡ��
	//HANGER_STATUS_SWAYING_STOP_THROW,// ��ֹ�����ӵ�ҡ��״̬
	//HANGER_STATUS_INTERSECT_TARGET,// ����������ץȡ��
	//HANGER_STATUS_INTERSECT_WALL,// ��������ǽ
	HANGER_STATUS_PULL_HAVING,// ���� ץ��
	HANGER_STATUS_PULL_UNHAVING,// ���� ûץ��
	HANGER_STATUS_THROW,// ��
	HANGER_STATUS_PAUSE// ��ͣ
};

enum
{
	TARGET_SPEED_TYPE_S = 2,
	TARGET_SPEED_TYPE_M,
	TARGET_SPEED_TYPE_B
};


/**************************************************
	��Ʒ����ID
***************************************************/
enum
{
	SKILL_ID_NO = 0,
	SKILL_ID_GRENADE,// ը��
	SKILL_ID_VIGOROUSLY_PILL,// ������
	SKILL_ID_MOONLIGHT// �¹ⱦ��
};

/**************************************************
	��ʯ����ID
***************************************************/
enum
{
	SKILL_ID_JEWEL_DROP = 0,// ��ʯ���� ��ͭǮ
	SKILL_ID_JEWEL_BALL,// ��ʯ���� ������
	SKILL_ID_JEWEL_FIVE_HANGER,// ��ʯ����������Ӽ���
	SKILL_ID_JEWEL_MAGNET,// ��ʯ���� ����ʯ(��)
	//SKILL_ID_JEWEL_DIZZY,// ��ʯ���� ��
	//SKILL_ID_JEWEL_GOURD,// ��ʯ���� �Ͻ��«(����)
	SKILL_ID_JEWEL_COUNT// ��ʯ���ܵ�����
};

/**************************************************
	�Ʒѵ�ID
***************************************************/
enum
{
	PAY_ID_GENUINE = 1,//������֤
	PAY_ID_TIMEMACHINE,// ʱ���
	PAY_ID_SUNWUKONG,// �����
	PAY_ID_BUDDAHA,// ���
	PAY_ID_HULUWA,// ��«��
	PAY_ID_MEET,// ��
	PAY_ID_JEWEL,// ��ʯ����
	PAY_ID_VALUE_PACKAGE,// ��ֵ���
	PAY_ID_GOLDEN_PACKAGE,// �ƽ����
};

class Global
{
public:
	static Global * getInstance(void);
	~Global(void);

	void getPayAwardByPayId(int _payId);

	int getPetElementIdByHideGateId(int _hideGateId, cocos2d::CCArray * _elementIds);

	int getChallengCostByChallengeType(int _challengeType);

	int getGenuineGateId(void);// ���������֤�Ĺؿ�

	int getWordsIdByMapIdAndRoleId(int _mapId, int _roleId);// ���ѡ��ؿ��������Ӧ�ĶԻ�id��

	int getTimeByChallengeLevel(void);// �����ս�ȼ���ʱ��
	int getChallengeLevel(void);// �����ս�Ĳ��
	void setChallengeLevel(int _b);// ������սģʽ�Ĳ��
	int getChallengeTimeLevel(void);// ���սģʽ����ʱ��Ĳ����
	void setChallengeTimeLevel(int _level); // ������սģʽ����ʱ��Ĳ����
	int getChallengeLevelType(void);// �����ս������
	void setChallengeLevelType(int _type);// ������ս������
	int getNextChallengeGateId(void);// ����´���սģʽ��id��
	int getChallengeCountSum(void);
	void setChallengeCountSum(int _sum);

	int getRoleSpeedByRoleId(int _roleId);// ͨ������id����ٶ�
	int getRoleSwapSpeedByRoleId(int _roleId);// ͨ������id���ҡ���ٶ�

	int getPetHeartFull(int _petElementId);	// ��ó������ɵ����谮����	

	int getCartoonId(void);// ���Ҫ���ŵ�������
	void setCartoonId(int _gateId);// ����Ҫ���ŵ������ĺ�

	bool getIsBuyThing(void);// �Ƿ���Ϸ��ʼǰ������
	void setIsBuyThing(bool _b);// �Ƿ���Ϸ��ʼǰ������

	bool getCurrGameLayerLoadDynamicTarget(int _dynamicTargetId);
	void setCurrGameLayerLoadDynamicTarget(int _dynamicTargetId, bool _isLoaded);
	void initCurrGameLayerLoadDynamicTarget(void);
	int getSimleGateNumAndGateIdBySelectBigGateType(cocos2d::CCArray * _gateIds);
	int getMapIdByGateId(int _gateId);// ͨ��gateid�Ż���������ڵ�map��id��
	int getSmallGateIdByGateId(int _gateId);// ͨ��gateid�Ż��С�صĺ�
	void setSelectGateType(int _gateType);
	int getSelectGateType(void);
	void setSelectGateId(int _gateId);// ����ѡ�еĹؿ�id�� 
	int getSelectGateId(void);// ���ѡ�еĹؿ�id�� 
	void setSelectGateNextGateId(int _nextGateId);// ����ѡ�еĹؿ���һ��id�� 
	int getSelectGateNextGateId(void);// ���ѡ�еĹؿ���һ��id�� 
	int getSelectRoleId(void);// ���ѡ������Ľ�ɫ
	void setSelectRoleId(int _roleId);// ����ѡ������Ľ�ɫ
	int getCurrGuideId(void);// ��ǰ�������ؿ��ĺ�  �����-1��ʾ���������ؿ�
	void setCurrGuideId(int _guideId);

	int getSceneSpeedByMapId(int _mapId);// ͨ��map��id����ĳ����ٶ�

	int getRolePriceByRoleId(int _roleId);// ��ý�����Ӧ��������ļ۸�

/**************************************************
��ȡ����ͬʱ����Ĵ���
**************************************************/
	double getJewelSkillScale(void);
	void setJewelSkillScale(double _scale);
/**************************************************
	��ȡ��������ʱ��ȷ�����ƶ��ٶȲ��������첽����
******************************************************/	
	float getJewelSkillDistance(void);
	void setJewelSkillDistance(float _distance);

	void initValueTimes(void);// ��ʼ����ý����ı���
	void setValueTimes(int _targetType, int _times);// ���⽱���ı���
	int getPropAwardNumById(int _propId);// ��ö�Ӧ����id�Ĺؿ����ֵ
	void appendPropAwardGet(int _propId, int _num);// ֱ�����
	void appendPropAwardGet(int _targetType, int _propId, int _num);// ����Ŀ���������
	void initPropAwardGet(void);// ��ʼ���ؿ���õĽ���
	void initPetElementGet(void);// ��ʼ����õĳ��ﾫ��
	void appendPetElementGet(int _petElementId, int num);// ��ӻ�õĳ����ֵ
	int getPetElementGetById(int _petElementId);// ��ó��ﾫ���Ļ�õ�ֵ
	bool getPetIsOpenByIdAndNum(int _petElementId, int num);

	int getGetJewelCount(void);// ��õı�ʯ��ͳ����
	int getMaxContinusesCount(void);// ������������
	int getContinuesCount(void);// �����������
	void setContinuesCount(int _appendNum);// ������������
	void initContinuesCount(void);// ������������

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

	int getGameControlTypeById(int _id);// �ر��ļ���ȡ��������

#ifdef							GOLDEN_MINER_2_VERSION_TIME
	float getTimeRatio(void);
	void setTimeRatio(float _f);
#endif

	//����
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

	int cartoonId;// ��ͨid   �����0���ǲ����ſ�ͨ
	int currGuideId;// ��ǰ�������ؿ��ĺ�  �����-1��ʾ���������ؿ�

	int selectGateType;	// ѡ��Ĵ�ص�����
	int selectRoleId;// ѡ����˵Ľ�ɫ
	int selectGateId;// ѡ�йؿ���id��
	int nextGateId;// ��һ�صĹؿ���id��

	bool currGameLayerLoadDynamicTarget[DYNAMIC_ID_COUNT-DYNAMIC_ID_XIAOZUANFENG];// ��ǰ��Ϸ���ص��Ҷ��������Ƿ��Ѿ�����
	int petElementGet[PET_ELEMENT_COUNT];// ��õ���������
	int propAwardGet[PROP_TYPE_COUNT];//ץ����Ӧ�Ŀ������
	int propAwardTimes[TARGET_TYPE_COUNT];//��ǰ��Ӧprop�Ļ�ñ���(Ŀǰ����Ի������prop���� )

/**************************************************
��ȡ����ͬʱ����Ĵ���
******************************************************/
	double jewelSkillScale;// ��ʯ���ܴ�����Ӧ����ķ�������
/**************************************************
	��ȡ��������ʱ��ȷ�����ƶ��ٶȲ��������첽����
******************************************************/
	float jewelSkillDistance;// ��ʯ���ܴ�����Ӧ����ķ�������

	double centreX;// ץ��ҡ�ڸ��ݵĵ�x����
	double centreY;// ץ��ҡ�ڸ��ݵĵ�y����

	int continuousCount;// ��������
	int maxContinuesCount;// ���������
	int getJewelCount;// ��õı�ʯ��ͳ����

	//double hangerStartX;// ���ӳ�ʼ����ʼ��x����
	//double hangerStartY;// ���ӳ�ʼ����ʼ��y����
	//double hangerCurrX;// ���ӵ�ǰ��x����
	//double hangerCurrY;// ���ӵ�ǰ��y����
	//double hangerAngle;// ���ӵ�ǰ�ĽǶ�
	int hangerStatus;// ���ӵ�ǰ��״̬
	//double hangerDistanceToRope;// ���������ӽڵ�ľ���
	//double hangerDistanceToCentre;// ���������ĵľ���
	//bool hangerCanThrow;
};

#endif
