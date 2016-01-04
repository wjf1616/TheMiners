#include "SelectChallenge.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "RoleInformation.h"
#include "Player.h"
#include "CartoonLayer.h"
#include "GameControl.h"
#include "LoadingLayer.h"
#include "PromptLayer.h"
#include "TemporaryPromptLayer.h"
#include "SlipGuide.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define			SelectChallenge_YUN_ASIDE						11	
#define			SelectChallenge_FRAME_ASIDE					111
#define			SelectChallenge_BUTTON_ASIDE					11
#define			SelectChallenge_YUN_MIDDLE					21	
#define			SelectChallenge_FRAME_MIDDLE					121
#define			SelectChallenge_BUTTON_MIDDLE					21

#define			SelectChallenge_BUTTON_SELECTED_UP			102
#define			SelectChallenge_BUTTON_UNSELECTED_DOWN		101


#define		SelectChallenge_POINT_Y										30
#define		SelectChallenge_POINT_X										30


static const ccColor3B myGrey={60,60,60};
static const ccColor4B myGrey4 = {0,0,0,200};

SelectChallenge::SelectChallenge(void)
	: mAnimationManager(NULL)
	,greyLayer(NULL)
	,isBackGround(false)
	,loadingLayer(NULL)
{
}


SelectChallenge::~SelectChallenge(void)
{
	CC_SAFE_RELEASE_NULL(ingotNum);// 道具选择按钮

	CCObject * p;
	CC_SAFE_RELEASE(pointIndexSprite);
	CCARRAY_FOREACH(selectPropId, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(pointPropSprites, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(currSelectPropName, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}
	CCARRAY_FOREACH(selectPropName, p)
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
	CCARRAY_FOREACH(currSelectPropFrameSprites, p)
	{
		CC_SAFE_RELEASE_NULL(p);
	}

	CC_SAFE_RELEASE_NULL(mAnimationManager);
	CCLOG("SelectChallenge::~SelectChallenge");
}

void SelectChallenge::onEnter(void)
{
	CCLayer::onEnter();

	setVisible(false);
	isBackGround = true;

	Player::getInstance()->getMusicControl()->playOtherBackGround();

	isFristPropPage = true;
	currPropIndex = 0;
	char _s[32];
	sprintf(_s, "%d",Player::getInstance()->getPropNum(PROP_TYPE_INGOT));
	ingotNum = CCLabelAtlas::create(_s, "xuanren/yuanbaoshuzi.png", 18, 26, '0');
	CC_SAFE_RETAIN(ingotNum);
	addChild(ingotNum, 998);

	currSelectSprites = new CCArray();
	selectPropSprites = new CCArray();

	// 道具界面
	currSelectPropFrameSprites = new cocos2d::CCArray();
	currSelectPropName = new cocos2d::CCArray();
	currSelectSprites = new cocos2d::CCArray();
	selectPropName = new CCArray();
	pointPropSprites = new cocos2d::CCArray();
	selectPropId = new cocos2d::CCArray();

	initSprites();

	setNodeBySelectIndex(true);

	Global::getInstance()->setSelectRoleId(Player::getInstance()->getLastRoleSelect());

	schedule(schedule_selector(SelectChallenge::doAction), 0);

	setTouchEnabled(true);
	setKeypadEnabled(true);
}

void SelectChallenge::onEnterTransitionDidFinish(void)
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

void SelectChallenge::startSelf(void)
{
	setVisible(true);
	isBackGround = false;
	mAnimationManager->runAnimationsForSequenceNamed("daojuchuxian");
}

void SelectChallenge::setLoadingLayer(cocos2d::CCLayer * _layer)
{
	loadingLayer = _layer;

	if (loadingLayer == NULL)
	{
		setVisible(true);
	}
}

void SelectChallenge::keyBackClicked(void)	
{
	onMenuItemBackClicked(NULL);
}

void SelectChallenge::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

SEL_MenuHandler SelectChallenge::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnBack", SelectChallenge::onMenuItemBackClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnPlay", SelectChallenge::onMenuItemPlayClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnPlus", SelectChallenge::onMenuItemPlusClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnShop", SelectChallenge::onMenuItemShopClicked);

	return NULL;
}

