#ifndef __GAMEOVERMENULOADER_H__
#define __GAMEOVERMENULOADER_H__

#include "GameOverMenu.h"

/* Forward declaration. */
class CCBReader;

class GameOverMenuLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameOverMenuLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameOverMenu);
};

#endif