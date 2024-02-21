cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_w_in_c C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init() 

add_executable(pico_w_in_c 
    blink.c
    flash_control.c
)

target_include_directories(pico_w_in_c PRIVATE ${CMAKE_CURRENT_LIST_DIR} )

pico_enable_stdio_usb(pico_w_in_c 1)
pico_enable_stdio_uart(pico_w_in_c 0)

pico_add_extra_outputs(pico_w_in_c)


target_link_libraries(pico_w_in_c 
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    hardware_flash
)
