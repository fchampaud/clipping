//#include <tclDecls.h>
#include <cmath>
#include <iostream>
#include "clipper.h"

std::vector<std::array<int, 2>>
Clipping::Clipper::clip_polygon_to_window(const Polygon &polygon, const Polygon &pw) {
    const auto pw_size = pw.points.size();
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
                if (cuts(s, pl[j], pw.points[i], pw.points[(i+1) % pw_size])) {
                    auto inter = intersect(s, pl[j], pw.points[i], pw.points[(i+1) % pw_size]);
                    if (inter != nullptr) {
                        ps.push_back(*inter);
                    }
                }
            }
            s = pl[j];

            if (visible(s, pw.points[i], pw.points[(i+1) % pw_size])) {
                ps.push_back(s);
            }
        }

        if (!ps.empty()) {
            if (cuts(s, f, pw.points[i], pw.points[(i+1) % pw_size])) {
                auto inter = intersect(s, f, pw.points[i], pw.points[(i+1) % pw_size]);
                if (inter != nullptr) {
                    ps.push_back(*inter);
                }
            }
            pl = ps;
        }
    }
    return pl;
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
    std::array<int, 4> a{};
    a[0] = e1[0] - s1[0];
    a[1] = s2[0] - e2[0];
    a[2] = e1[1] - s1[1];
    a[3] = s2[1] - e2[1];
    /**Calcul du determinant de A**/
    int deter = a[0] * a[3] - a[1] * a[2];
    return deter != 0;
}


/**
 * Returns the point of intersection between segments {p1;p2} and {p3;p4}
 * @param p1 The start point of the first segment
 * @param p2 The end point of the first segment
 * @param p3 The start point of the second segment
 * @param p4 The end point of the second segment
 * @return The point of intersection if the segments intersect, else null_ptr
 */
const std::array<int, 2>*
Clipping::Clipper::intersect(const std::array<int, 2> &p1,
                             const std::array<int, 2> &p2,
                             const std::array<int, 2> &p3,
                             const std::array<int, 2> &p4) {
    std::array<int, 4> a{};
    std::array<int, 2> b{};
    a[0] = p2[0] - p1[0];
    a[1] = p3[0] - p4[0];
    a[2] = p2[1] - p1[1];
    a[3] = p3[1] - p4[1];
    b[0] = p3[0] - p1[0];
    b[1] = p3[1] - p1[1];
    /**Calcul du determinant de A**/
    int deter = a[0] * a[3] - a[1] * a[2];
    if(deter!=0){
        /**Calcul de A-1**/
        std::array<double, 4> ai{};
        ai[0] = a[3] / static_cast<double>(deter);
        ai[1] = -(a[1]) / static_cast<double>(deter);
        ai[2] = -(a[2]) / static_cast<double>(deter);
        ai[3] = a[0] / static_cast<double>(deter);
        /**Resolution de l'équation X = A-1 * b**/
        double t = ai[0] * b[0] + ai[1] * b[1];
        //double s = ai[2] * b[0] + ai[3] * b[1];

        if (t < 0 || t > 1) {
            return nullptr;
        }

        auto *point = new std::array<int, 2>;
        point->at(0) = static_cast<int>(lround((1.F - t) * p1[0] + t * p2[0]));
        point->at(1) = static_cast<int>(lround((1.F - t) * p1[1] + t * p2[1]));
        return point;
    }
    else{
        return nullptr;
    }
}


/**
 * Returns whether point p is visible to segment {seg_start;seg_end}
 * @param p The point which visibility is tested
 * @param seg_start The start point of the segment
 * @param seg_end The end point of the segment
 * @return True if the point is visible to the segment, false otherwise
 */
bool
Clipping::Clipper::visible(const std::array<int, 2> &p,const std::array<int, 2> &seg_start,
                           const std::array<int, 2> &seg_end) {
    std::array<int, 2> normal = norm(seg_start,seg_end);
    std::array<int, 2> sp{};
    sp[0] = p[0] - seg_start[0];
    sp[1] = p[1] - seg_start[1];
    /**dot**/

    int dot = normal.at(0) * sp[0] + normal.at(1) * sp[1];
    if(dot > 0){ /**Si le point est a droite ( à verifier ) **/
        return true;
    }
    else{
        return false;
    }
}


/**
 * Returns the norm of segment {x1;y1}
 * @param x1 The start point of the segment
 * @param y1 The end point of the segment
 * @return A 2D vector representing the norm of the passed segment
 */
std::array<int, 2>
Clipping::Clipper::norm(const std::array<int, 2> &x1,const std::array<int, 2> &y1) {
    std::array<int, 2> normal{};
    /**sens trigonométrique (direct),**/
    normal.at(0) = -(y1[1] - x1[1]);
    normal.at(1) = y1[0] - x1[0];
    return normal;
}
