#include "GameControl.h"
#include "Explode.h"
#include "Sensitization.h"
#include "ScoreAppendEffect.h"
#include "JewelAppendEffect.h"
#include "PromptLayer.h"
#include "GameAppend.h"
#include "LoadingLayer.h"
#include "TimeAppendEffect.h"
#include "Explosive.h"
#include "CartoonLayer.h"
#include "PayService.h"
#include "CostLayer.h"
#include "TemporaryPromptLayer.h"
#include "SpotLightLayer.h"
#include "Buddaha.h"
#include "NetWork.h"
#include "GMJson.h"


#define			VIGOROUSLY_PILL_TIME			15			// 大力丸持续的时间长度
#define			GRENADE_TIME					20
#define			VIGOROUSLY_PILL_POWER			30			// 大力丸的加速度
#define			PROP_NUM_TAG					10086
#define			PROP_PILL_TAG					11086
#define			PROP_GRENADE_TAG				12086
#define			PROP_MOONLIGHT_TAG				13086

#define			ADD_NEW_SCORE_FLY_TIME_LONG		0.3

#define			RED_JEWEL_BLUE_X				766.4
#define			RED_JEWEL_RED_X					754.1
#define			RED_JEWEL_GREEN_X				717.8
#define			RED_JEWEL_YELLOW_X				707.3
#define			RED_JEWEL_PURPLE_X				736.1
#define			RED_JEWEL_BLUE_Y				240.8
#define			RED_JEWEL_RED_Y					207.3
#define			RED_JEWEL_GREEN_Y				207.9
#define			RED_JEWEL_YELLOW_Y				240.1
#define			RED_JEWEL_PURPLE_Y				264.4

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cs;

static const ccColor4B myGrey4 = {0,0,0,200};

GameControl::GameControl(void)
	: mAnimationManager(NULL)
	,jewelSkillSprite(NULL)
	//,carryTargetPoint(NULL)
	,leaveTimeLabel(NULL)
	,leastCoinLabel(NULL)
	,getCoinLabel(NULL)
	//,zhaDanSprite(NULL)
	//,biaozhunxian(NULL)
	,scoreAppendEffects(NULL)
	//,addScoreSystem(NULL)
	,countinueCountSprite(NULL)
	,jewelBombSystem(NULL)
	,jewelAppendEffects(NULL)
	,isScoreAppendEffectsPause(false)
	,isJewelAppendEffectsPause(false)
	,loadingLayer(NULL)
	,isGameOver(false)
	,timeAppendEffects(NULL)
	,powerBuff(NULL)
{
	isPayJewel = false;
	isBuddaha = false;
	isBuddahaTip = false;
	countinueCount = 0;
	explosive = NULL;
	countinueFailed = NULL;
	isNewGate = true;
	isOpenChallenge = true;
	isOpenHideGate = false;
	isFoodFull = false;
	isPropFull = false;
	isNewRole = ROLE_TYPE_ZHUBAJIE;
	isUpdate = false;
	tipId = 0;
	progressW = 0;
	progressH = 0;
	isUpdateProp = false;
	type = GAMEING_NORMAL;
	jewelAppendEffects = new CCArray();

	Player::getInstance()->setGameLayer(this);
	Player::getInstance()->setGameLayerIsPause(false);
#ifdef										GOLDEN_MINER_2_VERSION_TIME
	Global::getInstance()->setTimeRatio(1);
#endif

	isGenuine = false;
}


void GameControl::setGameControl(int _gateId, int roleType)
{	
//	a = 3;
//b = 0;
//c = 0;
//d = 0;
	if(_gateId %18 > 8 && _gateId%18 < 12)
	{
		isOpenHideGate = true;
	}

	setVisible(true);

	Global::getInstance()->setCurrGuideId(-1);
	// 技能状态初始化
	isStrongStatus = false;// 不在大力丸状态
	strongStatusTimeCount = 0;// 大力丸时间计数
	//isZhaDanStatus = false;// 不在大力丸状态
	//zhaDanStatusTimeCount = 0;// 大力丸时间计数
	isMoonLightStatus = false;// 不在大力丸状态
	moonLightStatusTimeCount = 0;// 大力丸时间计数
	isJewel = false;
	isTiming = true;
	isStartCountDownEffect = false;
	//flyTimeScore = ADD_NEW_SCORE_FLY_TIME_LONG;
	//flyTimeContinue = ADD_NEW_SCORE_FLY_TIME_LONG;

	getCoinTmp = -1;
	isDoJewelSkill = false;
	isBackGroud = false;

#ifdef								GOLDEN_MINER_2_VERSION_TIME
	timeCount = -10000.0;
#else
	timeCount = SCHEDULE_TIMES;
#endif
	//addNewJewelType = -1;
	// 爆炸对象初始化
	explodes = new CCArray();

	// 初始化当前道具的拥有情况
	for (int i = PROP_TYPE_COIN; i < PROP_TYPE_COUNT; i++)
	{
		if (i == PROP_TYPE_COIN)
		{
			currPropOwn[i] = 0;
		}
		else
		{
			currPropOwn[i] = Player::getInstance()->getPropNum(i);
		}
	}

	// 初始化对应物品的价值倍数
	Global::getInstance()->initContinuesCount();
	countinueCount = Global::getInstance()->getContinuesCount();
	Global::getInstance()->initValueTimes();
	Global::getInstance()->initPropAwardGet();
	Global::getInstance()->initPetElementGet();
	Global::getInstance()->initCurrGameLayerLoadDynamicTarget();

	// 根据关卡id创建关卡
	gate = Gate::getInstance(_gateId, this);

	// 对已经拥有的道具进行初始化
	role = Role::getInstance(roleType, this, 325, 383, 400, 356, 0.8);//(roleType, this, 325, 380, 400, 350, 0.8);
	//role = Role::getInstance(roleType, this, 400, 392, 400, 350, 0.8);
	role->retain();

	CCSprite * _tmp = NULL;

	_tmp = CCSprite::create("youxi/xiexian.png");
	_tmp->setPosition(ccp(getChildByTag(3)->getPositionX() - 6, getChildByTag(3)->getPositionY() + 10));
	addChild(_tmp);
	jewelSkillId = -1;

	//CCSize s = CCDirector::sharedDirector()->getWinSize();  
	//jewel = CCLabelTTF ::create("","Arial",22);
	//jewel->setPosition(ccp(300, s.height - 20));
	//addChild(jewel); 
	//roleSpeed = CCLabelTTF ::create("","Arial",22);
	//roleSpeed->setPosition(ccp(400, s.height - 60));
	//addChild(roleSpeed, 2*LAYER_ORDER_CONTROL); 
	//sceneSpeed = CCLabelTTF ::create("","Arial",22);
	//sceneSpeed->setPosition(ccp(400, s.height - 100));
	//addChild(sceneSpeed, 2*LAYER_ORDER_CONTROL); 
	//roleSwaySpeed = CCLabelTTF ::create("","Arial",22);
	//roleSwaySpeed->setPosition(ccp(400, s.height - 140));
	//addChild(roleSwaySpeed, 2*LAYER_ORDER_CONTROL); 

	greyLayer = CCLayerColor::create(myGrey4);
	greyLayer->retain();

	if (Player::getInstance()->getPropNum(PROP_TYPE_ALIGNMENT) == 1)
	{
		role->setIsHaveAlignment(true);
		//// 瞄准线
		//biaozhunxian = CCSprite::create("youxi/xian2.png");
		//biaozhunxian->setScaleX(0.65);
		//addChild(biaozhunxian, LAYER_ORDER_CONTROL-2);
		Player::getInstance()->appendPropNum(PROP_TYPE_ALIGNMENT, -1);
		Player::getInstance()->savePropNum(PROP_TYPE_ALIGNMENT, -1);
		//Player::getInstance()->appendPropNum(PROP_TYPE_ALIGNMENT ,-1);
		//Player::getInstance()->savePropNum(PROP_TYPE_ALIGNMENT ,-1);
	}
	else
	{
		role->setIsHaveAlignment(false);
	}

	getChildByTag(999)->setZOrder(LAYER_ORDER_CONTROL);
#ifdef										GAME_LAYER_JEWEL_IS_BUTTON
#else
	getChildByTag(4)->setZOrder(LAYER_ORDER_CONTROL);
#endif
	getChildByTag(5)->setZOrder(LAYER_ORDER_CONTROL);//左上方
	getChildByTag(5)->addChild(getPropNumLable(PROP_TYPE_GRENADE),1, PROP_NUM_TAG);	
	getChildByTag(6)->setZOrder(LAYER_ORDER_CONTROL);//左中间
	getChildByTag(6)->addChild(getPropNumLable(PROP_TYPE_VIGOROUSLY_PILL),1, PROP_NUM_TAG);	
	getChildByTag(7)->setZOrder(LAYER_ORDER_CONTROL);//左下角
	getChildByTag(7)->addChild(getPropNumLable(PROP_TYPE_MOONLIGHT),1,  PROP_NUM_TAG);

	_tmp = CCSprite::create("youxi/zhadan.png");
	_tmp->setPosition(ccp(58, 281));
	_tmp->setScale(0.6);
	//_tmp->setOpacity(175);
	addChild(_tmp, LAYER_ORDER_CONTROL);
	_tmp = CCSprite::create("youxi/liliang.png");
	_tmp->setPosition(ccp(58, 191));
	_tmp->setScale(0.6);
	//_tmp->setOpacity(175);
	addChild(_tmp, LAYER_ORDER_CONTROL);
	_tmp = CCSprite::create("youxi/shalou.png");
	_tmp->setPosition(ccp(58, 96));
	_tmp->setScale(0.6);
	//_tmp->setOpacity(175);
	addChild(_tmp, LAYER_ORDER_CONTROL);
	liuGuang = new CCArray();
	liuGuang->addObject(new Sensitization(SENSITIZATION_TYPE_RECT));
	((Sensitization *)liuGuang->lastObject())->setPosition(ccp(58, 281));
	((Sensitization *)liuGuang->lastObject())->setVisible(false);
	addChild((Sensitization *)liuGuang->lastObject(), LAYER_ORDER_CONTROL);
	liuGuang->addObject(new Sensitization(SENSITIZATION_TYPE_RECT));
	((Sensitization *)liuGuang->lastObject())->setPosition(ccp(58, 191));
	((Sensitization *)liuGuang->lastObject())->setVisible(false);
	addChild((Sensitization *)liuGuang->lastObject(), LAYER_ORDER_CONTROL);
	liuGuang->addObject(new Sensitization(SENSITIZATION_TYPE_RECT));
	((Sensitization *)liuGuang->lastObject())->setPosition(ccp(58, 96));
	((Sensitization *)liuGuang->lastObject())->setVisible(false);
	addChild((Sensitization *)liuGuang->lastObject(), LAYER_ORDER_CONTROL);
	lastTimeCountDownEffect = new LastTimeCountEffect(0);
	lastTimeCountDownEffect->setPosition(ccp(getChildByTag(1)->getPositionX() - 3.5, getChildByTag(1)->getPositionY() - 2));
	lastTimeCountDownEffect->setVisible(false);
	addChild(lastTimeCountDownEffect, LAYER_ORDER_CONTROL);
	//liuGuang->addObject(new Sensitization(SENSITIZATION_TYPE_TIME));
	//((Sensitization *)liuGuang->lastObject())->setPosition(ccp(getChildByTag(1)->getPositionX() - 3.5, getChildByTag(1)->getPositionY() - 2));
	//((Sensitization *)liuGuang->lastObject())->setVisible(false);
	//addChild((Sensitization *)liuGuang->lastObject(), LAYER_ORDER_CONTROL);

	// 初始化宝石显示　　
	jewelSprites = new cocos2d::CCArray();
	jewelSprites->addObject(CCSprite::create("youxi/lan.png"));
	((CCSprite *)jewelSprites->lastObject())->setPosition(ccp(RED_JEWEL_BLUE_X, RED_JEWEL_BLUE_Y));
	jewelSprites->addObject(CCSprite::create("youxi/hong.png"));
	((CCSprite *)jewelSprites->lastObject())->setPosition(ccp(RED_JEWEL_RED_X, RED_JEWEL_RED_Y));
	jewelSprites->addObject(CCSprite::create("youxi/lv.png"));
	((CCSprite *)jewelSprites->lastObject())->setPosition(ccp(RED_JEWEL_GREEN_X, RED_JEWEL_GREEN_Y));
	jewelSprites->addObject(CCSprite::create("youxi/huang.png"));
	((CCSprite *)jewelSprites->lastObject())->setPosition(ccp(RED_JEWEL_YELLOW_X, RED_JEWEL_YELLOW_Y));
	jewelSprites->addObject(CCSprite::create("youxi/zi.png"));
	((CCSprite *)jewelSprites->lastObject())->setPosition(ccp(RED_JEWEL_PURPLE_X, RED_JEWEL_PURPLE_Y));
	for (int i = 0; i <= (PROP_TYPE_JEWEL_PURPLE - PROP_TYPE_JEWEL_BLUE); i++)
	{
		addChild((CCSprite *)jewelSprites->objectAtIndex(i));
		if (0 == currPropOwn[i + PROP_TYPE_JEWEL_BLUE])
		{
			((CCSprite *)jewelSprites->objectAtIndex(i))->setVisible(false);
		}
		else
		{
			((CCSprite *)jewelSprites->objectAtIndex(i))->setVisible(true);
		}
		((CCSprite *)jewelSprites->objectAtIndex(i))->setZOrder(LAYER_ORDER_CONTROL);
	}

	progressW = getChildByTag(2)->getContentSize().width;
	progressH = getChildByTag(2)->getContentSize().height;
	progressX = getChildByTag(2)->getPositionX();
	((CCSprite *)getChildByTag(2))->setPositionX(progressX - progressW/2);
	((CCSprite *)getChildByTag(2))->setTextureRect(*new CCRect(0,0,0,0));

	//bb = role->getHanger()->getSpeedSelf();
	//cc = role->getHanger()->getSpeedScene();
	//dd = 1;

	if (loadingLayer != NULL)
	{
		setBackGroundWithOutGreyLayer(true);
		((LoadingLayer *)loadingLayer)->appendFinishLayerNum(1);
	}
	else
	{
		startSelf();
	}

	roleWords = NULL;
	isWords = false;
	if(type == GAMEING_NORMAL && Player::getInstance()->getMapLastRoleId(Global::getInstance()->getMapIdByGateId(Global::getInstance()->getSelectGateId())) != Global::getInstance()->getSelectRoleId())
	{
		isWords = doWordsById(Global::getInstance()->getWordsIdByMapIdAndRoleId(Global::getInstance()->getMapIdByGateId(Global::getInstance()->getSelectGateId()), Global::getInstance()->getSelectRoleId()));
	}
	//isWords = doWordsById(Global::getInstance()->getWordsIdByMapIdAndRoleId(Global::getInstance()->getMapIdByGateId(Global::getInstance()->getSelectGateId()), Global::getInstance()->getSelectRoleId()));


	// 添加宠物显示
	cs::Armature* armature;
	CCRepeatForever * repeat;
	CCNode * _tmpNode = CCNode::create();
	switch(Player::getInstance()->getSelectPet())
	{
	case PET_ELEMENT_JINGXIGUI:
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_JINGXIGUI))
		{
			// 加载
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("jingxigui", "", "flash/jingxigui/jingxigui.png", "flash/jingxigui/jingxigui.plist", "flash/jingxigui/skeleton.xml");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_JINGXIGUI, true);
		}
		armature = Armature::create("jingxigui");
		armature->setScale(0.4);
#ifdef						GOLDEN_MINER2_FLASH_FRAME
		armature->getAnimation()->play("jxgchibang" , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
#else
		armature->getAnimation()->play("jingxiguichibang" , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
#endif
		repeat = CCRepeatForever::create(CCJumpTo::create(2.5, armature->getPosition(), 15, 1));
		armature->runAction(repeat);
		_tmpNode->addChild(armature);
		_tmpNode->setZOrder(LAYER_ORDER_CONTROL);
		if (type == GAMEING_CHALLENGE)
		{
			_tmpNode->setPosition(380 ,410);
		}
		else
		{
			_tmpNode->setPosition(500 ,410);
		}
		addChild(_tmpNode);
		break;
	case PET_ELEMENT_LINGGANDAWANG:
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_LINGGANDAWANG))
		{
			// 加载
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("linggandawang", "", "flash/linggandawang/linggandawang.png", "flash/linggandawang/linggandawang.plist", "flash/linggandawang/skeleton.xml");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_LINGGANDAWANG, true);
		}
		armature = Armature::create("linggandawang");
		armature->setScale(0.4);
#ifdef						GOLDEN_MINER2_FLASH_FRAME
		armature->getAnimation()->play("lgdwpaopao" , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
#else
		armature->getAnimation()->play("lgdwpaopaoyoudong" , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
#endif
		repeat = CCRepeatForever::create(CCJumpTo::create(2.5, armature->getPosition(), 15, 1));
		armature->runAction(repeat);
		_tmpNode->addChild(armature);
		_tmpNode->setZOrder(LAYER_ORDER_CONTROL);
		if (type == GAMEING_CHALLENGE)
		{
			_tmpNode->setPosition(350 ,410);
		}
		else
		{
			_tmpNode->setPosition(485 ,410);
		}
		addChild(_tmpNode);
		break;
	case PET_ELEMENT_NIUMOWANG:
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_NIUMOWANG))
		{
			// 加载
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("niumowang", "", "flash/niumowang/niumowang.png", "flash/niumowang/niumowang.plist", "flash/niumowang/skeleton.xml");
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_NIUMOWANG, true);
		}
		armature = Armature::create("niumowang");
		armature->setScale(0.4);
#ifdef						GOLDEN_MINER2_FLASH_FRAME
		armature->getAnimation()->play("nmwchibang" , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
#else
		armature->getAnimation()->play("niuchibang" , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
#endif
		repeat = CCRepeatForever::create(CCJumpTo::create(2.5, armature->getPosition(), 15, 1));
		armature->runAction(repeat);
		_tmpNode->addChild(armature);
		_tmpNode->setZOrder(LAYER_ORDER_CONTROL);
		if (type == GAMEING_CHALLENGE)
		{
			_tmpNode->setPosition(330 ,410);
		}
		else
		{
			_tmpNode->setPosition(505 ,410);
		}
		addChild(_tmpNode);
		break;
	case PET_ELEMENT_YUMIANGONGZHU:
		if (!Global::getInstance()->getCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_YUMIANGONGZHU))
		{
			// 加载
#ifdef						GOLDEN_MINER2_FLASH_FRAME
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("yumiangongzhu", "", "flash/yumiangongzhu/yumiangongzhu.png", "flash/yumiangongzhu/yumiangongzhu.plist", "flash/yumiangongzhu/skeleton.xml");
#else
			cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("yumian", "", "flash/yumiangongzhu/yumiangongzhu.png", "flash/yumiangongzhu/yumiangongzhu.plist", "flash/yumiangongzhu/skeleton.xml");
#endif
			Global::getInstance()->setCurrGameLayerLoadDynamicTarget(DYNAMIC_ID_YUMIANGONGZHU, true);
		}
#ifdef						GOLDEN_MINER2_FLASH_FRAME
		armature = Armature::create("yumiangongzhu"); 
#else
		armature = Armature::create("yumian");
#endif
		armature->setScale(0.4);
#ifdef						GOLDEN_MINER2_FLASH_FRAME
		armature->getAnimation()->play("ymchibang" , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
#else
		armature->getAnimation()->play("yumianchibang" , 0, 50, 1, TWEEN_EASING_MAX);// 凶狠状态
#endif
		repeat = CCRepeatForever::create(CCJumpTo::create(2.5, armature->getPosition(), 15, 1));
		armature->runAction(repeat);
		_tmpNode->addChild(armature);
		_tmpNode->setZOrder(LAYER_ORDER_CONTROL);
		if (type == GAMEING_CHALLENGE)
		{
			_tmpNode->setPosition(355 ,410);
		}
		else
		{
			_tmpNode->setPosition(490 ,410);
		}
		addChild(_tmpNode);
		break;
	default:
		break;
	}

#ifdef						GOLDEN_MINER_2_VERSION_PAY
	// 计费相关添加
	if(!Player::getInstance()->getPay(PAY_ID_GENUINE) && Global::getInstance()->getSelectGateId() == Global::getInstance()->getGenuineGateId())
	{
		isGenuine = true;
	}
#endif

	schedule( schedule_selector(GameControl::doAction), 0);
	setTouchEnabled(true);
	isPause = false;
	setKeypadEnabled(true);
}

void GameControl::onExit()
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

GameControl::~GameControl(void)
{
	this->setTouchEnabled(false);
	CC_SAFE_DELETE(gate);
	CC_SAFE_RELEASE(role);
	CC_SAFE_RELEASE(powerBuff);
	CC_SAFE_RELEASE(greyLayer);
	CC_SAFE_RELEASE(leaveTimeLabel);
	CC_SAFE_RELEASE(getCoinLabel);
	CCObject * p = NULL;
	CCARRAY_FOREACH(jewelSprites, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CCARRAY_FOREACH(explodes, p)
	{
		CC_SAFE_RELEASE(p);
	}

	switch(jewelSkillId)
	{
	case SKILL_ID_JEWEL_DROP:
	case SKILL_ID_JEWEL_FIVE_HANGER:
		//case SKILL_ID_JEWEL_DIZZY:
		CC_SAFE_DELETE(jewelSkillSprite);
		break;
	default:
		break;
	}

	CC_SAFE_RELEASE(mAnimationManager);

	//cs::ArmatureDataManager::sharedArmatureDataManager()->removeAll();
	//cs::ArmatureDataManager::sharedArmatureDataManager()->purgeArmatureSystem();
	//CCTextureCache::sharedTextureCache()->removeAllTextures();
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();

	CCLOG("GameControl::~GameControl");
}

SEL_MenuHandler GameControl::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnProp1", GameControl::onMenuItemProp1Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnProp2", GameControl::onMenuItemProp2Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnProp3", GameControl::onMenuItemProp3Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnSkill", GameControl::onMenuItemSkillClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnPause", GameControl::onMenuItemPauseClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnGem", GameControl::onMenuItemGemClicked);

	return NULL;
}

SEL_CCControlHandler GameControl::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool GameControl::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void GameControl::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;

	if (Player::getInstance()->getJewelButtonTipCount() <= 0)
	{
		((CCMenuItem *)getChildByTag(999)->getChildByTag(9))->setEnabled(false);
	}
	//mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(GameControl::doAnimationCompleted));
	//mAnimationManager->runAnimationsForSequenceNamed("zc");
	CC_SAFE_RETAIN(mAnimationManager);
}

// 炸弹道具使用
void GameControl::onMenuItemProp1Clicked(cocos2d::CCObject * pSender)
{
	if (isGameOver)
	{
		return;
	}
	if (isBackGroud)
	{
		return;
	}
	// 这里注意什么样的控制条件
	//if (carryTargetPoint == NULL)
	//{
	//	return;
	//}
	//if (isZhaDanStatus)
	//{
	//	return;
	//}
	if (!role->canDoExplosive())
	{
		return;
	}
	if (explosive != NULL)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	
	// 判断道具是否还有
	if(Player::getInstance()->getPropNum(PROP_TYPE_GRENADE) > 0)
	{
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_PROP);

		// 道具即时扣除
		Player::getInstance()->appendPropNum(PROP_TYPE_GRENADE, -1);
		Player::getInstance()->savePropNum(PROP_TYPE_GRENADE,0);
		//currPropOwn[PROP_TYPE_GRENADE]--;
		//Global::getInstance()->appendPropAwardGet(PROP_TYPE_GRENADE, -1);// 可以存储负值
		getChildByTag(5)->removeChildByTag(PROP_NUM_TAG);
		getChildByTag(5)->addChild(getPropNumLable(PROP_TYPE_GRENADE),1, PROP_NUM_TAG);		
		doSkills(SKILL_ID_GRENADE);
	}
}

// 大力丸道具使用
void GameControl::onMenuItemProp2Clicked(cocos2d::CCObject * pSender)
{
	if (isGameOver)
	{
		return;
	}
	if (isBackGroud)
	{
		return;
	}
	if (isStrongStatus)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	
	// 判断道具是否还有
	if(Player::getInstance()->getPropNum(PROP_TYPE_VIGOROUSLY_PILL) > 0)
	{
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_PROP);

		// 道具即时扣除
		Player::getInstance()->appendPropNum(PROP_TYPE_VIGOROUSLY_PILL, -1);
		Player::getInstance()->savePropNum(PROP_TYPE_VIGOROUSLY_PILL,0);
		//currPropOwn[PROP_TYPE_VIGOROUSLY_PILL]--;
		//Global::getInstance()->appendPropAwardGet(PROP_TYPE_VIGOROUSLY_PILL, -1);// 可以存储负值
		getChildByTag(6)->removeChildByTag(PROP_NUM_TAG);
		getChildByTag(6)->addChild(getPropNumLable(PROP_TYPE_VIGOROUSLY_PILL),1,  PROP_NUM_TAG);	
		doSkills(SKILL_ID_VIGOROUSLY_PILL);
	}
}

// 月光宝盒道具使用
void GameControl::onMenuItemProp3Clicked(cocos2d::CCObject * pSender)
{
	if (isGameOver)
	{
		return;
	}
	if (isBackGroud)
	{
		return;
	}

	//if (isMoonLightStatus)
	//{
	//	return;
	//}

	if (leaveTime > 60)
	{
		if (Player::getInstance()->getMoonLightTipCount() > 0)
		{
			Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

			Player::getInstance()->setMoonLightTipCount(Player::getInstance()->getMoonLightTipCount() - 1);

			PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMING);
			setBackGround(true);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->moonLightInformation();
		}
	}
	else
	{
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
		// 判断道具是否还有
		if(Player::getInstance()->getPropNum(PROP_TYPE_MOONLIGHT) > 0)
		{
			Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_PROP);

			// 道具即时扣除
			Player::getInstance()->appendPropNum(PROP_TYPE_MOONLIGHT, -1);
			Player::getInstance()->savePropNum(PROP_TYPE_MOONLIGHT,0);
			//currPropOwn[PROP_TYPE_MOONLIGHT]--;
			//Global::getInstance()->appendPropAwardGet(PROP_TYPE_MOONLIGHT, -1);// 可以存储负值
			getChildByTag(7)->removeChildByTag(PROP_NUM_TAG);
			getChildByTag(7)->addChild(getPropNumLable(PROP_TYPE_MOONLIGHT),1,  PROP_NUM_TAG);
			doSkills(SKILL_ID_MOONLIGHT);
		}
	}
}

void GameControl::onMenuItemSkillClicked(cocos2d::CCObject * pSender)
{
	if (isGameOver)
	{
		return;
	}
	if (isBackGroud)
	{
		return;
	}
	// 播放技能的处理效果
	if (role->getSkillStatus() != ROLE_SKILL_STATUS_CANSKILL)
	{
		return;
	}

	if (isJewel)
	{
		return;
	}

	//if (role->getHanger()->getStatus() != HANGER_STATUS_SWAYING)
	//{
	//	return;
	//}

	isPause = true;
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	
	RoleSkillEffect * roleSkillEffect = (RoleSkillEffect *)Global::getInstance()->s->getRoleSkillEffect(this);
	setBackGround(true);
	Global::getInstance()->s->addLayerToRunningScene(roleSkillEffect);

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_SKILL);

	roleSkillEffect->doSkillEffect(role->getType());
}

