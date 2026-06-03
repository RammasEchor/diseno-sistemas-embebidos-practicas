# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(nordic-blinky)

file(GLOB_RECURSE app_sources
    src/app/*.c 
    src/services/*.c 
    src/hal/*.c 
    src/domain/*.c
)

target_sources(app PRIVATE ${app_sources})
target_include_directories(app PRIVATE src src/app src/domain src/services src/hal)
