LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                    ../../Classes/AppDelegate.cpp \
		         	../../Classes/Alignment.cpp \
		         	../../Classes/BigGateMenu.cpp \
		         	../../Classes/Buddaha.cpp \
		         	../../Classes/Carrier.cpp \
		         	../../Classes/CartoonLayer.cpp \
		         	../../Classes/ChallengeCount.cpp \
		         	../../Classes/ChallengeOver.cpp \
		         	../../Classes/CostLayer.cpp \
		         	../../Classes/CountDownEffect.cpp \
		         	../../Classes/DateManger.cpp \
		         	../../Classes/DizzySpecialEffect.cpp \
		        	../../Classes/DrawLayer.cpp \
		         	../../Classes/DynamicTarget.cpp \
		         	../../Classes/ExchangeHangerEffect.cpp \
					../../Classes/ExitLayer.cpp \
					../../Classes/Explode.cpp \
					../../Classes/Explosive.cpp \
					../../Classes/Finger.cpp \
					../../Classes/GameAppend.cpp \
					../../Classes/GameControl.cpp \
					../../Classes/GameOverMenu.cpp \
					../../Classes/Gate.cpp \
					../../Classes/Global.cpp \
					../../Classes/GMJson.cpp \
					../../Classes/GoldenMinerScene.cpp \
					../../Classes/HalpLayer.cpp \
					../../Classes/Hanger.cpp \
					../../Classes/IngotDrop.cpp \
					../../Classes/JewelAppendEffect.cpp \
					../../Classes/JewelSkillSprite.cpp \
					../../Classes/LastTimeCountEffect.cpp \
					../../Classes/LoadingLayer.cpp \
					../../Classes/MainAppendLayer.cpp \
					../../Classes/MainLayer.cpp \
					../../Classes/MusicControl.cpp \
					../../Classes/MyAboutLayer.cpp \
					../../Classes/MyScrollView.cpp \
					../../Classes/NetWork.cpp \
					../../Classes/PauseMenu.cpp \
					../../Classes/PayService.cpp \
					../../Classes/Pet.cpp \
					../../Classes/PetParkLayer.cpp \
					../../Classes/Player.cpp \
					../../Classes/PowerBuff.cpp \
					../../Classes/PromptLayer.cpp \
					../../Classes/Prop.cpp \
					../../Classes/RegisterLayer.cpp \
					../../Classes/Role.cpp \
					../../Classes/RoleInformation.cpp \
					../../Classes/RoleSkillEffect.cpp \
					../../Classes/Rope.cpp \
					../../Classes/ScoreAppendEffect.cpp \
					../../Classes/SelectChallenge.cpp \
					../../Classes/SelectPet.cpp \
					../../Classes/SelectRoleAndPet.cpp \
					../../Classes/SelectRoleAndPropMenu.cpp \
					../../Classes/Sensitization.cpp \
					../../Classes/SetMenu.cpp \
					../../Classes/SettingMenu.cpp \
					../../Classes/Shop.cpp \
					../../Classes/SimleGateMenu.cpp \
					../../Classes/Skill.cpp \
					../../Classes/SlipGuide.cpp \
					../../Classes/SpotLightLayer.cpp \
					../../Classes/Target.cpp \
					../../Classes/TemporaryPromptLayer.cpp \
					../../Classes/TimeAppendEffect.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../../ \
				    $(LOCAL_PATH)/../../../CocosDenshion/include	\
					$(LOCAL_PATH)/../../Classes/CSArmature \
					$(LOCAL_PATH)/../../Classes/CSArmature/animation \
					$(LOCAL_PATH)/../../Classes/CSArmature/datas \
					$(LOCAL_PATH)/../../Classes/CSArmature/display \
					$(LOCAL_PATH)/../../Classes/CSArmature/external_tool \
					$(LOCAL_PATH)/../../Classes/CSArmature/external_tool/tinyxml \
					$(LOCAL_PATH)/../../Classes/CSArmature/external_tool/Json \
					$(LOCAL_PATH)/../../Classes/CSArmature/external_tool/Json/json \
					$(LOCAL_PATH)/../../Classes/CSArmature/external_tool/Json/lib_json \
					$(LOCAL_PATH)/../../Classes/CSArmature/physics \
					$(LOCAL_PATH)/../../Classes/CSArmature/utils \
					$(LOCAL_PATH)/../../Classes/SPArmature/SPArmature \
					$(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/animation \
					$(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/datas \
					$(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/datas/display_data \
					$(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/display \
					$(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/display/display_factory \
					$(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/external_tool/Json \
					$(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/external_tool/Json/lib_json \
					$(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/utils

# CSArmature
include $(LOCAL_PATH)/../../Classes/CSArmature/CSArmature.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/CSArmature/, $(SOURCE))

# CSArmature/animation
include $(LOCAL_PATH)/../../Classes/CSArmature/animation/animation.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/CSArmature/animation/, $(SOURCE))

# CSArmature/datas
include $(LOCAL_PATH)/../../Classes/CSArmature/datas/datas.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/CSArmature/datas/, $(SOURCE))

# CSArmature/display
include $(LOCAL_PATH)/../../Classes/CSArmature/display/display.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/CSArmature/display/, $(SOURCE))

# CSArmature/external_tool
include $(LOCAL_PATH)/../../Classes/CSArmature/external_tool/external_tool.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/CSArmature/external_tool/, $(SOURCE))

# CSArmature/external_tool/tinyxml
include $(LOCAL_PATH)/../../Classes/CSArmature/external_tool/tinyxml/tinyxml.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/CSArmature/external_tool/tinyxml/, $(SOURCE))

# CSArmature/external_tool/Json
# include $(LOCAL_PATH)/../../Classes/CSArmature/external_tool/Json/Json.mk
# LOCAL_SRC_FILES += $(addprefix ./../../Classes/CSArmature/external_tool/Json/, $(SOURCE))

# CSArmature/external_tool/Json/lib_json
include $(LOCAL_PATH)/../../Classes/CSArmature/external_tool/Json/lib_json/lib_json.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/CSArmature/external_tool/Json/lib_json/, $(SOURCE))

# CSArmature/physics
include $(LOCAL_PATH)/../../Classes/CSArmature/physics/physics.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/CSArmature/physics/, $(SOURCE))

