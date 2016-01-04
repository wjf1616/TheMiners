#ifndef											__SPOT_LIGHT_LAYER_H__
#define											__SPOT_LIGHT_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class SpotLightLayer :
	public cocos2d::CCLayer
{
public:
	SpotLightLayer(CCNode * _stencil, CCNode * _message, CCNode * _directionSprite);
	~SpotLightLayer(void);

	virtual void onExit(void);
	void setStencilAction(CCFiniteTimeAction * _stencilAction);
	void setMessageAction(CCFiniteTimeAction * _messageAction);
	void setDirectionSpriteAction(CCFiniteTimeAction * _directionAction);
	virtual void ccTouchesEnded(CCSet* touches, CCEvent* pevent);

	void startAction(void);
	void setActionFinishCallBackFunc(CCCallFunc * _Func);
private:
	CCNode * stencil;
	CCNode * message;
	CCNode * direction;

	CCFiniteTimeAction * stencilAction;
	CCFiniteTimeAction * messageAction;
	CCFiniteTimeAction * directionAction;

	CCCallFunc * callBackFunc;

	void callbackStencil();
	void callbackMessage();
	void callbackDirection();
};


#endif
