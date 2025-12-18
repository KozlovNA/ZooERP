cmake_minimum_required(VERSION 3.14)
project(ZooERP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(ENABLE_COVERAGE "Enable code coverage" ON)
option(CMAKE_BUILD_TYPE "Debug or Release" ON)

if(ENABLE_COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()
# --- GTest ---
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- Boost.DI ---
FetchContent_Declare(
  boost-di
  GIT_REPOSITORY https://github.com/boost-ext/di.git
  GIT_TAG        v1.3.0
)
FetchContent_MakeAvailable(boost-di)

# --- ZooLib ---
add_library(ZooLib src/Animals.cpp src/Zoo.cpp)
target_include_directories(ZooLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# --- ZooApp ---
add_executable(ZooApp src/main.cpp src/MenuSystem)
target_link_libraries(ZooApp PRIVATE ZooLib)
target_include_directories(ZooApp PRIVATE "${boost-di_SOURCE_DIR}/include")

# --- Tests ---
enable_testing()
add_executable(ZooTests tests/zoo_test.cpp)
target_link_libraries(ZooTests PRIVATE ZooLib gtest_main)

include(GoogleTest)
gtest_discover_tests(ZooTests)
