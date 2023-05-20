cmake_minimum_required(VERSION 3.14)
project(Containers VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_BUILD_TYPE Release)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_compile_options(-Wall -Werror -Wextra -Wpedantic)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

find_package(GTest REQUIRED)
include(GoogleTest)
enable_testing()

file(GLOB SOURCES ./test/*.cc)
add_executable(tests ${SOURCES})

target_link_libraries(tests GTest::gtest_main)

gtest_discover_tests(tests)
