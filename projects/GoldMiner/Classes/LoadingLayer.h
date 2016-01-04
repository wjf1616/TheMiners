#ifndef		__LOADINGLAYER_H__
#define		__LOADINGLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"


class LoadingLayer :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	LoadingLayer(void);
	~LoadingLayer(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LoadingLayer, create);

	virtual void onExit(void);

	virtual void onEnterTransitionDidFinish(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void doAnimationCompleted(void);

	void calFinish1(CCNode* sender);
	void calFinish2(CCNode* sender);
	void calFinish3(CCNode* sender);
	void calFinish4(CCNode* sender);

	void loadingLayer(void);

	void addLoadingLayer(int _type, cocos2d::CCLayer * _layer);

	//void appendLoadingLayerNum(int _num);

	void appendFinishLayerNum(int _num);

	void setNextLayer(int _type, cocos2d::CCLayer * _layer);
private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ∂Øª≠π‹¿Ì

	cocos2d::CCArray * myLoadingLayers;

	//bool isSelfLoaded;
	int iLoading;
	
	int playCount;

	//int loadingLayerNum;

	int finishLayerNum;

	int nextLayerType;
	cocos2d::CCLayer * nextlayer;
};

#endif
