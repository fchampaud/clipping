//
// Created by Florian on 11/11/18.
//

#ifndef CLIPPER_CLIPPER_H
#define CLIPPER_CLIPPER_H

#include <vector>
#include <array>

namespace Clipping {
    class Clipper {
    public:
        std::vector<std::array<int, 2>> clip_polygon_to_window(std::vector<std::array<int, 2>>,
                                                               std::vector<std::array<int, 2>>);

        bool cuts(std::array<int, 2> &s1, std::array<int, 2> &e1, std::array<int, 2> &s2, std::array<int, 2> &e2);

        std::array<int, 2> *intersect(std::array<int, 2> &s1, std::array<int, 2> &e1, std::array<int, 2> &s2,
                                      std::array<int, 2> &e2);

        bool visible(std::array<int, 2> &p, std::array<int, 2> &seg_start, std::array<int, 2> &seg_end);

        std::array<int, 2> *norm(std::array<int, 2> &x1, std::array<int, 2> &y1);
    };
}

#endif //CLIPPER_CLIPPER_H
