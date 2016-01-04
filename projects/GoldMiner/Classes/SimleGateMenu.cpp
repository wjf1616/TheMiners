#include "SimleGateMenu.h"
#include "LoadingLayer.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "Player.h"
#include "PromptLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

//#define		SIMLE_GATE_HAVE_BESIDE_MOVE		

#define		HIDE_PETS_NUM												3
#define		HIDE_PETS_SCALE												0.6

#define		EACH_PAGE_ITEM_MUN											6

#define		SIMLE_GATE_MENU_POINT_Y										40
#define		SIMLE_GATE_MENU_POINT_X										30

static const ccColor4B myGrey4 = {0,0,0,200};

SimleGateMenu::SimleGateMenu(void)
	: mAnimationManager(NULL)
	,currPageIndex(1)
	,greyLayer(NULL)
	,loadingLayer(NULL)
	,isBackGround(false)
{
	selectSimleGateButtonIndex = -1;
}

void SimleGateMenu::onExit(void)
{
	setTouchEnabled(false);

	CCLayer::onExit();
}

SimleGateMenu::~SimleGateMenu(void)
{
	CCObject * p;
	CC_SAFE_RELEASE(pointIndexSprite);
	CCARRAY_FOREACH(pointSprites, p)
	{
		CC_SAFE_RELEASE(p);
	}
	CCARRAY_FOREACH(smileGateId, p)
	{
		CC_SAFE_RELEASE(p);
	}
	//CC_SAFE_DELETE(smileGateId);
	CCARRAY_FOREACH(smileGateIdOpen, p)
	{
		CC_SAFE_RELEASE(p);
	}
	//CC_SAFE_DELETE(smileGateIdOpen);
	CCARRAY_FOREACH(smileGateIdStar, p)
	{
		CC_SAFE_RELEASE(p);
	}
	//CC_SAFE_DELETE(smileGateIdStar);
	CCARRAY_FOREACH(gateNum, p)
	{
		CC_SAFE_RELEASE(p);
	}
	//CC_SAFE_DELETE(gateNum);
	CCARRAY_FOREACH(gateOpenItems, p)
	{
		CC_SAFE_RELEASE(p);
	}
	//CC_SAFE_DELETE(gateOpenItems);
	CCARRAY_FOREACH(gateCloseItems, p)
	{
		CC_SAFE_RELEASE(p);
	}
	//CC_SAFE_DELETE(gateCloseItems);
	CCARRAY_FOREACH(gateItemGetStars, p)
	{
		CC_SAFE_RELEASE(p);
	}
	//CC_SAFE_DELETE(gateItemGetStars);
	CCARRAY_FOREACH(gateItemUnGetStars, p)
	{
		CC_SAFE_RELEASE(p);
	}
	//CC_SAFE_DELETE(gateItemUnGetStars);
	CCARRAY_FOREACH(pageSprites, p)
	{
		CC_SAFE_RELEASE(p);
	}
	//CC_SAFE_DELETE(pageSprites);
	//CCARRAY_FOREACH(mButton, p)
	//{
	//	CC_SAFE_DELETE(p);
	//}
	//CC_SAFE_DELETE(mButton);
	//CCARRAY_FOREACH(hidePets, p)
	//{
	//	CC_SAFE_RELEASE(p);
	//}
	CC_SAFE_RELEASE_NULL(mAnimationManager);

	CCLOG("SimleGateMenu::~SimleGateMenu");
}

void SimleGateMenu::onEnterTransitionDidFinish(void)
{
	CCLayer::onEnterTransitionDidFinish();

	if (loadingLayer != NULL)
	{
		((LoadingLayer *)loadingLayer)->appendFinishLayerNum(1);
	}
	else
	{
		setVisible(true);
		isBackGround = false;
		mAnimationManager->runAnimationsForSequenceNamed("zc");
	}
}

