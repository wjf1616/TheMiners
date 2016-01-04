#ifndef		__TEMPORARYPROMPTLAYER_H__
#define		__TEMPORARYPROMPTLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#define				TEMP_PROMPT_BUY_SUCCESS					1
#define				TEMP_PROMPT_INGOT_NOT_RICH				2
#define				TEMP_PROMPT_PROP_FULL					3
#define				TEMP_PROMPT_FOOD_FULL					4


class TemporaryPromptLayer :
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	TemporaryPromptLayer(void);
	~TemporaryPromptLayer(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TemporaryPromptLayer, create);

	virtual void onExit(void);
	virtual void onEnter(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void setForwardLayer(cocos2d::CCLayer *_ccLayer, int _type);

	void doPromptByType(int _type);
	void setPromptType2(int _type2);

	void doAnimationCompleted(void);
private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ∂Øª≠π‹¿Ì∆˜
	cocos2d::CCLayer * forwardLayer;
	int forwardType;

	int type;
	int type2;
};

#endif

