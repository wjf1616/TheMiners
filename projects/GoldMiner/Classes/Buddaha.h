#ifndef								__BUDDAHA_LAYER__
#define								__BUDDAHA_LAYER__

#include "cocos2d.h"
#include "cocos-ext.h"



class Buddaha:
	public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner   
{
public:
	Buddaha(void);
	~Buddaha(void);
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Buddaha, create);

	virtual void onEnter(void);
	virtual void onExit(void);

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);

	void OnStart1(CCNode* sender);
	void OnStart2(CCNode* sender);
	void OnStart3(CCNode* sender);

	void setForwardLayer(cocos2d::CCLayer * _ccLayer);
	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);
	void doAnimationCompleted(void);

	void doAction(float _f);

private:
	cocos2d::extension::CCBAnimationManager *mAnimationManager;// ∂Øª≠π‹¿Ì∆˜

	cocos2d::CCLayer * forwardLayer;
	bool isDoAction;

	cocos2d::CCLabelAtlas * beforeTarget;
	cocos2d::CCLabelAtlas * afterTarget;
	cocos2d::CCArray * zhuan;
	bool isZhuan;
	int timeCount;

	cocos2d::CCArray * makeZhuan(double _x, double _y, int _type, cocos2d::CCNode * _node);
	void setZhuanIsDoing(bool _b);
};

//class Buddaha;
class CCBReader;

class BuddahaLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BuddahaLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Buddaha);
};

#endif
