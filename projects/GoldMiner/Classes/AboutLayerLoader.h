#ifndef __ABOUTLAYERLOADER_H__
#define __ABOUTLAYERLOADER_H__

#include "MyAboutLayer.h"

/* Forward declaration. */
class CCBReader;

class AboutLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AboutLayerLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MyAboutLayer);
};

#endif