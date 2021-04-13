######################## project details ##########################
cmake_minimum_required(VERSION 3.9)
project(mcpp VERSION 1.0.1 DESCRIPTION "math library for cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../out)

# cpp standard (c++14)
set(CMAKE_CXX_STANDARD 14)

####################### source files ##############################
add_subdirectory(lib/SFML-2.5.1 EXCLUDE_FROM_ALL)

include_directories(src/plot)
include_directories(src/variables)
include_directories(src/stats)
include_directories(src/calculus)
include_directories(src/misc)
include_directories(src/vectors)

include_directories(includes)

file(GLOB_RECURSE SRC "src/*.cpp")
file(GLOB_RECURSE HPP "includes/*.hpp")

add_library(mcpp SHARED ${SRC} includes/mcpp.hpp)
set_target_properties(
    mcpp PROPERTIES 
    VERSION ${PROJECT_VERSION})


target_link_libraries(mcpp sfml-graphics sfml-window sfml-system)

install(TARGETS mcpp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

INSTALL(DIRECTORY
    "includes/" DESTINATION include/${PROJECT_NAME}
)

install(CODE "execute_process(COMMAND ldconfig)")

####################### testing ##############################
add_subdirectory(lib/googletest EXCLUDE_FROM_ALL)

include_directories(tests/plot)
include_directories(tests/variables)
include_directories(tests/stats)
include_directories(tests/calculus)
include_directories(tests/misc)
include_directories(tests/vectors)

# variables
file(GLOB var_src "tests/variables/*.cpp")
add_executable(test_matrix ${var_src})
target_link_libraries(test_matrix mcpp gtest pthread) #-lgtest -lpthread 
