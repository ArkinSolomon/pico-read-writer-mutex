cmake_minimum_required(VERSION 3.13)
project(pico_read_writer_mutex C)

set(CMAKE_C_STANDARD 11)

#if (NOT TARGET pico_stdlib)
#    message(FATAL_ERROR "pico-sdk not found. Please call pico_sdk_init() in the top-level project before adding pico_read_writer_mutex.")
#endif ()

include(FetchContent)
FetchContent_Declare(
        pico-sdk
        GIT_REPOSITORY https://github.com/raspberrypi/pico-sdk.git
        GIT_TAG master
)
FetchContent_MakeAvailable(pico-sdk)

add_library(pico_read_writer_mutex src/read_writer_mutex.c include/read_writer_mutex.h)
target_include_directories(pico_read_writer_mutex PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

target_link_libraries(pico_read_writer_mutex INTERFACE pico_stdlib)