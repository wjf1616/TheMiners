#ifndef __REGISTERLAYERLOADER_H__
#define __REGISTERLAYERLOADER_H__

#include "RegisterLayer.h"

/* Forward declaration. */
class CCBReader;

class RegisterLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(RegisterLayerLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(RegisterLayer);
};

#endif