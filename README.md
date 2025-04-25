# STM32 Bare-Metal Embedded Project

## Project Overview  
This project is part of my second-year curriculum at Télécom Paris. The goal is to gain low-level control over the **STM32L475VGT6** (Cortex-M4) microcontroller 
**without relying on any OS or standard libraries**, building everything from scratch. The implementation emphasizes portability, ensuring compatibility across 
all ARMv7-based processors. The entire codebase is written in **C**, using a custom-developed CMSIS library. Debugging is performed via **GDB** and **J-Link** tools
provided by the course instructor.

## Key Features  
- **Bare-metal development**: No OS or external libraries used.  
- **Portable**: Designed to run on any ARMv7 processor.  
- **Custom CMSIS library**: For register naming and hardware abstraction.  
- **Efficient debugging**: Leverages GDB and J-Link for testing.  

## Development Steps  
1. **Linker Script**: Custom memory layout definition for the STM32L475.  
2. **Startup Code (crt0.s)**: Handled initialization of the stack, .data, and .bss sections.  
3. **LED Control**: GPIO configuration for green, blue, and yellow LEDs.  
4. **Clock Configuration**: Enabled and tuned the HSI/PLL clock frequencies.  
5. **CMSIS Integration**: Custom register header files for simplified hardware access.  
6. **UART Setup**: Configured baud rate, interrupts, and transmission protocols.  
7. **LED Matrix Control**: Driver for DM163-based LED matrices via SPI.  
8. **Interrupt Handling**: Implemented NVIC and custom ISRs for peripheral management.  
9. **GPIO Interrupts**: Configured edge/trigger modes for external events.  
10. **TIM2 Utilization**: Timer setup for PWM and time-based tasks.  
11. **XIP Execution**: Code execution directly from external flash memory.  
12. **RAM Optimization**: Critical code sections copied to RAM for faster execution.  

## Tools Used  
- **Hardware**: STM32L475VGT6 (Cortex-M4)  
- **Toolchain**: ARM GCC, Makefile  
- **Debugging**: GDB, J-Link  
- **Libraries**: Custom CMSIS implementation  
