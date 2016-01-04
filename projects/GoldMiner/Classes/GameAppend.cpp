#include "GameAppend.h"
#include "Global.h"
#include "GoldenMinerScene.h"
#include "GameControl.h"


USING_NS_CC;
USING_NS_CC_EXT;

GameAppend::GameAppend(void)
	:mAnimationManager(NULL)
	,texiaos(NULL)
{
	isCanTouch = false;
	isJewel = false;
	isIntroduce = false;
	timeCount = 0;
}


GameAppend::~GameAppend(void)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	if (texiaos != NULL)
	{
		CCObject * p;
		CCARRAY_FOREACH(texiaos, p)
		{
			CC_SAFE_RELEASE_NULL(p);
		}
	}

	CCLOG("GameAppend::~GameAppend");
}

void GameAppend::onEnter(void)
{
	CCLayer::onEnter();

	texiaos = NULL;
	isJewel = false;
	schedule( schedule_selector(GameAppend::doAction), 0);
}

void GameAppend::onExit(void)
{
	mAnimationManager->setAnimationCompletedCallback(NULL, NULL);

	CCLayer::onExit();
}

SEL_MenuHandler GameAppend::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "OnOff", GameAppend::onMenuItemOffClicked);
	return NULL;
}

cocos2d::SEL_CallFuncN GameAppend::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calFangShe1", GameAppend::calFangShe1);
	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "calFangShe2", GameAppend::calFangShe2);
}

SEL_CCControlHandler GameAppend::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

bool GameAppend::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAnimationManager", CCBAnimationManager *, this->mAnimationManager);

	return false;
}

void GameAppend::onMenuItemOffClicked(cocos2d::CCObject * pSender)
{
	((GameControl *)forwardLayer)->setBackGround(false);
	Global::getInstance()->s->removeLayerToRunningScene(this);
}

void GameAppend::calFangShe1(cocos2d::CCNode * pSender)
{
	float r = sqrt((0.5 - getChildByTag(11)->getAnchorPoint().x)*(0.5 - getChildByTag(11)->getAnchorPoint().x)*(getChildByTag(11)->getContentSize().width)*(getChildByTag(11)->getContentSize().width)
		+ (0.5 - getChildByTag(11)->getAnchorPoint().y)*(0.5 - getChildByTag(11)->getAnchorPoint().y)*(getChildByTag(11)->getContentSize().height)*(getChildByTag(11)->getContentSize().height));
	//粒子特效的移动
	for (int i = 0; i < 5; i++)
	{
		float _angle = atan2((0.5 - getChildByTag((i+1)*10 + 1)->getAnchorPoint().y), (0.5 - getChildByTag((i+1)*10 + 1)->getAnchorPoint().x));

		((CCParticleSystemQuad *)texiaos->objectAtIndex(i))->setPosition(ccp(getChildByTag((i+1)*10 + 1)->getPositionX() + r*cos(getChildByTag((i+1)*10 + 1)->getRotationX()/angleChange*pi + _angle), getChildByTag((i+1)*10 + 1)->getPositionY() + r*sin(getChildByTag((i+1)*10 + 1)->getRotationY()/angleChange*pi + _angle)));
		xx[i] = getChildByTag((i+1)*10 + 1)->getPositionX();
		yy[i] = getChildByTag((i+1)*10 + 1)->getPositionY();
	}
}

void GameAppend::calFangShe2(cocos2d::CCNode * pSender)
{
	CCParticleSystemQuad * p = CCParticleSystemQuad::create("lizitexiao/fangshe1/fangshe1.plist");
	addChild(p,1);
	p->setPosition(getChildByTag(91)->getPosition());
}

