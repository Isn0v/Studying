cmake_minimum_required(VERSION 3.27)
project(NSTT13)

# enable_testing()

set(CMAKE_CXX_STANDARD 23)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined -fsanitize=leak")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(src)
add_subdirectory(src)

# add_subdirectory(test)

