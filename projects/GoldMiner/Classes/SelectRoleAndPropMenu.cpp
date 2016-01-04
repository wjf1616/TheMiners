#include "SelectRoleAndPropMenu.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "RoleInformation.h"
#include "Player.h"
#include "CartoonLayer.h"
#include "GameControl.h"
#include "LoadingLayer.h"
#include "PromptLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define			SELECTROLEANDPROPMENU_YUN_ASIDE						11	
#define			SELECTROLEANDPROPMENU_FRAME_ASIDE					111
#define			SELECTROLEANDPROPMENU_BUTTON_ASIDE					11
#define			SELECTROLEANDPROPMENU_YUN_MIDDLE					21	
#define			SELECTROLEANDPROPMENU_FRAME_MIDDLE					121
#define			SELECTROLEANDPROPMENU_BUTTON_MIDDLE					21

#define			SELECTROLEANDPROPMENU_BUTTON_SELECTED_UP			102
#define			SELECTROLEANDPROPMENU_BUTTON_UNSELECTED_DOWN		101


#define		SELECTROLEANDPROPMENU_POINT_Y										40
#define		SELECTROLEANDPROPMENU_POINT_X										30


static const ccColor3B myGrey={60,60,60};
static const ccColor4B myGrey4 = {0,0,0,200};

SelectRoleAndPropMenu::SelectRoleAndPropMenu(void)
	: mAnimationManager(NULL)
	,greyLayer(NULL)
	,isBackGround(false)
	,loadingLayer(NULL)
{
}


SelectRoleAndPropMenu::~SelectRoleAndPropMenu(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);


	CC_SAFE_RELEASE_NULL(rolePageButton);// 人物选择按钮
	CC_SAFE_RELEASE_NULL(propPageButton);// 道具选择按钮
	CC_SAFE_RELEASE_NULL(ingotNum);// 道具选择按钮
	CC_SAFE_RELEASE_NULL(coupletSelect);// 道具选择按钮
	CC_SAFE_RELEASE_NULL(coupletAbout);// 道具选择按钮

	CC_SAFE_DELETE(propControl);

	CCObject * p;
	CC_SAFE_RELEASE(pointIndexSprite);
	CCARRAY_FOREACH(selectPropId, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(selectRoleSpritesName, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(pointRoleSprites, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(pointPropSprites, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectPropPrice, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectPropName, p)
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
	CCARRAY_FOREACH(selectRoleSpritesSpeed, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(selectRoleSpritesPower, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(selectRoleSpritesIntroduce, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(selectPropIntroduce, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(selectPropPrice, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(selectPropName, p)
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
	CCARRAY_FOREACH(selectPropSprites, p)
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
	CCARRAY_FOREACH(currSelectPropFrameSprites, p)
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
	CCARRAY_FOREACH(currSelectButtonBuySprites, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}

	CCLOG("SelectRoleAndPropMenu::~SelectRoleAndPropMenu");
}

void SelectRoleAndPropMenu::onEnter(void)
{
	CCLayer::onEnter();

	setVisible(false);
	isBackGround = true;

	Player::getInstance()->getMusicControl()->playOtherBackGround();

	isFristRolePage = true;
	isFristPropPage = true;
	currRoleIndex = 0;
	currPropIndex = 0;
	isRolePage = false;
	rolePageButton = CCSprite::create("xuanren/renwu.png");
	CC_SAFE_RETAIN(rolePageButton);
	addChild(rolePageButton);
	propPageButton = CCSprite::create("xuanren/daoju.png");
	CC_SAFE_RETAIN(propPageButton);
	addChild(propPageButton);
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
	selectPropSprites = new CCArray();
	selectRoleSprites = new CCArray();
	selectRoleSpritesIsHaving = new cocos2d::CCArray();
	currSelectRoleSpritesIsOpen = new cocos2d::CCArray();
	// 人物界面
	selectRoleSpritesName = new CCArray();
	currSelectRoleSpeedBackground = new CCArray();
	currSelectRolePowerBackground = new CCArray();
	currSelectRoleSpeed = new CCArray();
	currSelectRolePower = new CCArray();
	currSelectYunSprites = new CCArray();
	currSelectButtonSelectSprites = new CCArray();
	currSelectAboutSelectSprites = new CCArray();
	currSelectGetSelectSprites = new CCArray();
	currSelectFrameSprites = new CCArray();
	currSelectSpritesIntroduce = new cocos2d::CCArray();
	selectRoleSpritesSpeed = new CCArray();
	selectRoleSpritesPower = new CCArray();
	selectRoleSpritesIntroduce = new CCArray();
	currSelectPropPrice = new cocos2d::CCArray();
	currSelectPropName = new cocos2d::CCArray();
	pointRoleSprites = new cocos2d::CCArray();

	// 道具界面
	currSelectButtonBuySprites = new CCArray();
	currSelectPropFrameSprites = new cocos2d::CCArray();
	selectPropIntroduce = new CCArray();
	selectPropPrice = new CCArray();
	selectPropName = new CCArray();
	pointPropSprites = new cocos2d::CCArray();
	selectPropId = new cocos2d::CCArray();

	initSprites();
	setPageButton(isRolePage);

	Global::getInstance()->setSelectRoleId(Player::getInstance()->getLastRoleSelect());
	((CCSprite *)selectRoleSpritesName->objectAtIndex((currRoleIndex + 1)%selectRoleSpritesName->count()))->setVisible(false);

	schedule(schedule_selector(SelectRoleAndPropMenu::doAction), 0);

	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void SelectRoleAndPropMenu::onEnterTransitionDidFinish(void)
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

void SelectRoleAndPropMenu::startSelf(void)
{
	setVisible(true);
	isBackGround = false;
	mAnimationManager->runAnimationsForSequenceNamed("daojuchuxian");
}

void SelectRoleAndPropMenu::setLoadingLayer(cocos2d::CCLayer * _layer)
{
	loadingLayer = _layer;

	if (loadingLayer == NULL)
	{
		setVisible(true);
	}
}

void SelectRoleAndPropMenu::keyBackClicked(void)	
{
	onMenuItemBackClicked(NULL);
}

void SelectRoleAndPropMenu::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

SEL_MenuHandler SelectRoleAndPropMenu::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBack", SelectRoleAndPropMenu::onMenuItemBackClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnPlay", SelectRoleAndPropMenu::onMenuItemPlayClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnPlus", SelectRoleAndPropMenu::onMenuItemPlusClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnShop", SelectRoleAndPropMenu::onMenuItemShopClicked);

	// 解锁信息
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnUnlock1", SelectRoleAndPropMenu::menuAbout1Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnUnlock2", SelectRoleAndPropMenu::menuAbout2Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnUnlock3", SelectRoleAndPropMenu::menuAbout3Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnUnlock4", SelectRoleAndPropMenu::menuAbout4Callback);

	// 购买道具
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBuy1", SelectRoleAndPropMenu::menuBuy1Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBuy2", SelectRoleAndPropMenu::menuBuy2Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBuy3", SelectRoleAndPropMenu::menuBuy3Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBuy4", SelectRoleAndPropMenu::menuBuy4Callback);

	// 招募
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnRecruit1", SelectRoleAndPropMenu::menuGet1Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnRecruit2", SelectRoleAndPropMenu::menuGet2Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnRecruit3", SelectRoleAndPropMenu::menuGet3Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnRecruit4", SelectRoleAndPropMenu::menuGet4Callback);
	
	// 上阵
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBattle1", SelectRoleAndPropMenu::menuSelect1Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBattle2", SelectRoleAndPropMenu::menuSelect2Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBattle3", SelectRoleAndPropMenu::menuSelect3Callback);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBattle4", SelectRoleAndPropMenu::menuSelect4Callback);

	return NULL;
}

SEL_CCControlHandler SelectRoleAndPropMenu::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool SelectRoleAndPropMenu::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void SelectRoleAndPropMenu::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	//mAnimationManager->runAnimationsForSequenceNamed("daojuchuxian");
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(SelectRoleAndPropMenu::doAnimationCompleted));
	CC_SAFE_RETAIN(mAnimationManager);
}

