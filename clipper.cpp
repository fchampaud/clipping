//#include <tclDecls.h>
#include "clipper.h"

std::vector<std::array<int, 2>>
Clipper::clip_polygon_to_window(std::vector<std::array<int, 2>> pl, std::vector<std::array<int, 2>> pw) {
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

bool Clipper::cuts(std::array<int, 2> &s1, std::array<int, 2> &e1, std::array<int, 2> &s2, std::array<int, 2> &e2) {
    return false;
}

std::array<int, 2> *
Clipper::intersect(std::array<int, 2> &s1, std::array<int, 2> &e1, std::array<int, 2> &s2, std::array<int, 2> &e2) {
    return &s1;
}

bool Clipper::visible(std::array<int, 2> &p, std::array<int, 2> &seg_start, std::array<int, 2> &seg_end) {
    return false;
}

std::array<int, 2> *
Clipper::norm(std::array<int, 2> &x1, std::array<int, 2> &y1) {
    return nullptr;
}
