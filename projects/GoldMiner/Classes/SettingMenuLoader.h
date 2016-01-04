#ifndef __SETTINGMENULOADER_H__
#define __SETTINGMENULOADER_H__

#include "SettingMenu.h"

/* Forward declaration. */
class CCBReader;

class SettingMenuLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SettingMenuLoader, loader);

protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SettingMenu);
};

#endif