#################################################################################
#cfg.mak
#################################################################################

# Y/N 打开/关闭 编译器警报
export MO_COMPILE_WARING=N


#Y镜像直接烧到起始地址不需要boot引导(gdb只支持这种)
#N镜像需要烧写到指定地址boot引导运行
export MO_NOBOOT_BIN=Y


#Y gdb调试用
export MO_DEBUG=N


#由于服务器PATH传不进来在这里设置一下
export PATH :=/opt/gcc-arm-none-eabi-4_8-2014q3/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:${PATH}





#################################################################################
#end
#################################################################################








MAKE_ARGS = --no-print-directory

# don't propagate command line definitions to submakes, specifically, TARGET,
# since this will override the local makefile's definition of that. 
MAKEOVERRIDES=

# by convention, all symbols referring to a directory end with a slash - this allows
# directories to resolve to "" when equal to the working directory
SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

# for now, assume current dir is build/
PROJECT_DIR=../

# Define the build path, this is where all of the dependancies and
# object files will be placed.
# Note: Currently set to <project>/build/obj directory and set relative to
# the dir which makefile is invoked. If the makefile is moved to the project
# root, BUILD_PATH = build can be used to store the build products in 
# the build directory.
BUILD_PATH = $(SELF_DIR)obj/

# directory containing this project
EXT_LIBS_DIR=../../

#+++++++++++++++++++++++++++++++++++++++++++++++++++
#instead include $(SELF_DIR)tools.mk
#+++++++++++++++++++++++++++++++++++++++++++++++++++
# Define the compiler/tools prefix
GCC_PREFIX = arm-none-eabi-

# Define tools
CC = $(GCC_PREFIX)gcc
CPP = $(GCC_PREFIX)g++
AR = $(GCC_PREFIX)ar
OBJCOPY = $(GCC_PREFIX)objcopy
SIZE = $(GCC_PREFIX)size
DFU = dfu-util
CURL = curl

RM = rm -f
RMDIR = rm -f -r
MKDIR = mkdir -p




# Recursive wildcard function
rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# enumerates files in the filesystem and returns their path relative to the project root
# $1 the directory relative to the project root
# $2 the pattern to match, e.g. *.cpp
target_files = $(patsubst $(SRC_PATH)%,%,$(call rwildcard,$(SRC_PATH)$1,$2))



# URL to invoke cloud flashing
CLOUD_FLASH_URL = https://api.spark.io/v1/devices/$(INTORBT_CORE_ID)\?access_token=$(INTORBT_ACCESS_TOKEN)

# Path to the root of source files, in this case root of the project to
# include ../src and ../lib dirs.
# Note: Consider relocating source files in lib to src, or build a
#       separate library.
SRC_PATH = $(PROJECT_DIR)

# ensure defined
USRSRC += ""

# determine where user sources are, relative to project root
ifdef APP
USRSRC = applications/$(APP)/
CPPFLAGS += -std=gnu++11

ifndef TARGET
TARGET ?= $(notdir $(APP))
TARGETDIR ?= $(USRSRC)
endif
endif

ifdef TEST
USRSRC = tests/$(TEST)/
CPPFLAGS += -std=gnu++11
ifndef TARGET
TARGET ?= $(notdir $(TEST))
TARGETDIR ?= $(USRSRC)
endif
include $(PROJECT_DIR)tests/tests.mk
-include $(PROJECT_DIR)$(USRSRC)test.mk
endif

# user sources specified, so override application.cpp and pull in files from 
# the user source folder
ifneq ($(USRSRC),"")       
    NO_APPLICATION_CPP=1
    INCLUDE_DIRS += $(USRSRC)  # add user sources to include path
    # add C and CPP files 
    CPPSRC += $(call target_files,$(USRSRC),*.cpp)
    CSRC += $(call target_files,$(USRSRC),*.c)    
endif

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#public
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#递归获取所有文件以及文件夹(只能获取一个目录)
search_target_files_single = $(call rwildcard,$1,$2)

#递归获取多个目录下面的文件(允许多个目录)
search_target_file=$(foreach dir_for,$1,$(call search_target_files_single,$(dir_for),$2))








#######################################################################################
##平台传入变量
#######################################################################################

#平台传入用户目录文件夹路径默认值
ID_PATH ?=../../out/xiaoming/APP1

ID_ROOT_DIR := $(ID_PATH)/../





