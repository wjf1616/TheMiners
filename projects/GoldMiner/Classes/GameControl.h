#ifndef __GAMECONTROL_H__
#define __GAMECONTROL_H__

#include "cocos-ext.h"
#include "cocos2d.h"
#include "Player.h"
#include "Gate.h"
#include "Role.h"
#include "Global.h"
#include "JewelSkillSprite.h"
#include "GoldenMinerScene.h"
#include "RoleSkillEffect.h"
#include "CountDownEffect.h"
#include "LastTimeCountEffect.h"
#include "Finger.h"
#include "PowerBuff.h"

#define				SCHEDULE_TIMES					60

#define			GAMEING_NORMAL					1
#define			GAMEING_GUIDE					2
#define			GAMEING_CHALLENGE				3

class Explosive;
class SpotLightLayer;

class GameControl :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	GameControl(void);
	~GameControl(void);

	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameControl, create);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	virtual void keyBackClicked(void);

	void onMenuItemProp1Clicked(cocos2d::CCObject * pSender);
	void onMenuItemProp2Clicked(cocos2d::CCObject * pSender);
	void onMenuItemProp3Clicked(cocos2d::CCObject * pSender);
	void onMenuItemSkillClicked(cocos2d::CCObject * pSender);
	void onMenuItemPauseClicked(cocos2d::CCObject * pSender);
	void onMenuItemGemClicked(cocos2d::CCObject * pSender);

	void setGameControl(int _gateId, int roleType);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	virtual void setBackGround(bool _isBackGround);
	void setBackGroundWithOutGreyLayer(bool _isBackGround);

	void setLiZiTeXiaoVisible(bool _b);
	
	virtual void onExit();

	virtual void doAction(float _f);

	int getType(void);
	int getCurrMapId(void);
	virtual void setCurrMapId(int _currMapId);
	int getCurrSceneId(void);
	virtual void setCurrSceneId(int _currSceneId);
	void setValueTimes(int _targetType, int _times);
	void setIsTiming(bool _isTiming);
	void setIsJewel(bool _isJewel);
	void setIsDynamicTargetMoving(bool _isDynamicTargetMoving);
	void addExplode(int _type, float _x, float _y);
	void setLiuGuangVisiable(int _index, bool _b);
	void addExplosive(Explosive * _explosive);
	void setLeaveTime(int _leaveTime);
	void setLeastCoin(int _leastCoin);// 设置需要最少的铜钱值
	int getLeastCoin(void);

	virtual void finishRoleSkillEffect(void);
	void finishDraw(void);
	void finishJewelSkillEffect(void);

	//void doAnimationCompleted(void);
	void setTipId(int _tipId);

	cocos2d::CCPoint getGetCoinLabelPosition(void);

	void startSelf(void);
	void setLoadingLayer(cocos2d::CCLayer * _layer);

#ifdef						GOLDEN_MINER_2_VERSION_PAY
	// 正版验证  
	void doGenuine(void);
#endif
	void genuineSuccess(void);
	void genuineFailed(void);
	void payJewelSuccess(void);
	void payJewelFailed(void);

	int getMinUnhavingJewelId(void);

	int getCoinNum;
	int getIngotNum;
	int getStarNum;
	Gate * gate;// 当前关卡指针
	Role * role;// 当前角色指针
	//int carryTargetType;// 当前被抓取对象的类型（没有抓取为0）
	//void * carryTargetPoint;// 当前被抓取对象的地址引用
	int jewelSkillId;// 出发的宝石技能的id
	JewelSkillSprite * jewelSkillSprite;// 技能球
	//cocos2d::CCSprite *	biaozhunxian;