void GameControl::onMenuItemGemClicked(cocos2d::CCObject * pSender)
{
	if (isGameOver)
	{
		return;
	}

	if (isBackGroud)
	{
		return;
	}

	if (isJewel)
	{
		return;
	}

#ifdef										GAME_LAYER_JEWEL_IS_BUTTON

#ifdef										GOLDEN_MINER2_JEWEL_IS_PAY

#ifdef										GOLDEN_MINER2_VERSION_PAY_SELF
	// 填出自己计费点窗口
	setBackGroundWithOutGreyLayer(true);
	CostLayer * _layer = (CostLayer *)Global::getInstance()->s->getCostLayer(this, LAYER_ID_GAMING);
	_layer->costById(PAY_ID_JEWEL, CCCallFunc::create(this, callfunc_selector(GameControl::payJewelSuccess)), CCCallFunc::create(this, callfunc_selector(GameControl::payJewelFailed)));
	Global::getInstance()->s->addLayerToRunningScene(_layer);
#else
	// 弹出渠道计费点窗口

#endif

#else
	// 宝石不是计费版本则提示宝石技能释放说明
	if (Player::getInstance()->getJewelButtonTipCount() <= 0)
	{
		((CCMenuItem *)getChildByTag(999)->getChildByTag(9))->setEnabled(false);
		return;
	}
	Player::getInstance()->setJewelButtonTipCount(Player::getInstance()->getJewelButtonTipCount() - 1);

	if (Player::getInstance()->getJewelButtonTipCount() <= 0)
	{
		((CCMenuItem *)getChildByTag(999)->getChildByTag(9))->setEnabled(false);
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMING);
	setBackGround(true);
	Global::getInstance()->s->addLayerToRunningScene(promptLayer);
	promptLayer->jewelInformation();
#endif


#else
#endif
}

void GameControl::onMenuItemPauseClicked(cocos2d::CCObject * pSender)
{
	if (isGameOver)
	{
		return;
	}
	if (isBackGroud)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->pauseLoopEffect();
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	setBackGround(true);
	isUpdateProp = true;		
	if (type != GAMEING_GUIDE)
	{
		for(int i = PROP_TYPE_JEWEL_BLUE; i < PROP_TYPE_COUNT; i++)
		{
			Player::getInstance()->appendPropNum(i, Global::getInstance()->getPropAwardNumById(i));
			Player::getInstance()->savePropNum(i, Global::getInstance()->getPropAwardNumById(i));
		}
	}
	//tmpProp1Num = Player::getInstance()->getPropNum(PROP_TYPE_GRENADE);
	//tmpProp2Num = Player::getInstance()->getPropNum(PROP_TYPE_VIGOROUSLY_PILL);
	//tmpProp3Num = Player::getInstance()->getPropNum(PROP_TYPE_MOONLIGHT);
	Player::getInstance()->setGameLayerIsPause(true);
	Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getPauseMenu(this));
}

#ifdef						GOLDEN_MINER_2_VERSION_PAY
// 计费相关添加
void GameControl::doGenuine(void)
{
#ifdef						GOLDEN_MINER2_VERSION_PAY_SELF
	setBackGroundWithOutGreyLayer(true);
	CostLayer * _layer = (CostLayer *)Global::getInstance()->s->getCostLayer(this, LAYER_ID_GAMING);
	_layer->costGenuine(0, CCCallFunc::create(this, callfunc_selector(GameControl::genuineSuccess)), CCCallFunc::create(this, callfunc_selector(GameControl::genuineFailed)));
	Global::getInstance()->s->addLayerToRunningScene(_layer);
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
	setBackGroundWithOutGreyLayer(true);
	PayService::getInstance()->pay(PAY_ID_GENUINE, true, CCCallFunc::create(this, callfunc_selector(GameControl::genuineSuccess)), CCCallFunc::create(this, callfunc_selector(GameControl::genuineFailed)));
	//PayService::getInstance()->pay(PAY_ID_GENUINE, false, CCCallFunc::create(this, callfunc_selector(GameControl::genuineSuccess)), CCCallFunc::create(this, callfunc_selector(GameControl::genuineFailed)));

#else if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) //判断当前是否为Android平台
	isGenuine = false;
	isGenuining = false;
#endif
#endif
}
#endif

// 计费相关添加
void GameControl::payJewelSuccess(void)
{
	setBackGroundWithOutGreyLayer(false);
	isPayJewel = true;
	doJewelSkill();

	Player::getInstance()->setPay(PAY_ID_GENUINE, true);
}

// 计费相关添加
void GameControl::payJewelFailed(void)
{
	setBackGroundWithOutGreyLayer(false);
}

// 计费相关添加
void GameControl::genuineSuccess(void)
{
	setBackGroundWithOutGreyLayer(false);
	isGenuine = false;

	Player::getInstance()->setPay(PAY_ID_GENUINE, true);
}

// 计费相关添加
void GameControl::genuineFailed(void)
{
	LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
	CCLayer * p1 = Global::getInstance()->s->getMainLayer(p);

	p->addLoadingLayer(0,p1);
	p->setNextLayer(LAYER_ID_MAIN, p1);

	Global::getInstance()->s->replaceScene(p);
}

void GameControl::doAction(float _f)
{
	if (isBackGroud)
	{
		return;
	}

#ifdef						GOLDEN_MINER_2_VERSION_PAY
	// 计费相关添加
	if (isGenuine)
	{
		doGenuine();
		return;
	}
#endif

	// 首先对话
	// 并行说话的模式（不做返回处理）
	//// 串行说话的模式
	//if(!isUpdate && isWords)
	//{
	//	if(wuguiWords == NULL)
	//	{
	//		if(roleWords->getOpacity() == 0)
	//		{
	//			isWords = false;
	//		}
	//	}
	//	else
	//	{
	//		if(roleWords->getOpacity() == 0 && wuguiWords->getOpacity() == 0)
	//		{
	//			isWords = false;
	//		}
	//	}
	//	return;
	//}
#ifdef										GOLDEN_MINER_2_VERSION_TIME
	float _timeTimes = _f * SCHEDULE_TIMES;
	if (_timeTimes > 2)
	{
		_timeTimes = 2;
	}
	Global::getInstance()->setTimeRatio(_timeTimes);
#endif

	// 提示
	if (!isUpdate && tipId != 0 && Player::getInstance()->getTip(tipId))
	{
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMING);
		setBackGround(true);
		//setBackGroundWithOutGreyLayer(true);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->doGamingTip(tipId);
		Player::getInstance()->setTip(tipId, false);
		tipId = 0;
		return;
	}

	if (!isUpdate && !isStartCountDownEffect)
	{	// 播放开始倒计时
		CountDownEffect * countDownEffect = (CountDownEffect *)Global::getInstance()->s->getCountDownEffect(this);
		setBackGroundWithOutGreyLayer(true);
		Global::getInstance()->s->addLayerToRunningScene(countDownEffect);
		countDownEffect->doCountDownEffect(0);
		isStartCountDownEffect = true;
		return;
	}
	
	if (!isUpdate && isBuddahaTip)
	{	// 播放开始倒计时
		Buddaha * buddaha = (Buddaha *)Global::getInstance()->s->getBuddhaLayer(this);
		setBackGround(true);
		Global::getInstance()->s->addLayerToRunningScene(buddaha);
		isBuddahaTip = false;
	}

	if(jewelSkillId == SKILL_ID_JEWEL_DROP)
	{
		jewelSkillSprite->updateSkill(_f, this);
		//if (biaozhunxian != NULL)
		//{
		//	biaozhunxian->setVisible(false);
		//}
		return;
	}

	//if (a < 0)
	//{
	//	//onMenuItemSkillClicked(NULL);
	//	//doJewelSkill();
	//	a = 0;
	//}
	//else if (a > 0)
	//{
	//	a -= _f;
	//}

	char _s[64];
	//sprintf(_s, "jewel: %d",jewelSkillId);
	//jewel->setString(_s);
	//sprintf(_s, "roleSpeed: %d",role->getHanger()->getSpeedSelf());
	//roleSpeed->setString(_s);
	//sprintf(_s, "sceneSpeed: %d",role->getHanger()->getSpeedScene());
	//sceneSpeed->setString(_s);
	//sprintf(_s, "roleSwaySpeed: %f",fabs(role->getHanger()->getSpeedAngle()));
	//roleSwaySpeed->setString(_s);

	intersectCheck();
	role->doAction(_f, this);
	//// 瞄准线
	//if ((biaozhunxian != NULL))
	//{
	//	// 需要多转换一下角度
	//	if (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING && role->getHanger()->isVisible())
	//	{
	//		biaozhunxian->setRotation(angleCenter - Global::getInstance()->getHangerAngle());
	//		changeMiaoZhunXianPosition();
	//		biaozhunxian->setVisible(true);
	//	}
	//	else
	//	{
	//		biaozhunxian->setVisible(false);
	//	}
	//}
	gate->doAction(_f, this);

	checkContinueCount(_f);
	// 添加获得的积分
	scoreAppend(_f);
	// 爆炸相关的播放
	doExplode(_f);
	doLiuGuang(_f);

	if (isJewel)
	{
		if(jewelSkillId != -1)
		{
			jewelSkillSprite->updateSkill(_f, this);
			//if (biaozhunxian != NULL)
			//{
			//	biaozhunxian->setVisible(false);
			//}
		}
		else
		{
			if(jewelAppendEffects->count() == 0)
			{
				//isDoJewelSkill = true;
				if (!isDoJewelSkill)
				{
					doJewelSkill();
					//if (biaozhunxian != NULL)
					//{
					//	biaozhunxian->setVisible(false);
					//}
				}
			}
			else
			{
				updateJewelSkill(_f);
			}
		}
	}
	else
	{
		checkJewelSkill(_f);
	}

#ifdef										GOLDEN_MINER_2_VERSION_TIME
	if (isGameOver)
	{// 计时
		if (timeCount >= 1.5)
		{
			gameOver();
			return;
		}
		else
		{
			timeCount += _f;
		}
	}

	if (!isGameOver && gate->getTargetTotalNum() == 0)
	{
		// 游戏结束
		isGameOver = true;
		timeCount = 0.0;
		//gameOver();
		//return;
	}

	if (!isGameOver && isTiming)
	{// 计时
		timeCount -= _f;
		if ((int)timeCount < leaveTime)
		{
			//timeCount = SCHEDULE_TIMES;
			leaveTime--;
			sprintf(_s, "time: %d",leaveTime);
			setLeaveTime(leaveTime);
			if (leaveTime == 0)
			{
				// 游戏结束
				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_TIME_OUT);
				// 游戏结束
				isGameOver = true;
				timeCount = 0.0;
				lastTimeCountDownEffect->setVisible(false);
				//gameOver();
			}
			else if (leaveTime < 6)
			{
				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_TIME_LAST);
				((Sensitization *)liuGuang->objectAtIndex(SKILL_ID_MOONLIGHT-1))->setVisible(true);
				lastTimeCountDownEffect->setVisible(true);
			}
			else
			{
				lastTimeCountDownEffect->setVisible(false);
			}
		}
	}

	if (isStrongStatus)
	{
		strongStatusTimeCount += _f;
		if (strongStatusTimeCount >= VIGOROUSLY_PILL_TIME)
		{
			releaseSkills(SKILL_ID_VIGOROUSLY_PILL);	
		}
	}
	if (isMoonLightStatus)
	{
		moonLightStatusTimeCount += _f;
		if (moonLightStatusTimeCount >= VIGOROUSLY_PILL_TIME)
		{
			releaseSkills(SKILL_ID_MOONLIGHT);	
		}
	}
#else
	if (isGameOver)
	{// 计时
		if (timeCount == 0)
		{
			gameOver();
			return;
		}
		else
		{
			timeCount--;
		}
	}

	if (!isGameOver && gate->getTargetTotalNum() == 0)
	{
		// 游戏结束
		isGameOver = true;
		timeCount = SCHEDULE_TIMES*1.5;
		//gameOver();
		//return;
	}

	if (!isGameOver && isTiming)
	{// 计时
		timeCount--;
		if (timeCount == 0)
		{
			timeCount = SCHEDULE_TIMES;
			leaveTime--;
			sprintf(_s, "time: %d",leaveTime);
			setLeaveTime(leaveTime);
			if (leaveTime == 0)
			{
				// 游戏结束
				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_TIME_OUT);
				// 游戏结束
				isGameOver = true;
				timeCount = SCHEDULE_TIMES*1.5;
				lastTimeCountDownEffect->setVisible(false);
				//gameOver();
			}
			else if (leaveTime < 6)
			{
				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_TIME_LAST);
				((Sensitization *)liuGuang->objectAtIndex(SKILL_ID_MOONLIGHT-1))->setVisible(true);
				lastTimeCountDownEffect->setVisible(true);
			}
			else
			{
				lastTimeCountDownEffect->setVisible(false);
			}
		}
	}

	if (isStrongStatus)
	{
		strongStatusTimeCount++;
		if (strongStatusTimeCount == VIGOROUSLY_PILL_TIME * SCHEDULE_TIMES)
		{
			releaseSkills(SKILL_ID_VIGOROUSLY_PILL);	
		}
	}
	if (isMoonLightStatus)
	{
		moonLightStatusTimeCount++;
		if (moonLightStatusTimeCount == VIGOROUSLY_PILL_TIME * SCHEDULE_TIMES)
		{
			releaseSkills(SKILL_ID_MOONLIGHT);	
		}
	}
#endif

	if (explosive != NULL)
	{
		if (explosive->doAction(_f))
		{
			releaseSkills(SKILL_ID_GRENADE);
		}
	}
	//if (isZhaDanStatus)
	//{
	//	zhaDanStatusTimeCount++;
	//	double _positionX = 0;
	//	double _positionY = 0;
	//	if(carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
	//	{
	//		_positionX = ((Target *)carryTargetPoint)->getPositionX() + (Global::getInstance()->getcentreX() - ((Target *)carryTargetPoint)->getPositionX()) * (GRENADE_TIME - zhaDanStatusTimeCount) / GRENADE_TIME;
	//		_positionY = ((Target *)carryTargetPoint)->getPositionY() + (Global::getInstance()->getcentreY() - ((Target *)carryTargetPoint)->getPositionY()) * (GRENADE_TIME - zhaDanStatusTimeCount) / GRENADE_TIME;
	//		zhaDanSprite->setPosition(ccp(_positionX, _positionY));
	//	}
	//	else if (carryTargetType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
	//	{
	//		if (((DynamicTarget *)carryTargetPoint)->getId() == DYNAMIC_ID_SHELL)
	//		{
	//			_positionX = ((DynamicTargetShell *)carryTargetPoint)->shellSprite->getPositionX() + (Global::getInstance()->getcentreX() - ((DynamicTarget *)carryTargetPoint)->getArmature()->getPositionX()) * (GRENADE_TIME - zhaDanStatusTimeCount) / GRENADE_TIME;
	//			_positionY = ((DynamicTargetShell *)carryTargetPoint)->shellSprite->getPositionY() + (Global::getInstance()->getcentreY() - ((DynamicTarget *)carryTargetPoint)->getArmature()->getPositionY()) * (GRENADE_TIME - zhaDanStatusTimeCount) / GRENADE_TIME;
	//		}
	//		else
	//		{
	//			_positionX = ((DynamicTarget *)carryTargetPoint)->getArmature()->getPositionX() + (Global::getInstance()->getcentreX() - ((DynamicTarget *)carryTargetPoint)->getArmature()->getPositionX()) * (GRENADE_TIME - zhaDanStatusTimeCount) / GRENADE_TIME;
	//			_positionY = ((DynamicTarget *)carryTargetPoint)->getArmature()->getPositionY() + (Global::getInstance()->getcentreY() - ((DynamicTarget *)carryTargetPoint)->getArmature()->getPositionY()) * (GRENADE_TIME - zhaDanStatusTimeCount) / GRENADE_TIME;
	//		}
	//		zhaDanSprite->setPosition(ccp(_positionX, _positionY));
	//	}
	//	if (zhaDanStatusTimeCount == GRENADE_TIME)
	//	{
	//		releaseSkills(SKILL_ID_GRENADE);	
	//	}
	//}
	isUpdate = true;
}
	
bool GameControl::doWordsById(int _id)
{
	bool res = false;
	roleWords = NULL;
	wuguiWords = NULL;

	switch(_id)
	{
	case 1:
		roleWords = CCSprite::create("duihuakuang/1.png");
		res = true;
		break;
	case 11:
		roleWords = CCSprite::create("duihuakuang/5.png");
		wuguiWords = CCSprite::create("duihuakuang/4.png");
		res = true;
		break;
	case 12:
		roleWords = CCSprite::create("duihuakuang/3.png");
		wuguiWords = CCSprite::create("duihuakuang/2.png");
		res = true;
		break;
	case 21:
		roleWords = CCSprite::create("duihuakuang/6.png");
		res = true;
		break;
	case 22:
		roleWords = CCSprite::create("duihuakuang/7.png");
		res = true;
		break;
	case 23:
		roleWords = CCSprite::create("duihuakuang/8.png");
		res = true;
		break;
	case 31:
		roleWords = CCSprite::create("duihuakuang/9.png");
		res = true;
		break;
	case 32:
		roleWords = CCSprite::create("duihuakuang/10.png");
		res = true;
		break;
	case 33:
		roleWords = CCSprite::create("duihuakuang/11.png");
		res = true;
		break;
	case 34:
		roleWords = CCSprite::create("duihuakuang/12.png");
		res = true;
		break;
	case 41:
		roleWords = CCSprite::create("duihuakuang/14.png");
		res = true;
		break;
	case 42:
		roleWords = CCSprite::create("duihuakuang/15.png");
		res = true;
		break;
	case 43:
		roleWords = CCSprite::create("duihuakuang/16.png");
		res = true;
		break;
	case 44:
		roleWords = CCSprite::create("duihuakuang/17.png");
		res = true;
		break;
	case 45:
		roleWords = CCSprite::create("duihuakuang/18.png");
		res = true;
		break;
	default:
		break;
	}

	CCSequence * sequence;
	if (roleWords != NULL)
	{
		sequence = CCSequence::create(CCFadeIn::create(.3f),CCFadeTo::create(3,255*1),CCFadeOut::create(.3f),NULL);
		addChild(roleWords, 1000);
		roleWords->setPosition(ccp(510,440));
		roleWords->runAction(sequence);
	}

	if(wuguiWords != NULL)
	{
		wuguiWords->setOpacity(0);
		sequence = CCSequence::create(CCFadeTo::create(3.5f,0),CCFadeIn::create(.3f),CCFadeTo::create(1,255*1),CCFadeOut::create(.3f),NULL);
		addChild(wuguiWords, 1000);
		wuguiWords->setPosition(ccp(260,395));
		wuguiWords->runAction(sequence);
	}

	return res;
}

void GameControl::scoreAppend(float _f)
{
	if (!isScoreAppendEffectsPause && scoreAppendEffects != NULL)
	{
		ScoreAppendEffect * p;
		CCArray * removeIndexScoreAppendEffect = CCArray::create();

		for (int i = 0; i < scoreAppendEffects->count(); i++)
		{
			p = (ScoreAppendEffect *)scoreAppendEffects->objectAtIndex(i);
			if (p->doAction(_f))
			{
				removeIndexScoreAppendEffect->addObject(CCInteger::create(i));
			}
		}
		// 移除该移除的对象
		for (unsigned int i = removeIndexScoreAppendEffect->count(); i >0; i--)
		{
			removeChild((ScoreAppendEffect *)(scoreAppendEffects->objectAtIndex(((CCInteger *)removeIndexScoreAppendEffect->objectAtIndex(i-1))->getValue())),true);
			scoreAppendEffects->removeObjectAtIndex(((CCInteger *)removeIndexScoreAppendEffect->objectAtIndex(i-1))->getValue());
			removeIndexScoreAppendEffect->removeObjectAtIndex(i-1,true);
		}
	}

	if (getCoinTmp != Global::getInstance()->getPropAwardNumById(PROP_TYPE_COIN))
	{
		if (getCoinTmp != -1)
		{
			if (scoreAppendEffects == NULL)
			{
				scoreAppendEffects = new CCArray();
			}
			scoreAppendEffects->addObject(new ScoreAppendEffect(this, Global::getInstance()->getPropAwardNumById(PROP_TYPE_COIN) - getCoinTmp));
			addChild((ScoreAppendEffect *)scoreAppendEffects->lastObject(), LAYER_ORDER_CONTROL*2);
		}
		//if (getCoinTmp == -1)
		//{
		//	getCoinTmp = Global::getInstance()->getPropAwardNumById(PROP_TYPE_COIN);
		//	setGetCoinLabel();
		//}
		//else
		//{
		//	if (flyTimeScore < ADD_NEW_SCORE_FLY_TIME_LONG)
		//	{
		//		flyTimeScore += _f;
		//		addScoreSystem->setPosition(ccp(Global::getInstance()->getHangerCurrX() + flyTimeScore/ADD_NEW_SCORE_FLY_TIME_LONG*(getCoinLabel->getPositionX() - Global::getInstance()->getHangerCurrX()), Global::getInstance()->getHangerCurrY() + flyTimeScore/ADD_NEW_SCORE_FLY_TIME_LONG*(getCoinLabel->getPositionY() - Global::getInstance()->getHangerCurrY())));
		//	}
		//	else
		//	{
		//		if (addScoreSystem == NULL)
		//		{
		//			addScore(Global::getInstance()->getPropAwardNumById(PROP_TYPE_COIN) - getCoinTmp);
		//		}
		//		else
		//		{
		//			removeChild(addScoreSystem, true);
		//			removeChild(addScoreSprite, true);
		//			removeChild(addScoreNum, true);
		//			addScoreSystem = NULL;
		//			getCoinTmp = Global::getInstance()->getPropAwardNumById(PROP_TYPE_COIN);
		//			setGetCoinLabel();
		//		}
		//	}
		//}
		getCoinTmp = Global::getInstance()->getPropAwardNumById(PROP_TYPE_COIN);
		setGetCoinLabel();
	}
}

void GameControl::keyBackClicked(void)	
{
	if (!isPause)
	{
		onMenuItemPauseClicked(NULL);
	}
}

void GameControl::addExplode(int _type, float _x, float _y)
{
	explodes->addObject(new Explode(_type));
	((Explode *)explodes->lastObject())->setPosition(_x, _y);
	addChild((Explode *)explodes->lastObject(), LAYER_ORDER_CONTROL+1);
}
	
void GameControl::setLiuGuangVisiable(int _index, bool _b)
{
	((Sensitization *)liuGuang->objectAtIndex(_index))->setVisible(_b);
}

void GameControl::addExplosive(Explosive * _explosive)
{
	explosive = _explosive;
	addChild(explosive, LAYER_ORDER_CONTROL-1);
}

int GameControl::getCurrMapId(void)
{
	return currMapId;
}

int GameControl::getType(void)
{
	return type;
}

//void GameControl::changeMiaoZhunXianPosition(void)
//{
//	double positionX = Global::getInstance()->getHangerCurrX() + 
//		biaozhunxian->getContentSize().height * 0.8 / 2 * cos(Global::getInstance()->getHangerAngle() / angleChange * pi);
//	double positionY = Global::getInstance()->getHangerCurrY() + 
//		biaozhunxian->getContentSize().height * 0.8 / 2 * sin(Global::getInstance()->getHangerAngle() / angleChange * pi);
//
//	biaozhunxian->setPosition(ccp(positionX, positionY));
//}

//void GameControl::addNewJewel(int _propType)
//{
//	addNewJewelType = _propType;
//	flyTime = 0.0;
//	newJewelSystem = CCParticleSystemQuad::create("lizitexiao/daojulizi/daojulizi.plist");//plist文件可以通过例子编辑器获得
//	newJewelSystem->setPosition(ccp(Global::getInstance()->getcentreX(), Global::getInstance()->getcentreY()));
//	addChild(newJewelSystem, LAYER_ORDER_CONTROL *2);
//}

void GameControl::addJewelBomb(int _propType)
{
	if (jewelBombSystem != NULL)
	{
		removeChild(jewelBombSystem);
	}

	((CCSprite *)jewelSprites->objectAtIndex(_propType - PROP_TYPE_JEWEL_BLUE))->setVisible(true);
	jewelBombSystem = CCParticleSystemQuad::create("lizitexiao/xingxingsankai/xingxingsankai.plist");//plist文件可以通过例子编辑器获得

	switch(_propType)
	{
	case PROP_TYPE_JEWEL_BLUE:
		jewelBombSystem->setPosition(ccp(RED_JEWEL_BLUE_X, RED_JEWEL_BLUE_Y));
		break;
	case PROP_TYPE_JEWEL_PURPLE:
		jewelBombSystem->setPosition(ccp(RED_JEWEL_PURPLE_X, RED_JEWEL_PURPLE_Y));
		break;
	case PROP_TYPE_JEWEL_YELLOW:
		jewelBombSystem->setPosition(ccp(RED_JEWEL_YELLOW_X, RED_JEWEL_YELLOW_Y));
		break;
	case PROP_TYPE_JEWEL_GREEN:
		jewelBombSystem->setPosition(ccp(RED_JEWEL_GREEN_X, RED_JEWEL_GREEN_Y));
		break;
	case PROP_TYPE_JEWEL_RED:
		jewelBombSystem->setPosition(ccp(RED_JEWEL_RED_X, RED_JEWEL_RED_Y));
		break;
	default:
		break;
	}
	addChild(jewelBombSystem, LAYER_ORDER_CONTROL *2);
}

//void GameControl::addScore(int _score)
//{
//	flyTimeScore = 0.0;
//	addScoreSystem = CCParticleSystemQuad::create("lizitexiao/daojulizi/daojulizi.plist");//plist文件可以通过例子编辑器获得
//	addScoreSystem->setPosition(ccp(Global::getInstance()->getcentreX(), Global::getInstance()->getcentreY()));
//	addChild(addScoreSystem, LAYER_ORDER_CONTROL *2);
//
//	addScoreSprite = CCSprite::create("youxi/+.png");
//	addScoreSprite->setPosition(ccp(Global::getInstance()->getcentreX() + 90, Global::getInstance()->getcentreY()  + 65));
//	addChild(addScoreSprite);
//	char _s[32];
//	sprintf(_s, "%d",_score);
//	addScoreNum = CCLabelAtlas::create(_s, "youxi/daojushuzi.png", 25, 36, '0');
//	int i = 0;
//	int _getCoinTmp = _score;
//	while(1)
//	{
//		_getCoinTmp = _getCoinTmp / 10;
//		if (_getCoinTmp > 0)
//		{
//			i++;
//		}
//		else
//		{
//			break;
//		}
//	}
//	addScoreNum->setPosition(ccp(Global::getInstance()->getcentreX() + 50 + 44 + i*8, Global::getInstance()->getcentreY()  + 50));
//	addChild(addScoreNum);
//}
	
