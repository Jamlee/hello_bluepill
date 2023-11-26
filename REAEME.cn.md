# Hello BluePill
"Hello BluePill" 是基于 Stm32 BluePill 开发板编写的最基础的闪烁LED程序。使用的开发工具如下:
- arm-none-eabi-gcc: 版本 GNU Arm Embedded Toolchain 10.3-2021.10
- openocd: 提供烧录程序能力, 版本 OpenOCD-20231002-0.12.0
- git bash: 提供 rm 等命令, 版本任意。
- mingw64: 提供 make 等命令，mingw-make 复制一份改为 make。版本 GCC 13.2.0, https://winlibs.com/#download-release

# 运行脚本
```
# 1. 编译，进入源码目录 Source\hello_bluepill
make
openocd -f stlink_bluepill.cfg

# 2. 调试
telnet 127.0.0.1 4444
reset init # 重置启动, gbd 中 b main 后执行

# 3. gdb
arm-none-eabi-gdb build/hello_pill.elf
target remote :3333
b main
```