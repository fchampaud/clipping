//
// Created by florian on 17/02/19.
//

#include <GL/gl.h>
#include <iostream>
#include "Business.h"
#include "Scene.h"
#include "clipper.h"

void Clipping::Business::doTheClipping() {
    scene.clippedPolygons = scene.polygons;

    for (const auto &window : Clipping::scene.windows) {
        for (auto &polygon : scene.clippedPolygons) {
            polygon.points = Clipper::clip_polygon_to_window(polygon, window);
        }
    }
}

void Clipping::Business::doTheFilling() {
    Clipping::scene.doFilling = !Clipping::scene.doFilling;
}

void Clipping::Business::fillPolygons() {
    static const std::vector<std::array<float, 3>> colors = {
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1},
            {1, 1, 0}
    };

    glBegin(GL_POINTS);
    glColor3f(colors[Clipping::scene.colors[3]][0],
              colors[Clipping::scene.colors[3]][1],
              colors[Clipping::scene.colors[3]][2]);
    for (auto &polygon : scene.polygons) {
        for (int i = polygon.points[0][0]; i < polygon.points[1][0]; ++i) {
            for (int j = polygon.points[0][1]; j < polygon.points[1][1]; ++j) {
                glVertex2i(i, j);
            }
        }
    }
    glEnd();
}
