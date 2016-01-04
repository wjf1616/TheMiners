#ifndef				__EXPLODE_H__
#define				__EXPLODE_H__

#include "cocos2d.h"

using namespace cocos2d;

class Explode :
	public cocos2d::CCNode
{
public:
	Explode(int _type);
	~Explode(void);

	bool doAction(float _f);
private:
	int type;
	int index;
	CCArray * bitmaps;

	float startTime;
};
#endif