void GameAppend::doGuideInformation(int _guideId, int _step)
{
	introduceStep = _step;

	mAnimationManager->runAnimationsForSequenceNamed("duihuakuang1");
	isIntroduce = true;
	CCSprite * tmp;
	switch(_guideId)
	{
	case GUIDE_ID_PILL:
		if (introduceStep == 1)
		{
			getChildByTag(61)->addChild(CCSprite::create("yindao/zhuazhu.png"));
		}
		else if (introduceStep == 2)
		{
			tmp = CCSprite::create("yindao/shiyong.png");
			getChildByTag(61)->addChild(tmp);
			tmp->setPosition(ccp(0,20));
			tmp = CCSprite::create("yindao/dianji3.png");
			getChildByTag(61)->addChild(tmp);
			tmp->setPosition(ccp(0,-10));
		}
		break;
	case GUIDE_ID_GRENADE:
		if (introduceStep == 1)
		{
			getChildByTag(61)->addChild(CCSprite::create("yindao/dashit.png"));
		}
		else if (introduceStep == 2)
		{
			getChildByTag(61)->addChild(CCSprite::create("yindao/dianji3.png"));
		}
		break;
	case GUIDE_ID_MOONLIGHT:
		if (introduceStep == 1)
		{
			getChildByTag(61)->addChild(CCSprite::create("yindao/zhua.png"));
		}
		else if (introduceStep == 2)
		{
			getChildByTag(61)->addChild(CCSprite::create("yindao/dianji3.png"));
		}
		break;
	case GUIDE_ID_ROLE_SKILL:
		if (introduceStep == 1)
		{
			getChildByTag(61)->addChild(CCSprite::create("yindao/jiaose.png"));
		}
		else if (introduceStep == 2)
		{
			getChildByTag(61)->addChild(CCSprite::create("yindao/dianji4.png"));
		}
		break;
	case GUIDE_ID_JEWEIL_SKILL:
		if (introduceStep == 2)
		{
			getChildByTag(61)->addChild(CCSprite::create("yindao/dianji5.png"));
		}
		break;
	default:
		if (introduceStep == 1)
		{
			getChildByTag(61)->addChild(CCSprite::create("yindao/kuangqu.png"));
		}
		else if (introduceStep == 2)
		{
			getChildByTag(61)->addChild(CCSprite::create("yindao/dianjipingmu.png"));
		}
		break;
	}
	getChildByTag(61)->setPositionX(getChildByTag(61)->getPositionX() + 20);
	getChildByTag(61)->setPositionY(getChildByTag(61)->getPositionY() + 8);
	tmp = CCSprite::create("yindao/djjx1.png");
	tmp->setVisible(false);
	tmp->setPosition(ccp(110, -42));
	getChildByTag(61)->addChild(tmp,1,10086);
	tmp = CCSprite::create("yindao/djjx2.png");
	tmp->setPosition(ccp(110, -42));
	getChildByTag(61)->addChild(tmp,1,10087);
}

void GameAppend::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(mAnimationManager);
	mAnimationManager = pAnimationManager;
	mAnimationManager->setAnimationCompletedCallback(this, callfunc_selector(GameAppend::doAnimationCompleted));
	setTouchEnabled(true);
	CC_SAFE_RETAIN(mAnimationManager);
}

void GameAppend::setForwardLayer(cocos2d::CCLayer *_ccLayer)
{
	forwardLayer = _ccLayer;
}

void GameAppend::doAnimationCompleted(void)
{
	if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"zhuan") == 0)
	{	
		this->setVisible(false);
		for (int i = 0; i < 5; i++)
		{
			removeChild((CCParticleSystemQuad *)texiaos->objectAtIndex(i));
		}
		
		((GameControl *)forwardLayer)->finishJewelSkillEffect();
		((GameControl *)forwardLayer)->setBackGround(false);
		Global::getInstance()->s->removeLayerToRunningScene(this);
	}
	else if (strcmp(mAnimationManager->getLastCompletedSequenceName().c_str(),"duihuakuang1") == 0)
	{	
		isCanTouch = true;
	}
}

void GameAppend::doJewelSkillEffect(int _jewelSkillId)
{
	isCanTouch = true;
	// 播放转   还有粒子特效
	mAnimationManager->runAnimationsForSequenceNamed("zhuan");
	isJewel = true;
	texiaos = new cocos2d::CCArray();

	for (int i = 0; i < 5; i++)
	{
		texiaos->addObject(CCParticleSystemQuad::create("lizitexiao/gouzi1/gouzi1.plist"));
		addChild((CCParticleSystemQuad *)texiaos->objectAtIndex(i));
		((CCParticleSystemQuad *)texiaos->objectAtIndex(i))->setZOrder(-1);
	}
	switch(_jewelSkillId)
	{
	case SKILL_ID_JEWEL_DROP:
		getChildByTag(91)->addChild(CCSprite::create("youxi/quanpingtongqian.png"));
		break;
	case SKILL_ID_JEWEL_FIVE_HANGER:
		getChildByTag(91)->addChild(CCSprite::create("youxi/zhuagou.png"));
		break;
	case SKILL_ID_JEWEL_BALL:
		getChildByTag(91)->addChild(CCSprite::create("youxi/baoshitantan.png"));
		break;
	case SKILL_ID_JEWEL_MAGNET:
		getChildByTag(91)->addChild(CCSprite::create("youxi/xitieshi.png"));
		break;
	//case SKILL_ID_JEWEL_DIZZY:
	//	getChildByTag(91)->addChild(CCSprite::create("youxi/quanpingxuanyun.png"));
	//	break;
	//case SKILL_ID_JEWEL_GOURD:
	//	getChildByTag(91)->addChild(CCSprite::create("youxi/zijinhulu.png"));
	//	break;
	}
}