void GameControl::checkContinueCount(float _f)
{
	// 刷新连击
	if(0 != Global::getInstance()->getContinuesCount())
	{
		if(countinueCount != Global::getInstance()->getContinuesCount() && Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING)// 判断获得物品的时候
		{
			setContinueCount(Global::getInstance()->getContinuesCount());
			countinueCount = Global::getInstance()->getContinuesCount();
/*			setContinueCount(Global::getInstance()->getContinuesCount());
			if (flyTimeContinue < ADD_NEW_SCORE_FLY_TIME_LONG)
			{
				flyTimeContinue += _f;
			}
			else
			{
				if (countinueCountSprite == NULL)
				{
					if(Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING)
					{
						setContinueCount(Global::getInstance()->getContinuesCount());
					}
				}
				else
				{
					removeChild(countinueCountSprite, true);
					removeChild(countinueCountNum, true);
					countinueCountSprite = NULL;
					countinueCount = Global::getInstance()->getContinuesCount();
				}
			}	*/	
		}
	}
	else
	{
		if(countinueCount != Global::getInstance()->getContinuesCount() && Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING)// 在获得物品的时候
		{
			if (countinueFailed == NULL)
			{
				countinueFailed = CCSprite::create("youxi/lianjishibai.png");
				addChild(countinueFailed, LAYER_ORDER_CONTROL+1);
			}
			countinueFailed->setPosition(ccp(900, 300));
			CCSpawn * spawn = CCSpawn::create(CCFadeIn::create(.3f),CCMoveTo::create(.3f,ccp(600,300)),NULL);
			CCSequence * sequence = CCSequence::create(spawn,CCFadeTo::create(1,255*1),CCFadeOut::create(.2f),NULL);
			countinueFailed->runAction(sequence);
			countinueCount = Global::getInstance()->getContinuesCount();
		}
	}
}

void GameControl::setContinueCount(int _countinueCount)
{
	if (countinueCountSprite != NULL)
	{
		removeChild(countinueCountSprite, true);
		removeChild(countinueCountNum, true);
	}

	int startX = Global::getInstance()->getcentreX();
	int startY = Global::getInstance()->getcentreY();

	CCSequence * sequence;
	CCSpawn * spawn;

	countinueCountSprite = CCSprite::create("texiao/lianji.png");
	countinueCountSprite->setPosition(ccp(900, 300));
	spawn = CCSpawn::create(CCFadeIn::create(.3f),CCMoveTo::create(.3f,ccp(600,300)),NULL);/*
	countinueCountSprite->setPosition(ccp(startX + 250, Global::getInstance()->getcentreY()  + 15));
	spawn = CCSpawn::create(CCFadeIn::create(.3f),CCMoveTo::create(.3f,ccp(startX + 250,startY  + 15 +60)),NULL);*/
	sequence = CCSequence::create(spawn,CCFadeTo::create(1,255*1),CCFadeOut::create(.2f),NULL);
	//sequence = CCSequence::create(CCScaleTo::create(.1f,1.5f),CCScaleTo::create(.1f,1),
	//	CCMoveTo::create(.3f,ccp(startX + 250,startY  + 15 +60))
	//	,CCFadeOut::create(.2f),NULL);
	countinueCountSprite->runAction(sequence);
	addChild(countinueCountSprite);
	char _s[32];
	sprintf(_s, "%d",_countinueCount);
	countinueCountNum = CCLabelAtlas::create(_s, "youxi/daojushuzi.png", 25, 36, '0');
	int i = 0;
	int _getCoinTmp = _countinueCount;
	while(1)
	{
		_getCoinTmp = _getCoinTmp / 10;
		if (_getCoinTmp > 0)
		{
			i++;
		}
		else
		{
			break;
		}
	}
	countinueCountNum->setPosition(ccp(800 + 30 - i*20, 285));
	spawn = CCSpawn::create(CCFadeIn::create(.3f),CCMoveTo::create(.3f,ccp(500 + 30 - i*20, 285)),NULL);
	//countinueCountNum->setPosition(ccp(startX + 150 + 30 - i*20, startY));
	//spawn = CCSpawn::create(CCFadeIn::create(.3f),CCMoveTo::create(.3f,ccp(startX + 150 + 30 - i*20,startY +60)),NULL);
	sequence = CCSequence::create(spawn,CCFadeTo::create(1,255*1),CCFadeOut::create(.2f),NULL);
	//sequence = CCSequence::create(CCScaleTo::create(.1f,1.5f),CCScaleTo::create(.1f,1),
	//	CCMoveTo::create(.3f,ccp(startX + 150 + 30 - i*20,startY +60))
	//	,CCFadeOut::create(.2f),NULL);
	countinueCountNum->runAction(sequence);
	addChild(countinueCountNum);
}

void GameControl::setCurrMapId(int _currMapId)//(只能初始化一次)
{
	// 关卡显示相关初始化
	CCSprite * _tmp = CCSprite::create("youxi/diduosg.png");
	_tmp->setPosition(ccp(getChildByTag(3)->getPositionX() - 14, getChildByTag(3)->getPositionY()- 14));
	addChild(_tmp);
	_tmp = CCSprite::create("youxi/henxian.png");
	_tmp->setPosition(ccp(getChildByTag(3)->getPositionX() - 19, getChildByTag(3)->getPositionY()- 14));
	addChild(_tmp);

	if (_currMapId > 10)
	{
		currMapId = 0;
	}
	else
	{
		currMapId = _currMapId;
	}

	char _s[32];
	sprintf(_s, "%d",currMapId);

	currMapId = _currMapId;

	CCLabelAtlas * currMapIdLabel = CCLabelAtlas::create(_s, "youxi/guankashuzi.png", 12, 15, '0');
	currMapIdLabel->setPosition(ccp(getChildByTag(3)->getPositionX() - 34, getChildByTag(3)->getPositionY()- 21));
	addChild(currMapIdLabel);
}

int GameControl::getCurrSceneId(void)
{
	return currSceneId;
}

void GameControl::setCurrSceneId(int _currSceneId)//(只能初始化一次)
{
	currSceneId = _currSceneId;

	char _s[32];
	sprintf(_s, "%d",currSceneId);
	int i = 0;
	while(1)
	{
		currSceneId = currSceneId / 10;
		if (currSceneId > 0)
		{
			i++;
		}
		else
		{
			break;
		}
	}

	CCLabelAtlas * currSceneIdLabel = CCLabelAtlas::create(_s, "youxi/guankashuzi.png", 12, 15, '0');
	currSceneIdLabel->setPosition(ccp(getChildByTag(3)->getPositionX()-i*6 - 11, getChildByTag(3)->getPositionY()- 21));
	addChild(currSceneIdLabel);
	currSceneId = _currSceneId;
}

void GameControl::setValueTimes(int _targetType, int _times)
{
	Global::getInstance()->setValueTimes(_targetType, _times);
}

void GameControl::setLeaveTime(int _leaveTime)
{
#ifdef										GOLDEN_MINER_2_VERSION_TIME
	if (timeCount < -9999)
	{
		timeCount = _leaveTime+1;
	}
#endif

	leaveTime = _leaveTime;
	char _s[32];
	sprintf(_s, "%d",leaveTime);

	if (leaveTimeLabel != NULL)
	{
		removeChild(leaveTimeLabel);
		CC_SAFE_RELEASE(leaveTimeLabel);
	}
	leaveTimeLabel = CCLabelAtlas::create(_s, "youxi/shijianshuzi.png", 20, 27, '0');
	int i = 0;
	int _getCoinTmp = leaveTime;
	while(1)
	{
		_getCoinTmp = _getCoinTmp / 10;
		if (_getCoinTmp > 0)
		{
			i++;
		}
		else
		{
			break;
		}
	}
	leaveTimeLabel->setScale(1 - (i - 1)*0.2);
	leaveTimeLabel->setPosition(ccp(getChildByTag(1)->getPositionX() -(13+i*10)*leaveTimeLabel->getScale(), getChildByTag(1)->getPositionY() - 17*leaveTimeLabel->getScale()));
	addChild(leaveTimeLabel);
	CC_SAFE_RETAIN(leaveTimeLabel);
}

void GameControl::setLeastCoin(int _leastCoin)// 设置需要最少的铜钱值(只能初始化一次)
{
	if (type == GAMEING_NORMAL && !isBuddaha)
	{
		// 佛光
		if (Player::getInstance()->getPropNum(PROP_TYPE_BUDDAHA) > 0)
		{
			isBuddaha = true;
			isBuddahaTip = true;
			Player::getInstance()->appendPropNum(PROP_TYPE_BUDDAHA, -1);
			Player::getInstance()->savePropNum(PROP_TYPE_BUDDAHA, -1);
			//_leastCoin = _leastCoin / 2;
		}		
	}

	if (leastCoinLabel != NULL)
	{
		removeChild(leastCoinLabel);
	}

	leastCoin = _leastCoin;

	char _s[32];
	sprintf(_s, "%d",leastCoin);

	leastCoinLabel = CCLabelAtlas::create(_s, "youxi/guankashuzi.png", 12, 15, '0');
	leastCoinLabel->setPosition(ccp(getChildByTag(3)->getPositionX(), getChildByTag(3)->getPositionY() + 3));

	//if (leastCoin > 999)
	//{
	//	leastCoinLabel->setScale(0.8);
	//}

	addChild(leastCoinLabel);
}

int GameControl::getLeastCoin(void)// 设置需要最少的铜钱值(只能初始化一次)
{
	return leastCoin;
}

void GameControl::setIsDynamicTargetMoving(bool _isDynamicTargetMoving)
{
	gate->setIsDynamicTargetMoving(_isDynamicTargetMoving);
}

void GameControl::setIsTiming(bool _isTiming)
{
	//gate->setIsTiming(_isTiming);
	isTiming = _isTiming;
}

void GameControl::setIsJewel(bool _isJewel)
{
	//gate->setIsTiming(_isTiming);
	isJewel = _isJewel;
	isDoJewelSkill = _isJewel;
}

void GameControl::doSkills(int _skillId)
{
	switch (_skillId)
	{
	case SKILL_ID_GRENADE:
		role->doExplosive(this);
		//// 移除抓取的目标 并且对钩子的状态更改为没有抓取物的拉回状态 将被抓去物的速度置0
		//if (zhaDanSprite == NULL)
		//{
		//	zhaDanSprite = CCSprite::create("youxi/zhadan.png");
		//	zhaDanSprite->setPosition(ccp(Global::getInstance()->getcentreX(), Global::getInstance()->getcentreY()));
		//	addChild(zhaDanSprite, LAYER_ORDER_CONTROL-1);
		//}
		//zhaDanSprite->setVisible(true);
		//isZhaDanStatus = true;
		//zhaDanStatusTimeCount = 0;
		break;
	case SKILL_ID_VIGOROUSLY_PILL:
		// 大力丸 加速
		isStrongStatus = true;
		strongStatusTimeCount = 0;
		role->appendHangerSpeed(VIGOROUSLY_PILL_POWER);
		//role->getHanger()->appendSpeedSelf(VIGOROUSLY_PILL_POWER);
		powerBuff = new PowerBuff(this);
		powerBuff->retain();
		break;
	case SKILL_ID_MOONLIGHT:
		// 月光宝盒 直接对关卡时间进行添加
		//gate->appendTime(15);
		//leaveTime += 15;
		isMoonLightStatus = true;
		moonLightStatusTimeCount = 0;
		if (timeAppendEffects == NULL)
		{
			timeAppendEffects = new CCArray();
		}
		timeAppendEffects->addObject(new TimeAppendEffect(this));
		addChild((TimeAppendEffect *)timeAppendEffects->lastObject(), LAYER_ORDER_CONTROL);
#ifdef								GOLDEN_MINER_2_VERSION_TIME
		timeCount = -10000.0;
#endif
		setLeaveTime(leaveTime + 15);
		break;
	}
	((Sensitization *)liuGuang->objectAtIndex(_skillId-1))->setVisible(false);
}

void GameControl::releaseSkills(int _skillId)
{
	switch (_skillId)
	{
	case SKILL_ID_GRENADE:
		addExplode(B_EXPLODE, explosive->getPositionX(), explosive->getPositionY());
		role->releaseExplosive(this);
		removeChild(explosive, true);
		explosive = NULL;
		//if(carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
		//{
		//	addExplode(B_EXPLODE, ((Target *)carryTargetPoint)->getPositionX(), ((Target *)carryTargetPoint)->getPositionY());
		//	((Target *)carryTargetPoint)->setStatus(TARGET_STATUS_REMOVE);
		//	role->getHanger()->setStatus(HANGER_STATUS_PULL_UNHAVING);
		//	role->setStatus(ROLE_STATUS_PULL_UNHAVING);
		//	role->getHanger()->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
		//	carryTargetPoint = NULL;
		//	carryTargetType = -1;
		//}
		//else if (carryTargetType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
		//{
		//	if (((DynamicTarget *)carryTargetPoint)->getId() == DYNAMIC_ID_SHELL)
		//	{
		//		addExplode(B_EXPLODE, ((DynamicTargetShell *)carryTargetPoint)->shellSprite->getPositionX(), ((DynamicTargetShell *)carryTargetPoint)->shellSprite->getPositionY());
		//	}
		//	else
		//	{
		//		addExplode(B_EXPLODE, ((DynamicTarget *)carryTargetPoint)->getArmature()->getPositionX(), ((DynamicTarget *)carryTargetPoint)->getArmature()->getPositionY());
		//	}
		//	((DynamicTarget *)carryTargetPoint)->setStatus(TARGET_STATUS_REMOVE);
		//	role->getHanger()->setStatus(HANGER_STATUS_PULL_UNHAVING);
		//	role->setStatus(ROLE_STATUS_PULL_UNHAVING);
		//	role->getHanger()->setSpeedTarget(0, TARGET_SPEED_TYPE_S);
		//	carryTargetPoint = NULL;
		//	carryTargetType = -1;
		//}
		//zhaDanSprite->setVisible(false);
		//isZhaDanStatus = false;
		break;
	case SKILL_ID_VIGOROUSLY_PILL:
		// 大力丸 加速
		powerBuff->removeSelf(this);
		CC_SAFE_RELEASE(powerBuff);
		powerBuff = NULL;
	
		isStrongStatus = false;
		strongStatusTimeCount = 0;
		role->appendHangerSpeed(-VIGOROUSLY_PILL_POWER);
		//role->getHanger()->appendSpeedSelf(-VIGOROUSLY_PILL_POWER);
		break;
	case SKILL_ID_MOONLIGHT:
		// 大力丸 加速
		isMoonLightStatus = false;
		moonLightStatusTimeCount = 0;
		break;
	}
	((Sensitization *)liuGuang->objectAtIndex(_skillId-1))->setVisible(false);
}

void GameControl::doJewelSkill(void)
{
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_SKILL);

	//if((gate != NULL) && (gate->getCanGoundDynamicTargetNum() == 0))
	//{// 只有有怪物才能出现 葫芦 和 晕   故此减去2
	//	jewelSkillId = rand() % (SKILL_ID_JEWEL_COUNT - 2);
	//}
	//else if(gate->getGoldenNum() == 0)
	//{// 只有有怪物才能出现 葫芦 和 晕   故此减去1
	//	jewelSkillId = rand() % (SKILL_ID_JEWEL_COUNT - 1);
	//	if (jewelSkillId > (SKILL_ID_JEWEL_MAGNET - 1))
	//	{
	//		jewelSkillId++;
	//	}
	//}
	//else
	//{
	//	jewelSkillId = rand() % SKILL_ID_JEWEL_COUNT ;
	//}

	jewelSkillId = rand()% SKILL_ID_JEWEL_COUNT;

	if (gate->getTargetTotalNum() == 0 || leaveTime < 3 || isPayJewel)
	{// 抓取最后一个对象则只释放掉金子的技能
		jewelSkillId = SKILL_ID_JEWEL_DROP;
	}

	switch(jewelSkillId)
	{
	case SKILL_ID_JEWEL_DROP:
		jewelSkillSprite = new JewelSkillDrop(this);
		break;
	case SKILL_ID_JEWEL_MAGNET:// 吸铁石  30°
		jewelSkillSprite = new JewelSkillMagnet(this, role->getHanger());
		addChild((JewelSkillMagnet *)jewelSkillSprite, LAYER_ORDER_CONTROL-1);
		break;
	case SKILL_ID_JEWEL_BALL:
		jewelSkillSprite = new JewelSkillBall(this, role->getHanger());
		addChild((JewelSkillBall *)jewelSkillSprite, LAYER_ORDER_CONTROL-1);
		break;
	//case SKILL_ID_JEWEL_DIZZY:// 所有怪物变成晕眩状态
	//	jewelSkillSprite = new JewelSkillDizzy(this);
	//	break;
	//case SKILL_ID_JEWEL_GOURD:
	//	jewelSkillSprite = new JewelSkillGourd(this, role->getHanger());
	//	addChild((JewelSkillGourd *)jewelSkillSprite, LAYER_ORDER_CONTROL-1);
	//	break;
	case SKILL_ID_JEWEL_FIVE_HANGER:
		jewelSkillSprite = new JewelSkillFiveHanger(this);
		break;
	default:
		break;
	}

	// 播放完成宝石的处理效果
	GameAppend * gameAppend = (GameAppend *)Global::getInstance()->s->getGameAppendLayer(this);
	setBackGround(true);
	Global::getInstance()->s->addLayerToRunningScene(gameAppend);

	gameAppend->doJewelSkillEffect(jewelSkillId);	
}

void GameControl::intersectCheck(void)
{
	//// 只有钩子是丢出状态才能去抓取物品
	//if (Global::getInstance()->getHangerStatus() == HANGER_STATUS_THROW)
	//{
	//	bool flag = true;

	//	CCRect rHanger = cocos2d::CCRectMake(
	//		role->getHanger()->getPosition().x - (role->getHanger()->getContentSize().width - INTERSECT_CONTROL)/2,
	//		role->getHanger()->getPosition().y - (role->getHanger()->getContentSize().height - INTERSECT_CONTROL)/2,
	//		role->getHanger()->getContentSize().width - INTERSECT_CONTROL,
	//		role->getHanger()->getContentSize().height - INTERSECT_CONTROL);
	//	
	//	// 钩子碰撞矩阵
	//	if (gate->getTargets() != NULL)	
	//	{
	//		// 遍历固定对象
	//		for(unsigned int i = 0; i < gate->getTargets()->count(); i++)
	//		{
	//			Target * tmp = (Target *)gate->getTargets()->objectAtIndex(i);
	//			if (tmp->isCanCarry())// 目标是可抓取的状态
	//			{
	//				// 抓取目标的碰撞矩阵
	//				CCRect rTmp = cocos2d::CCRectMake(
	//					tmp->getPosition().x - (tmp->getContentSize().width - INTERSECT_CONTROL)/2,
	//					tmp->getPosition().y - (tmp->getContentSize().height - INTERSECT_CONTROL)/2,
	//					tmp->getContentSize().width - INTERSECT_CONTROL,
	//					tmp->getContentSize().height - INTERSECT_CONTROL);
	//				if(rHanger.intersectsRect(rTmp))
	//				{
	//					flag = false;
	//					Player::getInstance()->getMusicControl()->stopEffect(MUSICCONTROL_EFFECT_ID_THROW);
	//					Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_CARRY_TARGET);
	//					tmp->intersectByHanger(this);
	//				}
	//			}
	//			if (!flag)
	//			{
	//				break;
	//			}
	//		}
	//	}

	//	// 遍历移动对象
	//	if (gate->getDynamicTargets() != NULL)
	//	{		
	//		if (flag)
	//		{
	//			for(unsigned int i = 0; i < gate->getDynamicTargets()->count(); i++)
	//			{
	//				DynamicTarget * tmp = (DynamicTarget *)gate->getDynamicTargets()->objectAtIndex(i);

	//				if (tmp->isCanCarried())// 可抓取状态
	//				{
	//					CCRect rTmp = cocos2d::CCRectMake(
	//						tmp->getArmature()->getPositionX() - (tmp->getWidth() - INTERSECT_CONTROL)/2,
	//						tmp->getArmature()->getPositionY() - (tmp->getHeight() - INTERSECT_CONTROL)/2,
	//						tmp->getWidth() - INTERSECT_CONTROL,
	//						tmp->getHeight() - INTERSECT_CONTROL);
	//					if(rHanger.intersectsRect(rTmp))
	//					{
	//						flag = false;
	//						Player::getInstance()->getMusicControl()->stopEffect(MUSICCONTROL_EFFECT_ID_THROW);
	//						Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_CARRY_TARGET);
	//						tmp->doIntersectWithHanger(this);
	//					}
	//				}
	//				if (!flag)
	//				{
	//					break;
	//				}
	//			}
	//		}
	//	}

	//	if (!flag)
	//	{
	//		if (Global::getInstance()->getHangerStatus() == HANGER_STATUS_PULL_HAVING)
	//		{
	//			if (carryTargetPoint != NULL)
	//			{
	//				if(carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
	//				{
	//					if (((Target *)carryTargetPoint)->getId() == TARGET_ID_STONE_B)
	//					{
	//						((Sensitization *)liuGuang->objectAtIndex(SKILL_ID_GRENADE-1))->setVisible(true);
	//					}
	//					else if (((Target *)carryTargetPoint)->getId() == TARGET_ID_GOLDEN_B)
	//					{
	//						((Sensitization *)liuGuang->objectAtIndex(SKILL_ID_VIGOROUSLY_PILL-1))->setVisible(true);
	//					}
	//					
	//					role->getHanger()->setSpeedTarget(((Target *)carryTargetPoint)->getSpeed(), ((Target *)carryTargetPoint)->getSpeedType());
	//					explodes->addObject(new Explode(HANGER_EXPLODE));
	//					((Explode *)explodes->lastObject())->setPosition(ccp(Global::getInstance()->getHangerCurrX(), Global::getInstance()->getHangerCurrY()));
	//					addChild((Explode *)explodes->lastObject(), LAYER_ORDER_CONTROL+1);
	//				}
	//				else if (carryTargetType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
	//				{
	//					role->getHanger()->setSpeedTarget(((DynamicTarget *)carryTargetPoint)->getSpeed(), ((DynamicTarget *)carryTargetPoint)->getSpeedType());
	//					explodes->addObject(new Explode(HANGER_EXPLODE));
	//					((Explode *)explodes->lastObject())->setPosition(ccp(Global::getInstance()->getHangerCurrX(), Global::getInstance()->getHangerCurrY()));
	//					addChild((Explode *)explodes->lastObject(), LAYER_ORDER_CONTROL+1);
	//				}
	//			}
	//			else
	//			{
	//				CCLOG("严重错误，钩子撞到物品，但是携带的指针存储为空");
	//			}
	//		}
	//	}
	//}

	if (gate->getDynamicTargets() != NULL)
	{
		for (unsigned int i = 0; i < gate->getDynamicTargets()->count(); i++)
		{
			DynamicTarget * tmpDynamicTarget = (DynamicTarget *)gate->getDynamicTargets()->objectAtIndex(i);
			CCRect rDynamicTarget = cocos2d::CCRectMake(
				tmpDynamicTarget->getArmature()->getPositionX() - (tmpDynamicTarget->getWidth() - INTERSECT_CONTROL)/2,
				tmpDynamicTarget->getArmature()->getPositionY() - (tmpDynamicTarget->getHeight() - INTERSECT_CONTROL)/2,
				tmpDynamicTarget->getWidth() - INTERSECT_CONTROL,
				tmpDynamicTarget->getHeight() - INTERSECT_CONTROL);
			bool flag = true;
			if ((gate->getTargets() != NULL) && ((tmpDynamicTarget->getStatus() == DYNAMIC_TARGET_STATUS_MOVING) || (tmpDynamicTarget->getStatus() == DYNAMIC_TARGET_STATUS_CARRIER_CARRIED)))//移动状态（即自由状态）
			{
				// 检测移动目标与静止目标的碰撞问题
				for (unsigned int j = 0; j < gate->getTargets()->count(); j++)
				{
					Target * tmp = (Target *)gate->getTargets()->objectAtIndex(j);
					if (tmpDynamicTarget->isIntersectById(tmp->getId()) && (tmp->getStatus() == TARGET_STATUS_NORMAL || tmp->getStatus() == TARGET_STATUS_CARRIER_CARRIED))// 目标是可抓取的状态
					{
						// 抓取目标的碰撞矩阵
						CCRect rTmp = cocos2d::CCRectMake(
							tmp->getPosition().x - (tmp->getContentSize().width - INTERSECT_CONTROL)/2,
							tmp->getPosition().y - (tmp->getContentSize().height - INTERSECT_CONTROL)/2,
							tmp->getContentSize().width - INTERSECT_CONTROL,
							tmp->getContentSize().height - INTERSECT_CONTROL);
						if(rDynamicTarget.intersectsRect(rTmp))
						{
							flag = false;
							tmpDynamicTarget->intersectWithTarget(tmp->getId(), tmp , this);
						}
					}
					if (!flag)
					{
						break;
					}
				}
			}
			//if (flag && ((tmpDynamicTarget->getStatus() == DYNAMIC_TARGET_STATUS_MOVING) || (tmpDynamicTarget->getStatus() == DYNAMIC_TARGET_STATUS_STATIC) || (tmpDynamicTarget->getStatus() == DYNAMIC_TARGET_STATUS_CARRIER_CARRIED)))
			//{
			//	// 检测移动目标与移动物体的碰撞问题
			//	for (unsigned int j = i + 1; j < gate->getDynamicTargets()->count(); j++)
			//	{
			//		bool flag = true;
			//		DynamicTarget * tmp = (DynamicTarget *)gate->getDynamicTargets()->objectAtIndex(j);
			//		if ((tmp->getStatus() == DYNAMIC_TARGET_STATUS_MOVING) || (tmp->getStatus() == DYNAMIC_TARGET_STATUS_STATIC) || (tmpDynamicTarget->getStatus() == DYNAMIC_TARGET_STATUS_CARRIER_CARRIED))
			//		{
			//			if (tmpDynamicTarget->isIntersectById(tmp->getId()))// 目标是可抓取的状态
			//			{
			//				// 抓取目标的碰撞矩阵
			//				CCRect rTmp = cocos2d::CCRectMake(
			//					tmp->getArmature()->getPositionX() - (tmp->getWidth() - INTERSECT_CONTROL)/2,
			//					tmp->getArmature()->getPositionY() - (tmp->getHeight() - INTERSECT_CONTROL)/2,
			//					tmp->getWidth() - INTERSECT_CONTROL,
			//					tmp->getHeight() - INTERSECT_CONTROL);
			//				if(rDynamicTarget.intersectsRect(rTmp))
			//				{
			//					flag = false;
			//					tmpDynamicTarget->intersectWithDynamicTarget(tmp->getId(), tmp , this);
			//				}
			//			}
			//			if (!flag)
			//			{
			//				break;
			//			}
			//		}
			//	}
			//}
		}
	}

	//if (biaozhunxian != NULL)
	//{
	//	if (carryTargetPoint != NULL)
	//	{
	//		biaozhunxian->setVisible(false);
	//	}
	//	else
	//	{
	//		biaozhunxian->setVisible(true);
	//	}
	//}
}