#######################################################################################
##基本库编译变量
#######################################################################################
#基本库源码、头文件、生成库存放目录
LIB_BASE_PATH=../../out/public_use/lib_base/
INC_BASE_PATH=../../out/public_use/lib_base/
INC_ROS_PATH=../../out/public_use/lib_base/ros_lib
SRC_BASE_PATH=../../out/public_use/src_base/
SCRIPT_BASE_PATH=../../out/public_use/lib_base/

######################################################################################
#分理处带路径的cpp文件
CPPSRC_BASE = $(call search_target_files,$(SRC_BASE_PATH),*.cpp)

#转换为.o的目标文件
CPPOBJ_BASE = $(patsubst %.cpp,%.o, $(CPPSRC_BASE))

#转换为用户库路径的目标文件
CPPLIB_BASE =$(patsubst $(SRC_BASE_PATH)%,$(LIB_BASE_PATH)%, $(CPPOBJ_BASE))


#######################################################################################







#######################################################################################
##第三方库编译变量
#######################################################################################

#用户库源码、头文件、生成库存放目录
#LIB_SEC_PATH=$(ID_DIR)/lib_sec/
#INC_SEC_PATH=$(ID_DIR)/inc_sec/
#SRC_SEC_PATH=$(ID_DIR)/src_sec/



#分理处带路径的cpp文件
#CPPSRC_SEC = $(call search_target_files,$(SRC_SEC_PATH),*.cpp)

#转换为.o的目标文件
#CPPOBJ_SEC = $(patsubst %.cpp,%.o, $(CPPSRC_SEC))

#转换为用户库路径的目标文件
#CPPLIB_SEC =$(patsubst $(SRC_SEC_PATH)%,$(LIB_SEC_PATH)%, $(CPPOBJ_SEC))


#获取第三方库文件夹下面的libxxx.a并把其转换为-lxxx的连接选项
#LIB_SEC_A := $(patsubst $(LIB_SEC_PATH)lib%.a,-l%,$(wildcard $(LIB_SEC_PATH)*.a)) 



#######################################################################################

LIB_PUBLIC_DIR=../../out/public_use/lib_public/


LIB_USR ?= DHT22_lib_usr_test1}V1_11  DHT33_lib_usr_test2}V2_22
#LIB_PUBLIC ?= DHT00_lib_public_test1 DHT11_lib_public_test2
LIB_PUBLIC ?= DHT00_lib_public_test1}V1_11 DHT11_lib_public_test2}V2_22


#######################################################################################
##用户程序变量
#######################################################################################

#用户库源码、头文件、生成库存放目录

SRC_USR_PATH=$(ID_PATH)/src/
BIN_PLATFORM_OUT=$(ID_PATH)/out



#各个用户库源码路径


LIB_USR_PATH = $(shell echo ${LIB_USR} | awk '{ for(i=1; i<=NF; i++) print $$i }' | awk -F '}' '{print "${ID_ROOT_DIR}"$$0"/"$$1"/src/"}')

#LIB_USR_PATH = $(patsubst %,$(ID_ROOT_DIR)/%/src/, $(LIB_USR))


test:
	@echo ${LIB_USR_PATH}



#添加到用户源码
SRC_USR_PATH += $(LIB_USR_PATH)





#公共库全路径
LIB_PUBLIC_PATH = $(shell echo ${LIB_PUBLIC} | awk '{ for(i=1; i<=NF; i++) print $$i }' | awk -F '}' '{print "${LIB_PUBLIC_DIR}"$$0"/"$$1"/src/"}')

#LIB_PUBLIC_PATH = $(patsubst %,$(LIB_PUBLIC_DIR)/%/src/, $(LIB_PUBLIC))




#添加到用户源码
SRC_USR_PATH += $(LIB_PUBLIC_PATH)

#头文件目前与源码一个目录
INC_USR_PATH :=$(SRC_USR_PATH)





CPPSRC_USR=$(call search_target_file,$(SRC_USR_PATH),*.cpp)




#分理处带路径的cpp文件
#CPPSRC_USR = $(call search_target_files,$(SRC_USR_PATH),*.cpp)

#转换为.o的目标文件
CPPOBJ_USR = $(patsubst %.cpp,%.o, $(CPPSRC_USR))

#转换为用户库路径的目标文件
#CPPLIB_USR =$(patsubst $(SRC_USR_PATH)%,$(LIB_USR_PATH)%, $(CPPOBJ_USR))

#######################################################################################








#######################################################################################
##公共库(old)
#######################################################################################

