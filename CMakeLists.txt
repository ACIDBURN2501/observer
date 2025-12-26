cmake_minimum_required(VERSION 3.14)
project(observer VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# Option to build as shared library
option(BUILD_SHARED_LIBS "Build Observer as a shared library" OFF)

if(BUILD_SHARED_LIBS)
    add_library(observer SHARED
        src/observer.cpp
        src/observer_c.cpp)
else()
    add_library(observer STATIC
        src/observer.cpp
        src/observer_c.cpp)
endif()

# Ensure position independent code for shared builds
set_property(TARGET observer PROPERTY POSITION_INDEPENDENT_CODE ON)

# Alias for consistent use as a package
add_library(observer::observer ALIAS observer)

target_include_directories(observer
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Thread support
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(observer PUBLIC Threads::Threads)

# Testing
include(CTest)
if(BUILD_TESTING)
    # Basic test executable
    add_executable(tests tests/test.cpp)
    target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
    target_link_libraries(tests PRIVATE observer)
    add_test(NAME basic_test COMMAND tests)

    # Multi‑topic test executable
    add_executable(multi_topic_test tests/multi_topic_test.cpp)
    target_include_directories(multi_topic_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
    target_link_libraries(multi_topic_test PRIVATE observer)
    add_test(NAME multi_topic_test COMMAND multi_topic_test)

    # Thread‑safety test executable
    add_executable(thread_safety_test tests/thread_safety_test.cpp)
    target_include_directories(thread_safety_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
    target_link_libraries(thread_safety_test PRIVATE observer)
    add_test(NAME thread_safety_test COMMAND thread_safety_test)
endif()

# Install rules
include(GNUInstallDirs)

install(TARGETS observer
    EXPORT observerTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES src/observer.hpp src/observer_c.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT observerTargets
    FILE observerTargets.cmake
    NAMESPACE observer::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/observer)

