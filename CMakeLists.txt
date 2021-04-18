######################## project details ##########################
cmake_minimum_required(VERSION 3.10)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(mcpp VERSION 1.0.1 DESCRIPTION "math library for cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../out)

# cpp standard (c++14)
set(CMAKE_CXX_STANDARD 14)

####################### source files ##############################

#SFML
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/lib/SFML-2.4.2")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/lib/SFML-2.4.2/cmake/Modules")
find_package(SFML 2 REQUIRED graphics window system)
if(NOT SFML_FOUND)
    add_subdirectory(lib/SFML-2.4.2)
endif()

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

# vectors 
file(GLOB vec_src "tests/vectors/*.cpp")
add_executable(test_vector ${vec_src})
target_link_libraries(test_vector mcpp gtest pthread) #-lgtest -lpthread 