void SelectRoleAndPropMenu::setBackGround(bool _b)
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


void SelectRoleAndPropMenu::onMenuItemShopClicked(cocos2d::CCObject * pSender)
{
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

}

void SelectRoleAndPropMenu::onMenuItemBackClicked(cocos2d::CCObject * pSender)
{
	//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getShopLayer(NULL));

	//if (Global::getInstance()->getChallengeLevel() != 0)
	//{
	//	LoadingLayer * _tmp;
	//	CCLayer * _tmp1;
	//	_tmp = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
	//	_tmp1 = Global::getInstance()->s->getMainLayer(_tmp);

	//	_tmp->setNextLayer(LAYER_ID_MAIN, _tmp1);
	//	_tmp->addLoadingLayer(0,_tmp1);


	//	Global::getInstance()->s->replaceScene(_tmp);


	//	//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getMainLayer());
	//}
	//else
	//{
	//	// 有loading
	//	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	//	LoadingLayer * _tmp;
	//	CCLayer * _tmp1;
	//	_tmp = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
	//	_tmp1 = Global::getInstance()->s->getSimleGateMenu(_tmp);

	//	_tmp->setNextLayer(LAYER_ID_SMILE_GATE_SCENCE, _tmp1);
	//	_tmp->addLoadingLayer(0,_tmp1);


	//	Global::getInstance()->s->replaceScene(_tmp);

	//	//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getSimleGateMenu());
	//
	//	// 没有loading
	//	//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getSimleGateMenu(NULL));
	//}
}

void SelectRoleAndPropMenu::onMenuItemPlayClicked(cocos2d::CCObject * pSender)
{
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	Player::getInstance()->setLastRoleSelect(Global::getInstance()->getSelectRoleId());

	if (Global::getInstance()->getChallengeLevel() != 0)
	{
		//// 开始游戏loading的页面
		//LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
		//CCLayer * p1 = Global::getInstance()->s->getChallengeLayer(Global::getInstance()->getNextChallengeGateId(), Global::getInstance()->getSelectRoleId(), p);
		////((GameControl *)p1)->setLoadingLayer(p);
		////p->appendLoadingLayerNum(1);
		//p->addLoadingLayer(0,p1);
		//p->setNextLayer(LAYER_ID_GAMING, p1);

		//Global::getInstance()->s->replaceScene(p);
		////Global::getInstance()->s->addLayerToRunningScene(p1);

		//开始游戏没有loading的页面
		Global::getInstance()->s->replaceScene(Global::getInstance()->s->getChallengeLayer(Global::getInstance()->getNextChallengeGateId(), Global::getInstance()->getSelectRoleId(), NULL));
		//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getChallengeLayer(Global::getInstance()->getNextChallengeGateId(), Global::getInstance()->getSelectRoleId()));
	}
	else
	{
		Player::getInstance()->setLastMapId(Global::getInstance()->getMapIdByGateId(Global::getInstance()->getSelectGateId()));
		// 播放漫画
		Global::getInstance()->setCartoonId(0);
		Global::getInstance()->setCartoonId(Global::getInstance()->getSelectGateId());


		//// 开始游戏loading的页面
		//LoadingLayer * p = NULL;
		//CCLayer * p1 = NULL;
		//CCLayer * p2 = NULL;
		//CCLayer * p3 = NULL;
		//switch(Global::getInstance()->getCartoonId())
		//{
		//case 0:
		//	p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
		//	p1 = Global::getInstance()->s->getGameLayer(Global::getInstance()->getSelectGateId(), Global::getInstance()->getSelectRoleId(),p);
		//	p->setNextLayer(LAYER_ID_GAMING, p1);

		//	//((GameControl *)p1)->setLoadingLayer(p);

		//	//p->appendLoadingLayerNum(1);
		//	p->addLoadingLayer(0,p1);
		//	Global::getInstance()->s->replaceScene(p);
		//	//Global::getInstance()->s->addLayerToRunningScene(p1);
		//	break;
		//case CARTOON_BAOXIANGGUO:
		//	p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
		//	p1 = Global::getInstance()->s->getCartoonLayer(CARTOON_START, p);
		//	p2 = Global::getInstance()->s->getCartoonLayer(CARTOON_BAOXIANGGUO, p);
		//	p3 = Global::getInstance()->s->getGameLayer(Global::getInstance()->getSelectGateId(), Global::getInstance()->getSelectRoleId(),p);
		//	p->setNextLayer(LAYER_ID_CARTOON, p1);
		//	((CartoonLayer *)p1)->setNextLayer(LAYER_ID_CARTOON, p2);
		//	((CartoonLayer *)p2)->setNextLayer(LAYER_ID_GAMING, p3);

		//	//((CartoonLayer *)p1)->setLoadingLayer(p);
		//	//((CartoonLayer *)p2)->setLoadingLayer(p);
		//	//((GameControl *)p3)->setLoadingLayer(p);

		//	//p->appendLoadingLayerNum(1);
		//	p->addLoadingLayer(0,p1);
		//	p->addLoadingLayer(0,p2);
		//	p->addLoadingLayer(0,p3);
		//	Global::getInstance()->s->replaceScene(p);
		//	//Global::getInstance()->s->addLayerToRunningScene(p1);
		//	//Global::getInstance()->s->addLayerToRunningScene(p2);
		//	//Global::getInstance()->s->addLayerToRunningScene(p3);
		//	break;
		//case CARTOON_TONGYIANHE:
		//	p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
		//	p1 = Global::getInstance()->s->getCartoonLayer(CARTOON_TONGYIANHE,p);
		//	p2 = Global::getInstance()->s->getGameLayer(Global::getInstance()->getSelectGateId(), Global::getInstance()->getSelectRoleId(),p);
		//	p->setNextLayer(LAYER_ID_CARTOON, p1);
		//	((CartoonLayer *)p1)->setNextLayer(LAYER_ID_GAMING, p2);

		//	//((CartoonLayer *)p1)->setLoadingLayer(p);
		//	//((GameControl *)p2)->setLoadingLayer(p);

		//	//p->appendLoadingLayerNum(1);
		//	p->addLoadingLayer(0,p1);
		//	p->addLoadingLayer(0,p2);
		//	Global::getInstance()->s->replaceScene(p);
		//	//Global::getInstance()->s->addLayerToRunningScene(p1);
		//	//Global::getInstance()->s->addLayerToRunningScene(p2);
		//	break;
		//case CARTOON_NVERGUO:
		//	p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
		//	p1 = Global::getInstance()->s->getCartoonLayer(CARTOON_NVERGUO,p);
		//	p2 = Global::getInstance()->s->getGameLayer(Global::getInstance()->getSelectGateId(), Global::getInstance()->getSelectRoleId(),p);
		//	p->setNextLayer(LAYER_ID_CARTOON, p1);
		//	((CartoonLayer *)p1)->setNextLayer(LAYER_ID_GAMING, p2);

		//	//((CartoonLayer *)p1)->setLoadingLayer(p);
		//	//((GameControl *)p2)->setLoadingLayer(p);

		//	//p->appendLoadingLayerNum(1);
		//	p->addLoadingLayer(0,p1);
		//	p->addLoadingLayer(0,p2);
		//	Global::getInstance()->s->replaceScene(p);
		//	//Global::getInstance()->s->addLayerToRunningScene(p1);
		//	//Global::getInstance()->s->addLayerToRunningScene(p2);
		//	break;
		//case CARTOON_HUOYANSHAN:
		//	p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
		//	p1 = Global::getInstance()->s->getCartoonLayer(CARTOON_HUOYANSHAN,p);
		//	p2 = Global::getInstance()->s->getGameLayer(Global::getInstance()->getSelectGateId(), Global::getInstance()->getSelectRoleId(),p);
		//	p->setNextLayer(LAYER_ID_CARTOON, p1);
		//	((CartoonLayer *)p1)->setNextLayer(LAYER_ID_GAMING, p2);

		//	//((CartoonLayer *)p1)->setLoadingLayer(p);
		//	//((GameControl *)p2)->setLoadingLayer(p);

		//	//p->appendLoadingLayerNum(1);
		//	p->addLoadingLayer(0,p1);
		//	p->addLoadingLayer(0,p2);
		//	Global::getInstance()->s->replaceScene(p);
		//	//Global::getInstance()->s->addLayerToRunningScene(p1);
		//	//Global::getInstance()->s->addLayerToRunningScene(p2);
		//	break;
		//case CARTOON_LINGSHAN:
		//	p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
		//	p1 = Global::getInstance()->s->getCartoonLayer(CARTOON_LINGSHAN,p);
		//	p2 = Global::getInstance()->s->getGameLayer(Global::getInstance()->getSelectGateId(), Global::getInstance()->getSelectRoleId(),p);
		//	p->setNextLayer(LAYER_ID_CARTOON, p1);
		//	((CartoonLayer *)p1)->setNextLayer(LAYER_ID_GAMING, p2);

		//	//((CartoonLayer *)p1)->setLoadingLayer(p);
		//	//((GameControl *)p2)->setLoadingLayer(p);

		//	//p->appendLoadingLayerNum(1);
		//	p->addLoadingLayer(0,p1);
		//	p->addLoadingLayer(0,p2);
		//	Global::getInstance()->s->replaceScene(p);
		//	//Global::getInstance()->s->addLayerToRunningScene(p1);
		//	//Global::getInstance()->s->addLayerToRunningScene(p2);
		//	break;
		//default:
		//	break;
		//}

		// 开始游戏loading的页面
		if (Global::getInstance()->getCartoonId() != 0)
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

		//// 播放漫画
		//Global::getInstance()->setCartoonId(Global::getInstance()->getSelectGateId());
		//if (Global::getInstance()->getCartoonId() != 0)
		//{
		//	Global::getInstance()->s->replaceScene(Global::getInstance()->s->getCartoonLayer(Global::getInstance()->getCartoonId()));
		//}
		//else
		//{
		//	Player::getInstance()->setLastMapId(Global::getInstance()->getSelectGateId());
		//	Global::getInstance()->s->replaceScene(Global::getInstance()->s->getGameLayer(Global::getInstance()->getSelectGateId(), Global::getInstance()->getSelectRoleId()));
		//}
	}
}

