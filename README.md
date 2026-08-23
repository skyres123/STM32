# STM32F407 Bare-Metal C Drivers

## Overview
This repository contains a custom, bare-metal C driver library developed entirely at the register level for the STM32F407xx microcontroller family. It is specifically designed and tested for the **STM32F407 Discovery board**. It provides lightweight, highly optimized, and efficient peripheral control without relying on standard HAL or SPL libraries. 

> **Note:** This project is under active development. Drivers and features are continuously being updated and expanded.

## Implemented Peripheral Drivers
*   **Core MCU & Memory Map (`stm32f407xx.h`):** Contains the complete memory map, defining peripheral base addresses for AHB1/2/3 and APB1/2 buses. It includes precise register definition structures for core peripherals like RCC, GPIO, EXTI, SYSCFG, TIM, and USART.
*   **ARM Cortex-M4 System (`Arm_Cortex_M4.h`):** Provides macros and functions for managing the NVIC (Nested Vectored Interrupt Controller), mapping specific IRQ numbers, and configuring the SysTick timer.
*   **GPIO Interface (`gpio.h`):** Supports comprehensive pin initialization, allowing configuration of modes (Input, Output, Alternate Function, Analog), speeds, pull-up/pull-down resistors, and provides direct bit-level operations (read, write, toggle).
*   **Timers (`TIM.h`):** Features driver functions for initializing general-purpose and advanced timers (TIM1 through TIM10), configuring interrupts, and generating PWM or Output Compare signals.
*   **USART (`usart.h`):** Contains a configuration structure to easily set up UART communication with customizable baud rates, word lengths, stop bits, parity checks, and hardware flow control.
*   **Hardware RNG (`RNG.h`):** Includes functions to enable and fetch true 32-bit random values directly from the STM32's internal Random Number Generator hardware.

## Hardware Prerequisites
*   **Target Board:** STM32F407 Discovery (STM32F407G-DISC1)
*   **Toolchain:** Compatible with standard ARM GCC toolchains and IDEs supporting bare-metal development.

## Getting Started
To use these drivers, include the main `stm32f407xx.h` header in your source files to access all structural definitions and base addresses. Link the specific peripheral `.c` files you need for your project during the build process.
