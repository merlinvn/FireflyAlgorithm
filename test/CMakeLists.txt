

file(GLOB_RECURSE project_SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp )
list(REMOVE_ITEM project_SRCS "${PROJECT_SOURCE_DIR}/src/main.cpp")

file (GLOB_RECURSE test_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)

set(test_LIBS )
set(test_BIN ${PROJECT_NAME}-unittests)

include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(${test_BIN} ${test_SRCS} ${project_SRCS})
cotire(${test_BIN})
#TARGET_LINK_LIBRARIES(${test_BIN} ${test_LIBS})