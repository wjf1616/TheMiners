#include "BigGateMenu.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "Player.h"
#include "PromptLayer.h"
#include "LoadingLayer.h"
#include "GameControl.h"
#include "SlipGuide.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define		BIG_GATE_MENU_POINT_Y										40
#define		BIG_GATE_MENU_POINT_X										30


#define    BIG_GATE_DEBUG


static const ccColor3B myGrey={60,60,60};
static const ccColor4B myGrey4 = {0,0,0,200};

BigGateMenu::BigGateMenu(void)
	: mAnimationManager(NULL)
	,currPageIndex(0)
	,myButton(NULL)
	,isBackGround(false)
	,greyLayer(NULL)
	,loadingLayer(NULL)
{
#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::BigGateMenu    ");
#endif
	setVisible(false);
	isBackGround = true;
	isDoAction = false;
}

void BigGateMenu::onEnterTransitionDidFinish(void)
{
	CCLayer::onEnterTransitionDidFinish();


#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::onEnterTransitionDidFinish");
#endif

	// 都要重新  从数据存储获得新的数据（目前是因为引导的时候将缓存数据更改掉了才执行这样的操作的）
	Player::getInstance()->initPropNumFromDateStore();
	if (loadingLayer != NULL)
	{

#ifdef								BIG_GATE_DEBUG
		CCLOG("BigGateMenu::onEnterTransitionDidFinish      appendFinishLayerNum");
#endif
		((LoadingLayer *)loadingLayer)->appendFinishLayerNum(1);
	}
	else
	{
#ifdef								BIG_GATE_DEBUG
		CCLOG("BigGateMenu::onEnterTransitionDidFinish      startSelf");
#endif
		startSelf();
	}
}

void BigGateMenu::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);
	CCLayer::onExit();
}

