#ifndef __SHOPLOADER_H__
#define __SHOPLOADER_H__

#include "Shop.h"

/* Forward declaration. */
class CCBReader;

class ShopLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ShopLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Shop);
};

#endif