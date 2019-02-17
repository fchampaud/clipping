//#include <tclDecls.h>
#include "clipper.h"

std::vector<std::array<int, 2>>
Clipping::Clipper::clip_polygon_to_window(const Polygon &polygon, const Polygon &pw) {
    std::vector<std::array<int, 2>> ps;
    std::vector<std::array<int, 2>> pl {polygon.points};
    std::array<int, 2> s{};
    std::array<int, 2> f{};

    for (int i = 0; i < pw.points.size(); ++i) {
        ps.clear();

        for (int j = 0; j < pl.size(); ++j) {
            if (j == 0) {
                f = pl[j];
            } else {
                if (cuts(s, pl[j], pw.points[i], pw.points[i+1])) {
                    auto inter = intersect(s, pl[j], pw.points[i], pw.points[i + 1]);
                    ps.push_back(*inter);
                }
            }
            s = pl[j];

            if (visible(s, pw.points[i], pw.points[i+1])) {
                ps.push_back(s);
            }
        }

        if (!ps.empty()) {
            if (cuts(s, f, pw.points[i], pw.points[i+1])) {
                auto inter = intersect(s, f, pw.points[i], pw.points[i+1]);
                ps.push_back(*inter);
            }

            pl = ps;
        }
    }

    return ps;
}

bool
Clipping::Clipper::cuts(const std::array<int, 2> &s1, const std::array<int, 2> &e1, const std::array<int, 2> &s2,
                        const std::array<int, 2> &e2) {
    return false;
}

const std::array<int, 2> *
Clipping::Clipper::intersect(const std::array<int, 2> &s1, const std::array<int, 2> &e1, const std::array<int, 2> &s2,
                             const std::array<int, 2> &e2) {
    return &s1;
}

bool
Clipping::Clipper::visible(const std::array<int, 2> &p, const std::array<int, 2> &seg_start,
                           const std::array<int, 2> &seg_end) {
    return false;
}

std::array<int, 2> *
Clipping::Clipper::norm(std::array<int, 2> &x1, std::array<int, 2> &y1) {
    return nullptr;
}
