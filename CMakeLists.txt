cmake_minimum_required(VERSION 3.3)
project(Clipping)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
set(SOURCE_FILES main.cpp)
add_executable(test.out ${SOURCE_FILES})
target_link_libraries(test.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})