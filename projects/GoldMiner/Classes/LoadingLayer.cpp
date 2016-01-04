#include "LoadingLayer.h"
#include "Global.h"
#include "GoldenMinerScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

LoadingLayer::LoadingLayer(void)
	: mAnimationManager(NULL)
	,playCount(0)
	//,loadingLayerNum(0)
	,finishLayerNum(0)
	,nextLayerType(-1)
	,nextlayer(NULL)
	,myLoadingLayers(NULL)
	//,isSelfLoaded(false)
{
	playCount -= (rand()%2+1);
	iLoading = 0;
}

void LoadingLayer::onEnterTransitionDidFinish(void)
{
	CCLOG("LoadingLayer: onEnterTransitionDidFinish");
	CCLayer::onEnterTransitionDidFinish();

	//time_t  time1 = time(NULL);
	//struct tm *tm;
	//tm = localtime(&time1);
	//CCLOG("time 5 %d",tm->tm_sec);
	//if (myLoadingLayers != NULL)
	//{
	//	for (int i = 0; i < myLoadingLayers->count(); i++)
	//	{
	//		Global::getInstance()->s->addLayerToRunningScene((CCLayer *)myLoadingLayers->objectAtIndex(i));
	//		((CCLayer *)myLoadingLayers->objectAtIndex(i))->setZOrder(-1);
	//	}
	//}
	//time1 = time(NULL);
	//tm = localtime(&time1);
	//CCLOG("time 6 %d",tm->tm_sec);
}

void LoadingLayer::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);
	CCLayer::onExit();
}

LoadingLayer::~LoadingLayer(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	CCObject * p;
	CCARRAY_FOREACH(myLoadingLayers, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCLOG("LoadingLayer: ~LoadingLayer");
}

SEL_MenuHandler LoadingLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;
}

SEL_CCControlHandler LoadingLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName)
{
	return NULL;
}

cocos2d::SEL_CallFuncN LoadingLayer::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calFinish1", LoadingLayer::calFinish1);
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calFinish2", LoadingLayer::calFinish2);
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calFinish3", LoadingLayer::calFinish3);
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calFinish4", LoadingLayer::calFinish4);
}

bool LoadingLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void LoadingLayer::calFinish1(CCNode* sender)
{
	if (myLoadingLayers != NULL && (iLoading < myLoadingLayers->count()))
	{
		Global::getInstance()->s->addLayerToRunningScene((CCLayer *)myLoadingLayers->objectAtIndex(iLoading));
		((CCLayer *)myLoadingLayers->objectAtIndex(iLoading))->setZOrder(-1);
		iLoading++;
	}
	
	if (playCount == -1)
	{
		playCount = 1;
	}

	if (playCount > 0 && (myLoadingLayers->count() == finishLayerNum))
	{
		Global::getInstance()->s->removeLayerToRunningSceneAndSetNextLayer(this, nextLayerType, nextlayer);
		//nextlayer->release();
		finishLayerNum = -1;
	}
}

void LoadingLayer::calFinish2(CCNode* sender)
{
	if (myLoadingLayers != NULL && (iLoading < myLoadingLayers->count()))
	{
		Global::getInstance()->s->addLayerToRunningScene((CCLayer *)myLoadingLayers->objectAtIndex(iLoading));
		((CCLayer *)myLoadingLayers->objectAtIndex(iLoading))->setZOrder(-1);
		iLoading++;
	}
	if (playCount == -2)
	{
		playCount = 1;
	}
	if (playCount > 0 && (myLoadingLayers->count() == finishLayerNum))
	{
		Global::getInstance()->s->removeLayerToRunningSceneAndSetNextLayer(this, nextLayerType, nextlayer);
		//nextlayer->release();
		finishLayerNum = -1;
	}
}

void LoadingLayer::calFinish3(CCNode* sender)
{
	if (myLoadingLayers != NULL && (iLoading < myLoadingLayers->count()))
	{
		Global::getInstance()->s->addLayerToRunningScene((CCLayer *)myLoadingLayers->objectAtIndex(iLoading));
		((CCLayer *)myLoadingLayers->objectAtIndex(iLoading))->setZOrder(-1);
		iLoading++;
	}
	if (playCount == -3)
	{
		playCount = 1;
	}
	if (playCount > 0 && (myLoadingLayers->count() == finishLayerNum))
	{
		Global::getInstance()->s->removeLayerToRunningSceneAndSetNextLayer(this, nextLayerType, nextlayer);
		//nextlayer->release();
		finishLayerNum = -1;
	}
}