void SimleGateMenu::onEnter(void)
{
	CCLayer::onEnter();

	setVisible(false);
	isBackGround = true;

	Player::getInstance()->getMusicControl()->playOtherBackGround();

	isFrist = true;

	// 初始化当前关卡的情况
	pointIndexSprite = CCSprite::create("xuandaguan/dian1.png");
	pointIndexSprite->retain();
	pointSprites = CCArray::create();
	pointSprites->retain();
	gateOpenItems = CCArray::create();
	gateOpenItems->retain();
	gateCloseItems = CCArray::create();
	gateCloseItems->retain();
	gateItemGetStars = CCArray::create();
	gateItemGetStars->retain();
	gateItemUnGetStars = CCArray::create();
	gateItemUnGetStars->retain();
	smileGateId = CCArray::create();
	smileGateId->retain();
	smileGateIdOpen = CCArray::create();
	smileGateIdOpen->retain();
	smileGateIdStar = CCArray::create();
	smileGateIdStar->retain();
	gateNum = CCArray::create();
	gateNum->retain();
	pageSprites = CCArray::create();
	pageSprites->retain();
	//hidePets = CCArray::create();
	//hidePets->retain();

	smileGateNum = Global::getInstance()->getSimleGateNumAndGateIdBySelectBigGateType(smileGateId);

	//isStartPosition = true;  注释的处理滑平需要
	pageNum = smileGateNum / 6;
	if (0 != smileGateNum % 6)
	{
		pageNum++;
	}	

	isInitRect = true;
	m_touchMove = false;

	initGateIdInformation();
	initItemSprite();
	getChildByTag(999)->getChildByTag(1)->setVisible(false);

	for(int i = 0; i < 6; i++)
	{
		float _x = ((CCSprite *)gateOpenItems->objectAtIndex(i))->getPositionX();
		float _y = ((CCSprite *)gateOpenItems->objectAtIndex(i))->getPositionX();
		float _w = ((CCSprite *)gateOpenItems->objectAtIndex(i))->getContentSize().width;
		float _h = ((CCSprite *)gateOpenItems->objectAtIndex(i))->getContentSize().height;
		mButton[i].setRect(_x - _w/2, _y - _h/2, _w, _h);
	}

	addChild(pointIndexSprite);
	schedule(schedule_selector(SimleGateMenu::doAction), 0);
	this->setTouchEnabled(true);
	setKeypadEnabled(true);
}

void SimleGateMenu::startSelf(void)
{
	setVisible(true);
	isBackGround = false;
	mAnimationManager->runAnimationsForSequenceNamed("zc");
}

void SimleGateMenu::setLoadingLayer(cocos2d::CCLayer * _layer)
{
	loadingLayer = _layer;
}


void SimleGateMenu::keyBackClicked(void)	
{
	onMenuItemBackClicked(NULL);
}

SEL_MenuHandler SimleGateMenu::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBack", SimleGateMenu::onMenuItemBackClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnNext", SimleGateMenu::onMenuItemNextClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnForward", SimleGateMenu::onMenuItemForwardClicked);

	return NULL;
}

SEL_CCControlHandler SimleGateMenu::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool SimleGateMenu::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void SimleGateMenu::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	//mAnimationManager->runAnimationsForSequenceNamed("zc");
	CC_SAFE_RETAIN(mAnimationManager);
}

void SimleGateMenu::onMenuItemBackClicked(cocos2d::CCObject *pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	//// 有loading的
	//LoadingLayer * _tmp;
	//CCLayer * _tmp1;
	//_tmp = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
	//_tmp1 = Global::getInstance()->s->getBigGateMenu(_tmp);

	//_tmp->setNextLayer(LAYER_ID_BIG_GATE_MAP, _tmp1);
	//_tmp->addLoadingLayer(0,_tmp1);


	//Global::getInstance()->s->replaceScene(_tmp);

	// 没有loading的
	CCLOG("SimleGateMenu::onMenuItemBackClicked");
	Global::getInstance()->s->replaceScene(Global::getInstance()->s->getBigGateMenu(NULL));

	//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getBigGateMenu());
}

void SimleGateMenu::onMenuItemNextClicked(cocos2d::CCObject *pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	setCurrPageIndex(true);
}

void SimleGateMenu::onMenuItemForwardClicked(cocos2d::CCObject *pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	setCurrPageIndex(false);
}

void SimleGateMenu::initGateIdInformation(void)
{
	// 通过关卡id获得是否开启和星级状态
	// test 就只是显示用
	currPageIndex = 1;

	for (int i = 0; i < smileGateNum; i++)
	{
		//if (i < 6)
		//{
		//	smileGateIdOpen->addObject(CCInteger::create(1));//new CCInteger(1));//
		//	smileGateIdStar->addObject(CCInteger::create(i%4));//new CCInteger(i%4));//
		//}
		//else
		//{
		//	smileGateIdOpen->addObject(CCInteger::create(0));//new CCInteger(0));//
		//}
		if (Player::getInstance()->getGateOpenStatusByGateId(((CCInteger *)smileGateId->objectAtIndex(i))->getValue()))
		{
			smileGateIdOpen->addObject(CCInteger::create(1));
			smileGateIdStar->addObject(CCInteger::create(Player::getInstance()->getGateLeverStatusByGateId(((CCInteger *)smileGateId->objectAtIndex(i))->getValue())));
		}
		else
		{
			smileGateIdOpen->addObject(CCInteger::create(0));
			smileGateIdStar->addObject(CCInteger::create(Player::getInstance()->getGateLeverStatusByGateId(((CCInteger *)smileGateId->objectAtIndex(i))->getValue())));
		}

		if (i %6 == 0)
		{
			pointSprites->addObject(CCSprite::create("xuandaguan/dian2.png"));
			((CCSprite *)pointSprites->lastObject())->setPosition(ccp(400 - pageNum*SIMLE_GATE_MENU_POINT_X/2 + i/6*SIMLE_GATE_MENU_POINT_X + SIMLE_GATE_MENU_POINT_X/2, SIMLE_GATE_MENU_POINT_Y));
			addChild((CCSprite *)pointSprites->lastObject());
		}
	}
	
	//initHidePets();
}

