#ifndef				__FINGER_H__
#define				__FINGER_H__

#include "cocos2d.h"

using namespace cocos2d;

class Finger :
	public cocos2d::CCNode
{
public:
	Finger(void);
	~Finger(void);

	bool doAction(float _f);
private:
	int index;
	CCArray * bitmaps;

	float startTime;
};
#endif

