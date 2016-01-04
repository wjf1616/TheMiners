#include "RoleInformation.h"
#include "Global.h"
#include "GoldenMinerScene.h"
//#include "SelectRoleAndPropMenu.h"
#include "SelectRoleAndPet.h"
#include "Player.h"
#include "TemporaryPromptLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

RoleInformation::RoleInformation(void)
	: mAnimationManager(NULL)
	,forwardLayer(NULL)
{
	isBackGround = false;
}

void RoleInformation::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

RoleInformation::~RoleInformation(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	CCLOG("RoleInformation::~RoleInformation");
}

SEL_MenuHandler RoleInformation::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnUnlock", RoleInformation::onMenuItemUnlockClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBuy", RoleInformation::onMenuItemBuyClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnOff", RoleInformation::onMenuItemOffClicked);

	return NULL;
}

SEL_CCControlHandler RoleInformation::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool RoleInformation::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void RoleInformation::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(RoleInformation::doAnimationCompleted));
	CC_SAFE_RETAIN(mAnimationManager);
}

void RoleInformation::setForwardLayer(cocos2d::CCLayer *_ccLayer)
{
	forwardLayer = _ccLayer;
}

void RoleInformation::onMenuItemBuyClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	isBackGround = true;

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	int price =  Global::getInstance()->getRolePriceByRoleId(roleId);
	if (Player::getInstance()->getPropNum(PROP_TYPE_INGOT) >= price)
	{
		Player::getInstance()->appendPropNum(PROP_TYPE_INGOT ,-price);
		Player::getInstance()->savePropNum(PROP_TYPE_INGOT ,-price);
		Player::getInstance()->setRoleHavingStatusByRoleId(roleId ,true);
		
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FINISH);

		TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_ROLE_INFORMATION);
		_layer->doPromptByType(TEMP_PROMPT_BUY_SUCCESS);
		Global::getInstance()->s->addLayerToRunningScene(_layer);
		isBuy = true;
		//((SelectRoleAndPet *)forwardLayer)->reBack(0, true);
		//((SelectRoleAndPropMenu *)forwardLayer)->reBack(0, true);
	}
	else
	{
		// Ç®²»¹»¹ºÂò
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FAILED);

		TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_ROLE_INFORMATION);
		_layer->doPromptByType(TEMP_PROMPT_INGOT_NOT_RICH);
		Global::getInstance()->s->addLayerToRunningScene(_layer);
		isBuy = false;
		//((SelectRoleAndPet *)forwardLayer)->reBack(0, false);
		//((SelectRoleAndPropMenu *)forwardLayer)->reBack(0, false);
	}
	//Global::getInstance()->s->removeLayerToRunningScene(this);
}

void RoleInformation::onMenuItemOffClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	((SelectRoleAndPet *)forwardLayer)->reBack(0, false);
	//((SelectRoleAndPropMenu *)forwardLayer)->reBack(0, false);
	Global::getInstance()->s->removeLayerToRunningScene(this);
}

void RoleInformation::onMenuItemUnlockClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	((SelectRoleAndPet *)forwardLayer)->reBack(0, false);
	//((SelectRoleAndPropMenu *)forwardLayer)->reBack(0, false);
	Global::getInstance()->s->removeLayerToRunningScene(this);
}

