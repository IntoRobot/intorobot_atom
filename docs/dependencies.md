## 1. 下载和安装依赖包

如果您希望本地编译固件，需要安装如下依赖包：

1. [GCC for ARM Cortex processors](#1-gcc-for-arm-cortex-processors)
2. [Make](#2-make)
3. [Git](#5-git)


#### 1. GCC for ARM Cortex processors

intorobot atom 使用一个stm32 ARM Cortex M3 CPU。 所有的代码通过GNU GCC交叉编译环境编译。
编译要求 版本4.9.3 20150529 以上ARM GCC编译环境，否则将报错。

**Linux and Windows**:
- 下载和安装 版本4.9.x。 地址: https://launchpad.net/gcc-arm-embedded

**OS X** 用户需要使用homebrew安装[Homebrew](http://brew.sh/):

- `brew tap PX4/homebrew-px4`
- `brew update`
- `brew install gcc-arm-none-eabi-49`
- `arm-none-eabi-gcc --version` (要求v4.9.x)

#### 2. Make
为了把你的代码转换成二进制文件，你需要安装'make'工具。
下载地址：http://gnuwin32.sourceforge.net/packages/make.htm

#### 3. Git

下载和安装Git 地址: http://git-scm.com/



