#include "PauseMenu.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "GameControl.h"
#include "LoadingLayer.h"
#include "PromptLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum
{
	PAUSEMENU_XIAOSHI_TYPE_SHOP = 0,
	PAUSEMENU_XIAOSHI_TYPE_MENU,
	PAUSEMENU_XIAOSHI_TYPE_REPLAY,
	PAUSEMENU_XIAOSHI_TYPE_CONTINUE,
	PAUSEMENU_XIAOSHI_TYPE_SET,
	PAUSEMENU_XIAOSHI_TYPE_HELP,
};

PauseMenu::PauseMenu(void)
	: mAnimationManager(NULL)
	,forwardLayer(NULL)
	,xiaoshiType(-1)
{
	isDoAction = false;
}

void PauseMenu::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

PauseMenu::~PauseMenu(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	CCLOG("PauseMenu::~PauseMenu");
}

SEL_MenuHandler PauseMenu::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnShop", PauseMenu::onMenuItemShopClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnMenu", PauseMenu::onMenuItemMenuClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnReplay", PauseMenu::onMenuItemReplayClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnContinue", PauseMenu::onMenuItemContinueClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnSet", PauseMenu::onMenuItemSetClicked);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnHelp", PauseMenu::onMenuItemHelpClicked);

	return NULL;
}

SEL_CCControlHandler PauseMenu::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool PauseMenu::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void PauseMenu::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(PauseMenu::doAnimationCompleted));
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
	setIsDoAction(true);//isDoAction = true;
	CC_SAFE_RETAIN(mAnimationManager);
}

void PauseMenu::setIsDoAction(bool _b)
{
	isDoAction = _b;
	((CCMenu *)getChildByTag(999))->setEnabled(!isDoAction);
}

void PauseMenu::setForwardLayer(cocos2d::CCLayer *_ccLayer)
{
	forwardLayer = _ccLayer;
	char _s[32];
	// 要区分是挑战模式还是其他模式
	if (Global::getInstance()->getChallengeLevel() == 0)
	{
		isChallenge = false;
		isGuide = false;
		if (((GameControl *)forwardLayer)->getCurrMapId() > 10)
		{
			isGuide = true;
			trySprite = CCSprite::create("zanting/shilian.png");
			getChildByTag(1)->addChild(trySprite);
			trySprite->setPositionX(-30);

			switch(((GameControl *)forwardLayer)->getCurrSceneId())
			{
			case 1:
				tryNum = CCSprite::create("zanting/1.png");
				getChildByTag(1)->addChild(tryNum);
				tryNum->setPositionX(60);
				break;
			case 2:
				tryNum = CCSprite::create("zanting/2.png");
				getChildByTag(1)->addChild(tryNum);
				tryNum->setPositionX(60);
				break;
			case 3:
				tryNum = CCSprite::create("zanting/3.png");
				getChildByTag(1)->addChild(tryNum);
				tryNum->setPositionX(60);
				break;
			case 4:
				tryNum = CCSprite::create("zanting/4.png");
				getChildByTag(1)->addChild(tryNum);
				tryNum->setPositionX(60);
				break;
			case 5:
				tryNum = CCSprite::create("zanting/5.png");
				getChildByTag(1)->addChild(tryNum);
				tryNum->setPositionX(60);
				break;
			case 6:
				tryNum = CCSprite::create("zanting/6.png");
				getChildByTag(1)->addChild(tryNum);
				tryNum->setPositionX(60);
				break;
			default:
				break;
			}
		}
		else
		{
			sprintf(_s, "%d",((GameControl *)forwardLayer)->getCurrMapId());
			currMapIdLabel = CCLabelAtlas::create(_s, "zanting/shuzi.png", 40, 55, '0');
			getChildByTag(1)->addChild(currMapIdLabel);

			int currSceneId = ((GameControl *)forwardLayer)->getCurrSceneId();
			sprintf(_s, "%d",currSceneId);
			currSceneIdLabel = CCLabelAtlas::create(_s, "zanting/shuzi.png", 40, 55, '0');
			getChildByTag(1)->addChild(currSceneIdLabel);

			hengGang = CCSprite::create("zanting/henxian.png");
			getChildByTag(1)->addChild(hengGang);

			currMapIdLabel->setPosition(ccp(- 77, - 25));

			currSceneIdLabelControl = 0;
			int _currSceneId = currSceneId;
			while(1)
			{
				_currSceneId = _currSceneId / 10;
				if (_currSceneId > 0)
				{
					currSceneIdLabelControl++;
				}
				else
				{
					break;
				}
			}
			currSceneIdLabel->setPosition(ccp( currSceneIdLabelControl*5 + 13,  - 25));
			hengGang->setPosition(ccp( - 15, 0));
		}
	}
	else
	{
		isChallenge = true;
		isGuide = false;

		level = CCSprite::create("zanting/dic.png");
		getChildByTag(1)->addChild(level);
		
		sprintf(_s, "%d",Global::getInstance()->getChallengeLevel());
		levelNum = CCLabelAtlas::create(_s, "zanting/shuzi.png", 40, 55, '0');
		getChildByTag(1)->addChild(levelNum);
		if (Global::getInstance()->getChallengeLevel() > 9)
		{
			levelNum->setPosition(ccp( -40, -30));
		}
		else
		{
			levelNum->setPosition(ccp( -18, -30));
		}
	}

	setKeypadEnabled(true);
	//schedule( schedule_selector(PauseMenu::doAction), 0);
}

