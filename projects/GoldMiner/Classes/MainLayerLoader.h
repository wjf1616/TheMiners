#ifndef __MAINLAYERLOADER_H__
#define __MAINLAYERLOADER_H__

#include "MainLayer.h"

/* Forward declaration. */
class CCBReader;

class MainLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainLayerLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainLayer);
};

#endif