//
// Created by florian on 29/01/19.
//

#ifndef CLIPPING_POLYGON_H
#define CLIPPING_POLYGON_H


#include <array>
#include <vector>

namespace Clipping {
    struct Polygon {
        std::vector<std::array<int, 2>> points;
    };
}


#endif //CLIPPING_POLYGON_H
