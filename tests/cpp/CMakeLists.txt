cmake_minimum_required (VERSION 2.6)

project (SplitRunSpikes)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS -g)
set(CMAKE_CXX_FLAGS -O3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(SplitRunSpikes SplitRunSpikes.cpp ../../cpp/SplitRun.h ../../cpp/SplitRun.cpp)
