//
// Created by florian on 17/02/19.
//

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

}
