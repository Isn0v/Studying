cmake_minimum_required(VERSION 3.27)
project(NSTT5)

enable_testing()

set(CMAKE_CXX_STANDARD 23)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -O1 -ggdb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined -fsanitize=leak -v")

include_directories(src)
add_subdirectory(src)

add_subdirectory(test)

