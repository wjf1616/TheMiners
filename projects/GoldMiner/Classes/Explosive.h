#ifndef	__EXPLOSIVE_H__
#define __EXPLOSIVE_H__

#include "cocos2d.h"
#include "Global.h"

using namespace cocos2d;

class Hanger;

class Explosive :
	public cocos2d::CCSprite
{
public:
	Explosive(Hanger * _hanger);
	~Explosive(void);

	bool doAction(float _f);
private:
#ifdef							GOLDEN_MINER_2_VERSION_TIME
	float statusTimeCount;// ը���ļ�ʱ
#else
	int statusTimeCount;// ը���ļ�ʱ
#endif
	Hanger * hanger;
};

#endif