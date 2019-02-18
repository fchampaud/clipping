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
        int mode;
        bool doFilling;
    };

    extern Scene scene;
}


#endif //CLIPPING_SCENE_H
