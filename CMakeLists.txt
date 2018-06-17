cmake_minimum_required(VERSION 3.10)
project(LZW C)

set(CMAKE_C_STANDARD 99)

add_executable(LZW coder.c decoder.c define.h main.c bits.h)
target_link_libraries(LZW /home/toxaxab/CLionProjects/bits/cmake-build-debug/libbits.so)