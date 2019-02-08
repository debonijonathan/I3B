cmake_minimum_required(VERSION 3.11)
project(UnitTesting)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_CXX_FLAGS -fsanitize=address)

find_package(GTest REQUIRED)
enable_testing()


if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()

include_directories("../MockingbirdEngine")

list(APPEND SOURCES CameraTest.cpp
        ListTest.cpp
        LightTest.cpp
        MaterialTest.cpp
        MeshTest.cpp
        NodeTest.cpp
        ObjectTest.cpp
        TextureTest.cpp
        VertexTest.cpp
        TestLauncher.cpp)

add_executable(UnitTesting ${SOURCES})
add_test(NAME UnitTesting COMMAND UnitTesting -v)
target_link_libraries(UnitTesting LINK_PUBLIC MockingbirdEngine ${GTEST_BOTH_LIBRARIES})