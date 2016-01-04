#include "DrawLayer.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "PauseMenu.h"
#include "MainAppendLayer.h"
#include "Player.h"
#include "MainAppendLayer.h"
#include "GameControl.h"
#include "PromptLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define			DRAW_BOX_INDEX_COUNT				4
#define			DRAW_BOX_INDEX_TIME_CONTROL			0.5

#define			DRAW_STEP_TIME_CONTROL_1			(DRAW_BOX_INDEX_TIME_CONTROL + 1)				// 初始打开和展示时间
#define			DRAW_STEP_TIME_CONTROL_2			(DRAW_BOX_INDEX_TIME_CONTROL + 0.3)				// 关闭箱子 准备交换箱子
#define			DRAW_STEP_TIME_CONTROL_5			(DRAW_BOX_INDEX_TIME_CONTROL + 0.3)				// 选择箱子打开

#define			DRAW_CHECK_WIDTH					112
#define			DRAW_CHECK_HEIGHT					93

enum
{
	DRAW_BOX_TYPE_INGOT = 0,
	DRAW_BOX_TYPE_FOOD,
	DRAW_BOX_TYPE_GRENADE,
	DRAW_BOX_TYPE_MOONLIGHT,
	DRAW_BOX_TYPE_VIGOROUSLY_PILL,
	DRAW_BOX_TYPE_COUNT
};

static const ccColor4B myGrey4 = {0,0,0,200};

DrawLayer::DrawLayer(void)
	: mAnimationManager(NULL)
{
	isBackGround = false;
	drawCount = 0;
	timeCount = 0.0;
	step = -1;
	touchIndex = -1;
	boxs = NULL;
	awardImage = NULL;
	isTimeCount = false;
	costImage = NULL;
	costNum = NULL;
	mSystem = NULL;
}

DrawLayer::~DrawLayer(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);

	CCObject * p = NULL;
	CCARRAY_FOREACH(boxs, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}

	CCLOG("DrawLayer::~DrawLayer");
}

void DrawLayer::onEnter(void)
{
	CCLayer::onEnter();
}

void DrawLayer::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);
	CCLayer::onExit();
}

SEL_MenuHandler DrawLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName)
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnOff", DrawLayer::onMenuItemOffClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnConfirm", DrawLayer::onMenuItemConfirmClicked);

	return NULL;
}

SEL_CCControlHandler DrawLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName)
{
	return NULL;
}

bool DrawLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void DrawLayer::setForwardLayer(cocos2d::CCLayer * _ccLayer)
{
	forwardLayer = _ccLayer;
}

void DrawLayer::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	CCSprite * information = CCSprite::create("choujiang/tishi.png");
	information->setPosition(ccp(-15, -30));
	getChildByTag(1)->getChildByTag(6)->addChild(information);
	initBoxs();
	upDateCost();
	getChildByTag(2)->setZOrder(999);
	greyLayer = CCLayerColor::create(myGrey4);
	greyLayer->setVisible(false);
	getChildByTag(2)->addChild(greyLayer, -1);
	mAnimationManager->runAnimationsForSequenceNamed("tanchu");
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(DrawLayer::doAnimationCompleted));
	CC_SAFE_RETAIN(mAnimationManager);
}

void DrawLayer::onMenuItemOffClicked(cocos2d::CCObject * pSender)
{
	if (step == 7)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	for(int i = 0; i < boxs->count(); i++)
	{
		((DrawBox *)boxs->objectAtIndex(i))->setVisible(false);
		getChildByTag(1)->getChildByTag(i+1)->setVisible(true);
	}

	mAnimationManager->runAnimationsForSequenceNamed("xiaoshi");
}

void DrawLayer::onMenuItemConfirmClicked(cocos2d::CCObject * pSender)
{
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	mAnimationManager->runAnimationsForSequenceNamed("xiaoshi2");
}

void DrawLayer::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"xiaoshi") == 0)
	{
		((GameControl *)forwardLayer)->finishDraw();
		Global::getInstance()->s->removeLayerToRunningScene(this);
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"xiaoshi2") == 0)
	{
		greyLayer->setVisible(false);
		upDateCost();
		if (drawCount < 5)
		{
			setStep(4);
		}
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"tanchu") == 0)
	{
		schedule(schedule_selector(DrawLayer::doAction), 0);
		setTouchEnabled(true);
		setStep(1);
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"dong") == 0)
	{
		setStep(4);
	}

}

