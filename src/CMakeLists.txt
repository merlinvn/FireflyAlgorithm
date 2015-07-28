file(GLOB_RECURSE project_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)
#TODO: set lib
set(project_BIN ${PROJECT_NAME})

add_executable(${project_BIN} ${project_SRCS})

#TODO: link

#
#set(SOURCE_FILES main.cpp)
#add_executable(FireflyAlgorithm ${SOURCE_FILES})