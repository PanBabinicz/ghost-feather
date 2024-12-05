# Ghost Feather

[![GitHub tag (with filter)](https://img.shields.io/github/v/tag/PanBabinicz/ghost-feather?style=plastic&label=latest)](https://github.com/PanBabinicz/ghost-feather/releases/latest)

> [!NOTE]
> **Please bear in mind that the workspace was primarily created for enjoyment
> and educational endeavors.**

> The MIT License (MIT)
>
> Copyright (c) 2011-2024 The Bootstrap Authors
>
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in
> all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
> THE SOFTWARE.

# Compilation process

> [!NOTE]
> **The current compilation process will be changed**

```console
~ arm-none-eabi-gcc -g -c -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mcpu=cortex-m7 -mthumb \
                          -I memory -I bootloader \
                          startup/stm32f722xx/stm32722xx_startup.c -o build/stm32f722xx_startup.o
```

```console
~ arm-none-eabi-gcc -g -c -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mcpu=cortex-m7 -mthumb \
                          -I libopencm3/include -I memory -DSTM32F7 \
                          bootloader/stm32f722xx_first_bootloader.c -o build/stm32f722xx_first_bootloader.o
```

```console
~ arm-none-eabi-as -g vectortable/stm32f722xx/stm32f722xx_vectortable.S -o build/stm32f722xx_vectortable.o
```

```console
~ arm-none-eabi-gcc -g -nostartfiles -nostdlib -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mcpu=cortex-m7 -mthumb \
                       build/stm32f722xx_first_bootloader.o build/stm32f722xx_startup.o build/stm32f722xx_vectortable.o -o build/stm32f722xx_first_bootloader.elf \
                       -T linkerscript/stm32f722xx/stm32f722xx_bootloader.ld -L linkerscript/stm32f722xx -L libopencm3/lib -lopencm3_stm32f7
```

## CMake generators

> **Unix Makefiles**
>
> ```console
> ~ cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=arm-none-eabi-toolchain.cmake
> ~ cd build
> ~ cmake --build . --config Debug
> ```

> **Ninja Multi-Config**
>
> ```console
> ~ cmake -G "Ninja Multi-Config" -S . -B build -DCMAKE_TOOLCHAIN_FILE=arm-none-eabi-toolchain.cmake
> ~ cd build
> ~ cmake --build . --config Debug
> ```

# How to program

> For now, CMake generates two elf files. Each of these files needs to be uploaded to the device.

# Newlib

> To use newlib with libopencm3 it is necessary to recomplie the libc to be able to use hard floating point numbers which use on-chip FPU.
> The second option is to use soft floating point numbers but the speed will be slower.

# Marco Paland printf implementation

# DFU script