void DrawLayer::doAction(float _f)
{
	if (isTimeCount)
	{
		timeCount += _f;
		for(int i = 0; i < boxs->count(); i++)
		{
			((DrawBox *)boxs->objectAtIndex(i))->doAction(_f);
		}
		if (timeCount > timeCheckCount)
		{
			setStep(step+1);
		}
	}
}

void DrawLayer::setStep(int _step)
{
	step = _step;
	timeCount = 0;
	DrawBox * tmp = NULL;
	switch(step)
	{
	case 1:
		// 弹出后的处理    打开箱子+展示
		isTimeCount = true;
		timeCheckCount = DRAW_STEP_TIME_CONTROL_1;
		for(int i = 0; i < boxs->count(); i++)
		{
			tmp = (DrawBox *)boxs->objectAtIndex(i);
			tmp->setPosition(getChildByTag(1)->getChildByTag(i+1)->getPosition());
			tmp->setVisible(true);
			tmp->openBox();
			((CCSprite *)getChildByTag(1)->getChildByTag(i+1))->setVisible(false);
		}
		break;
	case 2:
		// 关闭箱子 + 准备换箱子
		isTimeCount = true;
		timeCheckCount = DRAW_STEP_TIME_CONTROL_2;
		for(int i = 0; i < boxs->count(); i++)
		{
			tmp = (DrawBox *)boxs->objectAtIndex(i);
			tmp->closeBox();
		}
		break;
	case 3:
		// 换箱子
		isTimeCount = false;
		mAnimationManager->runAnimationsForSequenceNamed("dong");
		for(int j = 0; j < boxs->count(); j++)
		{
			for (int i = 0; i < boxs->count(); i++)
			{
				tmp = (DrawBox *)boxs->objectAtIndex(i);
				boxs->exchangeObjectAtIndex(i,rand()%boxs->count());
			}
		}
		for(int i = 0; i < boxs->count(); i++)
		{
			tmp = (DrawBox *)boxs->objectAtIndex(i);
			tmp->setPosition(getChildByTag(1)->getChildByTag(i+1)->getPosition());
			tmp->setVisible(false);
			((CCSprite *)getChildByTag(1)->getChildByTag(i+1))->setVisible(true);
		}
		break;
	case 4:
		// 检测箱子选择
		isTimeCount = false;
		touchIndex = -1;
		break;
	case 5:
		// 选择箱子后打开
		isTimeCount = true;
		timeCheckCount = DRAW_STEP_TIME_CONTROL_5;
		tmp = (DrawBox *)boxs->objectAtIndex(touchIndex);
		tmp->setVisible(true);
		tmp->openBox();
		if (mSystem != NULL)
		{
			removeChild(mSystem, true);
		}
		mSystem = CCParticleSystemQuad::create("lizitexiao/xiangzi2/xiangzi2.plist");//plist文件可以通过例子编辑器获得
		addChild(mSystem, 10086);
		mSystem->setPosition(tmp->getPosition());

		((CCSprite *)getChildByTag(1)->getChildByTag(touchIndex+1))->setVisible(false);		
		break;
	case 6:
		// 选择箱子打开后弹出提示
		isTimeCount = false;
		tmp = (DrawBox *)boxs->objectAtIndex(touchIndex);
		drawCount++;
		if (awardImage != NULL)
		{
			getChildByTag(2)->getChildByTag(1)->removeChild(awardImage, true);
		}
		awardImage = tmp->getAward();
		getChildByTag(2)->getChildByTag(1)->addChild(awardImage, 1);
		mAnimationManager->runAnimationsForSequenceNamed("tanchu2");
		greyLayer->setVisible(true);
		break;
	case 7:
		isTimeCount = false;
		break;
	default:
		break;
	}
}

void DrawLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	if (step != 4)
	{
		return;
	}

	//此方法是cocos2d-x的标准操作，取touch集合第一个touch，将其位置转成opengl坐标，没办法，这些坐标太乱了，touch默认坐标是屏幕坐标，左上角为远点，cocos默认坐标是opengl坐标，左下角是原点。
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	m_touchBeginPos = touch->getLocation ();
	m_touchBeginPos = CCDirector::sharedDirector()->convertToGL( m_touchBeginPos );

	touchIndex = -1;
	for(int i = 0; i < boxs->count(); i++)
	{
		if (!((DrawBox *)boxs->objectAtIndex(i))->getIsGetAward())
		{
			CCSprite * _sprite = (CCSprite *)getChildByTag(1)->getChildByTag(i + 1);
			CCRect * _tmp = new CCRect(
				_sprite->getPositionX() - DRAW_CHECK_WIDTH/2
				,_sprite->getPositionY() - DRAW_CHECK_HEIGHT/2
				,DRAW_CHECK_WIDTH
				,DRAW_CHECK_HEIGHT);
			
			CCLOG("i = %d, m_touchBeginPos.x = %f, m_touchBeginPos.x = %f, x = %f, y = %f, w = %f, h = %f", i,m_touchBeginPos.x,m_touchBeginPos.y, _tmp->getMinX(), _tmp->getMinY(), _tmp->getMaxX(), _tmp->getMaxY());

			if(Global::getInstance()->isInRect(_tmp, m_touchBeginPos.x, 480 - m_touchBeginPos.y))
			{
				touchIndex = i;
				break;
			}
		}
	}

	m_touchMove = false;
}

void DrawLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	if (step != 4)
	{
		return;
	}

	m_touchMove = true;
}

void DrawLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	if (step != 4)
	{
		return;
	}

	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	m_touchEndPos = touch->getLocation ();
	m_touchEndPos = CCDirector::sharedDirector()->convertToGL( m_touchEndPos );

	if (touchIndex != -1)
	{
		if(m_touchMove && (m_touchBeginPos.x - m_touchEndPos.x) > 50 && (m_touchEndPos.x - m_touchBeginPos.x) > 50)
		{
			CCLOG("end meijizhong");
		}
		else
		{
			CCSprite * _sprite = (CCSprite *)getChildByTag(1)->getChildByTag(touchIndex + 1);
			CCRect * _tmp = new CCRect(
				_sprite->getPositionX() - DRAW_CHECK_WIDTH/2
				,_sprite->getPositionY() - DRAW_CHECK_HEIGHT/2
				,DRAW_CHECK_WIDTH
				,DRAW_CHECK_HEIGHT);
			if(Global::getInstance()->isInRect(_tmp, m_touchBeginPos.x, 480 - m_touchBeginPos.y))
			{
				if (drawCount == 0)
				{
					setStep(5);
				}
				else
				{
					setStep(7);
					PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_DRAW);
					Global::getInstance()->s->addLayerToRunningScene(promptLayer);
					promptLayer->drawOpenCost(costNum->getString());
				}
			}
		}
	}

	m_touchMove = false;
}

void DrawLayer::promptFinish(bool _isDraw)
{
	isBackGround = false;
	if (_isDraw)
	{
		setStep(5);
	}
	else
	{
		setStep(4);
	}
}

void DrawLayer::initBoxs(void)
{
	boxs = new cocos2d::CCArray();
	boxs->retain();

	int _lever = 1;
	int _type = -1;
	// 初始化1级宝箱
	_type = rand()%DRAW_BOX_TYPE_COUNT;
	boxs->addObject(new DrawBox(_lever, _type));
	addChild((DrawBox *)boxs->lastObject(), 1);
	((DrawBox *)boxs->lastObject())->setVisible(false);
	_type = rand()%DRAW_BOX_TYPE_COUNT;
	boxs->addObject(new DrawBox(_lever, _type));
	addChild((DrawBox *)boxs->lastObject(), 1);
	((DrawBox *)boxs->lastObject())->setVisible(false);
	// 初始化2级宝箱
	_lever++;
	_type = rand()%DRAW_BOX_TYPE_COUNT;
	boxs->addObject(new DrawBox(_lever, _type));
	addChild((DrawBox *)boxs->lastObject(), 1);
	((DrawBox *)boxs->lastObject())->setVisible(false);
	_type = rand()%DRAW_BOX_TYPE_COUNT;
	boxs->addObject(new DrawBox(_lever, _type));
	addChild((DrawBox *)boxs->lastObject(), 1);
	((DrawBox *)boxs->lastObject())->setVisible(false);
	// 初始化3级宝箱
	_lever++;
	_type = rand()%DRAW_BOX_TYPE_COUNT;
	boxs->addObject(new DrawBox(_lever, _type));
	addChild((DrawBox *)boxs->lastObject(), 1);
	((DrawBox *)boxs->lastObject())->setVisible(false);
}