void PauseMenu::keyBackClicked(void)	
{
	onMenuItemContinueClicked(NULL);
}

void PauseMenu::onMenuItemShopClicked(cocos2d::CCObject * pSender)
{
	if (isDoAction)
	{
		return;
	}

	setIsDoAction(true);//isDoAction = true;
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	doXiaoShiAnimation();
	xiaoshiType = PAUSEMENU_XIAOSHI_TYPE_SHOP;
}

void PauseMenu::onMenuItemMenuClicked(cocos2d::CCObject * pSender)
{
	if (isDoAction)
	{
		return;
	}

	setIsDoAction(true);//isDoAction = true;
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	//Player::getInstance()->getMusicControl()->stopLoopEffect();
	doXiaoShiAnimation();
	xiaoshiType = PAUSEMENU_XIAOSHI_TYPE_MENU;
}

void PauseMenu::onMenuItemReplayClicked(cocos2d::CCObject * pSender)
{
	if (isDoAction)
	{
		return;
	}

	setIsDoAction(true);//isDoAction = true;
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	//Player::getInstance()->getMusicControl()->stopLoopEffect();
	doXiaoShiAnimation();
	xiaoshiType = PAUSEMENU_XIAOSHI_TYPE_REPLAY;
}

void PauseMenu::onMenuItemContinueClicked(cocos2d::CCObject * pSender)
{
	if (isDoAction)
	{
		return;
	}

	setIsDoAction(true);//isDoAction = true;
	Player::getInstance()->getMusicControl()->recoverLoopEffect();
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	// 播背景音乐
	if(Global::getInstance()->getCurrGuideId() != -1)
	{
		switch (Global::getInstance()->getCurrGuideId())
		{
		case GUIDE_ID_PILL:
			Player::getInstance()->getMusicControl()->playGameBackGround(BIG_GATE_TYPE_BAOXIANGGUO);
			break;
		case GUIDE_ID_GRENADE:
			Player::getInstance()->getMusicControl()->playGameBackGround(BIG_GATE_TYPE_BAOXIANGGUO);
			break;
		case GUIDE_ID_MOONLIGHT:
			Player::getInstance()->getMusicControl()->playGameBackGround(BIG_GATE_TYPE_BAOXIANGGUO);
			break;
		case GUIDE_ID_ROLE_SKILL:
			Player::getInstance()->getMusicControl()->playGameBackGround(BIG_GATE_TYPE_LINGSHAN);
			break;
		case GUIDE_ID_JEWEIL_SKILL:
			Player::getInstance()->getMusicControl()->playGameBackGround(BIG_GATE_TYPE_HUOYANSHAN);
			break;
#ifdef									GOLDEN_MINER_2_NEW_GUIDE
		case GUIDE_ID_FRIST:
			Player::getInstance()->getMusicControl()->playGameBackGround(BIG_GATE_TYPE_BAOXIANGGUO);
			break;
#endif
		default:
			Player::getInstance()->getMusicControl()->playGameBackGround(BIG_GATE_TYPE_BAOXIANGGUO);
			break;
		}
	}
	else
	{
		Player::getInstance()->getMusicControl()->playGameBackGround(Global::getInstance()->getMapIdByGateId(Global::getInstance()->getSelectGateId()));
	}
	doXiaoShiAnimation();
	xiaoshiType = PAUSEMENU_XIAOSHI_TYPE_CONTINUE;
}

