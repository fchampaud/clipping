#ifndef CLIPPER_CLIPPER_H
#define CLIPPER_CLIPPER_H

#include <vector>
#include <array>
#include "Polygon.h"

namespace Clipping {
    class Clipper {
    public:
        static std::vector<std::array<int, 2>> clip_polygon_to_window(const Clipping::Polygon &, const Polygon &);

        static bool cuts(const std::array<int, 2> &s1, const std::array<int, 2> &e1, const std::array<int, 2> &s2,
                         const std::array<int, 2> &e2);

        static const std::array<int, 2> * intersect(const std::array<int, 2> &p1, const std::array<int, 2> &p2,
                                                    const std::array<int, 2> &p3, const std::array<int, 2> &p4);

        static bool visible(const std::array<int, 2> &p, const std::array<int, 2> &seg_start,
                            const std::array<int, 2> &seg_end);

        static std::array<int, 2> norm(const std::array<int, 2> &x1, const std::array<int, 2> &y1);
    };
}

#endif //CLIPPER_CLIPPER_H
