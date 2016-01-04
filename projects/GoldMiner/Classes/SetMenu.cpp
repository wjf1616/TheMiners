#include "SetMenu.h"

USING_NS_CC;
USING_NS_CC_EXT;

SetMenu::SetMenu(void)
{
}


SetMenu::~SetMenu(void)
{
}

SEL_MenuHandler SetMenu::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnOff", SetMenu::onMenuItemOffClicked);

	return NULL;
}

SEL_CCControlHandler SetMenu::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool SetMenu::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void SetMenu::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	//mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(PauseMenu::doAnimationCompleted));
	mAnimationManager->runAnimations("chuxian");
	CC_SAFE_RETAIN(mAnimationManager);
}

void SetMenu::onMenuItemOffClicked(cocos2d::CCObject * pSender)
{
	mAnimationManager->runAnimations("xiaoshi");
}