#ifndef			__DIZZY_SPECIAL_EFFECT_H__
#define			__DIZZY_SPECIAL_EFFECT_H__

#include "cocos2d.h"

using namespace cocos2d;

class DizzySpecialEffect :
	public cocos2d::CCNode
{
public:
	DizzySpecialEffect(void);
	~DizzySpecialEffect(void);
	bool doAction(float _f);

private:
	int index;
	CCArray * bitmaps;

	float startTime;
};

#endif