void GameControl::ccTouchesEnded(CCSet* touches, CCEvent* pevent)
{
	if (isGameOver)
	{
		return;
	}
	if (!isUpdate)
	{
		return;
	}
	if (isBackGroud)
	{
		return;
	}

	CCTouch* touch = (CCTouch*)( touches->anyObject() );
	CCPoint location = touch->getLocation();

	//if ((location.x < (roleSpeed->getPositionX() + roleSpeed->getContentSize().width/2)) 
	//	&& (location.x > (roleSpeed->getPositionX() - roleSpeed->getContentSize().width/2))
	//	&& (location.y < (roleSpeed->getPositionY() + roleSpeed->getContentSize().height/2))
	//	&& (location.y > (roleSpeed->getPositionY() - roleSpeed->getContentSize().height/2)))
	//{
	//	b++;
	//	if (b > 20)
	//	{
	//		b = -5;
	//	}
	//	role->getHanger()->setSpeedSelf(bb + b);
	//	return;
	//}
	//else if ((location.x < (sceneSpeed->getPositionX() + sceneSpeed->getContentSize().width/2)) 
	//	&& (location.x > (sceneSpeed->getPositionX() - sceneSpeed->getContentSize().width/2))
	//	&& (location.y < (sceneSpeed->getPositionY() + sceneSpeed->getContentSize().height/2))
	//	&& (location.y > (sceneSpeed->getPositionY() - sceneSpeed->getContentSize().height/2)))
	//{
	//	c++;
	//	if (c > 20)
	//	{
	//		c = -5;
	//	}
	//	role->getHanger()->setSpeedScene(cc + c);
	//	return;
	//}
	//else if ((location.x < (roleSwaySpeed->getPositionX() + roleSwaySpeed->getContentSize().width/2)) 
	//	&& (location.x > (roleSwaySpeed->getPositionX() - roleSwaySpeed->getContentSize().width/2))
	//	&& (location.y < (roleSwaySpeed->getPositionY() + roleSwaySpeed->getContentSize().height/2))
	//	&& (location.y > (roleSwaySpeed->getPositionY() - roleSwaySpeed->getContentSize().height/2)))
	//{
	//	d++;
	//	if (d > 20)
	//	{
	//		d = 0;
	//	}
	//	if (role->getHanger()->getSpeedAngle()>0)
	//	{
	//		role->getHanger()->setSpeedAngle(dd + d*0.2);
	//	}
	//	else
	//	{
	//		role->getHanger()->setSpeedAngle(-dd - d*0.2);
	//	}
	//	return;
	//}

	if (isJewel)
	{
		if (isDoJewelSkill && jewelSkillSprite->getStatus() == JEWEL_SKILL_SPRITE_STATUS_NORMAL)
		{
			jewelSkillSprite->doSkill(this);
			isDoJewelSkill = false;
		}
	}
	else
	{
		role->throwHanger(this);
	}
	//if(Global::getInstance()->getHangerCanThrow() && (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING))
	//{
	//	role->getHanger()->setStatus(HANGER_STATUS_THROW);
	//}

}

void GameControl::setGetCoinLabel(void)// 设置需要最少的铜钱值
{
	char _s[32];
	sprintf(_s, "%d",getCoinTmp);

	if (getCoinLabel != NULL)
	{
		removeChild(getCoinLabel);
		CC_SAFE_RELEASE(getCoinLabel);
	}
	getCoinLabel = CCLabelAtlas::create(_s, "youxi/guankashuzi.png", 12, 15, '0');
	int i = 0;
	int _getCoinTmp = getCoinTmp;
	while(1)
	{
		_getCoinTmp = _getCoinTmp / 10;
		if (_getCoinTmp > 0)
		{
			i++;
		}
		else
		{
			break;
		}
	}
	getCoinLabel->setPosition(ccp(getChildByTag(3)->getPositionX() - 23 - i*12, getChildByTag(3)->getPositionY() + 3));
	//if (getCoinTmp > 999)
	//{
	//	getCoinLabel->setScale(0.8);
	//}

	if (getCoinTmp >= leastCoin)
	{
		((CCSprite *)getChildByTag(2))->setPositionX(progressX);
		((CCSprite *)getChildByTag(2))->setTextureRect(*new CCRect(0,0,progressW,progressH));
	}
	else
	{
		((CCSprite *)getChildByTag(2))->setPositionX(progressX - progressW*(leastCoin - getCoinTmp)/leastCoin/2);
		((CCSprite *)getChildByTag(2))->setTextureRect(*new CCRect(0,0,progressW*getCoinTmp/leastCoin,progressH));
	}

	addChild(getCoinLabel);
	CC_SAFE_RETAIN(getCoinLabel);
}

void GameControl::updateJewelSkill(float _f)
{
	if (!isJewelAppendEffectsPause && jewelAppendEffects != NULL)
	{
		JewelAppendEffect * p;
		CCArray * removeIndexJewelAppendEffect = CCArray::create();

		for (int i = 0; i < jewelAppendEffects->count(); i++)
		{
			p = (JewelAppendEffect *)jewelAppendEffects->objectAtIndex(i);
			if (p->doAction(_f))
			{
				removeIndexJewelAppendEffect->addObject(CCInteger::create(i));
			}
		}
		// 移除该移除的对象
		for (unsigned int i = removeIndexJewelAppendEffect->count(); i >0; i--)
		{
			p = (JewelAppendEffect *)(jewelAppendEffects->objectAtIndex(((CCInteger *)removeIndexJewelAppendEffect->objectAtIndex(i-1))->getValue()));
			removeChild(p ,true);
			addJewelBomb(p->getAddNewJewelType());
			jewelAppendEffects->removeObject(p);
			removeIndexJewelAppendEffect->removeObjectAtIndex(i-1,true);
		}
	}
}

void GameControl::checkJewelSkill(float _f)										
{		
	updateJewelSkill(_f);
	//if (addNewJewelType != -1)
	//{
	//	flyTime += _f;
	//	switch(addNewJewelType)
	//	{
	//	case PROP_TYPE_JEWEL_BLUE:
	//		newJewelSystem->setPosition(ccp(Global::getInstance()->getHangerCurrX() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_BLUE_X - Global::getInstance()->getHangerCurrX()), Global::getInstance()->getHangerCurrY() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_BLUE_Y - Global::getInstance()->getHangerCurrY())));
	//		break;
	//	case PROP_TYPE_JEWEL_PURPLE:
	//		newJewelSystem->setPosition(ccp(Global::getInstance()->getHangerCurrX() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_PURPLE_X - Global::getInstance()->getHangerCurrX()), Global::getInstance()->getHangerCurrY() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_PURPLE_Y - Global::getInstance()->getHangerCurrY())));
	//		break;
	//	case PROP_TYPE_JEWEL_YELLOW:
	//		newJewelSystem->setPosition(ccp(Global::getInstance()->getHangerCurrX() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_YELLOW_X - Global::getInstance()->getHangerCurrX()), Global::getInstance()->getHangerCurrY() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_YELLOW_Y - Global::getInstance()->getHangerCurrY())));
	//		break;
	//	case PROP_TYPE_JEWEL_GREEN:
	//		newJewelSystem->setPosition(ccp(Global::getInstance()->getHangerCurrX() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_GREEN_X - Global::getInstance()->getHangerCurrX()), Global::getInstance()->getHangerCurrY() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_GREEN_Y - Global::getInstance()->getHangerCurrY())));
	//		break;
	//	case PROP_TYPE_JEWEL_RED:
	//		newJewelSystem->setPosition(ccp(Global::getInstance()->getHangerCurrX() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_RED_X - Global::getInstance()->getHangerCurrX()), Global::getInstance()->getHangerCurrY() + flyTime/ADD_NEW_JEWEL_FLY_TIME_LONG*(RED_JEWEL_RED_Y - Global::getInstance()->getHangerCurrY())));
	//		break;
	//	default:
	//		break;
	//	}
	//	if (flyTime >= ADD_NEW_JEWEL_FLY_TIME_LONG)
	//	{
	//		addJewelBomb(addNewJewelType);
	//		removeChild(newJewelSystem, true);
	//		addNewJewelType = -1;
	//	}
	//	return;
	//}

	bool _flag = true;									
	for (int i = PROP_TYPE_JEWEL_BLUE; i <= PROP_TYPE_JEWEL_PURPLE; i++)									
	{		
		if (currPropOwn[i] < (Player::getInstance()->getPropNum(i) + Global::getInstance()->getPropAwardNumById(i)))
		{
			if (currPropOwn[i] == 0)
			{
				currPropOwn[i] = 1;
				// 说明有获得新的宝石  添加宝石的效果
				//addNewJewel(i);
				//return;
				jewelAppendEffects->addObject(new JewelAppendEffect(this, i));
				addChild((JewelAppendEffect *)jewelAppendEffects->lastObject());
			}
			else
			{
				// 说明有获得已经拥有的宝石  平衡global信息
				Global::getInstance()->appendPropAwardGet(i, currPropOwn[i] - Player::getInstance()->getPropNum(i) - Global::getInstance()->getPropAwardNumById(i));
			}
		}
		
		if (currPropOwn[i] == 0)								
		{								
			_flag = false;						
		}								
	}									

	if (_flag)									
	{	
		isJewel = true;
		//isDoJewelSkill = true;
		//doJewelSkill();								
	}									
}		

//void GameControl::doAnimationCompleted(void)
//{
//	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"zhuan") == 0)
//	{
//		isBackGroud = false;
//	}
//}

cocos2d::CCPoint GameControl::getGetCoinLabelPosition(void)
{
	return getCoinLabel->getPosition();
}

int GameControl::getMinUnhavingJewelId(void)
{							
	for (int i = PROP_TYPE_JEWEL_BLUE; i <= PROP_TYPE_JEWEL_PURPLE; i++)									
	{		
		if (currPropOwn[i] == 0)
		{
			return i;
		}						
	}		
	return PROP_TYPE_JEWEL_BLUE;
}

void GameControl::startSelf(void)
{
	setVisible(true);
	setBackGroundWithOutGreyLayer(false);
	mAnimationManager->runAnimationsForSequenceNamed("zc");
}

void GameControl::setLoadingLayer(cocos2d::CCLayer * _layer)
{
	loadingLayer = _layer;

	if (loadingLayer == NULL)
	{
		setVisible(true);
	}
}

void GameControl::setBackGround(bool _isBackGround)
{
	if (_isBackGround == true)
	{
		Global::getInstance()->s->addLayerToRunningScene(greyLayer);
	}
	else
	{
		isPause = false;
		Global::getInstance()->s->removeLayerToRunningScene(greyLayer);
	}


	if (isUpdateProp)
	{
		isUpdateProp = false;

		//currPropOwn[PROP_TYPE_GRENADE] += Player::getInstance()->getPropNum(PROP_TYPE_GRENADE) - tmpProp1Num;
		//currPropOwn[PROP_TYPE_VIGOROUSLY_PILL] += Player::getInstance()->getPropNum(PROP_TYPE_VIGOROUSLY_PILL) - tmpProp2Num;
		//currPropOwn[PROP_TYPE_MOONLIGHT] += Player::getInstance()->getPropNum(PROP_TYPE_MOONLIGHT) - tmpProp3Num;

		getChildByTag(5)->removeChildByTag(PROP_NUM_TAG);
		getChildByTag(5)->addChild(getPropNumLable(PROP_TYPE_GRENADE),1, PROP_NUM_TAG);		
		getChildByTag(6)->removeChildByTag(PROP_NUM_TAG);
		getChildByTag(6)->addChild(getPropNumLable(PROP_TYPE_VIGOROUSLY_PILL),1,  PROP_NUM_TAG);	
		getChildByTag(7)->removeChildByTag(PROP_NUM_TAG);
		getChildByTag(7)->addChild(getPropNumLable(PROP_TYPE_MOONLIGHT),1,  PROP_NUM_TAG);
	}
	

	setLiZiTeXiaoVisible(!_isBackGround);
	isBackGroud = _isBackGround;
}

void GameControl::setBackGroundWithOutGreyLayer(bool _isBackGround)
{
	setLiZiTeXiaoVisible(!_isBackGround);
	isBackGroud = _isBackGround;
}

void GameControl::setLiZiTeXiaoVisible(bool _b)
{
	if (jewelAppendEffects != NULL)
	{
		for (int i = 0; i < jewelAppendEffects->count(); i++)
		{
			((JewelAppendEffect *)jewelAppendEffects->objectAtIndex(i))->setVisible(_b);
		}
	}

	if (scoreAppendEffects != NULL)
	{
		for (int i = 0; i < scoreAppendEffects->count(); i++)
		{
			((ScoreAppendEffect *)scoreAppendEffects->objectAtIndex(i))->setVisible(_b);
		}
	}

	if (countinueCountSprite != NULL)
	{
		countinueCountSprite->setVisible(_b);
		countinueCountNum->setVisible(_b);
	}

	isJewelAppendEffectsPause = !_b;
	isScoreAppendEffectsPause = !_b;
}

void GameControl::gameOver(void)
{
	setBackGround(true);
	Player::getInstance()->setGameLayer(NULL);
	Player::getInstance()->setGameLayerIsPause(true);
	if (isNewGate)
	{
		Player::getInstance()->setMapLastRoleId(Global::getInstance()->getMapIdByGateId(Global::getInstance()->getSelectGateId()), Global::getInstance()->getSelectRoleId());
		Player::getInstance()->getMusicControl()->stopLoopEffect();
		// 更新玩家的道具信息
		for(int i = PROP_TYPE_INGOT; i < PROP_TYPE_COUNT; i++)
		{
			if(i == PROP_TYPE_MEET)
			{
				Player::getInstance()->appendPropNum(i, Global::getInstance()->getPropAwardNumById(i));
				if(Global::getInstance()->getPropAwardNumById(i) > 0 && Player::getInstance()->getPropNum(i) > 99998)
				{
					Player::getInstance()->appendPropNum(i, 99999 - Global::getInstance()->getPropAwardNumById(i));
					isFoodFull = true;
				}
				Player::getInstance()->savePropNum(i,0);
			}
			else if(i > PROP_TYPE_INGOT && i < PROP_TYPE_ALIGNMENT)
			{
				Player::getInstance()->appendPropNum(i, Global::getInstance()->getPropAwardNumById(i));
				if(Global::getInstance()->getPropAwardNumById(i) > 0 && Player::getInstance()->getPropNum(i) > 98)
				{
					Player::getInstance()->appendPropNum(i, 99 - Global::getInstance()->getPropAwardNumById(i));
					isPropFull = true;
				}
				Player::getInstance()->savePropNum(i,0);
			}
			else
			{
				if (i == PROP_TYPE_INGOT)
				{// 将获得的铜钱转换为元宝
					getCoinNum = Global::getInstance()->getPropAwardNumById(PROP_TYPE_COIN);
					getStarNum = getStarNumByCoinAndGate(getCoinNum, leastCoin);
					getIngotNum = getIngotByCoin(getCoinNum);
					Player::getInstance()->appendPropNum(i, getIngotNum);
				}
				Player::getInstance()->appendPropNum(i, Global::getInstance()->getPropAwardNumById(i));
				Player::getInstance()->savePropNum(i,0);
			}
		}
		// 更新玩家的宠物信息
		for(int i = PET_ELEMENT_XIAOZUANFENG; i < PET_ELEMENT_COUNT; i++)
		{
			if (!Player::getInstance()->getPetHaving(i) && !Player::getInstance()->getPetBorn(i))
			{
				Player::getInstance()->appendPetElement(i, Global::getInstance()->getPetElementGetById(i));
				// 检测是否能够开启新的宠物(蛋变成宝宝)
				if (Global::getInstance()->getPetIsOpenByIdAndNum(i, Player::getInstance()->getPetElement(i)))
				{
					// 开启新宠物的动画
					Player::getInstance()->setPetBorn(i, true);   // 还有结算的页面没有做
					//Player::getInstance()->setPetHaving(i, true);
				}
			}	
		}
	}

	if (getCoinTmp >= leastCoin)
	{// 通关成功
		if (isNewGate)
		{
			// 本小关状态保存 （大于原先的才保存）
			Player::getInstance()->setGateLeverStatusByGateId(Global::getInstance()->getSelectGateId(), getStarNum);
			// 小关开启状态
			Player::getInstance()->setGateOpenStatusByGateId(Global::getInstance()->getSelectGateNextGateId(), true);
		}

		if (Global::getInstance()->getSelectGateNextGateId() == -1)
		{
			isNewGate = false;

			if(isOpenHideGate && checkHideGateOpen(Global::getInstance()->getSelectGateId() + 1))
			{
				PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMING);
				Global::getInstance()->s->addLayerToRunningScene(promptLayer);
				promptLayer->addNewHideGate(Global::getInstance()->getSelectGateId() + 1);
				Player::getInstance()->setGateOpenStatusByGateId(Global::getInstance()->getSelectGateId() + 1, true);
				isOpenHideGate = false;

				//Global::getInstance()->setSelectGateNextGateId(Global::getInstance()->getSelectGateId() + 1);

				return;
			}
			isOpenHideGate = false;

			if(isPropFull)
			{
				TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_GAMING);
				_layer->doPromptByType(TEMP_PROMPT_PROP_FULL);
				Global::getInstance()->s->addLayerToRunningScene(_layer);
				isPropFull = false;
				return;
			}
			if(isFoodFull)
			{
				TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_GAMING);
				_layer->doPromptByType(TEMP_PROMPT_FOOD_FULL);
				Global::getInstance()->s->addLayerToRunningScene(_layer);
				isFoodFull = false;
				return;
			}

			if (Global::getInstance()->getSelectGateId()%18 > 9)// 隐藏关卡  的  宝箱模式
			{
				//CCLOG("GameControl::gameOver         1");
				time_t  time1 = time(NULL);
				struct tm *tm;
				tm = localtime(&time1);
				int day = tm->tm_mday;
				day += tm->tm_mon * 100;
				day += tm->tm_year * 10000;

				if (day > Player::getInstance()->getHideGateDay())
				{
					// 更新时间 
					Player::getInstance()->setHideGateDay(day);
					Player::getInstance()->initHideGateDraw();
				}

				//CCLOG("GameControl::gameOver         2");
				if (Player::getInstance()->getHideGateDraw(Global::getInstance()->getSelectGateId()))
				{
					//CCLOG("GameControl::gameOver         3");
					Player::getInstance()->setHideGateDraw(Global::getInstance()->getSelectGateId(), false);
					//CCLOG("GameControl::gameOver         4");
					Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getDrawLayer(this));
					//CCLOG("GameControl::gameOver         5");
					if(Global::getInstance()->getSelectGateId()%18 != 12 && Player::getInstance()->getGateOpenStatusByGateId(Global::getInstance()->getSelectGateId() + 1))
					{
						//CCLOG("GameControl::gameOver         6");
						Global::getInstance()->setSelectGateNextGateId(Global::getInstance()->getSelectGateId() + 1);
						//CCLOG("GameControl::gameOver         7");
					}
					return;
				}
			}

			if (!Player::getInstance()->getCarttonIsPlay(CARTOON_END))
			{
				if(Global::getInstance()->getSelectGateId()%18 != 12 && Player::getInstance()->getGateOpenStatusByGateId(Global::getInstance()->getSelectGateId() + 1))
				{
					Global::getInstance()->setSelectGateNextGateId(Global::getInstance()->getSelectGateId() + 1);
				}
				this->setVisible(false);
				CartoonLayer * cartoonTmp = (CartoonLayer *)Global::getInstance()->s->getCartoonLayer(CARTOON_END, NULL);
				cartoonTmp->setNextLayer(0, this);
				Global::getInstance()->s->addLayerToRunningScene(cartoonTmp);
			}
			else
			{
				if(Global::getInstance()->getSelectGateId()%18 != 12 && Player::getInstance()->getGateOpenStatusByGateId(Global::getInstance()->getSelectGateId() + 1))
				{
					Global::getInstance()->setSelectGateNextGateId(Global::getInstance()->getSelectGateId() + 1);
				}
				Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getGameOverMenu(this, true));
			}

		}
		else
		{
			if (isNewGate &&(Global::getInstance()->getMapIdByGateId(Global::getInstance()->getSelectGateId()) != BIG_GATE_TYPE_LINGSHAN) && (Global::getInstance()->getSelectGateId()%18 == 9) && !Player::getInstance()->getMapOpenStatusByMapId(Global::getInstance()->getMapIdByGateId(Global::getInstance()->getSelectGateId() + 10)))
			{
				// 开始了新的map要播效果
				PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMING);
				Global::getInstance()->s->addLayerToRunningScene(promptLayer);
				promptLayer->addNewGate(Global::getInstance()->getMapIdByGateId(Global::getInstance()->getSelectGateNextGateId()));
				// 更新map开启状态
				Player::getInstance()->setMapOpenStatusByMapId(Global::getInstance()->getMapIdByGateId(Global::getInstance()->getSelectGateNextGateId() + 10), true);
				isNewGate = false;
				return;
			}
			isNewGate = false;

			if (isOpenChallenge && !Player::getInstance()->getChallengeIsOpen() && Player::getInstance()->getMapOpenStatusByMapId(BIG_GATE_TYPE_TONGYIANHE))
			{
				// 挑战模式开启的提示
				// 开始了新的map要播效果
				PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMING);
				Global::getInstance()->s->addLayerToRunningScene(promptLayer);
				promptLayer->challengeGateOpen();
				// 更新map开启状态
				Player::getInstance()->setChallengeIsOpen(true);
				isOpenChallenge = false;
				return;
			}
			isOpenChallenge = false;

			if(isOpenHideGate && checkHideGateOpen(Global::getInstance()->getSelectGateId() + 1))
			{
				PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMING);
				Global::getInstance()->s->addLayerToRunningScene(promptLayer);
				promptLayer->addNewHideGate(Global::getInstance()->getSelectGateId() + 1);
				Player::getInstance()->setGateOpenStatusByGateId(Global::getInstance()->getSelectGateId() + 1, true);
				isOpenHideGate = false;

				Global::getInstance()->setSelectGateNextGateId(Global::getInstance()->getSelectGateId() + 1);

				return;
			}
			isOpenHideGate = false;

			// 人物开启状态
			while(isNewRole < ROLE_TYPE_COUNT)
			{
				if (isNewRoleOpenByRoleId(isNewRole))
				{
					// 开始了新的人物要播效果
					PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMING);
					Global::getInstance()->s->addLayerToRunningScene(promptLayer);
					promptLayer->addNewRole();
					// 更新人物开启状态
					Player::getInstance()->setRoleOpenStatusByRoleId(isNewRole, true);
					Player::getInstance()->setOpenNewRole(true);
					isNewRole++;
					return;
				}
				else
				{
					isNewRole++;
				}
			}


			if(isPropFull)
			{
				TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_GAMING);
				_layer->doPromptByType(TEMP_PROMPT_PROP_FULL);
				Global::getInstance()->s->addLayerToRunningScene(_layer);
				isPropFull = false;
				return;
			}
			if(isFoodFull)
			{
				TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_GAMING);
				_layer->doPromptByType(TEMP_PROMPT_FOOD_FULL);
				Global::getInstance()->s->addLayerToRunningScene(_layer);
				isFoodFull = false;
				return;
			}


			if (Global::getInstance()->getSelectGateId()%18 > 9)// 隐藏关卡  的  宝箱模式
			{
				//CCLOG("GameControl::gameOver     2    1");
				time_t  time1 = time(NULL);
				struct tm *tm;
				tm = localtime(&time1);
				int day = tm->tm_mday;
				day += tm->tm_mon * 100;
				day += tm->tm_year * 10000;

				if (day > Player::getInstance()->getHideGateDay())
				{
					//CCLOG("GameControl::gameOver     2    2");
					// 更新时间 
					Player::getInstance()->setHideGateDay(day);
					Player::getInstance()->initHideGateDraw();
				}

				//CCLOG("GameControl::gameOver     2    3");
				if (Player::getInstance()->getHideGateDraw(Global::getInstance()->getSelectGateId()))
				{
					//CCLOG("GameControl::gameOver     2    4");
					Player::getInstance()->setHideGateDraw(Global::getInstance()->getSelectGateId(), false);
					Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getDrawLayer(this));
					//CCLOG("GameControl::gameOver     2    5");
					return;
				}
			}
			
			Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getGameOverMenu(this, true));
		}
	}
	else
	{// 通关失败

		if(isPropFull)
		{
			TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_GAMING);
			_layer->doPromptByType(TEMP_PROMPT_PROP_FULL);
			Global::getInstance()->s->addLayerToRunningScene(_layer);
			isPropFull = false;
			return;
		}
		if(isFoodFull)
		{
			TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_GAMING);
			_layer->doPromptByType(TEMP_PROMPT_FOOD_FULL);
			Global::getInstance()->s->addLayerToRunningScene(_layer);
			isFoodFull = false;
			return;
		}
		Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getGameOverMenu(this, false));
	}
}

bool GameControl::checkHideGateOpen(int _gateId)
{
	bool _flag = false;
	CCArray * _petElements = CCArray::create();
	if (Global::getInstance()->getPetElementIdByHideGateId(_gateId, _petElements) != 0)
	{
		_flag = true;
		for (int i = 0; i < _petElements->count(); i++)
		{
			if (Player::getInstance()->getPetHeart(((CCInteger *)_petElements->objectAtIndex(i))->getValue()) < Global::getInstance()->getPetHeartFull(((CCInteger *)_petElements->objectAtIndex(i))->getValue()))
			{
				_flag = false;
			}
		}
	}
	return _flag;
}

bool GameControl::isNewRoleOpenByRoleId(int _roleId)
{
	CCLOG("GameControl isNewRoleOpenByRoleId   _roleId = %d", _roleId);
	if (Player::getInstance()->getRoleOpenStatusByRoleId(_roleId))
	{
		CCLOG("GameControl isNewRoleOpenByRoleId   not open");
		return false;
	}
	else
	{
		bool res = false;
		CCLOG("GameControl isNewRoleOpenByRoleId   star=%d, maxLever=%d",Player::getInstance()->getStarSum(), Player::getInstance()->getChallengeMaxLevel());
		switch(_roleId)
		{
		case ROLE_TYPE_ZHUBAJIE:
			if (Player::getInstance()->getStarSum() > 9 && Player::getInstance()->getMapOpenStatusByMapId(BIG_GATE_TYPE_TONGYIANHE))
			{
				res = true;
			}
			break;
		case ROLE_TYPE_SHAHESHANG:
			if (Player::getInstance()->getStarSum() > 44 && Player::getInstance()->getMapOpenStatusByMapId(BIG_GATE_TYPE_NVERGUO))
			{
				res = true;
			}
			break;
		case ROLE_TYPE_XIAOLONGNV:
			if (Player::getInstance()->getChallengeMaxLevel() > 6 && Player::getInstance()->getMapOpenStatusByMapId(BIG_GATE_TYPE_LINGSHAN))
			{
				res = true;
			}
			break;
		default:
			break;
		}
		return res;
	}
}

