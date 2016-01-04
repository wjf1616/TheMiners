#include "ScoreAppendEffect.h"
#include "Global.h"
#include "GameControl.h"

#define			ADD_NEW_SCORE_FLY_TIME_LONG			0.5
#define			ADD_NEW_SCORE_REMOVE_TIME_LONG		1.5

USING_NS_CC;

ScoreAppendEffect::ScoreAppendEffect(GameControl * _gameControl, int _score)
{
	flyTimeScore = 0.0;
	destinationX = _gameControl->getGetCoinLabelPosition().x;
	destinationY = _gameControl->getGetCoinLabelPosition().y;
	startX = Global::getInstance()->getcentreX();
	startY = Global::getInstance()->getcentreY();

	addScoreSystem = CCParticleSystemQuad::create("lizitexiao/daojulizi/daojulizi.plist");//plist文件可以通过例子编辑器获得
	addScoreSystem->setPosition(ccp(startX, startY));
	addScoreSystem->retain();
	addChild(addScoreSystem);

	CCSequence * sequence;
	CCSpawn * spawn;

	addScoreSprite = CCSprite::create("youxi/+.png");
	addScoreSprite->setPosition(ccp(startX + 90, startY  - 45));
	spawn = CCSpawn::create(CCFadeIn::create(.3f),CCMoveTo::create(.3f,ccp(startX + 90,startY  - 45 +40)),NULL);
	sequence = CCSequence::create(spawn,CCFadeTo::create(1,255*1),CCFadeOut::create(.2f),NULL);
	//sequence = CCSequence::create(CCScaleTo::create(.1f,1.5f),CCScaleTo::create(.1f,1),
	//	CCMoveTo::create(.3f,ccp(startX + 90,startY  + 65 +80))
	//	,CCFadeOut::create(.2f),NULL);
	addScoreSprite->runAction(sequence);
	addScoreSprite->retain();
	addChild(addScoreSprite);
	char _s[32];
	sprintf(_s, "%d",_score);
	addScoreNum = CCLabelAtlas::create(_s, "youxi/daojushuzi.png", 25, 36, '0');
	int i = 0;
	int _getCoinTmp = _score;
	while(1)
	{
		_getCoinTmp = _getCoinTmp / 10;
		if (_getCoinTmp > 0)
		{
			i++;
		}
		else
		{
			break;
		}
	}
	addScoreNum->setPosition(ccp(startX + 50 + 44 + i*8, startY-60));
	spawn = CCSpawn::create(CCFadeIn::create(.3f),CCMoveTo::create(.3f,ccp(startX + 50 + 44 + i*8,startY -20)),NULL);
	sequence = CCSequence::create(spawn,CCFadeTo::create(1,255*1),CCFadeOut::create(.2f),NULL);
	//sequence = CCSequence::create(CCScaleTo::create(.1f,1.5f),CCScaleTo::create(.1f,1),
	//	CCMoveTo::create(.3f,ccp(startX + 50 + 44 + i*8,startY  + 50 +80))
	//	,CCFadeOut::create(.2f),NULL);
	addScoreNum->runAction(sequence);
	addScoreNum->retain();
	addChild(addScoreNum);

	this->autorelease();
}


ScoreAppendEffect::~ScoreAppendEffect(void)
{
}

void ScoreAppendEffect::onExit()
{
	CC_SAFE_RELEASE_NULL(addScoreSystem);
	CC_SAFE_RELEASE_NULL(addScoreSprite);
	CC_SAFE_RELEASE_NULL(addScoreNum);

	CCLayer::onExit();
}

bool ScoreAppendEffect::doAction(float _f)
{
	flyTimeScore += _f;
	if (flyTimeScore < ADD_NEW_SCORE_FLY_TIME_LONG)
	{
		addScoreSystem->setPosition(ccp(startX + flyTimeScore/ADD_NEW_SCORE_FLY_TIME_LONG*(destinationX - startX), startY + flyTimeScore/ADD_NEW_SCORE_FLY_TIME_LONG*(destinationY - startY)));
		return false;
	}
	else if(flyTimeScore < ADD_NEW_SCORE_REMOVE_TIME_LONG)
	{
		addScoreSystem->setVisible(false);
		return false;
	}
	else
	{
		setVisible(false);
		return true;
	}
}