# Clipping / filling 2D project

## Compiling

This part supposes that you have a working C++ compilation environment.

In all cases, you need the following libraries to compile the project:
* GLUT or FreeGLUT (the latter is maintained and modernised)
* GLEW

You can either install them system-wide or put them somewhere for CMake and the
compiler to find.

### With CMake

* create a build output directory and place yourself in it
* run `cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" <dir>`,
  where `<dir>` is the path to the project's working directory on your machine
* run `cmake --build . --target all -- -j 2`

### With your favorite IDE

Alternatively, a properly configured IDE that is compatible with
`CMakeLists.txt` files such as CLion should be able to easily build the project.

## Basic Usage

Run the program. An empty, black window will appear.

Middle mouse button opens the menu. By default, left mouse button draws a
polygon point by point. Right mouse button closes the polygon if at least 3
points have been placed.

Further possibilities are available via the menu.

All polygons must be declared counterclockwise for all functions to work.

## The Menu

The menu entries are as follows:

* _colors_: choose the colors for polygons, clipping windows, clipped polygons and
  filling
* _draw polygon to clip_: enable polygon drawing mode. In this mode, left clicking
  places a point and right clicking closes the polygon. This is the default mode
* _draw clipping window_: enable clipping window drawing mode. Works the same as
  polygon drawing mode, except it will draw clipping windows
* _add fill start point_: enable fill mode. In this mode, left clicking places a
  fill start point, from which filling will be done. Same as a bucket fill
* _clip all polygons_: clips all the polygons on the scene using all the windows
  on the scene, creating a new, clipped polygon for each existing polygon
* _clear everything_: clears the scene of all polygons, clipping windows and
  clipped polygons. Also empties the drawing points from polygon drawing mode or
  clipping window drawing mode