int GameControl::getIngotByCoin(int _coin)
{
	int res =  Global::getInstance()->getMaxContinusesCount() + Global::getInstance()->getGetJewelCount();
	if (getStarNum == 2)
	{
		res += _coin*3/100;
	}
	else if (getStarNum == 3)
	{
		res += _coin*5/100;
	}
	else
	{
		res += _coin/100;
	}
	return res;
}

int GameControl::getStarNumByCoinAndGate(int _getCoinNum, int _leastCoin)
{
	int res = 0;

	if (_getCoinNum >= _leastCoin)
	{
		res = 1;
	}

	if (isBuddaha)
	{
		_leastCoin = _leastCoin*2;
	}

	float tmp = (_getCoinNum - _leastCoin) / ((float) _leastCoin);

	if (tmp > 0.6)
	{
		res = 3;
	}
	else if (tmp > 0.3)
	{
		res = 2;
	}

	return res;
}

void GameControl::doLiuGuang(float _f)
{
	for (int i = 0; i < liuGuang->count(); i++)
	{
		Sensitization * tmp = (Sensitization *)liuGuang->objectAtIndex(i);
		if (tmp->isVisible())
		{
			tmp->doAction(_f);
			if ((i == (SKILL_ID_MOONLIGHT - 1)))
			{
				if (leaveTime > 5)
				{
					((Sensitization *)liuGuang->objectAtIndex(SKILL_ID_MOONLIGHT-1))->setVisible(false);
				}
			}
			else
			{
				if (Global::getInstance()->getHangerStatus() != HANGER_STATUS_PULL_HAVING) // 根据是否拥有大金块和大石头的状态控制
				{
					((Sensitization *)liuGuang->objectAtIndex(i))->setVisible(false);
				}
			}
		}
	}

	if (lastTimeCountDownEffect->isVisible())
	{
		lastTimeCountDownEffect->doAction(_f);
	}

	if (timeAppendEffects != NULL)
	{
		TimeAppendEffect * p;
		CCArray * removeIndexTimeAppendEffect = CCArray::create();

		for (int i = 0; i < timeAppendEffects->count(); i++)
		{
			p = (TimeAppendEffect *)timeAppendEffects->objectAtIndex(i);
			if (p->doAction(_f))
			{
				removeIndexTimeAppendEffect->addObject(CCInteger::create(i));
			}
		}
		// 移除该移除的对象
		for (unsigned int i = removeIndexTimeAppendEffect->count(); i >0; i--)
		{
			removeChild((ScoreAppendEffect *)(timeAppendEffects->objectAtIndex(((CCInteger *)removeIndexTimeAppendEffect->objectAtIndex(i-1))->getValue())),true);
			timeAppendEffects->removeObjectAtIndex(((CCInteger *)removeIndexTimeAppendEffect->objectAtIndex(i-1))->getValue());
			removeIndexTimeAppendEffect->removeObjectAtIndex(i-1,true);
		}
	}
}

void GameControl::doExplode(float _f)
{
	CCArray * removeIndexExplode = CCArray::create();

	for(unsigned int i = 0; i < explodes->count(); i++)
	{
		Explode * tmp = ((Explode  *)explodes->objectAtIndex(i));
		if(tmp->doAction(_f))
		{
			removeIndexExplode->addObject(CCInteger::create(i));
		}
	}

	// 移除该移除的对象
	for (unsigned int i = removeIndexExplode->count(); i >0; i--)
	{
		removeChild((Explode *)(explodes->objectAtIndex(((CCInteger *)removeIndexExplode->objectAtIndex(i-1))->getValue())),true);
		explodes->removeObject((Explode *)(explodes->objectAtIndex(((CCInteger *)removeIndexExplode->objectAtIndex(i-1))->getValue())),true);
		removeIndexExplode->removeObjectAtIndex(i-1,true);
	}

	if (powerBuff != NULL)
	{
		powerBuff->doAction(_f);
	}
}

void GameControl::finishRoleSkillEffect(void)
{
	role->doSkill(this);
}

void GameControl::finishJewelSkillEffect(void)
{
	if (!isPayJewel)
	{
		for (int i = PROP_TYPE_JEWEL_BLUE; i <= PROP_TYPE_JEWEL_PURPLE; i++)									
		{	
			// 减去消耗的宝石
			currPropOwn[i] = 0;
			((CCSprite *)jewelSprites->objectAtIndex(i - PROP_TYPE_JEWEL_BLUE))->setVisible(false);
			Global::getInstance()->appendPropAwardGet(i, currPropOwn[i] - Player::getInstance()->getPropNum(i) - Global::getInstance()->getPropAwardNumById(i));// 可以存储负值			
		}	
		//jewelSkillId = -1;
	}
	isPayJewel = false;
}

void GameControl::finishDraw(void)
{
	Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getGameOverMenu(this, true));
}

void GameControl::setTipId(int _tipId)
{
	tipId = _tipId;
}

cocos2d::CCLabelAtlas * GameControl::getPropNumLable(int _propId)
{
	char _s[64];

	int num = Player::getInstance()->getPropNum(_propId);
	//int num = currPropOwn[_propId];
	if(num > 99)
	{
		num = 99;
	}
	sprintf(_s, "%d", num);
	int i = 0;
	while(1)
	{
		num = num / 10;
		if (num > 0)
		{
			i++;
		}
		else
		{
			break;
		}
	}
	CCLabelAtlas * res = CCLabelAtlas::create(_s, "youxi/shuzi1.png", 9, 14, '0');
	res->setPosition(ccp(-4*i + 7,5));
	return res;
}


/********************************************************************
引导相关
************************************************************************/
GuideLayer::GuideLayer(void)
: GameControl()
{
	type = GAMEING_GUIDE;
}


void GuideLayer::setGuideLayer(int _guideId)
{
	setVisible(true);

	step = 0;
	checkStep = -1;
	isStepGetAward = false;
	stepTargets = NULL;

	Global::getInstance()->setCurrGuideId(_guideId);
	Player::getInstance()->setGuideLastIndex(Global::getInstance()->getCurrGuideId());

	guideId = _guideId;
	for (int i = 0; i < GUIDE_ID_JEWEIL_SKILL; i++)
	{
		touchCost[i] = false;
	}
	touchCost[guideId-1] = true;
	int _gateId;
	int _roleId;
	switch (_guideId)
	{
	case GUIDE_ID_PILL:
		_gateId = 995;
		_roleId = ROLE_TYPE_TANGSENG;
		// 初始化当前道具的拥有情况
		//for (int i = PROP_TYPE_COIN; i < PROP_TYPE_COUNT; i++)
		//{
		//	if (i == PROP_TYPE_VIGOROUSLY_PILL)
		//	{
		//		
		//		playerPropNum[i] = Player::getInstance()->getPropNum(i);
		//		Player::getInstance()->appendPropNum(i, 1);
		//	}
		//	else
		//	{
		//		playerPropNum[i] = Player::getInstance()->getPropNum(i);
		//		Player::getInstance()->appendPropNum(i, -playerPropNum[i]);
		//	}
		//}
		break;
	case GUIDE_ID_GRENADE:
		_gateId = 996;
		_roleId = ROLE_TYPE_TANGSENG;
		// 初始化当前道具的拥有情况
		//for (int i = PROP_TYPE_COIN; i < PROP_TYPE_COUNT; i++)
		//{
		//	if (i == PROP_TYPE_GRENADE)
		//	{
		//		playerPropNum[i] = Player::getInstance()->getPropNum(i);
		//		Player::getInstance()->appendPropNum(i, 1-playerPropNum[i]);
		//	}
		//	else
		//	{
		//		playerPropNum[i] = Player::getInstance()->getPropNum(i);
		//		Player::getInstance()->appendPropNum(i, -playerPropNum[i]);
		//	}
		//}
		break;
	case GUIDE_ID_MOONLIGHT:
		_gateId = 997;
		_roleId = ROLE_TYPE_TANGSENG;
		// 初始化当前道具的拥有情况
		//for (int i = PROP_TYPE_COIN; i < PROP_TYPE_COUNT; i++)
		//{
		//	if (i == PROP_TYPE_MOONLIGHT)
		//	{
		//		playerPropNum[i] = Player::getInstance()->getPropNum(i);
		//		Player::getInstance()->appendPropNum(i, 1-playerPropNum[i]);
		//	}
		//	else
		//	{
		//		playerPropNum[i] = Player::getInstance()->getPropNum(i);
		//		Player::getInstance()->appendPropNum(i, -playerPropNum[i]);
		//	}
		//}
		break;
	case GUIDE_ID_ROLE_SKILL:
		_gateId = 998;
		_roleId = ROLE_TYPE_SUNWUKONG;
		//// 初始化当前道具的拥有情况
		//for (int i = PROP_TYPE_COIN; i < PROP_TYPE_COUNT; i++)
		//{
		//	playerPropNum[i] = Player::getInstance()->getPropNum(i);
		//	Player::getInstance()->appendPropNum(i, -playerPropNum[i]);
		//}
		break;
	case GUIDE_ID_JEWEIL_SKILL:
		_gateId = 999;
		_roleId = ROLE_TYPE_ZHUBAJIE;
		//// 初始化当前道具的拥有情况
		for (int i = PROP_TYPE_COIN; i < PROP_TYPE_COUNT; i++)
		{
			if ((i < PROP_TYPE_JEWEL_BLUE))
			{
			}
			else if ((i == PROP_TYPE_JEWEL_YELLOW))
			{
				if (Player::getInstance()->getPropNum(i) > 0)
				{
					Player::getInstance()->appendPropNum(i, -Player::getInstance()->getPropNum(i));
				}
			}
			else
			{
				if (Player::getInstance()->getPropNum(i) == 0)
				{
					Player::getInstance()->appendPropNum(i, 1);
				}
			}

			//if ((i == PROP_TYPE_JEWEL_YELLOW) || (i < PROP_TYPE_JEWEL_BLUE))
			//{
			//	playerPropNum[i] = Player::getInstance()->getPropNum(i);
			//	Player::getInstance()->appendPropNum(i, -playerPropNum[i]);
			//}
			//else
			//{
			//	playerPropNum[i] = Player::getInstance()->getPropNum(i);
			//	Player::getInstance()->appendPropNum(i, 1-playerPropNum[i]);
			//}
		}
		break;
#ifdef									GOLDEN_MINER_2_NEW_GUIDE
	case GUIDE_ID_FRIST:
		_gateId = 997;
		_roleId = ROLE_TYPE_TANGSENG;
		break;
#endif
	default:
		_gateId = 994;
		_roleId = ROLE_TYPE_TANGSENG;
		//// 初始化当前道具的拥有情况
		//for (int i = PROP_TYPE_COIN; i < PROP_TYPE_COUNT; i++)
		//{
		//	playerPropNum[i] = Player::getInstance()->getPropNum(i);
		//	Player::getInstance()->appendPropNum(i, -playerPropNum[i]);
		//}
		break;
	}

	// 提示点击的手指头
	isFinger = 0;
	finger = new Finger();
	finger->setVisible(false);
	addChild(finger, 999*2);
	isCheck = true;
	isIntroduce = false;
	isTouchIntroduce = false;
	checkIsTouchIntroduce = false;

	// 技能状态初始化
	isStrongStatus = false;// 不在大力丸状态
	strongStatusTimeCount = 0;// 大力丸时间计数
	//isZhaDanStatus = false;// 不在大力丸状态
	//zhaDanStatusTimeCount = 0;// 大力丸时间计数
	isMoonLightStatus = false;// 不在大力丸状态
	moonLightStatusTimeCount = 0;// 大力丸时间计数
	isJewel = false;
	isTiming = true;
	isStartCountDownEffect = false;
	isTouchButton = false;
	//flyTimeScore = ADD_NEW_SCORE_FLY_TIME_LONG;
	//flyTimeContinue = ADD_NEW_SCORE_FLY_TIME_LONG;

	getCoinTmp = -1;
	isDoJewelSkill = false;
	isBackGroud = false;
#ifdef								GOLDEN_MINER_2_VERSION_TIME
	timeCount = -10000.0;
#else
	timeCount = SCHEDULE_TIMES;
#endif
	//addNewJewelType = -1;
	// 爆炸对象初始化
	explodes = new CCArray();

	// 初始化当前道具的拥有情况
	for (int i = PROP_TYPE_COIN; i < PROP_TYPE_COUNT; i++)
	{
		if (i == PROP_TYPE_COIN)
		{
			currPropOwn[i] = 0;
		}
		else
		{
			currPropOwn[i] = Player::getInstance()->getPropNum(i);
		}
	}

	// 初始化对应物品的价值倍数
	Global::getInstance()->initContinuesCount();
	Global::getInstance()->initValueTimes();
	Global::getInstance()->initPropAwardGet();
	Global::getInstance()->initPetElementGet();
	Global::getInstance()->initCurrGameLayerLoadDynamicTarget();

	// 根据关卡id创建关卡
	gate = Gate::getInstance(_gateId, this);

	// 对已经拥有的道具进行初始化
	role = Role::getInstance(_roleId, this, 325, 380, 400, 350, 0.8);
	//role = Role::getInstance(_roleId, this, 400, 392, 400, 350, 0.8);
	role->retain();
	// 关卡显示相关初始化
	CCSprite * _tmp = NULL;
	//CCSprite * _tmp = CCSprite::create("youxi/diduosg.png");
	//_tmp->setPosition(ccp(getChildByTag(3)->getPositionX() - 14, getChildByTag(3)->getPositionY()- 14));
	//addChild(_tmp);
	//_tmp = CCSprite::create("youxi/henxian.png");
	//_tmp->setPosition(ccp(getChildByTag(3)->getPositionX() - 19, getChildByTag(3)->getPositionY()- 14));
	//addChild(_tmp);
	_tmp = CCSprite::create("youxi/xiexian.png");
	_tmp->setPosition(ccp(getChildByTag(3)->getPositionX() - 6, getChildByTag(3)->getPositionY() + 10));
	addChild(_tmp);

	jewelSkillId = -1;

	CCSize s = CCDirector::sharedDirector()->getWinSize();  

	greyLayer = CCLayerColor::create(myGrey4);
	greyLayer->retain();

	spotLightLayer = NULL;
	//greyLayer1 = CCLayerColor::create(myGrey4);
	//greyLayer1->retain();
	//greyLayer2 = CCLayerColor::create(myGrey4);
	//greyLayer2->retain();

	progressW = getChildByTag(2)->getContentSize().width;
	progressH = getChildByTag(2)->getContentSize().height;
	progressX = getChildByTag(2)->getPositionX();
	((CCSprite *)getChildByTag(2))->setPositionX(progressX - progressW/2);
	((CCSprite *)getChildByTag(2))->setTextureRect(*new CCRect(0,0,0,0));

	role->setIsHaveAlignment(true);
	//// 瞄准线
	//biaozhunxian = CCSprite::create("youxi/xian2.png");
	//biaozhunxian->setScaleX(0.65);
	//addChild(biaozhunxian, LAYER_ORDER_CONTROL-2);

	getChildByTag(999)->setZOrder(LAYER_ORDER_CONTROL);
#ifdef										GAME_LAYER_JEWEL_IS_BUTTON
#else
	getChildByTag(4)->setZOrder(LAYER_ORDER_CONTROL);
#endif
	getChildByTag(5)->setZOrder(LAYER_ORDER_CONTROL);//左上方
	getChildByTag(5)->addChild(getPropNumLable(PROP_TYPE_GRENADE),1, PROP_NUM_TAG);	
	getChildByTag(6)->setZOrder(LAYER_ORDER_CONTROL);//左中间
	getChildByTag(6)->addChild(getPropNumLable(PROP_TYPE_VIGOROUSLY_PILL),1, PROP_NUM_TAG);	
	getChildByTag(7)->setZOrder(LAYER_ORDER_CONTROL);//左下角
	getChildByTag(7)->addChild(getPropNumLable(PROP_TYPE_MOONLIGHT),1,  PROP_NUM_TAG);

	_tmp = CCSprite::create("youxi/zhadan.png");
	_tmp->setPosition(ccp(58, 281));
	_tmp->setScale(0.6);
	addChild(_tmp, LAYER_ORDER_CONTROL, PROP_GRENADE_TAG);
	_tmp = CCSprite::create("youxi/liliang.png");
	_tmp->setPosition(ccp(58, 191));
	_tmp->setScale(0.6);
	addChild(_tmp, LAYER_ORDER_CONTROL, PROP_PILL_TAG);
	_tmp = CCSprite::create("youxi/shalou.png");
	_tmp->setPosition(ccp(58, 96));
	_tmp->setScale(0.6);
	addChild(_tmp, LAYER_ORDER_CONTROL, PROP_MOONLIGHT_TAG);
	liuGuang = new CCArray();
	liuGuang->addObject(new Sensitization(SENSITIZATION_TYPE_RECT));
	((Sensitization *)liuGuang->lastObject())->setPosition(ccp(58, 281));
	((Sensitization *)liuGuang->lastObject())->setVisible(false);
	addChild((Sensitization *)liuGuang->lastObject(), LAYER_ORDER_CONTROL);
	liuGuang->addObject(new Sensitization(SENSITIZATION_TYPE_RECT));
	((Sensitization *)liuGuang->lastObject())->setPosition(ccp(58, 191));
	((Sensitization *)liuGuang->lastObject())->setVisible(false);
	addChild((Sensitization *)liuGuang->lastObject(), LAYER_ORDER_CONTROL);
	liuGuang->addObject(new Sensitization(SENSITIZATION_TYPE_RECT));
	((Sensitization *)liuGuang->lastObject())->setPosition(ccp(58, 96));
	((Sensitization *)liuGuang->lastObject())->setVisible(false);
	addChild((Sensitization *)liuGuang->lastObject(), LAYER_ORDER_CONTROL);
	lastTimeCountDownEffect = new LastTimeCountEffect(0);
	lastTimeCountDownEffect->setPosition(ccp(getChildByTag(1)->getPositionX() - 3.5, getChildByTag(1)->getPositionY() - 2));
	lastTimeCountDownEffect->setVisible(false);
	addChild(lastTimeCountDownEffect, LAYER_ORDER_CONTROL);
	//liuGuang->addObject(new Sensitization(SENSITIZATION_TYPE_TIME));
	//((Sensitization *)liuGuang->lastObject())->setPosition(ccp(getChildByTag(1)->getPositionX() - 4, getChildByTag(1)->getPositionY() - 2));
	//((Sensitization *)liuGuang->lastObject())->setVisible(false);
	//addChild((Sensitization *)liuGuang->lastObject(), LAYER_ORDER_CONTROL+2);

	// 初始化宝石显示　　
	jewelSprites = new cocos2d::CCArray();
	jewelSprites->addObject(CCSprite::create("youxi/lan.png"));
	((CCSprite *)jewelSprites->lastObject())->setPosition(ccp(766.4, 240.8));
	jewelSprites->addObject(CCSprite::create("youxi/hong.png"));
	((CCSprite *)jewelSprites->lastObject())->setPosition(ccp(754.1, 207.3));
	jewelSprites->addObject(CCSprite::create("youxi/lv.png"));
	((CCSprite *)jewelSprites->lastObject())->setPosition(ccp(717.8, 207.9));
	jewelSprites->addObject(CCSprite::create("youxi/huang.png"));
	((CCSprite *)jewelSprites->lastObject())->setPosition(ccp(707.3, 240.1));
	jewelSprites->addObject(CCSprite::create("youxi/zi.png"));
	((CCSprite *)jewelSprites->lastObject())->setPosition(ccp(736.1, 264.4));

	if (step > 0 && stepTargets != NULL)
	{
		setCheckStep(1);
	}


	switch (guideId)
	{
	case GUIDE_ID_GRAP:
	case GUIDE_ID_PILL:
		getChildByTag(6)->setVisible(false);
		getChildByTag(999)->getChildByTag(6)->setVisible(false);
		getChildByTag(PROP_PILL_TAG)->setVisible(false);
		getChildByTag(6)->getChildByTag(PROP_NUM_TAG)->setVisible(false);
	case GUIDE_ID_GRENADE:
		getChildByTag(5)->setVisible(false);
		getChildByTag(999)->getChildByTag(5)->setVisible(false);
		getChildByTag(PROP_GRENADE_TAG)->setVisible(false);
		getChildByTag(5)->getChildByTag(PROP_NUM_TAG)->setVisible(false);
	case GUIDE_ID_MOONLIGHT:
		getChildByTag(7)->setVisible(false);
		getChildByTag(999)->getChildByTag(7)->setVisible(false);
		getChildByTag(PROP_MOONLIGHT_TAG)->setVisible(false);
		getChildByTag(7)->getChildByTag(PROP_NUM_TAG)->setVisible(false);
	case GUIDE_ID_ROLE_SKILL:
		role->setSkillVisible(false);
		getChildByTag(999)->getChildByTag(8)->setVisible(false);
	case GUIDE_ID_JEWEIL_SKILL:
		for (int i = 0; i <= (PROP_TYPE_JEWEL_PURPLE - PROP_TYPE_JEWEL_BLUE); i++)
		{
			addChild((CCSprite *)jewelSprites->objectAtIndex(i));
			//if (guideId == GUIDE_ID_JEWEIL_SKILL)
			//{
			//	if (0 == currPropOwn[i + PROP_TYPE_JEWEL_BLUE])
			//	{
			//		((CCSprite *)jewelSprites->objectAtIndex(i))->setVisible(false);
			//	}
			//	else
			//	{
			//		((CCSprite *)jewelSprites->objectAtIndex(i))->setVisible(true);
			//	}
			//}
			((CCSprite *)jewelSprites->objectAtIndex(i))->setVisible(false);

			((CCSprite *)jewelSprites->objectAtIndex(i))->setZOrder(LAYER_ORDER_CONTROL);
		}
#ifdef										GAME_LAYER_JEWEL_IS_BUTTON
		getChildByTag(999)->getChildByTag(9)->setVisible(false);
#else
		getChildByTag(4)->setVisible(false);
#endif
	}
	targetTotalNum = gate->getTargetTotalNum();
	if (guideId == GUIDE_ID_ROLE_SKILL || guideId == GUIDE_ID_JEWEIL_SKILL)
	{
		isStartCountDownEffect = true;
	}	

	if (loadingLayer != NULL)
	{
		setBackGroundWithOutGreyLayer(true);
		((LoadingLayer *)loadingLayer)->appendFinishLayerNum(1);
	}
	else
	{
		startSelf();
	}

	schedule( schedule_selector(GuideLayer::doAction), 0);
	setTouchEnabled(true);
	setKeypadEnabled(true);
	isJiangLiTip = true;
}

GuideLayer::~GuideLayer(void)
{
	CCLOG("GuideLayer::~GuideLayer");
}

SEL_MenuHandler GuideLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnProp1", GuideLayer::onMenuItemProp1Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnProp2", GuideLayer::onMenuItemProp2Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnProp3", GuideLayer::onMenuItemProp3Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnSkill", GuideLayer::onMenuItemSkillClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnPause", GuideLayer::onMenuItemPauseClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnGem", GameControl::onMenuItemGemClicked);

	return NULL;
}

SEL_CCControlHandler GuideLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool GuideLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void GuideLayer::setStepNum(int _step)
{
	if (_step > step)
	{
		step = _step;
	}
}

void GuideLayer::addStepTarget(CCObject * p)
{
	if (stepTargets == NULL)
	{
		stepTargets = new CCArray();
	}
	stepTargets->addObject(p);
}

void GuideLayer::setCheckStep(int _checkStep)
{
	checkStep = _checkStep;

	if (Global::getInstance()->getCurrGuideId() == GUIDE_ID_FRIST)
	{
		switch(checkStep)
		{
		case 1:
			guideId = GUIDE_ID_GRAP;
			isIntroduce = false;
			break;
		case 2:
			guideId = GUIDE_ID_PILL;
			isTouchButton = false;
			isIntroduce = false;
			isCheck = true;
			touchCost[guideId-1] = true;
			break;
		case 3:
			guideId = GUIDE_ID_GRENADE;
			isTouchButton = false;
			isCheck = true;
			isIntroduce = false;
			touchCost[guideId-1] = true;
			break;
		case 4:
			guideId = GUIDE_ID_MOONLIGHT;
			isTouchButton = false;
			isIntroduce = false;
			isCheck = true;
			touchCost[guideId-1] = true;
			break;
		case 5:
			guideId = GUIDE_ID_GRENADE;
			isCheck = false;
			isIntroduce = true;
			touchCost[guideId-1] = false;
			break;
		default:
			break;
		}
	}
	//else if (Global::getInstance()->getCurrGuideId() == GUIDE_ID_ROLE_SKILL)
	//{
	//}
	//else if (Global::getInstance()->getCurrGuideId() == GUIDE_ID_JEWEIL_SKILL)
	//{
	//}
}

void GuideLayer::onMenuItemProp1Clicked(cocos2d::CCObject * pSender)
{
	if (isGameOver)
	{
		return;
	}
	if (guideId == GUIDE_ID_JEWEIL_SKILL)
	{
		if (checkStep < 3)
		{
			return;
		}
	}
	else if (guideId == GUIDE_ID_ROLE_SKILL)
	{
		if (checkStep < 3)
		{
			return;
		}
	}
	if (guideId == GUIDE_ID_GRENADE)
	{
		if (isBackGroud)
		{
			if (isTouchIntroduce)
			{
				return;
			}
			else
			{
				if (checkIsTouchIntroduce)
				{
					checkIsTouchIntroduce = false;
					return;
				}
			}
			if (isFinger == 2)
			{
				isTouchButton = true;
				isFinger = 0;
				finger->setVisible(false);
				setBackGroundWithOutGreyLayer(false);

				removeChild(spotLightLayer, true);
			}
			else
			{
				return;
			}
		}
	}

	if (isBackGroud)
	{
		return;
	}
	// 这里注意什么样的控制条件
	//if (carryTargetPoint == NULL)
	//{
	//	return;
	//}
	//if (isZhaDanStatus)
	//{
	//	return;
	//}
	if (!role->canDoExplosive())
	{
		return;
	}
	if (explosive != NULL)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	if (touchCost[GUIDE_ID_GRENADE-1])
	{
		doSkills(SKILL_ID_GRENADE);
		touchCost[GUIDE_ID_GRENADE-1] = false;
		return;
	}
	

	// 判断道具是否还有
	if(Player::getInstance()->getPropNum(PROP_TYPE_GRENADE) > 0)
	{
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_PROP);

		// 道具即时扣除
		Player::getInstance()->appendPropNum(PROP_TYPE_GRENADE, -1);
		Player::getInstance()->savePropNum(PROP_TYPE_GRENADE,0);
		//currPropOwn[PROP_TYPE_GRENADE]--;
		//Global::getInstance()->appendPropAwardGet(PROP_TYPE_GRENADE, -1);// 可以存储负值
		getChildByTag(5)->removeChildByTag(PROP_NUM_TAG);
		getChildByTag(5)->addChild(getPropNumLable(PROP_TYPE_GRENADE),1, PROP_NUM_TAG);		
		doSkills(SKILL_ID_GRENADE);
	}
}

