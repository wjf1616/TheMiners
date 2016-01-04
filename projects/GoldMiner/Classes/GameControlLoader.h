#ifndef __GAMECONTROLLOADER_H__
#define __GAMECONTROLLOADER_H__

#include "GameControl.h"

/* Forward declaration. */
class CCBReader;

class GameControlLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameControlLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameControl);
};

#endif