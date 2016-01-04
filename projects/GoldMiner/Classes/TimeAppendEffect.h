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
	// ��û��ֵ�������Ч�͵÷���ʾ
	float startTime;
	int index;
	cocos2d::CCArray * bitmaps;

	cocos2d::CCSprite * addTimeSprite;
};

#endif
