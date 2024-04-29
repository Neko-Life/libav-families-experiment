# minimum CMake version required
cmake_minimum_required(VERSION 3.15)

# Project name, version and description
project(
  avformat-experiment
  VERSION 0.1.1
  LANGUAGES CXX
  DESCRIPTION "avformat-experiment")

set(MAIN_OUT main)
set(CXX_STANDARD 17)

file(GLOB_RECURSE PROJECT_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

file(GLOB_RECURSE PROJECT_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Create an executable
add_executable(
  # executable
  ${MAIN_OUT}
  # include files
  ${PROJECT_HEADER_FILES}
  # impl files
  ${PROJECT_SOURCE_FILES})

add_subdirectory(libs)

# Linking libraries
target_link_libraries(
  ${MAIN_OUT} opusfile ogg opus
  # Add any other libs you want to use here
)

# Specify includes
target_include_directories(
  ${MAIN_OUT} PRIVATE include ${LIBS_INCLUDE_DIRS}
  # Remember to add the include directories of any other libraries too
)

target_link_directories(${MAIN_OUT} PRIVATE ${LIBS_LIBDIRS})

# Set C++ version
set_target_properties(
  ${MAIN_OUT}
  PROPERTIES CXX_STANDARD ${CXX_STANDARD}
             CXX_STANDARD_REQUIRED ON
             EXPORT_COMPILE_COMMANDS ON)
