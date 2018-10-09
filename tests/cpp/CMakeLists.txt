cmake_minimum_required (VERSION 3.9)
project (SplitRunSpikes)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(SplitRunSpikes SplitRunSpikes.cpp)
target_link_libraries(SplitRunSpikes PRIVATE SplitRun)

enable_testing()
add_test(NAME "${PROJECT_NAME}" COMMAND "./SplitRunSpikes")
