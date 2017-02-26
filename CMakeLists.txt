cmake_minimum_required(VERSION 3.6)
project(tourtre_simple)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_custom_target(tourtre_simple COMMAND make -C ${mytest_SOURCE_DIR}
	                         CLION_EXE_DIR=${PROJECT_BINARY_DIR})
