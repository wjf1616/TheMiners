#ifndef __HALPLAYERLOADER_H__
#define __HALPLAYERLOADER_H__

#include "HalpLayer.h"

/* Forward declaration. */
class CCBReader;

class HalpLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HalpLayerLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HalpLayer);
};

#endif