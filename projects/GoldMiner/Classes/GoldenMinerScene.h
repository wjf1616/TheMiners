#ifndef __GOLDENMINERSENCE_H__
#define __GOLDENMINERSENCE_H__

#include "cocos2d.h"

class GoldenMinerScene
{
public:
	GoldenMinerScene(void);
	~GoldenMinerScene(void);

	cocos2d::CCScene * getSence(void);

	// 想当前的sence上再添加layer
	void addLayerToScene(cocos2d::CCLayer * _layer, cocos2d::CCScene * _sence);

	// 想当前的sence上再添加layer
	void addLayerToRunningScene(cocos2d::CCLayer * _layer);

	void removeLayerToRunningScene(cocos2d::CCLayer * _layer);

	// 推入对应场景(最好为非全屏的场景)
	//void pushScene(cocos2d::CCLayer * _layer);
	void removeLayerToRunningSceneAndSetNextLayer(cocos2d::CCLayer * _layer, int _nextType, cocos2d::CCLayer * _nextLayer);

	// 显示队列想要场景
	void popScene();
	
	// 代替显示
	void replaceScene(cocos2d::CCLayer * _layer);
	void replaceSceneWithCrossFade(float t,cocos2d::CCLayer * _layer);
	void replaceSceneWithTime(float t,cocos2d::CCLayer * _layer);

	// 设置相关layer方法
	cocos2d::CCLayer * getGuideLayer(int _guideId, cocos2d::CCLayer * _loadingLayer);
	cocos2d::CCLayer * getGameLayer(int _gateId, int roleId, cocos2d::CCLayer * _loadingLayer);
	cocos2d::CCLayer * getChallengeLayer(int _gateId, int roleId, cocos2d::CCLayer * _loadingLayer);
	cocos2d::CCLayer * getSettingMenu(cocos2d::CCLayer * _ccLayer, int _layerType);
	cocos2d::CCLayer * getPauseMenu(cocos2d::CCLayer * _ccLayer);
	cocos2d::CCLayer * getSimleGateMenu(cocos2d::CCLayer * _loadingLayer);
	cocos2d::CCLayer * getGameOverMenu(cocos2d::CCLayer *_ccLayer, bool _isWin);
	cocos2d::CCLayer * getChallengeOverMenu(int _layerType, cocos2d::CCLayer *_ccLayer);
	cocos2d::CCLayer * getChallengeCountMenu(cocos2d::CCLayer *_ccLayer);
	cocos2d::CCLayer * getSelectChallengeMenu(cocos2d::CCLayer * _loadingLayer);
	cocos2d::CCLayer * getSelectRoleAndPropMenu(cocos2d::CCLayer * _loadingLayer);
	cocos2d::CCLayer * getBigGateMenu(cocos2d::CCLayer * _loadingLayer);
	cocos2d::CCLayer * getGameAppendLayer(cocos2d::CCLayer *_ccLayer);
	cocos2d::CCLayer * getRoleSkillEffect(cocos2d::CCLayer * _ccLayer);
	cocos2d::CCLayer * getCountDownEffect(cocos2d::CCLayer * _ccLayer);
	cocos2d::CCLayer * getRoleInformation(cocos2d::CCLayer * _ccLayer);
	cocos2d::CCLayer * getLoadingLayer(void);
	cocos2d::CCLayer * getMainLayer(cocos2d::CCLayer * _loadingLayer);
	cocos2d::CCLayer * getMainAppendLayer(cocos2d::CCLayer * _ccLayer);
	cocos2d::CCLayer * getAboutLayer(cocos2d::CCLayer * _ccLayer, int _layerType);
	cocos2d::CCLayer * getHalpLayer(cocos2d::CCLayer * _ccLayer, int _layerType);
	cocos2d::CCLayer * getPetParkLayer(cocos2d::CCLayer * _loadingLayer);
	cocos2d::CCLayer * getCartoonLayer(int _cartoonId, cocos2d::CCLayer * _loadingLayer);
	cocos2d::CCLayer * getPromptLayer(cocos2d::CCLayer *_ccLayer, int _type);
	cocos2d::CCLayer * getShopLayer(cocos2d::CCLayer * _loadingLayer, cocos2d::CCLayer * _ccLayer, int _layerType);
	cocos2d::CCLayer * getSelectRoleAndPetMenu(cocos2d::CCLayer * _loadingLayer);
	cocos2d::CCLayer * getSelectPetMenu(cocos2d::CCLayer * _forwardLayer);
	cocos2d::CCLayer * getRegisterLayer(cocos2d::CCLayer * _forwardLayer);
	cocos2d::CCLayer * getExitLayer(cocos2d::CCLayer * _forwardLayer);
	cocos2d::CCLayer * getDrawLayer(cocos2d::CCLayer * _forwardLayer);
	cocos2d::CCLayer * getTempPromptLayer(cocos2d::CCLayer *_ccLayer, int _type);
	cocos2d::CCLayer * getCostLayer(cocos2d::CCLayer *_ccLayer, int _type);
	cocos2d::CCLayer * getBuddhaLayer(cocos2d::CCLayer *_ccLayer);
	cocos2d::CCLayer * getSlipGuideLayer(cocos2d::CCLayer *_ccLayer, int _type);
};

#endif

