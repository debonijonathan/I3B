cmake_minimum_required(VERSION 3.11)
project(GauntletClient)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_CXX_FLAGS -fsanitize=address)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()

include_directories("../MockingbirdEngine")

list(APPEND SOURCES main.cpp)

add_executable(GauntletClient ${SOURCES})
target_link_libraries(GauntletClient LINK_PUBLIC MockingbirdEngine)