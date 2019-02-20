//
// Created by esteban on 20/02/2019.
//

#ifndef CLIPPING_FILLER_H
#define CLIPPING_FILLER_H

#include <GL/glew.h>

#ifdef FREEGLUT
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#include <array>

#endif

namespace Clipping {
    class Filler {
    public:;
        static void RemplissageLigne(int x, int y, std::array<int,3> CC,  std::array<int,3> CR);
        static std::array<int,3> getPixelColor(int x, int y);
        static void drawLine(int x1, int y1, int x2 , std::array<int,3> C);
    };
}
#endif //CLIPPING_FILLER_H
