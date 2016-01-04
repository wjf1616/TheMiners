#ifndef __CHALLENGECOUNTLOADER_H__
#define __CHALLENGECOUNTLOADER_H__

#include "ChallengeCount.h"

/* Forward declaration. */
class CCBReader;

class ChallengeCountLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ChallengeCountLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ChallengeCount);
};

#endif