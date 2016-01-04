#ifndef __COSTLOADER_H__
#define __COSTLOADER_H__

#include "CostLayer.h"

/* Forward declaration. */
class CCBReader;

class CostLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CostLayerLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CostLayer);
};

#endif