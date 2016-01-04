#ifndef __SELECTPETLOADER_H__
#define __SELECTPETLOADER_H__

#include "SelectPet.h"

/* Forward declaration. */
class CCBReader;

class SelectPetLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SelectPetLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SelectPet);
};

#endif