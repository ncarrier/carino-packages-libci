LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libci
LOCAL_DESCRIPTION := Communication protocol implementation with the car
LOCAL_CATEGORY_PATH := libs

LOCAL_EXPORT_C_INCLUDES  := $(LOCAL_PATH)/include

LOCAL_SRC_FILES := \
	$(call all-c-files-under,src) \

include $(BUILD_LIBRARY)

