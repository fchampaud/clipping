//
// Created by florian on 29/01/19.
//

#ifndef CLIPPING_SCENE_H
#define CLIPPING_SCENE_H


#include <vector>
#include <array>

#include "Polygon.h"

namespace Clipping {
    struct Scene {
        std::vector<Polygon> polygons;
        std::vector<Polygon> windows;
        std::vector<Polygon> clippedPolygons;
        std::array<int, 4> colors;
        std::vector<std::array<float, 3>> colorPalette;
        int mode;
        std::vector<std::array<int, 2>> fillStartPoints;

        std::array<int, 2> currentPt;
        std::vector<std::array<int, 2>> pts;
        bool closed = false;
    };

    extern Scene scene;
    extern const int vp_width;
    extern const int vp_height;
}


#endif //CLIPPING_SCENE_H