void GuideLayer::onMenuItemProp2Clicked(cocos2d::CCObject * pSender)
{
	if (isGameOver)
	{
		return;
	}
	if (guideId == GUIDE_ID_PILL)
	{
		if (isBackGroud)
		{
			if (isTouchIntroduce)
			{
				return;
			}
			else
			{
				if (checkIsTouchIntroduce)
				{
					checkIsTouchIntroduce = false;
					return;
				}
			}
			if (isFinger == 2)
			{
				isTouchButton = true;
				isFinger = 0;
				finger->setVisible(false);
				setBackGroundWithOutGreyLayer(false);

				removeChild(spotLightLayer, true);
			}
			else
			{
				return;
			}
		}
	}

	if (isBackGroud)
	{
		return;
	}
	if (isStrongStatus)
	{
		return;
	}

	if (touchCost[GUIDE_ID_PILL-1])
	{
		doSkills(SKILL_ID_VIGOROUSLY_PILL);
		touchCost[GUIDE_ID_PILL-1] = false;
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	// 判断道具是否还有
	if(Player::getInstance()->getPropNum(PROP_TYPE_VIGOROUSLY_PILL) > 0)
	{
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_PROP);

		// 道具即时扣除
		Player::getInstance()->appendPropNum(PROP_TYPE_VIGOROUSLY_PILL, -1);
		Player::getInstance()->savePropNum(PROP_TYPE_VIGOROUSLY_PILL,0);
		//currPropOwn[PROP_TYPE_VIGOROUSLY_PILL]--;
		//Global::getInstance()->appendPropAwardGet(PROP_TYPE_VIGOROUSLY_PILL, -1);// 可以存储负值
		getChildByTag(6)->removeChildByTag(PROP_NUM_TAG);
		getChildByTag(6)->addChild(getPropNumLable(PROP_TYPE_VIGOROUSLY_PILL),1,  PROP_NUM_TAG);	
		doSkills(SKILL_ID_VIGOROUSLY_PILL);
	}
}

void GuideLayer::onMenuItemProp3Clicked(cocos2d::CCObject * pSender)
{
	if (isGameOver)
	{
		return;
	}
	if (guideId == GUIDE_ID_MOONLIGHT)
	{
		if (isBackGroud)
		{
			if (isTouchIntroduce)
			{
				return;
			}
			else
			{
				if (checkIsTouchIntroduce)
				{
					checkIsTouchIntroduce = false;
					return;
				}
			}
			if (isFinger == 2)
			{
				isTouchButton = true;
				isFinger = 0;
				finger->setVisible(false);
				setBackGroundWithOutGreyLayer(false);

				removeChild(spotLightLayer, true);
			}
			else
			{
				return;
			}
		}
	}

	if (isBackGroud)
	{
		return;
	}
	if (isMoonLightStatus)
	{
		return;
	}

	if (touchCost[GUIDE_ID_MOONLIGHT-1])
	{
		doSkills(SKILL_ID_MOONLIGHT);
		touchCost[GUIDE_ID_MOONLIGHT-1] = false;
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	// 判断道具是否还有
	if(Player::getInstance()->getPropNum(PROP_TYPE_MOONLIGHT) > 0)
	{
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_PROP);

		// 道具即时扣除
		Player::getInstance()->appendPropNum(PROP_TYPE_MOONLIGHT, -1);
		Player::getInstance()->savePropNum(PROP_TYPE_MOONLIGHT,0);
		//currPropOwn[PROP_TYPE_MOONLIGHT]--;
		//Global::getInstance()->appendPropAwardGet(PROP_TYPE_MOONLIGHT, -1);// 可以存储负值
		getChildByTag(7)->removeChildByTag(PROP_NUM_TAG);
		getChildByTag(7)->addChild(getPropNumLable(PROP_TYPE_MOONLIGHT),1,  PROP_NUM_TAG);
		doSkills(SKILL_ID_MOONLIGHT);
	}
}

void GuideLayer::onMenuItemSkillClicked(cocos2d::CCObject * pSender)
{
	if (isGameOver)
	{
		return;
	}
	if (guideId == GUIDE_ID_ROLE_SKILL)
	{
		if (isBackGroud)
		{
			if (isTouchIntroduce)
			{
				return;
			}
			else
			{
				if (checkIsTouchIntroduce)
				{
					checkIsTouchIntroduce = false;
					return;
				}
			}
			if (isFinger == 2)
			{
				isTouchButton = true;
				isFinger = 0;
				finger->setVisible(false);
				setBackGroundWithOutGreyLayer(false);
				setCheckStep(checkStep+1);

				removeChild(spotLightLayer, true);
				//removeChild(greyLayer1, true);
				//removeChild(greyLayer2,true);
			}
			else
			{
				return;
			}
		}
	}

	GameControl::onMenuItemSkillClicked(pSender);
}

void GuideLayer::onMenuItemPauseClicked(cocos2d::CCObject * pSender)
{
	if (isGameOver)
	{
		return;
	}
	if (isBackGroud)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->pauseLoopEffect();
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	setBackGround(true);
	isUpdateProp = true;	
	Player::getInstance()->setGameLayerIsPause(true);
	Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getPauseMenu(this));

	//if (isBackGroud)
	//{
	//	return;
	//}
	//Player::getInstance()->getMusicControl()->pauseLoopEffect();
	//Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	//setBackGround(true);
	//isUpdateProp = true;		
	//int _tmp = 0;
	//for(int i = PROP_TYPE_COIN; i < PROP_TYPE_COUNT; i++)
	//{
	//	_tmp = Player::getInstance()->getPropNum(i);
	//	Player::getInstance()->appendPropNum(i, playerPropNum[i] - _tmp);
	//	playerPropNum[i] = _tmp;
	//}
	////tmpProp1Num = Player::getInstance()->getPropNum(PROP_TYPE_GRENADE);
	////tmpProp2Num = Player::getInstance()->getPropNum(PROP_TYPE_VIGOROUSLY_PILL);
	////tmpProp3Num = Player::getInstance()->getPropNum(PROP_TYPE_MOONLIGHT);
	//Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getPauseMenu(this));
}

void GuideLayer::doAction(float _f)
{
#ifdef										GOLDEN_MINER_2_VERSION_TIME
	float _timeTimes = _f * SCHEDULE_TIMES;
	if (_timeTimes > 2)
	{
		_timeTimes = 2;
	}
	Global::getInstance()->setTimeRatio(_timeTimes);
#endif

	if (isBackGroud)
	{
		if (isFinger != 0)
		{
			finger->doAction(_f);
			doLiuGuang(_f);
		}
		return;
	}

	// 提示
	if (tipId != 0 && Player::getInstance()->getTip(tipId))
	{
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMING);
		setBackGround(true);
		//setBackGroundWithOutGreyLayer(true);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->doGamingTip(tipId);
		Player::getInstance()->setTip(tipId, false);
		tipId = 0;
		return;
	}

#ifdef								GOLDEN_MINER_2_NEW_GUIDE
	if (isStepGetAward && (role->getHanger()->getStatus() == HANGER_STATUS_SWAYING))
	{
		if (!Player::getInstance()->getIsGetAwardByGuideId(guideId))
		{
			// 没有获得奖励才奖励   否则直接进入下一次的引导  或者回到主页面
			// 奖励信息 	
			PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMING);
			setBackGround(true);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->doGuideAward(guideId);
			Player::getInstance()->setIsGetAwardByGuideId(guideId,true);
			isCheck = false;
			getAward();
		}
		isStepGetAward = false;
		setCheckStep(checkStep+1);
		return;
	}
#endif

	if (!isIntroduce)
	{	
		if (guideId != GUIDE_ID_ROLE_SKILL && guideId != GUIDE_ID_JEWEIL_SKILL)
		{
			GameAppend * promptLayer = (GameAppend *)Global::getInstance()->s->getGameAppendLayer(this);
			setBackGroundWithOutGreyLayer(true);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->doGuideInformation(guideId, 1);
		}
	}

	if (isIntroduce && !isStartCountDownEffect)
	{	// 播放开始倒计时
		isStartCountDownEffect = true;
	}

	if(jewelSkillId == SKILL_ID_JEWEL_DROP)
	{
		jewelSkillSprite->updateSkill(_f, this);
		//if (biaozhunxian != NULL)
		//{
		//	biaozhunxian->setVisible(false);
		//}
		return;
	}

	char _s[64];

	if (myIntersectCheck())
	{
		return;
	}

	role->doAction(_f, this);
	//// 瞄准线
	//if ((biaozhunxian != NULL))
	//{
	//	// 需要多转换一下角度
	//	if (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING && role->getHanger()->isVisible())
	//	{
	//		biaozhunxian->setVisible(true);
	//		biaozhunxian->setRotation(angleCenter - Global::getInstance()->getHangerAngle());
	//		changeMiaoZhunXianPosition();
	//	}
	//	else
	//	{
	//		biaozhunxian->setVisible(false);
	//	}
	//}
	gate->doAction(_f, this);


	if (!isIntroduce)
	{	
		if (guideId == GUIDE_ID_ROLE_SKILL)
		{
			if (targetTotalNum == (gate->getTargetTotalNum() + 1))
			{
				GameAppend * promptLayer = (GameAppend *)Global::getInstance()->s->getGameAppendLayer(this);
				setBackGroundWithOutGreyLayer(true);
				Global::getInstance()->s->addLayerToRunningScene(promptLayer);
				promptLayer->doGuideInformation(guideId, 1);
				return;
			}
		}
	}
	//// 针对抓钩引导的奖励提示
	//if (guideId == GUIDE_ID_GRAP)
	//{
	//	if (Global::getInstance()->getPropAwardNumById(PROP_TYPE_COIN) > 0)
	//	{
	//		if (!Player::getInstance()->getIsGetAwardByGuideId(guideId))
	//		{
	//			// 没有获得奖励才奖励   否则直接进入下一次的引导  或者回到主页面
	//			// 奖励信息 
	//			PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this);
	//			setBackGroundWithOutGreyLayer(true);
	//			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
	//			promptLayer->doGuideAward(guideId);
	//			Player::getInstance()->setIsGetAwardByGuideId(guideId,true);
	//			isCheck = false;

	//			return;
	//		}
	//	}
	//}
	//else
	if (guideId == GUIDE_ID_PILL)
	{
		if (!isTouchButton && (Global::getInstance()->getHangerStatus() == HANGER_STATUS_PULL_HAVING))
		{
			// 暂停说明了
			GameAppend * promptLayer = (GameAppend *)Global::getInstance()->s->getGameAppendLayer(this);
			setBackGroundWithOutGreyLayer(true);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->doGuideInformation(guideId, 2);
			isTouchIntroduce = true;
			checkIsTouchIntroduce = true;
			getChildByTag(6)->setVisible(true);
			getChildByTag(999)->getChildByTag(6)->setVisible(true);
			getChildByTag(PROP_PILL_TAG)->setVisible(true);
			getChildByTag(6)->getChildByTag(PROP_NUM_TAG)->setVisible(true);

			CCSprite * senticl = CCSprite::create("yindao/yuan.png");//youxi/baoshitantan.png");
			senticl->setScale(0.25);
			senticl->setPosition(ccp(65, 190));
			spotLightLayer = new SpotLightLayer(senticl, NULL, NULL);
			spotLightLayer->setActionFinishCallBackFunc(CCCallFunc::create(this, NULL));
			addChild(spotLightLayer, LAYER_ORDER_CONTROL*2);
			spotLightLayer->startAction();

			isFinger = 2;
			isStepGetAward = true;
			isCheck = false;
			finger->setPosition(ccp(58, 191));
			finger->setVisible(true);
		}
	}
	else if (guideId == GUIDE_ID_GRENADE)
	{
		if (!isTouchButton && (Global::getInstance()->getHangerStatus() == HANGER_STATUS_PULL_HAVING))
		{
			// 暂停说明了
			GameAppend * promptLayer = (GameAppend *)Global::getInstance()->s->getGameAppendLayer(this);
			setBackGroundWithOutGreyLayer(true);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->doGuideInformation(guideId, 2);
			isTouchIntroduce = true;
			checkIsTouchIntroduce = true;
			getChildByTag(5)->setVisible(true);
			getChildByTag(999)->getChildByTag(5)->setVisible(true);
			getChildByTag(PROP_GRENADE_TAG)->setVisible(true);
			getChildByTag(5)->getChildByTag(PROP_NUM_TAG)->setVisible(true);

			CCSprite * senticl = CCSprite::create("yindao/yuan.png");//youxi/baoshitantan.png");
			senticl->setScale(0.25);
			senticl->setPosition(ccp(65, 280));
			spotLightLayer = new SpotLightLayer(senticl, NULL, NULL);
			spotLightLayer->setActionFinishCallBackFunc(CCCallFunc::create(this, NULL));
			addChild(spotLightLayer, LAYER_ORDER_CONTROL*2);
			spotLightLayer->startAction();

			isFinger = 2;
			isStepGetAward = true;
			isCheck = false;
			finger->setPosition(ccp(58, 281));
			finger->setVisible(true);
		}
	}
	else if (guideId == GUIDE_ID_MOONLIGHT)
	{
		if (!isTouchButton && (Global::getInstance()->getHangerStatus() == HANGER_STATUS_PULL_HAVING))
		{
			// 暂停说明了
			GameAppend * promptLayer = (GameAppend *)Global::getInstance()->s->getGameAppendLayer(this);
			setBackGroundWithOutGreyLayer(true);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->doGuideInformation(guideId, 2);
			isTouchIntroduce = true;
			checkIsTouchIntroduce = true;
			getChildByTag(7)->setVisible(true);
			getChildByTag(999)->getChildByTag(7)->setVisible(true);
			getChildByTag(PROP_MOONLIGHT_TAG)->setVisible(true);
			getChildByTag(7)->getChildByTag(PROP_NUM_TAG)->setVisible(true);

			leaveTime = 3;
			((Sensitization *)liuGuang->objectAtIndex(SKILL_ID_MOONLIGHT-1))->setVisible(true);
#ifdef								GOLDEN_MINER_2_VERSION_TIME
			timeCount = -10000.0;
#endif
			setLeaveTime(leaveTime);

			CCSprite * senticl = CCSprite::create("yindao/yuan.png");//youxi/baoshitantan.png");
			senticl->setScale(0.25);
			senticl->setPosition(ccp(65, 95));
			spotLightLayer = new SpotLightLayer(senticl, NULL, NULL);
			spotLightLayer->setActionFinishCallBackFunc(CCCallFunc::create(this, NULL));
			addChild(spotLightLayer, LAYER_ORDER_CONTROL*2);
			spotLightLayer->startAction();

			isFinger = 2;
			isStepGetAward = true;
			isCheck = false;
			finger->setPosition(ccp(58, 96));
			finger->setVisible(true);
		}
	}

	checkContinueCount(_f);

	scoreAppend(_f);
	//if (getCoinTmp != Global::getInstance()->getPropAwardNumById(PROP_TYPE_COIN))
	//{
	//	if (getCoinTmp == -1)
	//	{
	//		getCoinTmp = Global::getInstance()->getPropAwardNumById(PROP_TYPE_COIN);
	//		setGetCoinLabel();
	//		return;
	//	}
	//	if (isFinger == 0)
	//	{
	//		if (flyTimeScore < ADD_NEW_SCORE_FLY_TIME_LONG)
	//		{
	//			flyTimeScore += _f;
	//			addScoreSystem->setPosition(ccp(Global::getInstance()->getHangerCurrX() + flyTimeScore/ADD_NEW_SCORE_FLY_TIME_LONG*(getCoinLabel->getPositionX() - Global::getInstance()->getHangerCurrX()), Global::getInstance()->getHangerCurrY() + flyTimeScore/ADD_NEW_SCORE_FLY_TIME_LONG*(getCoinLabel->getPositionY() - Global::getInstance()->getHangerCurrY())));
	//		}
	//		else
	//		{
	//			if (addScoreSystem == NULL)
	//			{
	//				addScore(Global::getInstance()->getPropAwardNumById(PROP_TYPE_COIN) - getCoinTmp);
	//			}
	//			else
	//			{
	//				removeChild(addScoreSystem, true);
	//				removeChild(addScoreSprite, true);
	//				removeChild(addScoreNum, true);
	//				addScoreSystem = NULL;
	//				getCoinTmp = Global::getInstance()->getPropAwardNumById(PROP_TYPE_COIN);
	//				setGetCoinLabel();
	//			}
	//		}
	//		//getCoinTmp = Global::getInstance()->getPropAwardNumById(PROP_TYPE_COIN);
	//		//setGetCoinLabel();
	//	}
	//}
	// 爆炸相关的播放
	doExplode(_f);
	doLiuGuang(_f);

	if (isJewel)
	{
		if(jewelSkillId != -1)
		{
			jewelSkillSprite->updateSkill(_f, this);
			//if (biaozhunxian != NULL)
			//{
			//	biaozhunxian->setVisible(false);
			//}
		}
		else
		{
			if(jewelAppendEffects->count() == 0)
			{
				//isDoJewelSkill = true;
				if (!isDoJewelSkill)
				{
					doJewelSkill();
					//if (biaozhunxian != NULL)
					//{
					//	biaozhunxian->setVisible(false);
					//}
				}
			}
			else if (!isDoJewelSkill)
			{
				updateJewelSkill(_f);
			}
		}
	}
	else
	{
		checkJewelSkill(_f);
	}

#ifdef												GOLDEN_MINER_2_VERSION_TIME
	if (isGameOver)
	{// 计时
		if (timeCount >= 1.5)
		{
			gameOver();
			return;
		}
		else
		{
			timeCount += _f;
		}
	}

	if (!isGameOver && gate->getTargetTotalNum() == 0)
	{
		// 游戏结束
		isGameOver = true;
		timeCount = 0.0;
		//gameOver();
		//return;
	}

	if (!isGameOver && isTiming)
	{// 计时
		timeCount -= _f;
		if ((int)timeCount < leaveTime)
		{
			leaveTime--;
			sprintf(_s, "time: %d",leaveTime);
			setLeaveTime(leaveTime);
			if (leaveTime == 0)
			{
				// 游戏结束
				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_TIME_OUT);
				// 游戏结束
				isGameOver = true;
				timeCount = 0.0;
				lastTimeCountDownEffect->setVisible(false);
				//gameOver();
			}
			else if (leaveTime < 6)
			{
				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_TIME_LAST);
				((Sensitization *)liuGuang->objectAtIndex(SKILL_ID_MOONLIGHT-1))->setVisible(true);
				lastTimeCountDownEffect->setVisible(true);
			}
			else
			{
				lastTimeCountDownEffect->setVisible(false);
			}
		}
	}

	if (isStrongStatus)
	{
		strongStatusTimeCount += _f;
		if (strongStatusTimeCount >= VIGOROUSLY_PILL_TIME)
		{
			releaseSkills(SKILL_ID_VIGOROUSLY_PILL);	
		}
	}
	if (isMoonLightStatus)
	{
		moonLightStatusTimeCount += _f;
		if (moonLightStatusTimeCount >= VIGOROUSLY_PILL_TIME)
		{
			releaseSkills(SKILL_ID_MOONLIGHT);	
		}
	}
#else
	if (isGameOver)
	{// 计时
		if (timeCount == 0)
		{
			gameOver();
			return;
		}
		else
		{
			timeCount--;
		}
	}

	if (!isGameOver && gate->getTargetTotalNum() == 0)
	{
		// 游戏结束
		isGameOver = true;
		timeCount = SCHEDULE_TIMES*1.5;
		//gameOver();
		//return;
	}

	if (!isGameOver && isTiming)
	{// 计时
		timeCount--;
		if (timeCount == 0)
		{
			timeCount = SCHEDULE_TIMES;
			leaveTime--;
			sprintf(_s, "time: %d",leaveTime);
			setLeaveTime(leaveTime);
			if (leaveTime == 0)
			{
				// 游戏结束
				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_TIME_OUT);
				// 游戏结束
				isGameOver = true;
				timeCount = SCHEDULE_TIMES*1.5;
				lastTimeCountDownEffect->setVisible(false);
				//gameOver();
			}
			else if (leaveTime < 6)
			{
				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_TIME_LAST);
				((Sensitization *)liuGuang->objectAtIndex(SKILL_ID_MOONLIGHT-1))->setVisible(true);
				lastTimeCountDownEffect->setVisible(true);
			}
			else
			{
				lastTimeCountDownEffect->setVisible(false);
			}
		}
	}

	if (isStrongStatus)
	{
		strongStatusTimeCount++;
		if (strongStatusTimeCount == VIGOROUSLY_PILL_TIME * SCHEDULE_TIMES)
		{
			releaseSkills(SKILL_ID_VIGOROUSLY_PILL);	
		}
	}
	if (isMoonLightStatus)
	{
		moonLightStatusTimeCount++;
		if (moonLightStatusTimeCount == VIGOROUSLY_PILL_TIME * SCHEDULE_TIMES)
		{
			releaseSkills(SKILL_ID_MOONLIGHT);	
		}
	}
#endif

	if (explosive != NULL)
	{
		if (explosive->doAction(_f))
		{
			releaseSkills(SKILL_ID_GRENADE);
		}
	}
	//if (isZhaDanStatus)
	//{
	//	zhaDanStatusTimeCount++;
	//	double _positionX = 0;
	//	double _positionY = 0;
	//	if(carryTargetType == GAMECONTROL_TYPE_TARGET_STATIC)
	//	{
	//		_positionX = ((Target *)carryTargetPoint)->getPositionX() + (Global::getInstance()->getcentreX() - ((Target *)carryTargetPoint)->getPositionX()) * (GRENADE_TIME - zhaDanStatusTimeCount) / GRENADE_TIME;
	//		_positionY = ((Target *)carryTargetPoint)->getPositionY() + (Global::getInstance()->getcentreY() - ((Target *)carryTargetPoint)->getPositionY()) * (GRENADE_TIME - zhaDanStatusTimeCount) / GRENADE_TIME;
	//		zhaDanSprite->setPosition(ccp(_positionX, _positionY));
	//	}
	//	else if (carryTargetType == GAMECONTROL_TYPE_TARGET_DYNAMIC)
	//	{
	//		if (((DynamicTarget *)carryTargetPoint)->getId() == DYNAMIC_ID_SHELL)
	//		{
	//			_positionX = ((DynamicTargetShell *)carryTargetPoint)->shellSprite->getPositionX() + (Global::getInstance()->getcentreX() - ((DynamicTarget *)carryTargetPoint)->getArmature()->getPositionX()) * (GRENADE_TIME - zhaDanStatusTimeCount) / GRENADE_TIME;
	//			_positionY = ((DynamicTargetShell *)carryTargetPoint)->shellSprite->getPositionY() + (Global::getInstance()->getcentreY() - ((DynamicTarget *)carryTargetPoint)->getArmature()->getPositionY()) * (GRENADE_TIME - zhaDanStatusTimeCount) / GRENADE_TIME;
	//		}
	//		else
	//		{
	//			_positionX = ((DynamicTarget *)carryTargetPoint)->getArmature()->getPositionX() + (Global::getInstance()->getcentreX() - ((DynamicTarget *)carryTargetPoint)->getArmature()->getPositionX()) * (GRENADE_TIME - zhaDanStatusTimeCount) / GRENADE_TIME;
	//			_positionY = ((DynamicTarget *)carryTargetPoint)->getArmature()->getPositionY() + (Global::getInstance()->getcentreY() - ((DynamicTarget *)carryTargetPoint)->getArmature()->getPositionY()) * (GRENADE_TIME - zhaDanStatusTimeCount) / GRENADE_TIME;
	//		}
	//		zhaDanSprite->setPosition(ccp(_positionX, _positionY));
	//	}
	//	if (zhaDanStatusTimeCount == GRENADE_TIME)
	//	{
	//		releaseSkills(SKILL_ID_GRENADE);	
	//	}
	//}
}

void GuideLayer::ccTouchesEnded(CCSet* touches, CCEvent* pevent)
{
	if (isGameOver)
	{
		return;
	}
	if (!isStartCountDownEffect)
	{
		return;
	}
#ifdef								GOLDEN_MINER_2_NEW_GUIDE
	if (guideId == GUIDE_ID_JEWEIL_SKILL)
	{
		if ((checkStep < 3) && (isFinger == 0))
		{
			return;
		}
	}
	else if (guideId == GUIDE_ID_ROLE_SKILL)
	{
		if ((checkStep < 2) && (isFinger == 0))
		{
			return;
		}
	}
	else if (isFinger == 0)
	{
		return;
	}
#endif

	if (isBackGroud)
	{
		if (isTouchIntroduce)
		{
			return;
		}
		else
		{
			if (checkIsTouchIntroduce)
			{
				checkIsTouchIntroduce = false;
				return;
			}
		}
		if (isFinger == 1)
		{
			if (guideId != GUIDE_ID_ROLE_SKILL)
			{
				isCheck = false;
			}

			if (guideId == GUIDE_ID_GRAP)
			{
				isStepGetAward = true;
			}

			isFinger = 0;
			finger->setVisible(false);
			setBackGroundWithOutGreyLayer(false);
			if(Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING)
			{
				role->getHanger()->setStatus(HANGER_STATUS_THROW);
			}
		}
		else if (isFinger == 3)
		{
			isCheck = false;
			isFinger = 0;
			finger->setVisible(false);
			setBackGroundWithOutGreyLayer(false);
			if(jewelSkillId != -1)
			{
				jewelSkillSprite->doSkill(this);
				isDoJewelSkill = false;
			}
		}
		return;
	}
	
	if (isJewel)
	{
		if (isDoJewelSkill && jewelSkillSprite->getStatus() == JEWEL_SKILL_SPRITE_STATUS_NORMAL)
		{
			jewelSkillSprite->doSkill(this);
			isDoJewelSkill = false;
		}
	}
	else
	{
		role->throwHanger(this);
	}
	//if(Global::getInstance()->getHangerCanThrow() && (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING))
	//{
	//	role->getHanger()->setStatus(HANGER_STATUS_THROW);
	//}

}

void GuideLayer::setBackGround(bool _isBackGround)
{
	if (_isBackGround == true)
	{
		Global::getInstance()->s->addLayerToRunningScene(greyLayer);
	}
	else
	{
		isPause = false;
		Global::getInstance()->s->removeLayerToRunningScene(greyLayer);
	}


	if (isUpdateProp)
	{
		isUpdateProp = false;
		getChildByTag(5)->removeChildByTag(PROP_NUM_TAG);
		getChildByTag(5)->addChild(getPropNumLable(PROP_TYPE_GRENADE),1, PROP_NUM_TAG);		
		getChildByTag(6)->removeChildByTag(PROP_NUM_TAG);
		getChildByTag(6)->addChild(getPropNumLable(PROP_TYPE_VIGOROUSLY_PILL),1,  PROP_NUM_TAG);	
		getChildByTag(7)->removeChildByTag(PROP_NUM_TAG);
		getChildByTag(7)->addChild(getPropNumLable(PROP_TYPE_MOONLIGHT),1,  PROP_NUM_TAG);
	}

	//if (isUpdateProp)
	//{
	//	isUpdateProp = false;

	//	int _tmp;
	//	for(int i = PROP_TYPE_COIN; i < PROP_TYPE_COUNT; i++)
	//	{
	//		_tmp = Player::getInstance()->getPropNum(i);
	//		Player::getInstance()->appendPropNum(i, playerPropNum[i] - _tmp);
	//		playerPropNum[i] = _tmp;
	//	}
	//}

	setLiZiTeXiaoVisible(!_isBackGround);
	isBackGroud = _isBackGround;
}