void SelectRoleAndPropMenu::onMenuItemPlusClicked(cocos2d::CCObject * pSender)
{
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
}

void SelectRoleAndPropMenu::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
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

	if (isRolePage)
	{
		isCheckButtonIsSelected = Global::getInstance()->isInRect(
			new CCRect(rolePageButton->getPositionX() + rolePageButton->getContentSize().width/2,
			propPageButton->getPositionY() - propPageButton->getContentSize().height*0.7/2,
			propPageButton->getContentSize().width*0.7,
			propPageButton->getContentSize().height*0.7
			),
			m_touchBeginPos.x,
			480 - m_touchBeginPos.y);
	}
	else
	{
		isCheckButtonIsSelected = Global::getInstance()->isInRect(
			new CCRect(rolePageButton->getPositionX() - rolePageButton->getContentSize().width*0.7/2,
			rolePageButton->getPositionY() - rolePageButton->getContentSize().height*0.7/2,
			propPageButton->getPositionX() - (rolePageButton->getPositionX() - rolePageButton->getContentSize().width*0.7/2),
			rolePageButton->getContentSize().height*0.7
			),
			m_touchBeginPos.x,
			480 - m_touchBeginPos.y);
	}
	m_touchMove = false;
}
void SelectRoleAndPropMenu::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	if (isBackGround)
	{
		return;
	}

	m_touchMove = true;
}
void SelectRoleAndPropMenu::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	if (isBackGround)
	{
		return;
	}

	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	m_touchEndPos = touch->getLocation ();
	m_touchEndPos = CCDirector::sharedDirector()->convertToGL( m_touchEndPos );
	if(m_touchMove)
	{
		//如果move了，那么看手指是否上下滑动超过50像素，这个纠正值得有，否则太灵敏了
		if ((m_touchBeginPos.x - m_touchEndPos.x) > 50)
		{
			if(isRolePage)
			{
				setCurrRole(true);
			}
			else
			{
				setCurrProp(true);
			}
		}
		else if ((m_touchEndPos.x - m_touchBeginPos.x) > 50)
		{
			if(isRolePage)
			{
				setCurrRole(false);
			}
			else
			{
				setCurrProp(false);
			}
		}
		else
		{
			checkButtonEvent();
		}
	}
	else
	{
		checkButtonEvent();
	}
	m_touchMove = false;
}

void SelectRoleAndPropMenu::changeCurrPage(void)
{
	for (int i = 0; i < selectRoleSpritesName->count(); i++)
	{
		((CCSprite *)selectRoleSpritesName->objectAtIndex(i))->setVisible(false);
	}
	if(isRolePage)
	{
		mAnimationManager->runAnimationsForSequenceNamed("rwxiaoshi");
		// 换button的显示

	}
	else
	{
		mAnimationManager->runAnimationsForSequenceNamed("daojuxiaoshi");
		// 换button的显示
	}
}
	
