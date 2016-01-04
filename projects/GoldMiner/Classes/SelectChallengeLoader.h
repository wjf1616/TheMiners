#ifndef __SELECTCHALLENGELOADER_H__
#define __SELECTCHALLENGELOADER_H__

#include "SelectChallenge.h"

/* Forward declaration. */
class CCBReader;

class SelectChallengeLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SelectChallengeLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SelectChallenge);
};

#endif