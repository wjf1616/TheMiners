#ifndef	__ALIGNMENT_H__
#define __ALIGNMENT_H__

#include "cocos2d.h"
#include "Global.h"

#define				ALIGNMENT_TYPE_NORMAL					1
#define				ALIGNMENT_TYPE_SHAHESHANG				2

using namespace cocos2d;

class Hanger;

class Alignment :
	public cocos2d::CCSprite
{
public:
	Alignment(void);
	~Alignment(void);

	void setJewelSkillUnVisiable(bool _b);

	bool doAction(float _f, Hanger * _hanger);

	void setType(int _type);
private:
	bool isJewelSkillUnVisiable;

	int type;

	int jiGuangTimeCount;

	void changeMiaoZhunXianPosition(Hanger * _hanger);
};

#endif