#include "SpotLightLayer.h"

static const ccColor4B myGrey4 = {0,0,0,200};

SpotLightLayer::SpotLightLayer(CCNode * _stencil, CCNode * _message, CCNode * _directionSprite)
{
	stencil = NULL;
	message = NULL;
	direction = NULL;
	stencilAction = NULL;
	messageAction = NULL;
	directionAction = NULL;
	
	stencil = _stencil;
	message = _message;
	direction = _directionSprite;

	//创建裁减节点类
	CCClippingNode *clipper = CCClippingNode::create();
	clipper->setContentSize(CCDirector::sharedDirector()->getVisibleSize());//*new CCSize(200, 200));
	clipper->setAlphaThreshold(0);
	//为设置裁减节点类设置“裁减模板”
	this->addChild(clipper);
	clipper->setStencil(stencil);
	clipper->setInverted(true);
	//设置裁减节点类所放的内容
	CCLayerColor * grewLayer = CCLayerColor::create(myGrey4);
	clipper->addChild(grewLayer);

	if (message != NULL)
	{
		clipper->addChild(message, 1);
		message->setVisible(false);
	}
	if (direction != NULL)
	{
		clipper->addChild(direction, 1);
		direction->setVisible(false);
	}

	setTouchEnabled(false);

	this->autorelease();
}

void SpotLightLayer::onExit(void)
{
	////if (callBackFunc != NULL)
	////{
	////	callBackFunc->release();
	////	callBackFunc = NULL;
	////}
	//if (stencilAction != NULL)
	//{
	//	stencilAction->release();
	//	stencilAction = NULL;
	//}
	//if (messageAction != NULL)
	//{
	//	messageAction->release();
	//	messageAction = NULL;
	//}
	//if (directionAction != NULL)
	//{
	//	directionAction->release();
	//	directionAction = NULL;
	//}
}

SpotLightLayer::~SpotLightLayer(void)
{
	//if (callBackFunc != NULL)
	//{
	//	callBackFunc->release();
	//	callBackFunc = NULL;
	//}
	if (stencilAction != NULL)
	{
		stencilAction->release();
		stencilAction = NULL;
	}
	if (messageAction != NULL)
	{
		messageAction->release();
		messageAction = NULL;
	}
	if (directionAction != NULL)
	{
		directionAction->release();
		directionAction = NULL;
	}
	CCLOG("SpotLightLayer::~SpotLightLayer");
}

void SpotLightLayer::ccTouchesEnded(CCSet* touches, CCEvent* pevent)
{
	if (callBackFunc != NULL)
	{
		callBackFunc->execute();
		callBackFunc->release();
		callBackFunc = NULL;
		setTouchEnabled(false);
	}
}

void SpotLightLayer::startAction(void)
{
	if (stencilAction == NULL)
	{
		setTouchEnabled(true);
	}
	else
	{
		stencil->runAction(stencilAction);
	}
}

void SpotLightLayer::setActionFinishCallBackFunc(CCCallFunc* _Func)
{
	assert(_Func);
	callBackFunc = _Func;
	callBackFunc->retain();
}

void SpotLightLayer::setStencilAction(CCFiniteTimeAction * _stencilAction)
{
	if (_stencilAction != NULL)
	{
		stencilAction = CCSequence::create(_stencilAction,
			CCCallFunc::create(this, callfunc_selector(SpotLightLayer::callbackStencil)), 
			NULL);
		stencilAction->retain();
	}
}

void SpotLightLayer::setMessageAction(CCFiniteTimeAction * _messageAction)
{
	if (_messageAction != NULL)
	{
		messageAction = CCSequence::create(	_messageAction,
			CCCallFunc::create(this, callfunc_selector(SpotLightLayer::callbackMessage)), 
			NULL);
		messageAction->retain();
	}
}

void SpotLightLayer::setDirectionSpriteAction(CCFiniteTimeAction * _directionAction)
{
	if (_directionAction != NULL)
	{
		directionAction = CCSequence::create(_directionAction,
			CCCallFunc::create(this, callfunc_selector(SpotLightLayer::callbackDirection)), 
			NULL);
		directionAction->retain();
	}
}

void SpotLightLayer::callbackStencil()
{
	stencilAction = NULL;
	message->setVisible(true);
	direction->setVisible(true);
	if (messageAction == NULL)
	{
		setTouchEnabled(true);
	}
	else
	{
		message->runAction(messageAction);
	}
	if (directionAction == NULL)
	{
		setTouchEnabled(true);
	}
	else
	{
		direction->runAction(directionAction);
	}
}

void SpotLightLayer::callbackMessage()
{
	messageAction = NULL;
	//if (directionAction == NULL)
	//{
	//	setTouchEnabled(true);
	//}
	//else
	//{
	//	direction->runAction(directionAction);
	//}
}

void SpotLightLayer::callbackDirection()
{
	directionAction = NULL;
	setTouchEnabled(true);
}