#include "RoleSkillEffect.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "GameControl.h"


USING_NS_CC;
USING_NS_CC_EXT;

RoleSkillEffect::RoleSkillEffect(void)
	:mAnimationManager(NULL)
{
}


RoleSkillEffect::~RoleSkillEffect(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	CCLOG("RoleSkillEffect::~RoleSkillEffect");
}

void RoleSkillEffect::onEnter(void)
{
	CCLayer::onEnter();
}

void RoleSkillEffect::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

SEL_MenuHandler RoleSkillEffect::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;
}

cocos2d::SEL_CallFuncN RoleSkillEffect::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calFinish", RoleSkillEffect::calXiaoShiFinish);
}

SEL_CCControlHandler RoleSkillEffect::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool RoleSkillEffect::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void RoleSkillEffect::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(RoleSkillEffect::doAnimationCompleted));
	CC_SAFE_RETAIN(mAnimationManager);
}

void RoleSkillEffect::setForwardLayer(cocos2d::CCLayer *_ccLayer)
{
	forwardLayer = _ccLayer;
}

void RoleSkillEffect::calXiaoShiFinish(CCNode* sender)
{
	Global::getInstance()->s->removeLayerToRunningScene(this);
	this->setVisible(false);
	((GameControl *)forwardLayer)->finishRoleSkillEffect();
	((GameControl *)forwardLayer)->setBackGround(false);
}

void RoleSkillEffect::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"dscj") == 0
		|| strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"dhlz") == 0
		|| strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"jqdj") == 0
		|| strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"sjjz") == 0
		|| strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"hxsh") == 0
		|| strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"huluwa") == 0)
	{	
		Global::getInstance()->s->removeLayerToRunningScene(this);
		this->setVisible(false);
		((GameControl *)forwardLayer)->finishRoleSkillEffect();
		((GameControl *)forwardLayer)->setBackGround(false);
	}
}

void RoleSkillEffect::doSkillEffect(int _roleId)
{
	// 播放转   还有粒子特效
	// 对应的对象要进行的标签的赋值
	switch (_roleId)
	{
	case ROLE_TYPE_XIAOLONGNV:
		mAnimationManager->runAnimationsForSequenceNamed("hxsh");
		break;
	case ROLE_TYPE_TANGSENG:
		mAnimationManager->runAnimationsForSequenceNamed("dscj");
		break;
	case ROLE_TYPE_ZHUBAJIE:
		mAnimationManager->runAnimationsForSequenceNamed("dhlz");
		break;
	case ROLE_TYPE_SHAHESHANG:
		mAnimationManager->runAnimationsForSequenceNamed("jqdj");
		break;
	case ROLE_TYPE_SUNWUKONG:
		mAnimationManager->runAnimationsForSequenceNamed("sjjz");
		break;
	case ROLE_TYPE_HULUWA:
		mAnimationManager->runAnimationsForSequenceNamed("huluwa");
		break;
	default:
		break;
	}
}