void SimleGateMenu::initItemSprite(void)
{
	for (int i = 0; i < 12; i++)
	{
		CCNode * _tmp = getChildByTag(i+1);
		gateOpenItems->addObject(CCSprite::create("xiaoguan/liang.png"));
		((CCSprite *)gateOpenItems->lastObject())->setVisible(false);
		_tmp->addChild((CCSprite *)gateOpenItems->lastObject());
		gateCloseItems->addObject(CCSprite::create("xiaoguan/suo.png"));
		((CCSprite *)gateCloseItems->lastObject())->setVisible(false);
		_tmp->addChild((CCSprite *)gateCloseItems->lastObject());

		char _s[32];
		sprintf(_s, "%d",(i + 1));
		gateNum->addObject(CCLabelAtlas::create(_s, "xiaoguan/shuzi.png", 23, 35, '0'));
		((CCLabelAtlas *)gateNum->lastObject())->setPosition(ccp(_tmp->getPositionX() - 10, _tmp->getPositionY() - 38));
		addChild((CCLabelAtlas *)gateNum->lastObject());
		for (int j = 0; j < 3; j++)
		{
			// 添加
			gateItemGetStars->addObject(CCSprite::create("xiaoguan/xing1.png"));
			((CCSprite *)gateItemGetStars->lastObject())->setPosition(ccp(_tmp->getPositionX() + (j - 1) * 40, _tmp->getPositionY() - 53));
			addChild((CCSprite *)gateItemGetStars->lastObject());
			//CCLOG("i = %d, j = %d, x = %f, y = %f",i,j,((CCSprite *)gateItemGetStars->lastObject())->getPositionX(),((CCSprite *)gateItemGetStars->lastObject())->getPositionY());
			gateItemUnGetStars->addObject(CCSprite::create("xiaoguan/xing2.png"));
			((CCSprite *)gateItemUnGetStars->lastObject())->setPosition(ccp(_tmp->getPositionX() + (j - 1) * 40, _tmp->getPositionY() - 53));
			addChild((CCSprite *)gateItemUnGetStars->lastObject());
		}
		if (((CCInteger *)smileGateIdOpen->objectAtIndex((currPageIndex - 1)*6 + i))->getValue() == 1)
		{
			((CCSprite *)gateOpenItems->objectAtIndex(i))->setVisible(true);
			((CCSprite *)gateCloseItems->objectAtIndex(i))->setVisible(false);
			int tmpStarNum = ((CCInteger *)smileGateIdStar->objectAtIndex((currPageIndex - 1)*6 + i))->getValue();
			for (int j = 0; j < 3; j++)
			{
				if (0 == tmpStarNum)
				{
					((CCSprite *)gateItemGetStars->objectAtIndex(i*3 + j))->setVisible(false);
					((CCSprite *)gateItemUnGetStars->objectAtIndex(i*3 + j))->setVisible(true);
				}
				else
				{
					((CCSprite *)gateItemGetStars->objectAtIndex(i*3 + j))->setVisible(true);
					((CCSprite *)gateItemUnGetStars->objectAtIndex(i*3 + j))->setVisible(false);
					tmpStarNum--;
				}
			}
		}
		else
		{
			((CCSprite *)gateOpenItems->objectAtIndex(i))->setVisible(false);
			((CCSprite *)gateCloseItems->objectAtIndex(i))->setVisible(true);
			((CCLabelAtlas *)gateNum->objectAtIndex(i))->setVisible(false);
			for (int j = 0; j < 3; j++)
			{
				((CCSprite *)gateItemGetStars->objectAtIndex(i*3 + j))->setVisible(false);
				((CCSprite *)gateItemUnGetStars->objectAtIndex(i*3 + j))->setVisible(false);
			}
		}
	}

	////页底显示
	//for (int i = 0; i < pageNum; i++)
	//{
	//	pageSprites->addObject(CCSprite::create("xiaoguan/"))
	//}
	
}

