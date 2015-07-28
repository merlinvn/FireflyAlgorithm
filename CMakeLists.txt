

cmake_minimum_required(VERSION 3.2)
project(FireflyAlgorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(MAINFOLDER $(PROJECT_SOURCE_DIR))
set(EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
set(LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")

include_directories("${MAINFOLDER}/src")


set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

include(cotire)
#
# Add Build Targets
#
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)

