cmake_minimum_required(VERSION 3.1)
project(lockpp LANGUAGES CXX VERSION 1.0)

# --------------------------------------------------------------------------------------------------------
# Create library
# --------------------------------------------------------------------------------------------------------

add_library(${PROJECT_NAME} INTERFACE)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_EXTENSIONS OFF CXX_STANDARD_REQUIRED ON)

# --------------------------------------------------------------------------------------------------------
# Include "include" folder
# --------------------------------------------------------------------------------------------------------

target_include_directories(${PROJECT_NAME} INTERFACE "include")

# --------------------------------------------------------------------------------------------------------
# Run tests
# --------------------------------------------------------------------------------------------------------

option(lockpp_tests "Run tests" OFF)

if (lockpp_tests)
    message(STATUS "Building lockpp tests")

    if (NOT TARGET Catch2::Catch2WithMain)
        include(FetchContent)
        FetchContent_Declare(Catch2 GIT_REPOSITORY "https://github.com/catchorg/Catch2" GIT_TAG v2.13.7)
        option(CATCH_BUILD_STATIC_LIBRARY "" ON)
        FetchContent_MakeAvailable(Catch2)
    endif()

    file(GLOB src "tests/*.cpp")
    add_executable(${PROJECT_NAME}_tests ${src})
    target_link_libraries(${PROJECT_NAME}_tests PRIVATE Catch2::Catch2WithMain ${PROJECT_NAME})
    
    if (UNIX)
        target_link_libraries(${PROJECT_NAME}_tests PRIVATE pthread)
    endif()
    
    target_compile_features(${PROJECT_NAME}_tests INTERFACE cxx_std_17)
    target_compile_options(${PROJECT_NAME}_tests INTERFACE -Wall -Werror -Wextra -pedantic)
    set_target_properties(${PROJECT_NAME}_tests PROPERTIES CXX_STANDARD 17 CXX_EXTENSIONS OFF CXX_STANDARD_REQUIRED ON)
endif()