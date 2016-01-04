#ifndef __DRAWLAYERLOADER_H__
#define __DRAWLAYERLOADER_H__

#include "DrawLayer.h"

/* Forward declaration. */
class CCBReader;

class DrawLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(DrawLayerLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(DrawLayer);
};

#endif