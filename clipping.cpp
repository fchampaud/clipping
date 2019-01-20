//#include <tclDecls.h>
#include "clipping.h"

std::vector<std::array<int, 2>>
Clipping::clip_polygon_to_window(std::vector<std::array<int, 2>> pl, std::vector<std::array<int, 2>> pw) {
    std::vector<std::array<int, 2>> ps;
    std::array<int, 2> s{};
    std::array<int, 2> f{};

    for (int i = 0; i < pw.size(); ++i) {
        ps.clear();

        for (int j = 0; j < pl.size(); ++j) {
            if (j == 0) {
                f = pl[j];
            } else {
                if (cuts(s, pl[j], pw[i], pw[i+1])) {
                    auto inter = intersect(s, pl[j], pw[i], pw[i + 1]);
                    ps.push_back(*inter);
                }
            }
            s = pl[j];

            if (visible(s, pw[i], pw[i+1])) {
                ps.push_back(s);
            }
        }

        if (!ps.empty()) {
            if (cuts(s, f, pw[i], pw[i+1])) {
                auto inter = intersect(s, f, pw[i], pw[i+1]);
                ps.push_back(*inter);
            }

            pl = ps;
        }
    }

    return ps;
}

bool Clipping::cuts(std::array<int, 2> &s1, std::array<int, 2> &e1, std::array<int, 2> &s2, std::array<int, 2> &e2) {
    return false;
}

std::array<int, 2> *
Clipping::intersect(std::array<int, 2> &s1, std::array<int, 2> &e1, std::array<int, 2> &s2, std::array<int, 2> &e2) {
    return &s1;
}

bool Clipping::visible(std::array<int, 2> &p, std::array<int, 2> &seg_start, std::array<int, 2> &seg_end) {
    return false;
}

/**
 * Dot product of two vectors
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @return the dot product of the two vectors (x1, y1), (x2, y2)
 */
float Clipping::dot(std::array<int, 2> &x1, std::array<int, 2> &y1, std::array<int, 2> &x2, std::array<int, 2> &y2) {
    return 1.F;
}

std::array<int, 2> *
Clipping::norm(std::array<int, 2> &x1, std::array<int, 2> &y1) {
    return nullptr;
}
