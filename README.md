# Clipping / filling 2D project

## Usage

Run the program. An empty, black window will appear.

Middle mouse button opens the menu. By default, left mouse button draws a
polygon point by point. Right mouse button closes the polygon if at least 3
points have been placed.

## The menu

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