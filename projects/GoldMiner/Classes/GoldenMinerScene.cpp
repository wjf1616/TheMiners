#include "GoldenMinerScene.h"
#include "cocos-ext.h"
#include "SimleGateMenuLoader.h"
#include "PauseMenuLoader.h"
#include "SettingMenuLoader.h"
#include "GameOverMenuLoader.h"
#include "SelectRoleAndPropMenuLoader.h"
#include "GameControlLoader.h"
#include "BigGateMenuLoader.h"
#include "GameAppendLoader.h"
#include "RoleSkillEffectLoader.h"
#include "CountDownEffectLoader.h"
#include "Player.h"
#include "LoadingLayerLoader.h"
#include "RoleInformationLoader.h"
#include "MainLayerLoader.h"
#include "MainAppendLayerLoader.h"
#include "GuideLayerLoader.h"
#include "AboutLayerLoader.h"
#include "HalpLayerLoader.h"
#include "PetParkLayerLoader.h"
#include "CartoonLayerLoader.h"
#include "PromptLayerLoader.h"
#include "ChallengeLayerLoader.h"
#include "ShopLoader.h"
#include "SelectRoleAndPetLoader.h"
#include "SelectPetLoader.h"
#include "ChallengeOverLoader.h"
#include "ChallengeCountLoader.h"
#include "SelectChallengeLoader.h"
#include "RegisterLayerLoader.h"
#include "ExitLayerLoader.h"
#include "DrawLayerLoader.h"
#include "TemporaryPromptLayerLoader.h"
#include "CostLayerLoader.h"
#include "Buddaha.h"
#include "SlipGuide.h"

USING_NS_CC;

GoldenMinerScene::GoldenMinerScene(void)
{
}


GoldenMinerScene::~GoldenMinerScene(void)
{
}

cocos2d::CCScene * GoldenMinerScene::getSence(void)
{
	CCScene * scene = NULL;

	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		//CCLayer * _tmp = getChallengeOverMenu(NULL);

		//Player::getInstance();

		LoadingLayer * _tmp;
		CCLayer * _tmp1;
		_tmp = (LoadingLayer *)getLoadingLayer();

		_tmp1 = getMainLayer(_tmp);
		((MainLayer *)_tmp1)->setIsFrist(true);
		_tmp->setNextLayer(LAYER_ID_MAIN, _tmp1);
		_tmp->addLoadingLayer(0,_tmp1);

		addLayerToScene(_tmp, scene);

	} while (0);

	return scene;
}

void GoldenMinerScene::popScene()
{
	CCDirector::sharedDirector()->getRunningScene()->removeChild((CCNode *)CCDirector::sharedDirector()->getRunningScene()->getChildren()->lastObject());
}