# CSArmature/utils
include $(LOCAL_PATH)/../../Classes/CSArmature/utils/utils.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/CSArmature/utils/, $(SOURCE))

# SPArmature/tinyxml
#include $(LOCAL_PATH)/../../Classes/SPArmature/tinyxml/tinyxml.mk
#LOCAL_SRC_FILES += $(addprefix ./../../Classes/SPArmature/tinyxml/, $(SOURCE))

# SPArmature/SPArmature
include $(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/SPArmature.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/SPArmature/SPArmature/, $(SOURCE))

# SPArmature/SPArmature/animation
include $(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/animation/animation.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/SPArmature/SPArmature/animation/, $(SOURCE))

# SPArmature/SPArmature/datas
include $(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/datas/datas.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/SPArmature/SPArmature/datas/, $(SOURCE))

# SPArmature/SPArmature/datas/display_data
include $(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/datas/display_data/display_data.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/SPArmature/SPArmature/datas/display_data/, $(SOURCE))

# SPArmature/SPArmature/display
include $(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/display/display.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/SPArmature/SPArmature/display/, $(SOURCE))

# SPArmature/display/display_factory
include $(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/display/display_factory/display_factory.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/SPArmature/SPArmature/display/display_factory/, $(SOURCE))

# SPArmature/external_tool/Json
include $(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/external_tool/Json/Json.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/SPArmature/SPArmature/external_tool/Json/, $(SOURCE))

# SPArmature/external_tool/Json/lib_json
#include $(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/external_tool/Json/lib_json/lib_json.mk
#LOCAL_SRC_FILES += $(addprefix ./../../Classes/SPArmature/SPArmature/external_tool/Json/lib_json/, $(SOURCE))

# SPArmature/SPArmature/utils
include $(LOCAL_PATH)/../../Classes/SPArmature/SPArmature/utils/utils.mk
LOCAL_SRC_FILES += $(addprefix ./../../Classes/SPArmature/SPArmature/utils/, $(SOURCE))



LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