void SimleGateMenu::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
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
	
	selectSimleGateButtonIndex = -1;
	for(int i = 0; i < 6; i++)
	{
		if(Global::getInstance()->isInRect(&mButton[i], m_touchBeginPos.x, 480 - m_touchBeginPos.y))
		{
			selectSimleGateButtonIndex = i;
			break;
		}
	}

	m_touchMove = false;
}
void SimleGateMenu::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	if (isBackGround)
	{
		return;
	}

	m_touchMove = true;
}
void SimleGateMenu::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
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
			setCurrPageIndex(true);
		}
		else if ((m_touchEndPos.x - m_touchBeginPos.x) > 50)
		{
			setCurrPageIndex(false);
		}
		else
		{
			if(selectSimleGateButtonIndex != -1)
			{
				checkButtonEvent();
			}
		}
	}
	else
	{
		if(selectSimleGateButtonIndex != -1)
		{
			checkButtonEvent();
		}
	}
	m_touchMove = false;
}

void SimleGateMenu::doAction(float _f)
{
	float _pointX;
	float _pointY;
	//更新星星的位置
	for (int i = 0; i < 12; i++)
	{
		_pointX = ((CCNode *)getChildByTag(i+1))->getPositionX();
		_pointY = ((CCNode *)getChildByTag(i+1))->getPositionY();
		int _num = ((CCLabelAtlas *)gateNum->objectAtIndex(i))->getContentSize().width / 23;
		((CCSprite *)gateOpenItems->objectAtIndex(i))->setPosition(ccp(0, -27));
		((CCSprite *)gateCloseItems->objectAtIndex(i))->setPosition(ccp(0, -27));
		((CCLabelAtlas *)gateNum->objectAtIndex(i))->setPosition(ccp(_pointX - 10 - (_num - 1)*23/2, _pointY - 30));
		for (int j = 0; j < 3; j++)
		{
			((CCSprite *)gateItemGetStars->objectAtIndex(i * 3 + j))->setPosition(ccp(_pointX + (j - 1) * 40, _pointY - 45));
			((CCSprite *)gateItemUnGetStars->objectAtIndex(i * 3 + j))->setPosition(ccp(_pointX + (j - 1) * 40, _pointY - 45));
		}
	}
	if (isInitRect)
	{
		for(int i = 0; i < 6; i++)
		{
			float _x = ((CCNode *)getChildByTag(i+1))->getPositionX();
			float _y = ((CCNode *)getChildByTag(i+1))->getPositionY();
			float _w = ((CCSprite *)gateOpenItems->objectAtIndex(i))->getContentSize().width;
			float _h = ((CCSprite *)gateOpenItems->objectAtIndex(i))->getContentSize().height;
			mButton[i].setRect(_x - _w/2, _y - _h/2, _w, _h);
		}
		isInitRect = false;
	}

	pointIndexSprite->setPosition(((CCSprite *)pointSprites->objectAtIndex(currPageIndex - 1))->getPosition());
}

