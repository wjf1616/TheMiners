#ifndef				__SCORE_APPEND_EFFECT_H__
#define				__SCORE_APPEND_EFFECT_H__

#include "cocos2d.h"

class GameControl;

class ScoreAppendEffect:
	public cocos2d::CCLayer
{
public:
	ScoreAppendEffect(GameControl * _gameControl, int _score);
	~ScoreAppendEffect(void);

	virtual void onExit();

	bool doAction(float _f);

private:

	float destinationX;
	float destinationY;

	float startX;
	float startY;

	// 获得积分的粒子特效和得分显示
	float flyTimeScore;
	cocos2d::CCParticleSystemQuad * addScoreSystem;
	cocos2d::CCSprite * addScoreSprite;
	cocos2d::CCLabelAtlas * addScoreNum;
};

#endif

