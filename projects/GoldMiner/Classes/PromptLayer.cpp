#include "PromptLayer.h"
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
#include "SelectChallenge.h"
#include "DrawLayer.h"
#include "SelectRoleAndPet.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define				HIDE_PETS_SCALE				0.5

PromptLayer::PromptLayer(void)
	:mAnimationManager(NULL)
	,forwardType(-1)
{
	isAward = false;
	timeCount = 0;
}


PromptLayer::~PromptLayer(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	CCLOG("PromptLayer::~PromptLayer");
}

void PromptLayer::onEnter(void)
{
	CCLayer::onEnter();
}

void PromptLayer::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

void PromptLayer::keyBackClicked(void)	
{
	onMenuItemOffClicked(NULL);
}

SEL_MenuHandler PromptLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnOff", PromptLayer::onMenuItemOffClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnConfirm", PromptLayer::onMenuItemConfirmClicked);
	return NULL;
}

SEL_CCControlHandler PromptLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool PromptLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void PromptLayer::onMenuItemOffClicked(cocos2d::CCObject * pSender)
{
	switch(forwardType)
	{
	case LAYER_ID_BIG_GATE_MAP:
		if(type == 10086)
		{
			((BigGateMenu *)forwardLayer)->reBackBackClicked(false);
		}
		else
		{
			((BigGateMenu *)forwardLayer)->setBackGround(false);
		}
		break;
	case LAYER_ID_CHALLENGE:
		if(type == 10086)
		{
			((SelectChallenge *)forwardLayer)->reBackBackClicked(false);
		}
		else
		{
			((SelectChallenge *)forwardLayer)->reBack(0, false);
		}
		break;
	case LAYER_ID_GAMING:
		((GameControl *)forwardLayer)->setBackGround(false);
		break;
	case LAYER_ID_SMILE_GATE_SCENCE:
		((SimleGateMenu *)forwardLayer)->setBackGround(false);
		break;
	case  LAYER_ID_MAIN_APPEND:
		((MainAppendLayer *)forwardLayer)->reBack();
		break;
	case LAYER_ID_SHOP:
		if(type == 2)
		{
			((Shop *)forwardLayer)->setBackGround2(false);
		}
		else if(type == 10086)
		{
			((Shop *)forwardLayer)->reBackBackClicked(false);
		}
		else
		{
			((Shop *)forwardLayer)->clearPropInformation();
		}
		break;
	case LAYER_ID_PROP_ROLE:
		((SelectRoleAndPropMenu *)forwardLayer)->reBack(0,false);
		break;
	case LAYER_ID_GATE_PAUSE:
		((PauseMenu *)forwardLayer)->reBack2(false);
		break;
	case LAYER_ID_PETPARK:
		if(type == 10086)
		{
			((PetParkLayer *)forwardLayer)->reBackBackClicked(false);
		}
		else
		{
			((PetParkLayer *)forwardLayer)->setBackGround(false, type, false);
		}
		break;
	case LAYER_ID_GAMEOVER:
		((GameOverMenu *)forwardLayer)->setBackGround(false);
		break;
	case LAYER_ID_CHALLENGE_COUNT:
		((ChallengeCount *)forwardLayer)->setBackGround(false);
		break;
	case LAYER_ID_PAUSE:
		((PauseMenu *)forwardLayer)->reBack2(false);
		break;
	case LAYER_ID_DRAW:
		((DrawLayer *)forwardLayer)->promptFinish(false);
		break;
	case LAYER_ID_ROLE:
		((SelectRoleAndPet *)forwardLayer)->reBack(0, false);
		break;
	default:
		break;
	}

	Global::getInstance()->s->removeLayerToRunningScene(this);
}

