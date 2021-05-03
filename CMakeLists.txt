######################## project details ##########################
cmake_minimum_required(VERSION 3.13)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# project detail
project(mcpp VERSION 1.0 DESCRIPTION "math library for cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../out)

# cpp standard (c++14)
set(CMAKE_CXX_STANDARD 14)

# flags
message("NO-PLOT=${NO-PLOT}")
message("NO-TEST=${NO-TEST}")

######################## files ####################################
# Directories
include_directories(src/plot)
include_directories(src/variables)
include_directories(src/stats)
include_directories(src/calculus)
include_directories(src/misc)
include_directories(src/vectors)
include_directories(includes)

# Files
file(GLOB_RECURSE SRC "src/*.cpp")
file(GLOB_RECURSE HPP "includes/*.hpp")

######################### build ###########################
# No plot
if(NO-PLOT)
    message("No ploting functionality")
    INSTALL(DIRECTORY
    "includes/" DESTINATION include/${PROJECT_NAME}
    PATTERN "includes/plot/" EXCLUDE
    PATTERN "includes/plot.hpp" EXCLUDE)
# There is plot
else()
    #SFML
    # to find sfml 
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/lib/SFML-2.5.1/cmake/Modules")
    find_package(SFML 2 COMPONENTS graphics window system)
    if(SFML_FOUND)
        message("SFML was found")
    else()
        add_subdirectory(lib/SFML-2.5.1)
    endif()

    # Library
    add_library(mcpp SHARED ${SRC} ${HPP})
    set_target_properties(
        mcpp PROPERTIES 
        VERSION ${PROJECT_VERSION})

    target_link_libraries(mcpp sfml-graphics sfml-window sfml-system)

    install(TARGETS mcpp
        LIBRARY DESTINATION lib
    )

    INSTALL(DIRECTORY
        "includes/" DESTINATION include/${PROJECT_NAME}
    )

    install(CODE "execute_process(COMMAND ldconfig)")
endif()

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

    # variables
    file(GLOB var_src "tests/variables/*.cpp")
    add_executable(test_matrix ${var_src})

    # vectors 
    file(GLOB vec_src "tests/vectors/*.cpp")
    add_executable(test_vector ${vec_src})

    # calculus 
    file(GLOB cal_src "tests/calculus/*.cpp")
    add_executable(test_calculus ${cal_src})

    #-lgtest -lpthread 
    if(NO-PLOT)
        target_link_libraries(test_matrix gtest pthread) 
        target_link_libraries(test_vector gtest pthread) 
        target_link_libraries(test_calculus gtest pthread) 
    else()
        target_link_libraries(test_matrix mcpp gtest pthread)  
        target_link_libraries(test_vector mcpp gtest pthread) 
        target_link_libraries(test_calculus mcpp gtest pthread) 
        endif()
endif()