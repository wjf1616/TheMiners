#ifndef __EXITLAYERLOADER_H__
#define __EXITLAYERLOADER_H__

#include "ExitLayer.h"

/* Forward declaration. */
class CCBReader;

class ExitLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ExitLayerLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ExitLayer);
};

#endif