void PromptLayer::onMenuItemConfirmClicked(cocos2d::CCObject * pSender)
{
	LoadingLayer * p;
	CCLayer * p1;
	switch(forwardType)
	{
	case LAYER_ID_PETPARK:
		if(type == 10086)
		{
			((PetParkLayer *)forwardLayer)->reBackBackClicked(true);
		}
		else
		{
			((PetParkLayer *)forwardLayer)->setBackGround(false, type, true);
		}
		break;
	case LAYER_ID_SMILE_GATE_SCENCE:
		p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
		p1 =Global::getInstance()->s->getPetParkLayer(p);
		p->addLoadingLayer(0,p1);
		p->setNextLayer(LAYER_ID_PETPARK, p1);

		Global::getInstance()->s->replaceScene(p);
		break;
	case LAYER_ID_PAUSE:
		((PauseMenu *)forwardLayer)->reBack2(true);
		break;
	case LAYER_ID_BIG_GATE_MAP:
		if(type == 10086)
		{
			((BigGateMenu *)forwardLayer)->reBackBackClicked(true);
		}
		break;
	case LAYER_ID_CHALLENGE:
		if(type == 10086)
		{
			((SelectChallenge *)forwardLayer)->reBackBackClicked(true);
		}
		break;
	case LAYER_ID_SHOP:
		if(type == 10086)
		{
			((Shop *)forwardLayer)->reBackBackClicked(true);
		}
		break;
	case LAYER_ID_DRAW:
		((DrawLayer *)forwardLayer)->promptFinish(true);
		break;
	default:
		break;
	}

	Global::getInstance()->s->removeLayerToRunningScene(this);
}

void PromptLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(PromptLayer::doAnimationCompleted));
	setTouchEnabled(true);
	CC_SAFE_RETAIN(mAnimationManager);
}

void PromptLayer::setForwardLayer(cocos2d::CCLayer *_ccLayer, int _type)
{
	forwardLayer = _ccLayer;
	forwardType = _type;
}