void GuideLayer::gameOver(void)
{
	Player::getInstance()->setGameLayer(NULL);
	Player::getInstance()->setGameLayerIsPause(true);
	// 添加已完成引导的页面
	if (isJiangLiTip)
	{
		Player::getInstance()->initPropNumFromDateStore();
		// 没有获得奖励才奖励   否则直接进入下一次的引导  或者回到主页面
		// 奖励信息 	
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMING);
		setBackGround(true);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->doGuideWin();
		isJiangLiTip = false;
		return;
	}

	if (!Player::getInstance()->getIsGetAwardByGuideId(guideId))
	{
		// 没有获得奖励才奖励   否则直接进入下一次的引导  或者回到主页面
		// 奖励信息 	
		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMING);
		setBackGround(true);
		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
		promptLayer->doGuideAward(guideId);
		Player::getInstance()->setIsGetAwardByGuideId(guideId,true);
		isCheck = false;
		getAward();
		return;
	}
		
	myGameOver();
}

void GuideLayer::myGameOver(void)
{
	Player::getInstance()->getMusicControl()->stopLoopEffect();
	guideId = Global::getInstance()->getCurrGuideId() + 1;
	if (guideId > GUIDE_ID_JEWEIL_SKILL)
	{
		//购买的正版（回到主页面）
		Player::getInstance()->setGuideIsFrist(false);

		LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
		CCLayer * p1 = Global::getInstance()->s->getBigGateMenu(p);

		p->addLoadingLayer(0,p1);
		p->setNextLayer(LAYER_ID_BIG_GATE_MAP, p1);

		Global::getInstance()->s->replaceScene(p);

		//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getBigGateMenu());
		//没有购买 提示购买  （购买后 进入第一关   否则也回到主页面）
		return;
	}

	//// 有loading的页面
	//LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
	//CCLayer * p1 = Global::getInstance()->s->getGuideLayer(guideId, p);
	//((GameControl *)p1)->setLoadingLayer(p);
	////p->appendLoadingLayerNum(1);
	//p->addLoadingLayer(0,p1);
	//p->setNextLayer(LAYER_ID_GAMING, p1);

	//Global::getInstance()->s->replaceScene(p);

	// 没有loading的页面
	Global::getInstance()->s->replaceScene(Global::getInstance()->s->getGuideLayer(guideId, NULL));

	//Global::getInstance()->s->addLayerToRunningScene(p1);
	//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getGuideLayer(guideId));
}


#define						GUIDE_CHECK_CONTROL						10

bool GuideLayer::myIntersectCheck(void)
{
	switch (guideId)
	{
	case GUIDE_ID_PILL:
#ifdef							GOLDEN_MINER_2_NEW_GUIDE
		// 抓中大金矿
		if ((stepTargets->count() != 0) && isCheck && isIntroduce && (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING) && Global::getInstance()->intersectCCRectWithSector(
			((Target *)stepTargets->lastObject())->getPosition().x - GUIDE_CHECK_CONTROL,
			((Target *)stepTargets->lastObject())->getPosition().y - GUIDE_CHECK_CONTROL,
			((Target *)stepTargets->lastObject())->getPosition().x + GUIDE_CHECK_CONTROL,
			((Target *)stepTargets->lastObject())->getPosition().y + GUIDE_CHECK_CONTROL,
			role->getHanger()->getCurrX(),
			role->getHanger()->getCurrY(),
			role->getHanger()->getAngle()-0.5,
			role->getHanger()->getAngle() + 0.5))
		{
			isFinger = 1;
			setBackGroundWithOutGreyLayer(true);
			finger->setPosition(ccp(500, 230));
			finger->setVisible(true);

			stepTargets->removeLastObject();

			return true;
		}
#else
		// 抓中大金矿
		if (isCheck && isIntroduce && (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING) && Global::getInstance()->intersectCCRectWithSector(
			((Target *)gate->getTargets()->objectAtIndex(0))->getPosition().x - 1,
			((Target *)gate->getTargets()->objectAtIndex(0))->getPosition().y - 1,
			((Target *)gate->getTargets()->objectAtIndex(0))->getPosition().x + 1,
			((Target *)gate->getTargets()->objectAtIndex(0))->getPosition().y + 1,
			role->getHanger()->getCurrX(),
			role->getHanger()->getCurrY(),
			role->getHanger()->getAngle()-0.5,
			role->getHanger()->getAngle() + 0.5))
			//Global::getInstance()->getHangerStartX(),
			//Global::getInstance()->getHangerStartY(),
			//Global::getInstance()->getHangerAngle()-0.5,
			//Global::getInstance()->getHangerAngle() + 0.5))
		{
			isFinger = 1;
			setBackGroundWithOutGreyLayer(true);
			finger->setPosition(ccp(500, 230));
			finger->setVisible(true);

			return true;
		}
#endif
		break;
	case GUIDE_ID_GRENADE:
		if (!isIntroduce)
		{
			break;
		}

#ifdef							GOLDEN_MINER_2_NEW_GUIDE
		if (isCheck)
		{
			// 检测石头
			if ((stepTargets->count() != 0) && (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING) && Global::getInstance()->intersectCCRectWithSector(
				((Target *)stepTargets->lastObject())->getPosition().x - GUIDE_CHECK_CONTROL,
				((Target *)stepTargets->lastObject())->getPosition().y - GUIDE_CHECK_CONTROL,
				((Target *)stepTargets->lastObject())->getPosition().x + GUIDE_CHECK_CONTROL,
				((Target *)stepTargets->lastObject())->getPosition().y + GUIDE_CHECK_CONTROL,
				role->getHanger()->getCurrX(),
				role->getHanger()->getCurrY(),
				role->getHanger()->getAngle()-0.5,
				role->getHanger()->getAngle() + 0.5))
			{
				// 暂停说明了
				isFinger = 1;
				setBackGroundWithOutGreyLayer(true);
				finger->setPosition(ccp(500, 230));
				finger->setVisible(true);

				stepTargets->removeLastObject();

				return true;
			}
		}
		else
		{
			// 检测砖石
			if ((stepTargets->count() != 0) && (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING) && Global::getInstance()->intersectCCRectWithSector(
				((Target *)stepTargets->lastObject())->getPosition().x - GUIDE_CHECK_CONTROL,
				((Target *)stepTargets->lastObject())->getPosition().y - GUIDE_CHECK_CONTROL,
				((Target *)stepTargets->lastObject())->getPosition().x + GUIDE_CHECK_CONTROL,
				((Target *)stepTargets->lastObject())->getPosition().y + GUIDE_CHECK_CONTROL,
				role->getHanger()->getCurrX(),
				role->getHanger()->getCurrY(),
				role->getHanger()->getAngle()-0.5,
				role->getHanger()->getAngle() + 0.5))
			{
				// 暂停说明了
				isFinger = 1;
				setBackGroundWithOutGreyLayer(true);
				finger->setPosition(ccp(500, 230));
				finger->setVisible(true);

				stepTargets->removeLastObject();

				return true;
			}
		}
#else
		if (isCheck)
		{
			for (int i = 0; i < gate->getTargets()->count(); i++)
			{
				// 检测石头
				if (((Target *)gate->getTargets()->objectAtIndex(i))->getId() == TARGET_ID_STONE_B)
				{
					if ((Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING) && Global::getInstance()->intersectCCRectWithSector(
						((Target *)gate->getTargets()->objectAtIndex(i))->getPosition().x - 1,
						((Target *)gate->getTargets()->objectAtIndex(i))->getPosition().y - 1,
						((Target *)gate->getTargets()->objectAtIndex(i))->getPosition().x + 1,
						((Target *)gate->getTargets()->objectAtIndex(i))->getPosition().y + 1,
						role->getHanger()->getCurrX(),
						role->getHanger()->getCurrY(),
						role->getHanger()->getAngle()-0.5,
						role->getHanger()->getAngle() + 0.5))
						//Global::getInstance()->getHangerStartX(),
						//Global::getInstance()->getHangerStartY(),
						//Global::getInstance()->getHangerAngle()-0.5,
						//Global::getInstance()->getHangerAngle() + 0.5))
					{
						// 暂停说明了
						isFinger = 1;
						setBackGroundWithOutGreyLayer(true);
						finger->setPosition(ccp(500, 230));
						finger->setVisible(true);

						return true;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < gate->getTargets()->count(); i++)
			{
				// 检测砖石
				if (((Target *)gate->getTargets()->objectAtIndex(i))->getId() == TARGET_ID_DIAMOND)
				{
					if ((Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING) && Global::getInstance()->intersectCCRectWithSector(
						((Target *)gate->getTargets()->objectAtIndex(i))->getPosition().x - 1,
						((Target *)gate->getTargets()->objectAtIndex(i))->getPosition().y - 1,
						((Target *)gate->getTargets()->objectAtIndex(i))->getPosition().x + 1,
						((Target *)gate->getTargets()->objectAtIndex(i))->getPosition().y + 1,
						role->getHanger()->getCurrX(),
						role->getHanger()->getCurrY(),
						role->getHanger()->getAngle()-0.5,
						role->getHanger()->getAngle() + 0.5))
						//Global::getInstance()->getHangerStartX(),
						//Global::getInstance()->getHangerStartY(),
						//Global::getInstance()->getHangerAngle()-0.5,
						//Global::getInstance()->getHangerAngle() + 0.5))
					{
						// 暂停说明了
						isFinger = 1;
						setBackGroundWithOutGreyLayer(true);
						finger->setPosition(ccp(500, 230));
						finger->setVisible(true);

						return true;
					}
				}
			}
		}
#endif
		break;
	case GUIDE_ID_MOONLIGHT:
#ifdef							GOLDEN_MINER_2_NEW_GUIDE
		//抓的宝箱
		if ((stepTargets->count() != 0) && isCheck && isIntroduce && (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING) && Global::getInstance()->intersectCCRectWithSector(
			((Target *)stepTargets->lastObject())->getPosition().x - GUIDE_CHECK_CONTROL,
			((Target *)stepTargets->lastObject())->getPosition().y - GUIDE_CHECK_CONTROL,
			((Target *)stepTargets->lastObject())->getPosition().x + GUIDE_CHECK_CONTROL,
			((Target *)stepTargets->lastObject())->getPosition().y + GUIDE_CHECK_CONTROL,
			role->getHanger()->getCurrX(),
			role->getHanger()->getCurrY(),
			role->getHanger()->getAngle()-0.5,
			role->getHanger()->getAngle() + 0.5))
			//Global::getInstance()->getHangerStartX(),
			//Global::getInstance()->getHangerStartY(),
			//Global::getInstance()->getHangerAngle()-0.5,
			//Global::getInstance()->getHangerAngle() + 0.5))
		{
			// 暂停说明了
			isFinger = 1;
			setBackGroundWithOutGreyLayer(true);
			finger->setPosition(ccp(500, 230));
			finger->setVisible(true);

			stepTargets->removeLastObject();

			return true;
		}
#else
		//抓的宝箱
		if (isCheck && isIntroduce && (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING) && Global::getInstance()->intersectCCRectWithSector(
			((Target *)gate->getTargets()->objectAtIndex(0))->getPosition().x - 1,
			((Target *)gate->getTargets()->objectAtIndex(0))->getPosition().y - 1,
			((Target *)gate->getTargets()->objectAtIndex(0))->getPosition().x + 1,
			((Target *)gate->getTargets()->objectAtIndex(0))->getPosition().y + 1,
			role->getHanger()->getCurrX(),
			role->getHanger()->getCurrY(),
			role->getHanger()->getAngle()-0.5,
			role->getHanger()->getAngle() + 0.5))
			//Global::getInstance()->getHangerStartX(),
			//Global::getInstance()->getHangerStartY(),
			//Global::getInstance()->getHangerAngle()-0.5,
			//Global::getInstance()->getHangerAngle() + 0.5))
		{
			// 暂停说明了
			isFinger = 1;
			setBackGroundWithOutGreyLayer(true);
			finger->setPosition(ccp(500, 230));
			finger->setVisible(true);

			return true;
		}
#endif
		break;
	case GUIDE_ID_ROLE_SKILL:
#ifdef							GOLDEN_MINER_2_NEW_GUIDE
		//点击技能按钮
		if (isCheck && !isBackGroud && isIntroduce)
		{
			GameAppend * promptLayer = (GameAppend *)Global::getInstance()->s->getGameAppendLayer(this);
			setBackGroundWithOutGreyLayer(true);

			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->doGuideInformation(guideId, 2);
			isTouchIntroduce = true;
			checkIsTouchIntroduce = true;
			role->setSkillVisible(true);
			getChildByTag(999)->getChildByTag(8)->setVisible(true);


			CCSprite * senticl = CCSprite::create("yindao/yuan.png");//youxi/baoshitantan.png");
			senticl->setScale(0.3);
			senticl->setPosition(ccp(730, 100));
			spotLightLayer = new SpotLightLayer(senticl, NULL, NULL);
			spotLightLayer->setActionFinishCallBackFunc(CCCallFunc::create(this, NULL));
			addChild(spotLightLayer, LAYER_ORDER_CONTROL*2);
			spotLightLayer->startAction();
			//greyLayer2->setContentSize(*new CCSize(650, 480));
			//greyLayer2->setPosition(0,0);
			//greyLayer1->setContentSize(*new CCSize(150, 320));
			//greyLayer1->setPosition(650,160);
			//addChild(greyLayer2, LAYER_ORDER_CONTROL*2);
			//addChild(greyLayer1, LAYER_ORDER_CONTROL*2);
			getChildByTag(999)->getChildByTag(8)->setZOrder(LAYER_ORDER_CONTROL * 2);
			// 暂停说明了
			isFinger = 2;
			finger->setPosition(ccp(734,105));
			finger->setVisible(true);
			isCheck = false;
			return true;
		}

		if (!isCheck)
		{
			break;
		}
		// 检测任意物品
		if ((stepTargets->count() != 0) && (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING) && Global::getInstance()->intersectCCRectWithSector(
			((Target *)stepTargets->lastObject())->getPosition().x - GUIDE_CHECK_CONTROL,
			((Target *)stepTargets->lastObject())->getPosition().y - GUIDE_CHECK_CONTROL,
			((Target *)stepTargets->lastObject())->getPosition().x + GUIDE_CHECK_CONTROL,
			((Target *)stepTargets->lastObject())->getPosition().y + GUIDE_CHECK_CONTROL,
			role->getHanger()->getCurrX(),
			role->getHanger()->getCurrY(),
			role->getHanger()->getAngle()-0.5,
			role->getHanger()->getAngle() + 0.5))
		{
			// 暂停说明了
			isFinger = 1;
			setBackGroundWithOutGreyLayer(true);
			finger->setPosition(ccp(500, 230));
			finger->setVisible(true);

			stepTargets->removeLastObject();
			setCheckStep(checkStep+1);

			return true;
		}
		//else
		//{
		//	CCLOG("GuideLayer GUIDE_ID_ROLE_SKILL stepTargets->count() = %d Global::getInstance()->getHangerStatus() = %d", stepTargets->count(),  Global::getInstance()->getHangerStatus());
		//}
#else
		//点击技能按钮
		if (isCheck && !isBackGroud && isIntroduce)
		{
			GameAppend * promptLayer = (GameAppend *)Global::getInstance()->s->getGameAppendLayer(this);
			setBackGroundWithOutGreyLayer(true);

			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->doGuideInformation(guideId, 2);
			isTouchIntroduce = true;
			checkIsTouchIntroduce = true;
			role->setSkillVisible(true);
			getChildByTag(999)->getChildByTag(8)->setVisible(true);

			CCSprite * senticl = CCSprite::create("youxi/baoshitantan.png");
			senticl->setScale(1.1);
			senticl->setPosition(ccp(730, 100));
			spotLightLayer = new SpotLightLayer(senticl, NULL, NULL);
			spotLightLayer->setActionFinishCallBackFunc(CCCallFunc::create(this, NULL));
			addChild(spotLightLayer, LAYER_ORDER_CONTROL*2);
			spotLightLayer->startAction();
			//greyLayer2->setContentSize(*new CCSize(650, 480));
			//greyLayer2->setPosition(0,0);
			//greyLayer1->setContentSize(*new CCSize(150, 320));
			//greyLayer1->setPosition(650,160);
			//addChild(greyLayer2, LAYER_ORDER_CONTROL*2);
			//addChild(greyLayer1, LAYER_ORDER_CONTROL*2);
			getChildByTag(999)->getChildByTag(8)->setZOrder(LAYER_ORDER_CONTROL * 2);
			// 暂停说明了
			isFinger = 2;
			finger->setPosition(ccp(734,105));
			finger->setVisible(true);
			isCheck = false;
			return true;
		}

		if (!isCheck)
		{
			break;
		}
		for (int i = 0; i < gate->getTargets()->count(); i++)
		{
			// 检测任意物品
			if ((role->getHanger()->getAngle() > angleCenter))
			{
				if ((Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING) && Global::getInstance()->intersectCCRectWithSector(
					((Target *)gate->getTargets()->objectAtIndex(i))->getPosition().x - 1,
					((Target *)gate->getTargets()->objectAtIndex(i))->getPosition().y - 1,
					((Target *)gate->getTargets()->objectAtIndex(i))->getPosition().x + 1,
					((Target *)gate->getTargets()->objectAtIndex(i))->getPosition().y + 1,
					role->getHanger()->getCurrX(),
					role->getHanger()->getCurrY(),
					role->getHanger()->getAngle()-0.5,
					role->getHanger()->getAngle() + 0.5))
					//Global::getInstance()->getHangerStartX(),
					//Global::getInstance()->getHangerStartY(),
					//Global::getInstance()->getHangerAngle()-0.5,
					//Global::getInstance()->getHangerAngle() + 0.5))
				{
					// 暂停说明了
					isFinger = 1;
					setBackGroundWithOutGreyLayer(true);
					finger->setPosition(ccp(500, 230));
					finger->setVisible(true);

					return true;
				}
			}
		}
#endif
		break;
	case GUIDE_ID_JEWEIL_SKILL:
		if (jewelSkillId == SKILL_ID_JEWEL_MAGNET)
		{
			if ((stepTargets->count() != 0) && (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING) && Global::getInstance()->intersectCCRectWithSector(
				((Target *)stepTargets->lastObject())->getPosition().x - GUIDE_CHECK_CONTROL,
				((Target *)stepTargets->lastObject())->getPosition().y - GUIDE_CHECK_CONTROL,
				((Target *)stepTargets->lastObject())->getPosition().x + GUIDE_CHECK_CONTROL,
				((Target *)stepTargets->lastObject())->getPosition().y + GUIDE_CHECK_CONTROL,
				role->getHanger()->getCurrX(),
				role->getHanger()->getCurrY(),
				role->getHanger()->getAngle()-0.5,
				role->getHanger()->getAngle() + 0.5))
			{
				// 暂停说明了
				isFinger = 3;
				setBackGroundWithOutGreyLayer(true);
				finger->setPosition(ccp(500, 230));
				finger->setVisible(true);

				stepTargets->removeLastObject();
				setCheckStep(checkStep+1);

				return true;
			}
			//else
			//{
			//	CCLOG("GuideLayer GUIDE_ID_JEWEIL_SKILL SKILL_ID_JEWEL_MAGNET stepTargets->count() = %d  Global::getInstance()->getHangerStatus() = %d", stepTargets->count(), Global::getInstance()->getHangerStatus());
			//}
		}

		if (!isCheck)
		{
			break;
		}
		// 检测黄宝石
		if ((stepTargets->count() != 0) && (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING) && Global::getInstance()->intersectCCRectWithSector(
			((Target *)stepTargets->lastObject())->getPosition().x - GUIDE_CHECK_CONTROL,
			((Target *)stepTargets->lastObject())->getPosition().y - GUIDE_CHECK_CONTROL,
			((Target *)stepTargets->lastObject())->getPosition().x + GUIDE_CHECK_CONTROL,
			((Target *)stepTargets->lastObject())->getPosition().y + GUIDE_CHECK_CONTROL,
			role->getHanger()->getCurrX(),
			role->getHanger()->getCurrY(),
			role->getHanger()->getAngle()-0.5,
			role->getHanger()->getAngle() + 0.5))
		{
			for (int i = 0; i <= (PROP_TYPE_JEWEL_PURPLE - PROP_TYPE_JEWEL_BLUE); i++)
			{
				if (guideId == GUIDE_ID_JEWEIL_SKILL)
				{
					if (0 == currPropOwn[i + PROP_TYPE_JEWEL_BLUE])
					{
						((CCSprite *)jewelSprites->objectAtIndex(i))->setVisible(false);
					}
					else
					{
						((CCSprite *)jewelSprites->objectAtIndex(i))->setVisible(true);
					}
				}
			}

#ifdef										GAME_LAYER_JEWEL_IS_BUTTON
			getChildByTag(999)->getChildByTag(9)->setVisible(true);
#else
			getChildByTag(4)->setVisible(true);
#endif
			// 暂停说明了
			GameAppend * promptLayer = (GameAppend *)Global::getInstance()->s->getGameAppendLayer(this);
			setBackGroundWithOutGreyLayer(true);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->doGuideInformation(guideId, 2);
			isTouchIntroduce = true;
			checkIsTouchIntroduce = true;
			getChildByTag(5)->setVisible(true);
			getChildByTag(999)->getChildByTag(5)->setVisible(true);
			getChildByTag(PROP_GRENADE_TAG)->setVisible(true);
			getChildByTag(5)->getChildByTag(PROP_NUM_TAG)->setVisible(true);

			isFinger = 1;
			finger->setPosition(ccp(500, 230));
			finger->setVisible(true);

			stepTargets->removeLastObject();
			setCheckStep(checkStep+1);

			return true;
		}
		//else
		//{
		//	CCLOG("GuideLayer GUIDE_ID_JEWEIL_SKILL stepTargets->count() = %d  Global::getInstance()->getHangerStatus() = %d", stepTargets->count(), Global::getInstance()->getHangerStatus());
		//}
		break;
	default:
#ifdef							GOLDEN_MINER_2_NEW_GUIDE
		// 抓中金矿
		if (gate->getTargets()->count() > 0 && (isFinger == 0) && isCheck && isIntroduce && (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING) &&  Global::getInstance()->intersectCCRectWithSector(
			((Target *)stepTargets->lastObject())->getPosition().x - GUIDE_CHECK_CONTROL,
			((Target *)stepTargets->lastObject())->getPosition().y - GUIDE_CHECK_CONTROL,
			((Target *)stepTargets->lastObject())->getPosition().x + GUIDE_CHECK_CONTROL,
			((Target *)stepTargets->lastObject())->getPosition().y + GUIDE_CHECK_CONTROL,
			role->getHanger()->getCurrX(),
			role->getHanger()->getCurrY(),
			role->getHanger()->getAngle() - 0.5,
			role->getHanger()->getAngle() + 0.5))
		{
			// 暂停说明了
			GameAppend * promptLayer = (GameAppend *)Global::getInstance()->s->getGameAppendLayer(this);
			setBackGroundWithOutGreyLayer(true);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->doGuideInformation(guideId, 2);
			isTouchIntroduce = true;
			checkIsTouchIntroduce = true;

			stepTargets->removeLastObject();

			isFinger = 1;
			finger->setPosition(ccp(500, 230));
			finger->setVisible(true);

			return true;
		}
		//else
		//{
		//	CCLOG("GuideLayer GUIDE_ID_GREP gate->getTargets()->count() = %d  isFinger = %d isIntroduce = %d Global::getInstance()->getHangerStatus() = %d", gate->getTargets()->count(), isFinger, isIntroduce, Global::getInstance()->getHangerStatus());
		//}
#else
		// 抓中金矿
		if (gate->getTargets()->count() > 0 && (isFinger == 0) && isCheck && isIntroduce && (Global::getInstance()->getHangerStatus() == HANGER_STATUS_SWAYING) &&  Global::getInstance()->intersectCCRectWithSector(
			((Target *)gate->getTargets()->objectAtIndex(0))->getPosition().x - 1,
			((Target *)gate->getTargets()->objectAtIndex(0))->getPosition().y - 1,
			((Target *)gate->getTargets()->objectAtIndex(0))->getPosition().x + 1,
			((Target *)gate->getTargets()->objectAtIndex(0))->getPosition().y + 1,
			role->getHanger()->getCurrX(),
			role->getHanger()->getCurrY(),
			role->getHanger()->getAngle()-0.5,
			role->getHanger()->getAngle() + 0.5))
			//Global::getInstance()->getHangerStartX(),
			//Global::getInstance()->getHangerStartY(),
			//Global::getInstance()->getHangerAngle()-0.5,
			//Global::getInstance()->getHangerAngle() + 0.5))
		{
			// 暂停说明了
			GameAppend * promptLayer = (GameAppend *)Global::getInstance()->s->getGameAppendLayer(this);
			setBackGroundWithOutGreyLayer(true);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->doGuideInformation(guideId, 2);
			isTouchIntroduce = true;
			checkIsTouchIntroduce = true;

			isFinger = 1;
			finger->setPosition(ccp(500, 230));
			finger->setVisible(true);

			return true;
		}
#endif
		break;
	}

	GameControl::intersectCheck();
	return false;
}

void GuideLayer::doSkills(int _skillId)
{
	GameControl::doSkills(_skillId);

	//if ((guideId > GUIDE_ID_GRAP) && (guideId < GUIDE_ID_ROLE_SKILL))
	//{
	//	if (!Player::getInstance()->getIsGetAwardByGuideId(guideId))
	//	{
	//		// 没有获得奖励才奖励   否则直接进入下一次的引导  或者回到主页面
	//		// 奖励信息 
	//		PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this);
	//		setBackGroundWithOutGreyLayer(true);
	//		Global::getInstance()->s->addLayerToRunningScene(promptLayer);
	//		promptLayer->doGuideAward(guideId);
	//		Player::getInstance()->setIsGetAwardByGuideId(guideId,true);
	//	}
	//}
}

void GuideLayer::getAward(void)
{	
	// 都要重新  从数据存储获得新的数据（目前是因为引导的时候将缓存数据更改掉了才执行这样的操作的）
	//Player::getInstance()->initPropNumFromDateStore();
	switch (guideId)
	{
	case GUIDE_ID_PILL:
		//Player::getInstance()->initPropNumFromDateStoreByType(PROP_TYPE_VIGOROUSLY_PILL);
		Player::getInstance()->appendPropNum(PROP_TYPE_VIGOROUSLY_PILL, 5);
		Player::getInstance()->savePropNum(PROP_TYPE_VIGOROUSLY_PILL,0);
		getChildByTag(6)->removeChildByTag(PROP_NUM_TAG);
		getChildByTag(6)->addChild(getPropNumLable(PROP_TYPE_VIGOROUSLY_PILL),1,  PROP_NUM_TAG);	
		break;
	case GUIDE_ID_GRENADE:
		//Player::getInstance()->initPropNumFromDateStoreByType(PROP_TYPE_GRENADE);
		Player::getInstance()->appendPropNum(PROP_TYPE_GRENADE, 5);
		Player::getInstance()->savePropNum(PROP_TYPE_GRENADE,0);
		getChildByTag(5)->removeChildByTag(PROP_NUM_TAG);
		getChildByTag(5)->addChild(getPropNumLable(PROP_TYPE_GRENADE),1, PROP_NUM_TAG);		
		break;
	case GUIDE_ID_MOONLIGHT:
		//Player::getInstance()->initPropNumFromDateStoreByType(PROP_TYPE_MOONLIGHT);
		Player::getInstance()->appendPropNum(PROP_TYPE_MOONLIGHT, 5);
		Player::getInstance()->savePropNum(PROP_TYPE_MOONLIGHT,0);
		getChildByTag(7)->removeChildByTag(PROP_NUM_TAG);
		getChildByTag(7)->addChild(getPropNumLable(PROP_TYPE_VIGOROUSLY_PILL),1,  PROP_NUM_TAG);	
		break;
	case GUIDE_ID_ROLE_SKILL:
		//Player::getInstance()->initPropNumFromDateStoreByType(PROP_TYPE_INGOT);
		Player::getInstance()->appendPropNum(PROP_TYPE_INGOT, 100);
		Player::getInstance()->savePropNum(PROP_TYPE_INGOT,0);
		break;
	case GUIDE_ID_JEWEIL_SKILL:
		//Player::getInstance()->initPropNumFromDateStoreByType(PROP_TYPE_INGOT);
		Player::getInstance()->appendPropNum(PROP_TYPE_INGOT, 200);
		Player::getInstance()->savePropNum(PROP_TYPE_INGOT,0);
		break;
	default:
		//Player::getInstance()->initPropNumFromDateStoreByType(PROP_TYPE_INGOT);
		Player::getInstance()->appendPropNum(PROP_TYPE_INGOT, 100);
		Player::getInstance()->savePropNum(PROP_TYPE_INGOT,0);
		break;
	}
}
	
void GuideLayer::finishRoleSkillEffect(void)
{
	//if ((guideId == GUIDE_ID_ROLE_SKILL) && !Player::getInstance()->getIsGetAwardByGuideId(guideId))
	//{
	//	// 没有获得奖励才奖励   否则直接进入下一次的引导  或者回到主页面
	//	// 奖励信息 
	//	PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this);
	//	setBackGroundWithOutGreyLayer(true);
	//	Global::getInstance()->s->addLayerToRunningScene(promptLayer);
	//	promptLayer->doGuideAward(guideId);
	//	Player::getInstance()->setIsGetAwardByGuideId(guideId,true);
	//}

	GameControl::finishRoleSkillEffect();
}

void GuideLayer::setCurrMapId(int _currMapId)//(只能初始化一次)
{
	// 关卡显示相关初始化
	//CCSprite * _tmp = CCSprite::create("youxi/yindao.png");
	CCSprite * _tmp = CCSprite::create("youxi/shilian.png");
	_tmp->setPosition(ccp(getChildByTag(3)->getPositionX() - 30, getChildByTag(3)->getPositionY()- 14));
	addChild(_tmp);

	currMapId = _currMapId;
}

void GuideLayer::setCurrSceneId(int _currSceneId)//(只能初始化一次)
{
	currSceneId = _currSceneId;

	char _s[32];
	sprintf(_s, "%d",currSceneId);
	int i = 0;
	while(1)
	{
		currSceneId = currSceneId / 10;
		if (currSceneId > 0)
		{
			i++;
		}
		else
		{
			break;
		}
	}

	CCLabelAtlas * currSceneIdLabel = CCLabelAtlas::create(_s, "youxi/guankashuzi.png", 12, 15, '0');
	currSceneIdLabel->setPosition(ccp(getChildByTag(3)->getPositionX()-i*6, getChildByTag(3)->getPositionY()- 21));
	addChild(currSceneIdLabel);
	currSceneId = _currSceneId;
}

void GuideLayer::doJewelSkill(void)
{
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_SKILL);

	jewelSkillId = SKILL_ID_JEWEL_MAGNET;//SKILL_ID_JEWEL_MAGNET;

	switch(jewelSkillId)
	{
	case SKILL_ID_JEWEL_DROP:
		jewelSkillSprite = new JewelSkillDrop(this);
		break;
	case SKILL_ID_JEWEL_MAGNET:// 吸铁石  30°
		jewelSkillSprite = new JewelSkillMagnet(this, role->getHanger());
		addChild((JewelSkillMagnet *)jewelSkillSprite, LAYER_ORDER_CONTROL-1);
		break;
	case SKILL_ID_JEWEL_BALL:
		jewelSkillSprite = new JewelSkillBall(this, role->getHanger());
		addChild((JewelSkillBall *)jewelSkillSprite, LAYER_ORDER_CONTROL-1);
		break;
	//case SKILL_ID_JEWEL_DIZZY:// 所有怪物变成晕眩状态
	//	jewelSkillSprite = new JewelSkillDizzy(this);
	//	break;
	//case SKILL_ID_JEWEL_GOURD:
	//	jewelSkillSprite = new JewelSkillGourd(this, role->getHanger());
	//	addChild((JewelSkillGourd *)jewelSkillSprite, LAYER_ORDER_CONTROL-1);
	//	break;
	case SKILL_ID_JEWEL_FIVE_HANGER:
		jewelSkillSprite = new JewelSkillFiveHanger(this);
		break;
	default:
		break;
	}

	// 播放完成宝石的处理效果
	GameAppend * gameAppend = (GameAppend *)Global::getInstance()->s->getGameAppendLayer(this);
	setBackGround(true);
	Global::getInstance()->s->addLayerToRunningScene(gameAppend);

	gameAppend->doJewelSkillEffect(jewelSkillId);

}

void GuideLayer::keyBackClicked(void)	
{
	GameControl::onMenuItemPauseClicked(NULL);
}

/**********************************************************************************
无限关卡
**********************************************************************************/
ChallengeLayer::ChallengeLayer(void)
: GameControl(){
	isConnectNet = true;
	isTimeAgain = true;
}

ChallengeLayer::~ChallengeLayer(void)
{
	CCLOG("ChallengeLayer::~ChallengeLayer");
}

void ChallengeLayer::setChallengeLayer(int _gateId, int roleType)
{
	type = GAMEING_CHALLENGE;
	challengeCountSumLabel = NULL;
	GameControl::setGameControl(_gateId, roleType);
	
	isUpdateSum = true;

	tipId = 0;
	isWords = false;

	isGenuine = false;

	//if (biaozhunxian != NULL)
	//{
	//	removeChild(biaozhunxian);
	//	biaozhunxian = NULL;
	//	
	//	Player::getInstance()->appendPropNum(PROP_TYPE_ALIGNMENT ,1);
	//	Player::getInstance()->savePropNum(PROP_TYPE_ALIGNMENT ,1);
	//}
	if (role->getIsHaveAlignment())
	{
		Player::getInstance()->appendPropNum(PROP_TYPE_ALIGNMENT ,1);
		Player::getInstance()->savePropNum(PROP_TYPE_ALIGNMENT ,1);
		role->setIsHaveAlignment(false);
	}
#ifdef								GOLDEN_MINER_2_VERSION_TIME
	timeCount = -10000.0;
#endif
	setLeaveTime(Global::getInstance()->getTimeByChallengeLevel());
}

cocos2d::SEL_MenuHandler ChallengeLayer::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnProp1", ChallengeLayer::onMenuItemProp1Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnProp2", ChallengeLayer::onMenuItemProp2Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnProp3", ChallengeLayer::onMenuItemProp3Clicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnSkill", ChallengeLayer::onMenuItemSkillClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnPause", ChallengeLayer::onMenuItemPauseClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnGem", GameControl::onMenuItemGemClicked);

	return NULL;
}