void PauseMenu::onMenuItemSetClicked(cocos2d::CCObject * pSender)
{
	if (isDoAction)
	{
		return;
	}

	setIsDoAction(true);//isDoAction = true;
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	doXiaoShiAnimation();
	xiaoshiType = PAUSEMENU_XIAOSHI_TYPE_SET;
}

void PauseMenu::onMenuItemHelpClicked(cocos2d::CCObject * pSender)
{	
	if (isDoAction)
	{
		return;
	}

	setIsDoAction(true);//isDoAction = true;
	Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);
	doXiaoShiAnimation();
	xiaoshiType = PAUSEMENU_XIAOSHI_TYPE_HELP;
}

void PauseMenu::doAnimationCompleted(void)
{
	setIsDoAction(false);//isDoAction = false;
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"xiaoshi") == 0)
	{	
		setIsDoAction(true);//isDoAction = true;
		switch(xiaoshiType)
		{
		case PAUSEMENU_XIAOSHI_TYPE_SHOP:
			setVisible(false);
			Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getShopLayer(NULL, this, LAYER_ID_GATE_PAUSE));
			break;
		case PAUSEMENU_XIAOSHI_TYPE_MENU:
			if (Global::getInstance()->getChallengeLevel() != 0)
			{
				// 提示挑战模式不能重玩
				PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_PAUSE);
				Global::getInstance()->s->addLayerToRunningScene(promptLayer);
				promptLayer->challengeGateOut();
			}
			else
			{
				if (Global::getInstance()->getCurrGuideId() != -1)
				{
					// 提示挑战模式不能重玩
					PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_PAUSE);
					Global::getInstance()->s->addLayerToRunningScene(promptLayer);
					promptLayer->isBack();
					//LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
					//CCLayer * p1 = Global::getInstance()->s->getBigGateMenu(p);

					//p->addLoadingLayer(0,p1);
					//p->setNextLayer(LAYER_ID_BIG_GATE_MAP, p1);

					//Global::getInstance()->s->replaceScene(p);

					//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getBigGateMenu());
					//Global::getInstance()->setCurrGuideId(-1);
				}
				else
				{
					// 提示挑战模式不能重玩
					PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_PAUSE);
					Global::getInstance()->s->addLayerToRunningScene(promptLayer);
					promptLayer->isBack();

					//LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
					//CCLayer * p1 = Global::getInstance()->s->getSimleGateMenu(p);

					//p->addLoadingLayer(0,p1);
					//p->setNextLayer(LAYER_ID_SMILE_GATE_SCENCE, p1);

					//Global::getInstance()->s->replaceScene(p);

					//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getSimleGateMenu());
				}
			}
			break;
		case PAUSEMENU_XIAOSHI_TYPE_REPLAY:
			if(Global::getInstance()->getCurrGuideId() != -1)
			{
				//重新运行当前引导

				// 有loading
				//LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
				//CCLayer * p1 = Global::getInstance()->s->getGuideLayer(Global::getInstance()->getCurrGuideId(), p);
				//((GameControl *)p1)->setLoadingLayer(p);
				////p->appendLoadingLayerNum(1);
				//p->addLoadingLayer(0,p1);
				//p->setNextLayer(LAYER_ID_GAMING, p1);

				//Global::getInstance()->s->replaceScene(p);
				////Global::getInstance()->s->addLayerToRunningScene(p1);

				// 没有loading的
				Global::getInstance()->s->replaceScene(Global::getInstance()->s->getGuideLayer(Global::getInstance()->getCurrGuideId(), NULL));

				//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getGuideLayer(Global::getInstance()->getCurrGuideId(), NULL));
			}
			else
			{
				if (Global::getInstance()->getChallengeLevel() != 0)
				{
					// 提示挑战模式不能重玩
					PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_PAUSE);
					Global::getInstance()->s->addLayerToRunningScene(promptLayer);
					promptLayer->challengeGateReplay();
				}
				else
				{
					// 提示挑战模式不能重玩
					PromptLayer * promptLayer = (PromptLayer *)Global::getInstance()->s->getPromptLayer(this, LAYER_ID_PAUSE);
					Global::getInstance()->s->addLayerToRunningScene(promptLayer);
					promptLayer->isReplay();
					//// loading 开始
					//Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

					//LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
					//CCLayer * p1 = Global::getInstance()->s->getShopLayer(p, NULL, 0);

					//p->addLoadingLayer(0,p1);
					//p->setNextLayer(LAYER_ID_SHOP, p1);

					//Global::getInstance()->s->replaceScene(p);

					//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getSelectRoleAndPropMenu());

					//// 直接刷
					////重新运行当前游戏
					////// 有loading的
					////LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
					////CCLayer * p1 = Global::getInstance()->s->getGameLayer(Global::getInstance()->getSelectGateId(), Global::getInstance()->getSelectRoleId(), p);
					////((GameControl *)p1)->setLoadingLayer(p);
					//////p->appendLoadingLayerNum(1);
					////p->addLoadingLayer(0,p1);
					////p->setNextLayer(LAYER_ID_GAMING, p1);

					////Global::getInstance()->s->replaceScene(p);
					//////Global::getInstance()->s->addLayerToRunningScene(p1);

					//// 没有loading的
					//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getGameLayer(Global::getInstance()->getSelectGateId(), Global::getInstance()->getSelectRoleId(), NULL));

					////Global::getInstance()->s->replaceScene(Global::getInstance()->s->getGameLayer(Global::getInstance()->getSelectGateId(), Global::getInstance()->getSelectRoleId(), NULL));
				}
			}
			break;
		case PAUSEMENU_XIAOSHI_TYPE_CONTINUE:
			Player::getInstance()->setGameLayerIsPause(false);
			((GameControl *)forwardLayer)->setBackGround(false);
			Global::getInstance()->s->removeLayerToRunningScene(this);
			break;
		case PAUSEMENU_XIAOSHI_TYPE_SET:
			Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getSettingMenu(this, LAYER_ID_GATE_PAUSE));
			break;
		case PAUSEMENU_XIAOSHI_TYPE_HELP:
			Global::getInstance()->s->addLayerToRunningScene(Global::getInstance()->s->getHalpLayer(this, LAYER_ID_GATE_PAUSE));
			break;
		default:
			break;
		}
	}
}