void SimleGateMenu::setCurrPageIndex(bool _isXiangZuo)
{
	if (_isXiangZuo)
	{
		if (currPageIndex != pageNum)
		{
			for (int i = 0; i < 12; i++)
			{
				char _s[32];
				sprintf(_s, "%d",(currPageIndex - 1)*6 + i + 1);
				gateNum->addObject(CCLabelAtlas::create(_s, "xiaoguan/shuzi.png", 23, 35, '0'));
				addChild((CCLabelAtlas *)gateNum->lastObject());
				gateNum->exchangeObjectAtIndex(i, gateNum->count()-1);
				removeChild((CCLabelAtlas *)gateNum->lastObject());
				gateNum->removeLastObject();
				if (((CCInteger *)smileGateIdOpen->objectAtIndex((currPageIndex - 1)*6 + i))->getValue() == 1)
				{
					((CCLabelAtlas *)gateNum->objectAtIndex(i))->setVisible(true);
					((CCSprite *)gateOpenItems->objectAtIndex(i))->setVisible(true);
					((CCSprite *)gateCloseItems->objectAtIndex(i))->setVisible(false);
					int tmpStarNum = ((CCInteger *)smileGateIdStar->objectAtIndex((currPageIndex - 1)*6 + i))->getValue();
					for (int j = 0; j < 3; j++)
					{
						if (0 == tmpStarNum)
						{
							((CCSprite *)gateItemGetStars->objectAtIndex(i*3 + j))->setVisible(false);
							((CCSprite *)gateItemUnGetStars->objectAtIndex(i*3 + j))->setVisible(true);
						}
						else
						{
							((CCSprite *)gateItemGetStars->objectAtIndex(i*3 + j))->setVisible(true);
							((CCSprite *)gateItemUnGetStars->objectAtIndex(i*3 + j))->setVisible(false);
							tmpStarNum--;
						}
					}
				}
				else
				{
					((CCLabelAtlas *)gateNum->objectAtIndex(i))->setVisible(false);
					((CCSprite *)gateOpenItems->objectAtIndex(i))->setVisible(false);
					((CCSprite *)gateCloseItems->objectAtIndex(i))->setVisible(true);
					for (int j = 0; j < 3; j++)
					{
						((CCSprite *)gateItemGetStars->objectAtIndex(i*3 + j))->setVisible(false);
						((CCSprite *)gateItemUnGetStars->objectAtIndex(i*3 + j))->setVisible(false);
					}
				}
			}

			mAnimationManager->runAnimationsForSequenceNamed("xiangzuo");
			currPageIndex++;
			if (currPageIndex == pageNum)
			{
				getChildByTag(999)->getChildByTag(2)->setVisible(false);
			}
			getChildByTag(999)->getChildByTag(1)->setVisible(true);
		}	
#ifdef								SIMLE_GATE_HAVE_BESIDE_MOVE
		else
		{
			mAnimationManager->runAnimationsForSequenceNamed("xiangyou1");
		}
#endif
	} 
	else
	{
		if (currPageIndex != 1)
		{
			for (int i = 0; i < 6; i++)
			{
				char _s[32];
				sprintf(_s, "%d",(currPageIndex - 1)*6 + i + 1);
				gateNum->addObject(CCLabelAtlas::create(_s, "xiaoguan/shuzi.png", 23, 35, '0'));
				addChild((CCLabelAtlas *)gateNum->lastObject());
				gateNum->exchangeObjectAtIndex(i, gateNum->count()-1);
				removeChild((CCLabelAtlas *)gateNum->lastObject());
				gateNum->removeLastObject();
				if (((CCInteger *)smileGateIdOpen->objectAtIndex((currPageIndex - 1)*6 + i))->getValue() == 1)
				{
					((CCLabelAtlas *)gateNum->objectAtIndex(i))->setVisible(true);
					((CCSprite *)gateOpenItems->objectAtIndex(i))->setVisible(true);
					((CCSprite *)gateCloseItems->objectAtIndex(i))->setVisible(false);
					int tmpStarNum = ((CCInteger *)smileGateIdStar->objectAtIndex((currPageIndex - 2)*6 + i))->getValue();
					for (int j = 0; j < 3; j++)
					{
						if (0 == tmpStarNum)
						{
							((CCSprite *)gateItemGetStars->objectAtIndex(i*3 + j))->setVisible(false);
							((CCSprite *)gateItemUnGetStars->objectAtIndex(i*3 + j))->setVisible(true);
						}
						else
						{
							((CCSprite *)gateItemGetStars->objectAtIndex(i*3 + j))->setVisible(true);
							((CCSprite *)gateItemUnGetStars->objectAtIndex(i*3 + j))->setVisible(false);
							tmpStarNum--;
						}
					}
				}
				else
				{
					((CCLabelAtlas *)gateNum->objectAtIndex(i))->setVisible(false);
					((CCSprite *)gateOpenItems->objectAtIndex(i))->setVisible(false);
					((CCSprite *)gateCloseItems->objectAtIndex(i))->setVisible(true);
					for (int j = 0; j < 3; j++)
					{
						((CCSprite *)gateItemGetStars->objectAtIndex(i*3 + j))->setVisible(false);
						((CCSprite *)gateItemUnGetStars->objectAtIndex(i*3 + j))->setVisible(false);
					}
				}
				sprintf(_s, "%d",(currPageIndex - 2)*6 + i + 1);
				gateNum->addObject(CCLabelAtlas::create(_s, "xiaoguan/shuzi.png", 23, 35, '0'));
				addChild((CCLabelAtlas *)gateNum->lastObject());
				gateNum->exchangeObjectAtIndex(i + 6, gateNum->count()-1);
				removeChild((CCLabelAtlas *)gateNum->lastObject());
				gateNum->removeLastObject();
				if (((CCInteger *)smileGateIdOpen->objectAtIndex((currPageIndex - 2)*6 + i))->getValue() == 1)
				{
					((CCLabelAtlas *)gateNum->objectAtIndex(i + 6))->setVisible(true);
					((CCSprite *)gateOpenItems->objectAtIndex(i + 6))->setVisible(true);
					((CCSprite *)gateCloseItems->objectAtIndex(i + 6))->setVisible(false);
					int tmpStarNum = ((CCInteger *)smileGateIdStar->objectAtIndex((currPageIndex - 2)*6 + i))->getValue();
					for (int j = 0; j < 3; j++)
					{
						if (0 == tmpStarNum)
						{
							((CCSprite *)gateItemGetStars->objectAtIndex((i + 6)*3 + j))->setVisible(false);
							((CCSprite *)gateItemUnGetStars->objectAtIndex((i + 6)*3 + j))->setVisible(true);
						}
						else
						{
							((CCSprite *)gateItemGetStars->objectAtIndex((i + 6)*3 + j))->setVisible(true);
							((CCSprite *)gateItemUnGetStars->objectAtIndex((i + 6)*3 + j))->setVisible(false);
							tmpStarNum--;
						}
					}
				}
				else
				{
					((CCLabelAtlas *)gateNum->objectAtIndex(i + 6))->setVisible(false);
					((CCSprite *)gateOpenItems->objectAtIndex(i + 6))->setVisible(false);
					((CCSprite *)gateCloseItems->objectAtIndex(i + 6))->setVisible(true);
					for (int j = 0; j < 3; j++)
					{
						((CCSprite *)gateItemGetStars->objectAtIndex((i + 6)*3 + j))->setVisible(false);
						((CCSprite *)gateItemUnGetStars->objectAtIndex((i + 6)*3 + j))->setVisible(false);
					}
				}
			}
			mAnimationManager->runAnimationsForSequenceNamed("xiangyou");
			currPageIndex--;
			if (currPageIndex == 1)
			{
				getChildByTag(999)->getChildByTag(1)->setVisible(false);
			}
			getChildByTag(999)->getChildByTag(2)->setVisible(true);
		}
#ifdef								SIMLE_GATE_HAVE_BESIDE_MOVE	
		else
		{
			if (isFrist)
			{	
				for (int i = 0; i < 6; i++)
				{
					char _s[32];
					sprintf(_s, "%d",(currPageIndex - 1)*6 + i + 1);
					gateNum->addObject(CCLabelAtlas::create(_s, "xiaoguan/shuzi.png", 23, 35, '0'));
					addChild((CCLabelAtlas *)gateNum->lastObject());
					gateNum->exchangeObjectAtIndex(i, gateNum->count()-1);
					removeChild((CCLabelAtlas *)gateNum->lastObject());
					gateNum->removeLastObject();
					if (((CCInteger *)smileGateIdOpen->objectAtIndex((currPageIndex - 1)*6 + i))->getValue() == 1)
					{
						((CCLabelAtlas *)gateNum->objectAtIndex(i))->setVisible(true);
						((CCSprite *)gateOpenItems->objectAtIndex(i))->setVisible(true);
						((CCSprite *)gateCloseItems->objectAtIndex(i))->setVisible(false);
						int tmpStarNum = ((CCInteger *)smileGateIdStar->objectAtIndex((currPageIndex - 1)*6 + i))->getValue();
						for (int j = 0; j < 3; j++)
						{
							if (0 == tmpStarNum)
							{
								((CCSprite *)gateItemGetStars->objectAtIndex(i*3 + j))->setVisible(false);
								((CCSprite *)gateItemUnGetStars->objectAtIndex(i*3 + j))->setVisible(true);
							}
							else
							{
								((CCSprite *)gateItemGetStars->objectAtIndex(i*3 + j))->setVisible(true);
								((CCSprite *)gateItemUnGetStars->objectAtIndex(i*3 + j))->setVisible(false);
								tmpStarNum--;
							}
						}
					}
					else
					{
						((CCLabelAtlas *)gateNum->objectAtIndex(i))->setVisible(false);
						((CCSprite *)gateOpenItems->objectAtIndex(i))->setVisible(false);
						((CCSprite *)gateCloseItems->objectAtIndex(i))->setVisible(true);
						for (int j = 0; j < 3; j++)
						{
							((CCSprite *)gateItemGetStars->objectAtIndex(i*3 + j))->setVisible(false);
							((CCSprite *)gateItemUnGetStars->objectAtIndex(i*3 + j))->setVisible(false);
						}
					}
					sprintf(_s, "%d",(currPageIndex - 1)*6 + i + 1);
					gateNum->addObject(CCLabelAtlas::create(_s, "xiaoguan/shuzi.png", 23, 35, '0'));
					addChild((CCLabelAtlas *)gateNum->lastObject());
					gateNum->exchangeObjectAtIndex(i + 6, gateNum->count()-1);
					removeChild((CCLabelAtlas *)gateNum->lastObject());
					gateNum->removeLastObject();
					if (((CCInteger *)smileGateIdOpen->objectAtIndex((currPageIndex - 1)*6 + i))->getValue() == 1)
					{
						((CCLabelAtlas *)gateNum->objectAtIndex(i + 6))->setVisible(true);
						((CCSprite *)gateOpenItems->objectAtIndex(i + 6))->setVisible(true);
						((CCSprite *)gateCloseItems->objectAtIndex(i + 6))->setVisible(false);
						int tmpStarNum = ((CCInteger *)smileGateIdStar->objectAtIndex((currPageIndex - 1)*6 + i))->getValue();
						for (int j = 0; j < 3; j++)
						{
							if (0 == tmpStarNum)
							{
								((CCSprite *)gateItemGetStars->objectAtIndex((i + 6)*3 + j))->setVisible(false);
								((CCSprite *)gateItemUnGetStars->objectAtIndex((i + 6)*3 + j))->setVisible(true);
							}
							else
							{
								((CCSprite *)gateItemGetStars->objectAtIndex((i + 6)*3 + j))->setVisible(true);
								((CCSprite *)gateItemUnGetStars->objectAtIndex((i + 6)*3 + j))->setVisible(false);
								tmpStarNum--;
							}
						}
					}
					else
					{
						((CCLabelAtlas *)gateNum->objectAtIndex(i + 6))->setVisible(false);
						((CCSprite *)gateOpenItems->objectAtIndex(i + 6))->setVisible(false);
						((CCSprite *)gateCloseItems->objectAtIndex(i + 6))->setVisible(true);
						for (int j = 0; j < 3; j++)
						{
							((CCSprite *)gateItemGetStars->objectAtIndex((i + 6)*3 + j))->setVisible(false);
							((CCSprite *)gateItemUnGetStars->objectAtIndex((i + 6)*3 + j))->setVisible(false);
						}
					}
				}
			}
			mAnimationManager->runAnimationsForSequenceNamed("xiangzuo1");
		}
#endif
	}
	isFrist = false;
}