SEL_CCControlHandler SelectChallenge::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool SelectChallenge::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void SelectChallenge::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
#ifndef										GOLDEN_MINER_2_BUY_INGOT	
	getChildByTag(999)->getChildByTag(89)->setVisible(false);
#endif
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(SelectChallenge::doAnimationCompleted));
	CC_SAFE_RETAIN(mAnimationManager);
}

void SelectChallenge::setBackGround(bool _b)
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


void SelectChallenge::onMenuItemShopClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	setBackGround(true);
	Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getShopLayer(NULL, this, LAYER_ID_CHALLENGE));

}

void SelectChallenge::reBackBackClicked(bool _b)
{
	setBackGround(false);
	if(_b)
	{
		// 返回首页面
		LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
		CCLayer * p1 = Global::getInstance()->s->getMainLayer(p);

		p->addLoadingLayer(0,p1);
		p->setNextLayer(LAYER_ID_MAIN, p1);

		Global::getInstance()->s->replaceScene(p);
	}
}

void SelectChallenge::onMenuItemBackClicked(cocos2d::CCObject * pSender)
{
	if (isBackGround)
	{
		return;
	}

	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_CHALLENGE);
	setBackGround(true);
	//promptLayer->setForwardLayer(this);
	Global::getInstance()->s->addLayerToRunningScene(promptLayer);
	promptLayer->isBack();
}

void SelectChallenge::onMenuItemPlayClicked(cocos2d::CCObject * pSender)
{
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

	if (costChallenge())
	{

		Global::getInstance()->setChallengeCountSum(0);
		Global::getInstance()->setChallengeLevel(1);
		Global::getInstance()->setChallengeTimeLevel(1);
		Global::getInstance()->setChallengeLevelType(((CCInteger *)selectPropId->objectAtIndex((currPropIndex + 1)%selectPropId->count()))->getValue());

		LoadingLayer * _tmp;
		CCLayer * _tmp1;
		_tmp = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();

		_tmp1 = Global::getInstance()->s->getShopLayer(_tmp, NULL, LAYER_ID_CHALLENGE);

		_tmp->setNextLayer(LAYER_ID_SHOP, _tmp1);
		_tmp->addLoadingLayer(0,_tmp1);


		Global::getInstance()->s->replaceScene(_tmp);
	}
	else
	{
		// 提示钱不够
		TemporaryPromptLayer * _layer = (TemporaryPromptLayer *)Global::getInstance()->s->getTempPromptLayer(this, LAYER_ID_CHALLENGE);
		_layer->doPromptByType(TEMP_PROMPT_INGOT_NOT_RICH);
		setBackGround(true);
		Global::getInstance()->s->addLayerToRunningScene(_layer);
	}

}

void SelectChallenge::onMenuItemPlusClicked(cocos2d::CCObject * pSender)
{
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
}
	
bool SelectChallenge::costChallenge(void)
{
	bool res = false;

	switch(((CCInteger *)selectPropId->objectAtIndex((currPropIndex + 1)%selectPropId->count()))->getValue())
	{
	case CHALLENGE_TYPE_IRON:
		if(Player::getInstance()->getPropNum(PROP_TYPE_INGOT) > 99)
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_INGOT, -100);
			res = true;
		}
		break;
	case CHALLENGE_TYPE_SILVER:
		if(Player::getInstance()->getPropNum(PROP_TYPE_INGOT) > 499)
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_INGOT, -500);
			res = true;
		}
		break;
	case CHALLENGE_TYPE_GOLD:
		if(Player::getInstance()->getPropNum(PROP_TYPE_INGOT) > 999)
		{
			Player::getInstance()->appendPropNum(PROP_TYPE_INGOT, -1000);
			res = true;
		}
		break;
	}
	return res;
}