void PromptLayer::bigGateNotOpen(void)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	//forwardType = LAYER_ID_BIG_GATE_MAP;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zanweikaiqi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/changjing.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::simleGateNotOpen(void)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	//forwardType = LAYER_ID_SMILE_GATE_SCENCE;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zanweikaiqi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/guanka.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::hideGateNotOpen(int _hideGateId, cocos2d::CCArray * _array)
{
	CCMenuItemImage * tmp3 = (CCMenuItemImage *)getChildByTag(999)->getChildByTag(5);
	CCTexture2D *pTexture;
	CCRect rect;
	// 添加根据状态换图的代码 (注意添加这里width 和 height跟随图片的宽高变换)
	pTexture = CCTextureCache::sharedTextureCache()->addImage("yindao/guai1.png");
	if (pTexture)
	{
		rect = CCRectZero;
		rect.size = pTexture->getContentSize();
		((CCSprite *)tmp3->getNormalImage())->setTexture(pTexture);
		((CCSprite *)tmp3->getNormalImage())->setTextureRect(rect);
	}
	pTexture = CCTextureCache::sharedTextureCache()->addImage("yindao/guai2.png");
	if (pTexture)
	{
		rect = CCRectZero;
		rect.size = pTexture->getContentSize();
		((CCSprite *)tmp3->getSelectedImage())->setTexture(pTexture);
		((CCSprite *)tmp3->getSelectedImage())->setTextureRect(rect);
	}
	if (pTexture)
	{
		rect = CCRectZero;
		rect.size = pTexture->getContentSize();
		((CCSprite *)tmp3->getDisabledImage())->setTexture(pTexture);
		((CCSprite *)tmp3->getDisabledImage())->setTextureRect(rect);
	}


	CCSprite * tmp = NULL;
	CCNode * tmp2 = NULL;
	tmp = CCSprite::create("yindao/zanweikaiqi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/yangcheng.png");
	tmp->setPosition(ccp(0, 40));
	getChildByTag(2)->addChild(tmp,1);
	char _s[24];
	sprintf(_s, "%d", _hideGateId%18-1);
	CCLabelAtlas * tmp4 = CCLabelAtlas::create(_s, "yindao/shuzi.png", 21, 30, '0');
	tmp4->setPosition(ccp(40, 40));
	getChildByTag(2)->addChild(tmp4,1);

	int start = -150;
	int end = 180;

	for (int i = 0; i < _array->count(); i++)
	{
		switch(((CCInteger *)_array->objectAtIndex(i))->getValue())
		{
		case PET_ELEMENT_JINGXIGUI:
			tmp2 = CCNode::create();
			tmp2->addChild(CCSprite::create("xuanrenyemian/kuang.png"));
			tmp2->addChild(CCSprite::create("xuanrenyemian/jingxi.png"));
			tmp2->setScale(HIDE_PETS_SCALE);
			tmp2->setPosition(ccp(start + (end - start)*(i+1.0)/(_array->count()+1), -20));
			getChildByTag(2)->addChild(tmp2,1);
			break;
		case PET_ELEMENT_LINGGANDAWANG:
			tmp2 = CCNode::create();
			tmp2->addChild(CCSprite::create("xuanrenyemian/kuang.png"));
			tmp2->addChild(CCSprite::create("xuanrenyemian/linggan.png"));
			tmp2->setScale(HIDE_PETS_SCALE);
			tmp2->setPosition(ccp(start + (end - start)*(i+1.0)/(_array->count()+1), -20));
			getChildByTag(2)->addChild(tmp2,1);
			break;
		case PET_ELEMENT_YUMIANGONGZHU:
			tmp2 = CCNode::create();
			tmp2->addChild(CCSprite::create("xuanrenyemian/kuang.png"));
			tmp2->addChild(CCSprite::create("xuanrenyemian/yumian.png"));
			tmp2->setScale(HIDE_PETS_SCALE);
			tmp2->setPosition(ccp(start + (end - start)*(i+1.0)/(_array->count()+1), -20));
			getChildByTag(2)->addChild(tmp2,1);
			break;
		case PET_ELEMENT_NIUMOWANG:
			tmp2 = CCNode::create();
			tmp2->addChild(CCSprite::create("xuanrenyemian/kuang.png"));
			tmp2->addChild(CCSprite::create("xuanrenyemian/niumo.png"));
			tmp2->setScale(HIDE_PETS_SCALE);
			tmp2->setPosition(ccp(start + (end - start)*(i+1.0)/(_array->count()+1), -20));
			getChildByTag(2)->addChild(tmp2,1);
			break;
		}
	}

	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::challengeGateNotOpen(void)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	//forwardType = LAYER_ID_MAIN_APPEND;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zanweikaiqi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/tiaozhan.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::notOpen(void)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	//forwardType = LAYER_ID_MAIN_APPEND;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/zanweikaifang.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::addNewRole(void)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	//forwardType = LAYER_ID_GAMING;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/jiangli.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/kaiqi1.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::payRoleIsHaving(void)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/yikaiqi.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::addNewGate(int _mapId)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	//forwardType = LAYER_ID_GAMING;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/gongxi3.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/dikaiqi.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	switch(_mapId)
	{
	case BIG_GATE_TYPE_BAOXIANGGUO:
		tmp = CCSprite::create("yindao/er.png");
		break;
	case BIG_GATE_TYPE_TONGYIANHE:
		tmp = CCSprite::create("yindao/er.png");
		break;
	case BIG_GATE_TYPE_NVERGUO:
		tmp = CCSprite::create("yindao/san.png");
		break;
	case BIG_GATE_TYPE_HUOYANSHAN:
		tmp = CCSprite::create("yindao/si.png");
		break;
	case BIG_GATE_TYPE_LINGSHAN:
		tmp = CCSprite::create("yindao/wu.png");
		break;
	default:
		break;
	}
	tmp->setPosition(ccp(-55, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::challengeGateOpen(void)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	//forwardType = LAYER_ID_MAIN_APPEND;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/gongxi3.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/dengzheni.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::targetInformationByTargetId(int targetId)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	//forwardType = LAYER_ID_GAMING;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);

	switch(targetId)
	{
	case TARGET_ID_BOMB:
		tmp = CCSprite::create("yindao/baozha.png");
		tmp->setPosition(ccp(0, 0));
		getChildByTag(2)->addChild(tmp,1);
		break;
	case DYNAMIC_ID_PEARL_SHELL:
		tmp = CCSprite::create("yindao/beike.png");
		tmp->setPosition(ccp(0, 0));
		getChildByTag(2)->addChild(tmp,1);
		break;
	case TARGET_ID_BOX:
		tmp = CCSprite::create("yindao/baoxiang.png");
		tmp->setPosition(ccp(0, 0));
		getChildByTag(2)->addChild(tmp,1);
		break;
	case DYNAMIC_ID_BAT:
		tmp = CCSprite::create("yindao/bianfu.png");
		tmp->setPosition(ccp(0, 0));
		getChildByTag(2)->addChild(tmp,1);
		break;
	case DYNAMIC_ID_JINGXIGUI:
		tmp = CCSprite::create("yindao/jingxi.png");
		tmp->setPosition(ccp(0, 0));
		getChildByTag(2)->addChild(tmp,1);
		break;
	case TARGET_ID_FOOD:
		tmp = CCSprite::create("yindao/kouliang2.png");
		tmp->setPosition(ccp(0, 0));
		getChildByTag(2)->addChild(tmp,1);
		break;
	case DYNAMIC_ID_HUOHUALIAN:
		tmp = CCSprite::create("yindao/lianhua.png");
		tmp->setPosition(ccp(0, 0));
		getChildByTag(2)->addChild(tmp,1);
		break;
	case DYNAMIC_ID_LINGGANDAWANG:
		tmp = CCSprite::create("yindao/linggan.png");
		tmp->setPosition(ccp(0, 0));
		getChildByTag(2)->addChild(tmp,1);
		break;
	case DYNAMIC_ID_NIUMOWANG:
		tmp = CCSprite::create("yindao/niumo.png");
		tmp->setPosition(ccp(0, 0));
		getChildByTag(2)->addChild(tmp,1);
		break;
	case DYNAMIC_ID_BIRD:
		tmp = CCSprite::create("yindao/xiaoniao.png");
		tmp->setPosition(ccp(0, 0));
		getChildByTag(2)->addChild(tmp,1);
		break;
	case DYNAMIC_ID_XIAOCHOUYU:
		tmp = CCSprite::create("yindao/xiaoyu.png");
		tmp->setPosition(ccp(0, 0));
		getChildByTag(2)->addChild(tmp,1);
		break;
	case DYNAMIC_ID_STAR:
		tmp = CCSprite::create("yindao/xingxing.png");
		tmp->setPosition(ccp(0, 0));
		getChildByTag(2)->addChild(tmp,1);
		break;
	case DYNAMIC_ID_YUMIANGONGZHU:
		tmp = CCSprite::create("yindao/yumian.png");
		tmp->setPosition(ccp(0, 0));
		getChildByTag(2)->addChild(tmp,1);
		break;
		break;
	default:
		break;
	}
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::challengeGateOut(void)
{	//forwardType = LAYER_ID_GATE_PAUSE;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/fanhuicaidan.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::challengeGateReplay(void)
{
	//forwardType = LAYER_ID_GATE_PAUSE;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/chongxin.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::specailFood(void)
{
	type = 2;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/kouliang3.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::jewelInformation(void)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	//forwardType = LAYER_ID_PETPARK;
	type = 0;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/jiqi2.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::moonLightInformation(void)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	//forwardType = LAYER_ID_PETPARK;
	type = 0;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/daojishi.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::roleIntruduceById(int _roleId)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	//forwardType = LAYER_ID_PETPARK;
	type = 0;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/renwushuoming.png");
	getChildByTag(1)->addChild(tmp,1);
	switch(_roleId)
	{
	case ROLE_TYPE_TANGSENG:
		tmp = CCSprite::create("yindao/1.png");
		break;
	case ROLE_TYPE_ZHUBAJIE:
		tmp = CCSprite::create("yindao/2.png");
		break;
	case ROLE_TYPE_SHAHESHANG:
		tmp = CCSprite::create("yindao/3.png");
		break;
	case ROLE_TYPE_SUNWUKONG:
		tmp = CCSprite::create("yindao/4.png");
		break;
	case ROLE_TYPE_XIAOLONGNV:
		tmp = CCSprite::create("yindao/5.png");
		break;
	case ROLE_TYPE_HULUWA:
		tmp = CCSprite::create("yindao/6.png");
		break;
	}
	tmp->setPosition(ccp(7, -6));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::petParkInformation(void)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	//forwardType = LAYER_ID_PETPARK;
	type = 0;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/guaiwuwo.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::addNewHideGate(int _hideGateId)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	//forwardType = LAYER_ID_PETPARK;
	type = 0;

	CCSprite * tmp = NULL;
	CCLabelAtlas * tmp2 = NULL;
	char _s[28];
	tmp = CCSprite::create("yindao/gongxi3.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/chenggong.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/henxian.png");
	tmp->setPosition(ccp(88, 28));
	getChildByTag(2)->addChild(tmp,1);
	sprintf(_s, "%d", Global::getInstance()->getMapIdByGateId(_hideGateId)+1);
	tmp2 = CCLabelAtlas::create(_s, "yindao/shuzi.png", 21, 30, '0');
	tmp2->setPosition(ccp(57, 10));
	getChildByTag(2)->addChild(tmp2,1);
	sprintf(_s, "%d", Global::getInstance()->getSmallGateIdByGateId(_hideGateId));
	tmp2 = CCLabelAtlas::create(_s, "yindao/shuzi.png", 21, 30, '0');
	tmp2->setPosition(ccp(100, 10));
	getChildByTag(2)->addChild(tmp2,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::isCheer(void)
{
	//forwardType = LAYER_ID_PETPARK;
	type = 1;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/shifou.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::isBack(void)
{
	CCSprite * tmp = NULL;

	type = 10086;

	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/shifou3.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::drawOpenCost(const char _cost[])
{
	CCSprite * tmp = NULL;

	type = 10086;

	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/xiaohao.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	//char _s[28];
	//sprintf(_s, "%d", _cost);
	CCLabelAtlas * tmp2 = CCLabelAtlas::create(_cost, "yindao/shuzi.png", 21, 30, '0');
	tmp2->setPosition(ccp(50, 10));
	getChildByTag(2)->addChild(tmp2,1);
	tmp = CCSprite::create("slsb/yuanbao.png");
	tmp->setPosition(ccp(140, 30));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::isChallengeShopBack(void)
{
	CCSprite * tmp = NULL;

	type = 10086;

	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/shifou3.png");
	tmp->setPosition(ccp(0, 10));
	getChildByTag(2)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/yijing.png");
	tmp->setPosition(ccp(10, -30));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::isReplay(void)
{
	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/shifou1.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::doAnimationCompleted(void)
{
	setKeypadEnabled(true);
}

void PromptLayer::miaoZhunXianInformation(void)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	type = 2;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/jimai.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::miaoBuddahaInformation(void)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	type = 1;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/jimai.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}

void PromptLayer::doGuideWin(void)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	//forwardType = LAYER_ID_GAMING;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/gongxi3.png");
	getChildByTag(1)->addChild(tmp,1);
	tmp = CCSprite::create("yindao/gongxi1.png");
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}


void PromptLayer::doGuideAward(int _guideId)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	//forwardType = LAYER_ID_GAMING;

	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
	isAward = true;
	CCSprite * tmp = NULL;
	char _s[32];
	CCLabelAtlas * leastCoinLabel = NULL;
	switch(_guideId)
	{
	case GUIDE_ID_PILL:
		tmp = CCSprite::create("yindao/jiangli.png");
		getChildByTag(1)->addChild(tmp,1);
		tmp = CCSprite::create("yindao/gongxi.png");
		tmp->setPosition(ccp(-50, 0));
		getChildByTag(2)->addChild(tmp,1);
		tmp = CCSprite::create("youxi/liliang.png");
		tmp->setPosition(ccp(50, 0));
		getChildByTag(2)->addChild(tmp,1);
		tmp = CCSprite::create("yindao/x.png");
		tmp->setPosition(ccp(100, 0));
		getChildByTag(2)->addChild(tmp,1);
		sprintf(_s, "%d",5);
		leastCoinLabel = CCLabelAtlas::create(_s, "yindao/shuzi.png", 21, 30, '0');
		leastCoinLabel->setPosition(ccp(120, -15));
		getChildByTag(2)->addChild(leastCoinLabel,1);
		break;
	case GUIDE_ID_GRENADE:
		tmp = CCSprite::create("yindao/jiangli.png");
		getChildByTag(1)->addChild(tmp,1);
		tmp = CCSprite::create("yindao/gongxi.png");
		tmp->setPosition(ccp(-50, 0));
		getChildByTag(2)->addChild(tmp,1);
		tmp = CCSprite::create("youxi/zhadan.png");
		tmp->setPosition(ccp(50, 0));
		getChildByTag(2)->addChild(tmp,1);
		tmp = CCSprite::create("yindao/x.png");
		tmp->setPosition(ccp(100, 0));
		getChildByTag(2)->addChild(tmp,1);
		sprintf(_s, "%d",5);
		leastCoinLabel = CCLabelAtlas::create(_s, "yindao/shuzi.png", 21, 30, '0');
		leastCoinLabel->setPosition(ccp(120, -15));
		getChildByTag(2)->addChild(leastCoinLabel,1);
		break;
	case GUIDE_ID_MOONLIGHT:
		tmp = CCSprite::create("yindao/jiangli.png");
		getChildByTag(1)->addChild(tmp,1);
		tmp = CCSprite::create("yindao/gongxi.png");
		tmp->setPosition(ccp(-50, 0));
		getChildByTag(2)->addChild(tmp,1);
		tmp = CCSprite::create("youxi/shalou.png");
		tmp->setPosition(ccp(50, 0));
		getChildByTag(2)->addChild(tmp,1);
		tmp = CCSprite::create("yindao/x.png");
		tmp->setPosition(ccp(100, 0));
		getChildByTag(2)->addChild(tmp,1);
		sprintf(_s, "%d",5);
		leastCoinLabel = CCLabelAtlas::create(_s, "yindao/shuzi.png", 21, 30, '0');
		leastCoinLabel->setPosition(ccp(120, -15));
		getChildByTag(2)->addChild(leastCoinLabel,1);
		break;
	case GUIDE_ID_ROLE_SKILL:
		tmp = CCSprite::create("yindao/jiangli.png");
		getChildByTag(1)->addChild(tmp,1);
		tmp = CCSprite::create("yindao/jiangli2.png");
		tmp->setPosition(ccp(-50, 10));
		getChildByTag(2)->addChild(tmp,1);
		sprintf(_s, "%d",100);
		leastCoinLabel = CCLabelAtlas::create(_s, "yindao/shuzi.png", 21, 30, '0');
		leastCoinLabel->setPosition(ccp(-10, -5));
		getChildByTag(2)->addChild(leastCoinLabel,1);
		tmp = CCSprite::create("yindao/yuanbao2.png");
		tmp->setPosition(ccp(80, 10));
		getChildByTag(2)->addChild(tmp,1);
		//tmp = CCSprite::create("yindao/wancheng2.png");
		//tmp->setPosition(ccp(0, 10));
		//getChildByTag(2)->addChild(tmp,1);
		//tmp = CCSprite::create("yindao/jiangli2.png");
		//tmp->setPosition(ccp(-50, -40));
		//getChildByTag(2)->addChild(tmp,1);
		//sprintf(_s, "%d",100);
		//leastCoinLabel = CCLabelAtlas::create(_s, "yindao/shuzi.png", 21, 30, '0');
		//leastCoinLabel->setPosition(ccp(-10, -55));
		//getChildByTag(2)->addChild(leastCoinLabel,1);
		//tmp = CCSprite::create("yindao/yuanbao2.png");
		//tmp->setPosition(ccp(80, -40));
		//getChildByTag(2)->addChild(tmp,1);
		break;
	case GUIDE_ID_JEWEIL_SKILL:
		tmp = CCSprite::create("yindao/jiangli.png");
		getChildByTag(1)->addChild(tmp,1);
		tmp = CCSprite::create("yindao/jiangli2.png");
		tmp->setPosition(ccp(-50, 10));
		getChildByTag(2)->addChild(tmp,1);
		sprintf(_s, "%d",100);
		leastCoinLabel = CCLabelAtlas::create(_s, "yindao/shuzi.png", 21, 30, '0');
		leastCoinLabel->setPosition(ccp(-10, -5));
		getChildByTag(2)->addChild(leastCoinLabel,1);
		tmp = CCSprite::create("yindao/yuanbao2.png");
		tmp->setPosition(ccp(80, 10));
		getChildByTag(2)->addChild(tmp,1);
		//tmp = CCSprite::create("yindao/wanchengsuoyou.png");
		//tmp->setPosition(ccp(0, 10));
		//getChildByTag(2)->addChild(tmp,1);
		//tmp = CCSprite::create("yindao/jiangli2.png");
		//tmp->setPosition(ccp(-50, -40));
		//getChildByTag(2)->addChild(tmp,1);
		//sprintf(_s, "%d",100);
		//leastCoinLabel = CCLabelAtlas::create(_s, "yindao/shuzi.png", 21, 30, '0');
		//leastCoinLabel->setPosition(ccp(-10, -55));
		//getChildByTag(2)->addChild(leastCoinLabel,1);
		//tmp = CCSprite::create("yindao/yuanbao2.png");
		//tmp->setPosition(ccp(80, -40));
		//getChildByTag(2)->addChild(tmp,1);
		break;
	default:
		tmp = CCSprite::create("yindao/jiangli.png");
		getChildByTag(1)->addChild(tmp,1);
		tmp = CCSprite::create("yindao/jiangli2.png");
		tmp->setPosition(ccp(-50, 10));
		getChildByTag(2)->addChild(tmp,1);
		sprintf(_s, "%d",100);
		leastCoinLabel = CCLabelAtlas::create(_s, "yindao/shuzi.png", 21, 30, '0');
		leastCoinLabel->setPosition(ccp(-10, -5));
		getChildByTag(2)->addChild(leastCoinLabel,1);
		tmp = CCSprite::create("yindao/yuanbao2.png");
		tmp->setPosition(ccp(80, 10));
		getChildByTag(2)->addChild(tmp,1);
		//tmp = CCSprite::create("yindao/wanc1.png");
		//tmp->setPosition(ccp(0, 10));
		//getChildByTag(2)->addChild(tmp,1);
		//tmp = CCSprite::create("yindao/jiangli2.png");
		//tmp->setPosition(ccp(-50, -40));
		//getChildByTag(2)->addChild(tmp,1);
		//sprintf(_s, "%d",100);
		//leastCoinLabel = CCLabelAtlas::create(_s, "yindao/shuzi.png", 21, 30, '0');
		//leastCoinLabel->setPosition(ccp(-10, -55));
		//getChildByTag(2)->addChild(leastCoinLabel,1);
		//tmp = CCSprite::create("yindao/yuanbao2.png");
		//tmp->setPosition(ccp(80, -40));
		//getChildByTag(2)->addChild(tmp,1);
		break;
	}
	// 转光
	CCSprite* sp1 = CCSprite::create("yindao/guang2.png");
	CCRotateBy* rot = CCRotateBy::create(4, 360);
	CCAction* forever = CCRepeatForever::create(rot);
	sp1->runAction(forever);           
	sp1->setPosition(getChildByTag(4)->getPosition());   
	addChild(sp1, -1);
}

void PromptLayer::doGamingTip(int _tipId)
{
	getChildByTag(999)->getChildByTag(5)->setVisible(false);

	//forwardType = LAYER_ID_GAMING;

	CCSprite * tmp = NULL;
	tmp = CCSprite::create("yindao/zhuyi.png");
	getChildByTag(1)->addChild(tmp,1);

	switch(_tipId)
	{
	case 31:
		tmp = CCSprite::create("yindao/baozha.png");
		break;
	case 32:
		tmp = CCSprite::create("yindao/baoxiang.png");
		break;
	case 33:
		tmp = CCSprite::create("yindao/zuanshi.png");
		break;
	case 34:
		tmp = CCSprite::create("yindao/jiqi.png");
		break;
	case 39:
		tmp = CCSprite::create("yindao/kouliang2.png");
		break;
	case 40:
		tmp = CCSprite::create("yindao/jingxi.png");
		break;
	case 41:
		tmp = CCSprite::create("yindao/linggan.png");
		break;
	case 42:
		tmp = CCSprite::create("yindao/yumian.png");
		break;
	case 43:
		tmp = CCSprite::create("yindao/niumo.png");
		break;
	case 44:
		tmp = CCSprite::create("yindao/xiaoyu.png");
		break;
	case 45:
		tmp = CCSprite::create("yindao/xiaoniao.png");
		break;
	case 46:
		tmp = CCSprite::create("yindao/beike.png");
		break;
	case 47:
		tmp = CCSprite::create("yindao/bianfu.png");
		break;
	case 48:
		tmp = CCSprite::create("yindao/lianhua.png");
		break;
	case 49:
		tmp = CCSprite::create("yindao/xingxing.png");
		break;
	}
	tmp->setPosition(ccp(0, 0));
	getChildByTag(2)->addChild(tmp,1);
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
}