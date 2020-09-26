cmake_minimum_required(VERSION 3.5)
project(logging-lib CXX)

if(WIN32)
set(COMPILE_OPTIONS)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)

else()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")
set(COMPILE_OPTIONS -Wall -Wextra -pedantic -Werror)
endif()

option(build_examples "Building examples" OFF)

find_package(Threads)

add_library(logger SHARED src/base_logger.cpp
                          src/logging_manager.cpp)

target_include_directories(logger PUBLIC include)
target_compile_options(logger PRIVATE ${COMPILE_OPTIONS})
install(TARGETS logger DESTINATION bin)

if(build_examples)
add_executable(loggertest examples/loggertest.cpp)
target_include_directories(loggertest PUBLIC include)
target_link_libraries(loggertest logger ${CMAKE_THREAD_LIBS_INIT})
target_compile_options(loggertest PRIVATE ${COMPILE_OPTIONS})
install(TARGETS loggertest DESTINATION bin)
endif()