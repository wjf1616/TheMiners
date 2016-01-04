#ifndef		__CARTOON_LAYER_H__
#define		__CARTOON_LAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class CartoonLayer :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	CartoonLayer(void);
	~CartoonLayer(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CartoonLayer, create);

	virtual void onEnterTransitionDidFinish(void);
	virtual void onExit();

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void setId(int _cartoonId);

	void doAction(float _f);
	void doAnimationCompleted(void);

	void setNextLayer(int _type, cocos2d::CCLayer * _layer);

	void setLoadingLayer(cocos2d::CCLayer * _layer);

	void startSelf(void);
private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ∂Øª≠π‹¿Ì∆˜

	int nextLayerType;
	cocos2d::CCLayer * nextlayer;
	cocos2d::CCLayer * loadingLayer;

	cocos2d::CCSprite * jixu;

	int cartoonId;

	cocos2d::CCSprite * bye;

	float timeCount;

	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
};

#endif