void SelectChallenge::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
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

	m_touchMove = false;
}
void SelectChallenge::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	if (isBackGround)
	{
		return;
	}

	m_touchMove = true;
}
void SelectChallenge::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
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
				setCurrProp(true);
		}
		else if ((m_touchEndPos.x - m_touchBeginPos.x) > 50)
		{
				setCurrProp(false);
		}
	}
	m_touchMove = false;
}

void SelectChallenge::setCurrProp(bool _isXiangZuo)
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

void SelectChallenge::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"rwxiaoshi") == 0)
	{	
		mAnimationManager->runAnimationsForSequenceNamed("daojuchuxian");
	}
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"daojuchuxian") == 0)
	{	
		if (Player::getInstance()->getGuideSlipChallenge())
		{
			SlipGuide * slipGuide = (SlipGuide *)Global::getInstance()->s->getSlipGuideLayer(this, LAYER_ID_CHALLENGE);
			setBackGround(true);
			Global::getInstance()->s->addLayerToRunningScene(slipGuide);
		}
	}
}

void SelectChallenge::reBack(int _type, bool _b)
{
	setBackGround(false);
}

void SelectChallenge::reBackWithVisiable(void)
{
	setVisible(true);
	reBack(0, false);
}

void SelectChallenge::initSprites(void)
{
	// 道具界面			当界面选项不足所需的4个时候  要添加一个循环
	selectPropSprites->addObject(CCSprite::create("tiaozhanmoshi/lanse.png"));
	selectPropName->addObject(CCSprite::create("tiaozhanmoshi/5.png"));
	selectPropId->addObject(CCInteger::create(CHALLENGE_TYPE_SILVER));

	selectPropSprites->addObject(CCSprite::create("tiaozhanmoshi/jinse.png"));
	selectPropName->addObject(CCSprite::create("tiaozhanmoshi/10.png"));
	selectPropId->addObject(CCInteger::create(CHALLENGE_TYPE_GOLD));

	selectPropSprites->addObject(CCSprite::create("tiaozhanmoshi/huise.png"));
	selectPropName->addObject(CCSprite::create("tiaozhanmoshi/1.png"));
	selectPropId->addObject(CCInteger::create(CHALLENGE_TYPE_IRON));

	selectPropSprites->addObject(CCSprite::create("tiaozhanmoshi/lanse.png"));
	selectPropName->addObject(CCSprite::create("tiaozhanmoshi/5.png"));
	selectPropId->addObject(CCInteger::create(CHALLENGE_TYPE_SILVER));

	selectPropSprites->addObject(CCSprite::create("tiaozhanmoshi/jinse.png"));
	selectPropName->addObject(CCSprite::create("tiaozhanmoshi/10.png"));
	selectPropId->addObject(CCInteger::create(CHALLENGE_TYPE_GOLD));

	selectPropSprites->addObject(CCSprite::create("tiaozhanmoshi/huise.png"));
	selectPropName->addObject(CCSprite::create("tiaozhanmoshi/1.png"));
	selectPropId->addObject(CCInteger::create(CHALLENGE_TYPE_IRON));
	// 添加道具点点
	for (int i = 0; i < 3; i++)
	{
		pointPropSprites->addObject(CCSprite::create("xuandaguan/dian2.png"));
		((CCSprite *)pointPropSprites->lastObject())->setPosition(ccp(400 - 3*SelectChallenge_POINT_X/2 + i*SelectChallenge_POINT_X + SelectChallenge_POINT_X/2, SelectChallenge_POINT_Y));
		addChild((CCSprite *)pointPropSprites->lastObject());
	}
	// 亮点点
	pointIndexSprite = CCSprite::create("xuandaguan/dian1.png");
	pointIndexSprite->retain();
	addChild(pointIndexSprite,998);

	for (int i = 0; i< 4; i++)
	{
		currSelectPropName->addObject((CCSprite *)selectPropName->objectAtIndex(i));

		currSelectSprites->addObject(selectPropSprites->objectAtIndex((i + currPropIndex) % selectPropSprites->count()));
		currSelectPropFrameSprites->addObject(CCSprite::create("tiaozhanmoshi/kuang.png"));
		getChildByTag(i+1)->addChild((CCSprite *)currSelectSprites->objectAtIndex(i));
		addChild((CCSprite *)currSelectPropName->objectAtIndex(i));
		getChildByTag(i+1)->addChild((CCSprite *)currSelectPropFrameSprites->objectAtIndex(i));
		//if (i % 2 == 0)
		//{
		//	((CCSprite *)currSelectSprites->objectAtIndex(i))->setColor(myGrey);
		//}
	}
}

