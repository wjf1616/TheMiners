#ifndef __CHALLENGELAYERLOADER_H__
#define __CHALLENGELAYERLOADER_H__

#include "GameControl.h"

/* Forward declaration. */
class CCBReader;

class ChallengeLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ChallengeLayerLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ChallengeLayer);
};

#endif