#ifndef __BIGGATEMENULOADER_H__
#define __BIGGATEMENULOADER_H__

#include "BigGateMenu.h"

/* Forward declaration. */
class CCBReader;

class BigGateMenuLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BigGateMenuLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(BigGateMenu);
};

#endif