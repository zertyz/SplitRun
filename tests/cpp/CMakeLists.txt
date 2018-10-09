cmake_minimum_required (VERSION 3.9)
project (SplitRunSpikes)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

if (NOT TARGET SplitRun)
	find_package(SplitRun REQUIRED)		# find_package is only needed if this CMakeLists.txt is called standalone (in opposition to being included by the uplevel CMakeLists.txt)
	add_library(SplitRun STATIC IMPORTED)
else()
	add_library(mutua::SplitRun ALIAS SplitRun)
endif()

add_executable(SplitRunSpikes SplitRunSpikes.cpp)
target_link_libraries(SplitRunSpikes PRIVATE mutua::SplitRun)

enable_testing()
add_test(NAME "${PROJECT_NAME}" COMMAND "./SplitRunSpikes")