void PauseMenu::reBack2(bool _b)
{
	if (_b)
	{
		Player::getInstance()->getMusicControl()->stopLoopEffect();
		if (xiaoshiType == PAUSEMENU_XIAOSHI_TYPE_MENU)
		{	
			Player::getInstance()->setGameLayer(NULL);
			Player::getInstance()->setGameLayerIsPause(true);
			if(Global::getInstance()->getCurrGuideId() == -1)
			{
				if (Global::getInstance()->getChallengeLevel() != 0)
				{
					// 要回到主页面

					LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
					CCLayer * p1 = Global::getInstance()->s->getMainLayer(p);

					p->addLoadingLayer(0,p1);
					p->setNextLayer(LAYER_ID_MAIN, p1);

					Global::getInstance()->s->replaceScene(p);


					//Global::getInstance()->s->replaceScene(Global::getInstance()->s->getMainLayer());
					Global::getInstance()->setChallengeLevel(0);
				}
				else
				{
					// loading 开始
					Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

					LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
					CCLayer * p1 = Global::getInstance()->s->getSimleGateMenu(p);

					p->addLoadingLayer(0,p1);
					p->setNextLayer(LAYER_ID_SMILE_GATE_SCENCE, p1);

					Global::getInstance()->s->replaceScene(p);
				}
			}
			else
			{
				LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
				CCLayer * p1 = Global::getInstance()->s->getMainLayer(p);

				p->addLoadingLayer(0,p1);
				p->setNextLayer(LAYER_ID_MAIN, p1);

				Global::getInstance()->s->replaceScene(p);
				Global::getInstance()->setCurrGuideId(-1);
			}
		}
		else if (xiaoshiType == PAUSEMENU_XIAOSHI_TYPE_REPLAY)
		{
			Player::getInstance()->setGameLayer(NULL);
			Player::getInstance()->setGameLayerIsPause(true);
			if(Global::getInstance()->getCurrGuideId() == -1)
			{
				if (Global::getInstance()->getChallengeLevel() != 0)
				{
					// 开启挑战模式
					Global::getInstance()->setChallengeLevel(0);

					LoadingLayer * _tmp;
					CCLayer * _tmp1;
					_tmp = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
					_tmp1 = Global::getInstance()->s->getSelectChallengeMenu(_tmp);

					_tmp->setNextLayer(LAYER_ID_CHALLENGE, _tmp1);
					_tmp->addLoadingLayer(0,_tmp1);


					Global::getInstance()->s->replaceScene(_tmp);
				}
				else
				{
					// loading 开始
					Player::getInstance()->getMusicControl()->playEffect(MUSICCONTROL_EFFECT_ID_BUTTON);

					LoadingLayer * p = (LoadingLayer *)Global::getInstance()->s->getLoadingLayer();
					CCLayer * p1 = Global::getInstance()->s->getShopLayer(p, NULL, 0);

					p->addLoadingLayer(0,p1);
					p->setNextLayer(LAYER_ID_SHOP, p1);

					Global::getInstance()->s->replaceScene(p);
				}
			}
		}
	}
	else
	{
		reBack();
	}
}

