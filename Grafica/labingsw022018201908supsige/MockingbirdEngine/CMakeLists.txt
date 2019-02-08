cmake_minimum_required(VERSION 3.11)
project(tuna_ge)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_CXX_FLAGS -fsanitize=address)

# Dependencies

find_package(glm REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

# look for freeimage
FIND_PATH(FREEIMAGE_INCLUDE_DIR FreeImage.h
        /usr/local/include
        /usr/include
        /opt/local/include
        )
FIND_LIBRARY(FREEIMAGE_LIBRARY freeimage
        /usr/lib
        /usr/local/lib
        /opt/local/lib
        )

IF(FREEIMAGE_INCLUDE_DIR)
    IF(FREEIMAGE_LIBRARY)
        SET( FREEIMAGE_FOUND "YES" )
        SET( FREEIMAGE_LIBRARIES ${FREEIMAGE_LIBRARY} )
    ENDIF(FREEIMAGE_LIBRARY)
ENDIF(FREEIMAGE_INCLUDE_DIR)

message("FreeImage: ${STATUS_FREEIMG}")


# Testing Framework
#enable_testing()
#find_package(GTest REQUIRED)

#add_executable(NodeTest structure/object/Object.cpp structure/node/Node.cpp test/NodeTest.cpp)
#target_link_libraries(NodeTest ${GTEST_BOTH_LIBRARIES})
#add_test(NodeTest NodeTest)

#find_program(MEMORYCHECK_COMMAND valgrind)
#set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )

#find_program(VALGRIND "valgrind")
#if(VALGRIND)
#    add_custom_target(valgrind-tunage-nodetest
#            COMMAND "${VALGRIND}" --tool=memcheck --leak-check=full --show-reachable=yes --num-callers=20 --track-fds=yes $<TARGET_FILE:NodeTest>)
#endif()


add_library(MockingbirdEngine STATIC
            Object.cpp
            Node.cpp
            Camera.cpp
            Light.cpp
            List.cpp
            Material.cpp
            Mesh.cpp
            Texture.cpp
            Vertex.cpp
            Engine.cpp
            OvoReader.cpp
        )
include_directories(MockingbirdEngine ${GLM_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})
target_link_libraries(MockingbirdEngine ${GLM_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} )


IF(FREEIMAGE_FOUND)
    INCLUDE_DIRECTORIES(${FREEIMAGE_INCLUDE_DIR})
    TARGET_LINK_LIBRARIES(MockingbirdEngine ${FREEIMAGE_LIBRARY})
ENDIF(FREEIMAGE_FOUND)

target_include_directories (MockingbirdEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})