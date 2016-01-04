#ifndef				__LASTTIMECOUNT_EFFECT_H__
#define				__LASTTIMECOUNT_EFFECT_H__

#include "cocos2d.h"

using namespace cocos2d;

class LastTimeCountEffect :
	public cocos2d::CCNode
{
public:
	LastTimeCountEffect(int _type);
	~LastTimeCountEffect(void);

	bool doAction(float _f);
private:
	int index;
	CCArray * bitmaps;

	float startTime;
	float perTime;
	bool isExchange;
};
#endif