#ifndef __PETPARKLAYERLOADER_H__
#define __PETPARKLAYERLOADER_H__

#include "PetParkLayer.h"

/* Forward declaration. */
class CCBReader;

class PetParkLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PetParkLayerLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PetParkLayer);
};

#endif