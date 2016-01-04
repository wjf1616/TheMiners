#include "SelectRoleAndPet.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "RoleInformation.h"
#include "Player.h"
#include "CartoonLayer.h"
#include "GameControl.h"
#include "LoadingLayer.h"
#include "PromptLayer.h"
#include "SelectPet.h"
#include "Shop.h"
#include "TemporaryPromptLayer.h"
#include "CostLayer.h"
#include "SlipGuide.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define			SelectRoleAndPet_YUN_ASIDE						11	
#define			SelectRoleAndPet_FRAME_ASIDE					111
#define			SelectRoleAndPet_BUTTON_ASIDE					11
#define			SelectRoleAndPet_YUN_MIDDLE						21	
#define			SelectRoleAndPet_FRAME_MIDDLE					121
#define			SelectRoleAndPet_BUTTON_MIDDLE					21

#define			SelectRoleAndPet_BUTTON_SELECTED_UP			102
#define			SelectRoleAndPet_BUTTON_UNSELECTED_DOWN		101


#define		SelectRoleAndPet_POINT_Y										40
#define		SelectRoleAndPet_POINT_X										30


static const ccColor3B myGrey={60,60,60};
static const ccColor4B myGrey4 = {0,0,0,200};

SelectRoleAndPet::SelectRoleAndPet(void)
	: mAnimationManager(NULL)
	,greyLayer(NULL)
	,isBackGround(false)
	,loadingLayer(NULL)
{
	Player::getInstance()->setOpenNewRole(false);
	introducehuluwaindex = -1;
	forwardLayer = NULL;
	forwardType = 0;
	myButton = NULL;
}


SelectRoleAndPet::~SelectRoleAndPet(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);


	CC_SAFE_RELEASE_NULL(ingotNum);// 道具选择按钮
	CC_SAFE_RELEASE_NULL(coupletSelect);// 道具选择按钮
	CC_SAFE_RELEASE_NULL(coupletAbout);// 道具选择按钮

	CC_SAFE_RELEASE(introducehuluwa);

	CCObject * p;
	CC_SAFE_RELEASE(pointIndexSprite);
	CCARRAY_FOREACH(selectRoleSpritesName, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(selectRoleSpritesTips, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(pointRoleSprites, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectSpritesIntroduce, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectRoleSpeedBackground, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectRolePowerBackground, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectRoleSpeed, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectRolePower, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectRoleSpeedInteger, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectRolePowerInteger, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	//CCARRAY_FOREACH(selectRoleSpritesSpeed, p)
	//{
	//	CC_SAFE_RELEASE_NULL(p);
	//}
	//CCARRAY_FOREACH(selectRoleSpritesPower, p)
	//{
	//	CC_SAFE_RELEASE_NULL(p);
	//}
	CCARRAY_FOREACH(selectRoleSpritesIntroduce, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(selectRoleSprites, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(selectRoleSpritesIsHaving, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(selectRoleSpritesIsOpen, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectSprites, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectRoleSpritesIsHaving, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectRoleSpritesIsOpen, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectYunSprites, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectButtonSelectSprites, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectButtonBuySprites, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectGetSelectSprites, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectAboutSelectSprites, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectFrameSprites, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}

	CCLOG("SelectRoleAndPet::~SelectRoleAndPet");
}

void SelectRoleAndPet::onEnter(void)
{
	CCLayer::onEnter();

	setTouchPriority(-256);

	if(Player::getInstance()->getSelectPet() > 0)
	{
		isPetVisiable = true;
		petLayer = (SelectPet *)Global::getInstance()->s->getSelectPetMenu(this);
		petLayer->setVisible(true);
		addChild(petLayer, 1000);
	}
	else
	{
		isPetVisiable = false;
		petLayer = NULL;
	}

	setIsPet(false);

	setVisible(false);
	isBackGround = true;

	Player::getInstance()->getMusicControl()->playOtherBackGround();

	isFristRolePage = true;
	currRoleIndex = (Player::getInstance()->getLastRoleSelect() - 1 + ROLE_TYPE_COUNT)%ROLE_TYPE_COUNT;
	char _s[32];
	sprintf(_s, "%d",Player::getInstance()->getPropNum(PROP_TYPE_INGOT));
	ingotNum = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
	CC_SAFE_RETAIN(ingotNum);
	addChild(ingotNum, 998);

	coupletSelect = CCSprite::create("xuanren/yishangzhen.png");// 已上阵
	coupletSelect->setPosition(ccp(280, 320));
	CC_SAFE_RETAIN(coupletSelect);
	addChild(coupletSelect);
	coupletAbout = CCSprite::create("xuanren/weijiesuo.png");// 未解锁
	coupletAbout->setPosition(ccp(280, 320));
	CC_SAFE_RETAIN(coupletAbout);
	addChild(coupletAbout);

	currSelectSprites = new CCArray();
	currSelectRoleSpritesIsHaving = new cocos2d::CCArray();
	selectRoleSpritesIsOpen = new cocos2d::CCArray();
	selectRoleSprites = new CCArray();
	selectRoleSpritesIsHaving = new cocos2d::CCArray();
	currSelectRoleSpritesIsOpen = new cocos2d::CCArray();
	// 人物界面
	selectRoleSpritesName = new CCArray();
	selectRoleSpritesTips = new cocos2d::CCArray();
	currSelectRoleSpeedBackground = new CCArray();
	currSelectRolePowerBackground = new CCArray();
	currSelectRoleSpeed = new CCArray();
	currSelectRolePower = new CCArray();
	currSelectRoleSpeedInteger = new CCArray();
	currSelectRolePowerInteger = new CCArray();
	currSelectYunSprites = new CCArray();
	currSelectButtonSelectSprites = new CCArray();
	currSelectButtonBuySprites = new CCArray();
	currSelectAboutSelectSprites = new CCArray();
	currSelectGetSelectSprites = new CCArray();
	currSelectFrameSprites = new CCArray();
	currSelectSpritesIntroduce = new cocos2d::CCArray();
	//selectRoleSpritesSpeed = new CCArray();
	//selectRoleSpritesPower = new CCArray();
	selectRoleSpritesIntroduce = new CCArray();
	pointRoleSprites = new cocos2d::CCArray();


	initSprites();

	setNodeBySelectIndex(true);

	((CCSprite *)selectRoleSpritesName->objectAtIndex((currRoleIndex + 1)%selectRoleSpritesName->count()))->setVisible(true);

	schedule(schedule_selector(SelectRoleAndPet::doAction), 0);

	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void SelectRoleAndPet::onEnterTransitionDidFinish(void)
{
	CCLayer::onEnterTransitionDidFinish();

	if (loadingLayer != NULL)
	{
		((LoadingLayer *)loadingLayer)->appendFinishLayerNum(1);
	}
	else
	{
		startSelf();
	}
}

void SelectRoleAndPet::startSelf(void)
{
	setVisible(true);
	isBackGround = false;
	mAnimationManager->runAnimationsForSequenceNamed("renwuchuxian2");
}

void SelectRoleAndPet::setLoadingLayer(cocos2d::CCLayer * _layer)
{
	loadingLayer = _layer;

	if (loadingLayer == NULL)
	{
		setVisible(true);
	}
}

void SelectRoleAndPet::setForwardLayer(cocos2d::CCLayer * _layer, int _layerType)
{
	forwardLayer = _layer;
	forwardType = _layerType;
	if (forwardType == LAYER_ID_SHOP)
	{
		((Shop *)forwardLayer)->setVisible(false);
	}
}

void SelectRoleAndPet::setBackInformation(cocos2d::CCLayer * _layer, int _layerType)
{
	backLayer = _layer;
	backLayerType = _layerType;

	if (backLayerType != 0)
	{
		getChildByTag(999)->getChildByTag(88)->setVisible(false);
	}
	
}

void SelectRoleAndPet::keyBackClicked(void)	
{
	onMenuItemBackClicked(NULL);
}

void SelectRoleAndPet::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

SEL_MenuHandler SelectRoleAndPet::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBack", SelectRoleAndPet::onMenuItemBackClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnPlay", SelectRoleAndPet::onMenuItemPlayClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnPlus", SelectRoleAndPet::onMenuItemPlusClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnShop", SelectRoleAndPet::onMenuItemShopClicked);

	// 解锁信息
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnUnlock1", SelectRoleAndPet::menuAbout1Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnUnlock2", SelectRoleAndPet::menuAbout2Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnUnlock3", SelectRoleAndPet::menuAbout3Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnUnlock4", SelectRoleAndPet::menuAbout4Callback);

	// 招募
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnRecruit1", SelectRoleAndPet::menuGet1Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnRecruit2", SelectRoleAndPet::menuGet2Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnRecruit3", SelectRoleAndPet::menuGet3Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnRecruit4", SelectRoleAndPet::menuGet4Callback);

	// 上阵
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBattle1", SelectRoleAndPet::menuSelect1Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBattle2", SelectRoleAndPet::menuSelect2Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBattle3", SelectRoleAndPet::menuSelect3Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBattle4", SelectRoleAndPet::menuSelect4Callback);

	// 购买
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBuy1", SelectRoleAndPet::menuBuy1Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBuy2", SelectRoleAndPet::menuBuy2Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBuy3", SelectRoleAndPet::menuBuy3Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBuy4", SelectRoleAndPet::menuBuy4Callback);

	return NULL;
}

