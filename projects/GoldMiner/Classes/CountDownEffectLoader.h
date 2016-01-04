#ifndef __COUNTDOWN_EFFECT_LOADER_H__
#define __COUNTDOWN_EFFECT_LOADER_H__

#include "CountDownEffect.h"

/* Forward declaration. */
class CCBReader;

class CountDownEffectLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CountDownEffectLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CountDownEffect);
};

#endif