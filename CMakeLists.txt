cmake_minimum_required(VERSION 3.2)

project(mjson)

string(CONCAT CXX_FLAGS
  "-rdynamic " 
  "-Og "
  "-ggdb "
  "-std=c++20 "
  "-Werror "
  "-Wall "
  "-Wno-unused-variable "
  "-Wno-unused-function "
  "-Wno-unused-but-set-variable"
)

set(CMAKE_CXX_FLAGS ${CXX_FLAGS})

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/bin)

file(GLOB_RECURSE srcs "${PROJECT_SOURCE_DIR}/src/mjson/*.cc")
list(APPEND LIB_SRC ${srcs})

add_library(mjson SHARED ${LIB_SRC})

set(LIBS
  mjson
)

add_executable(test ${PROJECT_SOURCE_DIR}/tests/test.cc)
target_link_libraries(test ${LIBS})

add_executable(other_test ${PROJECT_SOURCE_DIR}/tests/other_test.cc)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)