void SimleGateMenu::checkButtonEvent(void)
{
	if (Global::getInstance()->isInRect(&mButton[selectSimleGateButtonIndex],
		m_touchEndPos.x,
		480 - m_touchEndPos.y))
	{
		if(((CCInteger *)smileGateIdOpen->objectAtIndex((currPageIndex - 1)*6 + selectSimleGateButtonIndex))->getValue() == 1)
		{
			Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
			Global::getInstance()->setSelectGateId(((CCInteger *)smileGateId->objectAtIndex((currPageIndex - 1)*6 + selectSimleGateButtonIndex))->getValue());


			LoadingLayer * _tmp;
			CCLayer * _tmp1;
			_tmp = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
			//_tmp1 = Global::getInstance()->s->getSelectChallengeMenu(_tmp);

			//_tmp->setNextLayer(LAYER_ID_CHALLENGE, _tmp1);
			_tmp1 = Global::getInstance()->s->getShopLayer(_tmp, NULL, 0);

			_tmp->setNextLayer(LAYER_ID_SHOP, _tmp1);
			_tmp->addLoadingLayer(0,_tmp1);


			Global::getInstance()->s->replaceScene(_tmp);
			
			//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getSelectRoleAndPropMenu());
		}
		else
		{
			CCArray * tmp = CCArray::create();
			if (Global::getInstance()->getPetElementIdByHideGateId(((CCInteger *)smileGateId->objectAtIndex((currPageIndex - 1)*6 + selectSimleGateButtonIndex))->getValue(), tmp) != 0)
			{
				// 提示需要什么宠物
				PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_SMILE_GATE_SCENCE);
				setBackGround(true);
				promptLayer->setForwardLayer(this, LAYER_ID_SMILE_GATE_SCENCE);
				Global::getInstance()->s->addLayerToRunningScene(promptLayer);
				promptLayer->hideGateNotOpen(((CCInteger *)smileGateId->objectAtIndex((currPageIndex - 1)*6 + selectSimleGateButtonIndex))->getValue(),tmp);
			}
			else
			{
				PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_SMILE_GATE_SCENCE);
				setBackGround(true);
				promptLayer->setForwardLayer(this, LAYER_ID_SMILE_GATE_SCENCE);
				Global::getInstance()->s->addLayerToRunningScene(promptLayer);
				promptLayer->simleGateNotOpen();
			}
		}
	}	
}

