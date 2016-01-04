#ifndef				__POWERBUFF_H__
#define				__POWERBUFF_H__

#include "cocos2d.h"

class GameControl;

using namespace cocos2d;

class PowerBuff :
	public cocos2d::CCObject
{
public:
	PowerBuff(GameControl * _gameControl);
	~PowerBuff(void);

	bool doAction(float _f);

	void removeSelf(GameControl * _gameControl);
private:
	int index;

	bool isBuff;

	cocos2d::CCNode * bitmap;

	cocos2d::CCNode * buffBitmap;

	CCArray * bitmaps;
	
	CCArray * buffBitmaps;

	float startTime;
};
#endif

