#ifndef __ROLE_INFORMATION_LOADER_H__
#define __ROLE_INFORMATION_LOADER_H__

#include "RoleInformation.h"

/* Forward declaration. */
class CCBReader;

class RoleInformationLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(RoleInformationLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(RoleInformation);
};

#endif