void SimleGateMenu::setBackGround(bool _b)
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

//void SimleGateMenu::initHidePets(void)
//{
//	CCArray * _array  = NULL;
//	switch (Global::getInstance()->getSelectGateType())
//	{
//	case BIG_GATE_TYPE_BAOXIANGGUO:
//		_array = new CCArray();
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/jingxi.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array = new CCArray();
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/jingxi.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/yumian.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array = new CCArray();
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/jingxi.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/linggan.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/yumian.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		break;
//	case BIG_GATE_TYPE_TONGYIANHE:
//		_array = new CCArray();
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/linggan.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array = new CCArray();
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/jingxi.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/niumo.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array = new CCArray();
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/linggan.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/yumian.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/niumo.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		break;
//	case BIG_GATE_TYPE_NVERGUO:
//		_array = new CCArray();
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/yumian.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array = new CCArray();
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/linggan.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/yumian.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array = new CCArray();
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/jingxi.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/linggan.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/niumo.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		break;
//	case BIG_GATE_TYPE_HUOYANSHAN:
//		_array = new CCArray();
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/niumo.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array = new CCArray();
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/linggan.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/niumo.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array = new CCArray();
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/jingxi.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/yumian.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/niumo.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		break;
//	case BIG_GATE_TYPE_LINGSHAN:
//		_array = new CCArray();
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/jingxi.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/linggan.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array = new CCArray();
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/jingxi.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/linggan.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/yumian.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array = new CCArray();
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/jingxi.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/linggan.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/yumian.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		_array->addObject(CCSprite::create("xuanrenyemian/kuang.png"));
//		addChild((CCSprite *)_array->lastObject(), 10);
//		((CCSprite *)_array->lastObject())->addChild(CCSprite::create("xuanrenyemian/niumo.png"));
//		((CCSprite *)_array->lastObject())->setScale(HIDE_PETS_SCALE);
//		break;
//	default:
//		break;
//	}
//}


