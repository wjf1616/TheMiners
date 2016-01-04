#ifndef __ROPE_H__
#define __ROPE_H__
#include "cocos2d.h"
#include "Global.h"

using namespace cocos2d;

#define			ROPE_STATUS_NORMAL					1
#define			ROPE_STATUS_THROW					2
#define			ROPE_STATUS_INTERSECT				3
#define			ROPE_STATUS_PULL					4

class Hanger;

class Rope :
	public cocos2d::CCSprite
{
public:
	Rope(Hanger * hanger);

	~Rope(void);

	void doAction(float dt, Hanger * hanger);
	void changeImageByStatus(int _status, Hanger * _hanger);

	void changePosition(Hanger * hanger);

private:

	int status;

	int scaleExchange;
};

#endif

