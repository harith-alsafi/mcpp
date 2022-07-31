######################## project details ##########################
cmake_minimum_required(VERSION 3.10)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# project detail
project(mcpp VERSION 1.0 DESCRIPTION "math library for cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../out)

# cpp standard (c++17)
set(CMAKE_CXX_STANDARD 17)

# flags
message("NO-TEST=${NO-TEST}")

######################## files ####################################
# Directories
include_directories(includes)

# Files
file(GLOB_RECURSE HPP "includes/*.hpp")

######################### build ###########################
INSTALL(DIRECTORY
"includes/" DESTINATION include/${PROJECT_NAME})
####################### testing ##############################
if(NO-TEST)
    message("No unit-testing")
else()
    add_subdirectory(lib/googletest EXCLUDE_FROM_ALL)

    include_directories(tests/plot)
    include_directories(tests/variables)
    include_directories(tests/stats)
    include_directories(tests/calculus)
    include_directories(tests/misc)
    include_directories(tests/vectors)

    # matrix
    add_executable(test_matrix tests/variables/matrix_test.cpp)

    # table
    add_executable(test_table tests/variables/table_test.cpp)

    # vectors 
    add_executable(test_vector tests/variables/vector_test.cpp)

    # algebra
    add_executable(test_algebra tests/algebra/algebra_test.cpp)

    # calculus 
    file(GLOB cal_src "tests/calculus/*.cpp")
    add_executable(test_calculus ${cal_src})

    #-lgtest -lpthread 
    target_link_libraries(test_matrix gtest pthread)  
    target_link_libraries(test_table gtest pthread)  
    target_link_libraries(test_vector gtest pthread) 
    target_link_libraries(test_calculus gtest pthread) 
    target_link_libraries(test_algebra gtest pthread) 
endif()