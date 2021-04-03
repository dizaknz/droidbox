cmake_minimum_required(VERSION 3.4.1)

set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")
add_library(native_app_glue STATIC
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -fms-extensions")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

add_library(proj SHARED
        main.c)
target_include_directories(proj PRIVATE ./)
target_include_directories(proj PRIVATE ${ANDROID_NDK}/sources/android/native_app_glue)

target_link_libraries(proj
    android
    native_app_glue
    EGL
    GLESv1_CM
    log)
