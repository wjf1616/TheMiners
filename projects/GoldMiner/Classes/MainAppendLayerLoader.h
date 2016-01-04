#ifndef __MAINAPPENDLAYERLOADER_H__
#define __MAINAPPENDLAYERLOADER_H__

#include "MainAppendLayer.h"

/* Forward declaration. */
class CCBReader;

class MainAppendLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainAppendLayerLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainAppendLayer);
};

#endif