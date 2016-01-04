#ifndef __PROMPTLAYERLOADER_H__
#define __PROMPTLAYERLOADER_H__

#include "PromptLayer.h"

/* Forward declaration. */
class CCBReader;

class PromptLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PromptLayerLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PromptLayer);
};

#endif