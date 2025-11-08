#!/bin/bash

cd /workspace/thirdparty/libcsp
rm -rf build
./waf configure --with-os=freertos --toolchain=arm-none-eabi- --includes=/workspace/thirdparty/FreeRTOS-Kernel,/workspace/thirdparty/FreeRTOS-Kernel/include,/workspace/thirdparty/FreeRTOS-Kernel/portable/GCC/ARM_CM3,/workspace/embedded/Core/Inc
./waf clean
./waf build
cd -
