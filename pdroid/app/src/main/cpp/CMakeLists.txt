cmake_minimum_required(VERSION 3.4.1)

# build native_app_glue as a static lib
set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")
add_library(native_app_glue STATIC
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

# build app's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

add_library(paddledroid SHARED 
    shader.hpp
    display.hpp
    engine.hpp
    main.cpp)

target_include_directories(paddledroid PRIVATE
    ${ANDROID_NDK}/sources/android/native_app_glue)

# lib dependencies
target_link_libraries(paddledroid
    android
    native_app_glue
    EGL
    GLESv2
    log)
