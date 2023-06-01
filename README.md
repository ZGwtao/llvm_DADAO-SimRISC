# LLVM CodeGen for DADAO-SimRISC
DADAO-arch::SimRISC ISA extension for llvm CodeGen. This project is another approach beside [DADAO-TCH-llvm](https://github.com/gxt/DADAO/tree/master/TCH-llvm) to construct the toolchain that support SimRISC instruction system based on LLVM.
## Motivation
It has long been my desire to build a compiler backend from scratch for the DADAO-SimRISC project, and I am currently pursuing this goal by exploring different approaches.
I plan to tackle this mission by utilizing the LLVM-CodeGen platform, with the following steps:
- Developing a target agnostic LLVM-CodeGen backend demo and ensuring it runs smoothly.
- Populating the demo with target information for the DADAO & SimRISC instruction system.
- Exploring dynamic linking support (PIC), and considering the implementation of various optimization techniques
