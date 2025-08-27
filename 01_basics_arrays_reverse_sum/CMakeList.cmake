cmake_minimum_required(VERSION 3.10)
project(01_basics_arrays_reverse_sum)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(array_operations src/main.cpp)

# Включение санитайзеров для отладки памяти
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(array_operations PRIVATE -Wall -Wextra -g)
    target_link_options(array_operations PRIVATE -fsanitize=address,undefined)
endif()