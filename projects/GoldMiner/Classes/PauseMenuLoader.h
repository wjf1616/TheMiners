#ifndef __PAUSEMENULOADER_H__
#define __PAUSEMENULOADER_H__

#include "PauseMenu.h"

/* Forward declaration. */
class CCBReader;

class PauseMenuLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PauseMenuLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PauseMenu);
};

#endif