#ifndef __ROLE_SKILL_EFFECT_LOADER_H__
#define __ROLE_SKILL_EFFECT_LOADER_H__

#include "RoleSkillEffect.h"

/* Forward declaration. */
class CCBReader;

class RoleSkillEffectLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(RoleSkillEffectLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(RoleSkillEffect);
};

#endif