#用户库源码、头文件、生成库存放目录
#LIB_USR_PATH=$(ID_PATH)/lib_usr/
#INC_USR_PATH=$(ID_PATH)/inc_usr/
#SRC_USR_PATH=$(ID_PATH)/src_usr/

#BIN_PLATFORM_OUT=$(ID_PATH)/out

#递归获取所有文件以及文件夹
#target_files_usr = $(call rwildcard,$(SRC_USR_PATH),$1)

#分离出带路径的cpp文件
#CPPSRC_USR = $(call target_files_usr,*.cpp)

#转换为.o的目标文件
#CPPOBJ_USR = $(patsubst %.cpp,%.o, $(CPPSRC_USR))

#转换为用户库路径的目标文件
#CPPLIB_USR =$(patsubst $(SRC_USR_PATH)%,$(LIB_USR_PATH)%, $(CPPOBJ_USR))



#######################################################################################


TARGET ?= core-firmware
TARGETDIR ?= 


# Find all build.mk makefiles in each source directory in the src tree.
SRC_MAKEFILES := $(call rwildcard,$(SRC_PATH)src,build.mk)

# Include all build.mk defines source files.
include $(SRC_MAKEFILES)

# Paths to dependent projects, referenced from root of this project
LIB_CORE_COMMON_PATH = ../core-common-lib/
#LIB_CORE_COMMUNICATION_PATH = ../core-communication-lib/
LIB_CORE_LIBRARIES_PATH = libraries/

# Include directories for optional "libraries" (eg. Serial2.h)
INCLUDE_DIRS += $(LIB_CORE_LIBRARIES_PATH)Serial2

# Additional include directories, applied to objects built for this target.
# todo - delegate this to a include.mk file in each repo so include dirs are better
# encapsulated by their owning repo
INCLUDE_DIRS += $(LIB_CORE_COMMON_PATH)CMSIS/Include
INCLUDE_DIRS += $(LIB_CORE_COMMON_PATH)CMSIS/Device/ST/STM32F10x/Include
INCLUDE_DIRS += $(LIB_CORE_COMMON_PATH)STM32F10x_StdPeriph_Driver/inc
INCLUDE_DIRS += $(LIB_CORE_COMMON_PATH)STM32_USB-FS-Device_Driver/inc
#INCLUDE_DIRS += $(LIB_CORE_COMMON_PATH)CC3000_Host_Driver
INCLUDE_DIRS += $(LIB_CORE_COMMON_PATH)Core-Common/inc
#INCLUDE_DIRS += $(LIB_CORE_COMMON_PATH)SPARK_Services/inc
#INCLUDE_DIRS += $(LIB_CORE_COMMUNICATION_PATH)lib/tropicssl/include
#INCLUDE_DIRS += $(LIB_CORE_COMMUNICATION_PATH)src

INCLUDE_DIRS += ./src


# Compiler flags

#============add lbz=============================
ifeq ("$(MO_DEBUG)","Y") 
CFLAGS =  -g3 -gdwarf-2 -O0 -mcpu=cortex-m3 -mthumb 
#CFLAGS =  -g3 -gdwarf-2 -O0 -mcpu=cortex-m3 -mthumb -Werror
else
CFLAGS =  -g3 -gdwarf-2 -Os -mcpu=cortex-m3 -mthumb
endif
#=============end==============================

#添加基本库头文件
CFLAGS +=-I $(INC_BASE_PATH) -I $(INC_ROS_PATH)

#添加公共库、用户库根目录 因为头文件采用   #inclide <OLED/test.h>  的形式

#CFLAGS +=-I $(LIB_PUBLIC_DIR)



LIB_PUBLIC_INC = $(patsubst %,-I %/../../, $(LIB_PUBLIC_PATH))

CFLAGS += ${LIB_PUBLIC_INC}





#CFLAGS +=-I $(ID_ROOT_DIR)


LIB_USR_INC = $(patsubst %,-I %/../../, $(LIB_USR_PATH))

CFLAGS += $(LIB_USR_INC)




#添加用户库头文件
#CFLAGS +=-I $(INC_USR_PATH)
#CFLAGS +=$(foreach dir_for,$(INC_USR_PATH),-I $(dir_for))
CFLAGS +=$(patsubst %,-I %, $(INC_USR_PATH))






CFLAGS += $(patsubst %,-I$(SRC_PATH)%,$(INCLUDE_DIRS)) -I.
ifeq ("$(MO_COMPILE_WARING)","N") 
CFLAGS += -ffunction-sections -w -fmessage-length=0
else
CFLAGS += -ffunction-sections -Wall -fmessage-length=0
endif


