#ifndef __TEMPORARYPROMPTLOADER_H__
#define __TEMPORARYPROMPTLOADER_H__

#include "TemporaryPromptLayer.h"

/* Forward declaration. */
class CCBReader;

class TemporaryPromptLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TemporaryPromptLayerLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(TemporaryPromptLayer);
};

#endif