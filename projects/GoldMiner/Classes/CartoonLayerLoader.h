#ifndef __CARTOONLAYERLOADER_H__
#define __CARTOONLAYERLOADER_H__

#include "CartoonLayer.h"

/* Forward declaration. */
class CCBReader;

class CartoonLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CartoonLayerLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CartoonLayer);
};

#endif