protected:
	bool isPayJewel;
	bool isGenuine;// 是否进行正版验证
	bool isBuddaha;
	bool isBuddahaTip;
	bool isGameOver;// 是否已经游戏结束

	cocos2d::CCLayer * loadingLayer;

	int tipId;
	bool isNewGate;
	bool isOpenChallenge;
	bool isOpenHideGate;
	bool isPropFull;
	bool isFoodFull;
	bool checkHideGateOpen(int _gateId);
	// 人物开启相关
	int isNewRole;
	bool isNewRoleOpenByRoleId(int _roleId);

	bool isUpdate;

	cocos2d::extension::CCBAnimationManager *mAnimationManager;// 动画管理器
	
	cocos2d::CCLabelAtlas * leastCoinLabel;
	cocos2d::CCLabelAtlas * leaveTimeLabel;
	cocos2d::CCLabelAtlas * getCoinLabel;
	cocos2d::CCArray * jewelSprites;// 记录当前游戏页面宝石情况
	cocos2d::CCArray * explodes;// 爆炸效果
	cocos2d::CCArray * liuGuang;// 流光效果
	PowerBuff * powerBuff;
	LastTimeCountEffect * lastTimeCountDownEffect;

	bool isPause;

	//GameAppend * gameAppend;// 附加页面
	//RoleSkillEffect * roleSkillEffect;// 附加页面
	//CountDownEffect * countDownEffect;
	int leaveTime;// 剩余时间
	int leastCoin;// 通关的铜钱值门槛
	int currMapId;// 当前关卡id号
	int currSceneId;// 当前场景号
	bool isTiming;// 是否计时
	bool isJewel;// 是否在下宝石的特技状态
#ifdef													GOLDEN_MINER_2_VERSION_TIME
	float timeCount;
#else
	int timeCount;// 时间计时
#endif
	int getCoinTmp;
	bool isStartCountDownEffect;// 是否播放了开始动画

	std::string str;
	int currPropOwn[PROP_TYPE_COUNT];//实时拥有的prop数量

	bool isBackGroud;//是否成为背景层（添加灰色层）
	cocos2d::CCLayerColor * greyLayer;// 灰色层
	bool isDoJewelSkill;// 是否要释放宝石技能

	bool isStrongStatus;// 是否在大力丸状态
#ifdef													GOLDEN_MINER_2_VERSION_TIME
	float strongStatusTimeCount;// 大力丸时间计数
#else
	int strongStatusTimeCount;// 大力丸时间计数
#endif

	Explosive * explosive;
	//bool isZhaDanStatus;// 是否炸弹的状态
	//int zhaDanStatusTimeCount;// 炸弹的计时

	bool isMoonLightStatus;// 是否炸弹的状态
#ifdef													GOLDEN_MINER_2_VERSION_TIME
	float moonLightStatusTimeCount;// 炸弹的计时
#else
	int moonLightStatusTimeCount;// 炸弹的计时
#endif

	void doLiuGuang(float _f);
	void doSkills(int _skillId);
	void releaseSkills(int _skillId);
	virtual void doJewelSkill(void);
	void updateJewelSkill(float _f);
	void checkJewelSkill(float _f);
	void intersectCheck(void);
	void ccTouchesEnded(CCSet* touches, CCEvent* pevent);
	void setGetCoinLabel(void);// 设置需要最少的铜钱值
	virtual void gameOver(void);
	int getIngotByCoin(int _coin);
	int getStarNumByCoinAndGate(int _getCoinNum, int _leastCoin);
	void doExplode(float _f);
	cocos2d::CCLabelAtlas * getPropNumLable(int _propId);

	//void changeMiaoZhunXianPosition(void);

	// 获得技能宝石 粒子特效
	bool isJewelAppendEffectsPause;
	CCArray * jewelAppendEffects;
	//void addNewJewel(int _propType);
	//int addNewJewelType;
	//float flyTime;
	//CCParticleSystemQuad * newJewelSystem;
	// 获得技能宝石 粒子特效
	void addJewelBomb(int _propType);
	CCParticleSystemQuad * jewelBombSystem;

	//// 获得积分的粒子特效和得分显示
	bool isScoreAppendEffectsPause;
	CCArray * scoreAppendEffects;
	virtual void scoreAppend(float _f);
	//void addScore(int _score);
	//float flyTimeScore;
	//CCParticleSystemQuad * addScoreSystem;
	//CCSprite * addScoreSprite;
	//cocos2d::CCLabelAtlas * addScoreNum;

	// 连击的显示
	void checkContinueCount(float _f);
	void setContinueCount(int _countinueCount);
	int countinueCount;
	CCSprite * countinueCountSprite;
	cocos2d::CCLabelAtlas * countinueCountNum;
	// 连击失败
	cocos2d::CCSprite * countinueFailed;

	// 时间技能添加
	CCArray * timeAppendEffects;

	// 对话
	bool doWordsById(int _id);
	bool isWords;
	cocos2d::CCSprite * roleWords;
	cocos2d::CCSprite * wuguiWords;

	// 进度条
	float progressW;
	float progressH;
	float progressX;

	// 是否更新道具数量
	bool isUpdateProp;
	//int tmpProp1Num;
	//int tmpProp2Num;
	//int tmpProp3Num;

	// 类型
	int type;

