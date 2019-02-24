cmake_minimum_required(VERSION 3.3)

#set(CMAKE_VERBOSE_MAKEFILE TRUE)

project(Clipping)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
set(SOURCE_FILES main.cpp clipper.h clipper.cpp GUI.cpp GUI.h Scene.h Polygon.h Scene.cpp Business.cpp Business.h Filler.cpp Filler.h Display.cpp Display.h)
add_executable(test.out ${SOURCE_FILES})
target_link_libraries(test.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
