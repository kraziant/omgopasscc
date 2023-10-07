cmake_minimum_required(VERSION 3.5)
project(omgopasscc)

include_directories(${PROJECT_SOURCE_DIR}/inc/omgopasscc)

set(SOURCES sample/sample.cpp)

add_executable(sample ${SOURCES})
set_target_properties(
  sample
  PROPERTIES CXX_STANDARD 11
             CXX_STANDARD_REQUIRED ON
             CXX_EXTENSIONS OFF)
