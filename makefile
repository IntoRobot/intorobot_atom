############################################################################
# MODULE :                  																				 #
# Filename:     makefile                                                   #
# Version:	 1.0.0 																												 #
# Copyright (c) 2008, ml                                          #
# All rights reserved.                                                     #
# Modification History:                                                    #
# Date	     Name 	Description                                            #
# 2014-11-10	 lbz   	Created                                          #
############################################################################


################################################
### ml cfg
################################################





#编译stm32 bin
intorobot_stm32:
	make -C ./firmware-intorobot/build/ intorobot_stm32


#清除stm32 bin
clean:
	make -C ./firmware-intorobot/build/ clean



#清除所有
clean_all:clean clean_server_pack clean_platform_bin clean_public_lib clean_base_lib
	



#清除基础库
clean_base_lib:
	make -C ./firmware-intorobot/build/ clean_base_lib


#编译基础库
release_base_lib:
	make -C ./firmware-intorobot/build/ release_base_lib



#清除bin、用户代码、用户库
clean_platform_bin:
	make -C ./firmware-intorobot/build/ clean_platform_bin


#清除公共库	
clean_public_lib:
	make -C ./firmware-intorobot/build/ clean_public_lib	


#链接生成最终bin文件
release_platform_bin:
	make -C ./firmware-intorobot/build/ release_platform_bin



release_server_pack:
#	make -C ./firmware-intorobot/build/ clean_base_lib
	make -C ./firmware-intorobot/build/ release_base_lib

	make -C ./firmware-intorobot/build/ clean_platform_bin
	make -C ./firmware-intorobot/build/ release_platform_bin
	
	make -C ./firmware-intorobot/build/ clean_platform_bin
	make -C ./firmware-intorobot/build/ clean_public_lib

#	make -C ./firmware-intorobot/build/ clean_server
	make -C ./firmware-intorobot/build/ release_server


clean_server_pack:
	make -C ./firmware-intorobot/build/ clean_server





help:
	@echo "readme.txt"
	






