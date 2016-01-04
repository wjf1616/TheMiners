#ifndef				__TIME_APPEND_EFFECT_H__
#define				__TIME_APPEND_EFFECT_H__

#include "cocos2d.h"

class GameControl;

class TimeAppendEffect:
	public cocos2d::CCLayer
{
public:
	TimeAppendEffect(GameControl * _gameControl);
	~TimeAppendEffect(void);

	virtual void onExit();

	bool doAction(float _f);

private:
	// 获得积分的粒子特效和得分显示
	float startTime;
	int index;
	cocos2d::CCArray * bitmaps;

	cocos2d::CCSprite * addTimeSprite;
};

#endif