//1-6 6-7 固定顺序 显现位置差异的处理形态
//void SimleGateMenu::setCurrPageIndex(bool _isXiangZuo)
//{
//	if (_isXiangZuo)
//	{
//		if (currPageIndex != pageNum)
//		{
//			if (!isStartPosition)
//			{
//				for (int i = 0; i < 12; i++)
//				{
//					if (((CCInteger *)smileGateIdOpen->objectAtIndex((currPageIndex - 1)*6 + i))->getValue() == 1)
//					{
//						((CCSprite *)gateOpenItems->objectAtIndex(i))->setVisible(true);
//						((CCSprite *)gateCloseItems->objectAtIndex(i))->setVisible(false);
//						int tmpStarNum = ((CCInteger *)smileGateIdStar->objectAtIndex((currPageIndex - 1)*6 + i))->getValue();
//						for (int j = 0; j < 3; j++)
//						{
//							if (0 == tmpStarNum)
//							{
//								((CCSprite *)gateItemGetStars->objectAtIndex(i*3 + j))->setVisible(false);
//								((CCSprite *)gateItemUnGetStars->objectAtIndex(i*3 + j))->setVisible(true);
//							}
//							else
//							{
//								((CCSprite *)gateItemGetStars->objectAtIndex(i*3 + j))->setVisible(true);
//								((CCSprite *)gateItemUnGetStars->objectAtIndex(i*3 + j))->setVisible(false);
//								tmpStarNum--;
//							}
//						}
//					}
//					else
//					{
//						((CCSprite *)gateOpenItems->objectAtIndex(i))->setVisible(false);
//						((CCSprite *)gateCloseItems->objectAtIndex(i))->setVisible(true);
//					}
//				}
//			}
//			
//			mAnimationManager->runAnimations("xiangzuo");
//			currPageIndex++;
//			isStartPosition = false;
//		}		
//	} 
//	else
//	{
//		if (currPageIndex != 1)
//		{
//			if (isStartPosition)
//			{
//				for (int i = 0; i < 12; i++)
//				{
//					if (((CCInteger *)smileGateIdOpen->objectAtIndex((currPageIndex - 2)*6 + i))->getValue() == 1)
//					{
//						((CCSprite *)gateOpenItems->objectAtIndex(i))->setVisible(true);
//						((CCSprite *)gateCloseItems->objectAtIndex(i))->setVisible(false);
//						int tmpStarNum = ((CCInteger *)smileGateIdStar->objectAtIndex((currPageIndex - 2)*6 + i))->getValue();
//						for (int j = 0; j < 3; j++)
//						{
//							if (0 == tmpStarNum)
//							{
//								((CCSprite *)gateItemGetStars->objectAtIndex(i*3 + j))->setVisible(false);
//								((CCSprite *)gateItemUnGetStars->objectAtIndex(i*3 + j))->setVisible(true);
//							}
//							else
//							{
//								((CCSprite *)gateItemGetStars->objectAtIndex(i*3 + j))->setVisible(true);
//								((CCSprite *)gateItemUnGetStars->objectAtIndex(i*3 + j))->setVisible(false);
//								tmpStarNum--;
//							}
//						}
//					}
//					else
//					{
//						((CCSprite *)gateOpenItems->objectAtIndex(i))->setVisible(false);
//						((CCSprite *)gateCloseItems->objectAtIndex(i))->setVisible(true);
//					}
//				}
//			}
//			mAnimationManager->runAnimations("xiangyou");
//			currPageIndex--;
//			isStartPosition = true;
//		}
//	}
//}