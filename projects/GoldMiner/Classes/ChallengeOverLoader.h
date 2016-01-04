#ifndef __CHALLENGEOVERLOADER_H__
#define __CHALLENGEOVERLOADER_H__

#include "ChallengeOver.h"

/* Forward declaration. */
class CCBReader;

class ChallengeOverLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ChallengeOverLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ChallengeOver);
};

#endif