void SelectChallenge::setNodeBySelectIndex(bool _isXiangZuo)
{
	
		for (int i = 4; i > 0; i--)
		{// 移除node中的ccSprite
			getChildByTag(i)->removeChild((CCSprite *)currSelectSprites->lastObject());
			currSelectSprites->removeLastObject();
			removeChild((CCSprite *)currSelectPropName->lastObject(),true);
			currSelectPropName->removeLastObject();
		}
		for (int i = 0; i< 4; i++)
		{
			if (_isXiangZuo)
			{
				currSelectSprites->addObject(selectPropSprites->objectAtIndex((i + currPropIndex) % selectPropSprites->count()));
				currSelectPropName->addObject(selectPropName->objectAtIndex((i + currPropIndex) % selectPropSprites->count()));
			}
			else
			{
				if (i == 3)
				{
					currSelectSprites->addObject(selectPropSprites->objectAtIndex((selectPropSprites->count() - 1 + currPropIndex) % selectPropSprites->count()));
					currSelectPropName->addObject(selectPropName->objectAtIndex((selectPropSprites->count() - 1 + currPropIndex) % selectPropSprites->count()));
				}
				else
				{
					currSelectSprites->addObject(selectPropSprites->objectAtIndex((i + currPropIndex) % selectPropSprites->count()));
					currSelectPropName->addObject(selectPropName->objectAtIndex((i + currPropIndex) % selectPropSprites->count()));
				}
			}
			getChildByTag(i+1)->addChild((CCSprite *)currSelectSprites->objectAtIndex(i));
			addChild((CCSprite *)currSelectPropName->objectAtIndex(i));
			if (isFristPropPage)
			{
				currButtonIndex = 2;
				if (i % 2 == 0)
				{
					((CCSprite *)currSelectSprites->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectPropName->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectPropFrameSprites->objectAtIndex(i))->setColor(myGrey);
				}
				else
				{
					((CCSprite *)currSelectSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectPropName->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectPropFrameSprites->objectAtIndex(i))->setColor(ccWHITE);
				}
			}
			else
			{
				if (i % 2 == 1)
				{
					((CCSprite *)currSelectSprites->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectPropName->objectAtIndex(i))->setColor(myGrey);
					((CCSprite *)currSelectPropFrameSprites->objectAtIndex(i))->setColor(myGrey);
				}
				else
				{
					((CCSprite *)currSelectSprites->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectPropName->objectAtIndex(i))->setColor(ccWHITE);
					((CCSprite *)currSelectPropFrameSprites->objectAtIndex(i))->setColor(ccWHITE);
				}
			}
		}
		if (isFristPropPage)
		{
			isFristPropPage = false;
		}
		getChildByTag(999)->setZOrder(100);
}

void SelectChallenge::doAction(float _f)
{
	for (int i = 0; i < 4; i++)
	{
		double _positionX = ((CCNode *)getChildByTag(i+1))->getPositionX();
		double _positionY = ((CCNode *)getChildByTag(i+1))->getPositionY();
		double _scale =  ((CCNode *)getChildByTag(i+1))->getScale();
		((CCSprite *)currSelectPropName->objectAtIndex(i))->setPosition(ccp(_positionX+2*_scale, _positionY));
		((CCSprite *)currSelectSprites->objectAtIndex(i))->setPosition(ccp(0, 100+40*_scale));

		((CCSprite *)currSelectPropName->objectAtIndex(i))->setScale(_scale);
		((CCSprite *)currSelectSprites->objectAtIndex(i))->setScale(_scale);
	}

	pointIndexSprite->setPosition(((CCSprite *)pointPropSprites->objectAtIndex(currPropIndex%pointPropSprites->count()))->getPosition());

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