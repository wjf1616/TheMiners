APP_STL := gnustl_static
APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -DCOCOS2D_DEBUG=1
APP_CPPFLAGS += -Wno-error=format-security
APP_CPPFLAGS += -fpermissive
APP_PLATFORM := android-8