BigGateMenu::~BigGateMenu(void)
{
	CCObject * p;
	CC_SAFE_RELEASE(pointIndexSprite);

	CCARRAY_FOREACH(pointSprites, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CCARRAY_FOREACH(selectGateSprites, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CCARRAY_FOREACH(selectFrameSprites, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CCARRAY_FOREACH(selectSuoSprites, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CCARRAY_FOREACH(gateSprites, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CCARRAY_FOREACH(gateFrameSprites, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CCARRAY_FOREACH(gateTitleSprites, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CCARRAY_FOREACH(gateSuoSprites, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CC_SAFE_RELEASE_NULL(mAnimationManager);

	CCLOG("BigGateMenu::~BigGateMenu");
}

void BigGateMenu::startSelf(void)
{

#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::startSelf 1");
#endif
	setVisible(true);
	isBackGround = false;
#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::startSelf 2");
#endif
	mAnimationManager->runAnimationsForSequenceNamed("zc");
	isDoAction = true;
#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::startSelf 3");
#endif
}

void BigGateMenu::setLoadingLayer(cocos2d::CCLayer * _layer)
{
#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::setLoadingLayer   %d", _layer);
#endif
	loadingLayer = _layer;
}

void BigGateMenu::onEnter(void)
{
#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::onEnter");
#endif
	CCLayer::onEnter();

	Player::getInstance()->getMusicControl()->playOtherBackGround();
	// 初始化当前关卡的情况
	isSelectMyButton = false;

	selectGateSprites = new CCArray();
	selectFrameSprites = new CCArray();
	gateTitleSprites = new CCArray();
	gateSprites = new CCArray();
	gateFrameSprites = new CCArray();
	pointSprites = new CCArray();
	selectSuoSprites = new CCArray();// 框的形象
	gateSuoSprites = new CCArray();


#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::onEnter         1");
#endif

	// 添加选大关的显示  按照大关顺序来  和  框的形态
	if (Player::getInstance()->getMapOpenStatusByMapId(BIG_GATE_TYPE_BAOXIANGGUO))
	{
		gateSprites->addObject(CCSprite::create("xuandaguan/tu2.png"));
		gateFrameSprites->addObject(CCSprite::create("xuandaguan/kuang.png"));
		gateSuoSprites->addObject(CCInteger::create(1));
	}
	else
	{
		CCLOG("BigGateMenu::onEnter    error baoxiangguo is not open!");
	}

#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::onEnter         2");
#endif
	if (Player::getInstance()->getMapOpenStatusByMapId(BIG_GATE_TYPE_TONGYIANHE))
	{
		gateSprites->addObject(CCSprite::create("xuandaguan/tu3.png"));
		gateFrameSprites->addObject(CCSprite::create("xuandaguan/kuang.png"));
		gateSuoSprites->addObject(CCInteger::create(1));
	}
	else
	{
		gateSprites->addObject(CCSprite::create("xuandaguan/tu3.png"));
		//gateSprites->addObject(CCSprite::create("xuandaguan/tu7.png"));
		gateFrameSprites->addObject(CCSprite::create("xuandaguan/kuang.png"));
		gateSuoSprites->addObject(CCInteger::create(0));
	}

#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::onEnter         3");
#endif
	if (Player::getInstance()->getMapOpenStatusByMapId(BIG_GATE_TYPE_NVERGUO))
	{
		gateSprites->addObject(CCSprite::create("xuandaguan/tu4.png"));
		gateFrameSprites->addObject(CCSprite::create("xuandaguan/kuang.png"));
		gateSuoSprites->addObject(CCInteger::create(1));
	}
	else
	{
		gateSprites->addObject(CCSprite::create("xuandaguan/tu4.png"));
		//gateSprites->addObject(CCSprite::create("xuandaguan/tu8.png"));
		gateFrameSprites->addObject(CCSprite::create("xuandaguan/kuang.png"));
		gateSuoSprites->addObject(CCInteger::create(0));
	}

#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::onEnter         4");
#endif
	if (Player::getInstance()->getMapOpenStatusByMapId(BIG_GATE_TYPE_HUOYANSHAN))
	{
		gateSprites->addObject(CCSprite::create("xuandaguan/tu1.png"));
		gateFrameSprites->addObject(CCSprite::create("xuandaguan/kuang.png"));
		gateSuoSprites->addObject(CCInteger::create(1));
	}
	else
	{
		gateSprites->addObject(CCSprite::create("xuandaguan/tu1.png"));
		//gateSprites->addObject(CCSprite::create("xuandaguan/tu6.png"));
		gateFrameSprites->addObject(CCSprite::create("xuandaguan/kuang.png"));
		gateSuoSprites->addObject(CCInteger::create(0));
	}

#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::onEnter         5");
#endif
	if (Player::getInstance()->getMapOpenStatusByMapId(BIG_GATE_TYPE_LINGSHAN))
	{
		gateSprites->addObject(CCSprite::create("xuandaguan/tu5.png"));
		gateFrameSprites->addObject(CCSprite::create("xuandaguan/kuang.png"));
		gateSuoSprites->addObject(CCInteger::create(1));
	}
	else
	{
		gateSprites->addObject(CCSprite::create("xuandaguan/tu5.png"));
		//gateSprites->addObject(CCSprite::create("xuandaguan/tu9.png"));
		gateFrameSprites->addObject(CCSprite::create("xuandaguan/kuang.png"));
		gateSuoSprites->addObject(CCInteger::create(0));
	}


#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::onEnter         6");
#endif
	currPageIndex = BIG_GATE_TYPE_BAOXIANGGUO;
#ifndef										GOLDEN_MINER_2_NEW_GUIDE
	// 新手关
	gateSprites->addObject(CCSprite::create("xuandaguan/tu0.png"));
	gateFrameSprites->addObject(CCSprite::create("xuandaguan/kuang.png"));
	gateSuoSprites->addObject(CCInteger::create(1));
	if (Player::getInstance()->getGuideIsFrist())
	{
		currPageIndex = BIG_GATE_TYPE_GUIDE;
		Player::getInstance()->setGuideIsFrist(false);
	}
	else
	{
		currPageIndex = Player::getInstance()->getLastMapId() % BIG_GATE_TYPE_GUIDE;
	}
#else	
	currPageIndex = Player::getInstance()->getLastMapId() % BIG_GATE_TYPE_GUIDE;

	if (currPageIndex < BIG_GATE_TYPE_BAOXIANGGUO || currPageIndex > BIG_GATE_TYPE_LINGSHAN)
	{
		CCLOG("BigGateMenu  !!  %d",currPageIndex);
		currPageIndex = BIG_GATE_TYPE_BAOXIANGGUO;
	}

#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu  %d",currPageIndex);
#endif
#endif



#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::onEnter        8");
#endif
	// 添加选大关的标题
	gateTitleSprites->addObject(CCSprite::create("xuandaguan/baoxiang.png"));
	gateTitleSprites->addObject(CCSprite::create("xuandaguan/tongtianhe.png"));
	gateTitleSprites->addObject(CCSprite::create("xuandaguan/nverguo.png"));
	gateTitleSprites->addObject(CCSprite::create("xuandaguan/huoyanshan.png"));
	gateTitleSprites->addObject(CCSprite::create("xuandaguan/lingshan.png"));
#ifndef										GOLDEN_MINER_2_NEW_GUIDE
	//gateTitleSprites->addObject(CCSprite::create("xuandaguan/xinshouguan.png"));// 新手
	gateTitleSprites->addObject(CCSprite::create("xuandaguan/shilian.png"));// 新手
#endif

	m_touchMove = false;

	for (int i = 0; i < 4; i++)
	{
#ifdef								BIG_GATE_DEBUG
		CCLOG("BigGateMenu::onEnter         9      i = %d    gateFrameSprites->count() = %d ", i, gateFrameSprites->count());
#endif
		selectFrameSprites->addObject(gateFrameSprites->objectAtIndex((i + currPageIndex + gateFrameSprites->count()-1) % gateFrameSprites->count()));
		//getChildByTag(i+1)->addChild(CCSprite::create("xuandaguan/kuang.png"));
		getChildByTag(i+1)->addChild((CCSprite *)selectFrameSprites->objectAtIndex(i));
		selectGateSprites->addObject(gateSprites->objectAtIndex((i + currPageIndex + gateFrameSprites->count() - 1) % gateFrameSprites->count()));
		getChildByTag(i+1)->addChild((CCSprite *)selectGateSprites->objectAtIndex(i));
		selectSuoSprites->addObject(CCSprite::create("xuandaguan/suo.png"));
		if (((CCInteger *)gateSuoSprites->objectAtIndex((i + currPageIndex + gateFrameSprites->count()-1) % gateFrameSprites->count()))->getValue() == 1)
		{
			((CCSprite *)selectSuoSprites->lastObject())->setVisible(false);
		}
		((CCSprite *)selectSuoSprites->objectAtIndex(i))->setPosition(ccp(0, 12));
		((CCSprite *)selectGateSprites->objectAtIndex(i))->setPosition(ccp(-3, -3));
		getChildByTag(i+1)->addChild((CCSprite *)selectSuoSprites->lastObject(), 999);
		if (i == 1)
		{
			((CCSprite *)selectGateSprites->objectAtIndex(i))->setColor(ccWHITE);
			((CCSprite *)selectFrameSprites->objectAtIndex(i))->setColor(ccWHITE);
			((CCSprite *)selectSuoSprites->objectAtIndex(i))->setColor(ccWHITE);	
		}
		else
		{
			((CCSprite *)selectGateSprites->objectAtIndex(i))->setColor(myGrey);
			((CCSprite *)selectFrameSprites->objectAtIndex(i))->setColor(myGrey);
			((CCSprite *)selectSuoSprites->objectAtIndex(i))->setColor(myGrey);	
		}
	}

#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::onEnter         11    ");
#endif
	selectGateTitleSprites = (CCSprite *)gateTitleSprites->objectAtIndex(currPageIndex);
	getChildByTag(5)->addChild(selectGateTitleSprites);
#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::onEnter         12    ");
#endif

	for (int i = 0; i < gateFrameSprites->count(); i++)
	{
#ifdef								BIG_GATE_DEBUG
		CCLOG("BigGateMenu::onEnter         13    i = %d    gateFrameSprites->count() = %d ", i, gateFrameSprites->count());
#endif
		pointSprites->addObject(CCSprite::create("xuandaguan/dian2.png"));
		((CCSprite *)pointSprites->lastObject())->setPosition(ccp(400 - gateFrameSprites->count()*BIG_GATE_MENU_POINT_X/2 + i*BIG_GATE_MENU_POINT_X + BIG_GATE_MENU_POINT_X/2, BIG_GATE_MENU_POINT_Y));
		addChild((CCSprite *)pointSprites->lastObject());
	}
#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::onEnter         14    ");
#endif
	pointIndexSprite = CCSprite::create("xuandaguan/dian1.png");
	pointIndexSprite->retain();
	addChild(pointIndexSprite);
#ifdef								BIG_GATE_DEBUG
	CCLOG("BigGateMenu::onEnter         15    ");
#endif
	
	this->setTouchEnabled(true);
	setKeypadEnabled(true);
	schedule(schedule_selector(BigGateMenu::doAction), 0);
}

void BigGateMenu::setBackGround(bool _b)
{
	if (_b)
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

void BigGateMenu::reBackWithVisiable(void)
{
	setVisible(true);
	setBackGround(false);
}

void BigGateMenu::keyBackClicked(void)	
{
	onMenuItemBackClicked(NULL);
}


void BigGateMenu::doAction(float _f)
{
	if (myButton == NULL)
	{
		double _positionX = ((CCNode *)getChildByTag(2))->getPositionX();
		double _positionY = ((CCNode *)getChildByTag(2))->getPositionY();
		myButton = new cocos2d::CCRect(_positionX - ((CCSprite *)selectGateSprites->objectAtIndex(1))->getContentSize().width/2,
			_positionY - ((CCSprite *)selectGateSprites->objectAtIndex(1))->getContentSize().height/2,
			((CCSprite *)selectGateSprites->objectAtIndex(1))->getContentSize().width,
			 ((CCSprite *)selectGateSprites->objectAtIndex(1))->getContentSize().height);
	}

	pointIndexSprite->setPosition(((CCSprite *)pointSprites->objectAtIndex(currPageIndex))->getPosition());
}

SEL_MenuHandler BigGateMenu::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBack", BigGateMenu::onMenuItemBackClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnShop", BigGateMenu::onMenuItemShopClicked);

	return NULL;
}

SEL_CCControlHandler BigGateMenu::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;
}

bool BigGateMenu::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void BigGateMenu::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(BigGateMenu::doAnimationCompleted));
	CC_SAFE_RETAIN(mAnimationManager);
}

void BigGateMenu::doAnimationCompleted(void)
{
	isDoAction = false;

	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"zc") == 0)
	{	
		if (Player::getInstance()->getGuideSlipBigGate())
		{
			SlipGuide * slipGuide = (SlipGuide *)Global::getInstance()->s->getSlipGuideLayer(this, LAYER_ID_BIG_GATE_MAP);
			setBackGround(true);
			Global::getInstance()->s->addLayerToRunningScene(slipGuide);
		}
	}
	
}

void BigGateMenu::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	if (isBackGround)
	{
		return;
	}

	if (isDoAction)
	{
		return;
	}

	//此方法是cocos2d-x的标准操作，取touch集合第一个touch，将其位置转成opengl坐标，没办法，这些坐标太乱了，touch默认坐标是屏幕坐标，左上角为远点，cocos默认坐标是opengl坐标，左下角是原点。
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	m_touchBeginPos = touch->getLocation ();
	m_touchBeginPos = CCDirector::sharedDirector()->convertToGL( m_touchBeginPos );

	isSelectMyButton = false;
	if(myButton != NULL && Global::getInstance()->isInRect(myButton, m_touchBeginPos.x, 480 - m_touchBeginPos.y))
	{
		isSelectMyButton = true;
	}

#ifdef								BIG_GATE_DEBUG
	if (myButton == NULL)
	{
		CCLOG("BigGateMenu::ccTouchesBegan    myButton == NULL");
	}
#endif

	m_touchMove = false;
}

void BigGateMenu::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	if (isBackGround)
	{
		return;
	}

	if (isDoAction)
	{
		return;
	}

	m_touchMove = true;
}

