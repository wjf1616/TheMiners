#ifndef __SELECTROLEANDPROPMENULOADER_H__
#define __SELECTROLEANDPROPMENULOADER_H__

#include "SelectRoleAndPropMenu.h"

/* Forward declaration. */
class CCBReader;

class SelectRoleAndPropMenuLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SelectRoleAndPropMenuLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SelectRoleAndPropMenu);
};

#endif