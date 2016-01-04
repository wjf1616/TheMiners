#ifndef __GAMEAPPENDLOADER_H__
#define __GAMEAPPENDLOADER_H__

#include "GameAppend.h"

/* Forward declaration. */
class CCBReader;

class GameAppendLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameAppendLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameAppend);
};

#endif