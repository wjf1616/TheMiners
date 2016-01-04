#ifndef				__JEWEL_APPEND_EFFECT_H__
#define				__JEWEL_APPEND_EFFECT_H__

#include "cocos2d.h"

class GameControl;

class JewelAppendEffect:
	public cocos2d::CCLayer
{
public:
	JewelAppendEffect(GameControl * _gameControl, int _addNewJewelType);
	~JewelAppendEffect(void);

	virtual void onExit();

	bool doAction(float _f);

	int getAddNewJewelType(void);
private:

	float destinationX;
	float destinationY;

	float startX;
	float startY;

	// 获得技能宝石 粒子特效
	int addNewJewelType;
	float flyTime;
	cocos2d::CCParticleSystemQuad * newJewelSystem;
};

#endif
