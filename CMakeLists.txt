cmake_minimum_required(VERSION 3.1)

project(libBG)
add_library(bg src/bigint.h src/bigint.cpp src/fft.h src/fft.tcc)
target_include_directories(bg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_definitions(bg PUBLIC BIGINT_FFT_TRIGGER=0x1000000)
set_property(TARGET bg PROPERTY CXX_STANDARD 98)