void BigGateMenu::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	if (isBackGround)
	{
		return;
	}

	if (isDoAction)
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
			setCurrPageIndex(true);
		}
		else if ((m_touchEndPos.x - m_touchBeginPos.x) > 50)
		{
			setCurrPageIndex(false);
		}
		else
		{
			if(isSelectMyButton)
			{
				checkButtonEvent();
			}
		}
	}
	else
	{
		if(isSelectMyButton)
		{
			checkButtonEvent();
		}
	}
	m_touchMove = false;
}

void BigGateMenu::setCurrPageIndex(bool _isXiangZuo)
{
	if (_isXiangZuo)
	{
		currPageIndex++;
		currPageIndex = currPageIndex % gateSprites->count();
		setNodeBySelectIndex(_isXiangZuo);
		mAnimationManager->runAnimationsForSequenceNamed("xiangzuo");
		isDoAction = true;
	}
	else
	{
		currPageIndex--;
		currPageIndex = (currPageIndex + gateSprites->count()) % gateSprites->count();
		setNodeBySelectIndex(_isXiangZuo);
		mAnimationManager->runAnimationsForSequenceNamed("xiangyou");
		isDoAction = true;
	}
	getChildByTag(5)->removeChild(selectGateTitleSprites);
	selectGateTitleSprites = (CCSprite *)gateTitleSprites->objectAtIndex((1 + currPageIndex + gateFrameSprites->count()-1) % gateFrameSprites->count());
	getChildByTag(5)->addChild(selectGateTitleSprites);
}

