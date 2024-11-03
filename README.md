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