# Flag compiler error for [-Wdeprecated-declarations]
CFLAGS += -Werror=deprecated-declarations

# Generate dependency files automatically.
CFLAGS += -MD -MP -MF $@.d

# Target specific defines
CFLAGS += -DUSE_STDPERIPH_DRIVER
CFLAGS += -DSTM32F10X_MD


#============add lbz==============================
ifeq ("$(MO_NOBOOT_BIN)","N") 
CFLAGS += -DDFU_BUILD_ENABLE
else
CFLAGS += -DNOBOOT_EEPROM_ADDR
endif
#=============end===============================


CFLAGS += -DSPARK=1

ifeq ("$(USE_SWD_JTAG)","y") 
CFLAGS += -DUSE_SWD_JTAG
endif

ifeq ("$(DEBUG_BUILD)","y") 
CFLAGS += -DDEBUG_BUILD
else
CFLAGS += -DRELEASE_BUILD
endif

# C++ specific flags
CPPFLAGS += -fno-rtti -fno-exceptions

# Linker flags   linker_stm32f10x_md.ld


#============add lbz==============================
ifeq ("$(MO_NOBOOT_BIN)","N") 
LDFLAGS += -T$(PROJECT_DIR)linker/linker_stm32f10x_md_dfu.ld -nostartfiles -Xlinker --gc-sections
LDFLAGS_START := -T$(SCRIPT_BASE_PATH)/linker/linker_stm32f10x_md_dfu.ld -nostartfiles -Xlinker --gc-sections $(SCRIPT_BASE_PATH)/linker/startup_stm32f10x_md.o  

else
LDFLAGS += -T$(PROJECT_DIR)linker/linker_stm32f10x_md.ld -nostartfiles -Xlinker --gc-sections
LDFLAGS_START := -T$(SCRIPT_BASE_PATH)/linker/linker_stm32f10x_md.ld -nostartfiles  -Xlinker --gc-sections $(SCRIPT_BASE_PATH)/linker/startup_stm32f10x_md.o 

endif
#=============end===============================


LDFLAGS += -L$(PROJECT_DIR)$(LIB_CORE_COMMON_PATH)build -lcore-common-lib
#LDFLAGS += -L$(PROJECT_DIR)$(LIB_CORE_COMMUNICATION_PATH)build -lcore-communication-lib
LDFLAGS += -Wl,-Map,$(TARGETDIR)$(TARGET).map
LDFLAGS += --specs=nano.specs -lc -lnosys
LDFLAGS += -u _printf_float

# Assembler flags
ASFLAGS =  -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb 
ASFLAGS += -x assembler-with-cpp -fmessage-length=0

# Collect all object and dep files
ALLOBJ += $(addprefix $(BUILD_PATH), $(CSRC:.c=.o))
ALLOBJ += $(addprefix $(BUILD_PATH), $(CPPSRC:.cpp=.o))
ALLOBJ += $(addprefix $(BUILD_PATH), $(ASRC:.S=.o))

ALLDEPS += $(addprefix $(BUILD_PATH), $(CSRC:.c=.o.d))
ALLDEPS += $(addprefix $(BUILD_PATH), $(CPPSRC:.cpp=.o.d))
ALLDEPS += $(addprefix $(BUILD_PATH), $(ASRC:.S=.o.d))




intorobot_stm32:elf bin hex size
	cp ./core-firmware.* ../../out/
	

# All Target

all: intorobot_stm32 release_base_lib  release_platform_bin





release_server:clean_public_lib clean_platform_bin
	rm -rf ../../out/intorobot_stm32_server
	rm -rf ../../out/intorobot_stm32_server.tar.gz	

	rm -rf ../../out/intorobot_stm32_server
	
	mkdir -p ../../out/intorobot_stm32_server/out	
	cp -rf ../../out/xiaoming ../../out/intorobot_stm32_server/out/
	cp -rf ../../out/public_use ../../out/intorobot_stm32_server/out/
	
	mkdir -p  ../../out/intorobot_stm32_server/firmware-intorobot/build
	cp -rf makefile ../../out/intorobot_stm32_server/firmware-intorobot/build/

	cp -rf ../../makefile ../../out/intorobot_stm32_server/

	cp -rf ../../readme.txt ../../out/intorobot_stm32_server/


	



	@echo Add svn info

	@echo $(shell sed -i '/TIME_Compile:*/d' ../../readme.txt)
	@echo $(shell sed -i '/AUTHOR_Compile:*/d' ../../readme.txt)
	
	@echo $(shell echo "TIME_Compile: $$(date) " >> ../../readme.txt)
	@echo $(shell echo "AUTHOR_Compile: $$USER " >> ../../readme.txt)

	
	cp -rf ../../pack_install.sh ../../out/intorobot_stm32_server/
	
	find ../../out/intorobot_stm32_server/ -type d -name ".svn"|xargs rm -rf
	chmod -R 777 ../../out/intorobot_stm32_server

	cd ../../out/;tar -zcvf intorobot_stm32_server.tar.gz intorobot_stm32_server


