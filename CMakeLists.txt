cmake_minimum_required(VERSION 2.8)
add_definitions(-Wall -Wextra -pedantic -std=c++11)

include_directories(${PROJECT_SOURCE_DIR}/test/TestU01)
link_directories(${PROJECT_SOURCE_DIR}/test/TestU01/lib)
add_executable(main main.cpp)
target_link_libraries(main ${PROJECT_SOURCE_DIR}/test/TestU01/lib)