void BigGateMenu::checkButtonEvent(void)
{
	if (Global::getInstance()->isInRect(myButton,
		m_touchEndPos.x,
		480 - m_touchEndPos.y))
	{
		Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
		LoadingLayer * p = NULL;
		CCLayer * p1 = NULL;
#ifndef								GOLDEN_MINER_2_NEW_GUIDE
		if(currPageIndex == (gateFrameSprites->count()-1))
		{
			p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
			p1 = Global::getInstance()->s->getGuideLayer(GUIDE_ID_GRAP, p);
			p->setNextLayer(LAYER_ID_GAMING, p1);
			((GameControl *)p1)->setLoadingLayer(p);

			//p->appendLoadingLayerNum(1);
			p->addLoadingLayer(0,p1);
			Global::getInstance()->s->replaceScene(p);
			Player::getInstance()->setGuideIsFrist(false);
		}
		else
		{
#endif
			if (Player::getInstance()->getMapOpenStatusByMapId(currPageIndex))
			{
				Player::getInstance()->setLastMapId(currPageIndex);
				Global::getInstance()->setSelectGateType(currPageIndex);

				//LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
				//CCLayer * p1 = Global::getInstance()->s->getSimleGateMenu(p);

				//p->addLoadingLayer(0,p1);
				//p->setNextLayer(LAYER_ID_SMILE_GATE_SCENCE, p1);

				//Global::getInstance()->s->replaceScene(p);
				//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getSimleGateMenu());

				Global::getInstance()->s->replaceScene(Global::getInstance()->s->getSimleGateMenu(NULL));
			}
			else
			{
				PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_BIG_GATE_MAP);
				setBackGround(true);
				//promptLayer->setForwardLayer(this);
				Global::getInstance()->s->addLayerToRunningScene(promptLayer);
				promptLayer->bigGateNotOpen();
			}
#ifndef								GOLDEN_MINER_2_NEW_GUIDE
		}
#endif
	}	
}