clean_server:
	rm -rf $(INC_BASE_PATH)/*.h
	rm -rf $(INC_BASE_PATH)/linker
	rm -rf $(INC_BASE_PATH)/*.a
	rm -rf ../../out/intorobot_stm32_server
	rm -rf ../../out/intorobot_stm32_server.tar.gz	




#生成基本库		依赖库		所有.o文件	
release_base_lib:check_external_deps $(ALLOBJ)
	cp -rf ../../core-common-lib/build/libcore-common-lib.a $(LIB_BASE_PATH)/
#application.o文件不打入库
	mv ./obj/src/application.o ./obj/
	$(AR) -r $(LIB_BASE_PATH)/libintorobot_base.a ./obj/src/*.o  
	mv ./obj/application.o ./obj/src/ 


#合并库只使用一个库
#	mkdir   $(LIB_BASE_PATH)/lib_temp
#	mv $(LIB_BASE_PATH)/libintorobot_base.a $(LIB_BASE_PATH)/lib_temp/
#	mv $(LIB_BASE_PATH)/libcore-common-lib.a $(LIB_BASE_PATH)/lib_temp/
	
#	cd $(LIB_BASE_PATH)/lib_temp;$(AR) -x libintorobot_base.a 
#	cd $(LIB_BASE_PATH)/lib_temp;$(AR) -x libcore-common-lib.a

#	$(AR) -r $(LIB_BASE_PATH)/libintorobot_bottom.a $(LIB_BASE_PATH)/lib_temp/*.o  
#	rm -rf $(LIB_BASE_PATH)/lib_temp

	

#拷贝固件库源码	(目前不展示)	
#	cp ../src/*.cpp $(SRC_BASE_PATH)		

#拷贝公共库头源码
#	cp ../src/extend/*.cpp $(SRC_BASE_PATH)
	
#拷贝固件库头文件
	cp ../src/*.h $(INC_BASE_PATH) 	
	cp ../../core-common-lib/STM32_USB-FS-Device_Driver/inc/*.h $(INC_BASE_PATH) 
	cp ../../core-common-lib/STM32F10x_StdPeriph_Driver/inc/*.h $(INC_BASE_PATH) 
	cp ../../core-common-lib/Core-Common/inc/*.h $(INC_BASE_PATH) 
	cp ../../core-common-lib/CMSIS/Device/ST/STM32F10x/Include/*.h $(INC_BASE_PATH) 
	cp ../../core-common-lib/CMSIS/Include/*.h $(INC_BASE_PATH) 

#拷贝公共库头文件
#	cp ../src/extend/*.h $(INC_BASE_PATH)



#拷贝链接脚本
	cp -rf ../linker $(SCRIPT_BASE_PATH)/

#拷贝start.s  到连接脚本目录
	cp -rf ./obj/src/startup/*.o $(SCRIPT_BASE_PATH)/linker/


	
	@echo =====================
	@echo "release_base_lib done"
	@echo =====================

#清除基本库
clean_base_lib:
	$(RMDIR) $(BUILD_PATH)	
	@$(MAKE) -C $(PROJECT_DIR)$(LIB_CORE_COMMON_PATH)build clean $(MAKE_ARGS)
	
	rm -rf $(LIB_BASE_PATH)/*
	rm -rf $(INC_BASE_PATH)/*
#	rm -rf $(SRC_BASE_PATH)/*
	rm -rf $(SCRIPT_BASE_PATH)/linker
	@echo =====================
	@echo "clean_base_lib done"
	@echo =====================




#生成用户.o文件
release_usr_obj:$(CPPOBJ_USR)
#	$(AR) -r $(LIB_USR_PATH)/libintorobot_usr.a $(LIB_USR_PATH)/*.o
#	@rm -rf $(LIB_USR_PATH)/*.o
#	@rm -rf $(LIB_USR_PATH)/*.d
	@echo =====================
	@echo "release_usr_obj done"
	@echo =====================



#用户.o文件生成规则
$(ID_PATH)%.o:$(ID_PATH)%.cpp
	@echo Building file: $<
	@echo Invoking: ARM GCC CPP Compiler
#	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	@echo


$(LIB_PUBLIC_DIR)%.o:$(LIB_PUBLIC_DIR)%.cpp
	@echo Building file: $<
	@echo Invoking: ARM GCC CPP Compiler
#	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	@echo




#获取的用户库.h文件
LIB_USR_INC_FILE=$(call search_target_file,$(LIB_USR_PATH),*.h)


#需要链接到的.h文件
LIB_USR_INC_FILE_OBJ=$(subst /src/,/, $(LIB_USR_INC_FILE))



#获取的公共库
LIB_PUBLIC_INC_FILE=$(call search_target_file,$(LIB_PUBLIC_PATH),*.h)

#需要链接到的.h文件
LIB_PUBLIC_INC_FILE_OBJ=$(subst /src/,/, $(LIB_PUBLIC_INC_FILE))




IN_INC_FILE=$(LIB_USR_INC_FILE) $(LIB_PUBLIC_INC_FILE)
IN_INC_FILE_OBJ=$(LIB_USR_INC_FILE_OBJ) $(LIB_PUBLIC_INC_FILE_OBJ)







creat_ln_inc:$(IN_INC_FILE)


$(IN_INC_FILE):
	if [ ! -e $(subst /src/,/, $@) ]; then ln $@ $(subst /src/,/, $@) ;  fi


clean_ln_inc:
	rm -rf $(IN_INC_FILE_OBJ)











#清除用户库.o文件
LIB_USR_OBJ= $(patsubst %,%*.o, $(LIB_USR_PATH))
LIB_USR_DBJ= $(patsubst %,%*.d*, $(LIB_USR_PATH))


clean_usr_lib:clean_ln_inc
	@echo	======================
	rm -rf $(LIB_USR_OBJ)
	rm -rf $(LIB_USR_DBJ)
	@echo =====================
	@echo "clean_usr_lib done"
	@echo =====================


#清除公共库.o文件
LIB_PUBLIC_OBJ= $(patsubst %,%*.o, $(LIB_PUBLIC_PATH))
LIB_PUBLIC_DBJ= $(patsubst %,%*.d*, $(LIB_PUBLIC_PATH))

clean_public_lib:clean_ln_inc
	@echo	======================
	rm -rf $(LIB_PUBLIC_OBJ)
	rm -rf $(LIB_PUBLIC_DBJ)
	@echo =====================
	@echo "clean_public_lib done"
	@echo =====================







#生成第三方库
#release_sec_lib:$(CPPOBJ_SEC)
#	$(AR) -r $(LIB_SEC_PATH)/libintorobot_sec.a $(SRC_SEC_PATH)/*.o
#	@rm -rf $(LIB_SEC_PATH)/*.o
#	@rm -rf $(LIB_SEC_PATH)/*.d
#	@echo =====================
#	@echo "release_sec_lib done"
#	@echo =====================

#第三方库.o文件生成规则
#$(CPPOBJ_SEC):$(CPPSRC_SEC)
#	@echo Building file: $<
#	@echo Invoking: ARM GCC CPP Compiler
#	$(MKDIR) $(dir $@)
#	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
#	@echo

#清除第三方库
#clean_sec_lib:
#	rm -rf $(LIB_SEC_PATH)/*
#	rm -rf $(SRC_SEC_PATH)/*.o
#	rm -rf $(SRC_SEC_PATH)/*.d
#	@echo =====================
#	@echo "clean_sec_lib done"
#	@echo =====================



elf: $(TARGETDIR)$(TARGET).elf
bin: $(TARGETDIR)$(TARGET).bin
hex: $(TARGETDIR)$(TARGET).hex

# Program the core using dfu-util. The core should have been placed
# in bootloader mode before invoking 'make program-dfu'
program-dfu: $(TARGETDIR)$(TARGET).bin
	@echo Flashing using dfu:
	$(DFU) -d 1d50:607f -a 0 -s 0x08005000:leave -D $<

# Program the core using the cloud. INTORBT_CORE_ID and INTORBT_ACCESS_TOKEN must
# have been defined in the environment before invoking 'make program-cloud'
program-cloud: $(TARGETDIR)$(TARGET).bin
	@echo Flashing using cloud API, CORE_ID=$(INTORBT_CORE_ID):
	$(CURL) -X PUT -F file=@$< -F file_type=binary $(CLOUD_FLASH_URL)

# Display size
size: $(TARGETDIR)$(TARGET).elf
	@echo Invoking: ARM GNU Print Size
	$(SIZE) --format=berkeley $<
	@echo

# Create a hex file from ELF file
%.hex : %.elf
	@echo Invoking: ARM GNU Create Flash Image
	$(OBJCOPY) -O ihex $< $@
	@echo

# Create a bin file from ELF file
%.bin : %.elf
	@echo Invoking: ARM GNU Create Flash Image
	$(OBJCOPY) -O binary $< $@
	@echo







#删除原来的库路径
LDFLAGS_PLATFORM =$(patsubst -L%, , $(LDFLAGS))
LDFLAGS_PLATFORM :=$(patsubst -lcore-common-lib, , $(LDFLAGS_PLATFORM))

#替换新的连接脚本路径
#LDFLAGS_PLATFORM  :=$(patsubst -T../%,-T$(SCRIPT_BASE_PATH)/%, $(LDFLAGS_PLATFORM))


#删除 两个选线 提到最前面
LDFLAGS_PLATFORM  :=$(patsubst -T../%, , $(LDFLAGS_PLATFORM))
LDFLAGS_PLATFORM  :=$(patsubst -nostartfiles -Xlinker --gc-sections, , $(LDFLAGS_PLATFORM))


#替换新的map文件路径
LDFLAGS_PLATFORM  :=$(patsubst %core-firmware.map,%$(BIN_PLATFORM_OUT)/platform.map, $(LDFLAGS_PLATFORM))





#链接库单独
LDFLAGS_BASE =-L$(LIB_BASE_PATH) -lintorobot_base -lcore-common-lib


#添加基本库路径
#LDFLAGS_PLATFORM +=-L$(LIB_BASE_PATH)
#LDFLAGS_PLATFORM +=-lintorobot_base
#LDFLAGS_PLATFORM +=-lcore-common-lib

#LDFLAGS_PLATFORM +=-lintorobot_bottom




#添加第三方库
#LDFLAGS_PLATFORM +=-L$(LIB_SEC_PATH)
#LDFLAGS_PLATFORM +=-lintorobot_sec

#LDFLAGS_PLATFORM +=$(LIB_SEC_A)



#添加用户库
#LDFLAGS_PLATFORM +=-L$(LIB_USR_PATH)
#LDFLAGS_PLATFORM +=-lintorobot_usr



#根据基本库base 第三方库sec 用户库usr 连接生成最终的 bin文件

#release_platform_bin:creat_ln_inc release_usr_obj elf_platform hex_platform bin_platform
release_platform_bin:creat_ln_inc release_usr_obj elf_platform  bin_platform
#	cp -rf platform.* $(BIN_PLATFORM_OUT)/
#	rm -rf platform.* 
	@echo	======================
	@echo	"release_platform_bin done"	
	@echo	======================


elf_platform: $(BIN_PLATFORM_OUT)/platform.elf
bin_platform: $(BIN_PLATFORM_OUT)/platform.bin
hex_platform:$(BIN_PLATFORM_OUT)/platform.hex


$(BIN_PLATFORM_OUT)/platform.elf: $(CPPSRC_USR)  $(LIB_BASE_PATH)libcore-common-lib.a $(LIB_BASE_PATH)libintorobot_base.a
#	rm -rf $(LIB_BASE_PATH)/libcore-common-lib
#	rm -rf $(LIB_BASE_PATH)/libintorobot_base

#	mkdir $(LIB_BASE_PATH)/libcore-common-lib/
#	mkdir $(LIB_BASE_PATH)/libintorobot_base
	
#	cp -rf $(LIB_BASE_PATH)/libcore-common-lib.a  $(LIB_BASE_PATH)/libcore-common-lib/
#	cp -rf $(LIB_BASE_PATH)/libintorobot_base.a $(LIB_BASE_PATH)/libintorobot_base/

#	cd $(LIB_BASE_PATH)/libcore-common-lib  $(LIB_BASE_PATH)/libcore-common-lib/;$(AR) -x libcore-common-lib.a
#	cd $(LIB_BASE_PATH)/libintorobot_base;$(AR) -x libintorobot_base.a 

	@echo =============================
#	sleep 100

#	$(CPP)  $(CPPOBJ_USR) $(LIB_BASE_PATH)/libintorobot_base/*.o  --output $(BIN_PLATFORM_OUT)/platform.elf  $(LDFLAGS_PLATFORM)


	$(CPP) $(LDFLAGS_START) $(CFLAGS) $(CPPOBJ_USR) $(LDFLAGS_BASE) $(LDFLAGS_PLATFORM) --output $(BIN_PLATFORM_OUT)/platform.elf



#	rm -rf $(LIB_BASE_PATH)/libintorobot_base


		
#	$(CPP) $(CFLAGS) ./obj/src/startup/*.o $(SRC_USR_PATH)/*.o --output $(BIN_PLATFORM_OUT)/platform.elf  $(LDFLAGS_PLATFORM)



SRC_USR_OBJ=$(ID_PATH)/src/*.o
SRC_USR_DBJ=$(ID_PATH)/src/*.d*

clean_platform_bin:clean_usr_lib
	@echo	======================
	rm -rf $(SRC_USR_OBJ)
	rm -rf $(SRC_USR_DBJ)
	rm -rf $(BIN_PLATFORM_OUT)/*
	@echo	======================
	@echo	"clean_platform_bin done"	
	@echo	======================





$(TARGETDIR)$(TARGET).elf : check_external_deps $(ALLOBJ)
	@echo Building target: $@
	@echo Invoking: ARM GCC C++ Linker
	$(MKDIR) $(dir $@)
	$(CPP) $(CFLAGS) $(ALLOBJ) --output $@ $(LDFLAGS)
	@echo

# Check for external dependancies are up to date
# Note: Since this makefile has no knowledge of depenancies for
#       the external libs, make must be called on the libs for
#       every build. Targets which depend directly on this recipie
#       will then always be rebuilt, ie. $(TARGET).elf
check_external_deps:
	@echo Building core-common-lib
	@$(MAKE) -C $(PROJECT_DIR)$(LIB_CORE_COMMON_PATH)build $(MAKE_ARGS)
	@echo
	#@echo Building core-communication-lib
	#@$(MAKE) -C $(PROJECT_DIR)$(LIB_CORE_COMMUNICATION_PATH)build $(MAKE_ARGS)
	#@echo

# Tool invocations

# C compiler to build .o from .c in $(BUILD_DIR)
$(BUILD_PATH)%.o : $(SRC_PATH)%.c
	@echo Building file: $<
	@echo Invoking: ARM GCC C Compiler
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo

# Assember to build .o from .S in $(BUILD_DIR)
$(BUILD_PATH)%.o : $(SRC_PATH)%.S
	@echo Building file: $<
	@echo Invoking: ARM GCC Assember
	$(MKDIR) $(dir $@)
	$(CC) $(ASFLAGS) -c -o $@ $<
	@echo

# CPP compiler to build .o from .cpp in $(BUILD_DIR)
# Note: Calls standard $(CC) - gcc will invoke g++ as appropriate
$(BUILD_PATH)%.o : $(SRC_PATH)%.cpp
	@echo Building file: $<
	@echo Invoking: ARM GCC CPP Compiler
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	@echo

# Other Targets



clean_all:clean clean_base_lib  clean_platform_bin 




clean:
	
	$(RM) $(ALLOBJ) $(ALLDEPS) $(TARGETDIR)$(TARGET).elf $(TARGETDIR)$(TARGET).bin $(TARGETDIR)$(TARGET).hex $(TARGETDIR)$(TARGET).map
	$(RMDIR) $(BUILD_PATH)
	@echo
	@echo Clean core-common-lib
# Should clean invoke clean on the dependant libs as well? Sure..
	@$(MAKE) -C $(PROJECT_DIR)$(LIB_CORE_COMMON_PATH)build clean $(MAKE_ARGS)
	rm -rf ../../out/core-firmware.*
	@echo
	#@echo Clean core-communication-lib
	#@$(MAKE) -C $(PROJECT_DIR)$(LIB_CORE_COMMUNICATION_PATH)build clean $(MAKE_ARGS)
	#@echo

.PHONY: all clean clean_all intorobot_stm32 release_base_lib clean_base_lib  check_external_deps elf bin hex size program-dfu program-cloud $(IN_INC_FILE) clean_ln_inc
.SECONDARY:

# Include auto generated dependency files
-include $(ALLDEPS)