void LoadingLayer::calFinish4(CCNode* sender)
{
	if (myLoadingLayers != NULL && (iLoading < myLoadingLayers->count()))
	{
		Global::getInstance()->s->addLayerToRunningScene((CCLayer *)myLoadingLayers->objectAtIndex(iLoading));
		((CCLayer *)myLoadingLayers->objectAtIndex(iLoading))->setZOrder(-1);
		iLoading++;
	}
	if (playCount == -4)
	{
		playCount = 1;
	}
	if (playCount > 0 && (myLoadingLayers->count() == finishLayerNum))
	{
		Global::getInstance()->s->removeLayerToRunningSceneAndSetNextLayer(this, nextLayerType, nextlayer);
		//nextlayer->release();
		finishLayerNum = -1;
	}
}

void LoadingLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;

	int i = rand()%15;

	switch(i)
	{
	case 0:
		getChildByTag(1)->addChild(CCSprite::create("loading/1.png"));
		break;
	case 1:
		getChildByTag(1)->addChild(CCSprite::create("loading/2.png"));
		break;
	case 2:
		getChildByTag(1)->addChild(CCSprite::create("loading/3.png"));
		break;
	case 3:
		getChildByTag(1)->addChild(CCSprite::create("loading/4.png"));
		break;
	case 4:
		getChildByTag(1)->addChild(CCSprite::create("loading/5.png"));
		break;
	case 5:
		getChildByTag(1)->addChild(CCSprite::create("loading/6.png"));
		break;
	case 6:
		getChildByTag(1)->addChild(CCSprite::create("loading/7.png"));
		break;
	case 7:
		getChildByTag(1)->addChild(CCSprite::create("loading/8.png"));
		break;
	case 8:
		getChildByTag(1)->addChild(CCSprite::create("loading/9.png"));
		break;
	case 9:
		getChildByTag(1)->addChild(CCSprite::create("loading/10.png"));
		break;
	case 10:
		getChildByTag(1)->addChild(CCSprite::create("loading/11.png"));
		break;
	case 11:
		getChildByTag(1)->addChild(CCSprite::create("loading/12.png"));
		break;
	case 12:
		getChildByTag(1)->addChild(CCSprite::create("loading/13.png"));
		break;
	case 13:
		getChildByTag(1)->addChild(CCSprite::create("loading/14.png"));
		break;
	case 14:
		getChildByTag(1)->addChild(CCSprite::create("loading/15.png"));
		break;
	default:
		getChildByTag(1)->addChild(CCSprite::create("loading/1.png"));
		break;
	}


	mAnimationManager->runAnimationsForSequenceNamed("loading");
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(LoadingLayer::doAnimationCompleted));
	CC_SAFE_RETAIN(mAnimationManager);
}

void LoadingLayer::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"loading") == 0)
	{	
		mAnimationManager->runAnimationsForSequenceNamed("loading");
		playCount++;

		if (playCount > 0 && (myLoadingLayers->count() == finishLayerNum))
		{
			Global::getInstance()->s->removeLayerToRunningSceneAndSetNextLayer(this, nextLayerType, nextlayer);
			//nextlayer->release();
			finishLayerNum = -1;
		}
	}
}

void LoadingLayer::addLoadingLayer(int _type, cocos2d::CCLayer * _layer)
{
	if (myLoadingLayers == NULL)
	{
		myLoadingLayers = new cocos2d::CCArray();
	}

	myLoadingLayers->addObject(_layer);
}

//void LoadingLayer::appendLoadingLayerNum(int _num)
//{
//	loadingLayerNum += _num;
//}

void LoadingLayer::appendFinishLayerNum(int _num)
{
	finishLayerNum += _num;
}

void LoadingLayer::setNextLayer(int _type, cocos2d::CCLayer * _layer)
{
	nextLayerType = _type;
	nextlayer = _layer;

	//nextlayer->retain();
}