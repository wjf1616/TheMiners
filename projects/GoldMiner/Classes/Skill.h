#ifndef __SKILL_H__
#define __SKILL_H__

#include "GameControl.h"

enum
{
	SKILL_ID_CARRY_STONE_FIVE = 0,//
};


class Skill
{
public:
	Skill(void);
	~Skill(void);

	void doSkill(GameControl * _gameControl);
	void releaseSkill(GameControl * _gameControl);
};

#endif