void GameAppend::doAction(float _f)
{
	if (isJewel && texiaos != NULL)
	{
		float r = sqrt((0.5 - getChildByTag(11)->getAnchorPoint().x)*(0.5 - getChildByTag(11)->getAnchorPoint().x)*(getChildByTag(11)->getContentSize().width)*(getChildByTag(11)->getContentSize().width)
			+ (0.5 - getChildByTag(11)->getAnchorPoint().y)*(0.5 - getChildByTag(11)->getAnchorPoint().y)*(getChildByTag(11)->getContentSize().height)*(getChildByTag(11)->getContentSize().height));
		//粒子特效的移动
		for (int i = 0; i < 5; i++)
		{
			float _angle = atan2((0.5 - getChildByTag((i+1)*10 + 1)->getAnchorPoint().y), (0.5 - getChildByTag((i+1)*10 + 1)->getAnchorPoint().x));
		
			if (getChildByTag((i+1)*10 + 1)->getRotation()==1440)
			{
				//((CCParticleSystemQuad *)texiaos->objectAtIndex(i))->setPosition(ccp(getChildByTag((i+1)*10 + 1)->getPositionX() + r*cos(getChildByTag((i+1)*10 + 1)->getRotationX()/angleChange*pi + _angle), getChildByTag((i+1)*10 + 1)->getPositionY() + r*sin(getChildByTag((i+1)*10 + 1)->getRotationY()/angleChange*pi + _angle)));
				//CCLOG("i = %d,x = %f, y = %f, ax = %f, ay = %f, sx =%f, sy = %f, angle = %f, sin = %f, cos = %f", i, getChildByTag((i+1)*10 + 1)->getPositionX() - xx[i], getChildByTag((i+1)*10 + 1)->getPositionY() - yy[i], getChildByTag((i+1)*10 + 1)->getPositionX(), getChildByTag((i+1)*10 + 1)->getPositionY(), ((CCParticleSystemQuad *)texiaos->objectAtIndex(i))->getPositionX(), ((CCParticleSystemQuad *)texiaos->objectAtIndex(i))->getPositionY(), _angle, sin(_angle), cos(_angle));
				((CCParticleSystemQuad *)texiaos->objectAtIndex(i))->setPositionX(((CCParticleSystemQuad *)texiaos->objectAtIndex(i))->getPositionX() + getChildByTag((i+1)*10 + 1)->getPositionX() - xx[i]);
				((CCParticleSystemQuad *)texiaos->objectAtIndex(i))->setPositionY(((CCParticleSystemQuad *)texiaos->objectAtIndex(i))->getPositionY() + getChildByTag((i+1)*10 + 1)->getPositionY() - yy[i]);
			}
			else
			{
				//xx[i] = getChildByTag((i+1)*10 + 1)->getPositionX();
				//yy[i] = getChildByTag((i+1)*10 + 1)->getPositionY();
				((CCParticleSystemQuad *)texiaos->objectAtIndex(i))->setPosition(ccp(getChildByTag((i+1)*10 + 1)->getPositionX() + r*cos(getChildByTag((i+1)*10 + 1)->getRotationX()/angleChange*pi + _angle), getChildByTag((i+1)*10 + 1)->getPositionY() + r*sin(getChildByTag((i+1)*10 + 1)->getRotationY()/angleChange*pi + _angle)));
				//CCLOG("i = %d,x = %f, y = %f, angle = %f", i, ((CCParticleSystemQuad *)texiaos->objectAtIndex(i))->getPositionX(), ((CCParticleSystemQuad *)texiaos->objectAtIndex(i))->getPositionY(), getChildByTag((i+1)*10 + 1)->getRotationX()/angleChange*pi + _angle);
			}
		}
	}	
	else if (isIntroduce)
	{
		timeCount += _f;
		if (timeCount > 0.3)
		{
			timeCount = 0;
			if (getChildByTag(61)->getChildByTag(10087)->isVisible())
			{
				getChildByTag(61)->getChildByTag(10087)->setVisible(false);
				getChildByTag(61)->getChildByTag(10086)->setVisible(true);
			}
			else
			{
				getChildByTag(61)->getChildByTag(10087)->setVisible(true);
				getChildByTag(61)->getChildByTag(10086)->setVisible(false);
			}
		}
	}
}

void GameAppend::ccTouchesEnded(CCSet* touches, CCEvent* pevent)
{
	if (isIntroduce && isCanTouch)
	{
		Global::getInstance()->s->removeLayerToRunningScene(this);
		if (introduceStep == 1)
		{
			((GameControl *)forwardLayer)->setBackGroundWithOutGreyLayer(false);
			((GuideLayer *)forwardLayer)->isIntroduce = true;
		}
		else
		{
			((GuideLayer *)forwardLayer)->isTouchIntroduce = false;
		}
	}
}