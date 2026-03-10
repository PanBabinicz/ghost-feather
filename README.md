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

# Newlib

> To use newlib with libopencm3 it is necessary to recomplie the libc to be able to use hard floating point numbers which use on-chip FPU.
> The second option is to use soft floating point numbers but the speed will be slower.

# Marco Paland printf implementation

# DFU script

> **Description**
>
> The script enables firmware update over USART. It allows users to upload binary firmware files to microcontroller-based devices with minimal effort.
> The script handles communication setup, data formatting, and transmission to ensure reliable updates.

> **Usage**
>
> ```console
> ~ python3 dfu_usart.py <binary> <port> <baudrate>
> ```
>
> - `<binary>`:   The firmware to be uploaded.
> - `<port>`:     The name of the serial port connected to the target device (e.g., /dev/tty.usbmodem).
> - `<baudrate>`: The communication speed in bits per second (e.g., 9600, 115200).

# SOCAT tool

> **Usage**
>
> ```console
> ~ socat -d -d PTY,raw,echo=0 PTY,raw,echo=0
> ~ stty -f /dev/ttysxxx 115200
> ~ screen /dev/ttysxxx 115200
> ```

# Unit tests

> **Description**
>
> The unit tests verify the functionality, reliability, and error handling of embedded system controllers using Google Test (GTest).
>
> They cover various scenarios, including:
> - Core functionality validation.
> - Boundary condition testing.
> - Error handling and fault tolerance.
> - Performance and efficiency checks.

> **Usage**
>
> ```console
> ~ cmake -G "Ninja" -S . -B build -DPROJECT_ROOT_DIR=$(pwd)/../..
> ~ cmake --build build
> ~ cd build && ctest
> ```

# Conda

## What is Conda?

> Conda is an open-source **package manager and environment manager** used for installing, running, and
> updating software packages and their dependencies. It is widely used in data science, machine learning,
> and scientific computing because it simplifies managing complex software environments.
>
> Unlike `pip`, which only installs Python packages, **Conda can manage packages written in multiple languages**
> (such as Python, R, and C libraries) and handles system-level dependencies as well.
>
> Conda is distributed with platforms such as:

- **Anaconda** – a large distribution that includes many preinstalled scientific packages.
- **Miniconda** – a lightweight version that installs only Conda and Python.

## Why Use Conda?

> Conda helps solve common development problems:

- **Dependency management** – automatically installs required libraries.
- **Environment isolation** – different projects can use different package versions.
- **Cross-language support** – works with Python, R, and other tools.
- **Reproducibility** – environments can be exported and recreated.

> Example: one project may require `Python 3.9` while another requires `Python 3.11`. Conda allows both to
> coexist without conflicts.

## Creating an Environment

> A Conda environment is an isolated workspace containing its own Python version and installed packages.
>
> Create a new environment:

```bash
conda create -n myenv python=3.10
```

Here:
- `-n myenv` specifies the environment name
- `python=3.10` installs a specific Python version

## Activating an Environment

> Before using an environment, it must be activated.

```bash
conda activate myenv
```

> After activation, all installed packages and Python commands will come from this environment.
>
> To deactivate:

```bash
conda deactivate
```

## Installing Packages

> Packages can be installed directly into the active environment.

```bash
conda install numpy pandas matplotlib
```

> Conda will automatically resolve and install required dependencies.

## Listing Environments

> To see all available environments:

```bash
conda env list
```

> or:

```bash
conda info --envs
```

## Removing an Environment

> If an environment is no longer needed, it can be deleted:

```bash
conda remove -n myenv --all
```

## Exporting an Environment

> To share or reproduce an environment:

```bash
conda env export > environment.yml
```

> This file can later be used to recreate the same environment.

## Recreating an Environment

```bash
conda env create -f environment.yml
```

> This installs all packages and dependencies exactly as defined in the exported file.
