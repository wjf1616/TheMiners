#include "SettingMenu.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "PauseMenu.h"
#include "MainAppendLayer.h"
#include "Player.h"

USING_NS_CC;
USING_NS_CC_EXT;

SettingMenu::SettingMenu(void)
	: mAnimationManager(NULL)
{
	isDoAction = false;
}

SettingMenu::~SettingMenu(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);

	CCLOG("SettingMenu::~SettingMenu");
}

void SettingMenu::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

void SettingMenu::onEnter(void)
{
	CCLayer::onEnter();
	// Create the switch
	music = CCControlSwitch::create
		(
		CCSprite::create("shezhi/di.png"),
		CCSprite::create("shezhi/kai.png"),
		CCSprite::create("shezhi/guan.png"),
		CCSprite::create("shezhi/tuo.png")
		);
	music->setPosition(ccp (470, 280));
	musicEffect = Player::getInstance()->getMusicEffect();
	music->setOn(musicEffect);
	addChild(music);
	music->addTargetWithActionForControlEvents(this, cccontrol_selector(SettingMenu::musicValueChanged), CCControlEventValueChanged);
	// Update the value label
	musicValueChanged(music, CCControlEventValueChanged);

	// Create the switch
	backMusic = CCControlSwitch::create
		(
		CCSprite::create("shezhi/di.png"),
		CCSprite::create("shezhi/kai.png"),
		CCSprite::create("shezhi/guan.png"),
		CCSprite::create("shezhi/tuo2.png")
		);
	backMusic->setPosition(ccp (470, 170));
	musicBackGround = Player::getInstance()->getMusicBackGround();
	backMusic->setOn(musicBackGround);
	addChild(backMusic);
	backMusic->addTargetWithActionForControlEvents(this, cccontrol_selector(SettingMenu::backMusicValueChanged), CCControlEventValueChanged);
	// Update the value label
	backMusicValueChanged(backMusic, CCControlEventValueChanged);
}

void SettingMenu::keyBackClicked(void)	
{
	onMenuItemOffClicked(NULL);
}

SEL_MenuHandler SettingMenu::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnOff", SettingMenu::onMenuItemOffClicked);

	return NULL;
}

SEL_CCControlHandler SettingMenu::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool SettingMenu::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void SettingMenu::PlayAnimation(int _id)
{
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
	isDoAction = true;
}

void SettingMenu::setForwardLayer(cocos2d::CCLayer * _ccLayer, int _layerType)
{
	forwardLayer = _ccLayer;
	forwardType = _layerType;
	setKeypadEnabled(true);
}

void SettingMenu::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
	isDoAction = true;
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(SettingMenu::doAnimationCompleted));
	CC_SAFE_RETAIN(mAnimationManager);
}

void SettingMenu::onMenuItemOffClicked(cocos2d::CCObject * pSender)
{
	if (isDoAction)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	music->setVisible(false);
	backMusic->setVisible(false);
	mAnimationManager->runAnimationsForSequenceNamed("xiaoshi");
	isDoAction = true;
}

void SettingMenu::musicValueChanged(CCObject* sender, CCControlEvent controlEvent)
{
	CCControlSwitch* pSwitch = (CCControlSwitch*)sender;
	musicEffect = pSwitch->isOn();
	Player::getInstance()->setMusicEffect(musicEffect);
	Player::getInstance()->saveMusic();
}

void SettingMenu::backMusicValueChanged(CCObject* sender, CCControlEvent controlEvent)
{
	CCControlSwitch* pSwitch = (CCControlSwitch*)sender;
	musicBackGround = pSwitch->isOn();
	Player::getInstance()->setMusicBackGround(musicBackGround);
	Player::getInstance()->saveMusic();
}

void SettingMenu::doAnimationCompleted(void)
{
	isDoAction = false;
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"xiaoshi") == 0)
	{	
		Global::getInstance()->s->removeLayerToRunningScene(this);
		// 只有在退出的时候才存储到文件中去
		Player::getInstance()->saveMusic();
		if (forwardType == LAYER_ID_GATE_PAUSE)
		{
			((PauseMenu *)forwardLayer)->reBack();
		} 
		else if (forwardType == LAYER_ID_MAIN)
		{
			((MainAppendLayer *)forwardLayer)->reBack();
		}
	}
}