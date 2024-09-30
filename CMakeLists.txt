cmake_minimum_required(VERSION 3.14...3.29)

project(
    Automata
    VERSION 0.1
    DESCRIPTION "Cellular Automata Engine"
    LANGUAGES CXX
)

# Set Ce++ standard for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable folder support for IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# This does not automatically detect new source files. Re-run CMake as new source files are added
file(GLOB_RECURSE SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

# Set default build type to Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Compile options
add_compile_options(-Wall -Wextra -Wpedantic)

# Print all source files used to create executable
message(STATUS "Source Files:\n ${SOURCE_FILES}")

add_executable(automata ${SOURCE_FILES})

target_include_directories(automata PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)
