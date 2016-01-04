#ifndef				__SENSITIZATION_H__
#define				__SENSITIZATION_H__

#include "cocos2d.h"

#define					SENSITIZATION_TYPE_CIRCULAR				1
#define					SENSITIZATION_TYPE_RECT					2

using namespace cocos2d;

class Sensitization :
	public cocos2d::CCNode
{
public:
	Sensitization(int _type);
	~Sensitization(void);

	bool doAction(float _f);
private:
	int index;
	CCArray * bitmaps;

	float startTime;
};
#endif