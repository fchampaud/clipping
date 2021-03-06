//
// Created by florian on 17/02/19.
//

#include "clipper.h"
#include <GL/gl.h>
#include <iostream>
#include "Business.h"
#include "Scene.h"


void Clipping::Business::doTheClipping() {
    scene.clippedPolygons = scene.polygons;

    for (const auto &window : Clipping::scene.windows) {
        for (auto &polygon : scene.clippedPolygons) {
            polygon.points = Clipper::clip_polygon_to_window(polygon, window);
        }
    }
}

void Clipping::Business::doTheFilling() {
}

void Clipping::Business::fillPolygons() {
    glBegin(GL_POINTS);
    glColor3f(Clipping::scene.colorPalette[Clipping::scene.colors[3]][0],
              Clipping::scene.colorPalette[Clipping::scene.colors[3]][1],
              Clipping::scene.colorPalette[Clipping::scene.colors[3]][2]);
    for (auto &polygon : scene.polygons) {
        for (int i = polygon.points[0][0]; i < polygon.points[1][0]; ++i) {
            for (int j = polygon.points[0][1]; j < polygon.points[1][1]; ++j) {
                glVertex2i(i, j);
            }
        }
    }
    glEnd();
}