void DrawLayer::upDateCost(void)
{
	if (costNum == NULL)
	{
		getChildByTag(1)->getChildByTag(6)->removeChild(costImage, true);
	}
	else
	{
		getChildByTag(1)->getChildByTag(6)->removeChild(costNum, true);
	}
	char _s[24];
	switch(drawCount)
	{
	case 0:
		costImage = CCSprite::create("choujiang/mianfei.png");
		getChildByTag(1)->getChildByTag(6)->addChild(costImage);
		break;
	case 1:
		costImage = CCSprite::create("slsb/yuanbao.png");
		getChildByTag(1)->getChildByTag(6)->addChild(costImage);
		costImage->setPositionX(65);
		sprintf(_s, "%d", 10);
		costNum = CCLabelAtlas::create(_s, "choujiang/shuzi.png", 18, 25, '0');
		getChildByTag(1)->getChildByTag(6)->addChild(costNum);
		costNum->setPosition(ccp(-20, -15));
		break;
	case 2:
		sprintf(_s, "%d", 20);
		costNum = CCLabelAtlas::create(_s, "choujiang/shuzi.png", 18, 25, '0');
		getChildByTag(1)->getChildByTag(6)->addChild(costNum);
		costNum->setPosition(ccp(-20, -15));
		break;
	case 3:
		sprintf(_s, "%d", 50);
		costNum = CCLabelAtlas::create(_s, "choujiang/shuzi.png", 18, 25, '0');
		getChildByTag(1)->getChildByTag(6)->addChild(costNum);
		costNum->setPosition(ccp(-20, -15));
		break;
	case 4:
		sprintf(_s, "%d", 100);
		costNum = CCLabelAtlas::create(_s, "choujiang/shuzi.png", 18, 25, '0');
		getChildByTag(1)->getChildByTag(6)->addChild(costNum);
		costNum->setPosition(ccp(-20, -15));
		break;
	default:
		getChildByTag(1)->getChildByTag(7)->setVisible(false);
		getChildByTag(1)->getChildByTag(6)->removeChild(costImage, true);
		break;
	}
}


/**********************************************************************************
DrawBox
***********************************************************************************/
DrawBox::DrawBox(int _level, int _type)
{
	isGetAward = false;
	level = _level;
	type = _type;
	index = 0;
	status = 0;
	timeCount = 0;

	char _s[24];
	sprintf(_s, "choujiang/%d.png", type*3 + level); 
	awardImage = CCSprite::create(_s);
	boxImage = CCSprite::create("choujiang/xiangzi1.png");
	addChild(boxImage);
	addChild(awardImage);
	awardImage->setPosition(ccp(0,45));
	awardImage->setVisible(false);

	//boxImage->getContentSize()
	setContentSize(*new CCSize(112,93));

	autorelease();
}

DrawBox::~DrawBox(void)
{

}

int DrawBox::doAction(float _f)
{
	if (isGetAward)
	{
		return 0;
	}
	if (status == 1)
	{
		timeCount += _f;
		if (timeCount > DRAW_BOX_INDEX_TIME_CONTROL/DRAW_BOX_TYPE_COUNT)
		{
			timeCount = 0;
			index++;
			if (index == DRAW_BOX_INDEX_COUNT)
			{
				status = 0;
				return 1;
			}
			if (index == (DRAW_BOX_INDEX_COUNT-1))
			{
				awardImage->setVisible(true);
			}
			else
			{
				awardImage->setVisible(false);
			}
			setImageByIndex();
		}
	}
	else if (status == 2)
	{
		timeCount += _f;
		if (timeCount > DRAW_BOX_INDEX_TIME_CONTROL/DRAW_BOX_TYPE_COUNT)
		{
			timeCount = 0;
			index--;
			if (index == -1)
			{
				status = 0;
				return 2;
			}
			if (index == (DRAW_BOX_INDEX_COUNT-1))
			{
				awardImage->setVisible(true);
			}
			else
			{
				awardImage->setVisible(false);
			}
			setImageByIndex();
		}
	}

	return 0;
}

