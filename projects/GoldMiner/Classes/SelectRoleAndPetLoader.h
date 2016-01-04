#ifndef __SELECTROLEANDPETLOADER_H__
#define __SELECTROLEANDPETLOADER_H__

#include "SelectRoleAndPet.h"

/* Forward declaration. */
class CCBReader;

class SelectRoleAndPetLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SelectRoleAndPetLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SelectRoleAndPet);
};

#endif