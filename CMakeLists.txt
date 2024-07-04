cmake_minimum_required(VERSION 3.13)

set(PICO_BTSTACK_PATH ${CMAKE_CURRENT_LIST_DIR}/btstack)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(main_app
    main_app.c
    bt_hid.c
)

pico_enable_stdio_uart(main_app 1)

target_include_directories(main_app PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(main_app
    hardware_pwm
    hardware_gpio    
    pico_stdlib
    pico_cyw43_arch_none
    pico_btstack_classic
    pico_btstack_ble
    pico_btstack_cyw43
    pico_multicore
)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(main_app)