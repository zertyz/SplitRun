# Usage:
#	TYPE="Debug";   rm -fr $TYPE; mkdir $TYPE; cd $TYPE; cmake -DCMAKE_BUILD_TYPE=$TYPE ..; make; ctest; cd ..; ls -l "$TYPE/tests/cpp/SplitRunSpikes"
#	TYPE="Release"; rm -fr $TYPE; mkdir $TYPE; cd $TYPE; cmake -DCMAKE_BUILD_TYPE=$TYPE ..; make; ctest; cd ..; ls -l "$TYPE/tests/cpp/SplitRunSpikes"

cmake_minimum_required (VERSION 3.9)
project (SplitRun VERSION 2018.10.09)

set(CMAKE_CXX_STANDARD 17)

add_library(SplitRun
            "cpp/SplitRun.h"  "cpp/SplitRun.cpp"
)
target_compile_definitions(SplitRun PUBLIC "SPLIT_RUN_DEBUG=$<CONFIG:Debug>")
target_include_directories(SplitRun PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()
add_subdirectory("tests/cpp")
