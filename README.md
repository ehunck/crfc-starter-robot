# CRFC Starter Robot Platform

## Overview

## Pre-Requisites

### Windows

Install Windows Subsystem for Linux (wsl)

## Project Setup

Clone the repo:

```bash
....
```

Update all of the submodules (This pulls in the pico-sdk.)

```bash
git submodule update --init --recursive
```


This repository was setup by following the instructions here:

https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#quick-start-your-own-project

Install Prerequisites:

....

## Build the Project

```bash
mkdir build
cd build
cmake -DPICO_BOARD=pico_w -DPICO_SDK_PATH=../pico-sdk ../
make main_app
```

## Flash the Firmware

You now have `main_app.elf` to load via a debugger, or `main_app.uf2` that can be installed and run on your Raspberry Pi Pico via drag and drop.