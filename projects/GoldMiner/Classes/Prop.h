#ifndef __PROP_H__
#define __PROP_H__

#include "cocos2d.h"
#include "Global.h"

class Prop :
	public cocos2d::CCSprite
{
public:
	Prop(void);
	~Prop(void);

	static int getPrice(int _id);
	static int getSkillId(int _id);
};


#endif