void RoleInformation::getRoleAboutInfromationByRoleId(int _roleId)
{
	mAnimationManager->runAnimationsForSequenceNamed("jiesuo");
	roleId = _roleId;
	CCSprite * tmp = NULL;
	CCLabelAtlas * tmp1 = NULL;
	char _s[24];
	switch(_roleId)
	{
	case ROLE_TYPE_XIAOLONGNV:
		tmp = CCSprite::create("xuanrenyemian/3.png");
		tmp->setPositionY(10);
		getChildByTag(1)->addChild(tmp);
		break;
	case ROLE_TYPE_TANGSENG:
		break;
	case ROLE_TYPE_ZHUBAJIE:
		tmp = CCSprite::create("xuanrenyemian/1.png");
		tmp->setPositionY(10);
		getChildByTag(1)->addChild(tmp);
		tmp = CCSprite::create("xuanrenyemian/yiyongyou.png");
		tmp->setPositionY(-40);
		getChildByTag(1)->addChild(tmp);
		sprintf(_s,"%d",Player::getInstance()->getStarSum());
		tmp1 = CCLabelAtlas::create(_s, "xuanrenyemian/shuzi.png", 16, 21, '0');
		tmp1->setPosition(ccp(5, -50));
		getChildByTag(1)->addChild(tmp1);
		break;
	case ROLE_TYPE_SHAHESHANG:
		tmp = CCSprite::create("xuanrenyemian/2.png");
		tmp->setPositionY(10);
		getChildByTag(1)->addChild(tmp);
		tmp = CCSprite::create("xuanrenyemian/yiyongyou.png");
		tmp->setPositionY(-40);
		getChildByTag(1)->addChild(tmp);
		sprintf(_s,"%d",Player::getInstance()->getStarSum());
		tmp1 = CCLabelAtlas::create(_s, "xuanrenyemian/shuzi.png", 16, 21, '0');
		tmp1->setPosition(ccp(5, -50));
		getChildByTag(1)->addChild(tmp1);
		break;
	case ROLE_TYPE_SUNWUKONG:
		tmp = CCSprite::create("yindao/renwu.png");
		getChildByTag(1)->addChild(tmp);
		break;
	case ROLE_TYPE_HULUWA:
		tmp = CCSprite::create("yindao/renwu.png");
		getChildByTag(1)->addChild(tmp);
		break;
	default:
		break;
	}
	//mAnimationManager->runAnimationsForSequenceNamed("jiesuo");
	//CCSprite * tmp = NULL;
	//switch(_roleId)
	//{
	//case ROLE_TYPE_XIAOLONGNV:
	//	tmp = CCSprite::create("xuanren/tongguan.png");
	//	getChildByTag(1)->addChild(tmp);
	//	tmp = CCSprite::create("xuanren/4.png");
	//	tmp->setPositionX(-30);
	//	getChildByTag(1)->addChild(tmp);
	//	break;
	//case ROLE_TYPE_TANGSENG:
	//	break;
	//case ROLE_TYPE_ZHUBAJIE:
	//	tmp = CCSprite::create("xuanren/tongguan.png");
	//	getChildByTag(1)->addChild(tmp);
	//	tmp = CCSprite::create("xuanren/1.png");
	//	tmp->setPositionX(-30);
	//	getChildByTag(1)->addChild(tmp);
	//	break;
	//case ROLE_TYPE_SHAHESHANG:
	//	tmp = CCSprite::create("xuanren/tongguan.png");
	//	getChildByTag(1)->addChild(tmp);
	//	tmp = CCSprite::create("xuanren/2.png");
	//	tmp->setPositionX(-30);
	//	getChildByTag(1)->addChild(tmp);
	//	break;
	//case ROLE_TYPE_SUNWUKONG:
	//	tmp = CCSprite::create("xuanren/tongguan.png");
	//	getChildByTag(1)->addChild(tmp);
	//	tmp = CCSprite::create("xuanren/3.png");
	//	tmp->setPositionX(-30);
	//	getChildByTag(1)->addChild(tmp);
	//	break;
	//case ROLE_TYPE_HULUWA:
	//	tmp = CCSprite::create("yindao/renwu.png");
	//	getChildByTag(1)->addChild(tmp);
	//	break;
	//default:
	//	break;
	//}
}

