#ifndef				__INGOTDROP_H__
#define				__INGOTDROP_H__

#include "cocos2d.h"

using namespace cocos2d;

class IngotDrop :
	public cocos2d::CCNode
{
public:
	IngotDrop(int _speed, float _staticPositionY, float _staticLiveTime);
	~IngotDrop(void);

	bool doAction(float _f);
	float startPositionY;
private:
	int speed;
	int index;
	float staticLiveTime;
	float liveCount;
	float staticPositionY;
	CCArray * bitmaps;

	float startTime;
};
#endif


