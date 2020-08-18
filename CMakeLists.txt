cmake_minimum_required(VERSION 3.5)
project(logger CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "Debug")
set(COMPILE_OPTIONS -Wall -Wextra -pedantic -Werror)

find_package(Threads)

add_library(logger SHARED src/base_logger.cpp)

target_include_directories(logger PUBLIC include)
target_compile_options(logger PRIVATE ${COMPILE_OPTIONS})

if(build_example)
add_executable(loggertest examples/loggertest.cpp)
target_include_directories(loggertest PUBLIC include)
target_link_libraries(loggertest logger ${CMAKE_THREAD_LIBS_INIT})
target_compile_options(loggertest PRIVATE ${COMPILE_OPTIONS})
endif()