void RoleInformation::getRoleGetInfromationByRoleId(int _roleId)
{
	mAnimationManager->runAnimationsForSequenceNamed("zhaomu");
	roleId = _roleId;
	CCSprite * tmp = NULL;
	CCLabelAtlas * tmp1 = NULL;
	char _s[32];
	switch(_roleId)
	{
	case ROLE_TYPE_XIAOLONGNV:
		tmp = CCSprite::create("xuanren/zhaomu.png");
		tmp->setPositionX(-60);
		getChildByTag(1)->addChild(tmp);
		tmp = CCSprite::create("xuanren/yuanbao2.png");
		tmp->setPosition(ccp(30, 20));
		getChildByTag(1)->addChild(tmp);
		tmp = CCSprite::create("yindao/x.png");
		tmp->setPosition(ccp(70, 22));
		getChildByTag(1)->addChild(tmp);
		sprintf(_s,"%d",Global::getInstance()->getRolePriceByRoleId(roleId));
		tmp1 = CCLabelAtlas::create(_s, "xuanren/zhaomushuzi.png", 22, 30, '0');
		tmp1->setPosition(ccp(90, 8));
		getChildByTag(1)->addChild(tmp1);
		break;
	case ROLE_TYPE_TANGSENG:
		break;
	case ROLE_TYPE_ZHUBAJIE:
		tmp = CCSprite::create("xuanren/zhaomu.png");
		tmp->setPositionX(-60);
		getChildByTag(1)->addChild(tmp);
		tmp = CCSprite::create("xuanren/yuanbao2.png");
		tmp->setPosition(ccp(30, 20));
		getChildByTag(1)->addChild(tmp);
		tmp = CCSprite::create("yindao/x.png");
		tmp->setPosition(ccp(70, 22));
		getChildByTag(1)->addChild(tmp);
		sprintf(_s,"%d",Global::getInstance()->getRolePriceByRoleId(roleId));
		tmp1 = CCLabelAtlas::create(_s, "xuanren/zhaomushuzi.png", 22, 30, '0');
		tmp1->setPosition(ccp(90, 8));
		getChildByTag(1)->addChild(tmp1);
		break;
	case ROLE_TYPE_SHAHESHANG:
		tmp = CCSprite::create("xuanren/zhaomu.png");
		tmp->setPositionX(-60);
		getChildByTag(1)->addChild(tmp);
		tmp = CCSprite::create("xuanren/yuanbao2.png");
		tmp->setPosition(ccp(30, 20));
		getChildByTag(1)->addChild(tmp);
		tmp = CCSprite::create("yindao/x.png");
		tmp->setPosition(ccp(70, 22));
		getChildByTag(1)->addChild(tmp);
		sprintf(_s,"%d",Global::getInstance()->getRolePriceByRoleId(roleId));
		tmp1 = CCLabelAtlas::create(_s, "xuanren/zhaomushuzi.png", 22, 30, '0');
		tmp1->setPosition(ccp(90, 8));
		getChildByTag(1)->addChild(tmp1);
		break;
	case ROLE_TYPE_SUNWUKONG:
		tmp = CCSprite::create("xuanren/zhaomu.png");
		tmp->setPositionX(-60);
		getChildByTag(1)->addChild(tmp);
		tmp = CCSprite::create("xuanren/yuanbao2.png");
		tmp->setPosition(ccp(30, 20));
		getChildByTag(1)->addChild(tmp);
		tmp = CCSprite::create("yindao/x.png");
		tmp->setPosition(ccp(70, 22));
		getChildByTag(1)->addChild(tmp);
		sprintf(_s,"%d",Global::getInstance()->getRolePriceByRoleId(roleId));
		tmp1 = CCLabelAtlas::create(_s, "xuanren/zhaomushuzi.png", 22, 30, '0');
		tmp1->setPosition(ccp(90, 8));
		getChildByTag(1)->addChild(tmp1);
		break;
	case ROLE_TYPE_HULUWA:
		tmp = CCSprite::create("yindao/renwu.png");
		getChildByTag(1)->addChild(tmp);
		break;
	default:
		break;
	}
}
	
void RoleInformation::doAnimationCompleted(void)
{

}

void RoleInformation::InformationReBack(void)
{
	isBackGround = false;

	if (isBuy)
	{
		((SelectRoleAndPet *)forwardLayer)->reBack(0, true);
		Global::getInstance()->s->removeLayerToRunningScene(this);
	}
}