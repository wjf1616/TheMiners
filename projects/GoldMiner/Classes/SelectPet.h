#ifndef		__SELECTPET_H__
#define		__SELECTPET_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Prop.h"


class SelectPet :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	SelectPet(void);
	~SelectPet(void);

	virtual void onEnter(void);

	virtual void onExit(void);

	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SelectPet, create);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	bool outOrBack(bool _out);

	bool selectOtherPet(int _index);
	void doAnimationCompleted(void);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);
	void setForwardLayer(cocos2d::CCLayer * _layer);
private:
	bool isDoAction;

	cocos2d::extension::CCBAnimationManager *mAnimationManager;

	cocos2d::CCSprite * selectPet;

	cocos2d::CCArray * petsId;
	cocos2d::CCArray * petsSprite;
	cocos2d::CCArray * petsHaving;
	cocos2d::CCArray * petsUnHaving;

	cocos2d::CCSprite * getSpriteByTypeId(int _id);
	void exchangeSpriteByTypeId(cocos2d::CCSprite * _sprite, int _id);
};

#endif