SEL_CCControlHandler SelectRoleAndPet::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool SelectRoleAndPet::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void SelectRoleAndPet::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
#ifndef										GOLDEN_MINER_2_BUY_INGOT	
	getChildByTag(999)->getChildByTag(89)->setVisible(false);
#endif
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(SelectRoleAndPet::doAnimationCompleted));
	CC_SAFE_RETAIN(mAnimationManager);
}

void SelectRoleAndPet::setBackGround(bool _b)
{
	if (_b == true)
	{
		if (greyLayer == NULL)
		{
			greyLayer = CCLayerColor::create(myGrey4);
		}

		Global::getInstance()->s->addLayerToRunningScene(greyLayer);
	}
	else
	{
		if (greyLayer != NULL)
		{
			Global::getInstance()->s->removeLayerToRunningScene(greyLayer);
			greyLayer = NULL;
		}
	}
	isBackGround = _b;
}


void SelectRoleAndPet::setIsPet(bool _b)
{
	isPet = _b;
	((CCMenu *)getChildByTag(999))->setTouchEnabled(!isPet);
}


void SelectRoleAndPet::onMenuItemShopClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

}

void SelectRoleAndPet::onMenuItemBackClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->setLastRoleSelect(Global::getInstance()->getSelectRoleId());
	if (forwardType == LAYER_ID_SHOP)
	{
		((Shop *)forwardLayer)->setVisible(true);
	}
	((Shop *)forwardLayer)->reBack(LAYER_ID_ROLE, false);
	Global::getInstance()->s->removeLayerToRunningScene(this);
	//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getShopLayer(NULL, backLayer, backLayerType));// 在商城页面返回会出现空指针，因为直接换scene的原因
	
	//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getShopLayer(NULL, NULL, 0));
	//Global::getInstance()->s->removeLayerToRunningScene(this);
}

void SelectRoleAndPet::onMenuItemPlayClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	Player::getInstance()->setLastRoleSelect(Global::getInstance()->getSelectRoleId());

	if (Global::getInstance()->getChallengeLevel() != 0)
	{
		//开始游戏没有loading的页面
		Global::getInstance()->s->replaceScene(Global::getInstance()->s->getChallengeLayer(Global::getInstance()->getNextChallengeGateId(), Global::getInstance()->getSelectRoleId(), NULL));
	}
	else
	{
		Player::getInstance()->setLastMapId(Global::getInstance()->getMapIdByGateId(Global::getInstance()->getSelectGateId()));
		// 播放漫画
		Global::getInstance()->setCartoonId(0);
		Global::getInstance()->setCartoonId(Global::getInstance()->getSelectGateId());

		// 开始游戏loading的页面
		if (Global::getInstance()->getCartoonId() != 0&& !Player::getInstance()->getCarttonIsPlay(Global::getInstance()->getCartoonId()))
		{
			if (Global::getInstance()->getCartoonId() == CARTOON_BAOXIANGGUO)
			{
				Global::getInstance()->s->replaceScene(Global::getInstance()->s->getCartoonLayer(CARTOON_START, NULL));
			}
			else
			{
				Global::getInstance()->s->replaceScene(Global::getInstance()->s->getCartoonLayer(Global::getInstance()->getCartoonId(), NULL));
			}
		}
		else
		{
			Global::getInstance()->s->replaceScene(Global::getInstance()->s->getGameLayer(Global::getInstance()->getSelectGateId(), Global::getInstance()->getSelectRoleId(), NULL));
		}

	}
}

void SelectRoleAndPet::onMenuItemPlusClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
}

void SelectRoleAndPet::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	if (isBackGround)
	{
		return;
	}

	//此方法是cocos2d-x的标准操作，取touch集合第一个touch，将其位置转成opengl坐标，没办法，这些坐标太乱了，touch默认坐标是屏幕坐标，左上角为远点，cocos默认坐标是opengl坐标，左下角是原点。
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	m_touchBeginPos = touch->getLocation ();
	m_touchBeginPos = CCDirector::sharedDirector()->convertToGL( m_touchBeginPos );

	if (isPetVisiable && petLayer->isVisible())
	{
		petTouchIndex = -1;
		if (isPet)
		{
			for (int i = 2; i < 5; i++)
			{
				CCRect * myButton = new CCRect(
					petLayer->getChildByTag(1)->getChildByTag(i)->getPositionX() - petLayer->getChildByTag(1)->getChildByTag(i)->getContentSize().width/2,
					petLayer->getChildByTag(1)->getChildByTag(i)->getPositionY() - petLayer->getChildByTag(1)->getChildByTag(i)->getContentSize().height/2,
					petLayer->getChildByTag(1)->getChildByTag(i)->getContentSize().width,
					petLayer->getChildByTag(1)->getChildByTag(i)->getContentSize().height
					);
				if (Global::getInstance()->isInRect(myButton, m_touchBeginPos.x, 480 - m_touchBeginPos.y))
				{
					petTouchIndex = i;
				}
			}
		}
		else
		{
			CCRect * myButton = new CCRect(
				petLayer->getChildByTag(1)->getChildByTag(1)->getPositionX() - petLayer->getChildByTag(1)->getChildByTag(1)->getContentSize().width/2,
				petLayer->getChildByTag(1)->getChildByTag(1)->getPositionY() - petLayer->getChildByTag(1)->getChildByTag(1)->getContentSize().height/2,
				petLayer->getChildByTag(1)->getChildByTag(1)->getContentSize().width,
				petLayer->getChildByTag(1)->getChildByTag(1)->getContentSize().height
				);
			if (Global::getInstance()->isInRect(myButton, m_touchBeginPos.x, 480 - m_touchBeginPos.y))
			{
				petTouchIndex = 1;
			}
		}
	}

	isSelectMyButton = false;
	if(myButton != NULL && Global::getInstance()->isInRect(myButton, m_touchBeginPos.x, 480 - m_touchBeginPos.y))
	{
		isSelectMyButton = true;
	}

	m_touchMove = false;
}
void SelectRoleAndPet::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	if (isBackGround)
	{
		return;
	}

	m_touchMove = true;
}
void SelectRoleAndPet::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	if (isBackGround)
	{
		return;
	}

	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	m_touchEndPos = touch->getLocation ();
	m_touchEndPos = CCDirector::sharedDirector()->convertToGL( m_touchEndPos );

	if (isPetVisiable && petLayer->isVisible())
	{
		if (isPet)
		{
			if (petTouchIndex > 1)
			{
				CCRect * myButton = new CCRect(
					petLayer->getChildByTag(1)->getChildByTag(petTouchIndex)->getPositionX() - petLayer->getChildByTag(1)->getChildByTag(petTouchIndex)->getContentSize().width/2,
					petLayer->getChildByTag(1)->getChildByTag(petTouchIndex)->getPositionY() - petLayer->getChildByTag(1)->getChildByTag(petTouchIndex)->getContentSize().height/2,
					petLayer->getChildByTag(1)->getChildByTag(petTouchIndex)->getContentSize().width,
					petLayer->getChildByTag(1)->getChildByTag(petTouchIndex)->getContentSize().height
					);
				if (Global::getInstance()->isInRect(myButton, m_touchBeginPos.x, 480 - m_touchBeginPos.y))
				{
					// 更换对应的选择的宠物
					petLayer->selectOtherPet(petTouchIndex);
					return;
				}
			}

			// 收回
			petLayer->outOrBack(false);
			setIsPet(false);
			return;
		}
		else
		{
			if (petTouchIndex == 1)
			{
				CCRect * myButton = new CCRect(
					petLayer->getChildByTag(1)->getChildByTag(1)->getPositionX() - petLayer->getChildByTag(1)->getChildByTag(1)->getContentSize().width/2,
					petLayer->getChildByTag(1)->getChildByTag(1)->getPositionY() - petLayer->getChildByTag(1)->getChildByTag(1)->getContentSize().height/2,
					petLayer->getChildByTag(1)->getChildByTag(1)->getContentSize().width,
					petLayer->getChildByTag(1)->getChildByTag(1)->getContentSize().height
					);
				if (Global::getInstance()->isInRect(myButton, m_touchBeginPos.x, 480 - m_touchBeginPos.y))
				{
					// 弹出
					if (petLayer->outOrBack(true))
					{
						setIsPet(true);
					}

					return;
				}
			}
		}
	}


	if(m_touchMove)
	{
		//如果move了，那么看手指是否上下滑动超过50像素，这个纠正值得有，否则太灵敏了
		if ((m_touchBeginPos.x - m_touchEndPos.x) > 50)
		{
			((CCSprite *)selectRoleSpritesTips->objectAtIndex((currRoleIndex + 1) % selectRoleSprites->count()))->setVisible(false);
			setCurrRole(true);
		}
		else if ((m_touchEndPos.x - m_touchBeginPos.x) > 50)
		{
			((CCSprite *)selectRoleSpritesTips->objectAtIndex((currRoleIndex + 1) % selectRoleSprites->count()))->setVisible(false);
			setCurrRole(false);
		}
		else
		{
			if(isSelectMyButton)
			{
				if (Global::getInstance()->isInRect(myButton,
					m_touchEndPos.x,
					480 - m_touchEndPos.y))
				{
					PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_ROLE);
					setBackGround(true);
					promptLayer->setForwardLayer(this, LAYER_ID_ROLE);
					Global::getInstance()->s->addLayerToRunningScene(promptLayer);
					promptLayer->roleIntruduceById((currRoleIndex + 1) % selectRoleSprites->count());
				}
			}
		}
	}
	else
	{
		if(isSelectMyButton)
		{
			if (Global::getInstance()->isInRect(myButton,
				m_touchEndPos.x,
				480 - m_touchEndPos.y))
			{
				PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_ROLE);
				setBackGround(true);
				promptLayer->setForwardLayer(this, LAYER_ID_ROLE);
				Global::getInstance()->s->addLayerToRunningScene(promptLayer);
				promptLayer->roleIntruduceById((currRoleIndex + 1) % selectRoleSprites->count());
			}
		}
	}
	m_touchMove = false;
}

