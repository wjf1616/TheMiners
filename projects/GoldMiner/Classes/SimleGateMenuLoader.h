#ifndef __SIMLEGATEMENULOADER_H__
#define __SIMLEGATEMENULOADER_H__

#include "SimleGateMenu.h"

/* Forward declaration. */
class CCBReader;

class SimleGateMenuLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SimleGateMenuLoader, loader);
	//static SimleGateMenuLoader * loader() { 
	//	SimleGateMenuLoader * ptr = new SimleGateMenuLoader());
	//	if(ptr != NULL) { 
	//		ptr->autorelease(); 
	//		return ptr; 
	//	} 
	//	CC_SAFE_DELETE(ptr); 
	//	return NULL; 
	//}

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SimleGateMenu);
};

#endif