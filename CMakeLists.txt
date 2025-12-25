cmake_minimum_required(VERSION 3.14)
project(observer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

add_library(observer STATIC
    src/observer.cpp
    src/observer_c.cpp
)

target_include_directories(observer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)



# Example executable
add_executable(example examples/example.cpp)

# Ensure example sees headers in src
target_include_directories(example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(example PRIVATE observer)

# Test executable
add_executable(tests tests/test.cpp)

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(tests PRIVATE observer)