void BigGateMenu::reBackBackClicked(bool _b)
{
	setBackGround(false);
	if(_b)
	{
		// 返回首页面
		Global::getInstance()->s->removeLayerToRunningScene(this);

		LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
		CCLayer * p1 = Global::getInstance()->s->getMainLayer(p);

		p->addLoadingLayer(0,p1);
		p->setNextLayer(LAYER_ID_MAIN, p1);

		Global::getInstance()->s->replaceScene(p);
	}
}

void BigGateMenu::onMenuItemBackClicked(CCObject* pSender)
{
	if (isBackGround)
	{
		return;
	}

	if (isDoAction)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	
	PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_BIG_GATE_MAP);
	setBackGround(true);
	//promptLayer->setForwardLayer(this);
	Global::getInstance()->s->addLayerToRunningScene(promptLayer);
	promptLayer->isBack();

	//Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getMainLayer());
}

void BigGateMenu::onMenuItemShopClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	if (isDoAction)
	{
		return;
	}
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	setVisible(false);
	setBackGround(true);
	Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getShopLayer(NULL, this, LAYER_ID_BIG_GATE_MAP));
}

void BigGateMenu::setNodeBySelectIndex(bool _isXiangZuo)
{
	for (int i = 4; i > 0; i--)
	{// 移除node中的ccSprite
		getChildByTag(i)->removeChild((CCSprite *)selectGateSprites->lastObject());
		selectGateSprites->removeLastObject();
		getChildByTag(i)->removeChild((CCSprite *)selectFrameSprites->lastObject());
		selectFrameSprites->removeLastObject();
		//getChildByTag(i)->removeChild((CCSprite *)selectSuoSprites->objectAtIndex(i-1));
		((CCSprite *)selectSuoSprites->objectAtIndex(i-1))->setVisible(true);
	}

	for (int i = 0; i< 4; i++)
	{
		if (_isXiangZuo)
		{
			selectFrameSprites->addObject(gateFrameSprites->objectAtIndex((i + currPageIndex + gateSprites->count() - 2) % gateSprites->count()));
			selectGateSprites->addObject(gateSprites->objectAtIndex((i + currPageIndex + gateSprites->count() - 2) % gateSprites->count()));
			if (((CCInteger *)gateSuoSprites->objectAtIndex((i + currPageIndex + gateSprites->count() - 2) % gateSprites->count()))->getValue() == 1)
			{
				((CCSprite *)selectSuoSprites->objectAtIndex(i))->setVisible(false);
			}
		}
		else
		{
			if (i == 3)
			{
				selectFrameSprites->addObject(gateFrameSprites->objectAtIndex((gateSprites->count() - 1 + currPageIndex) % gateSprites->count()));
				selectGateSprites->addObject(gateSprites->objectAtIndex((gateSprites->count() - 1 + currPageIndex) % gateSprites->count()));
				if (((CCInteger *)gateSuoSprites->objectAtIndex((gateSprites->count() - 1 + currPageIndex) % gateSprites->count()))->getValue() == 1)
				{
					((CCSprite *)selectSuoSprites->objectAtIndex(i))->setVisible(false);
				}
			}
			else
			{
				selectFrameSprites->addObject(gateFrameSprites->objectAtIndex((i + currPageIndex) % gateSprites->count()));
				selectGateSprites->addObject(gateSprites->objectAtIndex((i + currPageIndex) % gateSprites->count()));
				if (((CCInteger *)gateSuoSprites->objectAtIndex((i + currPageIndex) % gateSprites->count()))->getValue() == 1)
				{
					((CCSprite *)selectSuoSprites->objectAtIndex(i))->setVisible(false);
				}
			}
		}
		getChildByTag(i+1)->addChild((CCSprite *)selectFrameSprites->objectAtIndex(i));
		getChildByTag(i+1)->addChild((CCSprite *)selectGateSprites->objectAtIndex(i));

		((CCSprite *)selectSuoSprites->objectAtIndex(i))->setPosition(ccp(0, 12));
		((CCSprite *)selectGateSprites->objectAtIndex(i))->setPosition(ccp(-3, -3));
		//getChildByTag(i+1)->addChild((CCSprite *)selectSuoSprites->objectAtIndex(i));
		if (i % 2 == 1)
		{
			((CCSprite *)selectGateSprites->objectAtIndex(i))->setColor(myGrey);
			((CCSprite *)selectFrameSprites->objectAtIndex(i))->setColor(myGrey);
			((CCSprite *)selectSuoSprites->objectAtIndex(i))->setColor(myGrey);			
		}
		else
		{
			((CCSprite *)selectGateSprites->objectAtIndex(i))->setColor(ccWHITE);
			((CCSprite *)selectFrameSprites->objectAtIndex(i))->setColor(ccWHITE);
			((CCSprite *)selectSuoSprites->objectAtIndex(i))->setColor(ccWHITE);		
		}

		if (_isXiangZuo)
		{
			if (((CCInteger *)gateSuoSprites->objectAtIndex((i + currPageIndex + gateSprites->count() - 2) % gateSprites->count()))->getValue() == 0)
			{
				((CCSprite *)selectGateSprites->objectAtIndex(i))->setColor(myGrey);	
				//((CCSprite *)selectSuoSprites->objectAtIndex(i))->setColor(myGrey);	
			}
		}
		else
		{
			if (i == 3)
			{
				if (((CCInteger *)gateSuoSprites->objectAtIndex((gateSprites->count() - 1 + currPageIndex) % gateSprites->count()))->getValue() == 0)
				{
					((CCSprite *)selectGateSprites->objectAtIndex(i))->setColor(myGrey);	
					//((CCSprite *)selectSuoSprites->objectAtIndex(i))->setColor(myGrey);	
				}
			}
			else
			{
				if (((CCInteger *)gateSuoSprites->objectAtIndex((i + currPageIndex) % gateSprites->count()))->getValue() == 0)
				{
					((CCSprite *)selectGateSprites->objectAtIndex(i))->setColor(myGrey);	
					//((CCSprite *)selectSuoSprites->objectAtIndex(i))->setColor(myGrey);	
				}
			}
		}
	}
}