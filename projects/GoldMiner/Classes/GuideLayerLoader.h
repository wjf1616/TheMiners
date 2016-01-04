#ifndef __GUIDELAYERLOADER_H__
#define __GUIDELAYERLOADER_H__

#include "GameControl.h"

/* Forward declaration. */
class CCBReader;

class GuideLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GuideLayerLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GuideLayer);
};

#endif