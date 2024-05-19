# minimum CMake version required
cmake_minimum_required(VERSION 3.15)

# Project name, version and description
project(
  avformat-experiment
  VERSION 0.1.1
  LANGUAGES CXX
  DESCRIPTION "avformat-experiment")

set(MAIN_OUT main)
set(ENCODE_OUT encode)
set(OPUSF_OUT opusf)
set(CXX_STANDARD 17)

file(GLOB_RECURSE PROJECT_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

file(GLOB_RECURSE PROJECT_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.cpp)

file(GLOB_RECURSE MAIN_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main/*.cpp)

file(GLOB_RECURSE ENCODE_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/encode/*.cpp)

file(GLOB_RECURSE OPUSF_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/opusf/*.cpp)

# Create an executable
add_executable(
  # executable
  ${MAIN_OUT}
  # include files
  ${PROJECT_HEADER_FILES}
  # impl files
  ${PROJECT_SOURCE_FILES}
  ${MAIN_SOURCE_FILES})

# Create an executable
add_executable(
  # executable
  ${ENCODE_OUT}
  # include files
  ${PROJECT_HEADER_FILES}
  # impl files
  ${PROJECT_SOURCE_FILES}
  ${ENCODE_SOURCE_FILES})

# Create an executable
add_executable(
  # executable
  ${OPUSF_OUT}
  # include files
  ${PROJECT_HEADER_FILES}
  # impl files
  ${PROJECT_SOURCE_FILES}
  ${OPUSF_SOURCE_FILES})

add_subdirectory(libs)

# Linking libraries
target_link_libraries(
  ${MAIN_OUT} opusfile ogg opus
  # Add any other libs you want to use here
)
target_link_libraries(
  ${ENCODE_OUT} opusfile ogg opus
  # Add any other libs you want to use here
)

target_link_libraries(
  ${OPUSF_OUT} opusfile ogg opus
  # Add any other libs you want to use here
)

# Specify includes
target_include_directories(
  ${MAIN_OUT} PRIVATE include ${LIBS_INCLUDE_DIRS}
  # Remember to add the include directories of any other libraries too
)
target_include_directories(
  ${ENCODE_OUT} PRIVATE include ${LIBS_INCLUDE_DIRS}
  # Remember to add the include directories of any other libraries too
)

target_include_directories(
  ${OPUSF_OUT} PRIVATE include ${LIBS_INCLUDE_DIRS}
  # Remember to add the include directories of any other libraries too
)

target_link_directories(${MAIN_OUT} PRIVATE ${LIBS_LIBDIRS})
target_link_directories(${ENCODE_OUT} PRIVATE ${LIBS_LIBDIRS})
target_link_directories(${OPUSF_OUT} PRIVATE ${LIBS_LIBDIRS})

# Set C++ version
set_target_properties(
  ${MAIN_OUT}
  PROPERTIES CXX_STANDARD ${CXX_STANDARD}
             CXX_STANDARD_REQUIRED ON
             EXPORT_COMPILE_COMMANDS ON)

set_target_properties(
  ${ENCODE_OUT}
  PROPERTIES CXX_STANDARD ${CXX_STANDARD}
             CXX_STANDARD_REQUIRED ON
             EXPORT_COMPILE_COMMANDS ON)

set_target_properties(
  ${OPUSF_OUT}
  PROPERTIES CXX_STANDARD ${CXX_STANDARD}
             CXX_STANDARD_REQUIRED ON
             EXPORT_COMPILE_COMMANDS ON)
