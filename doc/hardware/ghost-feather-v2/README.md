# 👻 Ghost Feather v2


## Introduction

> [!NOTE]  
> **Please bear in mind that the pcb was primarily created for enjoyment  
> and educational endeavors.**

> Ghost Feather v2 is a compact, four-layer PCB built for embedded systems and robotics exploration 🤖.
> This revision evolves the original design into a more capable flight-control-oriented platform,
> integrating additional sensors and support for modern FPV and radio systems.
>
> ✨ This version expands beyond basic functionality, introducing orientation awareness, altitude sensing,
> and improved control reliability.


## ✨ Key Features

- 🧠 STM32F722RET6 – Powerful Cortex-M7 MCU at the heart of the board

- 🌀 BMI088 IMU – High-performance 6-axis sensor optimized for vibration-heavy environments

- 🧭 IIS2MDCTR Magnetometer – 3-axis magnetic field sensing for heading and navigation

- 🌡️ BMP390 Barometer – High-resolution pressure sensor for altitude estimation

- 📡 External ELRS Receiver Support – Designed for use with Radiomaster RP3 (ExpressLRS 2.4 GHz) via CRSF protocol

- 🧪 Voltage Level Shifters – Built using MOSFETs to safely bridge logic levels

- 🛠️ SWD Tag Connector – For easy debugging and programming

- 🔌 4x PicoBlade Connectors – For connecting ESCs (Electronic Speed Controllers)

- 📡 1x PicoBlade Connector – Reserved for RF receiver (UART: CRSF)

- 🎥 FPV Camera Support – Dedicated power and video signal connections for analog FPV systems


## 🔧 Design Notes

- The board is designed to work with external ExpressLRS receivers, such as the Radiomaster RP3, avoiding the
  complexity of onboard RF design.

- Sensor suite upgrades (IMU, magnetometer, barometer) allow for advanced flight control and navigation
  capabilities.

- FPV support is implemented at the hardware level (power + signal routing), without onboard video processing.


## 🚧 Future Improvements

- Blackbox logging (SPI flash)
- OSD support (e.g., AT7456E)
- USB-C interface
- Improved power filtering for analog systems