// 代替显示
void GoldenMinerScene::replaceScene(cocos2d::CCLayer * _layer)
{
	CCScene *pScene = CCScene::create();

	if ((_layer != NULL) && (pScene != NULL))
	{
		pScene->addChild(_layer);
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

void GoldenMinerScene::replaceSceneWithTime(float t, cocos2d::CCLayer * _layer)
{
	CCScene *pScene = CCScene::create();

	if ((_layer != NULL) && (pScene != NULL))
	{
		pScene->addChild(_layer);
	}

	CCTransitionFade *pSceneCrossFade = CCTransitionFade::create(t, pScene);
	CCDirector::sharedDirector()->replaceScene(pSceneCrossFade);
}


// 代替显示
void GoldenMinerScene::replaceSceneWithCrossFade(float t,cocos2d::CCLayer * _layer)
{
	CCScene *pScene = CCScene::create();

	if ((_layer != NULL) && (pScene != NULL))
	{
		pScene->addChild(_layer);
	}

	CCTransitionCrossFade *pSceneCrossFade = CCTransitionCrossFade::create(t, pScene);
	CCDirector::sharedDirector()->replaceScene(pSceneCrossFade);
}

void GoldenMinerScene::addLayerToRunningScene(cocos2d::CCLayer * _layer)
{
	addLayerToScene(_layer, CCDirector::sharedDirector()->getRunningScene());
}

void GoldenMinerScene::removeLayerToRunningScene(cocos2d::CCLayer * _layer)
{
	CCDirector::sharedDirector()->getRunningScene()->removeChild(_layer);
}

void GoldenMinerScene::addLayerToScene(cocos2d::CCLayer * _layer, cocos2d::CCScene * _sence)
{
	if ((_layer != NULL) && (_sence != NULL))
	{
		_sence->addChild(_layer);
	}
}

void GoldenMinerScene::removeLayerToRunningSceneAndSetNextLayer(cocos2d::CCLayer * _layer, int _nextType, cocos2d::CCLayer * _nextLayer)
{
	switch(_nextType)
	{
	case LAYER_ID_MAIN:
		((MainLayer *)_nextLayer)->startSelf();
		break;
	case LAYER_ID_GAMING:
		((GameControl *)_nextLayer)->startSelf();
		break;
	case LAYER_ID_CARTOON:
		((CartoonLayer *)_nextLayer)->startSelf();
		break;
	case LAYER_ID_PETPARK:
		((PetParkLayer *)_nextLayer)->startSelf();
		break;
	case LAYER_ID_BIG_GATE_MAP:
		((BigGateMenu *)_nextLayer)->startSelf();
		break;
	case LAYER_ID_SMILE_GATE_SCENCE:
		((SimleGateMenu *)_nextLayer)->startSelf();
		break;
	case LAYER_ID_PROP_ROLE:
		((SelectRoleAndPropMenu *)_nextLayer)->startSelf();
		break;
	case LAYER_ID_SHOP:
		((Shop *)_nextLayer)->startSelf();
		break;
	case LAYER_ID_CHALLENGE:
		((SelectChallenge *)_nextLayer)->startSelf();
		break;
	default:
		break;
	}
	Global::getInstance()->s->removeLayerToRunningScene(_layer);
}

cocos2d::CCLayer * GoldenMinerScene::getGuideLayer(int _guideId, cocos2d::CCLayer * _loadingLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerPlay", GuideLayerLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
#ifdef										GAME_LAYER_JEWEL_IS_BUTTON
	layer = (GameControl*)ccbReader->readNodeGraphFromFile("37.ccbi"/*, this*/);
#else
	layer = (GameControl*)ccbReader->readNodeGraphFromFile("7.ccbi"/*, this*/);
#endif
	((GuideLayer*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	((GameControl*)layer)->setLoadingLayer(_loadingLayer);
	((GuideLayer*)layer)->setGuideLayer(_guideId);
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getGameLayer(int _gateId, int roleId, cocos2d::CCLayer * _loadingLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerPlay", GameControlLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
#ifdef										GAME_LAYER_JEWEL_IS_BUTTON
	layer = (GameControl*)ccbReader->readNodeGraphFromFile("37.ccbi"/*, this*/);
#else
	layer = (GameControl*)ccbReader->readNodeGraphFromFile("7.ccbi"/*, this*/);
#endif
	((GameControl*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	((GameControl*)layer)->setLoadingLayer(_loadingLayer);
	((GameControl*)layer)->setGameControl(_gateId, roleId);
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getChallengeLayer(int _gateId, int roleId, cocos2d::CCLayer * _loadingLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerPlay2", ChallengeLayerLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
#ifdef										GAME_LAYER_JEWEL_IS_BUTTON
	layer = (GameControl*)ccbReader->readNodeGraphFromFile("38.ccbi"/*, this*/);
#else
	layer = (ChallengeLayer*)ccbReader->readNodeGraphFromFile("27.ccbi"/*, this*/);
#endif
	((ChallengeLayer*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	((GameControl*)layer)->setLoadingLayer(_loadingLayer);
	((ChallengeLayer*)layer)->setChallengeLayer(_gateId, roleId);
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getSettingMenu(cocos2d::CCLayer * _ccLayer, int _layerType)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerSetup", SettingMenuLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (SettingMenu*)ccbReader->readNodeGraphFromFile("3.ccbi"/*, this*/);
	((SettingMenu*)layer)->setForwardLayer(_ccLayer, _layerType);
	((SettingMenu*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getPauseMenu(CCLayer * _ccLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerPause", PauseMenuLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (PauseMenu*)ccbReader->readNodeGraphFromFile("2.ccbi"/*, this*/);
	((PauseMenu*)layer)->setForwardLayer(_ccLayer);
	((PauseMenu*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getSimleGateMenu(cocos2d::CCLayer * _loadingLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayer", SimleGateMenuLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (SimleGateMenu*)ccbReader->readNodeGraphFromFile("1.ccbi"/*, this*/);
	((SimleGateMenu*)layer)->setLoadingLayer(_loadingLayer);
	((SimleGateMenu*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getGameOverMenu(cocos2d::CCLayer *_ccLayer, bool _isWin)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerWin", GameOverMenuLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (GameOverMenu*)ccbReader->readNodeGraphFromFile("4.ccbi"/*, this*/);
	CCLOG("GoldenMinerScene::getGameOverMenu 1 %d", layer->retainCount());
	((GameOverMenu*)layer)->setAnimationManager(ccbReader->getAnimationManager(), _ccLayer, _isWin);
	CCLOG("GoldenMinerScene::getGameOverMenu 2 %d", layer->retainCount());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getChallengeCountMenu(cocos2d::CCLayer *_ccLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerScore", ChallengeCountLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (ChallengeCount*)ccbReader->readNodeGraphFromFile("26.ccbi"/*, this*/);
	((ChallengeCount*)layer)->setAnimationManager(ccbReader->getAnimationManager(), _ccLayer);
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getChallengeOverMenu(int _layerType, cocos2d::CCLayer *_ccLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerRank", ChallengeOverLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (ChallengeOver*)ccbReader->readNodeGraphFromFile("29.ccbi"/*, this*/);
	((ChallengeOver*)layer)->setAnimationManager(ccbReader->getAnimationManager(), _layerType, _ccLayer);
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getSelectChallengeMenu(cocos2d::CCLayer * _loadingLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerBattle", SelectChallengeLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (SelectChallenge*)ccbReader->readNodeGraphFromFile("28.ccbi"/*, this*/);
	((SelectChallenge*)layer)->setLoadingLayer(_loadingLayer);
	((SelectChallenge*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getSelectRoleAndPropMenu(cocos2d::CCLayer * _loadingLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerChoose", SelectRoleAndPropMenuLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (SelectRoleAndPropMenu*)ccbReader->readNodeGraphFromFile("5.ccbi"/*, this*/);
	((SelectRoleAndPropMenu*)layer)->setLoadingLayer(_loadingLayer);
	((SelectRoleAndPropMenu*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getBigGateMenu(cocos2d::CCLayer * _loadingLayer)
{
	CCLOG("GoldenMinerScene::getBigGateMenu");
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerMap", BigGateMenuLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (BigGateMenu*)ccbReader->readNodeGraphFromFile("8.ccbi"/*, this*/);
	((BigGateMenu*)layer)->setLoadingLayer(_loadingLayer);
	((BigGateMenu*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getGameAppendLayer(CCLayer *_ccLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerPlay2", GameAppendLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (GameAppend*)ccbReader->readNodeGraphFromFile("11.ccbi"/*, this*/);
	((GameAppend*)layer)->setForwardLayer(_ccLayer);
	((GameAppend*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getRoleSkillEffect(cocos2d::CCLayer * _ccLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerSkill", RoleSkillEffectLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (RoleSkillEffect*)ccbReader->readNodeGraphFromFile("12.ccbi"/*, this*/);
	((RoleSkillEffect*)layer)->setForwardLayer(_ccLayer);
	((RoleSkillEffect*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getCountDownEffect(cocos2d::CCLayer * _ccLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerCountdown", CountDownEffectLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (CountDownEffect*)ccbReader->readNodeGraphFromFile("10.ccbi"/*, this*/);
	((CountDownEffect*)layer)->setForwardLayer(_ccLayer);
	((CountDownEffect*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getRoleInformation(cocos2d::CCLayer * _ccLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerUnlock", RoleInformationLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (RoleInformation*)ccbReader->readNodeGraphFromFile("6.ccbi"/*, this*/);
	((RoleInformation*)layer)->setForwardLayer(_ccLayer);
	((RoleInformation*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getLoadingLayer(void)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerLoading", LoadingLayerLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (LoadingLayer*)ccbReader->readNodeGraphFromFile("9.ccbi"/*, this*/);
	((LoadingLayer*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getMainLayer(cocos2d::CCLayer * _loadingLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerHomepage", MainLayerLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
#ifndef								GOLDEN_MINER_2_VERSION_REVIEW
#ifdef								GOLDEN_MINER_2_S
	layer = (MainLayer*)ccbReader->readNodeGraphFromFile("40.ccbi"/*, this*/);
#else
	layer = (MainLayer*)ccbReader->readNodeGraphFromFile("15.ccbi"/*, this*/);
#endif
#else
#ifdef								GOLDEN_MINER_2_S
	layer = (MainLayer*)ccbReader->readNodeGraphFromFile("41.ccbi"/*, this*/);
#else
	layer = (MainLayer*)ccbReader->readNodeGraphFromFile("33.ccbi"/*, this*/);// 测试版本
#endif
#endif

	((MainLayer*)layer)->setLoadingLayer(_loadingLayer);
	((MainLayer*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer *  GoldenMinerScene::getMainAppendLayer(cocos2d::CCLayer * _ccLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerHomepage2", MainAppendLayerLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (MainAppendLayer*)ccbReader->readNodeGraphFromFile("35.ccbi"/*, this*/);
	//layer = (MainAppendLayer*)ccbReader->readNodeGraphFromFile("14.ccbi"/*, this*/);
	((MainAppendLayer*)layer)->setAnimationManager(ccbReader->getAnimationManager(), _ccLayer);
	return layer;
}

CCLayer *  GoldenMinerScene::getAboutLayer(cocos2d::CCLayer * _ccLayer, int _layerType)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerAbout", AboutLayerLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (MyAboutLayer*)ccbReader->readNodeGraphFromFile("17.ccbi"/*, this*/);
	((MyAboutLayer*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	((MyAboutLayer*)layer)->setForwardLayer(_ccLayer, _layerType);
	return layer;
}

CCLayer *  GoldenMinerScene::getHalpLayer(cocos2d::CCLayer * _ccLayer, int _layerType)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerHelp", HalpLayerLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (HalpLayer *)ccbReader->readNodeGraphFromFile("16.ccbi"/*, this*/);
	CCLOG("GoldenMinerScene::getHalpLayer 1 %d", layer->retainCount());
	((HalpLayer*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	CCLOG("GoldenMinerScene::getHalpLayer 2 %d", layer->retainCount());
	((HalpLayer*)layer)->setForwardLayer(_ccLayer, _layerType);
	return layer;
}

CCLayer * GoldenMinerScene::getPetParkLayer(cocos2d::CCLayer * _loadingLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerMonster", PetParkLayerLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (PetParkLayer *)ccbReader->readNodeGraphFromFile("21.ccbi"/*, this*/);
	//layer = (PetParkLayer *)ccbReader->readNodeGraphFromFile("18.ccbi"/*, this*/);
	((PetParkLayer*)layer)->setLoadingLayer(_loadingLayer);
	((PetParkLayer*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

CCLayer * GoldenMinerScene::getCartoonLayer(int _cartoonId, cocos2d::CCLayer * _loadingLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerCartoon", CartoonLayerLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (CartoonLayer *)ccbReader->readNodeGraphFromFile("19.ccbi"/*, this*/);
	((CartoonLayer*)layer)->setId(_cartoonId);
	((CartoonLayer*)layer)->setLoadingLayer(_loadingLayer);
	((CartoonLayer*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getPromptLayer(CCLayer *_ccLayer, int _type)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerTips", PromptLayerLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (PromptLayer*)ccbReader->readNodeGraphFromFile("20.ccbi"/*, this*/);
	((PromptLayer*)layer)->setForwardLayer(_ccLayer, _type);
	((PromptLayer*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getShopLayer(cocos2d::CCLayer * _loadingLayer, cocos2d::CCLayer * _ccLayer, int _layerType)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerShop", ShopLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (Shop*)ccbReader->readNodeGraphFromFile("22.ccbi"/*, this*/);
	((Shop*)layer)->setLoadingLayer(_loadingLayer);
	((Shop*)layer)->setForwardLayer(_ccLayer, _layerType);
	((Shop*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getSelectRoleAndPetMenu(cocos2d::CCLayer * _loadingLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerChoose", SelectRoleAndPetLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (SelectRoleAndPet*)ccbReader->readNodeGraphFromFile("24.ccbi"/*, this*/);
	((SelectRoleAndPet*)layer)->setLoadingLayer(_loadingLayer);
	((SelectRoleAndPet*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getSelectPetMenu(cocos2d::CCLayer * _forwardLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerChoose2", SelectPetLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (SelectPet*)ccbReader->readNodeGraphFromFile("25.ccbi"/*, this*/);
	((SelectPet*)layer)->setForwardLayer(_forwardLayer);
	((SelectPet*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getRegisterLayer(cocos2d::CCLayer * _forwardLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerGift", RegisterLayerLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (RegisterLayer*)ccbReader->readNodeGraphFromFile("30.ccbi"/*, this*/);
	((RegisterLayer*)layer)->setForwardLayer(_forwardLayer);
	((RegisterLayer*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getExitLayer(cocos2d::CCLayer * _forwardLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerExit", ExitLayerLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (ExitLayer*)ccbReader->readNodeGraphFromFile("32.ccbi"/*, this*/);
	((ExitLayer*)layer)->setForwardLayer(_forwardLayer);
	((ExitLayer*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getDrawLayer(cocos2d::CCLayer * _forwardLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerLottery", DrawLayerLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (DrawLayer*)ccbReader->readNodeGraphFromFile("31.ccbi"/*, this*/);
	((DrawLayer*)layer)->setForwardLayer(_forwardLayer);
	((DrawLayer*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getTempPromptLayer(CCLayer *_ccLayer, int _type)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerTips2", TemporaryPromptLayerLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (TemporaryPromptLayer*)ccbReader->readNodeGraphFromFile("36.ccbi"/*, this*/);
	((TemporaryPromptLayer*)layer)->setForwardLayer(_ccLayer, _type);
	((TemporaryPromptLayer*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getCostLayer(CCLayer *_ccLayer, int _type)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerMoney", CostLayerLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (CostLayer*)ccbReader->readNodeGraphFromFile("34.ccbi"/*, this*/);
	((CostLayer*)layer)->setForwardLayer(_ccLayer, _type);
	((CostLayer*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getBuddhaLayer(CCLayer *_ccLayer)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerLight", BuddahaLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (Buddaha*)ccbReader->readNodeGraphFromFile("42.ccbi"/*, this*/);
	((Buddaha*)layer)->setForwardLayer(_ccLayer);
	((Buddaha*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}

cocos2d::CCLayer * GoldenMinerScene::getSlipGuideLayer(CCLayer *_ccLayer, int _type)
{
	CCLayer * layer = NULL;
	cocos2d::extension::CCNodeLoaderLibrary* ccNodeLoaderLibrary = NULL;
	cocos2d::extension::CCBReader* ccbReader = NULL;
	ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLayerSword", SlipGuideLoader::loader());
	ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	ccbReader->autorelease();
	layer = (SlipGuide*)ccbReader->readNodeGraphFromFile("43.ccbi"/*, this*/);
	((SlipGuide*)layer)->setForwardLayer(_ccLayer, _type);
	((SlipGuide*)layer)->setAnimationManager(ccbReader->getAnimationManager());
	return layer;
}