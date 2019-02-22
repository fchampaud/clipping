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

/**
 * Returns whether segment {s1;e1} cuts segment {s2;e2}
 * @param s1 The start point of the first segment
 * @param e1 The end point of the first segment
 * @param s2 The start point of the second segment
 * @param e2 The end point of the second segment
 * @return True if the segments cut each other, false otherwise
 */
bool
Clipping::Clipper::cuts(const std::array<int, 2> &s1, const std::array<int, 2> &e1, const std::array<int, 2> &s2,
                        const std::array<int, 2> &e2) {
    return false;
}

/**
 * Returns the point of intersection between segments {s1;e1} and {s2;e2}
 * @param s1 The start point of the first segment
 * @param e1 The end point of the first segment
 * @param s2 The start point of the second segment
 * @param e2 The end point of the second segment
 * @return The point of intersection if the segments intersect, else null_ptr
 */
const std::array<int, 2> *
Clipping::Clipper::intersect(const std::array<int, 2> &s1, const std::array<int, 2> &e1, const std::array<int, 2> &s2,
                             const std::array<int, 2> &e2) {
    return &s1;
}

/**
 * Returns whether point p is visible to segment {seg_start;seg_end}
 * @param p The point which visibility is tested
 * @param seg_start The start point of the segment
 * @param seg_end The end point of the segment
 * @return True if the point is visible to the segment, false otherwise
 */
bool
Clipping::Clipper::visible(const std::array<int, 2> &p, const std::array<int, 2> &seg_start,
                           const std::array<int, 2> &seg_end) {
    return false;
}

/**
 * Returns the norm of segment {x1;y1}
 * @param x1 The start point of the segment
 * @param y1 The end point of the segment
 * @return A 2D vector representing the norm of the passed segment
 */
std::array<int, 2> *
Clipping::Clipper::norm(std::array<int, 2> &x1, std::array<int, 2> &y1) {
    return nullptr;
}
