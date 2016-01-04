#include "Prop.h"


Prop::Prop(void)
{
}

Prop::~Prop(void)
{

}

int Prop::getPrice(int id)
{
	int res = 0;

	switch(id)
	{
	case PROP_TYPE_GRENADE:
		res = 50;
		break;
	case PROP_TYPE_VIGOROUSLY_PILL:
		res = 300;
		break;
	case PROP_TYPE_MOONLIGHT:
		res = 500;
		break;
	case PROP_TYPE_ALIGNMENT:
		res = 150;
		break;
	default:
		break;
	}
	return res;
}

int Prop::getSkillId(int id)
{
	int res = SKILL_ID_NO;

	switch(id)
	{
	case PROP_TYPE_GRENADE:
		res = SKILL_ID_GRENADE;
		break;
	case PROP_TYPE_VIGOROUSLY_PILL:
		res = SKILL_ID_VIGOROUSLY_PILL;
		break;
	case PROP_TYPE_MOONLIGHT:
		res = SKILL_ID_MOONLIGHT;
		break;
	default:
		break;
	}
	return res;
}