cocos2d::extension::SEL_CCControlHandler ChallengeLayer::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
	return NULL;
}

bool ChallengeLayer::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}


void ChallengeLayer::keyBackClicked(void)
{
	GameControl::onMenuItemPauseClicked(NULL);
}

void ChallengeLayer::finishRoleSkillEffect(void)
{
	GameControl::finishRoleSkillEffect();
}

void ChallengeLayer::doAction(float _f)
{
	if (isUpdateSum)
	{
		int i = 0;
		int _getCoinTmp = Global::getInstance()->getChallengeCountSum();
		while(1)
		{
			_getCoinTmp = _getCoinTmp / 10;
			if (_getCoinTmp > 0)
			{
				i++;
			}
			else
			{
				break;
			}
		}
		challengeCountSumLabel->setPosition(ccp(getChildByTag(88)->getPositionX() + 56 - i*16, getChildByTag(88)->getPositionY() - 10));
	}

	GameControl::doAction(_f);

	if (isGameOver && (leaveTime == 0) && isTimeAgain && getCoinTmp < leastCoin)
	{
#ifdef										GOLDEN_MINER2_VERSION_PAY_SELF
		// 填出自己计费点窗口
		setBackGroundWithOutGreyLayer(true);
		isTimeAgain = false;
		CostLayer * _layer = (CostLayer *)Global::getInstance()->s->getCostLayer(this, LAYER_ID_GAMING);
		_layer->costById(PAY_ID_TIMEMACHINE, CCCallFunc::create(this, callfunc_selector(ChallengeLayer::payTimeAgainSuccess)), CCCallFunc::create(this, callfunc_selector(ChallengeLayer::payTimeAgainFailed)));
		Global::getInstance()->s->addLayerToRunningScene(_layer);
#else
		// 弹出渠道计费点窗口

#endif
	}
}

void ChallengeLayer::gameOver(void)
{
	if (!isConnectNet)
	{
		return;
	}

	setBackGround(true);
	Player::getInstance()->setGameLayer(NULL);
	Player::getInstance()->setGameLayerIsPause(true);
	Player::getInstance()->getMusicControl()->stopLoopEffect();
	if (isNewGate)
	{
		// 更新玩家的道具信息
		for(int i = PROP_TYPE_FOOD; i < PROP_TYPE_COUNT; i++)
		{// 口粮 和 5中颜色的宝石更新
			Player::getInstance()->appendPropNum(i, Global::getInstance()->getPropAwardNumById(i));
			Player::getInstance()->savePropNum(i,0);
		}
		// 更新玩家的宠物信息
		for(int i = PET_ELEMENT_XIAOZUANFENG; i < PET_ELEMENT_COUNT; i++)
		{
			if (!Player::getInstance()->getPetHaving(i) && !Player::getInstance()->getPetBorn(i))
			{
				Player::getInstance()->appendPetElement(i, Global::getInstance()->getPetElementGetById(i));
				// 检测是否能够开启新的宠物(蛋变成宝宝)
				if (Global::getInstance()->getPetIsOpenByIdAndNum(i, Player::getInstance()->getPetElement(i)))
				{
					// 开启新宠物的动画
					Player::getInstance()->setPetBorn(i, true);   // 还有结算的页面没有做
				}
			}	
		}
		isNewGate = false;
	}

	if (getCoinTmp >= leastCoin)
	{// 通关成功
		////  有loading
		//LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
		//CCLayer * p1 = Global::getInstance()->s->getChallengeLayer(Global::getInstance()->getNextChallengeGateId(), Global::getInstance()->getSelectRoleId(),p);
		//((GameControl *)p1)->setLoadingLayer(p);
		////p->appendLoadingLayerNum(1);
		//p->addLoadingLayer(0,p1);
		//p->setNextLayer(LAYER_ID_GAMING, p1);

		//Global::getInstance()->s->replaceScene(p);
		////Global::getInstance()->s->addLayerToRunningScene(p1);

		// 没有loading页面
		Player::getInstance()->setChallengeMaxLevel(Global::getInstance()->getChallengeLevel());
		Global::getInstance()->setChallengeLevel(Global::getInstance()->getChallengeLevel()+1);
		Global::getInstance()->setChallengeTimeLevel(Global::getInstance()->getChallengeTimeLevel()+1);
		Global::getInstance()->s->replaceScene(Global::getInstance()->s->getChallengeLayer(Global::getInstance()->getNextChallengeGateId(), Global::getInstance()->getSelectRoleId(), NULL));


		//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getChallengeLayer(Global::getInstance()->getNextChallengeGateId(), Global::getInstance()->getSelectRoleId()));
	}
	else
	{// 通关失败
		if (gate->getTargetTotalNum() == 0)
		{// 通关成功
			////  有loading
			//LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
			//CCLayer * p1 = Global::getInstance()->s->getChallengeLayer(Global::getInstance()->getNextChallengeGateId(), Global::getInstance()->getSelectRoleId(),p);
			//((GameControl *)p1)->setLoadingLayer(p);
			////p->appendLoadingLayerNum(1);
			//p->addLoadingLayer(0,p1);
			//p->setNextLayer(LAYER_ID_GAMING, p1);

			//Global::getInstance()->s->replaceScene(p);
			////Global::getInstance()->s->addLayerToRunningScene(p1);
			
			// 没有loading页面
			Player::getInstance()->setChallengeMaxLevel(Global::getInstance()->getChallengeLevel());
			Global::getInstance()->setChallengeLevel(Global::getInstance()->getChallengeLevel()+1);
			Global::getInstance()->setChallengeTimeLevel(Global::getInstance()->getChallengeTimeLevel()+1);
			Global::getInstance()->s->replaceScene(Global::getInstance()->s->getChallengeLayer(Global::getInstance()->getNextChallengeGateId(), Global::getInstance()->getSelectRoleId(), NULL));

			//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getChallengeLayer(Global::getInstance()->getNextChallengeGateId(), Global::getInstance()->getSelectRoleId()));
		}
		else
		{

			// 人物开启状态
			while(isNewRole < ROLE_TYPE_COUNT)
			{
				if (isNewRoleOpenByRoleId(isNewRole))
				{
					// 开始了新的人物要播效果
					PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_GAMING);
					Global::getInstance()->s->addLayerToRunningScene(promptLayer);
					promptLayer->addNewRole();
					// 更新人物开启状态
					Player::getInstance()->setRoleOpenStatusByRoleId(isNewRole, true);
					Player::getInstance()->setOpenNewRole(true);
					isNewRole++;
					isNewGate = false;
					return;
				}
				else
				{
					isNewRole++;
				}
			}

			Global::getInstance()->setChallengeCountSum(Global::getInstance()->getChallengeCountSum() + getChallengeAwardByPropId(PROP_TYPE_COIN));
			// 奖励加进去
			//Player::getInstance()->appendPropNum(PROP_TYPE_INGOT, getChallengeAwardByPropId(PROP_TYPE_INGOT));
			//Player::getInstance()->savePropNum(PROP_TYPE_INGOT, getChallengeAwardByPropId(PROP_TYPE_INGOT));
			//Player::getInstance()->appendPropNum(PROP_TYPE_FOOD, getChallengeAwardByPropId(PROP_TYPE_FOOD));
			//Player::getInstance()->savePropNum(PROP_TYPE_INGOT, getChallengeAwardByPropId(PROP_TYPE_INGOT));
			
#ifdef									GOLDEN_MINER2_VIRSION_CHALLENGE
			if (Player::getInstance()->getChallengeAppendName())
			{
				NetWork::getInstance()->getInstance()->isHavingDate(this, callfuncND_selector(ChallengeLayer::onIsHavingDateCompleted));
			}
			else
			{
				// 更新排行榜数据
				ChallengeRecord newRecord = Player::getInstance()->getChallengeById();
				newRecord.level = Global::getInstance()->getChallengeLevel()-1;
				newRecord.score = Global::getInstance()->getChallengeCountSum();
				newRecord.roleId = Global::getInstance()->getSelectRoleId();
				Player::getInstance()->updateChallenge(newRecord);
				NetWork::getInstance()->updateSelfChallengeDate(Player::getInstance()->getChallengeById(), this, callfuncND_selector(ChallengeLayer::onUpdateChallengeDateCompleted));
			}
#else
			Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getChallengeCountMenu(this));
#endif
			CCLOG("ChallengeLayer   1");

			isConnectNet = false;

			//LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
			//CCLayer * p1 = Global::getInstance()->s->getMainLayer(p);

			//p->addLoadingLayer(0,p1);
			//p->setNextLayer(LAYER_ID_MAIN, p1);

			//Global::getInstance()->s->replaceScene(p);

			////Global::getInstance()->s->replaceScene(Global::getInstance()->s->getMainLayer());
		}
	}
}
// 计费相关添加
void ChallengeLayer::payTimeAgainSuccess(void)
{
	setBackGroundWithOutGreyLayer(false);
	isTimeAgain = true;
	Global::getInstance()->setChallengeTimeLevel(1);

#ifdef								GOLDEN_MINER_2_VERSION_TIME
	timeCount = -10000.0;
#endif
	setLeaveTime(60);

	isGameOver = false;
#ifndef								GOLDEN_MINER_2_VERSION_TIME
	timeCount = 60 * SCHEDULE_TIMES;
#endif
}

// 计费相关添加
void ChallengeLayer::payTimeAgainFailed(void)
{
	setBackGroundWithOutGreyLayer(false);
}

void ChallengeLayer::onUpdateChallengeDateCompleted(cocos2d::CCNode *sender, void *data)
{
	CCHttpResponse *response = (CCHttpResponse*)data;

	if (!response || !response->isSucceed())
	{
		if (response == NULL)
		{
			CCLOG("response is NULL");
		}
		else
		{
			CCLog("response failed");
			CCLog("error buffer: %s", response->getErrorBuffer());
		}

		Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getChallengeCountMenu(this));
		return;
	}

	Player::getInstance()->setChallengeUpdate(false);

	NetWork::getInstance()->getChallengeDate(this, callfuncND_selector(ChallengeLayer::onGetChallengeDateCompleted));
}

void ChallengeLayer::onGetChallengeDateCompleted(cocos2d::CCNode *sender, void *data)
{
	CCHttpResponse *response = (CCHttpResponse*)data;

	if (!response || !response->isSucceed())
	{
		if (response == NULL)
		{
			CCLOG("response is NULL");
		}
		else
		{
			CCLog("response failed   filedcode = %d", response->getResponseCode());
			CCLog("error buffer: %s", response->getErrorBuffer());
		}

		Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getChallengeCountMenu(this));
		return;
	}

	// dump data
	std::vector<char> *buffer = response->getResponseData();
	//把vector转换成std::string
	std::string buf(buffer->begin(),buffer->end()); 
	//buf.c_str()把std::string转换成string;
	GMJson * _json = new GMJson();
	_json->getChallengeDate(buf);
	delete(_json);
	Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getChallengeOverMenu(LAYER_ID_GAMING,this));
}

void ChallengeLayer::onIsHavingDateCompleted(cocos2d::CCNode *sender, void *data)
{
	CCHttpResponse *response = (CCHttpResponse*)data;

	if (!response || !response->isSucceed())
	{
		if (response == NULL)
		{
			CCLOG("response is NULL");
		}
		else
		{
			CCLog("response failed   filedcode = %d", response->getResponseCode());
			CCLog("error buffer: %s", response->getErrorBuffer());
		}

		Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getChallengeCountMenu(this));
		return;
	}
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	//把vector转换成std::string
	std::string buf(buffer->begin(),buffer->end()); 
	//buf.c_str()把std::string转换成string;
	GMJson * _json = new GMJson();
	_json->getSelfInformation(buf);
	delete(_json);
	if (Player::getInstance()->getChallengeAppendName())
	{
		Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getChallengeOverMenu(LAYER_ID_GAMING, this));
	}
	else
	{
		// 更新排行榜数据
		ChallengeRecord newRecord = Player::getInstance()->getChallengeById();
		newRecord.level = Global::getInstance()->getChallengeLevel()-1;
		newRecord.score = Global::getInstance()->getChallengeCountSum();
		newRecord.roleId = Global::getInstance()->getSelectRoleId();
		Player::getInstance()->updateChallenge(newRecord);
		NetWork::getInstance()->updateSelfChallengeDate(Player::getInstance()->getChallengeById(), this, callfuncND_selector(ChallengeLayer::onUpdateChallengeDateCompleted));
	}
}

void ChallengeLayer::doJewelSkill(void)
{
	GameControl::doJewelSkill();
}

void ChallengeLayer::scoreAppend(float _f)
{
	if (getCoinTmp != Global::getInstance()->getPropAwardNumById(PROP_TYPE_COIN))
	{
		setChallengCountSum();
	}

	GameControl::scoreAppend(_f);
}

int ChallengeLayer::getChallengeAwardByPropId(int _id)
{
	int res = 0;
	int times = 1;
	
		switch(Global::getInstance()->getChallengeLevelType())
		{
		case CHALLENGE_TYPE_IRON:
			if(_id == PROP_TYPE_INGOT)
			{
				times = 1;
			}
			else if(_id == PROP_TYPE_FOOD)
			{
				times = 1;
			}
			break;
		case CHALLENGE_TYPE_SILVER:
			if(_id == PROP_TYPE_INGOT)
			{
				times = 5;
			}
			else if(_id == PROP_TYPE_FOOD)
			{
				times = 3;
			}
			break;
		case CHALLENGE_TYPE_GOLD:
			if(_id == PROP_TYPE_INGOT)
			{
				times = 10;
			}
			else if(_id == PROP_TYPE_FOOD)
			{
				times = 5;
			}
			break;
		}

		switch(Global::getInstance()->getChallengeLevel() - 1)
		{
		case 1:
			if(_id == PROP_TYPE_COIN)
			{
				res = 500 * times;
			}
			else if(_id == PROP_TYPE_INGOT)
			{
				res = 10 * times;
			}
			else if(_id == PROP_TYPE_FOOD)
			{
				res = 1 * times;
			}
			break;
		case 2:
			if(_id == PROP_TYPE_COIN)
			{
				res = 1000 * times;
			}
			else if(_id == PROP_TYPE_INGOT)
			{
				res = 20 * times;
			}
			else if(_id == PROP_TYPE_FOOD)
			{
				res = 2 * times;
			}
			break;
		case 3:
			if(_id == PROP_TYPE_COIN)
			{
				res = 2000 * times;
			}
			else if(_id == PROP_TYPE_INGOT)
			{
				res = 40 * times;
			}
			else if(_id == PROP_TYPE_FOOD)
			{
				res = 3 * times;
			}
			break;
		case 4:
			if(_id == PROP_TYPE_COIN)
			{
				res = 5000 * times;
			}
			else if(_id == PROP_TYPE_INGOT)
			{
				res = 70 * times;
			}
			else if(_id == PROP_TYPE_FOOD)
			{
				res = 4 * times;
			}
			break;
		case 5:
			if(_id == PROP_TYPE_COIN)
			{
				res = 10000 * times;
			}
			else if(_id == PROP_TYPE_INGOT)
			{
				res = 100 * times;
			}
			else if(_id == PROP_TYPE_FOOD)
			{
				res = 5 * times;
			}
			break;
		case 6:
			if(_id == PROP_TYPE_COIN)
			{
				res = 15000 * times;
			}
			else if(_id == PROP_TYPE_INGOT)
			{
				res = 140 * times;
			}
			else if(_id == PROP_TYPE_FOOD)
			{
				res = 6 * times;
			}
			break;
		case 7:
			if(_id == PROP_TYPE_COIN)
			{
				res = 20000 * times;
			}
			else if(_id == PROP_TYPE_INGOT)
			{
				res = 180 * times;
			}
			else if(_id == PROP_TYPE_FOOD)
			{
				res = 7 * times;
			}
			break;
		case 8:
			if(_id == PROP_TYPE_COIN)
			{
				res = 27000 * times;
			}
			else if(_id == PROP_TYPE_INGOT)
			{
				res = 220 * times;
			}
			else if(_id == PROP_TYPE_FOOD)
			{
				res = 8 * times;
			}
			break;
		case 9:
			if(_id == PROP_TYPE_COIN)
			{
				res = 35000 * times;
			}
			else if(_id == PROP_TYPE_INGOT)
			{
				res = 270 * times;
			}
			else if(_id == PROP_TYPE_FOOD)
			{
				res = 9 * times;
			}
			break;
		default:
			if(Global::getInstance()->getChallengeLevel() > 9)
			{
				if(_id == PROP_TYPE_COIN)
				{
					res = 50000 * times;
				}
				else if(_id == PROP_TYPE_INGOT)
				{
					res = 320 * times;
				}
				else if(_id == PROP_TYPE_FOOD)
				{
					res = 10 * times;
				}
			}
			break;
		}
	return res;
}

void ChallengeLayer::setCurrMapId(int _currMapId)
{
	// 关卡显示相关初始化
	CCSprite * _tmp = CCSprite::create("youxi/diduosc.png");
	_tmp->setPosition(ccp(getChildByTag(3)->getPositionX() - 14, getChildByTag(3)->getPositionY()- 14));
	addChild(_tmp);

	char _s[32];
	sprintf(_s, "%d",Global::getInstance()->getChallengeLevel());


	CCLabelAtlas * currMapIdLabel = CCLabelAtlas::create(_s, "youxi/guankashuzi.png", 12, 15, '0');
	if (Global::getInstance()->getChallengeLevel() > 9)
	{
		currMapIdLabel->setPosition(ccp(getChildByTag(3)->getPositionX() - 27, getChildByTag(3)->getPositionY()- 22));
	}
	else
	{
		currMapIdLabel->setPosition(ccp(getChildByTag(3)->getPositionX() - 19, getChildByTag(3)->getPositionY()- 22));
	}
	addChild(currMapIdLabel);

	currMapId = _currMapId;

	setChallengCountSum();
}

void ChallengeLayer::setCurrSceneId(int _currSceneId)
{

}

void ChallengeLayer::setBackGround(bool _isBackGround)
{
	GameControl::setBackGround(_isBackGround);
}

void ChallengeLayer::setChallengCountSum(void)// 设置需要最少的铜钱值
{
	if (getCoinTmp != -1)
	{
		Global::getInstance()->setChallengeCountSum(Global::getInstance()->getChallengeCountSum() + Global::getInstance()->getPropAwardNumById(PROP_TYPE_COIN) - getCoinTmp);
		isUpdateSum = false;
	}

	char _s[32];
	sprintf(_s, "%d",Global::getInstance()->getChallengeCountSum());

	if (challengeCountSumLabel != NULL)
	{
		removeChild(challengeCountSumLabel);
		CC_SAFE_RELEASE(challengeCountSumLabel);
	}
	challengeCountSumLabel = CCLabelAtlas::create(_s, "youxi/zongfen.png", 16, 21, '0');
	int i = 0;
	int _getCoinTmp = Global::getInstance()->getChallengeCountSum();
	while(1)
	{
		_getCoinTmp = _getCoinTmp / 10;
		if (_getCoinTmp > 0)
		{
			i++;
		}
		else
		{
			break;
		}
	}
	challengeCountSumLabel->setPosition(ccp(getChildByTag(88)->getPositionX() + 56 - i*16, getChildByTag(88)->getPositionY() - 10));

	addChild(challengeCountSumLabel, LAYER_ORDER_CONTROL);
	CC_SAFE_RETAIN(challengeCountSumLabel);
}