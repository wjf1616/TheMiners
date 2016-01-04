#ifndef __SETMENULOADER_H__
#define __SETMENULOADER_H__

#include "SetMenu.h"

/* Forward declaration. */
class CCBReader;

class SetMenuLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SetMenuLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SetMenu);
};

#endif