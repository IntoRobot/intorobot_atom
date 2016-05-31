# This file is a makefile included from the top level makefile which
# defines the sources built for the target.

# Define the prefix to this directory. 
# Note: The name must be unique within this build and should be
#       based on the root of the project
TARGET_COMMON_PATH = Core-Common
TARGET_COMMON_SRC_PATH = $(TARGET_COMMON_PATH)/src

# Add tropicssl include to all objects built for this target
INCLUDE_DIRS += $(TARGET_COMMON_PATH)/inc

# C source files included in this build.
CSRC += $(TARGET_COMMON_SRC_PATH)/system_stm32f10x.c
CSRC += $(TARGET_COMMON_SRC_PATH)/usb_pwr.c
CSRC += $(TARGET_COMMON_SRC_PATH)/debug.c
CSRC += $(TARGET_COMMON_SRC_PATH)/panic.c
CSRC += $(TARGET_COMMON_SRC_PATH)/hw_config.c

# C++ source files included in this build.
CPPSRC +=

# ASM source files included in this build.
ASRC +=