void PauseMenu::reBack(void)
{
	mAnimationManager->runAnimationsForSequenceNamed("chuxian");
	setIsDoAction(true);//isDoAction = true;
	if (isChallenge)
	{
		level->setVisible(true);
		levelNum->setVisible(true);
	}
	else
	{
		if (isGuide)
		{
			trySprite->setVisible(true);
			tryNum->setVisible(true);
		}
		else
		{
			currMapIdLabel->setVisible(true);
			currSceneIdLabel->setVisible(true);
			hengGang->setVisible(true);
		}
	}
}

void PauseMenu::reBackWithVisiable(void)
{
	setVisible(true);
	reBack();
}

void PauseMenu::doAction(float _f)
{
	if (forwardLayer != NULL)
	{
		float scale = getChildByTag(1)->getScale();
		if (isChallenge)
		{
			level->setScale(scale);
			levelNum->setScale(scale);
			levelNum->setPosition(ccp(- 18*scale, - 30*scale));
		}
		else
		{
			if (isGuide)
			{
				trySprite->setScale(scale);
				trySprite->setPositionX(- 30*scale);
				tryNum->setScale(scale);
				tryNum->setPositionX(- 60*scale);
			}
			else
			{
				currMapIdLabel->setScale(scale);
				currSceneIdLabel->setScale(scale);
				hengGang->setScale(scale);
				currMapIdLabel->setPosition(ccp(- 77*scale, - 25*scale));
				currSceneIdLabel->setPosition(ccp((currSceneIdLabelControl*5 + 13)*scale,  - 25*scale));
				hengGang->setPosition(ccp( - 15*scale, 0));
			}
		}
	}
}

void PauseMenu::doXiaoShiAnimation(void)
{
	mAnimationManager->runAnimationsForSequenceNamed("xiaoshi");
	setIsDoAction(true);//isDoAction = true;
	if (isChallenge)
	{
		level->setVisible(false);
		levelNum->setVisible(false);
	}
	else
	{
		if (isGuide)
		{
			trySprite->setVisible(false);
			tryNum->setVisible(false);
		}
		else
		{
			hengGang->setVisible(false);
			currMapIdLabel->setVisible(false);
			currSceneIdLabel->setVisible(false);
		}
	}
}