#ifndef __LOADINGLAYERLOADER_H__
#define __LOADINGLAYERLOADER_H__

#include "LoadingLayer.h"

/* Forward declaration. */
class CCBReader;

class LoadingLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LoadingLayerLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LoadingLayer);
};

#endif