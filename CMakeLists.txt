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

    enable_testing()
    # set(GTEST_ROOT "../lib/googletest" CACHE PATH "Path to googletest")

    # find_package(GTest REQUIRED)
    include(GoogleTest)

    include_directories(tests/variables)
    include_directories(tests/calculus)
    include_directories(tests/algebra)
    include_directories(tests/communication)
    include_directories(tests/mathematics)
    include_directories(tests/numerical)
    include_directories(tests/stats)

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

    # statistics 
    add_executable(test_stats tests/stats/stats_test.cpp)

    #-lgtest -lpthread 
    target_link_libraries(test_matrix gtest pthread)  
    target_link_libraries(test_table gtest pthread)  
    target_link_libraries(test_vector gtest pthread) 
    target_link_libraries(test_calculus gtest pthread) 
    target_link_libraries(test_algebra gtest pthread)
    target_link_libraries(test_stats gtest pthread)

    
    gtest_discover_tests(test_matrix WORKING_DIRECTORY ../out)
    gtest_discover_tests(test_table WORKING_DIRECTORY ../out)
    gtest_discover_tests(test_vector WORKING_DIRECTORY ../out)
    gtest_discover_tests(test_calculus WORKING_DIRECTORY ../out)
    gtest_discover_tests(test_algebra WORKING_DIRECTORY ../out)
    gtest_discover_tests(test_stats WORKING_DIRECTORY ../out)



endif()