void SelectRoleAndPropMenu::setCurrRole(bool _isXiangZuo)
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
				((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_YUN_MIDDLE);
				((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
				((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
				((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
				((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
				((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
				((CCSprite *)currSelectRolePower->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
				((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_MIDDLE);
				((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_MIDDLE);
				((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_MIDDLE);
			}
			else
			{

				((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_YUN_ASIDE);
				((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
				((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
				((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
				((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
				((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
				((CCSprite *)currSelectRolePower->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
				((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_ASIDE);
				((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_ASIDE);
				((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_ASIDE);
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
				((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_YUN_MIDDLE);
				((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
				((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
				((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
				((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
				((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
				((CCSprite *)currSelectRolePower->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
				((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_MIDDLE);
				((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_MIDDLE);
				((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_MIDDLE);
			}
			else
			{

				((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_YUN_ASIDE);
				((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
				((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
				((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
				((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
				((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
				((CCSprite *)currSelectRolePower->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
				((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_ASIDE);
				((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_ASIDE);
				((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_ASIDE);

			}
		}
	}
	((CCSprite *)selectRoleSpritesName->objectAtIndex((currRoleIndex + 1)%selectRoleSpritesName->count()))->setVisible(true);
}
	
void SelectRoleAndPropMenu::setCurrProp(bool _isXiangZuo)
{
	if (_isXiangZuo)
	{
		currButtonIndex = 3;
		setNodeBySelectIndex(_isXiangZuo);
		currPropIndex++;
		currPropIndex = currPropIndex % selectPropSprites->count();
		mAnimationManager->runAnimationsForSequenceNamed("djxiangzuo");
	}
	else
	{
		currButtonIndex = 1;
		setNodeBySelectIndex(_isXiangZuo);
		currPropIndex--;
		currPropIndex = (currPropIndex + selectPropSprites->count()) % selectPropSprites->count();
		mAnimationManager->runAnimationsForSequenceNamed("djxiangyou");
	}
}

void SelectRoleAndPropMenu::checkButtonEvent(void)
{
	if (isCheckButtonIsSelected)
	{
		if (isRolePage)
		{
			if (Global::getInstance()->isInRect(
				new CCRect(rolePageButton->getPositionX() + rolePageButton->getContentSize().width/2,
				propPageButton->getPositionY() - propPageButton->getContentSize().height*0.7/2,
				propPageButton->getContentSize().width*0.7,
				propPageButton->getContentSize().height*0.7
				),
				m_touchEndPos.x,
				480 - m_touchEndPos.y))
			{
				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
				changeCurrPage();
				//setPageButton(false);
			}
			 
		}
		else
		{
			if (isCheckButtonIsSelected = Global::getInstance()->isInRect(
				new CCRect(rolePageButton->getPositionX() - rolePageButton->getContentSize().width*0.7/2,
				rolePageButton->getPositionY() - rolePageButton->getContentSize().height*0.7/2,
				propPageButton->getPositionX() - (rolePageButton->getPositionX() - rolePageButton->getContentSize().width*0.7/2),
				rolePageButton->getContentSize().height*0.7
				),
				m_touchEndPos.x,
				480 - m_touchEndPos.y))
			{
				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
				changeCurrPage();
				//setPageButton(true);
			}
		}
	}
	
}

void SelectRoleAndPropMenu::setPageButton(bool _isRolePage)
{

	isRolePage = _isRolePage;
	if (_isRolePage)
	{
		rolePageButton->setPosition(ccp(97,41));
		rolePageButton->setScale(1);
		rolePageButton->setZOrder(SELECTROLEANDPROPMENU_BUTTON_SELECTED_UP);
		propPageButton->setPosition(ccp(204,28));
		propPageButton->setScale(0.7);
		propPageButton->setZOrder(SELECTROLEANDPROPMENU_BUTTON_UNSELECTED_DOWN);

		for (int i = 0 ; i < 4; i++)
		{
			((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setVisible(true);
			((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setVisible(true);
			((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setVisible(true);
			((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setVisible(true);
			((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setVisible(true);
			((CCSprite *)currSelectRolePower->objectAtIndex(i))->setVisible(true);
			((CCSprite *)currSelectPropName->objectAtIndex(i))->setVisible(false);
			((CCLabelAtlas *)currSelectPropPrice->objectAtIndex(i))->setVisible(false);

			((CCSprite *)currSelectPropFrameSprites->objectAtIndex(i))->setVisible(false);
			((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setVisible(false);
		}
		for (int i =0; i < pointRoleSprites->count(); i++)
		{
			((CCSprite *)pointRoleSprites->objectAtIndex(i))->setVisible(true);
		}
		for (int i =0; i < pointPropSprites->count(); i++)
		{
			((CCSprite *)pointPropSprites->objectAtIndex(i))->setVisible(false);
		}
		coupletAbout->setVisible(false);
		coupletSelect->setVisible(false);
		isFristRolePage = true;
		setNodeBySelectIndex(true);
	}
	else
	{
		rolePageButton->setPosition(ccp(71,28));
		rolePageButton->setScale(0.7);
		rolePageButton->setZOrder(SELECTROLEANDPROPMENU_BUTTON_UNSELECTED_DOWN);
		propPageButton->setPosition(ccp(182,41));
		propPageButton->setScale(1);
		propPageButton->setZOrder(SELECTROLEANDPROPMENU_BUTTON_SELECTED_UP);

		for (int i = 0 ; i < 4; i++)
		{
			((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setVisible(false);
			((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setVisible(false);
			((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setVisible(false);
			((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setVisible(false);
			((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setVisible(false);
			((CCSprite *)currSelectRolePower->objectAtIndex(i))->setVisible(false);
			((CCSprite *)currSelectPropName->objectAtIndex(i))->setVisible(true);
			((CCLabelAtlas *)currSelectPropPrice->objectAtIndex(i))->setVisible(true);
			((CCSprite *)currSelectPropFrameSprites->objectAtIndex(i))->setVisible(true);
			((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setVisible(false);
			((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setVisible(false);
			((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setVisible(false);
			((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setVisible(true);
		}
		for (int i =0; i < pointRoleSprites->count(); i++)
		{
			((CCSprite *)pointRoleSprites->objectAtIndex(i))->setVisible(false);
		}
		for (int i =0; i < pointPropSprites->count(); i++)
		{
			((CCSprite *)pointPropSprites->objectAtIndex(i))->setVisible(true);
		}
		isFristPropPage = true;
		coupletAbout->setVisible(false);
		coupletSelect->setVisible(false);
		setNodeBySelectIndex(true);
	}


	getChildByTag(999)->setZOrder(100);
}

void SelectRoleAndPropMenu::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"rwxiaoshi") == 0)
	{	
		setPageButton(false);
		mAnimationManager->runAnimationsForSequenceNamed("daojuchuxian");
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"daojuxiaoshi") == 0)
	{
		setPageButton(true);
		mAnimationManager->runAnimationsForSequenceNamed("renwuchuxian2");
		((CCSprite *)selectRoleSpritesName->objectAtIndex((currRoleIndex + 1)%selectRoleSpritesName->count()))->setVisible(true);
	}
}
	
void SelectRoleAndPropMenu::reBack(int _type, bool _b)
{
	setBackGround(false);
	// type是值回来前调用界面的类型  这里没必要区分  只是购买才需要处理
	if(_b)
	{	
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

void SelectRoleAndPropMenu::initSprites(void)
{
	// 人物界面
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
	// 还要初始化是否拥有对象(假的现在)是否已经开启对象
	selectRoleSpritesSpeed->addObject(CCInteger::create(1));
	selectRoleSpritesPower->addObject(CCInteger::create(1));
	selectRoleSpritesIntroduce->addObject(CCSprite::create("xuanren/hxsh.png"));
	
	// 唐僧
	selectRoleSpritesIsHaving->addObject(CCInteger::create(1));
	selectRoleSpritesIsOpen->addObject(CCInteger::create(1));
	selectRoleSprites->addObject(CCSprite::create("xuanren/tangseng1.png"));
	selectRoleSpritesName->addObject(CCSprite::create("xuanren/tangseng.png"));
	((CCSprite *)selectRoleSpritesName->lastObject())->setPosition(ccp(405, 425));
	((CCSprite *)selectRoleSpritesName->lastObject())->setVisible(false);
	addChild((CCSprite *)selectRoleSpritesName->lastObject(), 998);
	// 还要初始化是否拥有对象(假的现在)是否已经开启对象
	selectRoleSpritesSpeed->addObject(CCInteger::create(1));
	selectRoleSpritesPower->addObject(CCInteger::create(1));
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
	// 还要初始化是否拥有对象(假的现在)是否已经开启对象
	selectRoleSpritesSpeed->addObject(CCInteger::create(1));
	selectRoleSpritesPower->addObject(CCInteger::create(1));
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
	// 还要初始化是否拥有对象(假的现在)是否已经开启对象
	selectRoleSpritesSpeed->addObject(CCInteger::create(1));
	selectRoleSpritesPower->addObject(CCInteger::create(1));
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
	// 还要初始化是否拥有对象(假的现在)是否已经开启对象
	selectRoleSpritesSpeed->addObject(CCInteger::create(1));
	selectRoleSpritesPower->addObject(CCInteger::create(1));
	selectRoleSpritesIntroduce->addObject(CCSprite::create("xuanren/sjjz.png"));

	// 添加任务点点
	for (int i = 0; i < 5; i++)
	{
		pointRoleSprites->addObject(CCSprite::create("xuandaguan/dian2.png"));
		((CCSprite *)pointRoleSprites->lastObject())->setPosition(ccp(400 - 5*SELECTROLEANDPROPMENU_POINT_X/2 + i*SELECTROLEANDPROPMENU_POINT_X + SELECTROLEANDPROPMENU_POINT_X/2, SELECTROLEANDPROPMENU_POINT_Y));
		addChild((CCSprite *)pointRoleSprites->lastObject());
	}

	// 道具界面			当界面选项不足所需的4个时候  要添加一个循环
	char _s[32];
	propControl = new Prop();
	selectPropSprites->addObject(CCSprite::create("xuanren/sl.png"));
	selectPropName->addObject(CCSprite::create("xuanren/sl1.png"));
	sprintf(_s, "%d",propControl->getPrice(PROP_TYPE_MOONLIGHT));
	selectPropPrice->addObject(CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0'));
	selectPropId->addObject(CCInteger::create(PROP_TYPE_MOONLIGHT));
	selectPropIntroduce->addObject(CCSprite::create("xuanren/sl2.png"));

	selectPropSprites->addObject(CCSprite::create("xuanren/zd.png"));
	selectPropName->addObject(CCSprite::create("xuanren/zhadan.png"));
	sprintf(_s, "%d",propControl->getPrice(PROP_TYPE_GRENADE));
	selectPropPrice->addObject(CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0'));
	selectPropId->addObject(CCInteger::create(PROP_TYPE_GRENADE));
	selectPropIntroduce->addObject(CCSprite::create("xuanren/zd1.png"));

	selectPropSprites->addObject(CCSprite::create("xuanren/llys.png"));
	selectPropName->addObject(CCSprite::create("xuanren/llys1.png"));
	sprintf(_s, "%d",propControl->getPrice(PROP_TYPE_VIGOROUSLY_PILL));
	selectPropPrice->addObject(CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0'));
	selectPropId->addObject(CCInteger::create(PROP_TYPE_VIGOROUSLY_PILL));
	selectPropIntroduce->addObject(CCSprite::create("xuanren/dlys2.png"));

	selectPropSprites->addObject(CCSprite::create("xuanren/miaozhunjing.png"));
	selectPropName->addObject(CCSprite::create("xuanren/miaozhunjing2.png"));
	sprintf(_s, "%d",propControl->getPrice(PROP_TYPE_ALIGNMENT));
	selectPropPrice->addObject(CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0'));
	selectPropId->addObject(CCInteger::create(PROP_TYPE_ALIGNMENT));
	selectPropIntroduce->addObject(CCSprite::create("xuanren/miaozhunjing1.png"));

	//selectPropSprites->addObject(CCSprite::create("xuanren/sl.png"));
	//selectPropName->addObject(CCSprite::create("xuanren/sl1.png"));
	//sprintf(_s, "%d",propControl->getPrice(PROP_TYPE_MOONLIGHT));
	//selectPropPrice->addObject(CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0'));
	//selectPropId->addObject(CCInteger::create(PROP_TYPE_MOONLIGHT));
	//selectPropIntroduce->addObject(CCSprite::create("xuanren/sl2.png"));

	//selectPropSprites->addObject(CCSprite::create("xuanren/zd.png"));
	//selectPropName->addObject(CCSprite::create("xuanren/zhadan.png"));
	//sprintf(_s, "%d",propControl->getPrice(PROP_TYPE_GRENADE));
	//selectPropPrice->addObject(CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0'));
	//selectPropId->addObject(CCInteger::create(PROP_TYPE_GRENADE));
	//selectPropIntroduce->addObject(CCSprite::create("xuanren/zd1.png"));

	//selectPropSprites->addObject(CCSprite::create("xuanren/llys.png"));
	//selectPropName->addObject(CCSprite::create("xuanren/llys1.png"));
	//sprintf(_s, "%d",propControl->getPrice(PROP_TYPE_VIGOROUSLY_PILL));
	//selectPropPrice->addObject(CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0'));
	//selectPropId->addObject(CCInteger::create(PROP_TYPE_VIGOROUSLY_PILL));
	//selectPropIntroduce->addObject(CCSprite::create("xuanren/sl2.png"));
	// 添加道具点点
	for (int i = 0; i < 4; i++)
	{
		pointPropSprites->addObject(CCSprite::create("xuandaguan/dian2.png"));
		((CCSprite *)pointPropSprites->lastObject())->setPosition(ccp(400 - 3*SELECTROLEANDPROPMENU_POINT_X/2 + i*SELECTROLEANDPROPMENU_POINT_X + SELECTROLEANDPROPMENU_POINT_X/2, SELECTROLEANDPROPMENU_POINT_Y));
		addChild((CCSprite *)pointPropSprites->lastObject());
	}
	// 亮点点
	pointIndexSprite = CCSprite::create("xuandaguan/dian1.png");
	pointIndexSprite->retain();
	addChild(pointIndexSprite,998);

	currSelectButtonSelectSprites->addObject(getChildByTag(999)->getChildByTag(41));
	currSelectButtonSelectSprites->addObject(getChildByTag(999)->getChildByTag(42));
	currSelectButtonSelectSprites->addObject(getChildByTag(999)->getChildByTag(43));
	currSelectButtonSelectSprites->addObject(getChildByTag(999)->getChildByTag(44));

	currSelectAboutSelectSprites->addObject(getChildByTag(999)->getChildByTag(11));
	currSelectAboutSelectSprites->addObject(getChildByTag(999)->getChildByTag(12));
	currSelectAboutSelectSprites->addObject(getChildByTag(999)->getChildByTag(13));
	currSelectAboutSelectSprites->addObject(getChildByTag(999)->getChildByTag(14));

	currSelectGetSelectSprites->addObject(getChildByTag(999)->getChildByTag(31));
	currSelectGetSelectSprites->addObject(getChildByTag(999)->getChildByTag(32));
	currSelectGetSelectSprites->addObject(getChildByTag(999)->getChildByTag(33));
	currSelectGetSelectSprites->addObject(getChildByTag(999)->getChildByTag(34));

	currSelectButtonBuySprites->addObject(getChildByTag(999)->getChildByTag(21));
	currSelectButtonBuySprites->addObject(getChildByTag(999)->getChildByTag(22));
	currSelectButtonBuySprites->addObject(getChildByTag(999)->getChildByTag(23));
	currSelectButtonBuySprites->addObject(getChildByTag(999)->getChildByTag(24));

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
		//addChild((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i));
		//addChild((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i));
		//addChild((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i));
		currSelectPropName->addObject((CCSprite *)selectPropName->objectAtIndex(i));
		currSelectPropPrice->addObject((CCSprite *)selectPropPrice->objectAtIndex(i));
		
		currSelectSprites->addObject(selectRoleSprites->objectAtIndex((i + currRoleIndex) % selectRoleSprites->count()));
		currSelectSpritesIntroduce->addObject(selectRoleSpritesIntroduce->objectAtIndex((i + currRoleIndex) % selectRoleSprites->count()));
		currSelectPropFrameSprites->addObject(CCSprite::create("xuanren/daojukuang.png"));
		getChildByTag(i+1)->addChild((CCSprite *)currSelectSprites->objectAtIndex(i));
		addChild((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i));
		addChild((CCSprite *)currSelectPropPrice->objectAtIndex(i));
		addChild((CCSprite *)currSelectPropName->objectAtIndex(i));
		((CCSprite *)currSelectPropName->objectAtIndex(i))->setVisible(false);
		getChildByTag(i+1)->addChild((CCSprite *)currSelectPropFrameSprites->objectAtIndex(i));
		//if (i % 2 == 0)
		//{
		//	((CCSprite *)currSelectSprites->objectAtIndex(i))->setColor(myGrey);
		//}
	}
}

void SelectRoleAndPropMenu::setNodeBySelectIndex(bool _isXiangZuo)
{
	if (isRolePage)
	{
		for (int i = 4; i > 0; i--)
		{// 移除node中的ccSprite
			getChildByTag(i)->removeChild((CCSprite *)currSelectSprites->lastObject());
			removeChild((CCSprite *)currSelectSpritesIntroduce->lastObject(),true);
			currSelectSprites->removeLastObject();
			currSelectSpritesIntroduce->removeLastObject();
		}
		for (int i = 0; i< 4; i++)
		{
			// 按钮显示相关
			if (((CCInteger *)selectRoleSpritesIsHaving->objectAtIndex((i + currRoleIndex) % selectRoleSprites->count()))->getValue() == 1)
			{
				// 拥有人物
				((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setVisible(true);
				((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setVisible(false);
				((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setVisible(false);
			}
			else
			{	// 没有拥有人物
				if (((CCInteger *)selectRoleSpritesIsOpen->objectAtIndex((i + currRoleIndex) % selectRoleSprites->count()))->getValue() == 1)
				{// 可以购买人物
					((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setVisible(false);
					((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setVisible(true);
					((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setVisible(false);
				}
				else
				{// 不能购买人物 只能看介绍
					((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setVisible(false);
					((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setVisible(false);
					((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setVisible(true);
				}
			}

			// 属性显示相关
			
			if (_isXiangZuo)
			{
				currSelectSprites->addObject(selectRoleSprites->objectAtIndex((i + currRoleIndex) % selectRoleSprites->count()));
				currSelectSpritesIntroduce->addObject(selectRoleSpritesIntroduce->objectAtIndex((i + currRoleIndex) % selectRoleSprites->count()));
			}
			else
			{
				if (i == 3)
				{
					currSelectSprites->addObject(selectRoleSprites->objectAtIndex((selectRoleSprites->count() - 1 + currRoleIndex) % selectRoleSprites->count()));
					currSelectSpritesIntroduce->addObject(selectRoleSpritesIntroduce->objectAtIndex((selectRoleSprites->count() - 1 + currRoleIndex) % selectRoleSprites->count()));
				}
				else
				{
					currSelectSprites->addObject(selectRoleSprites->objectAtIndex((i + currRoleIndex) % selectRoleSprites->count()));
					currSelectSpritesIntroduce->addObject(selectRoleSpritesIntroduce->objectAtIndex((i + currRoleIndex) % selectRoleSprites->count()));
				}
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
					((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setColor(myGrey);
					((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setColor(myGrey);
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
					((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setColor(ccWHITE);
				}
				if (i == 1)
				{
					currButtonIndex = 2;
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_YUN_MIDDLE);
					((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_YUN_MIDDLE);
					((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
					((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
					((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
					((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
					((CCSprite *)currSelectRolePower->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_MIDDLE);
					((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_MIDDLE);
					((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_MIDDLE);
					((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_MIDDLE);
				}
				else
				{
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_YUN_ASIDE);
					((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_YUN_ASIDE);
					((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
					((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
					((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
					((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
					((CCSprite *)currSelectRolePower->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_FRAME_ASIDE);
					((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_ASIDE);
					((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_ASIDE);
					((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setZOrder(SELECTROLEANDPROPMENU_BUTTON_ASIDE);
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
					((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setColor(myGrey);
					((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setColor(myGrey);
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
					((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setColor(ccWHITE);
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
	else
	{
		for (int i = 4; i > 0; i--)
		{// 移除node中的ccSprite
			getChildByTag(i)->removeChild((CCSprite *)currSelectSprites->lastObject());
			currSelectSprites->removeLastObject();
			removeChild((CCSprite *)currSelectSpritesIntroduce->lastObject(),true);
			currSelectSpritesIntroduce->removeLastObject();
			removeChild((CCLabelAtlas *)currSelectPropPrice->lastObject(),true);
			currSelectPropPrice->removeLastObject();
			removeChild((CCSprite *)currSelectPropName->lastObject(),true);
			currSelectPropName->removeLastObject();
		}
		for (int i = 0; i< 4; i++)
		{
			if (_isXiangZuo)
			{
				currSelectSprites->addObject(selectPropSprites->objectAtIndex((i + currPropIndex) % selectPropSprites->count()));
				currSelectSpritesIntroduce->addObject(selectPropIntroduce->objectAtIndex((i + currPropIndex) % selectPropSprites->count()));
				currSelectPropPrice->addObject(selectPropPrice->objectAtIndex((i + currPropIndex) % selectPropSprites->count()));
				currSelectPropName->addObject(selectPropName->objectAtIndex((i + currPropIndex) % selectPropSprites->count()));
			}
			else
			{
				if (i == 3)
				{
					currSelectSprites->addObject(selectPropSprites->objectAtIndex((selectPropSprites->count() - 1 + currPropIndex) % selectPropSprites->count()));
					currSelectSpritesIntroduce->addObject(selectPropIntroduce->objectAtIndex((selectPropSprites->count() - 1 + currPropIndex) % selectPropSprites->count()));
					currSelectPropPrice->addObject(selectPropPrice->objectAtIndex((selectPropSprites->count() - 1 + currPropIndex) % selectPropSprites->count()));
					currSelectPropName->addObject(selectPropName->objectAtIndex((selectPropSprites->count() - 1 + currPropIndex) % selectPropSprites->count()));
				}
				else
				{
					currSelectSprites->addObject(selectPropSprites->objectAtIndex((i + currPropIndex) % selectPropSprites->count()));
					currSelectSpritesIntroduce->addObject(selectPropIntroduce->objectAtIndex((i + currPropIndex) % selectPropSprites->count()));
					currSelectPropPrice->addObject(selectPropPrice->objectAtIndex((i + currPropIndex) % selectPropSprites->count()));
					currSelectPropName->addObject(selectPropName->objectAtIndex((i + currPropIndex) % selectPropSprites->count()));
				}
			}
			getChildByTag(i+1)->addChild((CCSprite *)currSelectSprites->objectAtIndex(i));
			addChild((CCLabelAtlas *)currSelectPropPrice->objectAtIndex(i));
			addChild((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i));
			addChild((CCSprite *)currSelectPropName->objectAtIndex(i));
			if (isFristPropPage)
			{
				currButtonIndex = 2;
				if (i % 2 == 0)
				{
					((CCSprite *)currSelectSprites->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setColor(myGrey);
					((CCLabelAtlas *)currSelectPropPrice->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectPropName->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectPropFrameSprites->objectAtIndex(i))->setColor(myGrey);
					((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setColor(myGrey);
				}
				else
				{
					((CCSprite *)currSelectSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setColor(ccWHITE);
					((CCLabelAtlas *)currSelectPropPrice->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectPropName->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectPropFrameSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setColor(ccWHITE);
				}
			}
			else
			{
				if (i % 2 == 1)
				{
					((CCSprite *)currSelectSprites->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setColor(myGrey);
					((CCLabelAtlas *)currSelectPropPrice->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectPropName->objectAtIndex(i))->setColor(myGrey);
						((CCSprite *)currSelectPropFrameSprites->objectAtIndex(i))->setColor(myGrey);
					((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setColor(myGrey);
				}
				else
				{
					((CCSprite *)currSelectSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setColor(ccWHITE);
					((CCLabelAtlas *)currSelectPropPrice->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectPropName->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectPropFrameSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setColor(ccWHITE);
				}
			}
		}
		if (isFristPropPage)
		{
			isFristPropPage = false;
		}
		getChildByTag(999)->setZOrder(100);
	}
}

void SelectRoleAndPropMenu::menuSelect1Callback(CCObject* pSender)
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
	}
}

void SelectRoleAndPropMenu::menuSelect2Callback(CCObject* pSender)
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
	}
}

void SelectRoleAndPropMenu::menuSelect3Callback(CCObject* pSender)
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
	}
}

void SelectRoleAndPropMenu::menuSelect4Callback(CCObject* pSender)
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
	}
}

void SelectRoleAndPropMenu::menuGet1Callback(CCObject* pSender)
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

void SelectRoleAndPropMenu::menuGet2Callback(CCObject* pSender)
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

void SelectRoleAndPropMenu::menuGet3Callback(CCObject* pSender)
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

void SelectRoleAndPropMenu::menuGet4Callback(CCObject* pSender)
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

void SelectRoleAndPropMenu::menuAbout1Callback(CCObject* pSender)
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

void SelectRoleAndPropMenu::menuAbout2Callback(CCObject* pSender)
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

void SelectRoleAndPropMenu::menuAbout3Callback(CCObject* pSender)
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

void SelectRoleAndPropMenu::menuAbout4Callback(CCObject* pSender)
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

void SelectRoleAndPropMenu::menuBuy1Callback(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (currButtonIndex == 1)
	{
		// 购买道具
		int id = ((CCInteger *)selectPropId->objectAtIndex((currPropIndex + 1) % selectPropSprites->count()))->getValue();

		if (id == PROP_TYPE_ALIGNMENT && (Player::getInstance()->getPropNum(PROP_TYPE_ALIGNMENT) > 0))
		{
			// 提示已经购买了瞄准线了 (瞄准线最多1个)
			PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_PROP_ROLE);
			setBackGround(true);
			//promptLayer->setForwardLayer(this);
			Global::getInstance()->s->addLayerToRunningScene(promptLayer);
			promptLayer->miaoZhunXianInformation();
		}
		else
		{
			if (Player::getInstance()->getPropNum(PROP_TYPE_INGOT) >= propControl->getPrice(id))
			{
				Player::getInstance()->appendPropNum(PROP_TYPE_INGOT ,-propControl->getPrice(id));
				Player::getInstance()->savePropNum(PROP_TYPE_INGOT ,-propControl->getPrice(id));
				Player::getInstance()->appendPropNum(id ,1);
				Player::getInstance()->savePropNum(id ,1);

				char _s[32];
				sprintf(_s, "%d",Player::getInstance()->getPropNum(PROP_TYPE_INGOT));
				removeChild(ingotNum);
				ingotNum = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
				CC_SAFE_RETAIN(ingotNum);
				addChild(ingotNum, 998);

				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FINISH);
			}
			else
			{
				// 钱不够购买
				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FAILED);
			}
		}
	}
}

void SelectRoleAndPropMenu::menuBuy2Callback(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (currButtonIndex == 2)
	{
		// 购买道具
		int id = ((CCInteger *)selectPropId->objectAtIndex((currPropIndex + 1) % selectPropSprites->count()))->getValue();

		if (id == PROP_TYPE_ALIGNMENT && (Player::getInstance()->getPropNum(PROP_TYPE_ALIGNMENT) > 0))
		{
			// 提示已经购买了瞄准线了 (瞄准线最多1个)
		}
		else
		{
			if (Player::getInstance()->getPropNum(PROP_TYPE_INGOT) >= propControl->getPrice(id))
			{
				Player::getInstance()->appendPropNum(PROP_TYPE_INGOT ,-propControl->getPrice(id));
				Player::getInstance()->savePropNum(PROP_TYPE_INGOT ,-propControl->getPrice(id));
				Player::getInstance()->appendPropNum(id ,1);
				Player::getInstance()->savePropNum(id ,1);

				char _s[32];
				sprintf(_s, "%d",Player::getInstance()->getPropNum(PROP_TYPE_INGOT));
				removeChild(ingotNum);
				ingotNum = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
				CC_SAFE_RETAIN(ingotNum);
				addChild(ingotNum, 998);

				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FINISH);
			}
			else
			{
				// 钱不够购买
				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FAILED);
			}
		}
	}
}

void SelectRoleAndPropMenu::menuBuy3Callback(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (currButtonIndex == 3)
	{
		// 购买道具
		int id = ((CCInteger *)selectPropId->objectAtIndex((currPropIndex + 1) % selectPropSprites->count()))->getValue();

		if (id == PROP_TYPE_ALIGNMENT && (Player::getInstance()->getPropNum(PROP_TYPE_ALIGNMENT) > 0))
		{
			// 提示已经购买了瞄准线了 (瞄准线最多1个)
		}
		else
		{
			if (Player::getInstance()->getPropNum(PROP_TYPE_INGOT) >= propControl->getPrice(id))
			{
				Player::getInstance()->appendPropNum(PROP_TYPE_INGOT ,-propControl->getPrice(id));
				Player::getInstance()->savePropNum(PROP_TYPE_INGOT ,-propControl->getPrice(id));
				Player::getInstance()->appendPropNum(id ,1);
				Player::getInstance()->savePropNum(id ,1);

				char _s[32];
				sprintf(_s, "%d",Player::getInstance()->getPropNum(PROP_TYPE_INGOT));
				removeChild(ingotNum);
				ingotNum = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
				CC_SAFE_RETAIN(ingotNum);
				addChild(ingotNum, 998);

				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FINISH);
			}
			else
			{
				// 钱不够购买
				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FAILED);
			}
		}
	}
}

void SelectRoleAndPropMenu::menuBuy4Callback(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	if (currButtonIndex == 4)
	{
		// 购买道具
		int id = ((CCInteger *)selectPropId->objectAtIndex((currPropIndex + 1) % selectPropSprites->count()))->getValue();

		if (id == PROP_TYPE_ALIGNMENT && (Player::getInstance()->getPropNum(PROP_TYPE_ALIGNMENT) > 0))
		{
			// 提示已经购买了瞄准线了 (瞄准线最多1个)
			
		}
		else
		{
			if (Player::getInstance()->getPropNum(PROP_TYPE_INGOT) >= propControl->getPrice(id))
			{
				Player::getInstance()->appendPropNum(PROP_TYPE_INGOT ,-propControl->getPrice(id));
				Player::getInstance()->savePropNum(PROP_TYPE_INGOT ,-propControl->getPrice(id));
				Player::getInstance()->appendPropNum(id ,1);
				Player::getInstance()->savePropNum(id ,1);

				char _s[32];
				sprintf(_s, "%d",Player::getInstance()->getPropNum(PROP_TYPE_INGOT));
				removeChild(ingotNum);
				ingotNum = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
				CC_SAFE_RETAIN(ingotNum);
				addChild(ingotNum, 998);

				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FINISH);
			}
			else
			{
				// 钱不够购买
				Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUY_FAILED);
			}
		}
	}
}

void SelectRoleAndPropMenu::doAction(float _f)
{
	if (isRolePage)
	{
		for (int i = 0; i < 4; i++)
		{
			double _positionX = ((CCNode *)getChildByTag(i+1))->getPositionX();
			double _positionY = ((CCNode *)getChildByTag(i+1))->getPositionY();

			double _scale =  ((CCNode *)getChildByTag(i+1))->getScale();
			((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setPosition(ccp(_positionX+7*_scale, _positionY-124*_scale));
			((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setPosition(ccp(_positionX+237*_scale, _positionY-111*_scale));
			((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setPosition(ccp(_positionX+1*_scale, _positionY-139*_scale));
			((CCMenuItemImage *)currSelectAboutSelectSprites->objectAtIndex(i))->setPosition(ccp(_positionX+1*_scale, _positionY-139*_scale));
			((CCMenuItemImage *)currSelectGetSelectSprites->objectAtIndex(i))->setPosition(ccp(_positionX+1*_scale, _positionY-139*_scale));
			((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setPosition(ccp(_positionX+233.5*_scale, _positionY-137.5*_scale));
			((CCSprite *)currSelectRoleSpeedBackground->objectAtIndex(i))->setPosition(ccp(_positionX+226*_scale, _positionY-87.5*_scale));
			((CCSprite *)currSelectRoleSpeed->objectAtIndex(i))->setPosition(ccp(_positionX+226*_scale, _positionY-87.5*_scale));
			((CCSprite *)currSelectRolePowerBackground->objectAtIndex(i))->setPosition(ccp(_positionX+233.5*_scale, _positionY-112.5*_scale));
			((CCSprite *)currSelectRolePower->objectAtIndex(i))->setPosition(ccp(_positionX+233.5*_scale, _positionY-112.5*_scale));


			((CCSprite *)currSelectYunSprites->objectAtIndex(i))->setScale(_scale);
			((CCSprite *)currSelectFrameSprites->objectAtIndex(i))->setScale(_scale);
			((CCMenuItemImage *)currSelectButtonSelectSprites->objectAtIndex(i))->setScale(_scale);
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
		}
		else
		{
			if ((currRoleIndex + 1) % selectRoleSprites->count() == Global::getInstance()->getSelectRoleId())
			{
				coupletAbout->setVisible(false);
				coupletSelect->setVisible(true);
			}
			else
			{
				coupletAbout->setVisible(false);
				coupletSelect->setVisible(false);
			}
		}
		pointIndexSprite->setPosition(((CCSprite *)pointRoleSprites->objectAtIndex(currRoleIndex%pointRoleSprites->count()))->getPosition());
	} 
	else
	{
		for (int i = 0; i < 4; i++)
		{
			double _positionX = ((CCNode *)getChildByTag(i+1))->getPositionX();
			double _positionY = ((CCNode *)getChildByTag(i+1))->getPositionY();
			double _scale =  ((CCNode *)getChildByTag(i+1))->getScale();
			((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setPosition(ccp(_positionX-2.5*_scale, _positionY-96.5*_scale));
			((CCLabelAtlas *)currSelectPropPrice->objectAtIndex(i))->setPosition(ccp(_positionX-43.5*_scale, _positionY-38*_scale));
			((CCSprite *)currSelectPropName->objectAtIndex(i))->setPosition(ccp(_positionX+2*_scale, _positionY+30.5*_scale));
			((CCSprite *)currSelectSprites->objectAtIndex(i))->setPosition(ccp(0, 100+40*_scale));
			((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setPosition(ccp(_positionX-2*_scale, _positionY+ 35+ 35*_scale));
			
			((CCMenuItemImage *)currSelectButtonBuySprites->objectAtIndex(i))->setScale(_scale);
			((CCSprite *)currSelectSpritesIntroduce->objectAtIndex(i))->setScale(_scale);
			((CCLabelAtlas *)currSelectPropPrice->objectAtIndex(i))->setScale(_scale);
			((CCSprite *)currSelectPropName->objectAtIndex(i))->setScale(_scale);
			((CCSprite *)currSelectSprites->objectAtIndex(i))->setScale(_scale);
		}

		pointIndexSprite->setPosition(((CCSprite *)pointPropSprites->objectAtIndex(currPropIndex%pointPropSprites->count()))->getPosition());
	}

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