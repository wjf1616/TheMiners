#ifndef				__EXCHANGE_HANGER_EFFECT_H__
#define				__EXCHANGE_HANGER_EFFECT_H__

#include "cocos2d.h"

class Hanger;

using namespace cocos2d;

class ExchangeHangerEffect :
	public cocos2d::CCLayer
{
public:
	ExchangeHangerEffect(Hanger * _hanger);
	~ExchangeHangerEffect(void);

	bool doAction(float _f);

	void toSpecial(void);

	void toNormal(void);
private:
	bool isSpecial;
	bool isAllVisiable;

	Hanger * hanger;

	CCParticleSystemQuad * mSystem;

	int index;
	CCArray * toSpecialBitmaps;
	CCArray * toNormalBitmaps;

	CCNode * special;
	CCNode * normal;

	float startTime;

	void setUnVisiable(void);
};
#endif

