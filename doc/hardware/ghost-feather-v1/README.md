# 👻 Ghost Feather v1

## Introduction

> [!NOTE]
> **Please bear in mind that the pcb was primarily created for enjoyment
> and educational endeavors.**

> Ghost Feather v1 is a compact, four-layer PCB built for embedded systems and robotics exploration 🤖.
> Designed with versatility and performance in mind, it brings together a robust set of components for
> a wide range of applications.
>
> This is the first version of the board, featuring only basic functionality – telemetry and advanced
> features are not yet included.

> ✨ Key Features
>
> - 🧠 STM32F722RET6 – Powerful Cortex-M7 MCU at the heart of the board
>
> - 🌀 BMI270 IMU – 6-axis motion sensing for orientation and motion tracking
>
> - 🧪 Voltage Level Shifters – Built using MOSFETs to safely bridge logic levels
>
> - 🛠️ SWD Tag Connector – For easy debugging and programming
>
> - 🔌 4x PicoBlade Connectors – For connecting ESCs (Electronic Speed Controllers)
>
> - 📡 1x PicoBlade Connector – For connecting an RF radio module

## 📃 Schematic

> This section includes the complete schematic of the board, created with KiCad.
> It outlines the core circuitry, microcontroller wiring, level shifters, connectors, and power.

![Schematic](https://github.com/PanBabinicz/ghost-feather/blob/develop/doc/hardware/ghost-feather-v1/screenshots/ghost-feather-v1-kicad-schematic.png)

## 🛠️ PCB

> This section showcases the 3D views of the PCB, generated using KiCad.
> These models provide a clear visual reference for component placement,
> board layout, and connector orientation.

### KiCAD 3D Model
![Front](https://github.com/PanBabinicz/ghost-feather/blob/develop/doc/hardware/ghost-feather-v1/screenshots/ghost-feather-v1-pcb-front.png)
![Rear](https://github.com/PanBabinicz/ghost-feather/blob/develop/doc/hardware/ghost-feather-v1/screenshots/ghost-feather-v1-pcb-rear.png)

### Manufactured PCB
![Bench](https://github.com/PanBabinicz/ghost-feather/blob/develop/doc/hardware/ghost-feather-v1/screenshots/real-drone-1.jpg)
![Floor](https://github.com/PanBabinicz/ghost-feather/blob/develop/doc/hardware/ghost-feather-v1/screenshots/real-drone-2.jpg)

### Preparation for tuning PID gains
![OnBench](https://github.com/PanBabinicz/ghost-feather/blob/develop/doc/hardware/ghost-feather-v1/screenshots/real-drone-prepared-for-tuning.jpg)
