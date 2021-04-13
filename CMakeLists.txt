######################## project details ##########################
cmake_minimum_required(VERSION 3.7.2)
project(mcpp VERSION 1.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../out)

# cpp standard (c++14)
set(CMAKE_CXX_STANDARD 14)

####################### source files ##############################
add_subdirectory(lib/SFML-2.5.1)

include_directories(src/plot)
include_directories(src/variables)
include_directories(src/stats)
include_directories(src/calculus)
include_directories(src/misc)
include_directories(src/vectors)
include_directories(includes)

file(GLOB_RECURSE SRC "src/*.cpp")
add_executable(mcpp ${SRC} includes/mcpp.hpp)
target_link_libraries(mcpp sfml-graphics sfml-window sfml-system)

####################### testing ##############################
add_subdirectory(lib/googletest)

include_directories(tests/plot)
include_directories(tests/variables)
include_directories(tests/stats)
include_directories(tests/calculus)
include_directories(tests/misc)
include_directories(tests/vectors)

# variables
file(GLOB var_src "tests/variables/*.cpp")
add_executable(test_matrix ${var_src})
target_link_libraries(test_matrix gtest pthread) #-lgtest -lpthread 
