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




# Test executable for basic test
add_executable(tests tests/test.cpp)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(tests PRIVATE observer)

# Test executable for multi‑topic test
add_executable(multi_topic_test tests/multi_topic_test.cpp)
target_include_directories(multi_topic_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(multi_topic_test PRIVATE observer)