private:

	//float a;

	//int b;
	//int c;
	//int d;

	//int bb;
	//int cc;
	//double dd;

	//cocos2d::CCLabelTTF  * jewel;// 
	//cocos2d::CCLabelTTF  * roleSpeed;// 
	//cocos2d::CCLabelTTF  * sceneSpeed;// 
	//cocos2d::CCLabelTTF  * roleSwaySpeed;// 

};


// 引导关卡
class GuideLayer :
	public GameControl
{
public:
	GuideLayer(void);
	~GuideLayer(void);

	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GuideLayer, create);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	virtual void keyBackClicked(void);

	void onMenuItemProp1Clicked(cocos2d::CCObject * pSender);
	void onMenuItemProp2Clicked(cocos2d::CCObject * pSender);
	void onMenuItemProp3Clicked(cocos2d::CCObject * pSender);
	void onMenuItemSkillClicked(cocos2d::CCObject * pSender);
	void onMenuItemPauseClicked(cocos2d::CCObject * pSender);

	void setGuideLayer(int _guideId);


	virtual void setCurrMapId(int _currMapId);
	virtual void setCurrSceneId(int _currSceneId);

	virtual void setBackGround(bool _isBackGround);
	
	virtual void finishRoleSkillEffect(void);

	virtual void doAction(float _f);

	void setStepNum(int _step);
	void addStepTarget(CCObject * p);

	bool isIntroduce;
	bool isTouchIntroduce;
	bool checkIsTouchIntroduce;
private:
	int step;
	int checkStep;
	bool isStepGetAward;
	CCArray * stepTargets;
	void setCheckStep(int _checkStep);

	bool isJiangLiTip;
	int guideId;
	Finger * finger;
	int isFinger;
	bool isCheck;
	bool isTouchButton;
	SpotLightLayer * spotLightLayer;
	//cocos2d::CCLayerColor * greyLayer1;// 灰色层
	//cocos2d::CCLayerColor * greyLayer2;// 灰色层

	int targetTotalNum;

	//int playerPropNum[PROP_TYPE_COUNT];
	bool touchCost[GUIDE_ID_JEWEIL_SKILL];

	void ccTouchesEnded(CCSet* touches, CCEvent* pevent);
	virtual void gameOver(void);
	bool myIntersectCheck(void);
	void myGameOver(void);
	void getAward(void);
	void doSkills(int _skillId);
	
	virtual void doJewelSkill(void);
};


// 无限关卡
class ChallengeLayer :
	public GameControl
{
public:
	ChallengeLayer(void);
	~ChallengeLayer(void);

	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ChallengeLayer, create);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void setChallengeLayer(int _gateId, int roleType);

	int getChallengeAwardByPropId(int _id);

	virtual void keyBackClicked(void);

	virtual void finishRoleSkillEffect(void);
	virtual void setBackGround(bool _isBackGround);
	virtual void doAction(float _f);

	virtual void scoreAppend(float _f);
	virtual void setCurrMapId(int _currMapId);
	virtual void setCurrSceneId(int _currSceneId);

	void onIsHavingDateCompleted(cocos2d::CCNode *sender, void *data);
	void onUpdateChallengeDateCompleted(cocos2d::CCNode *sender, void *data);
	void onGetChallengeDateCompleted(cocos2d::CCNode *sender, void *data);

	void payTimeAgainSuccess(void);
	void payTimeAgainFailed(void);

	bool isIntroduce;
private:
	bool isTimeAgain;
	bool isConnectNet;
	int guideId;
	Finger * finger;
	int isFinger;
	bool isCheck;
	bool isTouchButton;

	bool isUpdateSum;

	virtual void gameOver(void);
	virtual void doJewelSkill(void);

	void setChallengCountSum(void);
	CCLabelAtlas * challengeCountSumLabel;

};

#endif