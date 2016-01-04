#include "TemporaryPromptLayer.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "GameControl.h"
#include "BigGateMenu.h"
#include "SimleGateMenu.h"
#include "SelectRoleAndPropMenu.h"
#include "MainAppendLayer.h"
#include "PetParkLayer.h"
#include "Shop.h"
#include "GameOverMenu.h"
#include "ChallengeCount.h"
#include "LoadingLayer.h"
#include "PauseMenu.h"
#include "RegisterLayer.h"
#include "SelectChallenge.h"
#include "SelectRoleAndPet.h"
#include "RoleInformation.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define				HIDE_PETS_SCALE				0.6

TemporaryPromptLayer::TemporaryPromptLayer(void)
	:mAnimationManager(NULL)
	,forwardType(-1)
{
	type2 = -1;
}


TemporaryPromptLayer::~TemporaryPromptLayer(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);

	CCLOG("TemporaryPromptLayer::~TemporaryPromptLayer");
}

void TemporaryPromptLayer::onEnter(void)
{
	CCLayer::onEnter();
}

void TemporaryPromptLayer::onExit(void)
{
	CCLayer::onExit();
}

SEL_MenuHandler TemporaryPromptLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;
}

SEL_CCControlHandler TemporaryPromptLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool TemporaryPromptLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void TemporaryPromptLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(TemporaryPromptLayer::doAnimationCompleted));

	CC_SAFE_RETAIN(mAnimationManager);
}

void TemporaryPromptLayer::doPromptByType(int _type)
{	
	type = _type;

	switch(type)
	{
	case TEMP_PROMPT_BUY_SUCCESS:
		mAnimationManager->runAnimationsForSequenceNamed("goumai");
		break;
	case TEMP_PROMPT_INGOT_NOT_RICH:
		mAnimationManager->runAnimationsForSequenceNamed("yuanbao");
		break;
	case TEMP_PROMPT_PROP_FULL:
		mAnimationManager->runAnimationsForSequenceNamed("daoju");
		break;
	case TEMP_PROMPT_FOOD_FULL:
		mAnimationManager->runAnimationsForSequenceNamed("kouliang");
		break;
	}
}

void TemporaryPromptLayer::setPromptType2(int _type2)
{
	type2 = _type2;
}

void TemporaryPromptLayer::setForwardLayer(cocos2d::CCLayer *_ccLayer, int _type)
{
	forwardLayer = _ccLayer;
	forwardType = _type;
}

void TemporaryPromptLayer::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"goumai") == 0
		|| strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"yuanbao") == 0
		|| strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"daoju") == 0
		|| strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"kouliang") == 0)
	{
		switch(forwardType)
		{
		case LAYER_ID_GAMING:
			((GameControl *)forwardLayer)->setBackGround(false);
			break;
		case LAYER_ID_SHOP:
			if (type2 == 1)
			{
				((Shop *)forwardLayer)->clearPropInformation();				
			}
			else if (type2 == 2)
			{
				((Shop *)forwardLayer)->setBackGround2(false);
			}
			break;
		case LAYER_ID_PETPARK:
			((PetParkLayer *)forwardLayer)->setBackGround(false, type2, false);
			break;
		case LAYER_ID_GAMEOVER:
			((GameOverMenu *)forwardLayer)->setBackGround(false);
			break;
		case LAYER_ID_CHALLENGE_COUNT:
			((ChallengeCount *)forwardLayer)->setBackGround(false);
			break;
		case LAYER_ID_REGISTER:
			((RegisterLayer *)forwardLayer)->tempPromptReBack();
			break;
		case LAYER_ID_ROLE_INFORMATION:
			((RoleInformation *)forwardLayer)->InformationReBack();
			break;
		case LAYER_ID_ROLE:
			((SelectRoleAndPet *)forwardLayer)->reBack(0, false);
			break;
		case LAYER_ID_CHALLENGE:
			((SelectChallenge *)forwardLayer)->reBack(0, false);
			break;
		default:
			break;
		}

		Global::getInstance()->s->removeLayerToRunningScene(this);
	}
}