void DrawBox::openBox(void)
{
	status = 1;
	index = 0;
	timeCount = 0;
}

void DrawBox::closeBox(void)
{
	status = 2;
	timeCount = 0;
	index = DRAW_BOX_INDEX_COUNT - 1;
}

void DrawBox::setImageByIndex(void)
{
	CCTexture2D *pTexture;
	CCRect rect;
	char _s[48];
	sprintf(_s, "choujiang/xiangzi%d.png", index+1);

	pTexture = CCTextureCache::sharedTextureCache()->addImage(_s);
	if (pTexture)
	{
		rect = CCRectZero;
		rect.size = pTexture->getContentSize();
		boxImage->setTexture(pTexture);
		boxImage->setTextureRect(rect);
	}
}

bool DrawBox::getIsGetAward(void)
{
	return isGetAward;
}

cocos2d::CCSprite *  DrawBox::getAward(void)
{
	isGetAward = true;
	CCSprite * res = NULL;
	char _s[24];
	sprintf(_s, "choujiang/%d.png", type*3 + level); 
	res = CCSprite::create(_s);
	switch(type)
	{
	case DRAW_BOX_TYPE_INGOT:
		if (level == 1)
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_INGOT, 10);
			Player::getInstance()->savePropNum(PROP_TYPE_INGOT, 10);
		}
		else if (level == 2)
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_INGOT, 50);
			Player::getInstance()->savePropNum(PROP_TYPE_INGOT, 50);
		}
		else 
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_INGOT, 100);
			Player::getInstance()->savePropNum(PROP_TYPE_INGOT, 100);
		}
		break;
	case DRAW_BOX_TYPE_FOOD:
		if (level == 1)
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_FOOD, 1);
			Player::getInstance()->savePropNum(PROP_TYPE_FOOD, 1);
		}
		else if (level == 2)
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_FOOD, 3);
			Player::getInstance()->savePropNum(PROP_TYPE_FOOD, 3);
		}
		else 
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_FOOD, 5);
			Player::getInstance()->savePropNum(PROP_TYPE_FOOD, 5);
		}
		break;
	case DRAW_BOX_TYPE_GRENADE:
		if (level == 1)
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_GRENADE, 1);
			Player::getInstance()->savePropNum(PROP_TYPE_GRENADE, 1);
		}
		else if (level == 2)
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_GRENADE, 3);
			Player::getInstance()->savePropNum(PROP_TYPE_GRENADE, 3);
		}
		else 
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_GRENADE, 5);
			Player::getInstance()->savePropNum(PROP_TYPE_GRENADE, 5);
		}
		break;
	case DRAW_BOX_TYPE_MOONLIGHT:
		if (level == 1)
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_MOONLIGHT, 1);
			Player::getInstance()->savePropNum(PROP_TYPE_MOONLIGHT, 1);
		}
		else if (level == 2)
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_MOONLIGHT, 2);
			Player::getInstance()->savePropNum(PROP_TYPE_MOONLIGHT, 2);
		}
		else 
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_MOONLIGHT, 3);
			Player::getInstance()->savePropNum(PROP_TYPE_MOONLIGHT, 3);
		}
		break;
	case DRAW_BOX_TYPE_VIGOROUSLY_PILL:
		if (level == 1)
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_VIGOROUSLY_PILL, 1);
			Player::getInstance()->savePropNum(PROP_TYPE_VIGOROUSLY_PILL, 1);
		}
		else if (level == 2)
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_VIGOROUSLY_PILL, 2);
			Player::getInstance()->savePropNum(PROP_TYPE_VIGOROUSLY_PILL, 2);
		}
		else 
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_VIGOROUSLY_PILL, 3);
			Player::getInstance()->savePropNum(PROP_TYPE_VIGOROUSLY_PILL, 3);
		}
		break;
	default:
		break;
	}
	return res;
}