void SelectRoleAndPet::setCurrRole(bool _isXiangZuo)
{
	if (_isXiangZuo)
	{
		setNodeBySelectIndex(_isXiangZuo);
		currRoleIndex++;
		currRoleIndex = currRoleIndex % selectRoleSprites->count();
		mAnimationManager->runAnimationsForSequenceNamed("xiangzuo");
		for (int i = 0; i < 4; i++)
		{
			if (i == 2)
			{
				currButtonIndex = 3;
				((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_YUN_MIDDLE);
				((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
				((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
				((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
				((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
				((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
				((CCSprite *)currSelectRolePower->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
				((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_MIDDLE);
				((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_MIDDLE);
				((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_MIDDLE);
				((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_MIDDLE);
			}
			else
			{

				((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_YUN_ASIDE);
				((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
				((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
				((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
				((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
				((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
				((CCSprite *)currSelectRolePower->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
				((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_ASIDE);
				((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_ASIDE);
				((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_ASIDE);
				((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_ASIDE);
			}
		}
	}
	else
	{
		setNodeBySelectIndex(_isXiangZuo);
		currRoleIndex--;
		currRoleIndex = (currRoleIndex + selectRoleSprites->count()) % selectRoleSprites->count();
		mAnimationManager->runAnimationsForSequenceNamed("xiangyou");
		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				currButtonIndex = 1;
				((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_YUN_MIDDLE);
				((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
				((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
				((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
				((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
				((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
				((CCSprite *)currSelectRolePower->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
				((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_MIDDLE);
				((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_MIDDLE);
				((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_MIDDLE);
				((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_MIDDLE);
			}
			else
			{

				((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_YUN_ASIDE);
				((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
				((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
				((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
				((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
				((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
				((CCSprite *)currSelectRolePower->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
				((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_ASIDE);
				((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_ASIDE);
				((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_ASIDE);
				((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_ASIDE);

			}
		}
	}
	((CCSprite *)selectRoleSpritesName->objectAtIndex((currRoleIndex + 1)%selectRoleSpritesName->count()))->setVisible(true);
}

void SelectRoleAndPet::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"rwxiaoshi") == 0)
	{	
		mAnimationManager->runAnimationsForSequenceNamed("daojuchuxian");
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"daojuxiaoshi") == 0)
	{
		mAnimationManager->runAnimationsForSequenceNamed("renwuchuxian2");
		((CCSprite *)selectRoleSpritesName->objectAtIndex((currRoleIndex + 1)%selectRoleSpritesName->count()))->setVisible(true);
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"renwuchuxian2") == 0)
	{
		CCSprite * tmp = ((CCSprite *)currSelectSprites->objectAtIndex(1));
		myButton = new CCRect(getChildByTag(2)->getPositionX() - tmp->getContentSize().width/2
			,getChildByTag(2)->getPositionY() - tmp->getContentSize().height/2
			,tmp->getContentSize().width
			,tmp->getContentSize().height);


		if (Player::getInstance()->getGuideSlipRole())
		{
			SlipGuide * slipGuide = (SlipGuide *)Global::getInstance()->s->getSlipGuideLayer(this, LAYER_ID_ROLE);
			setBackGround(true);
			Global::getInstance()->s->addLayerToRunningScene(slipGuide);
		}

	}
}

void SelectRoleAndPet::reBack(int _type, bool _b)
{
	setBackGround(false);
	// type是值回来前调用界面的类型  这里没必要区分  只是购买才需要处理
	if(_b)
	{	
		coupletAbout->setVisible(false);
		int index = currSelectSprites->indexOfObject(selectRoleSprites->objectAtIndex((currRoleIndex + 1) % selectRoleSprites->count()));

		if(CC_INVALID_INDEX != index)
		{
			((CCSprite *)currSelectGetSelectSprites->objectAtIndex(index))->setVisible(false);
			((CCSprite *)currSelectButtonSelectSprites->objectAtIndex(index))->setVisible(true);
		}

		index = (currRoleIndex + 1) % selectRoleSprites->count();
		CCInteger * p = CCInteger::create(1);
		selectRoleSpritesIsHaving->addObject(p);
		selectRoleSpritesIsHaving->exchangeObjectAtIndex(selectRoleSpritesIsHaving->count()-1, index);
		selectRoleSpritesIsHaving->removeLastObject();

		char _s[32];
		sprintf(_s, "%d",Player::getInstance()->getPropNum(PROP_TYPE_INGOT));
		removeChild(ingotNum);
		ingotNum = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
		CC_SAFE_RETAIN(ingotNum);
		addChild(ingotNum, 998);
	}
}

void SelectRoleAndPet::initSprites(void)
{
	// 人物界面
	// 葫芦娃
	introducehuluwa = CCSprite::create("xuanren/wenhao2.png");
	addChild(introducehuluwa);
	introducehuluwa->retain();

	selectRoleSpritesIntroduce->addObject(CCSprite::create("xuanren/baohulu.png"));
	if (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_HULUWA))
	{
		selectRoleSpritesName->addObject(CCSprite::create("xuanren/fuluwa.png"));
		selectRoleSpritesIsHaving->addObject(CCInteger::create(1));
		selectRoleSpritesIsOpen->addObject(CCInteger::create(1));
		selectRoleSprites->addObject(CCSprite::create("xuanren/fulu1.png"));
	}
	else
	{
		((CCSprite *)selectRoleSpritesIntroduce->lastObject())->setVisible(false);
		selectRoleSpritesName->addObject(CCSprite::create("xuanren/wenhao1.png"));
		selectRoleSpritesIsHaving->addObject(CCInteger::create(0));
		if (Player::getInstance()->getRoleOpenStatusByRoleId(ROLE_TYPE_HULUWA))
		{
			selectRoleSpritesIsOpen->addObject(CCInteger::create(1));
			selectRoleSprites->addObject(CCSprite::create("xuanren/fulu2.png"));
		}
		else
		{
			selectRoleSpritesIsOpen->addObject(CCInteger::create(0));
			selectRoleSprites->addObject(CCSprite::create("xuanren/fulu2.png"));
		}
	}
	//selectRoleSpritesName->addObject(CCSprite::create("xuanren/wenhao1.png"));
	((CCSprite *)selectRoleSpritesName->lastObject())->setPosition(ccp(405, 425));
	((CCSprite *)selectRoleSpritesName->lastObject())->setVisible(false);
	addChild((CCSprite *)selectRoleSpritesName->lastObject(), 998);

	selectRoleSpritesTips->addObject(CCSprite::create("duihuakuang/27.png"));
	((CCSprite *)selectRoleSpritesTips->lastObject())->setPosition(ccp(305, 375));
	((CCSprite *)selectRoleSpritesTips->lastObject())->setScale(false);
	addChild((CCSprite *)selectRoleSpritesTips->lastObject(), 998);
	// 还要初始化是否拥有对象(假的现在)是否已经开启对象
	////selectRoleSpritesSpeed->addObject(CCInteger::create(1));
	////selectRoleSpritesPower->addObject(CCInteger::create(1));
	//selectRoleSpritesIntroduce->addObject(CCSprite::create("xuanren/baohulu.png"));
	//((CCSprite *)selectRoleSpritesIntroduce->lastObject())->setVisible(false);

	// 唐僧
	selectRoleSpritesIsHaving->addObject(CCInteger::create(1));
	selectRoleSpritesIsOpen->addObject(CCInteger::create(1));
	selectRoleSprites->addObject(CCSprite::create("xuanren/tangseng1.png"));
	selectRoleSpritesName->addObject(CCSprite::create("xuanren/tangseng.png"));
	((CCSprite *)selectRoleSpritesName->lastObject())->setPosition(ccp(405, 425));
	((CCSprite *)selectRoleSpritesName->lastObject())->setVisible(false);
	addChild((CCSprite *)selectRoleSpritesName->lastObject(), 998);

	selectRoleSpritesTips->addObject(CCSprite::create("duihuakuang/23.png"));
	((CCSprite *)selectRoleSpritesTips->lastObject())->setPosition(ccp(305, 375));
	((CCSprite *)selectRoleSpritesTips->lastObject())->setVisible(false);
	addChild((CCSprite *)selectRoleSpritesTips->lastObject(), 998);
	// 还要初始化是否拥有对象(假的现在)是否已经开启对象
	//selectRoleSpritesSpeed->addObject(CCInteger::create(1));
	//selectRoleSpritesPower->addObject(CCInteger::create(1));
	selectRoleSpritesIntroduce->addObject(CCSprite::create("xuanren/dscj.png"));

	// 八戒
	if (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_ZHUBAJIE))
	{
		selectRoleSpritesIsHaving->addObject(CCInteger::create(1));
		selectRoleSpritesIsOpen->addObject(CCInteger::create(1));
		selectRoleSprites->addObject(CCSprite::create("xuanren/bajie1.png"));
	}
	else
	{
		selectRoleSpritesIsHaving->addObject(CCInteger::create(0));
		if (Player::getInstance()->getRoleOpenStatusByRoleId(ROLE_TYPE_ZHUBAJIE))
		{
			selectRoleSpritesIsOpen->addObject(CCInteger::create(1));
			selectRoleSprites->addObject(CCSprite::create("xuanren/bajie1.png"));
		}
		else
		{
			selectRoleSpritesIsOpen->addObject(CCInteger::create(0));
			selectRoleSprites->addObject(CCSprite::create("xuanren/bajie1.png"));
			//selectRoleSprites->addObject(CCSprite::create("xuanren/bajiehui.png"));
		}
	}
	selectRoleSpritesName->addObject(CCSprite::create("xuanren/bajie.png"));
	((CCSprite *)selectRoleSpritesName->lastObject())->setPosition(ccp(405, 425));
	((CCSprite *)selectRoleSpritesName->lastObject())->setVisible(false);
	addChild((CCSprite *)selectRoleSpritesName->lastObject(), 998);

	selectRoleSpritesTips->addObject(CCSprite::create("duihuakuang/24.png"));
	((CCSprite *)selectRoleSpritesTips->lastObject())->setPosition(ccp(305, 375));
	((CCSprite *)selectRoleSpritesTips->lastObject())->setVisible(false);
	addChild((CCSprite *)selectRoleSpritesTips->lastObject(), 998);
	// 还要初始化是否拥有对象(假的现在)是否已经开启对象
	//selectRoleSpritesSpeed->addObject(CCInteger::create(1));
	//selectRoleSpritesPower->addObject(CCInteger::create(1));
	selectRoleSpritesIntroduce->addObject(CCSprite::create("xuanren/dahailaoz.png"));

	// 沙僧
	if (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_SHAHESHANG))
	{
		selectRoleSpritesIsHaving->addObject(CCInteger::create(1));
		selectRoleSpritesIsOpen->addObject(CCInteger::create(1));
		selectRoleSprites->addObject(CCSprite::create("xuanren/shaseng1.png"));
	}
	else
	{
		selectRoleSpritesIsHaving->addObject(CCInteger::create(0));
		if (Player::getInstance()->getRoleOpenStatusByRoleId(ROLE_TYPE_SHAHESHANG))
		{
			selectRoleSpritesIsOpen->addObject(CCInteger::create(1));
			selectRoleSprites->addObject(CCSprite::create("xuanren/shaseng1.png"));
		}
		else
		{
			selectRoleSpritesIsOpen->addObject(CCInteger::create(0));
			selectRoleSprites->addObject(CCSprite::create("xuanren/shaseng1.png"));
			//selectRoleSprites->addObject(CCSprite::create("xuanren/shasenghui.png"));
		}
	}
	selectRoleSpritesName->addObject(CCSprite::create("xuanren/shaseng.png"));
	((CCSprite *)selectRoleSpritesName->lastObject())->setPosition(ccp(405, 425));
	((CCSprite *)selectRoleSpritesName->lastObject())->setVisible(false);
	addChild((CCSprite *)selectRoleSpritesName->lastObject(), 998);

	selectRoleSpritesTips->addObject(CCSprite::create("duihuakuang/36.png"));
	((CCSprite *)selectRoleSpritesTips->lastObject())->setPosition(ccp(305, 375));
	((CCSprite *)selectRoleSpritesTips->lastObject())->setVisible(false);
	addChild((CCSprite *)selectRoleSpritesTips->lastObject(), 998);
	// 还要初始化是否拥有对象(假的现在)是否已经开启对象
	//selectRoleSpritesSpeed->addObject(CCInteger::create(1));
	//selectRoleSpritesPower->addObject(CCInteger::create(1));
	selectRoleSpritesIntroduce->addObject(CCSprite::create("xuanren/jjdj.png"));

	// 悟空
	if (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_SUNWUKONG))
	{
		selectRoleSpritesIsHaving->addObject(CCInteger::create(1));
		selectRoleSpritesIsOpen->addObject(CCInteger::create(1));
		selectRoleSprites->addObject(CCSprite::create("xuanren/wukong1.png"));
	}
	else
	{
		selectRoleSpritesIsHaving->addObject(CCInteger::create(0));
		if (Player::getInstance()->getRoleOpenStatusByRoleId(ROLE_TYPE_SUNWUKONG))
		{
			selectRoleSpritesIsOpen->addObject(CCInteger::create(1));
			selectRoleSprites->addObject(CCSprite::create("xuanren/wukong1.png"));
		}
		else
		{
			selectRoleSpritesIsOpen->addObject(CCInteger::create(0));
			selectRoleSprites->addObject(CCSprite::create("xuanren/wukong1.png"));
			//selectRoleSprites->addObject(CCSprite::create("xuanren/wukonghui.png"));
		}
	}
	selectRoleSpritesName->addObject(CCSprite::create("xuanren/wukong.png"));
	((CCSprite *)selectRoleSpritesName->lastObject())->setPosition(ccp(405, 425));
	((CCSprite *)selectRoleSpritesName->lastObject())->setVisible(false);
	addChild((CCSprite *)selectRoleSpritesName->lastObject(), 998);

	selectRoleSpritesTips->addObject(CCSprite::create("duihuakuang/25.png"));
	((CCSprite *)selectRoleSpritesTips->lastObject())->setPosition(ccp(305, 375));
	((CCSprite *)selectRoleSpritesTips->lastObject())->setVisible(false);
	addChild((CCSprite *)selectRoleSpritesTips->lastObject(), 998);
	// 还要初始化是否拥有对象(假的现在)是否已经开启对象
	//selectRoleSpritesSpeed->addObject(CCInteger::create(1));
	//selectRoleSpritesPower->addObject(CCInteger::create(1));
	selectRoleSpritesIntroduce->addObject(CCSprite::create("xuanren/sjjz.png"));


	// 龙女
	if (Player::getInstance()->getRoleHavingStatusByRoleId(ROLE_TYPE_XIAOLONGNV))
	{
		selectRoleSpritesIsHaving->addObject(CCInteger::create(1));
		selectRoleSpritesIsOpen->addObject(CCInteger::create(1));
		selectRoleSprites->addObject(CCSprite::create("xuanren/longnv1.png"));
	}
	else
	{
		selectRoleSpritesIsHaving->addObject(CCInteger::create(0));
		if (Player::getInstance()->getRoleOpenStatusByRoleId(ROLE_TYPE_XIAOLONGNV))
		{
			selectRoleSpritesIsOpen->addObject(CCInteger::create(1));
			selectRoleSprites->addObject(CCSprite::create("xuanren/longnv1.png"));
		}
		else
		{
			selectRoleSpritesIsOpen->addObject(CCInteger::create(0));
			selectRoleSprites->addObject(CCSprite::create("xuanren/longnv1.png"));
			//selectRoleSprites->addObject(CCSprite::create("xuanren/longnvhui.png"));
		}
	}
	selectRoleSpritesName->addObject(CCSprite::create("xuanren/longnv.png"));
	((CCSprite *)selectRoleSpritesName->lastObject())->setPosition(ccp(405, 425));
	((CCSprite *)selectRoleSpritesName->lastObject())->setVisible(false);
	addChild((CCSprite *)selectRoleSpritesName->lastObject(), 998);

	selectRoleSpritesTips->addObject(CCSprite::create("duihuakuang/26.png"));
	((CCSprite *)selectRoleSpritesTips->lastObject())->setPosition(ccp(305, 375));
	((CCSprite *)selectRoleSpritesTips->lastObject())->setVisible(false);
	addChild((CCSprite *)selectRoleSpritesTips->lastObject(), 998);
	// 还要初始化是否拥有对象(假的现在)是否已经开启对象
	//selectRoleSpritesSpeed->addObject(CCInteger::create(1));
	//selectRoleSpritesPower->addObject(CCInteger::create(1));
	selectRoleSpritesIntroduce->addObject(CCSprite::create("xuanren/hxsh.png"));


	// 添加任务点点
	for (int i = 0; i < selectRoleSprites->count(); i++)
	{
		pointRoleSprites->addObject(CCSprite::create("xuandaguan/dian2.png"));
		((CCSprite *)pointRoleSprites->lastObject())->setPosition(ccp(400 - selectRoleSprites->count()*SelectRoleAndPet_POINT_X/2 + i*SelectRoleAndPet_POINT_X + SelectRoleAndPet_POINT_X/2, SelectRoleAndPet_POINT_Y));
		addChild((CCSprite *)pointRoleSprites->lastObject());
	}

	// 亮点点
	pointIndexSprite = CCSprite::create("xuandaguan/dian1.png");
	pointIndexSprite->retain();
	addChild(pointIndexSprite,998);

	currSelectButtonSelectSprites->addObject(getChildByTag(999)->getChildByTag(41));
	currSelectButtonSelectSprites->addObject(getChildByTag(999)->getChildByTag(42));
	currSelectButtonSelectSprites->addObject(getChildByTag(999)->getChildByTag(43));
	currSelectButtonSelectSprites->addObject(getChildByTag(999)->getChildByTag(44));

	currSelectButtonBuySprites->addObject(getChildByTag(999)->getChildByTag(21));
	currSelectButtonBuySprites->addObject(getChildByTag(999)->getChildByTag(22));
	currSelectButtonBuySprites->addObject(getChildByTag(999)->getChildByTag(23));
	currSelectButtonBuySprites->addObject(getChildByTag(999)->getChildByTag(24));

	currSelectAboutSelectSprites->addObject(getChildByTag(999)->getChildByTag(11));
	currSelectAboutSelectSprites->addObject(getChildByTag(999)->getChildByTag(12));
	currSelectAboutSelectSprites->addObject(getChildByTag(999)->getChildByTag(13));
	currSelectAboutSelectSprites->addObject(getChildByTag(999)->getChildByTag(14));

	currSelectGetSelectSprites->addObject(getChildByTag(999)->getChildByTag(31));
	currSelectGetSelectSprites->addObject(getChildByTag(999)->getChildByTag(32));
	currSelectGetSelectSprites->addObject(getChildByTag(999)->getChildByTag(33));
	currSelectGetSelectSprites->addObject(getChildByTag(999)->getChildByTag(34));

	for (int i = 0; i< 4; i++)
	{
		currSelectYunSprites->addObject(CCSprite::create("xuanren/yun.png"));
		addChild((CCSprite *)currSelectYunSprites->objectAtIndex(i));
		currSelectFrameSprites->addObject(CCSprite::create("xuanren/jieshao.png"));
		addChild((CCSprite *)currSelectFrameSprites->objectAtIndex(i));
		currSelectRoleSpeedBackground->addObject(CCSprite::create("xuanren/hui.png"));
		addChild((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i));
		currSelectRolePowerBackground->addObject(CCSprite::create("xuanren/hui.png"));
		addChild((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i));
		currSelectRoleSpeed->addObject(CCSprite::create("xuanren/lan.png"));
		addChild((CCSprite *)currSelectRoleSpeed->objectAtIndex(i));
		currSelectRolePower->addObject(CCSprite::create("xuanren/hong.png"));
		addChild((CCSprite *)currSelectRolePower->objectAtIndex(i));
		currSelectRoleSpeedInteger->addObject(CCInteger::create(Global::getInstance()->getRoleSwapSpeedByRoleId(i)));
		currSelectRolePowerInteger->addObject(CCInteger::create(Global::getInstance()->getRoleSpeedByRoleId(i)));

		currSelectSprites->addObject(selectRoleSprites->objectAtIndex((i + currRoleIndex) % selectRoleSprites->count()));
		currSelectSpritesIntroduce->addObject(selectRoleSpritesIntroduce->objectAtIndex((i + currRoleIndex) % selectRoleSprites->count()));
		getChildByTag(i+1)->addChild((CCSprite *)currSelectSprites->objectAtIndex(i));
		addChild((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i));
	}
}

void SelectRoleAndPet::setNodeBySelectIndex(bool _isXiangZuo)
{
		for (int i = 4; i > 0; i--)
		{// 移除node中的ccSprite
			getChildByTag(i)->removeChild((CCSprite *)currSelectSprites->lastObject());
			removeChild((CCSprite *)currSelectSpritesIntroduce->lastObject(),true);
			currSelectSprites->removeLastObject();
			currSelectSpritesIntroduce->removeLastObject();
			currSelectRoleSpeedInteger->removeLastObject();
			currSelectRolePowerInteger->removeLastObject();
		}
		introducehuluwaindex = -1;
		introducehuluwa->setVisible(false);
		for (int i = 0; i< 4; i++)
		{
			int tmpIndex = -1;

			// 属性显示相关

			if (_isXiangZuo)
			{
				currSelectSprites->addObject(selectRoleSprites->objectAtIndex((i + currRoleIndex) % selectRoleSprites->count()));
				currSelectSpritesIntroduce->addObject(selectRoleSpritesIntroduce->objectAtIndex((i + currRoleIndex) % selectRoleSprites->count()));
			
				tmpIndex = (i + currRoleIndex) % selectRoleSprites->count();			
			}
			else
			{
				if (i == 3)
				{
					currSelectSprites->addObject(selectRoleSprites->objectAtIndex((selectRoleSprites->count() - 1 + currRoleIndex) % selectRoleSprites->count()));
					currSelectSpritesIntroduce->addObject(selectRoleSpritesIntroduce->objectAtIndex((selectRoleSprites->count() - 1 + currRoleIndex) % selectRoleSprites->count()));
				
					tmpIndex = (selectRoleSprites->count() - 1 + currRoleIndex) % selectRoleSprites->count();	
				}
				else
				{
					currSelectSprites->addObject(selectRoleSprites->objectAtIndex((i + currRoleIndex) % selectRoleSprites->count()));
					currSelectSpritesIntroduce->addObject(selectRoleSpritesIntroduce->objectAtIndex((i + currRoleIndex) % selectRoleSprites->count()));
					
					tmpIndex = (i + currRoleIndex) % selectRoleSprites->count();
				}
			}

			int S = Global::getInstance()->getRoleSpeedByRoleId(tmpIndex);
			int P = Global::getInstance()->getRoleSwapSpeedByRoleId(tmpIndex);
			currSelectRoleSpeedInteger->addObject(CCInteger::create(S));
			currSelectRolePowerInteger->addObject(CCInteger::create(P));
			float W = ((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->getContentSize().width;
			float H = ((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->getContentSize().height;

			
			// 按钮显示相关
			if (((CCInteger *)selectRoleSpritesIsHaving->objectAtIndex((i + currRoleIndex) % selectRoleSprites->count()))->getValue() == 1)
			{
				// 拥有人物
				((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setVisible(true);
				((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setVisible(false);
				((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setVisible(false);
				((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setVisible(false);
			}
			else
			{	// 没有拥有人物
				if(tmpIndex == ROLE_TYPE_HULUWA || tmpIndex == ROLE_TYPE_SUNWUKONG)
				{
					((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setVisible(false);
					((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setVisible(false);
					((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setVisible(false);
					((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setVisible(true);
				}
				else
				{
					if (((CCInteger *)selectRoleSpritesIsOpen->objectAtIndex((i + currRoleIndex) % selectRoleSprites->count()))->getValue() == 1)
					{// 可以购买人物
						((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setVisible(false);
						((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setVisible(true);
						((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setVisible(false);
						((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setVisible(false);
					}
					else
					{// 不能购买人物 只能看介绍
						((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setVisible(false);
						((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setVisible(false);
						((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setVisible(true);
						((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setVisible(false);
					}
				}
			}


			if (tmpIndex == ROLE_TYPE_HULUWA && (((CCInteger *)selectRoleSpritesIsHaving->objectAtIndex(tmpIndex))->getValue() == 0))
			{
				introducehuluwaindex = i;
				introducehuluwa->setVisible(true);
				((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setVisible(false);
				((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setVisible(false);
				((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setVisible(false);
				((CCSprite *)currSelectRolePower->objectAtIndex(i))->setVisible(false);
			}
			else
			{
				((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setVisible(true);
				((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setVisible(true);
				((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setVisible(true);
				((CCSprite *)currSelectRolePower->objectAtIndex(i))->setVisible(true);
				((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setTextureRect(* new CCRect(0, 0, W-16*(5 - S), H));
				((CCSprite *)currSelectRolePower->objectAtIndex(i))->setTextureRect(* new CCRect(0, 0, W-16*(5 - P), H));
			}

			getChildByTag(i+1)->addChild((CCSprite *)currSelectSprites->objectAtIndex(i));
			addChild((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i));
			if (isFristRolePage)
			{
				if (i % 2 == 0)
				{
					((CCSprite *)currSelectSprites->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectRolePower->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setColor(myGrey);
					((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setColor(myGrey);
					((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setColor(myGrey);
					((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setColor(myGrey);
					((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setColor(myGrey);

					if (tmpIndex == ROLE_TYPE_HULUWA)
					{
						introducehuluwa->setColor(myGrey);
					}
				}
				else
				{
					((CCSprite *)currSelectSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectRolePower->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setColor(ccWHITE);
					((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setColor(ccWHITE);
					if (tmpIndex == ROLE_TYPE_HULUWA)
					{
						introducehuluwa->setColor(ccWHITE);
					}
				}
				if (i == 1)
				{
					currButtonIndex = 2;
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setZOrder(SelectRoleAndPet_YUN_MIDDLE);
					((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_YUN_MIDDLE);
					((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
					((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
					((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
					((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
					((CCSprite *)currSelectRolePower->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_MIDDLE);
					((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_MIDDLE);
					((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_MIDDLE);
					((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_MIDDLE);
					((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_MIDDLE);
				}
				else
				{
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setZOrder(SelectRoleAndPet_YUN_ASIDE);
					((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_YUN_ASIDE);
					((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
					((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
					((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
					((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
					((CCSprite *)currSelectRolePower->objectAtIndex(i))->setZOrder(SelectRoleAndPet_FRAME_ASIDE);
					((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_ASIDE);
					((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_ASIDE);
					((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_ASIDE);
					((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setZOrder(SelectRoleAndPet_BUTTON_ASIDE);
				}
			}
			else
			{
				if (i % 2 == 1)
				{
					((CCSprite *)currSelectSprites->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectRolePower->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setColor(myGrey);
					((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setColor(myGrey);
					((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setColor(myGrey);
					((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setColor(myGrey);
					((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setColor(myGrey);
					if (tmpIndex == ROLE_TYPE_HULUWA)
					{
						introducehuluwa->setColor(myGrey);
					}
				}
				else
				{
					((CCSprite *)currSelectSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectRolePower->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setColor(ccWHITE);
					((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setColor(ccWHITE);
					if (tmpIndex == ROLE_TYPE_HULUWA)
					{
						introducehuluwa->setColor(ccWHITE);
					}
				}
			}
		}
		if (isFristRolePage)
		{
			isFristRolePage = false;
		}
		for (int i = 0; i < selectRoleSpritesName->count(); i++)
		{
			((CCSprite *)selectRoleSpritesName->objectAtIndex(i))->setVisible(false);
		}
		getChildByTag(999)->setZOrder(100);
}

// 计费相关添加
void SelectRoleAndPet::onMenuItemPaySuccess(void)
{

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FINISH);

	coupletAbout->setVisible(false);
	int index = currSelectSprites->indexOfObject(selectRoleSprites->objectAtIndex((currRoleIndex + 1) % selectRoleSprites->count()));

	if(CC_INVALID_INDEX != index)
	{
		((CCSprite *)currSelectButtonBuySprites->objectAtIndex(index))->setVisible(false);
		((CCSprite *)currSelectButtonSelectSprites->objectAtIndex(index))->setVisible(true);
	}


	if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_SUNWUKONG)
	{
		Global::getInstance()->getPayAwardByPayId(ROLE_TYPE_SUNWUKONG);
	}
	else if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_HULUWA)
	{
		int S = Global::getInstance()->getRoleSpeedByRoleId((currRoleIndex + 1) % selectRoleSprites->count());
		int P = Global::getInstance()->getRoleSwapSpeedByRoleId((currRoleIndex + 1) % selectRoleSprites->count());
		float W = ((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(0))->getContentSize().width;
		float H = ((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(0))->getContentSize().height;

		Global::getInstance()->getPayAwardByPayId(ROLE_TYPE_HULUWA);

		introducehuluwa->setVisible(false);
		((CCSprite *)selectRoleSpritesIntroduce->objectAtIndex(ROLE_TYPE_HULUWA))->setVisible(true);

		CCSprite * _sp = CCSprite::create("xuanren/fulu1.png");
		selectRoleSprites->addObject(_sp);
		selectRoleSprites->exchangeObjectAtIndex(selectRoleSprites->count()-1, ROLE_TYPE_HULUWA);
		selectRoleSprites->removeLastObject();
		getChildByTag(index+1)->removeChild((CCSprite *)currSelectSprites->objectAtIndex(index));
		currSelectSprites->addObject(_sp);
		currSelectSprites->exchangeObjectAtIndex(currSelectSprites->count()-1, index);
		currSelectSprites->removeLastObject();
		getChildByTag(index+1)->addChild((CCSprite *)currSelectSprites->objectAtIndex(index));

		_sp = CCSprite::create("xuanren/fuluwa.png");
		selectRoleSpritesName->addObject(_sp);
		((CCSprite *)selectRoleSpritesName->lastObject())->setPosition(ccp(405, 425));
		selectRoleSpritesName->exchangeObjectAtIndex(selectRoleSpritesName->count()-1, ROLE_TYPE_HULUWA);
		removeChild((CCSprite *)selectRoleSpritesName->lastObject());
		addChild((CCSprite *)selectRoleSpritesName->objectAtIndex(ROLE_TYPE_HULUWA), 998);
		selectRoleSpritesName->removeLastObject();

		((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(index))->setVisible(true);
		((CCSprite *)currSelectRolePowerBackground->objectAtIndex(index))->setVisible(true);
		((CCSprite *)currSelectRoleSpeed->objectAtIndex(index))->setVisible(true);
		((CCSprite *)currSelectRolePower->objectAtIndex(index))->setVisible(true);
		((CCSprite *)currSelectRoleSpeed->objectAtIndex(index))->setTextureRect(* new CCRect(0, 0, W-16*(5 - S), H));
		((CCSprite *)currSelectRolePower->objectAtIndex(index))->setTextureRect(* new CCRect(0, 0, W-16*(5 - P), H));
	}

	index = (currRoleIndex + 1) % selectRoleSprites->count();
	CCInteger * p = CCInteger::create(1);
	selectRoleSpritesIsHaving->addObject(p);
	selectRoleSpritesIsHaving->exchangeObjectAtIndex(selectRoleSpritesIsHaving->count()-1, index);
	selectRoleSpritesIsHaving->removeLastObject();
	p = CCInteger::create(1);
	selectRoleSpritesIsOpen->addObject(p);
	selectRoleSpritesIsOpen->exchangeObjectAtIndex(selectRoleSpritesIsOpen->count()-1, index);
	selectRoleSpritesIsOpen->removeLastObject();

	char _s[32];
	sprintf(_s, "%d",Player::getInstance()->getPropNum(PROP_TYPE_INGOT));
	removeChild(ingotNum);
	ingotNum = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
	CC_SAFE_RETAIN(ingotNum);
	addChild(ingotNum, 998);

	TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_ROLE);
	_layer->doPromptByType(TEMP_PROMPT_BUY_SUCCESS);
	Global::getInstance()->s->addLayerToRunningScene(_layer);
	//setBackGround(false);
}


// 计费相关添加
void SelectRoleAndPet::onMenuItemPayFailed(void)
{	
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FAILED);
	
	setBackGround(false);
}

void SelectRoleAndPet::menuBuy1Callback(cocos2d::CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	
	if (currButtonIndex == 1)
	{
		// 计费点
#ifdef						GOLDEN_MINER_2_VERSION_PAY

#ifdef						GOLDEN_MINER2_VERSION_PAY_SELF
		setBackGround(true);

		if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_HULUWA)
		{
			CostLayer * _layer = (CostLayer *)Global::getInstance()->s->getCostLayer(this, LAYER_ID_ROLE);
			_layer->costById(PAY_ID_HULUWA, CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
			Global::getInstance()->s->addLayerToRunningScene(_layer);
		}
		else if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_SUNWUKONG)
		{
			CostLayer * _layer = (CostLayer *)Global::getInstance()->s->getCostLayer(this, LAYER_ID_ROLE);
			_layer->costById(PAY_ID_SUNWUKONG, CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
			Global::getInstance()->s->addLayerToRunningScene(_layer);
		}
#else
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
		setBackGround(true);

		if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_HULUWA)
		{
			PayService::getInstance()->pay(PAY_ID_HULUWA, true,  CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
		}
		else if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_SUNWUKONG)
		{
			PayService::getInstance()->pay(PAY_ID_SUNWUKONG, true,  CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
		}

	#endif
#endif
#else
		onMenuItemPaySuccess();
#endif
	}
}

void SelectRoleAndPet::menuBuy2Callback(cocos2d::CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	
	if (currButtonIndex == 2)
	{
		// 计费点
#ifdef						GOLDEN_MINER_2_VERSION_PAY

#ifdef						GOLDEN_MINER2_VERSION_PAY_SELF
		setBackGround(true);

		if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_HULUWA)
		{
			CostLayer * _layer = (CostLayer *)Global::getInstance()->s->getCostLayer(this, LAYER_ID_ROLE);
			_layer->costById(PAY_ID_HULUWA, CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
			Global::getInstance()->s->addLayerToRunningScene(_layer);
		}
		else if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_SUNWUKONG)
		{
			CostLayer * _layer = (CostLayer *)Global::getInstance()->s->getCostLayer(this, LAYER_ID_ROLE);
			_layer->costById(PAY_ID_SUNWUKONG, CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
			Global::getInstance()->s->addLayerToRunningScene(_layer);
		}
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
		setBackGround(true);

		if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_HULUWA)
		{
			PayService::getInstance()->pay(PAY_ID_HULUWA, true,  CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
		}
		else if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_SUNWUKONG)
		{
			PayService::getInstance()->pay(PAY_ID_SUNWUKONG, true,  CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
		}

#endif
#endif
#else
		onMenuItemPaySuccess();
#endif
	}

}

void SelectRoleAndPet::menuBuy3Callback(cocos2d::CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	
	if (currButtonIndex == 3)
	{
		// 计费点
#ifdef						GOLDEN_MINER_2_VERSION_PAY

#ifdef						GOLDEN_MINER2_VERSION_PAY_SELF
		setBackGround(true);

		if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_HULUWA)
		{
			CostLayer * _layer = (CostLayer *)Global::getInstance()->s->getCostLayer(this, LAYER_ID_ROLE);
			_layer->costById(PAY_ID_HULUWA, CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
			Global::getInstance()->s->addLayerToRunningScene(_layer);
		}
		else if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_SUNWUKONG)
		{
			CostLayer * _layer = (CostLayer *)Global::getInstance()->s->getCostLayer(this, LAYER_ID_ROLE);
			_layer->costById(PAY_ID_SUNWUKONG, CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
			Global::getInstance()->s->addLayerToRunningScene(_layer);
		}
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
		setBackGround(true);

		if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_HULUWA)
		{
			PayService::getInstance()->pay(PAY_ID_HULUWA, true,  CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
		}
		else if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_SUNWUKONG)
		{
			PayService::getInstance()->pay(PAY_ID_SUNWUKONG, true,  CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
		}

#endif
#endif
#else
		onMenuItemPaySuccess();
#endif
	}

}

void SelectRoleAndPet::menuBuy4Callback(cocos2d::CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	
	if (currButtonIndex == 4)
	{
		// 计费点
#ifdef						GOLDEN_MINER_2_VERSION_PAY

#ifdef						GOLDEN_MINER2_VERSION_PAY_SELF
		setBackGround(true);

		if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_HULUWA)
		{
			CostLayer * _layer = (CostLayer *)Global::getInstance()->s->getCostLayer(this, LAYER_ID_ROLE);
			_layer->costById(PAY_ID_HULUWA, CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
			Global::getInstance()->s->addLayerToRunningScene(_layer);
		}
		else if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_SUNWUKONG)
		{
			CostLayer * _layer = (CostLayer *)Global::getInstance()->s->getCostLayer(this, LAYER_ID_ROLE);
			_layer->costById(PAY_ID_SUNWUKONG, CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
			Global::getInstance()->s->addLayerToRunningScene(_layer);
		}
#else
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
		setBackGround(true);

		if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_HULUWA)
		{
			PayService::getInstance()->pay(PAY_ID_HULUWA, true,  CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
		}
		else if ((currRoleIndex + 1) % selectRoleSprites->count() == ROLE_TYPE_SUNWUKONG)
		{
			PayService::getInstance()->pay(PAY_ID_SUNWUKONG, true,  CCCallFunc::create(this,callfunc_selector(SelectRoleAndPet::onMenuItemPaySuccess)), CCCallFunc::create(this, callfunc_selector(SelectRoleAndPet::onMenuItemPayFailed)));
		}

#endif
#endif
#else
		onMenuItemPaySuccess();
#endif
	}

}

void SelectRoleAndPet::menuSelect1Callback(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (currButtonIndex == 1)
	{
		int _tmpIndex = currSelectSprites->indexOfObject(selectRoleSprites->objectAtIndex(Global::getInstance()->getSelectRoleId()));
		if (_tmpIndex != CC_INVALID_INDEX)
		{
			((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(_tmpIndex))->setVisible(true);
		}
		Global::getInstance()->setSelectRoleId((currRoleIndex + 1) % selectRoleSprites->count());


		CCSequence * sequence;
		sequence = CCSequence::create(CCFadeIn::create(.3f),CCFadeTo::create(1,255*1),CCFadeOut::create(.3f),NULL);
		((CCSprite *)selectRoleSpritesTips->objectAtIndex((currRoleIndex + 1) % selectRoleSprites->count()))->setVisible(true);
		((CCSprite *)selectRoleSpritesTips->objectAtIndex((currRoleIndex + 1) % selectRoleSprites->count()))->runAction(sequence);
	}
}

void SelectRoleAndPet::menuSelect2Callback(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (currButtonIndex == 2)
	{
		int _tmpIndex = currSelectSprites->indexOfObject(selectRoleSprites->objectAtIndex(Global::getInstance()->getSelectRoleId()));
		if (_tmpIndex != CC_INVALID_INDEX)
		{
			((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(_tmpIndex))->setVisible(true);
		}
		Global::getInstance()->setSelectRoleId((currRoleIndex + 1) % selectRoleSprites->count());


		CCSequence * sequence;
		sequence = CCSequence::create(CCFadeIn::create(.3f),CCFadeTo::create(1,255*1),CCFadeOut::create(.3f),NULL);
		((CCSprite *)selectRoleSpritesTips->objectAtIndex((currRoleIndex + 1) % selectRoleSprites->count()))->setVisible(true);
		((CCSprite *)selectRoleSpritesTips->objectAtIndex((currRoleIndex + 1) % selectRoleSprites->count()))->runAction(sequence);
	}
}

void SelectRoleAndPet::menuSelect3Callback(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (currButtonIndex == 3)
	{
		int _tmpIndex = currSelectSprites->indexOfObject(selectRoleSprites->objectAtIndex(Global::getInstance()->getSelectRoleId()));
		if (_tmpIndex != CC_INVALID_INDEX)
		{
			((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(_tmpIndex))->setVisible(true);
		}
		Global::getInstance()->setSelectRoleId((currRoleIndex + 1) % selectRoleSprites->count());


		CCSequence * sequence;
		sequence = CCSequence::create(CCFadeIn::create(.3f),CCFadeTo::create(1,255*1),CCFadeOut::create(.3f),NULL);
		((CCSprite *)selectRoleSpritesTips->objectAtIndex((currRoleIndex + 1) % selectRoleSprites->count()))->setVisible(true);
		((CCSprite *)selectRoleSpritesTips->objectAtIndex((currRoleIndex + 1) % selectRoleSprites->count()))->runAction(sequence);
	}
}

void SelectRoleAndPet::menuSelect4Callback(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (currButtonIndex == 4)
	{
		int _tmpIndex = currSelectSprites->indexOfObject(selectRoleSprites->objectAtIndex(Global::getInstance()->getSelectRoleId()));
		if (_tmpIndex != CC_INVALID_INDEX)
		{
			((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(_tmpIndex))->setVisible(true);
		}
		Global::getInstance()->setSelectRoleId((currRoleIndex + 1) % selectRoleSprites->count());


		CCSequence * sequence;
		sequence = CCSequence::create(CCFadeIn::create(.3f),CCFadeTo::create(1,255*1),CCFadeOut::create(.3f),NULL);
		((CCSprite *)selectRoleSpritesTips->objectAtIndex((currRoleIndex + 1) % selectRoleSprites->count()))->setVisible(true);
		((CCSprite *)selectRoleSpritesTips->objectAtIndex((currRoleIndex + 1) % selectRoleSprites->count()))->runAction(sequence);
	}
}

void SelectRoleAndPet::menuGet1Callback(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (currButtonIndex == 1)
	{
		// 购买人物
		RoleInformation * information = (RoleInformation *)Global::getInstance()->s->getRoleInformation(this);
		setBackGround(true);
		Global::getInstance()->s->addLayerToRunningScene(information);
		information->getRoleGetInfromationByRoleId((currRoleIndex + 1) % selectRoleSprites->count());
	}
}

void SelectRoleAndPet::menuGet2Callback(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (currButtonIndex == 2)
	{
		// 购买人物
		RoleInformation * information = (RoleInformation *)Global::getInstance()->s->getRoleInformation(this);
		setBackGround(true);
		Global::getInstance()->s->addLayerToRunningScene(information);
		information->getRoleGetInfromationByRoleId((currRoleIndex + 1) % selectRoleSprites->count());
	}
}

void SelectRoleAndPet::menuGet3Callback(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (currButtonIndex == 3)
	{
		// 购买人物
		RoleInformation * information = (RoleInformation *)Global::getInstance()->s->getRoleInformation(this);
		setBackGround(true);
		Global::getInstance()->s->addLayerToRunningScene(information);
		information->getRoleGetInfromationByRoleId((currRoleIndex + 1) % selectRoleSprites->count());
	}
}

void SelectRoleAndPet::menuGet4Callback(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (currButtonIndex == 4)
	{
		// 购买人物
		RoleInformation * information = (RoleInformation *)Global::getInstance()->s->getRoleInformation(this);
		setBackGround(true);
		Global::getInstance()->s->addLayerToRunningScene(information);
		information->getRoleGetInfromationByRoleId((currRoleIndex + 1) % selectRoleSprites->count());
	}
}

void SelectRoleAndPet::menuAbout1Callback(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (currButtonIndex == 1)
	{
		// 介绍
		RoleInformation * information = (RoleInformation *)Global::getInstance()->s->getRoleInformation(this);
		setBackGround(true);
		Global::getInstance()->s->addLayerToRunningScene(information);
		information->getRoleAboutInfromationByRoleId((currRoleIndex + 1) % selectRoleSprites->count());
	}
}

void SelectRoleAndPet::menuAbout2Callback(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (currButtonIndex == 2)
	{
		// 介绍
		RoleInformation * information = (RoleInformation *)Global::getInstance()->s->getRoleInformation(this);
		setBackGround(true);
		Global::getInstance()->s->addLayerToRunningScene(information);
		information->getRoleAboutInfromationByRoleId((currRoleIndex + 1) % selectRoleSprites->count());
	}
}

void SelectRoleAndPet::menuAbout3Callback(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (currButtonIndex == 3)
	{
		// 介绍
		RoleInformation * information = (RoleInformation *)Global::getInstance()->s->getRoleInformation(this);
		setBackGround(true);
		Global::getInstance()->s->addLayerToRunningScene(information);
		information->getRoleAboutInfromationByRoleId((currRoleIndex + 1) % selectRoleSprites->count());
	}
}

void SelectRoleAndPet::menuAbout4Callback(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (currButtonIndex == 4)
	{
		// 介绍
		RoleInformation * information = (RoleInformation *)Global::getInstance()->s->getRoleInformation(this);
		setBackGround(true);
		Global::getInstance()->s->addLayerToRunningScene(information);
		information->getRoleAboutInfromationByRoleId((currRoleIndex + 1) % selectRoleSprites->count());
	}
}

void SelectRoleAndPet::doAction(float _f)
{

	//introducehuluwa->setVisible(false);
		for (int i = 0; i < 4; i++)
		{
			double _positionX = ((CCNode *)getChildByTag(i+1))->getPositionX();
			double _positionY = ((CCNode *)getChildByTag(i+1))->getPositionY();

			int S = ((CCInteger *)currSelectRoleSpeedInteger->objectAtIndex(i))->getValue();
			int P = ((CCInteger *)currSelectRolePowerInteger->objectAtIndex(i))->getValue();
			float W = ((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->getContentSize().width;


			double _scale =  ((CCNode *)getChildByTag(i+1))->getScale();
			((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setPosition(ccp(_positionX+7*_scale, _positionY-124*_scale));
			((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setPosition(ccp(_positionX+237*_scale, _positionY-111*_scale));
			((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setPosition(ccp(_positionX+1*_scale, _positionY-139*_scale));
			((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setPosition(ccp(_positionX+1*_scale, _positionY-139*_scale));
			((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setPosition(ccp(_positionX+1*_scale, _positionY-139*_scale));
			((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setPosition(ccp(_positionX+1*_scale, _positionY-139*_scale));
			((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setPosition(ccp(_positionX+233.5*_scale, _positionY-137.5*_scale));
			((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setPosition(ccp(_positionX+226*_scale, _positionY-87.5*_scale));
			((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setPosition(ccp(_positionX+(226 - W/2 + 8*S)*_scale, _positionY-87.5*_scale));
			((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setPosition(ccp(_positionX+233.5*_scale, _positionY-112.5*_scale));
			((CCSprite *)currSelectRolePower->objectAtIndex(i))->setPosition(ccp(_positionX+(233.5 - W/2 + 8*P)*_scale, _positionY-112.5*_scale));


			if (i == introducehuluwaindex)
			{
				//introducehuluwa->setVisible(true);
				introducehuluwa->setZOrder(((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->getZOrder());
				introducehuluwa->setPosition(ccp(_positionX+226*_scale, _positionY-112.5*_scale));
				introducehuluwa->setScale(_scale);
			}


			((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setScale(_scale);
			((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setScale(_scale);
			((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setScale(_scale);
			((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setScale(_scale);
			((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setScale(_scale);
			((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setScale(_scale);
			((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setScale(_scale);
			((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setScale(_scale);
			((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setScale(_scale);
			((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setScale(_scale);
			((CCSprite *)currSelectRolePower->objectAtIndex(i))->setScale(_scale);
		}
		int _tmpIndex = currSelectSprites->indexOfObject(selectRoleSprites->objectAtIndex(Global::getInstance()->getSelectRoleId()));
		if (_tmpIndex != CC_INVALID_INDEX)
		{
			((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(_tmpIndex))->setVisible(false);
		}
		if (0 == ((CCInteger *)selectRoleSpritesIsOpen->objectAtIndex((currRoleIndex + 1) % selectRoleSprites->count()))->getValue())
		{
			coupletAbout->setVisible(true);
			coupletSelect->setVisible(false);
			if (isPetVisiable)
			{
				petLayer->setVisible(false);
			}
		}
		else
		{
			if ((currRoleIndex + 1) % selectRoleSprites->count() == Global::getInstance()->getSelectRoleId())
			{
				coupletAbout->setVisible(false);
				coupletSelect->setVisible(true);
				if (isPetVisiable)
				{
					petLayer->setVisible(true);
				}
			}
			else
			{
				coupletAbout->setVisible(false);
				coupletSelect->setVisible(false);
				if (isPetVisiable)
				{
					petLayer->setVisible(false);
				}
			}
		}
		pointIndexSprite->setPosition(((CCSprite *)pointRoleSprites->objectAtIndex(currRoleIndex%pointRoleSprites->count()))->getPosition());

	double _positionX = ((CCNode *)getChildByTag(10))->getPositionX();
	double _positionY = ((CCNode *)getChildByTag(10))->getPositionY();
	int i = 0;
	int length = Player::getInstance()->getPropNum(PROP_TYPE_INGOT);
	while(1)
	{
		length = length / 10;
		if (length > 0)
		{
			i++;
		}
		else
		{
			break;
		}
	}
	ingotNum->setPosition(ccp(_positionX - i*8, _positionY - 13));
}